/********************************************************************************
* @file     clock_test_sample.c                                                 *
* @brief    An example implementing MCO clock out                               *
* @author   Yeshvanth M  <yeshvanthmuniraj@gmail.com>                           *
* @date     09-Jan-2023                                                         *
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

#include "system/system_config.h"
#include "/hal/gpio/hal_gpio.h"

int main()
{
    system_config_t config = LOW_POWER;
    hal_gpio_t gpio = 
    {
        .pin = PIN_8,
        .port = PORTA,
        .func = CLOCK_OUT,
    };
    
    system_config_init (config);
    hal_gpio_config_port (&gpio, true, false);
    hal_gpio_config_pin (&gpio);
    
    /* 
    For STM32F401 Target:
        For LOW_POWER, SYSCLK is 64 MHz and HCLK is 8 MHz 
        The MCO1 outputs 64 MHz / 4 = 16 MHz clock in PA8.
        
        For HIGH_PERFORMANCE, SYSCLK is 84 MHz and HCLK is also 84 MHz 
        The MCO1 outputs 84 MHz / 4 = 21 MHz clock in PA8. 
    
    For STM32F429 Target:
        For LOW_POWER, SYSCLK is 32 MHz and HCLK is 32 MHz 
        The MCO1 outputs 32 MHz / 4 = 8 MHz clock in PA8. 
    
        For HIGH_PERFORMANCE, SYSCLK is 168 MHz and HCLK is also 168 MHz 
        The MCO1 outputs 168 MHz / 4 = 42 MHz clock in PA8. 
    */
    
    for(;;);
}
