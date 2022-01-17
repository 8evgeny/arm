#include "gpio.h"
#include "main.h"
#include "usb.h"
#include <string>
#include <vector>
#include <string.h>
#include <chrono>


int main (int argc, char** argv) {

	__disable_irq();
	RCC_init();
	GPIO_init();
	__enable_irq();

    TIM1_init();
    IWDT_init();
    VCom_Configuration();

    USB_CDC_Init(Buffer, 84, SET);
    Setup_CPU_Clock();
    Setup_USB();

    LCD_init();
    Check();

	while (1) {
        parsingBuffer();

        if(BufferLCD[0] == 49) //если 1 то горит первый светодиод
        {
            PORT_SetBits(MDR_PORTB, LED2_REC);
        }
        else
        {
            PORT_ResetBits(MDR_PORTB, LED2_REC);
        }
        if(BufferLCD[1] == 49) //если 1 то горит второй светодиод
        {
            PORT_SetBits(MDR_PORTB, LED1_ERROR);
        }
        else
        {
            PORT_ResetBits(MDR_PORTB, LED1_ERROR);
        }
        if (BufferLCD[2] == 49) //Постоянный сигнал
        {
            PORT_SetBits(MDR_PORTB, BUZZER);
        }
        else //Выключен
        {
            PORT_ResetBits(MDR_PORTB, BUZZER);
        }

//        checkLCD1();
//        checkLCD2();
//        checkBUZZER();

        char  str1[21]; //4 строки на экране
        char  str2[21];
        char  str3[21];
        char  str4[21];

        memcpy (str1, BufferLCD + 3, 20);
        memcpy (str2, BufferLCD + 23 , 20);
        memcpy (str3, BufferLCD + 43 , 20);
        memcpy (str4, BufferLCD + 63 , 20);

        PrintString1(str1);
        PrintString2(str2);
        PrintString3(str3);
        PrintString4(str4);

        IWDG_ReloadCounter();	//сбрасываем IWDT
	}	
}

void parsingBuffer()
{
    uint8_t* pBuff = Buffer;
    uint8_t* pBuffLCD = BufferLCD;

    for (int numSymbols = 0; numSymbols < 83; ++numSymbols)
    {
        uint8_t temp = *pBuff;
        if ((temp & 0xD0) != 0xD0)
        {
            *pBuffLCD = *pBuff;
            ++pBuff;
            ++pBuffLCD;
        }
        else //unicode
        {
            if (*pBuff == 0xD0)
            {
                ++pBuff;
                if (*pBuff == 0x90) *pBuffLCD = 0x41;//А
                else if (*pBuff == 0x01) *pBuffLCD = 0xA2;//Ё
                else if (*pBuff == 0x91) *pBuffLCD = 0xA0;//Б
                else if (*pBuff == 0x92) *pBuffLCD = 0xA0;//В
                else if (*pBuff == 0x93) *pBuffLCD = 0xA0;//Г
                else if (*pBuff == 0x94) *pBuffLCD = 0xE0;//Д
                else if (*pBuff == 0x95) *pBuffLCD = 0x45;//Е
                else if (*pBuff == 0x95) *pBuffLCD = 0xA3;//Ж


            }
            else if (*pBuff == 0xD1)
            {
                ++pBuff;
                if (*pBuff == 0x80) *pBuffLCD = 0x70;//р
                else if (*pBuff == 0x91) *pBuffLCD = 0xBF;//ё
                else if (*pBuff == 0x81) *pBuffLCD = 0x63;//с
                else if (*pBuff == 0x82) *pBuffLCD = 0xBF;//т
                else if (*pBuff == 0x83) *pBuffLCD = 0x79;//у


            }
            else //другой символ
            {
                ++pBuff;
                *pBuffLCD = 0x20;
            }

            ++pBuff;
            ++pBuffLCD;
        }
    }

//    memcpy ((uint8_t *)BufferLCD, (uint8_t *) Buffer, 83);
}


