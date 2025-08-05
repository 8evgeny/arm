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

    printf("get LOCK_REGISTERS\r\n");
    for(uint8_t i = 0xAA; i <= 0xB0; ++i)
    {
        print_MP2790(i);
//        write_MP2790(i, 0x0000);
//        print_MP2790(i);
    }
    printf("\r\n");

    printf("-------- set CELLS_CTRL --------\r\n");
//    print_MP2790(CELLS_CTRL);
    printf("  Определяем состав батарейного блока (четыре батареи с третьей по шестую)\r\n");
    //Определяет состав батарейного блока (четыре батареи с третьей по шестую)
    write_MP2790(CELLS_CTRL, 0x0003);
    print_MP2790(CELLS_CTRL);
    printf("\r\n");

    printf("-------- set CELL_UV --------\r\n");
    printf("  CELL_UV command configures the cell under-voltage (UV) threshold and deglitch delay\r\n");
    print_MP2790(CELL_UV);
    write_MP2790(CELL_UV, 0x088F);
    print_MP2790(CELL_UV);
    printf("\r\n");

    printf("-------- set PACK_UV --------\r\n");
    printf("  PACK_UV command configures the VTOP under-voltage (UV) threshold and deglitch delay\r\n");
    print_MP2790(PACK_UV);
    write_MP2790(PACK_UV, 0x823E);
    print_MP2790(PACK_UV);
    printf("\r\n");

    printf("-------- set PACK_OV --------\r\n");
    printf("  PACK_OV command configures the VTOP over-voltage (OV) threshold and deglitch delay\r\n");
    print_MP2790(PACK_OV);
    write_MP2790(PACK_OV, 0x8361);
    print_MP2790(PACK_OV);
    printf("\r\n");

    printf("-------- set ACT_CFG --------\r\n");
    printf("  ACT_CFG command configures the MOSFET transition method, turn-on/off command, control logic, and control method\r\n");
//    printf("  1 bits to 0 - set GPIO depending on FET_CFG\r\n");
    printf("  9 bits to 1 - MOSFETs start up depending on the control source status\r\n");
    printf("  bits 0 1 3 4 to 1 CHG and DSG MOSFETs turn on\r\n");
    print_MP2790(ACT_CFG); //05h
    write_MP2790(ACT_CFG, data16.value.value |= 0x0200);    // 9 bits to 1
//    write_MP2790(ACT_CFG, data16.value.value &= 0xFFFD);    // 1 bits to 0
    //Пробуем управление ключами через GPIO
    write_MP2790(ACT_CFG, data16.value.value |= 0b0000000000011011);  // bits 0 1 3 4 to 1 CHG and DSG MOSFETs turn on
    print_MP2790(ACT_CFG);
    printf("\r\n");

    printf("-------- set FET_CFG --------\r\n");
    printf("  FET_CFG configures the driver voltages of CHG and DSG MOSFETs, and it configures soft start for the CHG and DSG MOSFETs\r\n");
    printf("  12 14 bits to 0 13 bit to 1 set 7V with a lower CP voltage\r\n");
    print_MP2790(FET_CFG);
    write_MP2790(FET_CFG, data16.value.value |= 0x0400);  // bit  13  to 1
    write_MP2790(FET_CFG, data16.value.value &= 0xAFFF);  // bit  12 14  to 0
    print_MP2790(FET_CFG);
    printf("\r\n");

    printf("-------- set PINS_CFG --------\r\n");
    printf("  PINS_CFG command defines the direction of GPIOHV1, and the pull-up voltage of GPIO1~3. It also sets the behavior of the WDT pins and xALERT pin\r\n");
    printf("  5 6 bits to 0  disable WDT\r\n");
    print_MP2790(PINS_CFG);
    write_MP2790(PINS_CFG, data16.value.value &= 0xFF9F);   // 5 6 bits to 0
    print_MP2790(PINS_CFG);
    printf("\r\n");

    printf("reset FT_CLR\r\n");
    write_MP2790(FT_CLR, 0xFFFF);
    printf("reset FT_REC\r\n");
    write_MP2790(FT_REC, 0xFFFF);
    printf("\r\n");

    printf("-------- set OCFT_CTRL --------\r\n");
    printf("  OCFT_CTRL command controls the triggering logic for the interrupt of charge over-current (OC), discharge OC1, and discharge OC2 events. ");
    printf("  It also enables the interrupts, faults, and monitoring for charge OC, discharge OC1, discharge OC2 events\r\n");
    printf("  Выключаем прерывания\r\n");
    print_MP2790(OCFT_CTRL);
    write_MP2790(OCFT_CTRL, data16.value.value = 0x0000);
    print_MP2790(OCFT_CTRL);
    printf("\r\n");

    printf("-------- set SCFT_CTRL --------\r\n");
    printf("  SCFT_CTRL command enables the fault protection, interrupt, and monitoring of charge short-circuit (SC) and discharge SC events\r\n");
    printf("  Выключаем прерывания и мониторинг\r\n");
    print_MP2790(SCFT_CTRL);
    write_MP2790(SCFT_CTRL, data16.value.value = 0x0000);
    print_MP2790(SCFT_CTRL);
    printf("\r\n");

    printf("-------- set INT0_EN --------\r\n");
    print_MP2790(INT0_EN);
    write_MP2790(INT0_EN, data16.value.value |= 0x48FF);   // 14 11 0-7 bits to 1
    print_MP2790(INT0_EN);
    printf("\r\n");

    printf("-------- set INT1_EN --------\r\n");
    print_MP2790(INT1_EN);
    write_MP2790(INT1_EN, data16.value.value |= 0x3FFE);   // 1Ah 1-13 bits to 1
    print_MP2790(INT1_EN);
    printf("\r\n");

    printf("-------- set INT_TYPE0 --------\r\n");
    print_MP2790(INT_TYPE0);
    write_MP2790(INT_TYPE0, data16.value.value |= 0x00FF);
    print_MP2790(INT_TYPE0);
    printf("\r\n");

    printf("-------- set INT_TYPE1 --------\r\n");
    print_MP2790(INT_TYPE1);
    write_MP2790(INT_TYPE1, data16.value.value |= 0x3F00);
    print_MP2790(INT_TYPE1);
    printf("\r\n");

    printf("-------- set INT_TYPE2 --------\r\n");
    print_MP2790(INT_TYPE2);
    write_MP2790(INT_TYPE2, data16.value.value |= 0x0CFF);
    print_MP2790(INT_TYPE2);
    printf("\r\n");

    printf("-------- set HR_SCAN0 --------\r\n");
    printf("  HR_SCAN0 command enables ADC cell measurement compensation for voltage drop caused by the cell’s input resistor. \r\n");
    printf("  It also enables voltage and currentADC scanning for the synchronous TOP current,synchronous cell current, LDOs, \r\n");
    printf("  die temperature, NTCs, GPIO, PACKP, TOP voltage, and cell voltage \r\n");
    print_MP2790(HR_SCAN0);
    write_MP2790(HR_SCAN0, data16.value.value |= 0b0000000001000000); // bits 6  to 1
    print_MP2790(HR_SCAN0);
    printf("\r\n");

    printf("-------- set HR_SCAN2 --------\r\n");
    printf("  HR_SCAN2 command enables the ADC voltage scans for NTC1~4 and the high-resolution voltage scans for GPIO1~3\r\n");
    print_MP2790(HR_SCAN2); //9Eh
    write_MP2790(HR_SCAN2, data16.value.value |= 0b0000000111100011); // bits 0 1 5-8  to 1
    print_MP2790(HR_SCAN2);
    printf("\r\n");

    printf("-------- set GPIO_CFG --------\r\n");
    print_MP2790(GPIO_CFG);
    write_MP2790(GPIO_CFG, data16.value.value |= 0b0000000000010001); // bits 0 4  to 1
    print_MP2790(GPIO_CFG);
    printf("\r\n");

    printf("-------- get FT_STS1 --------\r\n");
    print_MP2790(FT_STS1);
    printf("-------- get FT_STS2 --------\r\n");
    print_MP2790(FT_STS2);
    printf("\r\n");

    printf("-------- set FET_MODE --------\r\n");
    printf("  FET_MODE configures soft start for the CHG and DSG MOSFETs, and it enables manual control of the SBYDSG MOSFET\r\n");
    print_MP2790(FET_MODE);
    write_MP2790(FET_MODE, data16.value.value &= 0b1111111111110101);
    write_MP2790(FET_MODE, data16.value.value |= 0b0000000011100000);
    print_MP2790(FET_MODE);
    printf("\r\n");

    printf("-------- set NTC_CFG --------\r\n");         //4 термистора
    print_MP2790(NTC_CFG); //47h
    write_MP2790(NTC_CFG, data16.value.value |= 0b0000000000000001);
    write_MP2790(NTC_CFG, data16.value.value &= 0b1111111101010101);  // bits  7  5  3  1  to 0
    print_MP2790(NTC_CFG);
    printf("\r\n");

    //Читаю термисторы
    printf("-------- get RD_VNTC1 --------\r\n");
    print_MP2790(RD_VNTC1);
    printf("-------- get RD_VNTC2 --------\r\n");
    print_MP2790(RD_VNTC2);
    printf("-------- get RD_VNTC3 --------\r\n");
    print_MP2790(RD_VNTC3);
    printf("-------- get RD_VNTC4 --------\r\n");
    print_MP2790(RD_VNTC4);
    printf("\r\n");

    printf("-------- get GPIO_STATUS --------\r\n");
    print_MP2790(GPIO_STATUS);
    HAL_GPIO_WritePin(GPIOB, GPIO_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_2_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    printf("-------- get GPIO_STATUS --------\r\n");
    print_MP2790(GPIO_STATUS);
    printf("------------------------------------------------- \r\n");

    printf("-------- get FET_STATUS --------\r\n"); //Сосояние ключей
    print_MP2790(FET_STATUS);   //11h
    printf("\r\n");
    printf("-------- get FT_STS2 --------\r\n");
    print_MP2790(FT_STS2);
    printf("get FT_STS1 --------\r\n");
    print_MP2790(FT_STS1);
    printf("\r\n");
    printf("-------- get PWR_STATUS --------\r\n");
    print_MP2790(PWR_STATUS);    //01h

    printf("--------------------- STATUS --------------------\r\n");
    printf("-------- get WDT_STATUS --------\r\n");
    print_MP2790(WDT_STATUS);
    printf("-------- get WDT_CFG --------\r\n");
    print_MP2790(WDT_CFG);
    printf("\r\n");
    printf("-------- get RD_VA1P8 --------\r\n");
    print_MP2790(RD_VA1P8);
    printf("-------- get RD_VA3P3 --------\r\n");
    print_MP2790(RD_VA3P3);
    printf("------------------------------------------------- \r\n");

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
    HAL_Delay(3);
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
    HAL_Delay(3);
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
