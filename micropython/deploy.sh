#!/bin/bash

# ESP32-S3 MicroPython Deployment Script
# Automates firmware flashing and file transfer

set -e  # Exit on any error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
FIRMWARE_DIR="$SCRIPT_DIR/micropython_src/ports/esp32/build-ESP32_S3_1_28_BOX"
PORT="${1:-auto}"  # USB port, auto-detect if not specified
BAUD_RATE=460800

echo "=========================================="
echo "ESP32-S3 MicroPython Deployment Script"
echo "=========================================="

# Function to detect ESP32 device
detect_device() {
    echo "🔍 Detecting ESP32 device..."
    
    # Common USB device paths for ESP32
    POSSIBLE_PORTS=(
        "/dev/ttyUSB0"
        "/dev/ttyUSB1" 
        "/dev/ttyACM0"
        "/dev/ttyACM1"
        "/dev/cu.usbserial-*"
        "/dev/cu.SLAB_USBtoUART"
    )
    
    if [ "$PORT" = "auto" ]; then
        for port in "${POSSIBLE_PORTS[@]}"; do
            if [ -e "$port" ] || ls $port 2>/dev/null; then
                PORT="$port"
                echo "✅ Found device at: $PORT"
                return 0
            fi
        done
        
        echo "❌ No ESP32 device detected automatically"
        echo "   Please specify port manually: $0 /dev/ttyUSB0"
        echo "   Available ports:"
        ls /dev/tty* 2>/dev/null | grep -E "(USB|ACM|SLAB)" || echo "   None found"
        exit 1
    else
        if [ -e "$PORT" ]; then
            echo "✅ Using specified port: $PORT"
        else
            echo "❌ Specified port not found: $PORT"
            exit 1
        fi
    fi
}

# Function to check firmware files
check_firmware() {
    echo "🔍 Checking firmware files..."
    
    if [ ! -f "$FIRMWARE_DIR/micropython.bin" ]; then
        echo "❌ MicroPython firmware not found!"
        echo "   Please build first: make BOARD=ESP32_S3_1_28_BOX"
        exit 1
    fi
    
    echo "✅ Firmware files found:"
    echo "   Bootloader: $(ls -lh $FIRMWARE_DIR/bootloader/bootloader.bin | awk '{print $5}')"
    echo "   Partition:  $(ls -lh $FIRMWARE_DIR/partition_table/partition-table.bin | awk '{print $5}')"  
    echo "   Firmware:   $(ls -lh $FIRMWARE_DIR/micropython.bin | awk '{print $5}')"
}

# Function to flash firmware
flash_firmware() {
    echo "🔥 Flashing MicroPython firmware..."
    
    cd "$FIRMWARE_DIR"
    
    # Erase flash first (recommended for clean install)
    echo "🗑️  Erasing flash..."
    python -m esptool --chip esp32s3 --port "$PORT" erase_flash
    
    echo "📤 Flashing firmware components..."
    python -m esptool \
        --chip esp32s3 \
        --port "$PORT" \
        --baud $BAUD_RATE \
        --before default_reset \
        --after hard_reset \
        write_flash \
        --flash_mode dio \
        --flash_freq 80m \
        --flash_size 16MB \
        0x0 bootloader/bootloader.bin \
        0x8000 partition_table/partition-table.bin \
        0x10000 micropython.bin
    
    echo "✅ Firmware flashed successfully!"
}

# Function to wait for device to boot
wait_for_boot() {
    echo "⏳ Waiting for device to boot..."
    sleep 3
    
    # Try to connect and get initial response
    timeout 10 python -c "
import serial
import time
try:
    ser = serial.Serial('$PORT', 115200, timeout=2)
    ser.write(b'\\r\\n')
    time.sleep(1)
    response = ser.read(100)
    if b'>>>' in response or b'MicroPython' in response:
        print('✅ MicroPython is responding')
    else:
        print('⚠️  Device may still be booting')
    ser.close()
except Exception as e:
    print(f'⚠️  Could not connect: {e}')
" 2>/dev/null || echo "⚠️  Boot check timeout (normal for first boot)"
}

# Function to transfer test file
transfer_test_file() {
    echo "📁 Transferring test file..."
    
    TEST_FILE="$SCRIPT_DIR/test_board.py"
    
    if [ ! -f "$TEST_FILE" ]; then
        echo "❌ Test file not found: $TEST_FILE"
        return 1
    fi
    
    # Use ampy tool if available, otherwise provide manual instructions
    if command -v ampy >/dev/null 2>&1; then
        echo "📤 Using ampy to transfer file..."
        ampy --port "$PORT" put "$TEST_FILE" main.py
        echo "✅ Test file transferred as main.py"
    else
        echo "ℹ️  ampy tool not available. Manual file transfer needed:"
        echo "   1. Install ampy: pip install adafruit-ampy"  
        echo "   2. Transfer file: ampy --port $PORT put $TEST_FILE main.py"
        echo "   3. Or copy-paste the test script via REPL"
    fi
}

# Function to show connection instructions
show_connection_info() {
    echo ""
    echo "🔗 Connection Information:"
    echo "   Serial Port: $PORT"
    echo "   Baud Rate:   115200"
    echo "   Connection:  minicom -D $PORT -b 115200"
    echo "   Or:          screen $PORT 115200"
    echo ""
    echo "📋 Manual Test Steps:"
    echo "   1. Connect: minicom -D $PORT -b 115200"
    echo "   2. Press ENTER to get Python prompt (>>>)"
    echo "   3. Run: exec(open('main.py').read())  # If file was transferred"
    echo "   4. Or copy-paste the test script content"
    echo ""
    echo "🧪 Expected Test Results:"
    echo "   • System info with MicroPython version"
    echo "   • PSRAM test with 1MB allocation"  
    echo "   • GPIO LED blinking test"
    echo "   • I2C device scanning"
    echo "   • Board wrapper availability check"
}

# Main execution
main() {
    detect_device
    check_firmware  
    
    echo ""
    read -p "📋 Ready to flash firmware to $PORT? (y/N): " -n 1 -r
    echo
    
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        flash_firmware
        wait_for_boot
        transfer_test_file
        show_connection_info
        
        echo ""
        echo "🎉 Deployment completed successfully!"
        echo "   Your ESP32-S3 is now running MicroPython with PSRAM support"
    else
        echo "❌ Deployment cancelled"
        exit 1
    fi
}

# Run main function
main "$@"