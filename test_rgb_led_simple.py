# Simple RGB LED test to verify the set_led function
import spotpear
import time

def test_rgb_led():
    print("Testing RGB LED function...")
    
    try:
        # Initialize board
        board = spotpear.Board()
        print("✅ Board initialized successfully")
        
        # Test set_led function
        print("🔴 Testing RGB LED - Red")
        board.set_led(255, 0, 0)
        time.sleep(1)
        
        print("🟢 Testing RGB LED - Green") 
        board.set_led(0, 255, 0)
        time.sleep(1)
        
        print("🔵 Testing RGB LED - Blue")
        board.set_led(0, 0, 255)
        time.sleep(1)
        
        print("⚫ LED Off")
        board.set_led(0, 0, 0)
        
        print("✅ RGB LED function working correctly!")
        return True
        
    except AttributeError as e:
        print(f"❌ RGB LED function not found: {e}")
        return False
    except Exception as e:
        print(f"❌ Error testing RGB LED: {e}")
        return False

if __name__ == "__main__":
    test_rgb_led()