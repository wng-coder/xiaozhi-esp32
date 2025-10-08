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
        print(f"Flash size: {esp32.flash_size()} bytes")
        print(f"Flash user start: {esp32.flash_user_start()}")
    
    # Memory information
    print(f"Free memory: {gc.mem_free()} bytes")
    print(f"Allocated memory: {gc.mem_alloc()} bytes")
    
    # CPU frequency
    print(f"CPU frequency: {machine.freq()} Hz")
    print()

def test_psram():
    """Test PSRAM functionality"""
    print("=== PSRAM Test ===")
    try:
        # Try to allocate large memory to use PSRAM
        large_data = bytearray(1024 * 1024)  # 1MB allocation
        large_data[0] = 0xAA
        large_data[-1] = 0x55
        
        if large_data[0] == 0xAA and large_data[-1] == 0x55:
            print("✓ PSRAM allocation and access test passed")
            print(f"  Allocated 1MB, start=0x{large_data[0]:02X}, end=0x{large_data[-1]:02X}")
        else:
            print("✗ PSRAM data integrity test failed")
        
        del large_data
        gc.collect()
        print("✓ PSRAM memory released")
        
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
        # Test I2C0 (pins 8/9)
        i2c0 = machine.I2C(0, scl=machine.Pin(9), sda=machine.Pin(8))
        devices0 = i2c0.scan()
        print(f"I2C0 (SCL=9, SDA=8) devices: {[hex(addr) for addr in devices0]}")
        
        # Test I2C1 (pins 17/18) 
        i2c1 = machine.I2C(1, scl=machine.Pin(18), sda=machine.Pin(17))
        devices1 = i2c1.scan()
        print(f"I2C1 (SCL=18, SDA=17) devices: {[hex(addr) for addr in devices1]}")
        
        print("✓ I2C scan completed")
        
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