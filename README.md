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

Damit das Display auch Software mäßig angesteuert werden kann, müssen noch folgende Definitionen
in der Software getätigt werden.

```
#define ILI9341_SPI_PORT			hspix
#define ILI9341_RES_Pin				GPIO_PIN_x
#define ILI9341_RES_GPIO_Port		GPIOx
#define ILI9341_CS_Pin				GPIO_PIN_x
#define ILI9341_CS_GPIO_Port		GPIOx
#define ILI9341_DC_Pin				GPIO_PIN_x
#define ILI9341_DC_GPIO_Port		GPIOx
#define ILI9341_LED_Pin				GPIO_PIN_x
#define ILI9341_LED_GPIO_Port		GPIOx
```

Wobei x die Angabe des definierten Pins, Ports bzw. SPIs ist.

### Rotierung

Damit das Display richtig ausgerichtet ist, kann folgender Definition verwendet werden.

```
#define ILI9341_Orientation			1
```

Die Angabe der Zahl definiert die Richtung und kann von 1 bis 4 geändert werden.

### LED

Der LED Pin ist zugleich auch für das Einschalten des Displays zuständig. Dabei wird nur Text
auf dem Display angezeigt wenn der Pin LED gesetzt ist. Wird der Pin LED wieder ausgeschaltet,
so ist das Display ebenfalls wieder aus.

Hierfür werden die Funtkionen ILI9341_LedON und ILI9341_LedOFF genutzt.

### Initialisierung

Damit die Bibliothek genutzt werden kann, muss zu Beginn im Programmcode einmal die
Initialisierung des Displays aufgerufen werden. Dies passiert über die Funktion ILI9341_Init.
Idealer weise wird diese Funktion in der `Main` vor der `while(1)` ausgeführt. Danach können
dann alle Funktionen aus der Bibliothek verwendet werden.