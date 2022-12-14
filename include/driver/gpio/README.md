# GPIO Driver Specification and API Documentation

This driver is used for two target platforms : STM32F429ZITx and STM32F401CCUx Microcontrollers
Given below are the structures, list of APIs and their functionality which is used by the application.

### Structures

```
typedef struct {
    uint8_t gpio_pinNumber;         /* The pin number of the GPIO peripheral - 1, 2, 3 , etc. */
    uint8_t gpio_pinMode;           /* Pin modes of the GPIO pin - I/O, Analog or AltFun      */
    uint8_t gpio_pinSpeed;          /* Speed of the GPIO pin - high, medium or low            */
    uint8_t gpio_pinPuPdControl;    /* Pull up or pull down control of the GPIO pin           */
    uint8_t gpio_pinOpType;         /* Output type of the GPIO pin - push-pull or open drain  */
    uint8_t gpio_pinAltFunMode;     /* Alternate function mode of the GPIO pin - refer manual */
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

### 2. API to configure a GPIO Pin
```

```