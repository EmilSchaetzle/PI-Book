# PI-Book - Building instructions
## How to build the case of the PI-Book:
1. Print all parts with a 3D-Printer.
2. The PIBookCasingParts 1-6 belong together. You may need a good amount of pressure to combine the different parts, or you simply grind the edges.
3. The PIBookKeyboardTable 1 & 2 fit in the gaps in the ground. Table 1 is on the lefthand side and table 2 on the righthand side.
4. The PIBookCoverParts 1-6 belong together and fit in the bottom part of the casing.
5. The PIBookTopParts 1-4 are for the lid.
6. It is recommended to use some glue to fix all parts.
7. To mount the lid to the rest of the case you have to drill some holes in the back side of the casing. We didn't design the holes, so you can use your own hinges.
8. The keys can also be glued on the keyboard.

## What else do i have to do?
1. Install the Raspberry Pi and the Video Driver Board.
2. Put the power supply in (you also find the schematics in our repository). To connect it to the Raspberry Pi and the Video Driver Board you may have to remove the original power connector (you may need to pull/push harder as usual to remove it).
3. Remove the analog video connector from the Raspberry Pi and the Video Driver Board and connect it with 2 cables.
4. Glue the screen and the solar cell on the lid. Make sure to install it the right way around.
5. Guide the cables inside through the holes provided for this purpose and connect them to the Video Driver Board/the power supply.
6. Build in the keyboard and connect it to the Raspberry Pi (connect it correctly!). The plans for the keyboard are also in our repository. You have to order the circuit board and all components. Then you have to place the chip and solder it (thats not easy!). Do the same with all the other components.
7. Glue the GPIO and connect it to the Raspberry Pi (don't forget the Logic-Level-Shifter).
8. Glue the micro usb port and connect it to the power supply.
9. Built in your power switch. You may have to adjust the existing pedestal.
10. Now compile and install the software for the keyboard-chip via the ICSP header.
11. Add https://emilschaetzle.de/pi-book as a PPA and install the pibook-hid-driver-dkms package.
12. Your DONE! Congratulations!


## If you have any questions, send us an email to: pibook@emilschaetzle.de


## Our components:

- battery: https://www.amazon.de/gp/product/B007AF2858/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1 and https://www.amazon.de/gp/product/3860008331/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1
- loading module: https://www.amazon.de/gp/product/B077XW1XBJ/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1
- audio cable: https://www.amazon.de/gp/product/B00K1PCKJ8/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1
- charger module: https://www.amazon.de/gp/product/B07D2G345P/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1 and https://www.amazon.de/gp/product/B077XW1XBJ/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1
- voltage regulators: https://www.amazon.de/gp/product/B06XSJSCSW/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1
- step up module: https://www.amazon.de/gp/product/B079H3YD8V/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1
- step down module: https://www.amazon.de/gp/product/B00QFDRR9S/ref=ppx_yo_dt_b_asin_title_o07_s00?ie=UTF8&psc=1
- display and Video Driver Board: https://www.ebay.de/itm/10-1-Zoll-Farb-TFT-LCD-Display-mit-HDMI-VGA-Video-Driver-Board-f%C3%BCr-Raspberry-Pi/123153134147?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2648
- 50 pin flex cable: https://www.ebay.de/itm/Flachbandkabel-LVDS-Flex-Kabel-SERONICS-AWM-20861-105-C-FT1-FT2-50-Pins/113573288524?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2648
- jumper wire: https://www.ebay.de/itm/Jumper-Wire-Steckbr%C3%BCcken-Steckbrett-Kabel-20p-male-female-m%C3%A4nnlich-weiblich/252715145677?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649
- Logic-Level-Shifter: https://www.ebay.de/itm/4-Kanal-Pegelwandler-bidirectional-I2C-SPI-Logic-Level-Shifter-ESP-Arduino/202099886271?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649
- hinges: https://www.ganter-griff.de/de/produkte/3.3-Schwenken-Verriegeln-von-Tueren-und-Klappen/Scharniere-mit-einstellbarer-Friktion/GN-233-Scharniere-mit-einstellbarer-Friktion-Kunststoff-Cleanline
- Raspberry Pi: https://www.sertronics-shop.de/raspberry-pi-co/raspberry-pi/boards-kits/raspberry-pi-3-modell-b-43
- buttons: http://d.digikey.com/wXyKp37SN10n0GXd00o0c09 CKN9093-ND
- joystick: http://d.digikey.com/v03y0p9d07NKSGeXX00o10n 1568-1526-ND
- Pi-Connector: http://d.digikey.com/l9Xog001NXyGnK0730p0f0S 732-5316-ND
- ICSP Header: http://d.digikey.com/yX9SyoGp070NKXgn3h10000 732-5295-ND
- resonator 15pF: http://d.digikey.com/O091G3oK000npSNi0j07XyX 490-1212-ND
- resonator 30pF: http://d.digikey.com/SX1K070yN030pSGnX009okj X905-ND
- ATmega: http://d.digikey.com/a10n0N0XoS0y00lKkXp93G7 ATMEGA2560-16AU-ND
- resistor: http://d.digikey.com/m000pm003no7XNGyX9l0SK1 BC4504CT-ND
- capacitor: http://d.digikey.com/A90o03SX00p7XGo10N0nnyK BC1084CT-ND
- GPIO: http://d.digikey.com/s0o90NX0yXpp0Sno3G0170K SAM11096-ND
- we already had a micro usb port and a power switch so you have to search one by yourself
