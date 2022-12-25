# GPIO Driver Specification and API Documentation

This driver is used for two target platforms : STM32F429ZITx and STM32F401CCUx Microcontrollers
Given below are the structures, list of APIs and their functionality which is used by the application.

### Structures

```
typedef struct {
    uint8_t pinNumber;         /* The pin number of the GPIO peripheral - 1, 2, 3 , etc. */
    uint8_t pinMode;           /* Pin modes of the GPIO pin - I/O, Analog or AltFun      */
    uint8_t pinSpeed;          /* Speed of the GPIO pin - high, medium or low            */
    uint8_t pinPuPdControl;    /* Pull up or pull down control of the GPIO pin           */
    uint8_t pinOpType;         /* Output type of the GPIO pin - push-pull or open drain  */
    uint8_t pinAltFunMode;     /* Alternate function mode of the GPIO pin - refer manual */
} driver_gpio_config_t;
```

### 1. API to configure the clock for a GPIO instance
```
driver_gpio_clock_control ()
```
Brief: Enable or disable the clock for a particular GPIO instance
- Enables / disables the GPIO peripheral clock by setting / clearing the corresponding bit in AHB1ENR
- All GPIO peripherals are directly connected to the AHB1 - refer memory map
- AHB & APB clock control registers are part of RCC group

### 2. API to initialize a GPIO Pin
```
driver_gpio_init ()
```
Brief: Configure a GPIO Pin of a particular GPIO instance
- Call driver_gpio_clock_control () amd enables the peripheral clock
- Configure the following:
    1. Pin mode in the MODER register - Input / Output / Alternate function / Analog
    2. Speed in the SPEEDR register - Low / Medium / High / Very High
    3. Pull-up / pull-down config in PUPDR register - Pull Up / Pull Down 
    4. Output type in OTYPER register - Push-pull / Open Drain
    5. Alternate function mode in AFR register - AF0 - .... AF15
- Return the error code

### 3. API to de-initialize a GPIO Pin
```
driver_gpio_deInit ()
```
Brief: Disable a particular GPIO instance by disabling the peripheral clock