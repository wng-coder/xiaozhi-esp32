#!/bin/bash

# Quick verification script for MicroPython integration
# Checks if all components are ready for deployment

echo "🔍 MicroPython Integration Verification"
echo "======================================"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/micropython_src/ports/esp32/build-ESP32_S3_1_28_BOX"

# Check build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "❌ Build directory not found: $BUILD_DIR"
    echo "   Run: make BOARD=ESP32_S3_1_28_BOX"
    exit 1
fi

echo "✅ Build directory found"

# Check firmware files
REQUIRED_FILES=(
    "micropython.bin"
    "bootloader/bootloader.bin" 
    "partition_table/partition-table.bin"
)

echo ""
echo "📁 Firmware Files:"
for file in "${REQUIRED_FILES[@]}"; do
    filepath="$BUILD_DIR/$file"
    if [ -f "$filepath" ]; then
        size=$(ls -lh "$filepath" | awk '{print $5}')
        echo "  ✅ $file ($size)"
    else
        echo "  ❌ $file (missing)"
        MISSING_FILES=true
    fi
done

if [ "$MISSING_FILES" = true ]; then
    echo ""
    echo "❌ Missing firmware files. Please rebuild:"
    echo "   cd micropython_src/ports/esp32"
    echo "   make BOARD=ESP32_S3_1_28_BOX clean"
    echo "   make BOARD=ESP32_S3_1_28_BOX"
    exit 1
fi

# Check board configuration
echo ""
echo "⚙️  Board Configuration:"
BOARD_DIR="$SCRIPT_DIR/micropython_src/ports/esp32/boards/ESP32_S3_1_28_BOX"
CONFIG_FILES=(
    "mpconfigboard.h"
    "sdkconfig.board"
    "mpconfigboard.cmake"
)

for file in "${CONFIG_FILES[@]}"; do
    if [ -f "$BOARD_DIR/$file" ]; then
        echo "  ✅ $file"
    else
        echo "  ❌ $file"
    fi
done

# Check test script
echo ""
echo "🧪 Test Script:"
if [ -f "$SCRIPT_DIR/test_board.py" ]; then
    lines=$(wc -l < "$SCRIPT_DIR/test_board.py")
    echo "  ✅ test_board.py ($lines lines)"
else
    echo "  ❌ test_board.py (missing)"
fi

# Check deployment script
echo ""
echo "🚀 Deployment:"
if [ -f "$SCRIPT_DIR/deploy.sh" ] && [ -x "$SCRIPT_DIR/deploy.sh" ]; then
    echo "  ✅ deploy.sh (executable)"
else
    echo "  ❌ deploy.sh (missing or not executable)"
fi

# Show key configuration details
echo ""
echo "🔧 Key Configuration:"
if [ -f "$BOARD_DIR/mpconfigboard.h" ]; then
    psram=$(grep "MICROPY_HW_PSRAM" "$BOARD_DIR/mpconfigboard.h" | grep -v "//" | head -1)
    bluetooth=$(grep "MICROPY_PY_BLUETOOTH" "$BOARD_DIR/mpconfigboard.h" | grep -v "//" | head -1)
    echo "  PSRAM: $psram"
    echo "  Bluetooth: $bluetooth"
fi

if [ -f "$BOARD_DIR/sdkconfig.board" ]; then
    spiram=$(grep "CONFIG_SPIRAM=y" "$BOARD_DIR/sdkconfig.board" || echo "CONFIG_SPIRAM not found")
    bt_enabled=$(grep "CONFIG_BT_ENABLED=n" "$BOARD_DIR/sdkconfig.board" || echo "CONFIG_BT_ENABLED not set")
    echo "  ESP-IDF SPIRAM: $spiram"
    echo "  ESP-IDF Bluetooth: $bt_enabled"
fi

# Show flash command
echo ""
echo "📤 Flash Command:"
echo "  esptool.py --chip esp32s3 --port /dev/ttyUSB0 --baud 460800 \\"
echo "    --before default_reset --after hard_reset write_flash \\"
echo "    --flash_mode dio --flash_freq 80m --flash_size 16MB \\"
echo "    0x0 bootloader/bootloader.bin \\"
echo "    0x8000 partition_table/partition-table.bin \\"
echo "    0x10000 micropython.bin"

# Show sizes
echo ""
echo "📊 Size Information:"
total_size=0
for file in "${REQUIRED_FILES[@]}"; do
    if [ -f "$BUILD_DIR/$file" ]; then
        size_bytes=$(stat -c%s "$BUILD_DIR/$file")
        size_kb=$((size_bytes / 1024))
        total_size=$((total_size + size_bytes))
        printf "  %-30s %6d KB\n" "$file" "$size_kb"
    fi
done
total_kb=$((total_size / 1024))
echo "  $(printf '%-30s %6d KB' 'Total firmware size:' $total_kb)"

# Check available space
app_partition_size=$((2048 * 1024))  # 2MB app partition
free_space=$((app_partition_size - $(stat -c%s "$BUILD_DIR/micropython.bin")))
free_kb=$((free_space / 1024))
free_percent=$((free_space * 100 / app_partition_size))
echo "  $(printf '%-30s %6d KB (%d%%)' 'Free app space:' $free_kb $free_percent)"

echo ""
echo "✅ MicroPython integration verification complete!"
echo ""
echo "🚀 Next Steps:"
echo "   1. Connect ESP32-S3 device via USB"
echo "   2. Run: ./deploy.sh"
echo "   3. Connect: minicom -D /dev/ttyUSB0 -b 115200"
echo "   4. Test: exec(open('main.py').read())"