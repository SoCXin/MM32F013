////////////////////////////////////////////////////////////////////////////////
/// @file    tim_Sync_1master2slave.h
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FIRMWARE FUNCTIONS.
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
#ifndef ___TIM_SYNC_1MASTER2SLAVE_H
#define ___TIM_SYNC_1MASTER2SLAVE_H
// Files includes
#include "hal_conf.h"
#include  "stdio.h"


void TIM1_GPIO_Init(void);
void TIM2_GPIO_Init(void);
void TIM3_GPIO_Init(void);
void TIM1_Master_Init(u16 arr, u16 psc);
void TIM2_Slave_Init(u16 arr, u16 psc);
void TIM3_Slave_Init(u16 arr, u16 psc);

/// @}


/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
