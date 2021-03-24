////////////////////////////////////////////////////////////////////////////////
/// @file    main.c
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
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
#define _MAIN_C_

// Files includes


#include "delay.h"
#include "adcx.h"
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN_Exported_Constants
/// @{

/// @}



////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is main entrance.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
s32 main(void)
{

    DMAInit();
    //PA0
    ADCConfig(ADCch0);
    //Start Conversion
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while(1) {
        //Determine whether the second-order filter is over
        if(ADCFilterflag) {
            //Clear the filter end flag
            ADCFilterflag = 0;
            //Convert the filtered value to voltage
            Get_ADCVolatge();
            //Start Conversion
            ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        }
    }
}




/// @}

/// @}

/// @}
