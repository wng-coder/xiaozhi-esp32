# Complete MicroPython test for xiaozhi integration with RGB LED support
import spotpear
import time

def test_xiaozhi_integration():
    print("=== Xiaozhi Integration Test with RGB LED ===")
    
    # Initialize the spotpear board
    board = spotpear.Board()
    print("Board initialized successfully")
    
    # Test hardware functions first
    print("\n--- Hardware Functions Test ---")
    
    # Test sensors
    try:
        temp = board.get_temperature()
        print(f"Temperature: {temp}°C")
    except Exception as e:
        print(f"Temperature sensor error: {e}")
    
    try:
        humidity = board.get_humidity()
        print(f"Humidity: {humidity}%")
    except Exception as e:
        print(f"Humidity sensor error: {e}")
    
    try:
        accel_data = board.get_accelerometer()
        print(f"Accelerometer: {accel_data}")
    except Exception as e:
        print(f"Accelerometer error: {e}")
    
    # Test LED functions including new RGB LED
    print("\n--- LED Control Test ---")
    
    # Test basic LED functions
    print("Testing basic LED on/off...")
    board.led_on()
    time.sleep(0.5)
    board.led_off()
    time.sleep(0.5)
    
    # Test LED blink
    print("Testing LED blink...")
    board.led_blink(3)
    time.sleep(2)
    
    # Test new RGB LED function
    print("Testing RGB LED colors...")
    colors = [
        (255, 0, 0),    # Red
        (0, 255, 0),    # Green  
        (0, 0, 255),    # Blue
        (255, 255, 0),  # Yellow
        (255, 0, 255),  # Magenta
        (0, 255, 255),  # Cyan
        (255, 255, 255),# White
        (0, 0, 0)       # Off
    ]
    
    for i, (r, g, b) in enumerate(colors):
        print(f"Setting LED to RGB({r}, {g}, {b}) - {['Red', 'Green', 'Blue', 'Yellow', 'Magenta', 'Cyan', 'White', 'Off'][i]}")
        board.set_led(r, g, b)
        time.sleep(1)
    
    # Test xiaozhi application integration
    print("\n--- Xiaozhi Application Test ---")
    
    # Check initial status
    status = board.get_xiaozhi_status()
    print(f"Initial xiaozhi status: {status}")
    
    # Launch xiaozhi application
    print("Launching xiaozhi application...")
    launch_result = board.launch_xiaozhi_application()
    print(f"Launch result: {launch_result}")
    
    # Monitor xiaozhi status with RGB status indicators
    print("Monitoring xiaozhi status with RGB indicators...")
    for i in range(10):
        status = board.get_xiaozhi_status()
        is_running = status == 1
        print(f"Cycle {i+1}: Real xiaozhi running: {is_running}")
        
        # Use RGB LED to indicate status
        if is_running:
            # Green for running
            board.set_led(0, 255, 0)  
        else:
            # Red for not running
            board.set_led(255, 0, 0)  
            
        time.sleep(1)
    
    # Test concurrent operations
    print("\n--- Concurrent Operations Test ---")
    print("Testing concurrent xiaozhi + MicroPython operations...")
    
    for i in range(5):
        # Xiaozhi status
        status = board.get_xiaozhi_status()
        
        # Hardware sensor reading
        try:
            temp = board.get_temperature()
        except:
            temp = "N/A"
            
        # RGB LED cycling while xiaozhi runs
        color_cycle = [
            (255, 100, 0),   # Orange
            (100, 255, 100), # Light green
            (100, 100, 255), # Light blue
        ]
        r, g, b = color_cycle[i % len(color_cycle)]
        board.set_led(r, g, b)
        
        print(f"Concurrent test {i+1}: Xiaozhi={status}, Temp={temp}°C, LED=RGB({r},{g},{b})")
        time.sleep(1)
    
    # Test xiaozhi stop
    print("\n--- Xiaozhi Stop Test ---")
    print("Stopping xiaozhi application...")
    stop_result = board.stop_xiaozhi_application()
    print(f"Stop result: {stop_result}")
    
    time.sleep(2)
    final_status = board.get_xiaozhi_status()
    print(f"Final xiaozhi status: {final_status}")
    
    # Turn off RGB LED
    board.set_led(0, 0, 0)
    
    print("\n=== Integration Test Complete ===")

if __name__ == "__main__":
    test_xiaozhi_integration()