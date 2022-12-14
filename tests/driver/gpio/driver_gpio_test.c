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

static void test_driver_gpio_init(void)
{
    driver_gpio_pinConfig_t testPin;
    testPin.param.pinNumber = GPIO_PIN_0;
    testPin.param.pinMode = INPUT;
    testPin.param.pinSpeed = LOW;
    testPin.param.pinPuPdControl = NO_PUPD;
    testPin.param.pinOpType = PUSH_PULL;
    
    /* Test Peripheral clock enabled in AHB1ENR */
    testPin.pInst = GPIOA;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000001 , "GPIOA Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOA, DISABLE);
    
    testPin.pInst = GPIOB;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000002 , "GPIOB Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOB, DISABLE);
    
    testPin.pInst = GPIOC;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000004 , "GPIOC Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOC, DISABLE);
    
    testPin.pInst = GPIOD;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000008 , "GPIOD Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOD, DISABLE);
    
    testPin.pInst = GPIOE;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000010 , "GPIOD Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOE, DISABLE);

#ifdef STM32F429xx
    testPin.pInst = GPIOF;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000020 , "GPIOF Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOF, DISABLE);
    
    testPin.pInst = GPIOG;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000040 , "GPIOG Clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOG, DISABLE);
#endif

    testPin.pInst = GPIOH;
    driver_gpio_init(&testPin);
    TEST_ASSERT_MESSAGE(RCC->AHB1ENR == 0x00000080 , "GPIOH clock not enabled in AHB1ENR")
    driver_gpio_clock_control(GPIOH, DISABLE);
    
}

int main(void)
{
    UNITY_BEGIN("GPIO Driver Test Started", __DATE__, __TIME__);
    RUN_TEST(test_driver_gpio_init);
    UNITY_END();
}
