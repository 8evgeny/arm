#include "main.h"

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
const char *bit_rep[16] =
{
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};

typedef struct _data16
{
    union
    {
        uint16_t value;
        uint8_t val[2];
    }value;
}data_16;
data_16 data16; //2650

typedef struct _data8
{
    uint8_t value;
}data_8;

data_16 data16;
data_8 data8;

void all_led_OFF()
{
    GPIO_OFF(Blue_LED_Pin);
    GPIO_OFF(Red_LED_Pin);
    GPIO_OFF(Green_LED_Pin);
    GPIO_OFF(Yellow_LED_Pin);
}
int _write(int fd, char *str, int len)
{
    HAL_GPIO_WritePin(USART2_CS_GPIO_Port, USART2_CS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(USART3_CS_GPIO_Port, USART3_CS_Pin, GPIO_PIN_SET);
    for(int i=0; i<len; ++i)
    {
        HAL_UART_Transmit(&huart2, (uint8_t *)&str[i], 1, 0xFFFF);
        HAL_UART_Transmit(&huart3, (uint8_t *)&str[i], 1, 0xFFFF);
        SEGGER_RTT_PutChar(0, str[i]);
//        delayUS_ASM(30);
    }
    HAL_GPIO_WritePin(USART2_CS_GPIO_Port, USART2_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(USART3_CS_GPIO_Port, USART3_CS_Pin, GPIO_PIN_RESET);
    return len;
}

void test_EEPROM(uint16_t addr, const char * data)
{
    // Пишет по 8 байт в адреса кратные 8 Читать может больше
    uint16_t num = 8;
    printf("test I2C_EEPROM ...\r\n");
    uint8_t rd_value[20] = {0};
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Read(&hi2c2, EEPROM_I2C_ADDRESS, addr, I2C_MEMADD_SIZE_8BIT, rd_value, num, HAL_MAX_DELAY);
    printf("EEPROM read: %s\r\n",rd_value);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Write(&hi2c2, EEPROM_I2C_ADDRESS, addr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)data, num, HAL_MAX_DELAY);
    printf("EEPROM write: %s\r\n", data);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Read(&hi2c2, EEPROM_I2C_ADDRESS, addr, I2C_MEMADD_SIZE_8BIT, rd_value, num, HAL_MAX_DELAY);
    printf("EEPROM read: %s\r\n",rd_value);
}

void led_Test()
{
    GPIO_ON(Blue_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Blue_LED_Pin);
    HAL_Delay(30);
    GPIO_ON(Red_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Red_LED_Pin);
    HAL_Delay(30);
    GPIO_ON(Green_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Green_LED_Pin);
    HAL_Delay(30);
    GPIO_ON(Yellow_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Yellow_LED_Pin);

    HAL_Delay(500);

    GPIO_ON(Yellow_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Yellow_LED_Pin);
    GPIO_ON(Green_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Green_LED_Pin);
    HAL_Delay(30);
    GPIO_ON(Red_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Red_LED_Pin);
    HAL_Delay(30);
    GPIO_ON(Blue_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Blue_LED_Pin);

    HAL_Delay(500);
}

uint16_t read_MP2650_16(uint8_t regAddr)
{
    data16.value.value = 0xFFFF;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
    HAL_StatusTypeDef ret;
    ret = HAL_I2C_Mem_Read(&hi2c1, MP2650_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, data16.value.val, 2, HAL_MAX_DELAY);
    if(HAL_OK == ret)
    {
        return data16.value.value;
    }
    else
    {
        printf("error code = %d\r\n", ret);
        return 0xFFFF;
    }
}

void write_MP2650_16(uint8_t regAddr, uint16_t regValue)
{
    HAL_Delay(3);
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Write(&hi2c1, MP2650_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&regValue, 2, HAL_MAX_DELAY);
}

void print_MP2650_16(uint8_t regAddr)
{
    data16.value.value = read_MP2650_16(regAddr);
    printf("MP2650_16 reg %02X     0x%04X\t", regAddr, data16.value.value);
    print_byte(data16.value.val[1]);
    printf(" ");
    print_byte(data16.value.val[0]);
    ext_print_16(regAddr);
    printf("\r\n");
}

void ext_print_16(uint8_t regAddr)
{
    if(regAddr == ADC_Battery_Voltage_Result_16BIT)
    {
        uint16_t V = 0;
        V += ((data16.value.value >>6) & 0x0001) * 250; //больше в 20 раз
        V += ((data16.value.value >>7) & 0x0001) * 500;
        V += ((data16.value.value >>8) & 0x0001) * 1000;
        V += ((data16.value.value >>9) & 0x0001) * 2000;
        V += ((data16.value.value >>10) & 0x0001) * 4000;
        V += ((data16.value.value >>11) & 0x0001) * 8000;
        V += ((data16.value.value >>12) & 0x0001) * 16000;
        V += ((data16.value.value >>13) & 0x0001) * 32000;
        V += ((data16.value.value >>14) & 0x0001) * 64000;
        V += ((data16.value.value >>15) & 0x0001) * 128000;
        printf("  ADC_Battery_Voltage             %d.%03d V", V/10000, V%10000);
    }
    if(regAddr == ADC_System_Voltage_Result_16BIT)
    {
        uint16_t V = 0;
        V += ((data16.value.value >>6) & 0x0001) * 250; //больше в 20 раз
        V += ((data16.value.value >>7) & 0x0001) * 500;
        V += ((data16.value.value >>8) & 0x0001) * 1000;
        V += ((data16.value.value >>9) & 0x0001) * 2000;
        V += ((data16.value.value >>10) & 0x0001) * 4000;
        V += ((data16.value.value >>11) & 0x0001) * 8000;
        V += ((data16.value.value >>12) & 0x0001) * 16000;
        V += ((data16.value.value >>13) & 0x0001) * 32000;
        V += ((data16.value.value >>14) & 0x0001) * 64000;
        V += ((data16.value.value >>15) & 0x0001) * 128000;
        printf("  ADC_System_Voltage              %d.%03d V", V/10000, V%10000);
    }
    if(regAddr == ADC_Battery_Charge_Current_Result_16BIT)
    {
        uint16_t I = 0;
        I += ((data16.value.value >>6) & 0x0001) * 125; //больше в 10 раз
        I += ((data16.value.value >>7) & 0x0001) * 250;
        I += ((data16.value.value >>8) & 0x0001) * 500;
        I += ((data16.value.value >>9) & 0x0001) * 1000;
        I += ((data16.value.value >>10) & 0x0001) * 2000;
        I += ((data16.value.value >>11) & 0x0001) * 4000;
        I += ((data16.value.value >>12) & 0x0001) * 8000;
        I += ((data16.value.value >>13) & 0x0001) * 16000;
        I += ((data16.value.value >>14) & 0x0001) * 32000;
        I += ((data16.value.value >>15) & 0x0001) * 64000;
        printf("  ADC_Battery_Charge_Current      %d.%03d mA", I/10, I%10);
    }
    if(regAddr == ADC_Input_Voltage_Result_16BIT)
    {
        uint16_t U = 0;
        U += ((data16.value.value >>6) & 0x0001) * 25; //mV
        U += ((data16.value.value >>7) & 0x0001) * 50;
        U += ((data16.value.value >>8) & 0x0001) * 100;
        U += ((data16.value.value >>9) & 0x0001) * 200;
        U += ((data16.value.value >>10) & 0x0001) * 400;
        U += ((data16.value.value >>11) & 0x0001) * 800;
        U += ((data16.value.value >>12) & 0x0001) * 1600;
        U += ((data16.value.value >>13) & 0x0001) * 3200;
        U += ((data16.value.value >>14) & 0x0001) * 6400;
        U += ((data16.value.value >>15) & 0x0001) * 12800;
        printf("  ADC_Input_Voltage               %d.%03d V",U/1000,U%1000);
    }
    if(regAddr == ADC_Input_Current_Result_16BIT)
    {
        uint16_t I = 0;
        I += ((data16.value.value >>6) & 0x0001) * 13; //В 2 раза больше
        I += ((data16.value.value >>7) & 0x0001) * 25;
        I += ((data16.value.value >>8) & 0x0001) * 50;
        I += ((data16.value.value >>9) & 0x0001) * 100;
        I += ((data16.value.value >>10) & 0x0001) * 200;
        I += ((data16.value.value >>11) & 0x0001) * 400;
        I += ((data16.value.value >>12) & 0x0001) * 800;
        I += ((data16.value.value >>13) & 0x0001) * 1600;
        I += ((data16.value.value >>14) & 0x0001) * 3200;
        I += ((data16.value.value >>15) & 0x0001) * 6400;
        printf("  ADC_Input_Current               %d.%d mA", I/2, I%2);
    }
    if(regAddr == ADC_OTG_Output_Voltage_Result_16BIT)
    {
        uint16_t U = 0;
        U += ((data16.value.value >>6) & 0x0001) * 25; //mV
        U += ((data16.value.value >>7) & 0x0001) * 50;
        U += ((data16.value.value >>8) & 0x0001) * 100;
        U += ((data16.value.value >>9) & 0x0001) * 200;
        U += ((data16.value.value >>10) & 0x0001) * 400;
        U += ((data16.value.value >>11) & 0x0001) * 800;
        U += ((data16.value.value >>12) & 0x0001) * 1600;
        U += ((data16.value.value >>13) & 0x0001) * 3200;
        U += ((data16.value.value >>14) & 0x0001) * 6400;
        U += ((data16.value.value >>15) & 0x0001) * 12800;
        printf("  ADC_OTG_Output_Voltage          %d.%03d V",U/1000,U%1000);
    }
    if(regAddr == ADC_OTG_Output_Current_Result_16BIT)
    {
        uint16_t I = 0;
        I += ((data16.value.value >>6) & 0x0001) * 13; //В 2 раза больше
        I += ((data16.value.value >>7) & 0x0001) * 25;
        I += ((data16.value.value >>8) & 0x0001) * 50;
        I += ((data16.value.value >>9) & 0x0001) * 100;
        I += ((data16.value.value >>10) & 0x0001) * 200;
        I += ((data16.value.value >>11) & 0x0001) * 400;
        I += ((data16.value.value >>12) & 0x0001) * 800;
        I += ((data16.value.value >>13) & 0x0001) * 1600;
        I += ((data16.value.value >>14) & 0x0001) * 3200;
        I += ((data16.value.value >>15) & 0x0001) * 6400;
        printf("  ADC_OTG_Output_Current          %d.%d mA", I/2, I%2);
    }
    if(regAddr == ADC_Junction_Temperature_Result_16BIT)
    {
        uint16_t T = 0;
        T += ((data16.value.value >>6) & 0x0001);
        T += ((data16.value.value >>7) & 0x0001) * 2;
        T += ((data16.value.value >>8) & 0x0001) * 4;
        T += ((data16.value.value >>9) & 0x0001) * 8;
        T += ((data16.value.value >>10) & 0x0001) * 16;
        T += ((data16.value.value >>11) & 0x0001) * 32;
        T += ((data16.value.value >>12) & 0x0001) * 64;
        T += ((data16.value.value >>13) & 0x0001) * 128;
        T += ((data16.value.value >>14) & 0x0001) * 256;
        T += ((data16.value.value >>15) & 0x0001) * 512;
        uint16_t temp = 903000 - 2578 * T;
        printf("  ADC_Junction_Temperature        %d.%02d C", temp/1000, temp%100);
    }
    if(regAddr == ADC_System_Power_Result_16BIT)
    {
        uint16_t W = 0;
        W += ((data16.value.value >>6) & 0x0001) * 125; //больше в 1000 раз
        W += ((data16.value.value >>7) & 0x0001) * 250;
        W += ((data16.value.value >>8) & 0x0001) * 500;
        W += ((data16.value.value >>9) & 0x0001) * 1000;
        W += ((data16.value.value >>10) & 0x0001) * 2000;
        W += ((data16.value.value >>11) & 0x0001) * 4000;
        W += ((data16.value.value >>12) & 0x0001) * 8000;
        W += ((data16.value.value >>13) & 0x0001) * 16000;
        W += ((data16.value.value >>14) & 0x0001) * 32000;
        W += ((data16.value.value >>15) & 0x0001) * 64000;
        printf("  ADC_System_Power                %d.%03d W", W/1000, W%1000);
    }
    if(regAddr == ADC_Battery_Discharge_Current_Result_16BIT)
    {
        uint16_t I = 0;
        I += ((data16.value.value >>6) & 0x0001) * 125; //больше в 10 раз
        I += ((data16.value.value >>7) & 0x0001) * 250;
        I += ((data16.value.value >>8) & 0x0001) * 500;
        I += ((data16.value.value >>9) & 0x0001) * 1000;
        I += ((data16.value.value >>10) & 0x0001) * 2000;
        I += ((data16.value.value >>11) & 0x0001) * 4000;
        I += ((data16.value.value >>12) & 0x0001) * 8000;
        I += ((data16.value.value >>13) & 0x0001) * 16000;
        I += ((data16.value.value >>14) & 0x0001) * 32000;
        I += ((data16.value.value >>15) & 0x0001) * 64000;
        printf("  ADC_Battery_Discharge_Current   %d.%03d mA", I/10, I%10);
    }
    if(regAddr == ADC_Result_for_NTC_Voltage_16BIT) //NTC[11:0] x 1.6V / 4096
    {
        uint16_t V = 0;
        V = (data16.value.value & 0b0000111111111111) ;
        V *= 16000;
        V /= 4096;
        printf("  ADC_Result_for_NTC_Voltage      %d.%01d mV", V/10, V%10);
    }
}

void print_byte(uint8_t byte)
{
    printf("%s%s", bit_rep[byte >> 4], bit_rep[byte & 0x0F]);
}

void print_Regs16()
{
    print_MP2650_16(ADC_Battery_Voltage_Result_16BIT);
    print_MP2650_16(ADC_System_Voltage_Result_16BIT);
    print_MP2650_16(ADC_Battery_Charge_Current_Result_16BIT);
    print_MP2650_16(ADC_Input_Voltage_Result_16BIT);
    print_MP2650_16(ADC_Input_Current_Result_16BIT);
    print_MP2650_16(ADC_OTG_Output_Voltage_Result_16BIT);
    print_MP2650_16(ADC_OTG_Output_Current_Result_16BIT);
    print_MP2650_16(ADC_Junction_Temperature_Result_16BIT);
    print_MP2650_16(ADC_System_Power_Result_16BIT);
    print_MP2650_16(ADC_Battery_Discharge_Current_Result_16BIT);
    print_MP2650_16(ADC_Result_for_NTC_Voltage_16BIT);
    printf("\r\n");
}

void init_MP2650()
{
    all_led_OFF();
    led_Test();
    REG_00_set_Input_Current_Limit_1(1500);             //1500 mA default       Range: 0mA to 5A
    REG_0F_set_Input_Current_Limit_2(1500);             //1500 mA default       Range: 0mA to 5A
    REG_01_set_Input_Voltage_Limit(4500);               //4,5V default          Range: 0V to 25.5V
    REG_02_set_Charge_Current(300);                     //1000 mA default       Range: 0A to 5A
    REG_03_set_PreCharge_Current(180);                  //180 mA default        Range: 180 - 840 mA
    REG_03_set_Termination_Current(200);                //200 mA default        Range: 0mA to 1500mA
    REG_04_set_Battery_Full_Voltage_for_one_Cell(4200); //Default: 4.2V/cell    Range: 3.7125V/cell to 4.5V/cell
    REG_04_set_Battery_Threshold_for_one_Cell_100mV();
    REG_07_set_4_cells();
    REG_08_CHARGE_EN(true);                             //  Default: 1
    REG_08_NTC_GCOMP_SEL(true);                         //  Default: 1
    REG_08_BATTFET_EN(true);                            //  Default: 1
    REG_2D_VBATT_LP_EN(true);                           //  Default: 1
}

uint8_t read_MP2650_8(uint8_t regAddr)
{
    data8.value = 0xFF;
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
    HAL_StatusTypeDef ret;
    ret = HAL_I2C_Mem_Read(&hi2c1, MP2650_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, &data8.value, 1, HAL_MAX_DELAY);
    if(HAL_OK == ret)
    {
        return data8.value;
    }
    else
    {
        printf("error code = %d\r\n", ret);
        return 0xFF;
    }
}

void write_MP2650_8(uint8_t regAddr, uint8_t regValue)
{
    HAL_Delay(3);
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Write(&hi2c1, MP2650_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&regValue, 1, HAL_MAX_DELAY);
}

void print_MP2650_8(uint8_t regAddr)
{
    data8.value = read_MP2650_8(regAddr);
    printf("MP2650_8  reg %02X     0x%02X\t", regAddr, data8.value);
    print_byte(data8.value);
    printf("\r\n");
}

void print_Regs8()
{
    print_MP2650_8(Input_Current_Limit_1_Setting);
    print_MP2650_8(Input_Voltage_Limit_Setting);
    print_MP2650_8(Charge_Current_Setting);
    print_MP2650_8(Pre_Charge_and_Termination_Current_Setting);
    print_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting);
    print_MP2650_8(Battery_Impedance_Compensation_Junction_Temperature_Regulation);
    print_MP2650_8(OTG_Voltage_Setting);
    print_MP2650_8(Pre_Charge_Threshold_and_OTG_Output_Current_Limit_Setting);
    print_MP2650_8(Configuration_Register_0);
    print_MP2650_8(Configuration_Register_1);
    print_MP2650_8(Configuration_Register_2);
    print_MP2650_8(Configuration_Register_3);
    print_MP2650_8(Configuration_Register_4);
    print_MP2650_8(System_OTG_Under_Voltage_and_Over_Voltage_Setting);
    print_MP2650_8(PROCHOT_Interrupt_Debounce_Time_and_Duration_Time_Setting);
    print_MP2650_8(Input_Current_Limit_2_Setting);
    print_MP2650_8(Input_Current_Limit_2_Duration_Setting);
    print_MP2650_8(Two_Level_Input_Current_Limit_Period_Setting);
    print_MP2650_8(Input_OCP_Threshold_for_Triggering_PROCHOT);
    print_MP2650_8(Status_Register);
    print_MP2650_8(Fault_Register);
    print_MP2650_8(Battery_OVP_Deglitch_Time);
    print_MP2650_8(Battery_Voltage_Loop_Enable);
    print_MP2650_8(Battery_Pre_Charge_Threshold_Option);
    print_MP2650_8(System_Voltage_Threshold_for_Pulse_Skipping);
    print_MP2650_8(INT_Mask_for_Hi_Z_Mode_Entry_and_Exit);
    print_MP2650_8(Analog_Frequency_Loop_Enable);
    print_MP2650_8(Hi_Z_Mode_Indication_DC_DC_Switcher_is_Off);
    printf("\r\n");
}

void REG_00_set_Input_Current_Limit_1(u_int16_t value) //in mA
{
    if (value > (0b01111111 * 50)) value = 0b01111111 * 50;
    uint8_t val = 0;
    val += value/50;
    write_MP2650_8(Input_Current_Limit_1_Setting, val);
}
void REG_01_set_Input_Voltage_Limit(u_int16_t value)
{
    if (value > (0b01111111 * 100)) value = 0b01111111 * 100;
    uint8_t val = 0;
    val += value/100;
    write_MP2650_8(Input_Voltage_Limit_Setting, val);
}
void REG_02_set_Charge_Current(u_int16_t value) //in mA
{
    if (value > (0b01111111 * 50)) value = 0b01111111 * 50;
    uint8_t val = 0;
    val += value/50;
    write_MP2650_8(Charge_Current_Setting, val);
}
void REG_03_set_PreCharge_Current(u_int16_t value) //180 - 840
{
//    data8.value &= 0b00001111;
//    data8.value |= 0b00110000;
    if (value <=180)
    {
        data8.value &= 0b00001111;
        data8.value |= 0b01000000;
    }
    if ((value > 180) && (value <= 240))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b01010000;
    }
    if ((value > 240) && (value <= 300))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b01100000;
    }
    if ((value > 300) && (value <= 360))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b01110000;
    }
    if ((value > 360) && (value <= 420))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b10000000;
    }
    if ((value > 420) && (value <= 480))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b10010000;
    }
    if ((value > 480) && (value <= 540))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b10100000;
    }
    if ((value > 540) && (value <= 600))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b10110000;
    }
    if ((value > 600) && (value <= 660))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b11000000;
    }
    if ((value > 660) && (value <= 720))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b11010000;
    }
    if ((value > 720) && (value <= 780))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b11100000;
    }
    if (value > 780)
    {
        data8.value &= 0b00001111;
        data8.value |= 0b11110000;
    }
}
void REG_03_set_Termination_Current(u_int16_t value)
{
    if (value > (0b00001111 * 100)) value = 0b00001111 * 100;
    uint8_t val = 0;
    val += value/100;
    val &= 0b00001111;
    read_MP2650_8(Pre_Charge_and_Termination_Current_Setting);
    data8.value &= 0b11110000;
    data8.value |= val;
    write_MP2650_8(Pre_Charge_and_Termination_Current_Setting, data8.value);
}
void REG_04_set_Battery_Full_Voltage_for_one_Cell(u_int16_t value)
{
    value *= 10;
    read_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting);
    data8.value &= 0b10000001;

    if (value < 37125) value = 37125;
    if (value > 45000) value = 45000;
    value -= 37125;
    uint8_t val = value / 125;
    data8.value |= (val<<1);
    write_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting, data8.value);
}
void REG_04_set_Battery_Threshold_for_one_Cell_100mV()
{
    read_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting);
    data8.value &= 0b11111110;
    write_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting, data8.value);
}
void REG_04_set_Battery_Threshold_for_one_Cell_200mV()
{
    read_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting);
    data8.value |= 0b00000001;
    write_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting, data8.value);
}
void REG_07_set_4_cells()
{
    read_MP2650_8(Pre_Charge_Threshold_and_OTG_Output_Current_Limit_Setting);
    write_MP2650_8(Pre_Charge_Threshold_and_OTG_Output_Current_Limit_Setting, data8.value &= 0b00111111);
    write_MP2650_8(Pre_Charge_Threshold_and_OTG_Output_Current_Limit_Setting, data8.value |= 0b10000000);
}
void REG_08_BATTFET_EN(_Bool val)
{
    if(val)
    {
        read_MP2650_8(Configuration_Register_0);
        write_MP2650_8(Configuration_Register_0, data8.value |= 0b00000010);
    }
    else
    {
        read_MP2650_8(Configuration_Register_0);
        write_MP2650_8(Configuration_Register_0, data8.value &= 0b11111101);
    }
}
void REG_08_CHARGE_EN(_Bool val)
{
    if(val)
    {
        read_MP2650_8(Configuration_Register_0);
        write_MP2650_8(Configuration_Register_0, data8.value |= 0b00010000);
    }
    else
    {
        read_MP2650_8(Configuration_Register_0);
        write_MP2650_8(Configuration_Register_0, data8.value &= 0b11101111);
    }
}
void REG_08_NTC_GCOMP_SEL(_Bool val)
{
    if(val)
    {
        read_MP2650_8(Configuration_Register_0);
        write_MP2650_8(Configuration_Register_0, data8.value |= 0b00000100);
    }
    else
    {
        read_MP2650_8(Configuration_Register_0);
        write_MP2650_8(Configuration_Register_0, data8.value &= 0b11111011);
    }
}
void REG_0F_set_Input_Current_Limit_2(u_int16_t value)
{
    if (value > (0b01111111 * 50)) value = 0b01111111 * 50;
    uint8_t val = 0;
    val += value/50;
    write_MP2650_8(Input_Current_Limit_2_Setting, val);
}
void REG_2D_VBATT_LP_EN(_Bool val)
{
    if(val)
    {
        read_MP2650_8(Battery_Voltage_Loop_Enable);
        write_MP2650_8(Battery_Voltage_Loop_Enable, data8.value |= 0b00000001);
    }
    else
    {
        read_MP2650_8(Battery_Voltage_Loop_Enable);
        write_MP2650_8(Battery_Voltage_Loop_Enable, data8.value &= 0b11111110);
    }
}
