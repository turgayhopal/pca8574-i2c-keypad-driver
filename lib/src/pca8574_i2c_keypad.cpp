// Header: LCD I2C (Liquid Crystal) Cpp Driver Source File
// File Name: lcd_i2c.cpp
// Author: Turgay Hopal
// Date: 1.1.2024

#include "../inc/pca8574_i2c_keypad.hpp"

Keypad::Keypad()
{
    keypad_config_t config = {"/dev/i2c-1", 0x38};
    keypad_init(config);
}

Keypad::Keypad(keypad_config_t config)
{
    keypad_init(config);
}

keypad_key_t Keypad::getKey()
{
    uint8_t press_key, rows, cols;

    rows = read_bytes_i2c(READ_ROWS);
    if (rows == READ_ROWS)
    {
        return KEYPAD_KEY_NONE;
    }
    else if (rows == 0xE0)
    {
        press_key = 0;
    }
    else if (rows == 0xD0)
    {
        press_key = 1;
    }
    else if (rows == 0xB0)
    {
        press_key = 2;
    }
    else if (rows == 0x70)
    {
        press_key = 3;
    }
    cols = read_bytes_i2c(READ_COLS);
    if (cols == READ_COLS)
    {
        return KEYPAD_KEY_NONE;
    }
    else if (cols == 0x0E)
    {
        press_key += 0;
    }
    else if (cols == 0x0D)
    {
        press_key += 4;
    }
    else if (cols == 0x0B)
    {
        press_key += 8;
    }
    else if (cols == 0x07)
    {
        press_key += 12;
    }

    return (keypad_key_t) press_key;

}

void Keypad::keypad_init(keypad_config_t config)
{
    this->config.i2c_device_path = config.i2c_device_path;
    this->config.slave_addr = config.slave_addr;
    read_bytes_i2c(ENABLE_INTERRUPTS);
}

void Keypad::write_bytes_i2c(uint8_t *data, uint8_t size)
{
    int file;

    if ((file = open(this->config.i2c_device_path, O_RDWR)) < 0)
    {
    }
    else
    {
        if (ioctl(file, I2C_SLAVE, this->config.slave_addr) < 0)
        {
        }
        else
        {
            if (write(file, data, size) == size)
            {
            }
        }
    }

    close(file);
}

int8_t Keypad::read_bytes_i2c(uint8_t mask)
{
    char rx_buffer[1];

    write_bytes_i2c(&mask, 1);

    int file;

    if ((file = open(this->config.i2c_device_path, O_RDWR)) < 0)
    {
        close(file);
        return -1;
    }
    else
    {
        if (ioctl(file, I2C_SLAVE, this->config.slave_addr) < 0)
        {
            close(file);
            return -1;
        }
        else
        {
            if (read(file, rx_buffer, 1) != 1)
            {
                close(file);
                return -1;
            }
        }
    }

    close(file);

    return (uint8_t)rx_buffer[0];
}
