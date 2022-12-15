/********************************************************************************
* @file     driver_gpio.c                                                       *
* @brief    File includes implementations of GPIO driver functions.             *
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

#include "/driver/gpio/driver_gpio.h"

common_rc_t driver_gpio_clock_control (GPIO_TypeDef* pGpioInst, bool bEnable)
{
    /* Return code is OK by default */
    common_rc_t rc = RC_OK;
    
    if (bEnable) {
        /* Enable the peripheral clock for the respective GPIO instance */
        if (pGpioInst == GPIOA) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        }
        else if (pGpioInst == GPIOB) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
        } 
        else if (pGpioInst == GPIOC) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
        }
        else if (pGpioInst == GPIOD) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
        }
        else if (pGpioInst == GPIOE) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
        }
#ifdef STM32F429xx
        else if (pGpioInst == GPIOF) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
        }
        else if (pGpioInst == GPIOG) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
        }
#endif        
        else if (pGpioInst == GPIOH) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
        }
        else {
            /* If the GPIO instance not part of the MCU, return error param */
            rc = RC_ERR_PARAM;
        }
    }
    else {
        /* Disable the peripheral clock for the respective GPIO instance */
        if (pGpioInst == GPIOA) {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
        }
        else if (pGpioInst == GPIOB) {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
        } 
        else if (pGpioInst == GPIOC) {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
        }
        else if (pGpioInst == GPIOD) {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
        }
        else if (pGpioInst == GPIOE) {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN;
        }
#ifdef STM32F429xx
        else if (pGpioInst == GPIOF) {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOFEN;
        }
        else if (pGpioInst == GPIOG) {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOGEN;
        }
#endif        
        else if (pGpioInst == GPIOH) {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN;
        }
        else {
            /* If the GPIO instance not part of the MCU, return error param */
            rc = RC_ERR_PARAM;
        }
    }
    
    return rc;
}

common_rc_t driver_gpio_init (driver_gpio_pinConfig_t* pGpioPin)
{
    /* Return code is OK by default */
    common_rc_t rc = RC_OK;
    
    /* Enable the peripheral clock */
    rc = driver_gpio_clock_control(pGpioPin->pInst, ENABLE);
    
    if (rc == RC_OK) {
        /* Configure the pin mode */
        if (pGpioPin->param.pinMode <= ANALOG) {
            /* Clear the MODER bits for that GPIO pin number */
            pGpioPin->pInst->MODER &= ~(uint32_t)(GPIO_MODER_Clear_Msk << GPIO_MODER_Pos(pGpioPin->param.pinNumber));
            /* Set the MODER bits as required mode for that GPIO pin number */
            pGpioPin->pInst->MODER |= (uint32_t)(pGpioPin->param.pinMode << GPIO_MODER_Pos(pGpioPin->param.pinNumber));
        }
        else {
            rc = RC_ERR_PARAM;
        }
        if (rc == RC_OK) {
            /* Configure the pin speed */
            if (pGpioPin->param.pinSpeed <= VERY_HIGH) {
                /* Clear the OSPEEDR bits for that GPIO pin number */
                pGpioPin->pInst->OSPEEDR &= ~(uint32_t)(GPIO_OSPEEDR_Clear_Msk << GPIO_OSPEEDR_Pos(pGpioPin->param.pinNumber)); 
                /* Set the OSPEEDR bits as required speed for that GPIO pin number */
                pGpioPin->pInst->OSPEEDR |= (uint32_t)(pGpioPin->param.pinSpeed << GPIO_OSPEEDR_Pos(pGpioPin->param.pinNumber));
            }
            else {
                rc = RC_ERR_PARAM;
            }
        }
        if (rc == RC_OK) {
            /* Confgure pull-up or pull-down */
            if (pGpioPin->param.pinPuPdControl <= PULL_DOWN) {
                /* Clear the PUPDR bits for that GPIO pin number */
                pGpioPin->pInst->PUPDR &= ~(uint32_t)(GPIO_PUPDR_Clear_Msk << GPIO_PUPDR_Pos(pGpioPin->param.pinNumber)); 
                /* Set the PUPDR bits as required speed for that GPIO pin number */
                pGpioPin->pInst->PUPDR |= (uint32_t)(pGpioPin->param.pinPuPdControl << GPIO_PUPDR_Pos(pGpioPin->param.pinNumber));
            }
            else {
                rc = RC_ERR_PARAM;
            }
        }
        if (rc == RC_OK) {
            /* Configure the output type */
            if (pGpioPin->param.pinOpType <= OPEN_DRAIN) {
                /* Clear the OTYPER bits for that GPIO pin number */
                pGpioPin->pInst->OTYPER &= ~(uint32_t)(GPIO_OTYPER_Clear_Msk << pGpioPin->param.pinNumber); 
                /* Set the PUPDR bits as required speed for that GPIO pin number */
                pGpioPin->pInst->OTYPER |= (uint32_t)(pGpioPin->param.pinOpType << pGpioPin->param.pinNumber);
            }
            else {
                rc = RC_ERR_PARAM;
            }
        }
        if (rc == RC_OK) {
            /* Configure the alternate function register */
            if (pGpioPin->param.pinMode == ALTFUN) {
                
                if (pGpioPin->param.pinAltFunMode <= AF15) {
                    /* Clear the AFR bits for that GPIO pin number */
                    pGpioPin->pInst->AFR[GPIO_AFR_Index(pGpioPin->param.pinNumber)] 
                            &= ~(uint32_t)(GPIO_AFR_Clear_Msk << GPIO_AFR_Pos(pGpioPin->param.pinNumber));
                    
                    /* Set the AFR bits as required alternate function for that GPIO pin number */
                    pGpioPin->pInst->AFR[GPIO_AFR_Index(pGpioPin->param.pinNumber)] 
                            |= (uint32_t)(pGpioPin->param.pinAltFunMode << GPIO_AFR_Pos(pGpioPin->param.pinNumber));
                }
                else {
                    rc = RC_ERR_PARAM;
                }
            }
        }
    }
    
    return rc;
}
