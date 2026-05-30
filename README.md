# Overview
An esp-32 based dashboard with a 4.2" e-ink display from waveshare.
## Why?
Its main purpouse is just sitting on a desk and looking nice, nothing much besides that.
## Features
- Displaying current spotify playing song
- Time and date
- Weather
- [WIP]
# Part List
- [Seeed Studio Xiao ESP32-S3 Plus](https://kamami.pl/xiao/1195704-xiao-esp32s3-plus-plytka-rozwojowa-z-mikrokontrolerem-esp32s3-5906623496303.html)
- [Waveshare 4.2" e-ink display](https://botland.com.pl/wyswietlacze-e-paper/9655-e-paper-e-ink-42-400x300px-modul-z-wyswietlaczem-spi-waveshare-13353-5904422338312.html)
- [4000mAh li-po](https://botland.com.pl/akumulatory-li-pol-1s-37v/15644-akumulator-li-pol-akyga-4000mah-1s-37v-zlacze-jst-bec-gniazdo-80x50x8mm-5904422343644.html)
- 2 * 100kOhm Resistors -- i already own them
- [JST-BEC female adapter](https://botland.com.pl/akcesoria-do-akumulatorow/2865-para-konektorow-jst-bec-do-akumulatorow-li-pol-5904422331221.html)
- Male pin headers 8x2.54mm -- They come with the display
# Media
## Schematics & PCB
![sch](https://github.com/teocza-111/esp-32Dashboard/blob/main/Media/schematic.png)
![PCB](https://github.com/teocza-111/esp-32Dashboard/blob/main/Media/PCB.png)
## Renders [WIP]
![PCB](https://github.com/teocza-111/esp-32Dashboard/blob/main/Media/PCB-render.png)
![V0](https://github.com/teocza-111/esp-32Dashboard/blob/main/Media/dashboard-render-nocase.png)
## Bill of materials
|Name                           |Purpose                                   |Quantity|Total Cost (USD)|Link                                                |Distributor    |
|-------------------------------|------------------------------------------|--------|----------------|----------------------------------------------------|---------------|
|JST-PH 2.0 Female              |Connecting the battery to the mcu         |1       |0.84            |https://pl.aliexpress.com/item/4000199807342.htm    |AliExpress     |
|100kOhm Resistors              |Safely reading the volatage of the battery|2       |0.00            |                                                    |My resistor kit|
|4000mAh li-po battery          |The power source                          |1       |9.48            |https://pl.aliexpress.com/item/1005009889665207.html|AliExpress     |
|Seeed Studio Xiao ESP32-S3 Plus|MCU                                       |1       |12.46           |https://pl.aliexpress.com/item/1005010291070801.html|AliExpress     |
|Waveshare 4.2" e-ink display   |The display                               |1       |39.44           |https://pl.aliexpress.com/item/1005004260969887.html|AliExpress     |
|PCB                            |It's... Well a PCB                        |1       |10.00           |                                                    |JLCPCB         |

