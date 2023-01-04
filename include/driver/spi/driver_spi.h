/********************************************************************************
* @file     driver_spi.h                                                        *
* @brief    SPI Driver Header File                                              *
* @author   Yeshvanth M  <yeshvanthmuniraj@gmail.com>                           *
* @date     31-Dec-2022                                                         *
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

#ifndef _DRIVER_SPI_H_
#define _DRIVER_SPI_H_

#include "stm32f4xx.h"
#include "common/common_def.h"
#include <stdbool.h>

/* Structure provided by SPI driver to HAL */

/** @brief SPI config structure used to configure a SPI peripheral */

typedef struct {
    uint8_t spiConfig;     /*< possible values from @spi_config_t   >*/
    uint8_t spiMode;       /*< possible values from @spi_mode_t     >*/
    uint8_t	spiCpol;       /*< possible values from @spi_clkpol_t   >*/
    uint8_t spiCpha;       /*< possible values from @spi_clkpha_t   >*/
    uint8_t spiDff;        /*< possible values from @spi_dff_t      >*/
    uint8_t spiSsm;        /*< possible values from @spi_ssm_t      >*/
    uint8_t spiCrcEn;      /*< possible values from @spi_crc_t      >*/
    uint8_t spiSpeed;      /*< possible values from @spi_baudrate_t >*/
} driver_spi_t;


typedef enum {
    SLAVE,
    MASTER
} spi_config_t;

typedef enum {
    SIMPLEX_TX,
    SIMPLEX_RX,
    HALF_DUPLEX,
    FULL_DUPLEX,
} spi_mode_t;

typedef enum {
    CPOL_LOW,
    CPOL_HIGH
} spi_clkpol_t;

typedef enum {
    CPHA_LOW,
    CPHA_HIGH
} spi_clkpha_t;

typedef enum {
    DFF_8_BIT,
    DFF_16_BIT
} spi_dff_t;

typedef enum {
    SSM_DISABLE,
    SSM_ENABLE
} spi_ssm_t;

typedef enum {
    CRC_DISABLE,
    CRC_ENABLE
} spi_crc_t;

typedef enum {
    PCLK_DIV_2,
    PCLK_DIV_4,
    PCLK_DIV_8,
    PCLK_DIV_16,
    PCLK_DIV_32,
    PCLK_DIV_64,
    PCLK_DIV_128,
    PCLK_DIV_256,
} spi_speed_t;

common_rc_t driver_spi_init (driver_spi_t* spiConfig);

#endif
