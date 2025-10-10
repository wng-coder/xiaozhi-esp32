# Simple MicroPython test for board module
# Copy and paste this into the MicroPython REPL

print("Testing board module...")

try:
    import board
    print("✓ board module imported successfully")
    
    # Create board instance
    b = board.Board()
    print("✓ Board instance created")
    
    # Test get_type
    board_type = b.get_type()
    print(f"Board type: {board_type}")
    
    # Test get_uuid  
    board_uuid = b.get_uuid()
    print(f"Board UUID: {board_uuid}")
    
    print("✓ All tests passed!")
    
except Exception as e:
    print(f"✗ Error: {e}")
    import sys
    sys.print_exception(e)