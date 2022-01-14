
//---------------------------------
// rcc_delay.c
// ����� ��������� (MDR32)
//---------------------------------
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_iwdg.h"
//---------------------------------
#include "gpio.h"
#include "main.h"
//---------------------------------
// ��������� ������������ ����������������
//---------------------------------
void RCC_init() {
	RST_CLK_DeInit();	//����� ��������
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);			//��������� �������� ������ 8 ��� (CPU_C1_SEL)
	while (RST_CLK_HSEstatus() != SUCCESS);	//���� ��������� HSE
	RST_CLK_CPUclkSelectionC1(RST_CLK_CPU_C1srcHSEdiv1);	//������������� CPU_C1: �������� ������������ CPU
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul9); 	//CPU_PLL = 8MHz * 9 = 72 MHz
	RST_CLK_CPU_PLLuse(ENABLE);	//������������� CPU_C2_SEL: ���������� CPU_PLL ��� ����� CPU_C3_SEL
  RST_CLK_CPU_PLLcmd(ENABLE);	//�������� CPU_PLL
	while (RST_CLK_CPU_PLLstatus() != SUCCESS);	//���� ��������� CPU_PLL
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);	//������������ CPU_C3_SEL = 1
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);	//�������� ������������ - ����� ������������
	RST_CLK_HSIcmd(DISABLE);// ��������� HSI	
}
//---------------------------------
// ��������� IWDT
//---------------------------------
void IWDT_init() {
	RST_CLK_LSIcmd(ENABLE);	// �������� LSI
	while (RST_CLK_LSIstatus() != SUCCESS);	//���� ��������� LSI
	RST_CLK_PCLKcmd(RST_CLK_PCLK_IWDG, ENABLE);	//��������� ������������
	IWDG_WriteAccessEnable();	//��������� ������ � ��������� IWDG
	IWDG_SetPrescaler(IWDG_Prescaler_256);	//������������� ������������ 4, 8, 16 ... 256
	IWDG_SetReload(0x0FFF);	//�������� ��� ������������ 0x0000...0x0FFF.
	IWDG_ReloadCounter();		//������������� ��������
	IWDG_WriteAccessDisable();	//��������� ������ � ��������� IWDG
	IWDG_Enable();	//�������� IWDT	
}
//---------------------------------
// ��������� TIM1
//---------------------------------
void TIM1_init() {
	TIMER_CntInitTypeDef TIM1_InitStructure;
	//��������� ������������
	RST_CLK_PCLKcmd (RST_CLK_PCLK_TIMER1, ENABLE);
	//�������� ������� ������� TIM_CLOCK = 2 (��, �� ��� �������� ���������)
	TIMER_BRGInit(MDR_TIMER1, TIMER_HCLKdiv1);	
	//��������� TIM1
	TIM1_InitStructure.TIMER_IniCounter = 0;
	TIM1_InitStructure.TIMER_Prescaler = 3600;	//������������ 3600	
	TIM1_InitStructure.TIMER_Period = 10;	//������������ � 1000 (��, �� ��� �������� ���������)
	TIM1_InitStructure.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;
	TIM1_InitStructure.TIMER_CounterDirection = TIMER_CntDir_Up;
	TIM1_InitStructure.TIMER_EventSource = TIMER_EvSrc_TM1;
	TIM1_InitStructure.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_1;
	TIM1_InitStructure.TIMER_ARR_UpdateMode = TIMER_ARR_Update_On_CNT_Overflow;
	TIM1_InitStructure.TIMER_ETR_FilterConf = TIMER_Filter_1FF_at_TIMER_CLK;
	TIM1_InitStructure.TIMER_ETR_Prescaler = TIMER_ETR_Prescaler_None;
	TIM1_InitStructure.TIMER_ETR_Polarity = TIMER_ETRPolarity_NonInverted;
	TIM1_InitStructure.TIMER_BRK_Polarity = TIMER_BRKPolarity_NonInverted;
	TIMER_CntInit(MDR_TIMER1, &TIM1_InitStructure);
	TIMER_ITConfig(MDR_TIMER1, TIMER_STATUS_CNT_ARR, ENABLE);
	NVIC_SetPriority (Timer1_IRQn, 1); // ��������� ����������
	NVIC_EnableIRQ(Timer1_IRQn);
	TIMER_Cmd(MDR_TIMER1, ENABLE);
}
//---------------------------------
void Timer1_IRQHandler() {
	TIMER_ClearFlag(MDR_TIMER1, TIMER_STATUS_CNT_ARR);
	if (delay_dec) delay_dec--;
}
//---------------------------------
// �������� � ������������
//---------------------------------
void delay_ms(uint32_t ms) {
	delay_dec = ms;
	while (delay_dec) {};
}
/*
//---------------------------------
// ��������� SysTick
//---------------------------------
void SysTick_init(void) {
	#define	CLKSOURCE		(1<<2)	//��������� �������� �������������: 0 - LSI, 1 - HCLK
	#define TCKINT			(1<<1)	//��������� ������ �� ���������� �� ���������� �������
	#define ENABLE			(1<<0)	//��������� ������ �������
	SysTick->LOAD = (72000000/1000)-1;
	SysTick->CTRL |= CLKSOURCE|TCKINT|ENABLE;	
}
//---------------------------------
// ���������� SysTick
//---------------------------------
void SysTick_Handler (void) {
	//if (delay_dec) delay_dec--;
}
*/
