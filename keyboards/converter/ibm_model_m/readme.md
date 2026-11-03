# IBM Model M 1391401 to USB Converter

This target reads the Model M's native PS/2 scan-code set 2 and reports keys through QMK's matrix and keymap system. Customize the default keymap or add layers like any other QMK keyboard.

## Build

```sh
qmk compile -kb converter/ibm_model_m -km default
```

## Wiring

Use a 5 V / 16 MHz Pro Micro. Connect the keyboard's PS/2 connector as follows:

| PS/2 connector | Signal | Pro Micro |
| --- | --- | --- |
| Pin 1 | Data | D3 (`PD0`) |
| Pin 3 | Ground | GND |
| Pin 4 | +5 V | VCC |
| Pin 5 | Clock | D2 (`PD1`, `INT1`) |

PS/2 connector pin numbers are viewed at the socket, not inferred from cable wire colors. The PS/2 clock and data lines are open-collector; add a 4.7 kOhm pull-up from each line to +5 V for a robust bus. Do not connect a 5 V keyboard directly to a 3.3 V Pro Micro without suitable level protection.

The QMK PS/2 USART driver requires USART1 `XCK1` on `PD5`; that pin is not broken out on a standard Pro Micro. This target therefore uses the interrupt driver on the Pro Micro's exposed `PD1` clock pin. A board that exposes `PD5` can be adapted to USART operation.