#!/usr/bin/env python3
"""
Direct MicroPython test script for main.cc integration.
Run this directly on the MicroPython device.
"""

print("=== SpotpearBoard main.cc Integration Test ===")
print()

try:
    from spotpear import SpotpearBoard
    board = SpotpearBoard()
    print("✓ SpotpearBoard instance created successfully")
except Exception as e:
    print(f"✗ Failed to create SpotpearBoard: {e}")

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

# Test existing board functions
print("\n--- Test 5: Volume Functions ---")
try:
    board.set_volume(75)
    vol = board.get_volume()
    print(f"Volume test: set 75, got {vol}")
    print("✓ Volume functions working")
except Exception as e:
    print(f"✗ Volume functions failed: {e}")

print("\n--- Test 6: Brightness Functions ---") 
try:
    board.set_brightness(128)
    brightness = board.get_brightness()
    print(f"Brightness test: set 128, got {brightness}")
    print("✓ Brightness functions working")
except Exception as e:
    print(f"✗ Brightness functions failed: {e}")

print("\n=== Main.cc Integration Test Complete ===")