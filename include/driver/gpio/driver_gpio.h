/********************************************************************************
* @file     driver_gpio.h                                                       *
* @brief    GPIO Driver Header File                                             *
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

#include "stm32f4xx.h"

/* GPIO config structure used by the application to configure a GPIO Pin */
typedef struct {
    uint8_t gpio_pinNumber;         /*< possible values from @gpio_pinNumbers >*/
    uint8_t	gpio_pinMode;           /*< possible values from @gpio_pinModes   >*/
    uint8_t gpio_pinSpeed;          /*< possible values from @gpio_pinSpeeds  >*/
    uint8_t gpio_pinPuPdControl;    /*< possible values from @gpio_pinPuPd    >*/
    uint8_t gpio_pinOpType;         /*< possible values from @gpio_pinOpTypes >*/
    uint8_t gpio_pinAltFunMode;     /*< possible values from @gpio_pinAltFun  >*/
} driver_gpio_config_t;

enum gpio_pinNumbers {
    GPIO_PIN_0,     /*< GPIO Pin number 0  >*/
    GPIO_PIN_1,     /*< GPIO Pin number 1  >*/
    GPIO_PIN_2,     /*< GPIO Pin number 2  >*/
    GPIO_PIN_3,     /*< GPIO Pin number 3  >*/
    GPIO_PIN_4,     /*< GPIO Pin number 4  >*/
    GPIO_PIN_5,     /*< GPIO Pin number 5  >*/
    GPIO_PIN_6,     /*< GPIO Pin number 6  >*/
    GPIO_PIN_7,     /*< GPIO Pin number 7  >*/
    GPIO_PIN_8,     /*< GPIO Pin number 8  >*/
    GPIO_PIN_9,     /*< GPIO Pin number 9  >*/
    GPIO_PIN_10,    /*< GPIO Pin number 10 >*/    
    GPIO_PIN_11,    /*< GPIO Pin number 11 >*/    
    GPIO_PIN_12,    /*< GPIO Pin number 12 >*/    
    GPIO_PIN_13,    /*< GPIO Pin number 13 >*/
    GPIO_PIN_14,    /*< GPIO Pin number 14 >*/
    GPIO_PIN_15,    /*< GPIO Pin number 15 >*/
};

enum gpio_pinModes {
    INPUT,
    OUTPUT,
    ALTFUN,
    ANALOG,
};

enum gpio_pinSpeeds {
    LOW,
    MEDIUM,
    HIGH,
    VERY_HIGH,
};

enum gpio_pinPuPdControl {
    NO_PUPD,
    PULL_UP,
    PULL_DOWN,
};

enum gpio_pinAltFunMode {
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15,
};
