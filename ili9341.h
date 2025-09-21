//----------------------------------------------------------------------
// Titel	:	ILI9341.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	19.05.2025
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Display ILI9341
// Quelle	:	https://github.com/afiskon/stm32-ili9341/blob/master/Lib/ili9341/ili9341.h
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_ILI9341_H_
#define INC_ILI9341_H_
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include-Dateien
//----------------------------------------------------------------------
#include "font.h"
//----------------------------------------------------------------------

// Memory Access Control Register
//----------------------------------------------------------------------
#define ILI9341_MADCTL_MY			0x80
#define ILI9341_MADCTL_MX			0x40
#define ILI9341_MADCTL_MV			0x20
#define ILI9341_MADCTL_ML			0x10
#define ILI9341_MADCTL_RGB			0x00
#define ILI9341_MADCTL_BGR			0x08
#define ILI9341_MADCTL_MH			0x04
//----------------------------------------------------------------------

// Neudefinieren des SPI wenn notwendig
//----------------------------------------------------------------------
#define ILI9341_SPI_PORT hspi3
extern SPI_HandleTypeDef ILI9341_SPI_PORT;
//----------------------------------------------------------------------

// Pins definieren
//----------------------------------------------------------------------
#define ILI9341_RES_Pin				DIS_RESET_Pin
#define ILI9341_RES_GPIO_Port		DIS_RESET_GPIO_Port
#define ILI9341_CS_Pin				DIS_CS_Pin
#define ILI9341_CS_GPIO_Port		DIS_CS_GPIO_Port
#define ILI9341_DC_Pin				DIS_DC_Pin
#define ILI9341_DC_GPIO_Port		DIS_DC_GPIO_Port
#define ILI9341_LED_Pin				DIS_LED_Pin
#define ILI9341_LED_GPIO_Port		DIS_LED_GPIO_Port
//----------------------------------------------------------------------

// Standard Orientierung
//----------------------------------------------------------------------
// Ausrichtung Pins unten = Normal
// Normal 1, Upside down 4, Nach recht liegend 2, Nach links liegend 3
#define ILI9341_Orientation			1

// Normal
#if ILI9341_Orientation == 1
//----------------------------------------------------------------------
#define ILI9341_WIDTH				240
#define ILI9341_HEIGHT				320
#define ILI9341_ROTATION			(ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR)
//----------------------------------------------------------------------

// Drehe nach rechts
#elif ILI9341_Orientation == 2
//----------------------------------------------------------------------
#define ILI9341_WIDTH				320
#define ILI9341_HEIGHT				240
#define ILI9341_ROTATION			(ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
//----------------------------------------------------------------------

// Drehe nach links
#elif ILI9341_Orientation == 3
//----------------------------------------------------------------------
#define ILI9341_WIDTH				320
#define ILI9341_HEIGHT				240
#define ILI9341_ROTATION			(ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
//----------------------------------------------------------------------

// Stelle Display auf den Kopf
#elif ILI9341_Orientation == 4
//----------------------------------------------------------------------
#define ILI9341_WIDTH				240
#define ILI9341_HEIGHT				320
#define ILI9341_ROTATION			(ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR)
//----------------------------------------------------------------------
#endif
//----------------------------------------------------------------------

// Farben definieren
//----------------------------------------------------------------------
#define ILI9341_BLACK				0x0000									/*   0,   0,   0 */
#define ILI9341_NAVY				0x000F									/*   0,   0, 128 */
#define ILI9341_DARKGREEN			0x03E0									/*   0, 128,   0 */
#define ILI9341_DARKCYAN			0x03EF									/*   0, 128, 128 */
#define ILI9341_MAROON				0x7800									/* 128,   0,   0 */
#define ILI9341_PURPLE				0x780F									/* 128,   0, 128 */
#define ILI9341_OLIVE				0x7BE0									/* 128, 128,   0 */
#define ILI9341_LIGHTGREY			0xC618									/* 192, 192, 192 */
#define ILI9341_DARKGREY			0x7BEF									/* 128, 128, 128 */
#define ILI9341_BLUE				0x001F									/*   0,   0, 255 */
#define ILI9341_GREEN				0x07E0									/*   0, 255,   0 */
#define ILI9341_CYAN				0x07FF									/*   0, 255, 255 */
#define ILI9341_RED					0xF800									/* 255,   0,   0 */
#define ILI9341_MAGENTA				0xF81F									/* 255,   0, 255 */
#define ILI9341_YELLOW				0xFFE0									/* 255, 255,   0 */
#define ILI9341_WHITE				0xFFFF									/* 255, 255, 255 */
#define ILI9341_ORANGE				0xFD20									/* 255, 165,   0 */
#define ILI9341_GREENYELLOW			0xAFE5									/* 173, 255,  47 */
#define ILI9341_COLOR565			(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void ILI9341_Unselect (void);
void ILI9341_Init (void);
void ILI9341_DrawPixel (uint16_t x, uint16_t y, uint16_t color);
void ILI9341_WriteString (uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void ILI9341_FillRectangle (uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ILI9341_FillScreen (uint16_t color);
void ILI9341_DrawImage (uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
void ILI9341_InvertColors (bool invert);
void ILI9341_LedON (void);
void ILI9341_LedOFF (void);
//----------------------------------------------------------------------

#endif // INC_ILI9341_H_
