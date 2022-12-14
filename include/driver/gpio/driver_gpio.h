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

#ifndef _DRIVER_GPIO_H_
#define _DRIVER_GPIO_H_

#include "stm32f4xx.h"
#include "common/common_def.h"
#include <stdbool.h>

/* Structure provided by GPIO driver to application */

/** @brief GPIO config structure used by 
    the application to configure a GPIO Pin */
typedef struct {
    uint8_t pinNumber;         /*< possible values from @gpio_pinNumbers_t >*/
    uint8_t	pinMode;           /*< possible values from @gpio_pinModes_t   >*/
    uint8_t pinSpeed;          /*< possible values from @gpio_pinSpeeds_t  >*/
    uint8_t pinPuPdControl;    /*< possible values from @gpio_pinPuPd_t    >*/
    uint8_t pinOpType;         /*< possible values from @gpio_pinOpTypes_t >*/
    uint8_t pinAltFunMode;     /*< possible values from @gpio_pinAltFun_t  >*/
} driver_gpio_pin_t;

/** @brief GPIO config structure used by 
    the application to configure a GPIO Pin */
typedef struct {
	GPIO_TypeDef *pInst;	    /* GPIO instance */
	driver_gpio_pin_t param;	/* Holds GPIO pin configuration parameters */
} driver_gpio_pinConfig_t;

/* Enums for the configurable GPIO parameters */

/** @brief Available pin numbers of a GPIO peripheral */
typedef enum {
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
} gpio_pinNumbers_t;

/** @brief Available pin modes in the GPIO peripheral */
typedef enum {
    INPUT,    /*< Input Mode of GPIO    >*/
    OUTPUT,   /*< output Mode of GPIO   >*/
    ALTFUN,   /*< Alternate Fun of GPIO >*/
    ANALOG,   /*< Analog Mode of GPIO   >*/
} gpio_pinModes_t;

#define GPIO_OSPEEDR_Clear_Msk        0x3UL
#define GPIO_OSPEEDR_Pos(number) (2u * number)

/** @brief Available pin speeds in the GPIO peripheral */
typedef enum {
    LOW,        /*<  Low Speed       >*/
    MEDIUM,     /*<  Medium Speed    >*/
    HIGH,       /*<  High Speed      >*/
    VERY_HIGH,  /*<  Very high speed >*/
} gpio_pinSpeeds_t;

#define GPIO_MODER_Clear_Msk        0x3UL
#define GPIO_MODER_Pos(number) (2u * number)

/** @brief Available input control in the GPIO peripheral */
typedef enum {
    NO_PUPD,    /*< No pull-up or pull-down >*/
    PULL_UP,    /*< Pull-up                 >*/
    PULL_DOWN,  /*< Pull-down               >*/
} gpio_pinPuPdControl_t;

#define GPIO_PUPDR_Clear_Msk        0x3UL
#define GPIO_PUPDR_Pos(number) (2u * number)

/** @brief Available output types in the GPIO peripheral */
typedef enum {
    PUSH_PULL,
    OPEN_DRAIN
} gpio_pinOpTypes_t;    

#define GPIO_OTYPER_Clear_Msk        0x1UL

/** @brief Available alternate functions in the GPIO peripheral */
typedef enum {
    AF0,    /*< Alternate function 0  >*/
    AF1,    /*< Alternate function 1  >*/
    AF2,    /*< Alternate function 2  >*/
    AF3,    /*< Alternate function 3  >*/
    AF4,    /*< Alternate function 4  >*/
    AF5,    /*< Alternate function 5  >*/
    AF6,    /*< Alternate function 6  >*/
    AF7,    /*< Alternate function 7  >*/
    AF8,    /*< Alternate function 8  >*/
    AF9,    /*< Alternate function 9  >*/
    AF10,   /*< Alternate function 10 >*/
    AF11,   /*< Alternate function 11 >*/
    AF12,   /*< Alternate function 12 >*/
    AF13,   /*< Alternate function 13 >*/
    AF14,   /*< Alternate function 14 >*/
    AF15,   /*< Alternate function 15 >*/
} gpio_pinAltFunMode_t;

#define GPIO_AFR_Clear_Msk     0xFUL
#define GPIO_AFR_Pos(number)   ((number % 8u) * 4u)
#define GPIO_AFR_Index(number) (number / 8u)

/**
 * @brief Clock control for the GPIO peripheral
 *
 * @param pGpioInst - Pointer
 *        Pointer to the GPIO instance
 *
 * @param bEnable - Boolean
 *        True: enable peripheral clock
 *        False: disable peripheral clock
 *
 * @returns None
 */
common_rc_t driver_gpio_clock_control (GPIO_TypeDef* pGpioInst, bool bEnable);

/**
 * @brief Configure a GPIO pin
 *
 * @param pGpio - Pointer
 *        Pointer to the GPIO pin configurations
 *
 * @returns None
 */
common_rc_t driver_gpio_init (driver_gpio_pinConfig_t* pGpioPin);

#endif  /* _DRIVER_GPIO_H_ */
