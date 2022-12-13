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






