#!/usr/bin/env python3
import serial
import time
import sys

def test_board_module():
    try:
        # Connect to ESP32-S3
        print("Connecting to ESP32-S3 at /dev/ttyACM0...")
        ser = serial.Serial('/dev/ttyACM0', 115200, timeout=2)
        
        # Wait for MicroPython to boot and clear any boot messages
        time.sleep(3)
        ser.reset_input_buffer()
        
        # Send a newline to get a clean prompt
        ser.write(b'\r\n')
        time.sleep(0.5)
        ser.reset_input_buffer()
        
        # Test import board
        print("\n1. Testing import board...")
        ser.write(b'import board\r\n')
        time.sleep(0.5)
        response = ser.read(ser.in_waiting or 1).decode('utf-8', errors='ignore')
        print(f"Response: {repr(response)}")
        
        # Test get_type
        print("\n2. Testing board.get_type()...")
        ser.write(b'print(board.get_type())\r\n')
        time.sleep(0.5)
        response = ser.read(ser.in_waiting or 1).decode('utf-8', errors='ignore')
        print(f"Response: {repr(response)}")
        
        # Test get_uuid
        print("\n3. Testing board.get_uuid()...")
        ser.write(b'print(board.get_uuid())\r\n')
        time.sleep(0.5)
        response = ser.read(ser.in_waiting or 1).decode('utf-8', errors='ignore')
        print(f"Response: {repr(response)}")
        
        # Test completion message
        ser.write(b'print("Board module works!")\r\n')
        time.sleep(0.5)
        response = ser.read(ser.in_waiting or 1).decode('utf-8', errors='ignore')
        print(f"Final response: {repr(response)}")
        
        ser.close()
        print("\nBoard module test completed successfully!")
        
    except Exception as e:
        print(f"Error testing board module: {e}")
        return False
    
    return True

if __name__ == "__main__":
    test_board_module()