/********************************************************************************
* @file     hal_gpio.h                                                          *
* @brief    GPIO HAL Header File                                                *
* @author   Yeshvanth M  <yeshvanthmuniraj@gmail.com>                           *
* @date     13-Dec-2022                                                         *
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

#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

#include "driver/gpio/driver_gpio.h"
#include "common/common_def.h"
#include "stdlib.h"
#include <stdbool.h>

/* Structure provided by GPIO driver to application */

/** @brief GPIO config structure used by 
    the application to configure a Pin */
typedef struct {
    uint8_t port;
    uint8_t pin;
    uint8_t func;
} hal_gpio_t;


/* Enums for the configurable GPIO parameters */

/** @brief Available pin numbers of a GPIO peripheral */
typedef enum {
    PIN_0,     /*< Pin number 0  >*/
    PIN_1,     /*< Pin number 1  >*/
    PIN_2,     /*< Pin number 2  >*/
    PIN_3,     /*< Pin number 3  >*/
    PIN_4,     /*< Pin number 4  >*/
    PIN_5,     /*< Pin number 5  >*/
    PIN_6,     /*< Pin number 6  >*/
    PIN_7,     /*< Pin number 7  >*/
    PIN_8,     /*< Pin number 8  >*/
    PIN_9,     /*< Pin number 9  >*/
    PIN_10,    /*< Pin number 10 >*/    
    PIN_11,    /*< Pin number 11 >*/    
    PIN_12,    /*< Pin number 12 >*/    
    PIN_13,    /*< Pin number 13 >*/
    PIN_14,    /*< Pin number 14 >*/
    PIN_15,    /*< Pin number 15 >*/
} hal_gpioPinNumbers_t;

typedef enum {
    PORTA,
    PORTB,
    PORTC,
#ifdef STM32F429xx
    PORTD,
    PORTE,
    PORTF,
    PORTG,
    PORTH,
#endif
} hal_gpioPorts_t;

typedef enum {
    LED,
    ONBOARD_BUTTON,
    EXT_BUTTON_PU,
    EXT_BUTTON_PD,
    SWITCH,
    CLOCK_OUT,
} hal_gpioFunc_t;

common_rc_t hal_gpio_config_port(hal_gpio_t* port, bool bEnable, bool bReset);

common_rc_t hal_gpio_config_pin(hal_gpio_t* pin);

uint16_t hal_gpio_read_port (hal_gpio_t* gpio, uint16_t mask);

void hal_gpio_write_port (hal_gpio_t* gpio, uint16_t data, uint16_t mask);    

bool hal_gpio_read_pin (hal_gpio_t* gpio);

void hal_gpio_write_pin (hal_gpio_t* gpio, bool bSet);

void hal_gpio_toggle_pin (hal_gpio_t* gpio);

#endif  /* _HAL_GPIO_H_ */
