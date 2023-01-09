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
#include "/system/system_config.h"

static GPIO_TypeDef* map_gpio_port(uint8_t port);

common_rc_t hal_gpio_config_port (hal_gpio_t* gpio, bool bEnable, bool bReset)
{
    common_rc_t rc;
    driver_gpio_pinConfig_t gpioPort = 
    { 
        .pInst = map_gpio_port(gpio->port)
    };
    
    if (bReset)
    {
        rc = driver_gpio_reset(gpioPort.pInst);
    }
    else
    {
        if (bEnable)
        {
            rc = driver_gpio_peripheral_config(&gpioPort, ENABLE);
        }
        else
        {
            rc = driver_gpio_peripheral_config(&gpioPort, DISABLE);
        }
    }
    
    return rc;
}

common_rc_t hal_gpio_config_pin (hal_gpio_t* gpio)
{
    common_rc_t rc = RC_OK;
    driver_gpio_pinConfig_t gpioPin;
    
    gpioPin.pInst = map_gpio_port(gpio->port);
    gpioPin.param.pinNumber = gpio->pin;
    gpioPin.param.pinOpType = PUSH_PULL;
    
    switch (gpio->func)
    {
        case LED:
        {
            gpioPin.param.pinMode = OUTPUT;
            gpioPin.param.pinSpeed = LOW;
            gpioPin.param.pinPuPdControl = NO_PUPD;
            break;
        }
        case ONBOARD_BUTTON:
        case EXT_BUTTON_PU:
        {
            gpioPin.param.pinMode = INPUT;
            gpioPin.param.pinSpeed = HIGH;
            gpioPin.param.pinPuPdControl = PULL_UP;
            break;
        }
        case EXT_BUTTON_PD:
        {
            gpioPin.param.pinMode = INPUT;
            gpioPin.param.pinSpeed = HIGH;
            gpioPin.param.pinPuPdControl = PULL_DOWN;
            break;
        }
        case SWITCH:
        {
            gpioPin.param.pinMode = INPUT;
            gpioPin.param.pinSpeed = HIGH;
            gpioPin.param.pinPuPdControl = NO_PUPD;
            break;
        }
        case CLOCK_OUT:
        {
            gpioPin.param.pinMode = ALTFUN;
            gpioPin.param.pinSpeed = VERY_HIGH;
            gpioPin.param.pinPuPdControl = NO_PUPD;
            gpioPin.param.pinAltFunMode = AF0;
            
            if ((gpioPin.param.pinNumber == GPIO_PIN_8) && (gpioPin.pInst == GPIOA))
            {
                system_config_mco(MCO1);
            }
            else if ((gpioPin.param.pinNumber == GPIO_PIN_9) && (gpioPin.pInst == GPIOC))
            {
                system_config_mco(MCO2);
            }
            else
            {
                rc = RC_ERR_PARAM;
            }
            break;
        }
        default:
        {
            rc = RC_ERR_PARAM;
            break;
        }
    }
    
    if (rc == RC_OK)
    {
        driver_gpio_config_pin(&gpioPin);
    }
    
    return rc;
}

uint16_t hal_gpio_read_port (hal_gpio_t* gpio, uint16_t mask)
{
    return driver_gpio_read_port (map_gpio_port (gpio->port), mask);
}

void hal_gpio_write_port (hal_gpio_t* gpio, uint16_t data, uint16_t mask)
{
    driver_gpio_write_port (map_gpio_port (gpio->port), data, mask);
}    

bool hal_gpio_read_pin (hal_gpio_t* gpio)
{
    return driver_gpio_read_pin (map_gpio_port (gpio->port), gpio->pin);
}

void hal_gpio_write_pin (hal_gpio_t* gpio, bool bSet)
{
    driver_gpio_write_pin (map_gpio_port (gpio->port), bSet, gpio->pin);
}

void hal_gpio_toggle_pin (hal_gpio_t* gpio)
{
    driver_gpio_toggle_pin (map_gpio_port (gpio->port), gpio->pin);
}

static GPIO_TypeDef* map_gpio_port (uint8_t port)
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
