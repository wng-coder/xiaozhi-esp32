
from machine import I2C, I2S, Pin, PWM
import time, math, gc

class ES8311Audio:
    def __init__(self, sample_rate=24000, buffer_size=2048, pa_pin=46, mclk_pin=16):
        self.sample_rate = sample_rate
        self.buffer_size = buffer_size
        self.pa_pin = pa_pin
        self.mclk_pin = mclk_pin
        self.mclk_pwm = None
        self.i2c_port = 0
        self.addr = 0x18

    def setup_mclk(self):
        mclk_freq = 256 * self.sample_rate
        self.mclk_pwm = PWM(Pin(self.mclk_pin))
        self.mclk_pwm.freq(mclk_freq)
        self.mclk_pwm.duty_u16(32768)
        print(f"MCLK generated: {mclk_freq}Hz on pin {self.mclk_pin}")
        return self.mclk_pwm

    def es8311_init(self):
        self.setup_mclk()
        time.sleep_ms(50)
        i2c = I2C(self.i2c_port, scl=Pin(14), sda=Pin(15), freq=100000)
        def write(reg, val):
            i2c.writeto_mem(self.addr, reg, bytes([val]))
        def read(reg):
            return i2c.readfrom_mem(self.addr, reg, 1)[0]
        write(0x44, 0x08)
        write(0x44, 0x08)
        write(0x01, 0x30)
        write(0x02, 0x10)
        write(0x00, 0x00)
        write(0x00, 0x1F)
        write(0x01, 0x30)
        write(0x01, 0x00)
        write(0x45, 0x00)
        write(0x0D, 0xFC)
        write(0x02, 0x00)
        write(0x00, 0x80)
        write(0x01, 0x3F)
        regv = read(0x02) & 0x07
        regv |= ((1-1) << 5)
        regv |= (0 << 3)
        write(0x02, regv)
        regv = ((1-1) << 4) | ((1-1) << 0)
        write(0x05, regv)
        regv = read(0x03) & 0x80
        regv |= (0 << 6) | (0x10 << 0)
        write(0x03, regv)
        regv = read(0x04) & 0x80
        regv |= (0x10 << 0)
        write(0x04, regv)
        regv = read(0x07) & 0xC0
        regv |= (0 << 0)
        write(0x07, regv)
        write(0x08, 0xFF)
        regv = read(0x06) & 0xE0
        regv |= ((4-1) << 0)
        write(0x06, regv)
        write(0x09, 0x4C)
        write(0x0A, 0x4C)
        write(0x17, 0xBF)
        write(0x0E, 0x02)
        write(0x12, 0x00)
        write(0x14, 0x1A)
        write(0x0D, 0x01)
        write(0x15, 0x40)
        write(0x37, 0x08)
        write(0x45, 0x00)
        write(0x31, 0x00)
        write(0x32, 0xFF)
        pa = Pin(self.pa_pin, Pin.OUT)
        pa.value(1)
        time.sleep_ms(10)
        print("ES8311 fully configured.")
        return self.mclk_pwm

    def record_mic(self, duration_sec=5, filename="mic_record.raw"):
        self.es8311_init()
        time.sleep_ms(100)
        try:
            i2s_in = I2S(0,
                sck=Pin(9), ws=Pin(45), sd=Pin(10),
                mode=I2S.RX, bits=16, format=I2S.MONO, rate=self.sample_rate, ibuf=self.buffer_size)
            print("Recording mic to file...", filename)
            t_end = time.ticks_add(time.ticks_ms(), duration_sec * 1000)
            with open(filename, "wb") as f:
                while time.ticks_diff(t_end, time.ticks_ms()) > 0:
                    buf = bytearray(self.buffer_size)
                    num_bytes = i2s_in.readinto(buf)
                    if num_bytes:
                        f.write(buf[:num_bytes])
            i2s_in.deinit()
            print("Recording done.")
        except Exception as e:
            print(f"Error during recording: {e}")
            gc.collect()
        return filename

    def play_sound_file(self, filename):
        self.es8311_init()
        time.sleep_ms(100)
        try:
            i2s_out = I2S(1,
                sck=Pin(9), ws=Pin(45), sd=Pin(8),
                mode=I2S.TX, bits=16, format=I2S.MONO, rate=self.sample_rate, ibuf=self.buffer_size)
            print("Playing sound from file (mono)...", filename)
            with open(filename, "rb") as f:
                bytes_played = 0
                while True:
                    chunk = f.read(self.buffer_size)
                    if not chunk:
                        break
                    i2s_out.write(chunk)
                    bytes_played += len(chunk)
            i2s_out.deinit()
            print(f"Playback done. Played {bytes_played} bytes.")
        except Exception as e:
            print(f"Error during playback: {e}")
            gc.collect()
        return self.mclk_pwm

    def play_test_tone(self, freq=440, duration=2):
        self.es8311_init()
        time.sleep_ms(100)
        try:
            i2s_out = I2S(1,
                sck=Pin(9), ws=Pin(45), sd=Pin(8),
                mode=I2S.TX, bits=16, format=I2S.STEREO, rate=self.sample_rate, ibuf=self.buffer_size)
            print(f"Playing {freq}Hz test tone...")
            samples_per_cycle = self.sample_rate // freq
            amplitude = 16000
            for _ in range(duration * self.sample_rate // 512):
                buf = bytearray(512 * 4)
                for i in range(512):
                    sample = int(amplitude * math.sin(2 * math.pi * i / samples_per_cycle))
                    buf[i*4] = sample & 0xFF
                    buf[i*4+1] = (sample >> 8) & 0xFF
                    buf[i*4+2] = sample & 0xFF
                    buf[i*4+3] = (sample >> 8) & 0xFF
                i2s_out.write(buf)
            i2s_out.deinit()
            print("Test tone done.")
        except Exception as e:
            print(f"Error during test tone: {e}")
            gc.collect()
        return self.mclk_pwm