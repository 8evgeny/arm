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
uint16_t U1,U2,U3,U4,I1,I2,I3,I4,V_PACK,V_TOP,NTC1,NTC2,NTC3,NTC4;
uint16_t Temperature;

void init_2790()
{
    printf("\r\n========== init_MP2790 ===========\r\n\n");
    getWDTStatus();
    resetErrors();
    getLockRegisters();
    initBatteryNum();
    initInterrupts();
    initPins();
    initFET_CFG();

    // printf("  FET_MODE\r\n");
    // read_MP2790(FET_MODE);
    // write_MP2790(FET_MODE, data16.value.value |= 0b0000000000000000);
    // write_MP2790(FET_MODE, data16.value.value &= 0b1111111111111101);
    // print_MP2790(FET_MODE);
    // printf("\r\n");

    printf("  DSGOC_LIM\r\n");
    read_MP2790(DSGOC_LIM);
    write_MP2790(DSGOC_LIM, data16.value.value |= 0b0001000000010000);
    print_MP2790(DSGOC_LIM);
    printf("\r\n");

    printf("  DSGSC_CFG\r\n");
    read_MP2790(DSGSC_CFG);
    write_MP2790(DSGSC_CFG, data16.value.value |= 0b0100000000000000);
    print_MP2790(DSGSC_CFG);
    printf("\r\n");

    printf("  OC_STATUS\r\n");
    print_MP2790(OC_STATUS);
    printf("\r\n");

    init_NTC();
    get_V_PACK_TOP();
    // init_UV_OV();   //Тут перестает ключ включаться
    init_time_SC_detection();
    init_CHG_DSG_MOSFET();

    getStatus();
    get_V_PACK_TOP();
    HAL_Delay(1);
    printf("------------- after 1ms ------------ \r\n");
    getStatus();
    get_V_PACK_TOP();

    // HAL_Delay(50);
    // printf("------------- after 50ms ------------ \r\n");
    // getStatus();
    // get_V_PACK_TOP();
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
    data16.value.value = 0xFFFF;
    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_SET);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_Delay(5);
    HAL_I2C_Mem_Read(&hi2c2, MP2790_I2C_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, data16.value.val, 2, HAL_MAX_DELAY);

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
    HAL_Delay(5);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Write(&hi2c2, MP2790_I2C_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&regValue, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_RESET);
}

void read_Temp()
{
    //T = Reading x 0.01481 - 269.12 (°C)
    adcOn();
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
    adcOn();
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

void adcOn()
{
    write_MP2790(ADC_CTRL, 0x0001);
    while((read_MP2790(ADC_CTRL) & 0x0002) != 0x0002);
}

void get_V_PACK_TOP()
{
    adcOn();
//    printf("  get RD_VPACKP\r\n");
//    print_MP2790(RD_VPACKP);
    V_PACK = read_MP2790(V_PACK) * 80000 / 32768;
    printf("  V_PACK=%d,%03dV\r\n",V_PACK/1000, V_PACK%1000);
//    printf("  get RD_VTOP\r\n");
//    print_MP2790(RD_VTOP);
    V_TOP = read_MP2790(RD_VTOP) * 80000 / 32768;
    printf("  V_TOP=%d,%03dV\r\n",V_TOP/1000, V_TOP%1000);
    printf("\r\n");
}

void initInterrupts()
{
    printf("  initInterrupts()\r\n");
    read_MP2790(INT0_EN);
    write_MP2790(INT0_EN, data16.value.value |= 0x48FF);   // 19h 14 11 0-7 bits to 1
    print_MP2790(INT0_EN);
    read_MP2790(INT1_EN);
    write_MP2790(INT1_EN, data16.value.value |= 0x3FFE);   // 1Ah 1-13 bits to 1
    print_MP2790(INT1_EN);
    read_MP2790(INT_TYPE0);
    write_MP2790(INT_TYPE0, data16.value.value |= 0x00FF);
    print_MP2790(INT_TYPE0);
    read_MP2790(INT_TYPE1);
    write_MP2790(INT_TYPE1, data16.value.value |= 0x3F00);
    print_MP2790(INT_TYPE1);
    read_MP2790(INT_TYPE2);
    write_MP2790(INT_TYPE2, data16.value.value |= 0x0CFF);
    print_MP2790(INT_TYPE2);
    printf("\r\n");
}

void getLockRegisters()
{
    printf("  getLockRegisters()\r\n");
    for(uint8_t i = 0xAA; i <= 0xB0; ++i)
    {
        print_MP2790(i);
    }
    printf("\r\n");
}

void init_UV_OV()
{
    printf("  init_UV_OV()\r\n");
    read_MP2790(CELL_UV);
    write_MP2790(CELL_UV, 0x088F);
    print_MP2790(CELL_UV);

    read_MP2790(PACK_UV);
    write_MP2790(PACK_UV, 0x823E);
    print_MP2790(PACK_UV);

    read_MP2790(PACK_OV);
    write_MP2790(PACK_OV, 0x8361);
    print_MP2790(PACK_OV);
    printf("\r\n");
}

void initFET_CFG()
{
    printf("  initFET_CFG()\r\n");
    read_MP2790(FET_CFG);
    write_MP2790(FET_CFG, data16.value.value |= 0x0400);  // bit  13  to 1
    write_MP2790(FET_CFG, data16.value.value &= 0xAFFF);  // bit  12 14  to 0
    write_MP2790(FET_CFG, data16.value.value |= 0b0000000000000111);
    print_MP2790(FET_CFG);
    printf("\r\n");
}
void initBatteryNum()
{
    printf("  initBatteryNum()\r\n");
// Определяем состав батарейного блока (четыре батареи с третьей по шестую)
    write_MP2790(CELLS_CTRL, 0x0003);
    print_MP2790(CELLS_CTRL);
    printf("\r\n");
}

void init_time_SC_detection()
{
    printf("  init_time_SC_detection()\r\n");
    read_MP2790(FT1_CFG);
    write_MP2790(FT1_CFG, data16.value.value = 0b0000000000001110);
    print_MP2790(FT1_CFG);
    printf("\r\n");
}

void resetErrors()
{
    printf("  resetErrors()\r\n");
//    printf("reset FT_CLR\r\n");
    write_MP2790(FT_CLR, 0xFFFF);
//    printf("reset FT_REC\r\n");
    write_MP2790(FT_REC, 0xFFFF);
    printf("\r\n");
}

void initPins()
{
    printf("  initPins()\r\n");
    write_MP2790(PINS_CFG, data16.value.value &= 0b1111111110011111);   // 5 6 bits to 0
    print_MP2790(PINS_CFG);
    printf("\r\n");
}

void init_NTC()
{
    printf("  init_NTC()\r\n");
    read_MP2790(HR_SCAN0);
    write_MP2790(HR_SCAN0, data16.value.value |= 0b0000000001000000); // bits 6  to 1
    print_MP2790(HR_SCAN0);

    read_MP2790(HR_SCAN2);
    write_MP2790(HR_SCAN2, data16.value.value |= 0b0000000111100011); // bits 0 1 5-8  to 1
    print_MP2790(HR_SCAN2);

    read_MP2790(NTC_CFG);
    write_MP2790(NTC_CFG, data16.value.value |= 0b0000000000000001);
    write_MP2790(NTC_CFG, data16.value.value &= 0b1111111101010101);  // bits  7  5  3  1  to 0
    print_MP2790(NTC_CFG);

//Читаю термисторы
    adcOn();
//    Value = Reading x 100 / 32768 (%NTCB)
    print_MP2790(RD_VNTC1);
//    NTC1 = read_MP2790(RD_VNTC1) * 100000 / 32768;
//    printf("NTC1=%d,%03dV\r\n",NTC1/1000, NTC1%1000);
    print_MP2790(RD_VNTC2);
    print_MP2790(RD_VNTC3);
    print_MP2790(RD_VNTC4);
    printf("\r\n");
}

void getStatus()
{
    printf("  getStatus()\r\n");
    printf("  FT_STS\r\n");
    print_MP2790(FT_STS1);
    print_MP2790(FT_STS2);
    printf("  FET_STATUS\r\n");
    print_MP2790(FET_STATUS);
    printf("  PWR_STATUS\r\n");
    print_MP2790(PWR_STATUS);
    printf("\r\n");

}

void getWDTStatus()
{
    printf("  getWDTStatus()\r\n");
    print_MP2790(WDT_STATUS);
    printf("\r\n");
}

void init_CHG_DSG_MOSFET()
{
    printf("  init_CHG_DSG_MOSFET()\r\n");
    read_MP2790(ACT_CFG);
    write_MP2790(ACT_CFG, data16.value.value |= 0b00000001000011000);    //  3  4  9 bits to 1
    write_MP2790(ACT_CFG, data16.value.value &= 0b1111111111111101);     //  1 bit to 0
    print_MP2790(ACT_CFG);
    printf("\r\n");
}
