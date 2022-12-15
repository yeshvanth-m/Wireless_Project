/********************************************************************************
* @file     driver_gpio_test                                                    *
* @brief    File contains driver level unit tests for GPIO                      *
* @author   Yeshvanth M  <yeshvanthmuniraj@gmail.com>                           *
* @date     14-Dec-2022                                                         *
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

#include "unity.h"
#include <stdio.h>
#include "driver/gpio/driver_gpio.h"

void setUp(void) {
	/* Set up the test environment */
}

void tearDown(void) {
	/* Clean up the test environment */
}

#ifdef STM32F429xx
GPIO_TypeDef* GPIOs[8] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, NULL};
#else
GPIO_TypeDef* GPIOs[8] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH, NULL};
#endif

static void test_driver_gpio_init(void)
{
    driver_gpio_pinConfig_t testPin;
    testPin.param.pinNumber = GPIO_PIN_0;
    testPin.param.pinMode = INPUT;
    testPin.param.pinSpeed = LOW;
    testPin.param.pinPuPdControl = NO_PUPD;
    testPin.param.pinOpType = PUSH_PULL;
    
    /* Test Peripheral clock enabled in AHB1ENR */
    /* Enable the clock, check respective bit and then disable the clock for that peripheral */
    testPin.pInst = GPIOA;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000001, "GPIOA Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOA, DISABLE);
    
    testPin.pInst = GPIOB;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000002, "GPIOB Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOB, DISABLE);
    
    testPin.pInst = GPIOC;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000004, "GPIOC Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOC, DISABLE);
    
    testPin.pInst = GPIOD;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000008, "GPIOD Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOD, DISABLE);
    
    testPin.pInst = GPIOE;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000010, "GPIOE Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOE, DISABLE);

#ifdef STM32F429xx
    testPin.pInst = GPIOF;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000020, "GPIOF Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOF, DISABLE);
    
    testPin.pInst = GPIOG;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000040, "GPIOG Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOG, DISABLE);
#endif

    testPin.pInst = GPIOH;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000080, "GPIOH clock not enabled in AHB1ENR")
    
    /* Traverse through all GPIOs available in MCU */
    for (uint8_t i = 0u; GPIOs[i] != NULL; i++) {
        /* Test GPIO pin mode in MODER register */
        testPin.pInst = GPIOs[i];
        uint32_t moder = 0u, otyper = 0u, ospeedr = 0u, pupdr = 0u, afr[2] = {0u, 0u};
        
/* Presets in hardware registers
        if (GPIOs[i] == GPIOA) {
            moder = 0x0C000000;
            ospeedr = 0x0C000000;
            pupdr = 0x64000000;
        }
        else if (GPIOs[i] == GPIOB) {
            moder = 0x00000280;
            ospeedr = 0x000000C0;
            pupdr = 0x00000100;
        }
*/
        
        for (uint8_t pin = 0u; pin < 16u; pin++) {
            testPin.param.pinNumber = pin;
            
            for (gpio_pinModes_t mode = INPUT; mode <= ANALOG; mode++) {
                moder &= ~(GPIO_MODER_Clear_Msk << GPIO_MODER_Pos(pin));
                moder |= (mode << GPIO_MODER_Pos(pin));
                testPin.param.pinMode = mode;
                driver_gpio_init(&testPin);
                TEST_ASSERT_EQUAL_UINT32_MESSAGE(moder, GPIOs[i]->MODER, "GPIO mode not set in MODER register");
            }
            
            for (gpio_pinOpTypes_t opType = PUSH_PULL; opType <= OPEN_DRAIN; opType++) {
                otyper &= ~(GPIO_OTYPER_Clear_Msk << pin);
                otyper |= (opType << pin);
                testPin.param.pinOpType = opType;
                driver_gpio_init(&testPin);
                TEST_ASSERT_EQUAL_UINT32_MESSAGE(otyper, GPIOs[i]->OTYPER, "GPIO output type not set in OTYPER register");
            }
            
            for (gpio_pinSpeeds_t speed = LOW; speed <= VERY_HIGH; speed++) {
                ospeedr &= ~(GPIO_OSPEEDR_Clear_Msk << GPIO_OSPEEDR_Pos(pin));
                ospeedr |= (speed << GPIO_OSPEEDR_Pos(pin));
                testPin.param.pinSpeed = speed;
                driver_gpio_init(&testPin);
                TEST_ASSERT_EQUAL_UINT32_MESSAGE(ospeedr, GPIOs[i]->OSPEEDR, "GPIO output speed not set in OSPEEDR register");
            }
            
            for (gpio_pinPuPdControl_t pupd = NO_PUPD; pupd <= PULL_DOWN; pupd++) {
                pupdr &= ~(GPIO_PUPDR_Clear_Msk << GPIO_PUPDR_Pos(pin));
                pupdr |= (pupd << GPIO_PUPDR_Pos(pin));
                testPin.param.pinPuPdControl = pupd;
                driver_gpio_init(&testPin);
                TEST_ASSERT_EQUAL_UINT32_MESSAGE(pupdr, GPIOs[i]->PUPDR, "GPIO pull-up/down not set in PUPDR register");
            }
            
            testPin.param.pinMode = ALTFUN;
            for (gpio_pinAltFunMode_t af = AF0; af <= AF15; af++) {
                afr[GPIO_AFR_Index(pin)] &= ~(GPIO_AFR_Clear_Msk << GPIO_AFR_Pos(pin));
                afr[GPIO_AFR_Index(pin)] |= (af << GPIO_AFR_Pos(pin));
                testPin.param.pinAltFunMode = af;
                driver_gpio_init(&testPin);
                TEST_ASSERT_EQUAL_UINT32_MESSAGE(afr[GPIO_AFR_Index(pin)], GPIOs[i]->AFR[GPIO_AFR_Index(pin)], "GPIO alt fun not set in AFR register");
            }
            
            testPin.param.pinMode = ANALOG;
            driver_gpio_init(&testPin);
            
        }
    }
}

int main(void)
{
    UNITY_BEGIN("GPIO Driver Test Started", __DATE__, __TIME__);
    RUN_TEST(test_driver_gpio_init);
    UNITY_END();
}
