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
* Configure the system with the following parameters for STM32F401:
*
  * @brief  System Clock Configuration for Low Power
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK			              = 64 MHz
  *            HCLK			                  = 8 MHz
  *            AHB Prescaler                  = 8
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSE Frequency		          = 25 MHz
  *            PLL_M                          = 25
  *            PLL_N                          = 128
  *            PLL_P                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  */

/* PLL config for Low Power */
#define PLL_M_LP                   25u
#define PLL_N_LP                   128u
#define PLL_P_LP                   2u

/* Prescalars for low power */
#define AHB_PRESCLR_LP             RCC_CFGR_HPRE_DIV8
#define APB1_PRESCLR_LP            RCC_CFGR_PPRE1_DIV1
#define APB2_PRESCLR_LP            RCC_CFGR_PPRE2_DIV1


/*
  * @brief  System Clock Configuration for High Performance
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK			              = 84 MHz
  *            HCLK			                  = 84 MHz
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency		          = 25 MHz
  *            PLL_M                          = 25
  *            PLL_N                          = 168
  *            PLL_P                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  */

/* PLL config for High Performance */
#define PLL_M_HP                   25u
#define PLL_N_HP                   168u
#define PLL_P_HP                   2u

/* Prescalars for high performance */
#define AHB_PRESCLR_HP             RCC_CFGR_HPRE_DIV1
#define APB1_PRESCLR_HP            RCC_CFGR_PPRE1_DIV2
#define APB2_PRESCLR_HP            RCC_CFGR_PPRE2_DIV1

/***************************************************************************************/

void system_config_init(system_config_t cfg)
{
	/********************************************************
    1. ENABLE HSE and wait for the HSE to become Ready
	2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	5. Configure the MAIN PLL
	6. Enable the PLL and wait for it to become ready
	7. Select the Clock Source and wait for it to be set
	********************************************************/

	/* Enable HSE and wait for the HSE to become ready */
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));
	
	/* Set the power enable clock and voltage regulator */
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS;
	
	
	/* Configure the flash prefetch and the latency Related Settings */
	FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
    
    /* Configure PLL and prescsalars based on low power or high performance config */
    if (cfg == LOW_POWER)
    {
        /* Configure the prescalars for HCLK, PCLK1, PCLK2 */
        RCC->CFGR |= (AHB_PRESCLR_LP | APB1_PRESCLR_LP | APB2_PRESCLR_LP);

        /*  Configure the Main PLL with divisors and clock source */
        RCC->PLLCFGR = (PLL_M_LP << RCC_PLLCFGR_PLLM_Pos) 
                        | (PLL_N_LP << RCC_PLLCFGR_PLLN_Pos) 
                          | (PLL_P_LP << RCC_PLLCFGR_PLLP_Pos) 
                            | (RCC_PLLCFGR_PLLSRC_HSE);
    }
    else
    {
        /* Configure the prescalars for HCLK, PCLK1, PCLK2 */
        RCC->CFGR |= (AHB_PRESCLR_HP | APB1_PRESCLR_HP | APB2_PRESCLR_HP);

        /*  Configure the Main PLL with divisors and clock source */
        RCC->PLLCFGR = (PLL_M_HP << RCC_PLLCFGR_PLLM_Pos) 
                        | (PLL_N_HP << RCC_PLLCFGR_PLLN_Pos) 
                          | (PLL_P_HP << RCC_PLLCFGR_PLLP_Pos) 
                            | (RCC_PLLCFGR_PLLSRC_HSE);
    }

	/* Enable the PLL and wait for it to become ready */
	RCC->CR |= RCC_CR_PLLON;  
	while (!(RCC->CR & RCC_CR_PLLRDY));  
	
	/* Select the Clock Source as PLL and wait for it to be set */
	RCC->CFGR |= RCC_CFGR_SW_PLL; 
	while (((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL));
    
    /* Call the system core clock update to update the global clock variable (CMSIS) */
    SystemCoreClockUpdate();
}
