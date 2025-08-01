#include "main.h"
extern I2C_HandleTypeDef hi2c2;
typedef struct _reg_8
{
    uint8_t value;
    uint32_t CRC_calc;
    union
    {
        uint32_t CRC_read;
        uint8_t CRC_[4];
    }readCRC;
}reg_8;

typedef struct _reg_16
{
    union
    {
        uint16_t value;
        uint8_t val[2];
    }value;

    uint32_t CRC_calc;
    union
    {
        uint32_t CRC_read;
        uint8_t CRC_[4];
    }readCRC;
}reg_16;

typedef struct _reg_32
{
    union
    {
        uint32_t value;
        uint8_t val[4];
    }value;

    uint32_t CRC_calc;
    union
    {
        uint32_t CRC_read;
        uint8_t CRC_[4];
    }readCRC;
}reg_32;

reg_8 reg8;
reg_16 reg16;
reg_32 reg32;   //42790

void init_42790()
{
    printf("\r\n------ init_42790 ------\r\n\n");
//    disable_42790_REGS_CRC();
//    enable_42790_REGS_CRC();
//    read_42790_REGS();

//    test_write_42790();

//    print_MP42790_8_CRC(0x1001);
//    print_MP42790_16_CRC(0x1207);
//    print_MP42790_32_CRC(0x005A);
}
void disable_42790_REGS_CRC()
{
    printf("\r\n----- Disable CRC ------\r\n");
    write_MP42790_8_CRC(0x4100,0x08);
    HAL_Delay(50);
    read_MP42790_8_CRC(0x4100);
    while(reg8.value != 0x08)
    {
        HAL_Delay(50);
        write_MP42790_8_CRC(0x4100,0x08);
        HAL_Delay(50);
        read_MP42790_8_CRC(0x4100);
    }
    printf("\r\n");
}
void enable_42790_REGS_CRC()
{
    printf("\r\n----- Enable CRC ------\r\n");
    write_MP42790_8_CRC(0x4100, 0x88);
    HAL_Delay(50);
    read_MP42790_8_CRC(0x4100);
    while(reg8.value != 0x88)
    {
        HAL_Delay(50);
        write_MP42790_8_CRC(0x4100,0x88);
        HAL_Delay(50);
        read_MP42790_8_CRC(0x4100);
    }
    printf("\r\n");
}
void read_42790_REGS()
{
    for (int i=0; i < 0x78; i+=2)
    {
        print_MP42790_16_CRC(i);
    }
    for (int i=0x200; i <= 0x023C; i+=4)
    {
        print_MP42790_32_CRC(i);
    }
    for (int i=0x280; i <= 0x02C0; i+=0xF)
    {
        print_MP42790_16_CRC(i);
    }
    for (int i=0x0564; i <= 0x058C; i+=1)
    {
        print_MP42790_8_CRC(i);
    }

    print_MP42790_16_CRC(0x058D);
    print_MP42790_16_CRC(0x0590);
    print_MP42790_16_CRC(0x0593);
    print_MP42790_16_CRC(0x0597);
    print_MP42790_16_CRC(0x059B);
    print_MP42790_16_CRC(0x059F);
    print_MP42790_16_CRC(0x05A3);
    print_MP42790_16_CRC(0x05A5);

    for (int i=0x05A8; i <= 0x05B7; i+=1)
    {
        print_MP42790_8_CRC(i);
    }
    for (int i=0x608; i <= 0x0648; i+=4)
    {
        print_MP42790_32_CRC(i);
    }
    for (int i=0x0C00; i <= 0x0C3E; i+=2)
    {
        print_MP42790_16_CRC(i);
    }
    for (int i=0x0C62; i <= 0x0C6A; i+=1)
    {
        print_MP42790_8_CRC(i);
    }
    print_MP42790_8_CRC(0x0C89);
    print_MP42790_8_CRC(0x1000);
    print_MP42790_8_CRC(0x1001);
    print_MP42790_8_CRC(0x1100);
    for (int i=0x1200; i <= 0x1206; i+=1)
    {
        print_MP42790_8_CRC(i);
    }
    for (int i=0x1207; i <= 0x122D; i+=2)
    {
        print_MP42790_16_CRC(i);
    }
    print_MP42790_8_CRC(0x122F);
    print_MP42790_16_CRC(0x1230);
    print_MP42790_8_CRC(0x1232);
    print_MP42790_16_CRC(0x1233);
    print_MP42790_8_CRC(0x1235);
    print_MP42790_16_CRC(0x1236);
//    print_MP42790_8_CRC(0x1238);
    print_MP42790_16_CRC(0x1239);
//    print_MP42790_8_CRC(0x123B);
    print_MP42790_16_CRC(0x123C);
    print_MP42790_8_CRC(0x123E);
    print_MP42790_16_CRC(0x1400);
    print_MP42790_16_CRC(0x1402);
    print_MP42790_8_CRC(0x1406);
    print_MP42790_16_CRC(0x1500);
    print_MP42790_16_CRC(0x1502);
    print_MP42790_16_CRC(0x1504);
    print_MP42790_8_CRC(0x1506);
    print_MP42790_8_CRC(0x150A);
    for (int i=0x1600; i <= 0x1605; i+=1)
    {
        print_MP42790_8_CRC(i);
    }
    for (int i=0x1700; i <= 0x1704; i+=1)
    {
        print_MP42790_8_CRC(i);
    }
    for (int i=0x1800; i <= 0x1806; i+=1)
    {
        print_MP42790_8_CRC(i);
    }
    print_MP42790_8_CRC(0x4000);
    print_MP42790_8_CRC(0x4100);
}
void pulse_SDA()
{
    HAL_I2C_DeInit(&hi2c2);
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);

    /*Configure GPIO pins : GPIO2_IN_Pin GPIO1_IN_Pin */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
    delayUS_ASM(600); //5ms
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12);
    MX_I2C2_Init();
}
void send_Address_Len_8(uint16_t regAddr)
{
    union
    {
        uint32_t regAddressLentch;
        uint8_t tmp[4];
    }dataWrite;
    uint8_t toWrite[3];
    dataWrite.regAddressLentch = 0;
    dataWrite.regAddressLentch |= regAddr<<16;
    dataWrite.regAddressLentch |= 0x00000100;
    toWrite[0] = dataWrite.tmp[2];
    toWrite[1] = dataWrite.tmp[3];
    toWrite[2] = dataWrite.tmp[1];
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Transmit(&hi2c2, MP42790_I2C_ADDRESS, toWrite, 3, HAL_MAX_DELAY);
}
void send_Address_Len_16(uint16_t regAddr)
{
    union
    {
        uint32_t regAddressLentch;
        uint8_t tmp[4];
    }dataWrite;
    uint8_t toWrite[3];
    dataWrite.regAddressLentch = 0;
    dataWrite.regAddressLentch |= regAddr<<16;
    dataWrite.regAddressLentch |= 0x00000200;
    toWrite[0] = dataWrite.tmp[2];
    toWrite[1] = dataWrite.tmp[3];
    toWrite[2] = dataWrite.tmp[1];
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Transmit(&hi2c2, MP42790_I2C_ADDRESS, toWrite, 3, HAL_MAX_DELAY);
}
void send_Address_Len_32(uint16_t regAddr)
{
    union
    {
        uint32_t regAddressLentch;
        uint8_t tmp[4];
    }dataWrite;
    uint8_t toWrite[3];
    dataWrite.regAddressLentch = 0;
    dataWrite.regAddressLentch |= regAddr<<16;
    dataWrite.regAddressLentch |= 0x00000400;
    toWrite[0] = dataWrite.tmp[2];
    toWrite[1] = dataWrite.tmp[3];
    toWrite[2] = dataWrite.tmp[1];
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Transmit(&hi2c2, MP42790_I2C_ADDRESS, toWrite, 3, HAL_MAX_DELAY);
}
uint8_t toRead8CRC[5];
uint32_t sum;
union
{
    uint32_t readCRC;
    uint8_t crc[4];
}data;
void receive_Data_8_CRC(uint16_t regAddr, int8_t * pCRC_OK)
{
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Receive(&hi2c2, MP42790_I2C_ADDRESS, toRead8CRC, 5, HAL_MAX_DELAY);
    sum = crc32(regAddr, 1, toRead8CRC);
    reg8.value = toRead8CRC[0];
    reg8.CRC_calc = sum;
    reg8.readCRC.CRC_[3] = toRead8CRC[4];
    reg8.readCRC.CRC_[2] = toRead8CRC[3];
    reg8.readCRC.CRC_[1] = toRead8CRC[2];
    reg8.readCRC.CRC_[0] = toRead8CRC[1];
    data.readCRC = sum;
    if((data.crc[0] == toRead8CRC[1]) && (data.crc[1] == toRead8CRC[2]) && (data.crc[2] == toRead8CRC[3]) && (data.crc[3] == toRead8CRC[4]) )
    {
//        printf("----- CRC  OK !!!! ----\r\n");
        *pCRC_OK = 0;
    }
    else
    {
        printf("----- CRC  ERROR !!!! ----\r\n");
        *pCRC_OK = -1;
    }
}
void receive_Data_16_CRC(uint16_t regAddr)
{
    uint8_t toRead16CRC[6];
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Receive(&hi2c2, MP42790_I2C_ADDRESS, toRead16CRC, 6, HAL_MAX_DELAY);
    uint32_t sum = crc32(regAddr, 2, toRead16CRC);
    reg16.value.val[0] = toRead16CRC[0];
    reg16.value.val[1] = toRead16CRC[1];
    reg16.CRC_calc = sum;
    reg16.readCRC.CRC_[3] = toRead16CRC[5];
    reg16.readCRC.CRC_[2] = toRead16CRC[4];
    reg16.readCRC.CRC_[1] = toRead16CRC[3];
    reg16.readCRC.CRC_[0] = toRead16CRC[2];
}
void receive_Data_32_CRC(uint16_t regAddr)
{
    uint8_t toRead32CRC[8];
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Receive(&hi2c2, MP42790_I2C_ADDRESS, toRead32CRC, 8, HAL_MAX_DELAY);
    uint32_t sum = crc32(regAddr, 4, toRead32CRC);
    reg32.value.val[0] = toRead32CRC[0];
    reg32.value.val[1] = toRead32CRC[1];
    reg32.value.val[2] = toRead32CRC[2];
    reg32.value.val[3] = toRead32CRC[3];
    reg32.CRC_calc = sum;
    reg32.readCRC.CRC_[3] = toRead32CRC[7];
    reg32.readCRC.CRC_[2] = toRead32CRC[6];
    reg32.readCRC.CRC_[1] = toRead32CRC[5];
    reg32.readCRC.CRC_[0] = toRead32CRC[4];
}
uint8_t read_MP42790_8_CRC(uint16_t regAddr)
{
    HAL_Delay(10);
    pulse_SDA();
    send_Address_Len_8(regAddr);
    int8_t CRC_OK = -1;
    int8_t * pCRC_OK = &CRC_OK;
    receive_Data_8_CRC(regAddr, pCRC_OK);
    if(CRC_OK != 0)
    {
        reg8.value = 0xFF;
    }
    return reg8.value;
}
void print_MP42790_8_CRC(uint16_t regAddr)
{
    read_MP42790_8_CRC(regAddr);
    printf("MP42790 reg %04X   0x%02X\t\t", regAddr, reg8.value);
    print_byte(reg8.value);
    printf("\t\t\t\tCRC - %08lX \tcalcCRC - %08lX", (unsigned long)reg8.readCRC.CRC_read, (unsigned long)reg8.CRC_calc);
    printf("\r\n");
}
void write_MP42790_8_CRC(uint16_t regAddr, uint8_t value)
{
    uint8_t toWrite[8];
    HAL_Delay(10);
    pulse_SDA();
    union
    {
        uint32_t toSend1;
        uint8_t tmp1[4];
    }dataWrite1;
    union
    {
        uint32_t toSend2;
        uint8_t tmp2[4];
    }dataWrite2;

    dataWrite1.toSend1 = 0;
    dataWrite1.toSend1 |= regAddr<<16;
    dataWrite1.toSend1 |= 0x00000100;
    dataWrite1.toSend1 |= value;

    dataWrite2.toSend2 = crc32(regAddr, 1, &value);

    toWrite[0] = dataWrite1.tmp1[2];  //младший адреса
    toWrite[1] = dataWrite1.tmp1[3];  //старший адреса
    toWrite[2] = dataWrite1.tmp1[1];  //длина - 1
    toWrite[3] = dataWrite1.tmp1[0];  //value
    toWrite[4] = dataWrite2.tmp2[0];  //младший CRC
    toWrite[5] = dataWrite2.tmp2[1];
    toWrite[6] = dataWrite2.tmp2[2];
    toWrite[7] = dataWrite2.tmp2[3];  //старший CRC

//    printf("toSend - %02X%02X%02X%02X%02X%02X%02X%02X \r\n", toWrite[0], toWrite[1], toWrite[2], toWrite[3], toWrite[4], toWrite[5],  toWrite[6], toWrite[7]);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Transmit(&hi2c2, MP42790_I2C_ADDRESS, toWrite, 8, HAL_MAX_DELAY);
}
uint16_t read_MP42790_16_CRC(uint16_t regAddr)
{
    HAL_Delay(10);
    pulse_SDA();
    send_Address_Len_16(regAddr);
    receive_Data_16_CRC(regAddr);
    return reg16.value.value;
}
void print_MP42790_16_CRC(uint16_t regAddr)
{
    read_MP42790_16_CRC(regAddr);
    printf("MP42790 reg %04X   0x%04X\t", regAddr, reg16.value.value);
    print_byte(reg16.value.val[1]);
    printf(" ");
    print_byte(reg16.value.val[0]);
    printf("\t\t\tCRC - %08lX \tcalcCRC - %08lX", (unsigned long)reg16.readCRC.CRC_read, (unsigned long)reg16.CRC_calc);
    printf("\r\n");
}
void write_MP42790_16_CRC(uint16_t regAddr, uint16_t value)
{
    uint8_t toWrite[9] = {0};
    HAL_Delay(10);
    pulse_SDA();
    union
    {
        uint32_t sendCRC;
        uint8_t crc[4];
    }crc;
    crc.sendCRC = crc32(regAddr, 2, (uint8_t *)&value);
    toWrite[0] = regAddr;       //младший байт адреса
    toWrite[1] = regAddr>>8;    //старший байт адреса
    toWrite[2] = 0x02;          //число байт
    toWrite[3] = value;         //младший байт данных
    toWrite[4] = value>>8;
    toWrite[5] = crc.crc[0];    //младший байтCRC
    toWrite[6] = crc.crc[1];
    toWrite[7] = crc.crc[2];
    toWrite[8] = crc.crc[3];    //старший байт CRC
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Transmit(&hi2c2, MP42790_I2C_ADDRESS, toWrite, 9, HAL_MAX_DELAY);
}
uint32_t read_MP42790_32_CRC(uint16_t regAddr)
{
    HAL_Delay(10);
    pulse_SDA();
    send_Address_Len_32(regAddr);
    receive_Data_32_CRC(regAddr);
    return reg32.value.value;
}
void print_MP42790_32_CRC(uint16_t regAddr)
{
    read_MP42790_32_CRC(regAddr);
    printf("MP42790 reg %04X   0x%08X\t", regAddr, reg32.value.value);
    print_byte(reg32.value.val[3]);
    printf(" ");
    print_byte(reg32.value.val[2]);
    printf(" ");
    print_byte(reg32.value.val[1]);
    printf(" ");
    print_byte(reg32.value.val[0]);
    printf("\tCRC - %08lX \tcalcCRC - %08lX", (unsigned long)reg32.readCRC.CRC_read, (unsigned long)reg32.CRC_calc);
    printf("\r\n");
}
void write_MP42790_32_CRC(uint16_t regAddr, uint32_t value)
{
    uint8_t toWrite[11] = {0};
    HAL_Delay(10);
    pulse_SDA();
    union
    {
        uint32_t sendCRC;
        uint8_t crc[4];
    }crc;
    crc.sendCRC = crc32(regAddr, 4, (uint8_t *)&value);
    toWrite[0] = regAddr;       //младший байт адреса
    toWrite[1] = regAddr>>8;    //старший байт адреса
    toWrite[2] = 0x04;          //число байт
    toWrite[3] = value;         //младший байт данных
    toWrite[4] = value>>8;
    toWrite[5] = value>>16;
    toWrite[6] = value>>24;
    toWrite[7] = crc.crc[0];    //младший байтCRC
    toWrite[8] = crc.crc[1];
    toWrite[9] = crc.crc[2];
    toWrite[10] = crc.crc[3];    //старший байт CRC
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Transmit(&hi2c2, MP42790_I2C_ADDRESS, toWrite, 11, HAL_MAX_DELAY);
}
void test_write_42790()
{
    CONFIG_MODE_CMD();
    printf("\r\n--- test write reg 8 ---\r\n");
    uint16_t reg8 = 0x1238;
    print_MP42790_8_CRC(reg8);
    uint8_t value8 = read_MP42790_8_CRC(reg8);
    ++value8;
    write_MP42790_8_CRC(reg8, value8);
    print_MP42790_8_CRC(reg8);

    printf("\r\n--- test write reg 16 ---\r\n");
    uint16_t reg16 = 0x1207;
    print_MP42790_16_CRC(reg16);
    uint8_t value16 = read_MP42790_16_CRC(reg16);
    ++value16;
    write_MP42790_16_CRC(reg16, value16);
    print_MP42790_16_CRC(reg16);

    printf("\r\n--- test write reg 32 ---\r\n");
    uint16_t reg32 = 0x005A;
    print_MP42790_32_CRC(reg32);
    uint8_t value32 = read_MP42790_32_CRC(reg32);
    ++value32;
    write_MP42790_32_CRC(reg32, value32);
    print_MP42790_32_CRC(reg32);
}
void RST_CMD()             //Reset the fuel gauge. This is a self-clearing function
{
    printf("\r\n----- RST_CMD -------\r\n");
    write_MP42790_8_CRC(0x7FFE, 0x01);
}
void EXE_CMD()             //Trigger a fuel gauge update refresh
{
    printf("\r\n----- EXE_CMD -------\r\n");
    write_MP42790_8_CRC(0x7FFE, 0x01);
}
void EDIT_CONFIG_CMD()     //The fuel gauge settings can be edited
{
    printf("\r\n----- EDIT_CONFIG_CMD -------\r\n");
    write_MP42790_8_CRC(0x7FFD, 0x01);
}
void END_EDIT_CONFIG_CMD() //The fuel gauge settings cannot be edited
{
    printf("\r\n----- END_EDIT_CONFIG_CMD -------\r\n");
    write_MP42790_8_CRC(0x7FFC, 0x01);
}
void CONFIG_MODE_CMD()     //Enter configuration mode
{
    printf("\r\n----- CONFIG_MODE_CMD -------\r\n");
    write_MP42790_8_CRC(0x7FFB, 0x01);
}
void CONFIG_EXIT_CMD()     //The fuel gauge settings cannot be edited
{
    printf("\r\n----- CONFIG_EXIT_CMD -------\r\n");
    write_MP42790_8_CRC(0x7FFA, 0x01);
}
void CONFIG_RST_CMD()      //Enter configuration mode
{
    printf("\r\n----- CONFIG_RST_CMD -------\r\n");
    write_MP42790_8_CRC(0x7FF9, 0x01);
}
void LOG_RST_CMD()         //Exit configuration mode. The new configuration is stored in the NVM
{
    printf("\r\n----- LOG_RST_CMD -------\r\n");
    write_MP42790_8_CRC(0x7FF8, 0x01);
}
