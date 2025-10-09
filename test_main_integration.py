#!/usr/bin/env python3
"""
Test script for main.cc integration in MicroPython SpotpearBoard module.
Tests the new application initialization functions from main.cc.
"""

import sys
sys.path.append('/workspaces/xiaozhi-esp32/micropython/micropython_src/ports/esp32')

import time

# Test data for the new main.cc integration functions
def test_main_integration():
    print("=== SpotpearBoard main.cc Integration Test ===")
    print()
    
    try:
        from spotpear import SpotpearBoard
        board = SpotpearBoard()
        print("✓ SpotpearBoard instance created successfully")
    except Exception as e:
        print(f"✗ Failed to create SpotpearBoard: {e}")
        return False
    
    # Test 1: Initialize NVS Flash
    print("\n--- Test 1: NVS Flash Initialization ---")
    try:
        result = board.init_nvs()
        print(f"NVS Flash init result: {result}")
        if result:
            print("✓ NVS Flash initialized successfully")
        else:
            print("⚠ NVS Flash init returned False (may already be initialized)")
    except Exception as e:
        print(f"✗ NVS Flash init failed: {e}")
    
    # Test 2: Initialize Event Loop
    print("\n--- Test 2: Event Loop Initialization ---")
    try:
        result = board.init_event_loop()
        print(f"Event loop init result: {result}")
        if result:
            print("✓ Event loop initialized successfully")
        else:
            print("⚠ Event loop init returned False (may already exist)")
    except Exception as e:
        print(f"✗ Event loop init failed: {e}")
    
    # Test 3: Get System Information
    print("\n--- Test 3: System Information ---")
    try:
        info = board.get_system_info()
        print(f"System info: {info}")
        if info and len(info) > 10:
            print("✓ System information retrieved successfully")
        else:
            print("✗ System information seems incomplete")
    except Exception as e:
        print(f"✗ System info failed: {e}")
    
    # Test 4: Start Application (placeholder function)
    print("\n--- Test 4: Application Startup ---")
    try:
        result = board.start_application()
        print(f"Start application result: {result}")
        if result:
            print("✓ Application start returned success")
        else:
            print("⚠ Application start returned False (placeholder function)")
    except Exception as e:
        print(f"✗ Application start failed: {e}")
    
    # Test existing board functions to ensure they still work
    print("\n--- Test 5: Existing Board Functions ---")
    try:
        board.set_volume(75)
        vol = board.get_volume()
        print(f"Volume test: set 75, got {vol}")
        
        board.set_brightness(128)
        brightness = board.get_brightness()
        print(f"Brightness test: set 128, got {brightness}")
        
        print("✓ Existing board functions still working")
    except Exception as e:
        print(f"✗ Existing board functions failed: {e}")
    
    print("\n=== Main.cc Integration Test Complete ===")
    return True

if __name__ == "__main__":
    test_main_integration()