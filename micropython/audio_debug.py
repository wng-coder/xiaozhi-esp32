from machine import I2C, I2S, Pin, PWM
import time

# Generate MCLK for ES8311 codec using PWM
def setup_mclk(mclk_pin=16, sample_rate=24000):
    """Generate MCLK signal required by ES8311 codec."""
    mclk_freq = 256 * sample_rate  # 6.144MHz for 24kHz sample rate
    mclk_pwm = PWM(Pin(mclk_pin))
    mclk_pwm.freq(mclk_freq)
    mclk_pwm.duty_u16(32768)  # 50% duty cycle
    print(f"MCLK generated: {mclk_freq}Hz on pin {mclk_pin}")
    return mclk_pwm

# ES8311 register dump for debugging
def es8311_read_registers(i2c_port=0, addr=0x18):
    i2c = I2C(i2c_port, scl=Pin(14), sda=Pin(15), freq=100000)
    def read(reg):
        try:
            return i2c.readfrom_mem(addr, reg, 1)[0]
        except:
            return 0xFF
    
    print("ES8311 Register Dump:")
    important_regs = [0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 
                     0x0D, 0x0E, 0x12, 0x14, 0x15, 0x17, 0x31, 0x32, 0x37, 0x44, 0x45]
    for reg in important_regs:
        val = read(reg)
        print(f"  Reg 0x{reg:02X}: 0x{val:02X}")

# ES8311 initialization following exact C++ driver sequence
def es8311_init_exact_sequence(i2c_port=0, addr=0x18, pa_pin=46, sample_rate=24000):
    # Step 1: Setup MCLK signal first
    mclk_pwm = setup_mclk(mclk_pin=16, sample_rate=sample_rate)
    time.sleep_ms(50)
    
    i2c = I2C(i2c_port, scl=Pin(14), sda=Pin(15), freq=100000)
    def write(reg, val):
        i2c.writeto_mem(addr, reg, bytes([val]))
        print(f"Write reg 0x{reg:02X} = 0x{val:02X}")
    def read(reg):
        return i2c.readfrom_mem(addr, reg, 1)[0]
    
    print("Starting ES8311 exact C++ sequence...")
    
    # Exact sequence from C++ es8311_open() and es8311_start()
    
    # I2C noise immunity (from es8311_open)
    write(0x44, 0x08)
    write(0x44, 0x08)  # Write twice
    
    # Power management sequence (from es8311_open)
    write(0x01, 0x30)
    write(0x02, 0x10) 
    write(0x00, 0x00)
    write(0x00, 0x1F)
    write(0x01, 0x30)
    write(0x01, 0x00)
    write(0x45, 0x00)
    write(0x0D, 0xFC)  # Different from before!
    write(0x02, 0x00)
    
    # Clock coefficient configuration (exact from coeff table)
    # For 6144000Hz MCLK, 24kHz: pre_div=1, pre_multi=1, adc_div=1, dac_div=1, etc.
    regv = read(0x02) & 0x07
    regv |= ((1-1) << 5)  # pre_div = 1 -> 0
    regv |= (0 << 3)      # datmp = 0 (pre_multi=1)
    write(0x02, regv)
    
    regv = ((1-1) << 4) | ((1-1) << 0)  # Both dividers = 1 -> 0
    write(0x05, regv)
    
    regv = read(0x03) & 0x80
    regv |= (0 << 6) | (0x10 << 0)  # fs_mode=0, adc_osr=0x10
    write(0x03, regv)
    
    regv = read(0x04) & 0x80  
    regv |= (0x10 << 0)  # dac_osr=0x10
    write(0x04, regv)
    
    regv = read(0x07) & 0xC0
    regv |= (0 << 0)  # lrck_h=0
    write(0x07, regv)
    
    write(0x08, 0xFF)  # lrck_l=0xFF
    
    regv = read(0x06) & 0xE0
    regv |= ((4-1) << 0)  # bclk_div=4 -> 3
    write(0x06, regv)
    
    # Start sequence (from es8311_start)
    write(0x00, 0x80)  # Master clock enabled, slave mode
    write(0x01, 0x3F)  # Use MCLK, normal polarity
    
    # Enable DAC path (from es8311_start) 
    write(0x09, 0x4C)  # DAC I2S interface: 16-bit, enabled
    write(0x0A, 0x4C)  # ADC I2S interface: 16-bit, enabled (for completeness)
    
    # Audio path enables (from es8311_start)
    write(0x17, 0xBF)
    write(0x0E, 0x02) 
    write(0x12, 0x00)
    write(0x14, 0x1A)  # This is key - different value!
    write(0x0D, 0x01)  # Change from 0xFC to 0x01
    write(0x15, 0x40)
    write(0x37, 0x08)
    write(0x45, 0x00)
    
    # Unmute and volume (ensure DAC is active)
    write(0x31, 0x00)  # Unmute DAC
    write(0x32, 0xC0)  # High volume but not max
    
    # Enable PA last
    pa = Pin(pa_pin, Pin.OUT)
    pa.value(1)  # Enable PA
    time.sleep_ms(100)
    
    print("ES8311 exact sequence complete.")
    return mclk_pwm, pa

# Test with simple audio playback using exact sequence
def test_playback_simple(freq=1000, duration=2):
    import math
    
    mclk_pwm, pa_pin = es8311_init_exact_sequence()
    time.sleep_ms(200)  # Extra settling time
    
    # Use mono format to match simpler configuration
    i2s_out = I2S(1,
        sck=Pin(9), ws=Pin(45), sd=Pin(8),
        mode=I2S.TX, bits=16, format=I2S.MONO, rate=24000, ibuf=2048)
    
    print(f"Playing {freq}Hz test tone (mono, simplified)...")
    
    # Generate simpler audio pattern
    samples_per_cycle = 24000 // freq
    amplitude = 8000  # Lower amplitude to avoid clipping
    
    for _ in range(duration * 24000 // 256):
        buf = bytearray(256 * 2)  # 256 mono samples * 2 bytes
        for i in range(256):
            sample = int(amplitude * math.sin(2 * math.pi * i / samples_per_cycle))
            buf[i*2] = sample & 0xFF
            buf[i*2+1] = (sample >> 8) & 0xFF
        i2s_out.write(buf)
    
    i2s_out.deinit()
    print("Simple test tone done.")
    
    # Read back registers to verify configuration
    es8311_read_registers()
    
    return mclk_pwm, pa_pin

# Test PA pin configurations
def test_pa_configurations(freq=1000, duration=1):
    import math
    
    print("=== Testing PA Pin Configurations ===")
    
    # Initialize codec but don't set PA yet
    mclk_pwm = setup_mclk(mclk_pin=16, sample_rate=24000)
    time.sleep_ms(50)
    
    # Quick codec init without PA
    i2c = I2C(0, scl=Pin(14), sda=Pin(15), freq=100000)
    def write(reg, val):
        i2c.writeto_mem(0x18, reg, bytes([val]))
    
    # Minimal codec setup
    write(0x44, 0x08)
    write(0x00, 0x1F)
    time.sleep_ms(10) 
    write(0x00, 0x80)
    write(0x01, 0x3F)
    write(0x09, 0x4C)
    write(0x31, 0x00)
    write(0x32, 0xC0)
    write(0x14, 0x1A)
    write(0x0D, 0x01)
    
    # Test different PA configurations
    pa = Pin(46, Pin.OUT)
    
    configs = [
        ("PA High", 1),
        ("PA Low", 0),
        ("PA High (retry)", 1)
    ]
    
    for config_name, pa_value in configs:
        print(f"\n--- Testing {config_name} ---")
        pa.value(pa_value)
        time.sleep_ms(100)
        
        # Quick tone test
        i2s_out = I2S(1, sck=Pin(9), ws=Pin(45), sd=Pin(8), mode=I2S.TX, bits=16, format=I2S.MONO, rate=24000, ibuf=1024)
        
        samples_per_cycle = 24000 // freq
        for _ in range(duration * 24000 // 128):
            buf = bytearray(128 * 2)
            for i in range(128):
                sample = int(16000 * math.sin(2 * math.pi * i / samples_per_cycle))
                buf[i*2] = sample & 0xFF
                buf[i*2+1] = (sample >> 8) & 0xFF
            i2s_out.write(buf)
        
        i2s_out.deinit()
        print(f"{config_name} test done - do you hear audio?")
        time.sleep_ms(500)
    
    return mclk_pwm, pa