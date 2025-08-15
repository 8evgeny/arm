/* Перечень регистров микросхемы MP2650 */

//8 БИТНЫЕ - 28шт
#define Input_Current_Limit_1_Setting                                       0x00
#define Input_Voltage_Limit_Setting                                         0x01
#define Charge_Current_Setting                                              0x02
#define Pre_Charge_and_Termination_Current_Setting                          0x03
#define Battery_Full_Voltage_and_Recharge_Threshold_Setting                 0x04
#define Battery_Impedance_Compensation_Junction_Temperature_Regulation      0x05
#define OTG_Voltage_Setting                                                 0x06
#define Pre_Charge_Threshold_and_OTG_Output_Current_Limit_Setting           0x07
#define Configuration_Register_0                                            0x08
#define Configuration_Register_1                                            0x09
#define Configuration_Register_2                                            0x0A
#define Configuration_Register_3                                            0x0B
#define Configuration_Register_4                                            0x0C
#define System_OTG_Under_Voltage_and_Over_Voltage_Setting                   0x0D
#define PROCHOT_Interrupt_Debounce_Time_and_Duration_Time_Setting           0x0E
#define Input_Current_Limit_2_Setting                                       0x0F
#define Input_Current_Limit_2_Duration_Setting                              0x10
#define Two_Level_Input_Current_Limit_Period_Setting                        0x11
#define Input_OCP_Threshold_for_Triggering_PROCHOT                          0x12
#define Status_Register                                                     0x13
#define Fault_Register                                                      0x14
#define Battery_OVP_Deglitch_Time                                           0x2B
#define Battery_Voltage_Loop_Enable                                         0x2D
#define Battery_Pre_Charge_Threshold_Option                                 0x30
#define System_Voltage_Threshold_for_Pulse_Skipping                         0x31
#define INT_Mask_for_Hi_Z_Mode_Entry_and_Exit                               0x33
#define Analog_Frequency_Loop_Enable                                        0x36
#define Hi_Z_Mode_Indication_DC_DC_Switcher_is_Off                          0x48

//16 БИТНЫЕ - 11 шт
#define ADC_Battery_Voltage_Result_16BIT                                    0x16
#define ADC_System_Voltage_Result_16BIT                                     0x18
#define ADC_Battery_Charge_Current_Result_16BIT                             0x1A
#define ADC_Input_Voltage_Result_16BIT                                      0x1C
#define ADC_Input_Current_Result_16BIT                                      0x1E
#define ADC_OTG_Output_Voltage_Result_16BIT                                 0x20
#define ADC_OTG_Output_Current_Result_16BIT                                 0x22
#define ADC_Junction_Temperature_Result_16BIT                               0x24
#define ADC_System_Power_Result_16BIT                                       0x26
#define ADC_Battery_Discharge_Current_Result_16BIT                          0x28
#define ADC_Result_for_NTC_Voltage_16BIT                                    0x40
