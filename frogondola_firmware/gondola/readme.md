# Gondola

![gondola](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [my-fi](https://github.com/my-fi-25073)
* Hardware Supported: STM32F072
* Hardware Availability: most of GH60 based keyboard

Make example for this keyboard (after setting up your build environment):

    make gondola:default

Flashing example for this keyboard:

    make gondola:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
