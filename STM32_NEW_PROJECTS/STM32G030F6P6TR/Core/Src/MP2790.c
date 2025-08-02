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
    print_MP2790(ACT_CFG);
    write_MP2790(ACT_CFG, data16.value.value |= 0x0018);  // bit  4  3  to 1
    print_MP2790(ACT_CFG);
    printf("\r\n");

    printf("get PWR_STATUS\r\n");
    print_MP2790(PWR_STATUS);
    printf("\r\n");

    printf("get FET_STATUS\r\n"); //Сосояние ключей
    print_MP2790(FET_STATUS);
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
    write_MP2790(ADC_CTRL, 0x0001);
    while((read_MP2790(ADC_CTRL) & 0x0002) != 0x0002);
    read_MP2790(RD_TDIE);
    Temperature = read_MP2790(RD_TDIE);
    printf("T=%04X\r\n",Temperature);
}

void read_U_I()
{
    write_MP2790(ADC_CTRL, 0x0001);
    while((read_MP2790(ADC_CTRL) & 0x0002) != 0x0002);
    U1 = read_MP2790(RD_VCELL3);//Voltage = Reading x 5000 / 32768 (mV)
    U2 = read_MP2790(RD_VCELL4);
    U3 = read_MP2790(RD_VCELL5);
    U4 = read_MP2790(RD_VCELL6);
    I1 = read_MP2790(RD_ICELL3);
    I2 = read_MP2790(RD_ICELL4);
    I3 = read_MP2790(RD_ICELL5);
    I4 = read_MP2790(RD_ICELL6);
    printf("U1=%04X I1=%04X\r\n",U1,I1);
    printf("U2=%04X I2=%04X\r\n",U2,I2);
    printf("U3=%04X I3=%04X\r\n",U3,I3);
    printf("U4=%04X I4=%04X\r\n",U4,I4);
    printf("\r\n");
}
