## lorapipe

Lorapipe is a tool for piping LoRa data to and from consumer grade radios.

## Features

 - Simple serial cli built into the firmware
 - KISS-TNC (coming soon)

## Compiling
- Install [PlatformIO](https://docs.platformio.org) in [Visual Studio Code](https://code.visualstudio.com).
- Clone and open the lorapipe repository in Visual Studio Code.
- See the example applications you can modify and run:
  - [Simple Repeater](./examples/simple_repeater)

## Flashing

We haven't built a flashing tool yet. You can flash builds using the OEM provided flashing tools or using the developer instructions to flash using VS Code.

- Flash using your platform's OEM flashing tool


## Hardware Compatibility

lorapipe is designed for devices supported by MeshCore so check their support list in the [MeshCore Flasher](https://flasher.meshcore.co.uk). We support all the same hardware.

## Serial CLI

The lorapipe firmware initially starts up in a serial mode which is human readable. You can connect to the serial console using a serial terminal application like below.

`minicom -D /dev/ttyACM0`

Once connected the lorapipe device has a simple CLI. The CLI is largely similar to meshcore with a few notable additions.

### LoRa pipe CLI additions

 * `txraw <hex...>` - Transmist a packet
 * `get syncword <word>` - Read the syncword setting
 * `set kiss port <port>` - Set the KISS device port
 * `set radio <freq>,<bw>,<sf>,<coding-rate>,<syncword>` - Configure the radio
 * `serial mode kiss` - Switch to KISS mode
 * `rxlog on`
   * Output format: ` [timestamp],[type=RXLOG],[rssi],[snr],[hex...]\n` 

### Existing Commands

 * `reboot`
 * `clock sync`
 * `start ota`
 * `clock`
 * `time`
 * `tempradio`
 * `clear stats`
 * `get af`
 * `get agc.reset.interval`
 * `get name`
 * `get lat`
 * `get lon`
 * `get radio`
 * `get rxdelay`
 * `get txdelay`
 * `get tx`
 * `get freq`
 * `set af`
 * `set int.thresh`
 * `set agc.reset.interval`
 * `set name`
 * `set radio`
 * `set lat`
 * `set lon`
 * `set rxdelay`
 * `set txdelay`
 * `set tx`
 * `set freq`
 * `erase`
 * `ver`
 * `log start`
 * `log stop`
 * `rxlog on`
 * `rxlog off`
