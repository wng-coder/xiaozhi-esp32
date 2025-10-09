# Test both I2C scan and RGB LED functions
import spotpear
import time

def test_missing_functions():
    print("=== Testing Missing Functions ===")
    
    try:
        # Initialize board
        board = spotpear.SpotpearBoard()
        print("✅ Board initialized successfully")
        
        # Test I2C scan function
        print("\n🔍 Testing I2C scan function...")
        try:
            devices = board.i2c_scan()
            print(f"✅ I2C scan successful! Found devices: {devices}")
        except AttributeError as e:
            print(f"❌ I2C scan function not found: {e}")
            
        # Test RGB LED function
        print("\n🌈 Testing RGB LED function...")
        try:
            print("🔴 Setting LED to Red")
            board.set_led(255, 0, 0)
            time.sleep(1)
            
            print("🟢 Setting LED to Green") 
            board.set_led(0, 255, 0)
            time.sleep(1)
            
            print("⚫ Turning LED off")
            board.set_led(0, 0, 0)
            print("✅ RGB LED function working!")
        except AttributeError as e:
            print(f"❌ RGB LED function not found: {e}")
            
        # Test xiaozhi integration
        print("\n🚀 Testing xiaozhi integration...")
        try:
            status = board.get_xiaozhi_status() 
            print(f"✅ Xiaozhi status: {status}")
            
            if status == 0:
                print("Launching xiaozhi...")
                board.launch_xiaozhi_application()
                time.sleep(2)
                status = board.get_xiaozhi_status()
                print(f"Xiaozhi status after launch: {status}")
        except AttributeError as e:
            print(f"❌ Xiaozhi function not found: {e}")
            
        print("\n🎉 Function test complete!")
        
    except Exception as e:
        print(f"❌ Error during testing: {e}")

if __name__ == "__main__":
    test_missing_functions()