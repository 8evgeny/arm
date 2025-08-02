#include "main.h"
#include "i2c.h"
extern I2C_HandleTypeDef hi2c2;
typedef struct _data16
{
    union
    {
        uint16_t value;
        uint8_t val[2];
    }value;
}data_16;
data_16 data16; //2790
uint16_t U1,U2,U3,U4,I1,I2,I3,I4;
uint16_t Temperature;

void init_2790()
{
    printf("\r\n------ init_2790 ------\r\n\n");
//    read_2790_REGS();

    printf("get LOCK_REGISTER\r\n");
    print_MP2790(LOCK_REGISTER);
    printf("\r\n");

//Конфигурирование
    printf("set CELLS_CTRL\r\n");
    print_MP2790(CELLS_CTRL);
    write_MP2790(CELLS_CTRL, 0x0003); //Определяет состав батарейного блока (четыре батареи с третьей по шестую)
    print_MP2790(CELLS_CTRL);
    printf("\r\n");

    printf("set ACT_CFG\r\n");
    print_MP2790(ACT_CFG); //05h
    write_MP2790(ACT_CFG, data16.value.value |= 0x0200);    // O5h 9 bits to 1
    write_MP2790(ACT_CFG, data16.value.value &= 0xFFFD);    // O5h 1 bits to 0
    print_MP2790(ACT_CFG);
    printf("\r\n");

    printf("set PINS_CFG\r\n");
    print_MP2790(PINS_CFG); //0Dh
    write_MP2790(PINS_CFG, data16.value.value &= 0xFF9F);   // ODh 5 6 bits to 0
    print_MP2790(PINS_CFG);
    printf("\r\n");

//Инициализация
    printf("set INT0_EN\r\n");
    print_MP2790(INT0_EN); //19h
    write_MP2790(INT0_EN, data16.value.value |= 0x48FF);   // 19h 14 11 0-7 bits to 1
    print_MP2790(INT0_EN);
    printf("\r\n");

    printf("set INT1_EN\r\n");
    print_MP2790(INT1_EN); //1Ah
    write_MP2790(INT1_EN, data16.value.value |= 0x3FFE);   // 1Ah 1-13 bits to 1
    print_MP2790(INT1_EN);
    printf("\r\n");

    printf("set INT_TYPE0\r\n");
    print_MP2790(INT_TYPE0); //1Bh
    write_MP2790(INT_TYPE0, data16.value.value |= 0x00FF);
    print_MP2790(INT_TYPE0);
    printf("\r\n");

    printf("set INT_TYPE1\r\n");
    print_MP2790(INT_TYPE1); //1Ch
    write_MP2790(INT_TYPE1, data16.value.value |= 0x3F00);
    print_MP2790(INT_TYPE1);
    printf("\r\n");

    printf("set INT_TYPE2\r\n");
    print_MP2790(INT_TYPE2); //1Dh
    write_MP2790(INT_TYPE2, data16.value.value |= 0x0CFF);
    print_MP2790(INT_TYPE2);
    printf("\r\n");

    printf("set FET_CFG\r\n");
    print_MP2790(FET_CFG); //14h
    write_MP2790(FET_CFG, data16.value.value |= 0x0400);  // bit  13  to 1
    write_MP2790(FET_CFG, data16.value.value &= 0xAFFF);  // bit  12 14  to 0
    print_MP2790(FET_CFG);
    printf("\r\n");

    printf("set ACT_CFG\r\n");
    write_MP2790(ACT_CFG, data16.value.value &= 0xFFE7);  // bit  4  3  to 0
    print_MP2790(ACT_CFG);  //05h
    write_MP2790(ACT_CFG, data16.value.value |= 0x0018);  // bit  4  3  to 1
    print_MP2790(ACT_CFG);
    printf("\r\n");

//    printf("set FET_MODE\r\n");
//    print_MP2790(FET_MODE);  //13h
//    write_MP2790(FET_MODE, data16.value.value &= 0b1111111111110111);  // bit  3  to 0
//    print_MP2790(FET_MODE);
//    printf("\r\n");

    printf("set NTC_CFG\r\n");         //4 термистора
    print_MP2790(NTC_CFG); //47h
    write_MP2790(NTC_CFG, data16.value.value &= 0b1111101101010101);  // bit  1  3  5  7  10  to 0
    print_MP2790(NTC_CFG);
    printf("\r\n");

    //Читаю термисторы
    printf("get RD_V_NTC1_LR\r\n");
    print_MP2790(RD_V_NTC1_LR);   //42h
    printf("get RD_V_NTC2_LR\r\n");
    print_MP2790(RD_V_NTC2_LR);   //41h
    printf("get RD_V_NTC3_LR\r\n");
    print_MP2790(RD_V_NTC3_LR);   //40h
    printf("get RD_V_NTC4_LR\r\n");
    print_MP2790(RD_V_NTC4_LR);   //3Fh
    printf("\r\n");

    printf("get FET_STATUS\r\n"); //Сосояние ключей
    print_MP2790(FET_STATUS);   //11h
    printf("\r\n");

    printf("get PWR_STATUS\r\n");
    print_MP2790(PWR_STATUS);    //01h
    printf("\r\n");





//    write_MP2790(ACT_CFG, 0x0200);
//    print_MP2790(ACT_CFG);
//    print_MP2790(PWR_STATUS);
//    write_MP2790(ACT_CFG, 0x0218);
//    print_MP2790(ACT_CFG);
//    print_MP2790(PWR_STATUS);
}

void read_2790_REGS()
{
    for (int i=0; i <= 0xB9; ++i)
    {
        print_MP2790(i);
        HAL_Delay(1);
    }
}

uint16_t read_MP2790(uint8_t regAddr)
{
    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_SET);
//    HAL_Delay(1);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Read(&hi2c2, MP2790_I2C_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, data16.value.val, 2, HAL_MAX_DELAY);

write_MP2790(GPIO_STATUS, 0x0000); //Фейковая запись чтобы далее шло чтение

    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_RESET);
    return data16.value.value;
}

void print_MP2790(uint8_t regAddr)
{
    printf("MP2790  reg %02X     0x%04X\t", regAddr, read_MP2790(regAddr));
    print_byte(data16.value.val[1]);
    printf(" ");
    print_byte(data16.value.val[0]);
    printf("\r\n");
}

void write_MP2790(uint8_t regAddr, uint16_t regValue)
{
    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Write(&hi2c2, MP2790_I2C_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&regValue, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_RESET);
}

void read_Temp()
{
    //T = Reading x 0.01481 - 269.12 (°C)
    write_MP2790(ADC_CTRL, 0x0001);
    while((read_MP2790(ADC_CTRL) & 0x0002) != 0x0002);
    read_MP2790(RD_TDIE);
    Temperature = read_MP2790(RD_TDIE);
//    printf("T=%04X\r\n",Temperature);
    float t = Temperature * 0.01481f;
    t-=269.12f;
    t*=100;
    printf("T=%d,%02d°C\r\n",(int)t/100, (int)t%100);
}

void read_U_I()
{
    //Voltage = Reading x 5000 / 32768 (mV)
    //I = Reading x 100 / 32768 / RSENSE (A) RSENSE is the external current-sense resistor (in mΩ)
    write_MP2790(ADC_CTRL, 0x0001);
    while((read_MP2790(ADC_CTRL) & 0x0002) != 0x0002);
    U1 = read_MP2790(RD_VCELL3) * 5000 / 32768;
    U2 = read_MP2790(RD_VCELL4) * 5000 / 32768;
    U3 = read_MP2790(RD_VCELL5) * 5000 / 32768;
    U4 = read_MP2790(RD_VCELL6) * 5000 / 32768;

    I1 = (read_MP2790(RD_ICELL3) & 0x7FFF) * 20000000 / 32768 ; //in mkA
    I2 = (read_MP2790(RD_ICELL4) & 0x7FFF) * 20000000 / 32768;
    I3 = (read_MP2790(RD_ICELL5) & 0x7FFF) * 20000000 / 32768 ;
    I4 = (read_MP2790(RD_ICELL6) & 0x7FFF) * 20000000 / 32768 ;

    printf("U1=%d,%03dV I1=%d,%03dmA\r\n",U1/1000, U1%1000, I1/1000,I1%1000);
    printf("U2=%d,%03dV I2=%d,%03dmA\r\n",U2/1000, U2%1000, I2/1000,I2%1000);
    printf("U3=%d,%03dV I3=%d,%03dmA\r\n",U3/1000, U3%1000, I3/1000,I3%1000);
    printf("U4=%d,%03dV I4=%d,%03dmA\r\n",U4/1000, U4%1000, I4/1000,I4%1000);
    printf("\r\n");
}
