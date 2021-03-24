////////////////////////////////////////////////////////////////////////////////
/// @file     usb_def.h
/// @author   AE TEAM
/// @brief    Definitions related to USB Core
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

//Define to prevent recursive inclusion
#ifndef __USB_DEF_H
#define __USB_DEF_H

//Includes


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Example_Layer
/// @brief MM32 Example Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_RESOURCE
/// @brief MM32 Examples resource modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Constants
/// @{

//Exported types
typedef enum _RECIPIENT_TYPE {
    DEVICE_RECIPIENT,     //Recipient device
    INTERFACE_RECIPIENT,  //Recipient interface
    ENDPOINT_RECIPIENT,   //Recipient endpoint
    OTHER_RECIPIENT
} RECIPIENT_TYPE;


typedef enum _STANDARD_REQUESTS {
    GET_STATUS = 0,
    CLEAR_FEATURE,
    RESERVED1,
    SET_FEATURE,
    RESERVED2,
    SET_ADDRESS,
    GET_DESCRIPTOR,
    SET_DESCRIPTOR,
    GET_CONFIGURATION,
    SET_CONFIGURATION,
    GET_INTERFACE,
    SET_INTERFACE,
    TOTAL_sREQUEST,  // Total number of Standard request
    SYNCH_FRAME = 12
} STANDARD_REQUESTS;

// Definition of "USBwValue"
typedef enum _DESCRIPTOR_TYPE {
    DEVICE_DESCRIPTOR = 1,
    CONFIG_DESCRIPTOR,
    STRING_DESCRIPTOR,
    INTERFACE_DESCRIPTOR,
    ENDPOINT_DESCRIPTOR
} DESCRIPTOR_TYPE;

// Feature selector of a SET_FEATURE or CLEAR_FEATURE
typedef enum _FEATURE_SELECTOR {
    ENDPOINT_STALL,
    DEVICE_REMOTE_WAKEUP
} FEATURE_SELECTOR;

// Exported constants
// Definition of "USBbmRequestType"
#define REQUEST_TYPE      0x60  // Mask to get request type  
#define STANDARD_REQUEST  0x00  // Standard request  
#define CLASS_REQUEST     0x20  // Class request  
#define VENDOR_REQUEST    0x40  // Vendor request  

#define RECIPIENT         0x1F  // Mask to get recipient  

// Exported macro
// Exported functions

/// @}


/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
