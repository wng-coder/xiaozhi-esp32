# Enhanced MicroPython Board Module Test
# Copy and paste this into the MicroPython REPL

print("Testing enhanced board module...")

try:
    import board
    print("✓ Board module imported")
    
    # Create board instance
    b = board.Board()
    print("✓ Board instance created")
    
    # Test basic info
    board_type = b.get_type()
    print(f"Board type: {board_type}")
    
    board_uuid = b.get_uuid()
    print(f"Board UUID: {board_uuid}")
    
    # Test new functionality
    print("\n--- Testing System Info ---")
    system_info = b.get_system_info()
    print(f"System info: {system_info}")
    
    print("\n--- Testing Battery Level ---")
    battery_result = b.get_battery_level()
    success, level, charging, discharging = battery_result
    print(f"Battery - Success: {success}, Level: {level}%, Charging: {charging}, Discharging: {discharging}")
    
    print("\n--- Testing Temperature ---")
    temp_result = b.get_temperature()
    success, temperature = temp_result
    print(f"Temperature - Success: {success}, Value: {temperature}°C")
    
    print("\n✓ All enhanced board module tests passed!")
    
except Exception as e:
    print(f"✗ Error: {e}")
    import sys
    sys.print_exception(e)