# baremetal-blink

Blinks the user LED on a Nucleo-F446RE by writing directly to the STM32F446RE registers. No HAL, no CMSIS headers, just addresses from the reference manual.

## Hardware

- Nucleo-F446RE (STM32F446RE, Cortex-M4)
- User LED LD2 on PA5

## How it works

`src/main.c` uses three registers:

| Register      | What it does here                                     |
|---------------|-------------------------------------------------------|
| `RCC_AHB1ENR` | Enables the GPIOA clock (it is off after reset)       |
| `GPIOA_MODER` | Sets PA5 as a general-purpose output (`MODER5 = 01`)  |
| `GPIOA_ODR`   | Toggles PA5 in the main loop                          |

## Build

Requirements: CMake 3.20+, Ninja and the `arm-none-eabi` GCC toolchain in your `PATH`.

```
cmake --preset Debug
cmake --build --preset Debug
```

The output is `build/Debug/baremetal-blink.elf`. Use `Release` instead of `Debug` for an optimized build.

The project also opens in VS Code with the STM32Cube extensions, which read the CMake presets and the toolchain bundles listed in `.settings/`.

## Flash

With STM32CubeProgrammer:

```
STM32_Programmer_CLI -c port=SWD -w build/Debug/baremetal-blink.elf -v -rst
```

## Project layout

```
src/main.c                  LED blink code
src/startup_stm32f446xx.S   vector table and reset handler
src/syscall.c, sysmem.c     newlib stubs
stm32f446xe_flash.ld        linker script
cmake/                      toolchain and build configuration
```

## Reference

RM0390, STM32F446xx reference manual. Register addresses come from section 2.2.2 (memory map, table 1); the register layouts come from the RCC and GPIO chapters.
