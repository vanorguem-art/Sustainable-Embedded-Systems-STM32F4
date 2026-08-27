# STM32F4 Embedded Systems - PoliTo Lab Projects

**Author:** Yvana Fotso
**Contact:** vanorguem@gmail.com | https://www.linkedin.com/in/yvana-fotso
**Platform:** STM32F411RE Nucleo | STM32CubeIDE | LL Drivers  
**Course:** Digital Systems & Embedded - Politecnico di Torino

This repository contains 6 hands-on projects on STM32F4 low-level programming, focusing on real-time GPIO control, button debouncing, and signal generation. These projects are part of my portfolio for Master MICS application at University of Luxembourg.

### 🔧 Projects Overview

**PART0 - Basic LED Blink**
- Bare-metal LED blink using LL drivers
- Busy-wait delay implementation

**PART1.1 - Button Controlled LED (Polling)**
- Reading user button (PC13) without interrupts
- LED on/off based on button state

**PART1.2 - Button Controlled LED with Debouncing**
- Software debouncing using delay
- Stable button reading

**PART1.3 - Frequency Control (LAB Highlight)**
- LED blinks at ~1 Hz
- When button pressed, frequency doubles to ~2 Hz
- Square wave generation visible on oscilloscope (PA5)
- **Key skill:** Dynamic delay adjustment: `wait / 2`

**PART2 - Toggle Mode (Fixed LED)**
- One button press = LED ON (fixed)
- Second press = LED OFF
- State machine with `led_state`

**PART3 - Toggle Mode (Blinking LED) - Advanced**
- One press = LED starts blinking
- Second press = LED stops
- Combines toggle logic + blinking loop
```c
if (button_pressed) led_state = !led_state;
if (led_state == 1) {
  // blink logic
}
