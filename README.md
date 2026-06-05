# STM32 ILI9341 Display
 
Eine in C implementierte Treiberbibliothek für den ILI9341-Display-Controller auf
STM32-Mikrocontrollern. Die Ansteuerung erfolgt über SPI. Die Bibliothek umfasst
Funktionen zur Anzeige von Text, geometrischen Flächen, Einzelpixeln und Bildern
sowie einen integrierten Zeichensatz in drei Größen.
 
Die Bibliothek basiert auf dem Projekt von [afiskon/stm32-ili9341](https://github.com/afiskon/stm32-ili9341)
und wurde weiterentwickelt.
 
## Beschreibung
 
Das ILI9341 ist ein weit verbreiteter TFT-Display-Controller für 2,4"–2,8"-Displays
mit einer Auflösung von 240×320 Pixeln. Die Bibliothek steuert das Display
vollständig über SPI an und verwaltet die GPIO-Leitungen für Reset, Chip-Select,
Data/Command und Hintergrundbeleuchtung direkt im Code. Farben werden im RGB565-Format
(16 Bit) übergeben.
 
## Dateien
 
| Datei             | Beschreibung                                                             |
|-------------------|--------------------------------------------------------------------------|
| `ili9341.h`       | Hauptheader: API, Farbdefinitionen, Orientierung, Pin-Mapping            |
| `ili9341.c`       | Implementierung aller Display-Funktionen                                 |
| `font.h`          | `FontDef`-Struktur und Deklaration der drei Schriftgrößen                |
| `font.c`          | Pixel-Daten der Zeichensätze Font_7x10, Font_11x18, Font_16x26          |
| `ili9341_img.h`   | Testbild als uint16_t-Array im RGB565-Format (projektspezifisch anpassen)|
 
## Hardware-Anschluss
 
Das Display wird über SPI im Full-Duplex-Master-Modus betrieben. Zusätzlich zum
SPI-Bus werden vier GPIO-Leitungen benötigt:
 
| Signal  | Beschreibung                                      |
|---------|---------------------------------------------------|
| RESET   | Hardware-Reset des Displays                       |
| CS      | Chip-Select (wird manuell im Code gesteuert)      |
| DC      | Data/Command-Umschaltung                          |
| LED     | Hintergrundbeleuchtung / Display ein/aus          |
 
**Hinweis zum SPI:** Das Hardware-NSS-Signal muss in CubeMX auf „Disable" gestellt
werden, da der CS-Pin manuell gesteuert wird. Dies ermöglicht es, mehrere Befehle
nacheinander zu senden und später eine Touch-Anbindung über denselben SPI-Port zu
realisieren.
 
## Konfiguration in `main.h`
 
Folgende Definitionen müssen in der `main.h` des Projekts gesetzt werden, damit die
Bibliothek korrekt auf die Hardware zugreifen kann:
 
```c
#define DIS_SPI_PORT        hspix               // z. B. hspi3
 
#define DIS_RESET_Pin       GPIO_PIN_x
#define DIS_RESET_GPIO_Port GPIOx
 
#define DIS_CS_Pin          GPIO_PIN_x
#define DIS_CS_GPIO_Port    GPIOx
 
#define DIS_DC_Pin          GPIO_PIN_x
#define DIS_DC_GPIO_Port    GPIOx
 
#define DIS_ON_Pin          GPIO_PIN_x
#define DIS_ON_GPIO_Port    GPIOx
```
 
Wobei `x` jeweils der konkrete Pin, Port oder SPI-Handle des Projekts ist.
 
### Displayausrichtung
 
Die Orientierung wird ebenfalls in `main.h` oder direkt in `ili9341.h` definiert:
 
```c
#define ILI9341_Orientation  1
```
 
| Wert | Ausrichtung             | Auflösung  |
|------|-------------------------|------------|
| `1`  | Normal (Pins unten)     | 240 × 320  |
| `2`  | Nach rechts gedreht     | 320 × 240  |
| `3`  | Nach links gedreht      | 320 × 240  |
| `4`  | Auf den Kopf gestellt   | 240 × 320  |
 
## API
 
```c
void ILI9341_Init(void);                                                          // Display initialisieren
void ILI9341_LedON(void);                                                         // Hintergrundbeleuchtung einschalten
void ILI9341_LedOFF(void);                                                        // Hintergrundbeleuchtung ausschalten
void ILI9341_FillScreen(uint16_t color);                                          // Gesamten Bildschirm mit Farbe füllen
void ILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color);                  // Einzelnen Pixel setzen
void ILI9341_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                            uint16_t color);                                       // Rechteck mit Farbe füllen
void ILI9341_WriteString(uint16_t x, uint16_t y, const char* str,
                          FontDef font, uint16_t color, uint16_t bgcolor);        // Text ausgeben
void ILI9341_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                        const uint16_t* data);                                    // Bild ausgeben (RGB565-Array)
void ILI9341_InvertColors(bool invert);                                           // Farben invertieren
void ILI9341_Unselect(void);                                                      // CS-Pin freigeben
```
 
## Zeichensätze
 
Die Bibliothek enthält drei eingebettete Zeichensätze, die direkt an `ILI9341_WriteString` übergeben werden:
 
| Schrift      | Größe (B × H) | Verwendung               |
|--------------|---------------|--------------------------|
| `Font_7x10`  | 7 × 10 Pixel  | Kleine Beschriftungen    |
| `Font_11x18` | 11 × 18 Pixel | Standardtext             |
| `Font_16x26` | 16 × 26 Pixel | Große, gut lesbare Texte |
 
## Vordefinierte Farben
 
Die Bibliothek stellt fertige RGB565-Farbkonstanten bereit:
 
`ILI9341_BLACK`, `ILI9341_WHITE`, `ILI9341_RED`, `ILI9341_GREEN`, `ILI9341_BLUE`,
`ILI9341_CYAN`, `ILI9341_MAGENTA`, `ILI9341_YELLOW`, `ILI9341_ORANGE`, `ILI9341_NAVY`,
`ILI9341_DARKGREEN`, `ILI9341_DARKCYAN`, `ILI9341_MAROON`, `ILI9341_PURPLE`,
`ILI9341_OLIVE`, `ILI9341_LIGHTGREY`, `ILI9341_DARKGREY`, `ILI9341_GREENYELLOW`
 
Eigene Farben können mit dem Makro berechnet werden:
 
```c
ILI9341_COLOR565(r, g, b)   // Berechnet RGB565 aus 8-Bit R, G, B
```
 
## Verwendung
 
### 1. Dateien einbinden
 
Alle Dateien in das STM32-Projekt kopieren und den Header einbinden:
 
```c
#include "ili9341.h"
```
 
### 2. Initialisierung
 
Vor der Hauptschleife einmalig aufrufen:
 
```c
ILI9341_Init();
ILI9341_DisplayON();
```
 
### 3. Anzeige
 
```c
// Bildschirm schwarz füllen
ILI9341_FillScreen(ILI9341_BLACK);
 
// Text ausgeben
ILI9341_WriteString(10, 10, "Hallo Welt!", Font_16x26, ILI9341_WHITE, ILI9341_BLACK);
 
// Rechteck zeichnen
ILI9341_FillRectangle(20, 60, 100, 50, ILI9341_BLUE);
 
// Einzelnen Pixel setzen
ILI9341_DrawPixel(120, 160, ILI9341_RED);
 
// Bild anzeigen (aus ili9341_img.h)
ILI9341_DrawImage(0, 0, 240, 320, (uint16_t*)image_data);
```
 
### 4. Bilder anzeigen
 
Bilder müssen als `uint16_t`-Array im RGB565-Format in `ili9341_img.h` abgelegt werden.
Das Array kann z. B. mit einem Bildkonverter (z. B. LCD Image Converter) aus einer
Grafik erzeugt werden. Breite und Höhe des Bildes müssen beim Aufruf von `ILI9341_DrawImage`
angegeben werden.
 
## Quellen
 
Diese Bibliothek basiert auf:
- [afiskon/stm32-ili9341](https://github.com/afiskon/stm32-ili9341)

## Abhängigkeiten
 
- `main.h` – STM32 HAL (inkl. SPI- und GPIO-Handle)

## Lizenz
 
Dieses Projekt steht unter der [GPL-3.0 Lizenz](LICENSE).
 
