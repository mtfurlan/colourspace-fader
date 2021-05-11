# Colourspace library

Goal: get a nice colour fade that looks like each colour is equal

## Approach
In CIELCHab, with a static L and C, iterate over h.
* convert CIELCHab to RGB
* convert RGB to CIELab, calculate difference from last RGB point
* while under min diff, keep iterating h
* store last CIELCH
* output

### Issues
It's a bit jumpy with CIE74/94 ΔE(Or I did the hue stuff wrong, changed it since
I stopped using these), kinda slow with CIE2000 ΔE, and it stays too long on
blue.


## Layout
* lib/colurConvert
  * yy_color_converter with extra wrappers and ΔE functions
  * Needs to be combined and cleaned up
  * needs to become actual PIO library with it's own tests and such
* test/testColourConvert
  * testing colourconvert library
* src/main.ino
  * actual colourfade!

## Sources
* https://github.com/ibireme/yy_color_convertor
* http://www.brucelindbloom.com/index.html?Math.html

## Debug stack dump on ESP8266
```
java -jar /tmp/EspStackTraceDecoder.jar ~/.platformio/packages/toolchain-xtensa/bin/xtensa-lx106-elf-addr2line  ./.pio/build/d1_mini/firmware.elf dump
```
