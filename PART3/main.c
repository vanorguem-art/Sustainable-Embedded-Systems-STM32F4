#include "main.h"
int wait=2000000;
int button;
int led_state=0;
int prev_button_state=1;
int i;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
int main(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));
  SystemClock_Config();
  MX_GPIO_Init();
  LL_GPIO_WriteReg(GPIOA, ODR,(LL_GPIO_ReadReg(GPIOA,ODR) | 0x20));
    while (1)
    {
  	  button=(LL_GPIO_ReadReg(GPIOC,IDR) & (0x01 << 13)) >> 13;
  	  if((button==0) && (prev_button_state==1)){
  		  LL_GPIO_WriteReg(GPIOA, ODR,(LL_GPIO_ReadReg(GPIOA,ODR) ^ 0x20));
  		  led_state=!led_state;
  		  if(led_state==1){
  			  LL_GPIO_WriteReg(GPIOA, ODR,(LL_GPIO_ReadReg(GPIOA,ODR) | 0x20));
  		  }else{
  			  LL_GPIO_WriteReg(GPIOA, ODR,(LL_GPIO_ReadReg(GPIOA,ODR) & ~0x20));
  		  }
  	  }
  	  prev_button_state=button;
  	  if(led_state==1){
  		  LL_GPIO_WriteReg(GPIOA, ODR,(LL_GPIO_ReadReg(GPIOA,ODR) ^ 0x20));
  		  for (i=0; i<wait; i++){}
  	  }
  }
}
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0){}
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE2);
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1){}
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI){}
  LL_Init1msTick(16000000);
  LL_SetSystemCoreClock(16000000);
}
static void MX_GPIO_Init(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
  GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void Error_Handler(void){ __disable_irq(); while (1){} }
