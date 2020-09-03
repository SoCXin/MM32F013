////////////////////////////////////////////////////////////////////////////////
/// @file     bkp.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
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
#define _BKP_C_

// Files includes
#include "bkp.h"
#include "led.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup BKP
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup BKP_Exported_Constants
/// @{

/////////////////////////////////////////////////////////////////////////////////
/// @brief   configure ADC1single transform  mode
/// @param   None
/// @retval  None
/////////////////////////////////////////////////////////////////////////////////

BKPDR_Typedef BKPDataReg[10] = {
    BKP_DR1, BKP_DR2, BKP_DR3, BKP_DR4, BKP_DR5, BKP_DR6, BKP_DR7, BKP_DR8,
    BKP_DR9, BKP_DR10
};
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN_Exported_Functions
/// @{
////////////////////////////////////////////////////////////////////////////////
/// @brief   This function is main entrance.
/// @param   None
/// @retval  None
////////////////////////////////////////////////////////////////////////////////
void BKP_Test(void)
{
    int i;
    // Enable PWR and BKP clock
    RCC->APB1ENR |= RCC_APB1ENR_PWR;
    // Enable write access to Backup domain
    PWR->CR |= PWR_CR_DBP;
    // Write data to register library
    for(i = 0; i < 10; i++) {
        (*(u16*)(BKP_BASE + BKPDataReg[i])) = 0xabcd;
    }
    // Check if the written data are correct
    for(i = 0; i < 10; i++) {
        if(*(u16*)(BKP_BASE + BKPDataReg[1]) != (0xabcd)) {
            // Turn off LED1
            LED1_ON();//Data read-write error
            break;
        }
        else {
            // Turn off LED3
            LED3_ON();//Correct data reading and writing
        }
    }
}
/// @}


/// @}

/// @}
