/********************************************************************************
* @file     driver_rcc.h                                                        *
* @brief    Clock config Header File                                            *
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

#ifndef _DRIVER_RCC_H_
#define _DRIVER_RCC_H_

#include "stm32f4xx.h"
#include "common/common_def.h"
#include <stdbool.h>

/* Structure provided by RCC driver to application */

/** @brief RCC config structure used by 
    the application to configure the system clock */
typedef struct {
    uint8_t clockOption;        /*< possible values from @rcc_clockOptions_t >*/
    uint8_t clockSource;        /*< possible values from @rcc_clockSources_t >*/
} driver_rcc_clock_t;

/** @brief RCC config structure used by 
    the application to configure RCC */
typedef struct {
	driver_rcc_clock_t param;	/*< Holds RCC clock configuration parameters >*/
} driver_gpio_clockConfig_t;

/* Enums for the configurable RCC parameters */

/** @brief Available clock sources for the MCU */
typedef enum {
    LOW_POWER,          /*< Lower clock config  >*/
    HIGH_PERFORMANCE,   /*< High performance clock config  >*/
} rcc_clockOptions_t;

typedef enum {
    INTERNAL,       /* High Speed Internal (RC Osc) clock config  */
    EXTERNAL,       /* High Speed External (Crystal) clock config */
} rcc_clockSources_t;

/**
 * @brief Configure clock for the MCU
 *
 * @param pClockConfig - Pointer
 *        Pointer to the clock configurations
 *
 * @returns RC - Return Code
 */


#endif  /* _DRIVER_GPIO_H_ */
