/********************************************************************************
* @file     hal_gpio.c                                                          *
* @brief    File includes implementations of GPIO HAL functions.                *
* @author   Yeshvanth M  <yeshvanthmuniraj@gmail.com>                           *
* @date     25-Dec-2022                                                         *
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

static GPIO_TypeDef* map_gpio_port(uint8_t port);

void hal_gpio_enable(hal_gpio_pin_t* pin)
{
    driver_gpio_pinConfig_t gpioPin;
    
    gpioPin.pInst = map_gpio_port(pin->port);
    gpioPin.param.pinNumber = pin->number;
    
    switch (pin->func) 
    {
        case LED:
        {
            gpioPin.param.pinMode = OUTPUT;
            gpioPin.param.pinSpeed = LOW;
            gpioPin.param.pinOpType = PUSH_PULL;
            gpioPin.param.pinPuPdControl = NO_PUPD;
            break;
        }
        case ONBOARD_BUTTON:
        {
            
            break;
        }
        case EXT_BUTTON_PD:
        
    }
}

static GPIO_TypeDef* map_gpio_port(uint8_t port)
{
    GPIO_TypeDef* gpioInst;
    
    switch (port) 
    {
        case PORTA:
            gpioInst = GPIOA;
            break;
        case PORTB:
            gpioInst = GPIOB;
            break;
        case PORTC:
            gpioInst = GPIOC;
            break;
#ifdef STM32F429xx
        case PORTD:
            gpioInst = GPIOD;
            break;
        case PORTD:
            gpioInst = GPIOD;
            break;
        case PORTE:
            gpioInst = GPIOE;
            break;
        case PORTF:
            gpioInst = GPIOF;
            break;
        case PORTG:
            gpioInst = GPIOG;
            break;
        case PORTH:
            gpioInst = GPIOH;
            break;
#endif
        default:
            gpioInst = NULL;
            break;
    }
    
    return gpioInst;
}
