# OLED_Image_Converter
OLED Image Converter for OLED display 128x64 based on SSD1306 controller.
Has two modes: standart mode: 1 pixel per bit; and compress mode with RLE encoding.
## Here some examples:
### Standard decoding for STM32:
```
void ssd1306_DrawBitmap(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, const uint8_t* bitmap)
{
	uint16_t byteCount = 0;
	for(uint8_t j = 0; j < heigth; j++)
	{
		uint8_t pixelCount = 0;
		uint8_t row = y+j;
		for(uint8_t i = 0; i < width/8; i++)
		{
			for(uint8_t a = 0; a < 8; a++)
			{
				ssd1306_DrawPixel(x+pixelCount,row,((*(bitmap + byteCount)) >> a) & 1);
				pixelCount++;
			}
			byteCount++;
		}
	}
}
```
### Compressed decoding for STM32:
```
void ssd1306_DrawCompressedBitmap(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, const uint8_t* bitmap, uint16_t size)
{
	uint8_t dx = 0;
	uint8_t row = y;
	uint8_t dy = 0;
	for(uint16_t byteCount = 0; byteCount < size; byteCount++)
	{
		uint8_t color = (((*(bitmap + byteCount)) >> 7) & 1);
		uint8_t count = (*(bitmap + byteCount)) & 0x7F;
		if(dy >= heigth)
		{
		break;
		}
		else
		{
			for(uint8_t i = 0; i<=count; i++)
			{
			  if(dx>=width-1)
			  {
			  dx = 0;
			  dy++;
			  row++;
			  }
			  else
			  {
			  ssd1306_DrawPixel(x+dx,row,color);
			  dx++;
			  }
			}
		}
	}
}
```
## Warning! It has A LoT oF BuGs 🐞!
Im not a professional programmer, im more better in analogue circuits, but for my education and future projects im created this simple converter with a lot of spaggeti code.
## Preview:
![image](https://github.com/InsaneEngineer/OLED_Image_Converter/assets/64024820/37f8d430-e2f7-4764-9869-77f273dc2955)
### Resulsts: Not compressed image has size of 1 kB, compressed image has size of 776 Bytes, not great not terrible.
## Image:
![Test](https://github.com/InsaneEngineer/OLED_Image_Converter/assets/64024820/84eb499b-77fb-4024-99fa-f7edcc01f06a)

