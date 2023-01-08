/********************************************************************************
* @file     led_chaser.c                                                        *
* @brief    GPIO example implementing an LED chaser                             *
* @author   Yeshvanth M  <yeshvanthmuniraj@gmail.com>                           *
* @date     19-Dec-2022                                                         *
*********************************************************************************
*                                                                               *
* This program is free software: you can redistribute it and/or modify it       *
* under the terms of the GNU General Public License as published by the Free    *
* Software Foundation, either version 3 of the License, or (at your option)     *
* any later version.                                                            *
*                                                                               *
* This program is distributed in the hope that it will be useful, but           *
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY    *
* or FITNESS FOR A PARTICULAR PURPOSE.                                          *
* See the GNU General Public License for more details.                          *
*                                                                               *
* You should have received a copy of the GNU General Public License             *
* along with this program. If not, see <https://www.gnu.org/licenses/>.         *
*                                                                               *
********************************************************************************/

#include "/hal/gpio/hal_gpio.h"

static hal_gpio_t led_array;

static void setup_led_array(void)
{
    led_array.port = PORTA;
    
    /* Enable the port */
    hal_gpio_config_port (&led_array, true, false);
    
    for (uint8_t pin = 0u; pin < 7u; pin++)
    {
        led_array.pin = pin;
        led_array.func = LED;
        hal_gpio_config_pin (&led_array);
    }
}

int main()
{
    uint8_t led_bits_array;
    uint16_t mask;
    led_bits_array = 1u;
    mask = 0xFu;
    
    setup_led_array();
    
    while (1) {
        hal_gpio_write_port (&led_array, (uint16_t)led_bits_array, mask);
        led_bits_array = (uint8_t)(led_bits_array << 1u);
        delay();
    }
    
}