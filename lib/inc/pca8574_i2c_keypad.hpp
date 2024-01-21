// Header: PCA8574 Keypad Cpp Driver Header File
// File Name: pca8574_i2c_keypad.hpp
// Author: Turgay Hopal
// Date: 1.1.2024

#include <iostream>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

// INSRUCTIONS

constexpr uint8_t ENABLE_INTERRUPTS = 0xF0;
constexpr uint8_t READ_ROWS = 0xF0;
constexpr uint8_t READ_COLS = 0x0F;

typedef struct
{
    const char *i2c_device_path;
    uint8_t slave_addr;
} keypad_config_t;

typedef enum keypad_key_e
{
    KEYPAD_KEY_1 = 0x01,
    KEYPAD_KEY_2,
    KEYPAD_KEY_3,
    KEYPAD_KEY_4,
    KEYPAD_KEY_5,
    KEYPAD_KEY_6,
    KEYPAD_KEY_7,
    KEYPAD_KEY_8,
    KEYPAD_KEY_9,
    KEYPAD_KEY_10,
    KEYPAD_KEY_11,
    KEYPAD_KEY_12,
    KEYPAD_KEY_13,
    KEYPAD_KEY_14,
    KEYPAD_KEY_15,
    KEYPAD_KEY_16,
    KEYPAD_KEY_NONE,
} keypad_key_t;

class Keypad
{
private:
    keypad_config_t config;

    void keypad_init(keypad_config_t config);
    void write_bytes_i2c(uint8_t *data, uint8_t size);
    int8_t read_bytes_i2c(uint8_t mask);

public:
    keypad_key_t getKey();

    Keypad();
    Keypad(keypad_config_t config);
};
