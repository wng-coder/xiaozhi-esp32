#!/usr/bin/env python3
"""
Quick PSRAM test for ESP32-S3 with newly flashed PSRAM-enabled firmware
"""

import gc
import time

def test_psram_simple():
    """Quick PSRAM functionality test"""
    print("=== PSRAM Test ===")
    print(f"Initial free memory: {gc.mem_free()} bytes")
    
    try:
        # Test progressively larger allocations
        sizes = [100*1024, 500*1024, 1024*1024, 2*1024*1024]  # 100KB, 500KB, 1MB, 2MB
        
        for size in sizes:
            print(f"\nTesting {size//1024}KB allocation...")
            try:
                data = bytearray(size)
                data[0] = 0xAA
                data[-1] = 0x55
                
                if data[0] == 0xAA and data[-1] == 0x55:
                    print(f"✓ {size//1024}KB allocation successful")
                    print(f"  Free memory after allocation: {gc.mem_free()} bytes")
                else:
                    print(f"✗ {size//1024}KB data integrity failed")
                
                del data
                gc.collect()
                
            except MemoryError as e:
                print(f"✗ {size//1024}KB allocation failed: {e}")
                break
            except Exception as e:
                print(f"✗ {size//1024}KB test error: {e}")
                break
                
        print(f"\nFinal free memory: {gc.mem_free()} bytes")
        
    except Exception as e:
        print(f"✗ PSRAM test failed: {e}")

if __name__ == '__main__':
    test_psram_simple()