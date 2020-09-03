////////////////////////////////////////////////////////////////////////////////
/// @file    pwr.c
/// @author  AE TEAM
/// @brief    In window comparator mode,The transformation results are detected
///           Set the threshold value from 0 to 3V, and connect PB6 and PA0 with
///           jumper cap to see the effect.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////
// Define to prevent recursive inclusion
#define _PWR_C_

// Files includes
#include "delay.h"
#include "led.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup PWR
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup PWR_Exported_Functions
/// @{
#define RTC_IRQHandler RTC_BKP_IRQHandler

////////////////////////////////////////////////////////////////////////////////
/// @brief  delay nTime ms
/// @note   get x times.
/// @param  nTime  nTime ms.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void deleyNop(u32 DlyTime)
{
    u32 i, j;
    for(i = 0; i < DlyTime; i++) {
        for(j = 0; j < 100; j++) {
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
    }
}
void Iwdg_Irq_ON(void)
{

    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    EXTI_DeInit();
    EXTI_StructInit(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line = EXTI_Line24 ;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt ;
    EXTI_InitStructure.EXTI_Trigger =   EXTI_Trigger_Rising_Falling  ;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    EXTI_ClearITPendingBit(EXTI_Line24);

    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IWDG_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}
void WWDG_IRQHandler(void)
{

    EXTI_ClearFlag(EXTI_Line24);
    IWDG_WriteAccessCmd(0x5555);
    IWDG->CR |= 0x02;
    IWDG->KR = 0xAAAA;
    LED1_TOGGLE();
    deleyNop(100);
}
#define IWDG_FLAG_IVU               ((uint16_t)0x0004)
void IVU_CheckStatus(void)
{
    while(1) {
        if(IWDG_GetFlagStatus(IWDG_FLAG_IVU) == RESET) {
            break;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Set IWDG on
/// @param  IWDG_Prescaler     prescaler value
///         Reload      reload value
/// @retval None
////////////////////////////////////////////////////////////////////////////////
void Write_Iwdg_ON(u16 IWDG_Prescaler, u16 Reload)
{
    RCC_LSICmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

    PVU_CheckStatus();
    IWDG_WriteAccessCmd(0x5555);
    IWDG_SetPrescaler(IWDG_Prescaler);

    RVU_CheckStatus();
    IWDG_WriteAccessCmd(0x5555);
    IWDG_SetReload(Reload & 0xfff);

    IVU_CheckStatus();
    IWDG_WriteAccessCmd(0x5555);
    IWDG->IGEN = 0x50;

    IWDG_ReloadCounter();
    IWDG_WriteAccessCmd(0x5555);
    IWDG->CR |= 1;
    IWDG_Enable();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  initialize LED GPIO pin
/// @note   if use jtag/swd interface GPIO PIN as LED, need to be careful,
///         can not debug or program.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void PWR_STOP_iwdg_Init(void)
{
//    important notes
//    need to set those GPIO Pins as AIN exclude the wake up pin;
//    need to disalbe those interrupts (Systick, Timer), exclude the wake interrupt
    int i;
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWREN, ENABLE);
    for(i = 0; i < 6; i++) {
        deleyNop(1000);
        LED3_TOGGLE();
    }
    Iwdg_Irq_ON();
    Write_Iwdg_ON(IWDG_Prescaler_32, 0xFFF);
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
}


/// @}

/// @}

/// @}
