#include <iostream>
#include "lib/inc/pca8574_i2c_keypad.hpp"
#include <cstring>

int main(int argc, char const *argv[])
{

    Keypad keypad;

    while (1)
    {
        std::cout << "Key : " << keypad.getKey() << std::endl;
        usleep(500000);
    }

    return 0;
}
