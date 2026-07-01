# DBR Organ Console

USB MIDI console firmware for virtual pipe organs based on **STM32F401** and **TinyUSB**.

Originally designed for **Aeolus**, the firmware is intended to be compatible with any software supporting the standard USB MIDI protocol, including GrandOrgue and other virtual organ applications.

---

## Features

* STM32F401 based firmware
* USB MIDI device using TinyUSB
* Two manuals
* One pedalboard
* 64 illuminated stop buttons
* Matrix keyboard scanning
* Low latency MIDI transmission
* Modular firmware architecture
* USB Vendor/Product descriptors fully customizable

---

## Hardware

Current hardware configuration:

* STM32F401CCU6
* USB Full Speed
* Two manual keyboards
* Pedalboard interface
* 64 stop buttons with LEDs

---

## Firmware

Main software modules:

* Keyboard matrix scanner
* Pedalboard scanner
* Stop management
* LED management
* USB MIDI interface
* TinyUSB integration

---

## Project structure

```
Core/
Drivers/
TinyUSB/
Docs/
    Images/
    Manual/
    Schematic/
```

---

## Building

Development environment:

* STM32CubeIDE
* STM32 HAL
* TinyUSB

The TinyUSB library will be included as a Git submodule.

---

## Roadmap

* [x] USB MIDI implementation
* [x] Dual manual support
* [x] Pedalboard support
* [x] Stop controls
* [ ] USB descriptor customization
* [ ] GitHub public release
* [ ] pid.codes VID/PID registration

---

## License

BSD 3-Clause License.

