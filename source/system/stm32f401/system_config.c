/********************************************************************************
* @file     system_config.c                                                     *
* @brief    System Config Implementations File                                  *
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

#include "system/system_config.h"

/***************************************************************************************
* Configure the system configuration:
* 1. If external clock source is selected then enable it and wait till it becomes ready
* 2. If internal clock source is selected then see how we can enable it - ???
*
*
*
*
*
*
*
****************************************************************************************/

void system_config_init(system_config_t cfg, system_clock_source_t clk)
{
    
}
