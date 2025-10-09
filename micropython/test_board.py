#!/usr/bin/env python3
"""
Test script for ESP32-S3 1.28 BOX board functionality with MicroPython
Tests board functions, PSRAM, I2C, and displays system information
"""

import sys
import gc
import machine
import time
try:
    import esp32
    esp32_available = True
except ImportError:
    esp32_available = False

def test_system_info():
    """Test basic system information"""
    print("=== System Information ===")
    print(f"MicroPython version: {sys.version}")
    print(f"Platform: {sys.platform}")
    
    if esp32_available:
        try:
            if hasattr(esp32, 'flash_size'):
                print(f"Flash size: {esp32.flash_size()} bytes")
            if hasattr(esp32, 'flash_user_start'):
                print(f"Flash user start: {esp32.flash_user_start()}")
        except Exception as e:
            print(f"ESP32 info not available: {e}")
    
    # Memory information
    print(f"Free memory: {gc.mem_free()} bytes")
    print(f"Allocated memory: {gc.mem_alloc()} bytes")
    
    # CPU frequency
    print(f"CPU frequency: {machine.freq()} Hz")
    print()

def test_psram():
    """Test PSRAM functionality"""
    print("=== PSRAM Test ===")
    print(f"Initial free memory: {gc.mem_free()} bytes")
    
    # Check if esp32 module has PSRAM info
    if esp32_available:
        try:
            # Try to get PSRAM info if available
            if hasattr(esp32, 'spiram_size'):
                print(f"SPIRAM size: {esp32.spiram_size()} bytes")
            if hasattr(esp32, 'spiram_available'):
                print(f"SPIRAM available: {esp32.spiram_available()}")
            else:
                print("No SPIRAM functions available in esp32 module")
        except Exception as e:
            print(f"No SPIRAM info available from esp32 module: {e}")
    
    # Test progressive allocations to find actual limit
    sizes = [100*1024, 200*1024, 400*1024, 512*1024, 1024*1024]  # 100KB to 1MB
    
    try:
        for size in sizes:
            try:
                print(f"Testing {size//1024}KB allocation...")
                large_data = bytearray(size)
                large_data[0] = 0xAA
                large_data[-1] = 0x55
                
                if large_data[0] == 0xAA and large_data[-1] == 0x55:
                    print(f"✓ {size//1024}KB allocation successful")
                    print(f"  Free memory after: {gc.mem_free()} bytes")
                else:
                    print(f"✗ {size//1024}KB data integrity failed")
                
                del large_data
                gc.collect()
                print(f"  Free memory after cleanup: {gc.mem_free()} bytes")
                
            except MemoryError as e:
                print(f"✗ {size//1024}KB allocation failed: {e}")
                print(f"  Maximum allocatable size appears to be < {size//1024}KB")
                break
            except Exception as e:
                print(f"✗ {size//1024}KB test error: {e}")
                break
        
        # PSRAM diagnosis
        max_free = gc.mem_free()
        if max_free < 1024*1024:  # Less than 1MB
            print(f"\n⚠️  PSRAM appears NOT active - only {max_free//1024}KB available")
            print("   This suggests PSRAM initialization failed")
        else:
            print(f"\n✓ PSRAM appears active - {max_free//1024//1024}MB+ available")
                
    except Exception as e:
        print(f"✗ PSRAM test failed: {e}")
    print()

def test_gpio():
    """Test GPIO functionality"""
    print("=== GPIO Test ===")
    try:
        # Test LED pin if available (pin 48 based on our config)
        led_pin = machine.Pin(48, machine.Pin.OUT)
        
        print("Testing LED blink...")
        for i in range(3):
            led_pin.on()
            time.sleep(0.2)
            led_pin.off() 
            time.sleep(0.2)
        print("✓ GPIO/LED test completed")
        
    except Exception as e:
        print(f"✗ GPIO test failed: {e}")
    print()

def test_i2c():
    """Test I2C functionality"""
    print("=== I2C Test ===")
    try:
        # Audio Codec I2C (from config.h: SDA=15, SCL=14)
        i2c_codec = machine.I2C(0, scl=machine.Pin(14), sda=machine.Pin(15))
        devices_codec = i2c_codec.scan()
        print(f"Audio Codec I2C (SCL=14, SDA=15) devices: {[hex(addr) for addr in devices_codec]}")
        if 0x18 in devices_codec:  # ES8311_CODEC_DEFAULT_ADDR is typically 0x18
            print("  ✓ ES8311 Audio Codec detected!")
        
        # Touchpad I2C (from config.h: SDA=11, SCL=7)
        i2c_touch = machine.I2C(1, scl=machine.Pin(7), sda=machine.Pin(11))
        devices_touch = i2c_touch.scan()
        print(f"Touchpad I2C (SCL=7, SDA=11) devices: {[hex(addr) for addr in devices_touch]}")
        if devices_touch:
            print(f"  ✓ Touch controller detected at address(es): {[hex(addr) for addr in devices_touch]}")
        
        print("✓ I2C scan completed with correct hardware pins")
        
    except Exception as e:
        print(f"✗ I2C test failed: {e}")
    print()

def test_board_wrapper():
    """Test custom board wrapper functions if available"""
    print("=== Board Wrapper Test ===")
    try:
        # Try to import our custom spotpear module
        import spotpear
        print("✓ Spotpear module loaded")
        
        # Test board functions
        board = spotpear.SpotpearBoard()
        print("✓ SpotpearBoard class instantiated")
        
        # Test if methods are available
        methods = [attr for attr in dir(board) if not attr.startswith('_')]
        print(f"Available methods: {methods}")
        
    except ImportError:
        print("ℹ Spotpear module not available (expected in some builds)")
    except Exception as e:
        print(f"✗ Board wrapper test failed: {e}")
    print()

def main():
    """Main test function"""
    print("=" * 50)
    print("ESP32-S3 1.28 BOX MicroPython Board Test")
    print("=" * 50)
    
    test_system_info()
    test_psram()
    test_gpio()
    test_i2c()
    test_board_wrapper()
    
    print("=" * 50)
    print("Board test completed!")
    print("=" * 50)

if __name__ == '__main__':
    main()