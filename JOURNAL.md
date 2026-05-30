---
title: "esp32-Dashboard"
author: "teocza"
description: "Esp32-based desk dashboard with an e-ink display"
created_at: "2026-05-30"
---

# 5/30/2026 8 PM - Started the CAD

_Time spent: 2h_

I don't have any photos yet since i forgot to take any and im wirting this on a laptop, (will be added once im back on da pc)
I made the first part of the case, the idea is that there will be a plate that i will be able to slide into the main housing
Also a stand-thingy would be nice, will think abt that

# 5/24/2026 6 PM - Finished the firmware

_Time spent: 1.5h_

Assigned pins, made the code actually work with hardware
I used claude for a clean display layout (forgive me)
The rest i did by hand
![Zrzut ekranu (120)](https://stasis.hackclub-assets.com/images/1779646341833-t2mm5g.png)
will start designing the case asap

![image](https://stasis.hackclub-assets.com/images/1779646341833-t2mm5g.png)

# 5/9/2026 6 PM - Firmware and other minor thing

_Time spent: 4.5h_

Added all the parts to the bill of material,

Started working on my firmware, looked into the spotify display guide for some help authenticating my spotify account, added time fetching and weather data fetching using open meteo.
```
const char* WEATHER_URL =
  "https://api.open-meteo.com/v1/forecast"
  "?latitude=0000&longitude=0000"
  "&current=temperature_2m";
```
 Connecting to my home wifi etc.
I didn't yet add drawing the info to the screen, just fetching.
I decided to paste this into claude to find any mistakes and see if i can improve something but it just said that "yeah your thing is bs look at this" and basically re-did the whole thing
well i cant really complain since i dont really enjoy coding and i have my finals on monday so after that ill have soooo much time for debugging all of that

here are some screenshots

![Zrzut ekranu (105)](https://stasis.hackclub-assets.com/images/1778351400870-54o3uf.png)

![Zrzut ekranu (104)](https://stasis.hackclub-assets.com/images/1778351400849-wnngs6.png)


ill still count the time it took me to research all the libraries write the original code make the bom etc.

i also (will after writing this) expanded the earlier entries in the journal with some more info

![image](https://stasis.hackclub-assets.com/images/1778351400870-54o3uf.png)
![image](https://stasis.hackclub-assets.com/images/1778351400849-wnngs6.png)

# 5/5/2026 7 PM - Quick PCB update and new renders

_Time spent: 0.25h_

Made the JST-PH female port on the pcb more accesible so the battery cable doesn't bend that much,

Also gave my README.md a quick update with all the new screenshots and renders,
I'll start working on the case and firmware soon since the pcb is finished (or so I hope)


![dashboard-render-nocase](https://stasis.hackclub-assets.com/images/1778010327673-c4om9v.png)

![image](https://stasis.hackclub-assets.com/images/1778010327673-c4om9v.png)

# 4/25/2026 1 PM - Research and PCB

_Time spent: 5h_

So I wanted to make something that would look nice on my desk and it landed on a dashboard.
I got inspired by the spotify displays that people make so I want this to also be integrated with my spotify.

More on what will this exactly do will come when i start making the firmware.

anyway

Today I made the overall part list schematic and PCB

The main mcu is a seeed studio esp32-s3 plus, the display will be connected using SPI (the 8 male pin header). The battery has a JST-PH 2.0 male connector so i decided to include a female one(resembled by the 2 male pin header) on the pcb for easy connection.
2 * 100k ohms resistors to read the battery voltage (ADC)

![PCB-render](https://stasis.hackclub-assets.com/images/1777124565668-8tov3t.png)
The board may seem a bit big but the display will be even bigger so it doesnt really matter.

I couldn't decide between a few diffrent board but it landed on the Seeed studio esp32-s3 plus, it has abattery voltage regulator,charging and voltage reading capebilities

I'll also make a short README.md on the github repo after writing this journal

![image](https://stasis.hackclub-assets.com/images/1777124565668-8tov3t.png)
