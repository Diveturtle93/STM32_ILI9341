# Display ILI9341 ansteuern

Diese Bibliothek stellt alle nötigen Funktionen für die Ansteuerung eines ILI9341-Display mit
einem STM32 zur Verfügung. Dabei wird das Display über SPI angesteuert. Zusätzlich sind noch
die Leitungen Reset und DC am Display anzuschließen und im Programm zu steuern.

Die Bibliothek stellt Funktionen zur Anzeige von Text, einzelnen Zeichen oder einem Image
zur Verfügung. Für die Ausgabe von Text wird zusätzlich noch der Zeichensatz mit erstellt.
Dieser ist in drei größen vorhanden. 7x10 Pixel, 11x18 Pixel und 16x26 Pixel. Eine Anpassung
für weitere Schriftsätze kann ebenfalls erfolgen.

Aktuell ist eine Funktion für die Anzeige eines Bildes vorhanden. Dafür wird ein Testbild im
Speicher abgelegt. Diese muss individuell auf die Bedürfnisse eines jeden Projektes angepasst
werden.

Weitere Funktionen die für die Ansteuerung des Displays vorhanden sind, sind DrawPixel,
FillRectangle und FillScreen. Bei der Funktion DrawPixel wird an der Koordinate x y ein Pixel
in der definierten Farbe ausgegeben. Das Selbe passiert auch bei den Funktionen FillRectangle
und FillScreen. FillRectangle definiert an der Koordinate x y einen rechteckigen Bereich der
mit der definierten Farbe gefüllt wird. FillScreen löscht das gesamte Display und setzt alle
Pixel mit der gewünschten Farbe.

### Pining

Damit das Display auch softwaremäßig angesteuert werden kann, müssen noch die Pins in der
Software bestimmt werden. Die Konfiguration der Bibliothek sieht wie folgt aus.

```
#define ILI9341_RES_Pin				DIS_RESET_Pin
#define ILI9341_RES_GPIO_Port		DIS_RESET_GPIO_Port
#define ILI9341_CS_Pin				DIS_CS_Pin
#define ILI9341_CS_GPIO_Port		DIS_CS_GPIO_Port
#define ILI9341_DC_Pin				DIS_DC_Pin
#define ILI9341_DC_GPIO_Port		DIS_DC_GPIO_Port
#define ILI9341_LED_Pin				DIS_LED_Pin
#define ILI9341_LED_GPIO_Port		DIS_LED_GPIO_Port
```

Damit werden alle Pins die zusätzlich zum SPI benötigt werden gesetzt. Nun müssen entweder
die zu nutzenden Pins mit den Platzhaltern `DIS_RESET, DIS_CS, DIS_DC` und `DIS_LED` benannt
werden. Dies ist am einfachsten in MX-Cube. Oder man setzt die Pins manuell in der `main.h`.

Ebenfalls werden die Pins für den SPI Port ausgewählt. Dann muss noch der SPI-Port an die
Bibliothek übergeben werden. Dies kann man mit dem nächsten Befehl machen.

```
#define ILI9341_SPI_PORT hspi3
```

Standardmäßig ist in der Software SPI3 ausgewählt. Hier kann aber auch jeder andere SPI-Port
verwendet werden.

### SPI

Zusätzlich zur Auswahl des SPI, muss dieser auch noch richtig eingestellt werden. Der SPI
fungiert als Full-Duplex Master. Eine Hardware Chip-Select Leitung wird nicht benötigt.
Diese wird schon bei der Definition der Pins mit dabei und kann ausgeschaltet bleiben.

Auch ein DMA oder Interrupt Handler wird für die Bibliothekt nicht benötigt. Daher können
diese beiden Einstellungen ebenfalls abgeschaltet bleiben.

Als nächstes folgt die Einstellung der Parameter. Die nachfolgende Tabelle stellt alle
Parameter für die Einstellung des SPIs für das ILI9341 Display dar.

|  |  |  |
|:-|:-|:-|
| Basic Parameter |  |  |
| | Frame Format | Motorola |
| | Data Size | 8 Bits |
| | First Bit | MSB First |
| Clock Parameter |  |  |
| | Prescaler | 2 | |
| | Clock Polarity (CPOL) | Low |
| | Clock Phase (CPHL) | 1 Edge |
| Advanced Parameters | | |
| | CRC Calculation | Disable |
| | NSS Signal Type | Software |

Für den Prescaler ist noch auf die Frequenz zu achten. Die Bibliothek ist aktuell nicht in
der Lage die Frequenz automatisch einzustellen. Daher ist der Prescaler an die eigenen
Einstellungen für den STM32 anzupassen. Hier ist der Prescaler 2 und der SPI für das Display
läuft mit einer Taktfrequenz von 18 MHz.

### Rotierung

Damit das Display richtig ausgerichtet wird, kann folgender Definition verwendet werden.

```
#define ILI9341_Orientation			1
```

Die Angabe der Zahl definiert die Richtung und kann von 1 bis 4 geändert werden. Hierbei ist
die Standardausrichtung mit den Pinnen nach unten.

| Ausrichtung | Orientierung |
|:----------- |:------------:|
| Normal | 1 |
| Nach Rechts gedreht | 2 |
| Nach Links gedreht | 3 |
| Upside Down | 4 |

In der Software wird abgefragt, ob die Orientierung ausgewählt wurde. Dies kann mit dem oben
genannten Define gemacht werden. Wird das Define nicht in der `main.h` gesetzt, so wird die
Standardausrichtung ausgewählt.

### LED

Der LED Pin ist zugleich auch für das Einschalten des Displays zuständig. Dabei wird nur Text
auf dem Display angezeigt wenn der Pin LED gesetzt ist. Wird der Pin LED wieder ausgeschaltet,
so ist das Display ebenfalls wieder aus.

Hierfür werden die Funtkionen ILI9341_LedON und ILI9341_LedOFF genutzt.

### Initialisierung

Damit die Bibliothek genutzt werden kann, muss zu Beginn im Programmcode einmal die
Initialisierung des Displays aufgerufen werden. Dies passiert über die Funktion ILI9341_Init.
Idealer weise wird diese Funktion in der `main` vor der `while(1)` ausgeführt. Danach können
dann alle Funktionen aus der Bibliothek verwendet werden.