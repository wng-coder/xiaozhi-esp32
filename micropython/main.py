from machine import Pin, I2C, SPI, Timer, PWM
import time
from audio import record_mic, play_sound

# Pin assignments from config.h
AUDIO_I2S_GPIO_MCLK = 16
AUDIO_I2S_GPIO_WS   = 45
AUDIO_I2S_GPIO_BCLK = 9
AUDIO_I2S_GPIO_DIN  = 10
AUDIO_I2S_GPIO_DOUT = 8

AUDIO_CODEC_PA_PIN      = 46
AUDIO_CODEC_I2C_SDA_PIN = 15
AUDIO_CODEC_I2C_SCL_PIN = 14

BUILTIN_LED_GPIO   = 48
BOOT_BUTTON_GPIO   = 0

DISPLAY_WIDTH      = 240
DISPLAY_HEIGHT     = 240
DISPLAY_MIRROR_X   = True
DISPLAY_MIRROR_Y   = False
DISPLAY_SWAP_XY    = False
DISPLAY_OFFSET_X   = 0
DISPLAY_OFFSET_Y   = 0

DISPLAY_BACKLIGHT_PIN           = 42
DISPLAY_BACKLIGHT_OUTPUT_INVERT = True

DISPLAY_SPI_SCLK_PIN  = 4
DISPLAY_SPI_MOSI_PIN  = 2
DISPLAY_SPI_CS_PIN    = 5
DISPLAY_SPI_DC_PIN    = 47
DISPLAY_SPI_RESET_PIN = 38

TP_PIN_NUM_TP_SDA = 11
TP_PIN_NUM_TP_SCL = 7
TP_PIN_NUM_TP_RST = 6
TP_PIN_NUM_TP_INT = 12

DISPLAY_SPI_SCLK_HZ = 40_000_000

# --- Touchpad (CST816D) ---
class Cst816d:
    def __init__(self, i2c, addr=0x15):
        self.i2c = i2c
        self.addr = addr
        self.tp = {'num': 0, 'x': -1, 'y': -1}
        chip_id = self.read_reg(0xA3)
        print("Get chip ID: 0x{:02X}".format(chip_id))

    def read_reg(self, reg):
        return self.i2c.readfrom_mem(self.addr, reg, 1)[0]

    def read_regs(self, reg, length):
        return self.i2c.readfrom_mem(self.addr, reg, length)

    def update_touch_point(self):
        buf = self.read_regs(0x02, 6)
        if buf[0] == 0xFF:
            buf[0] = 0x00
        self.tp['num'] = buf[0] & 0x01
        self.tp['x'] = ((buf[1] & 0x0F) << 8) | buf[2]
        self.tp['y'] = ((buf[3] & 0x0F) << 8) | buf[4]

    def get_touch_point(self):
        return self.tp

# --- Display (GC9A01) ---
# You need a MicroPython driver for GC9A01, e.g. https://github.com/jeffmer/micropython_gc9a01
try:
    from gc9a01 import GC9A01
except ImportError:
    GC9A01 = None
    print("GC9A01 driver not found. Please install it for display support.")

class CustomLcdDisplay:
    def __init__(self, spi, cs, dc, rst, width, height):
        if GC9A01:
            self.display = GC9A01(spi, cs=cs, dc=dc, rst=rst, width=width, height=height)
        else:
            self.display = None
        # Add padding to status bar if needed (LVGL not available in MicroPython)
        # self.display.fill_rect(...)

# --- Button ---
class Button:
    def __init__(self, pin_num):
        self.pin = Pin(pin_num, Pin.IN, Pin.PULL_UP)
        self.last_state = self.pin.value()
        self.callback = None

    def on_click(self, callback):
        self.callback = callback

    def check(self):
        state = self.pin.value()
        if self.last_state == 1 and state == 0:
            if self.callback:
                self.callback()
        self.last_state = state

# --- Power Save Timer ---
class PowerSaveTimer:
    def __init__(self, sleep_time=60):
        self.timer = Timer(-1)
        self.sleep_time = sleep_time

    def start(self):
        self.timer.init(period=self.sleep_time * 1000, mode=Timer.ONE_SHOT, callback=self.enter_sleep)

    def enter_sleep(self, t):
        print("Entering deep sleep")
        # machine.deepsleep()

# --- Main Board Setup ---
def main():
    # I2C for codec and touch
    i2c_codec = I2C(0, scl=Pin(AUDIO_CODEC_I2C_SCL_PIN), sda=Pin(AUDIO_CODEC_I2C_SDA_PIN), freq=400000)
    i2c_touch = I2C(1, scl=Pin(TP_PIN_NUM_TP_SCL), sda=Pin(TP_PIN_NUM_TP_SDA), freq=400000)

    # SPI for display
    spi = SPI(2, baudrate=DISPLAY_SPI_SCLK_HZ, polarity=0, phase=0,
              sck=Pin(DISPLAY_SPI_SCLK_PIN), mosi=Pin(DISPLAY_SPI_MOSI_PIN))
    cs  = Pin(DISPLAY_SPI_CS_PIN, Pin.OUT)
    dc  = Pin(DISPLAY_SPI_DC_PIN, Pin.OUT)
    rst = Pin(DISPLAY_SPI_RESET_PIN, Pin.OUT)

    display = CustomLcdDisplay(spi, cs, dc, rst, DISPLAY_WIDTH, DISPLAY_HEIGHT)

    # Touchpad
    touchpad = Cst816d(i2c_touch)

    # Button
    button = Button(BOOT_BUTTON_GPIO)
    def on_button():
        print("Button clicked! Recording...")
        audio = record_mic(3)  # Record 3 seconds
        print("Playing back...")
        play_sound(audio)
    button.on_click(on_button)

    # Power save
    power_save = PowerSaveTimer(60)
    power_save.start()

    # LED and Backlight
    led = Pin(BUILTIN_LED_GPIO, Pin.OUT)
    backlight = PWM(Pin(DISPLAY_BACKLIGHT_PIN))
    backlight.freq(1000)
    backlight.duty_u16(65535 if not DISPLAY_BACKLIGHT_OUTPUT_INVERT else 0)

    # Main loop
    while True:
        button.check()
        touchpad.update_touch_point()
        tp = touchpad.get_touch_point()
        if tp['num'] > 0:
            print("Touch at x={}, y={}".format(tp['x'], tp['y']))
        time.sleep(0.01)

main()
