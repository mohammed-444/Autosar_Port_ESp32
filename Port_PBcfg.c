 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Source file for esp32 Microcontroller - Port Driver.
 *
 * Author: Mohammed Alaa
 ******************************************************************************/

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION           (1U)
#define PORT_PBCFG_SW_MINOR_VERSION           (0U)
#define PORT_PBCFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION   (3U)

#include "Port.h"

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

#include "Port_MemMap.h"

/*this array use to store the pins which will be left without configuration*/
const uint8 Banned_Pins[PORT_BANNED_PINS]={PORT_Pin0 , PORT_Pin1 , PORT_Pin3 , PORT_Pin5 , PORT_Pin6 , PORT_Pin7 , PORT_Pin8 , PORT_Pin9 , PORT_Pin10 , PORT_Pin11 , PORT_Pin12
										   , PORT_Pin15 , PORT_Pin20 , PORT_Pin24 , PORT_Pin28 , PORT_Pin29 , PORT_Pin30 , PORT_Pin31 , PORT_Pin37 , PORT_Pin38};

/*this array use to map the address of the IO_MUX to continuously without the need of calling every one independently*/
const uint32 PinIndex_to_IO_MUX_PinIndex[PORT_CONFIGURED_PINS]={
		(uint32)IO_MUX_GPIO0_REG , (uint32)IO_MUX_GPIO1_REG , (uint32)IO_MUX_GPIO2_REG , (uint32)IO_MUX_GPIO3_REG , (uint32)IO_MUX_GPIO4_REG , (uint32)IO_MUX_GPIO5_REG, (uint32)IO_MUX_GPIO6_REG
		,(uint32)IO_MUX_GPIO7_REG , (uint32)IO_MUX_GPIO8_REG , (uint32)IO_MUX_GPIO9_REG , (uint32)IO_MUX_GPIO10_REG , (uint32)IO_MUX_GPIO11_REG , (uint32)IO_MUX_GPIO12_REG, (uint32)IO_MUX_GPIO13_REG
		,(uint32)IO_MUX_GPIO14_REG , (uint32)IO_MUX_GPIO15_REG , (uint32)IO_MUX_GPIO16_REG , (uint32) IO_MUX_GPIO17_REG , (uint32)IO_MUX_GPIO18_REG , (uint32)IO_MUX_GPIO19_REG , (uint32)IO_MUX_GPIO20_REG
		,(uint32)IO_MUX_GPIO21_REG , (uint32)IO_MUX_GPIO22_REG , (uint32)IO_MUX_GPIO23_REG , (uint32) IO_MUX_GPIO24_REG , (uint32)IO_MUX_GPIO25_REG , (uint32)IO_MUX_GPIO26_REG , (uint32)IO_MUX_GPIO27_REG
		,(uint32)ZERO , (uint32)ZERO , (uint32)ZERO , (uint32)ZERO , (uint32)IO_MUX_GPIO32_REG , (uint32)IO_MUX_GPIO33_REG , (uint32)IO_MUX_GPIO34_REG ,(uint32)IO_MUX_GPIO35_REG , (uint32)IO_MUX_GPIO36_REG ,
		(uint32)IO_MUX_GPIO37_REG ,(uint32)IO_MUX_GPIO38_REG , (uint32)IO_MUX_GPIO39_REG };


/* Description: Structure to configure each individual PIN:
 *	1. the number of the pin .
 *  2. the direction of pin --> INPUT or OUTPUT
 *  3. the internal resistor --> Disable, Pull up or Pull down
 *  4. initial port pin output  ( PORT_PIN_LEVEL_LOW,PORT_PIN_LEVEL_HIGH)
 *  5. a const_HighInput or a const_LowInput or Func_dependant
 *  6. 0: normal output; 1: open drain output
 *  7. Select the drive strength of the pad. [0-3]A higher value corresponds with a higher strength.
 *  8. Port_Input_PinInitialMode
 *  9. Port_Output_PinInitialMode
 *  10. Bypass the GPIO Matrix. 1: route through GPIO Matrix, 0: connect signal directly to peripheral configured in the IO_MUX
 *  11. Select the IO_MUX function for this signal
 *  12. pin direction changeable (true, false)
 *  13. pin mode changeable (true, false)
 */
/* PB structure used with Port_Init API */
const Port_ConfigType Port_PinConfig = {
/*-------------------------------------------------------------------IO0 button, boot strap pin, must be high on boot (can't use ADC with WIFI)---------------------------------------------------------------*/
{{PORT_Pin0 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*---------------------------------------------------------------------------------Used for USB communications------------------------------------------------------------------------------------------------*/
{PORT_Pin1  , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*----------------------------------------------------------------------------------------connected to a led-------------------------------------------------------------------------------------------------*/
{PORT_Pin2  , PORT_PIN_OUT , OFF ,PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*---------------------------------------------------------------------------------Used for USB communications------------------------------------------------------------------------------------------------*/
{PORT_Pin3  , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
{PORT_Pin4  , PORT_PIN_OUT , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*------------------------------------------------------------------------------ boot strap pin, must be high on boot ----------------------------------------------------------------------------------------*/
{PORT_Pin5  , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*--------------------------------------------------------------------------------SPI USED DURING FLASHING MEMORY-------------------------------------------------------------------------------------------------*/
{PORT_Pin6  , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin7  , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin8  , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin9  , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin10 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin11 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*----------------------------------------------------------------------Boot strap input pin, must be low on boot (can't use ADC with WIFI)-------------------------------------------------------------------*/
{PORT_Pin12 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
{PORT_Pin13 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin14 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*------------------------------------------------------------------------Boot strap input pin, must be high on boot (can't use ADC with WIFI)----------------------------------------------------------------*/
{PORT_Pin15 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
{PORT_Pin16 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin17 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin18 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin19 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*--------------------------------------------------------------------------------------------DO NOT EXIST----------------------------------------------------------------------------------------------------*/
{PORT_Pin20 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*----------------------------------------------------------------------------------------I2C SCL-->22 , SDA--> 21-------------------------------------------------------------------------------------------*/
{PORT_Pin21 , PORT_PIN_OUT , PULL_UP , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_3 , I2CEXT0_SDA_in , I2CEXT0_SDA_out , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin22 , PORT_PIN_OUT , PULL_UP , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_3 , I2CEXT0_SCL_in , I2CEXT0_SCL_out , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
{PORT_Pin23 , PORT_PIN_OUT , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*--------------------------------------------------------------------------------------------DO NOT EXIST----------------------------------------------------------------------------------------------------*/
{PORT_Pin24 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
{PORT_Pin25 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin26 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin27 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*--------------------------------------------------------------------------------------------DO NOT EXIST----------------------------------------------------------------------------------------------------*/
{PORT_Pin28 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin29 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin30 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin31 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
{PORT_Pin32 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin33 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*------------------------------------------------------------------------------------------INPUT ONLY PINS---------------------------------------------------------------------------------------------------*/
{PORT_Pin34 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin35 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin36 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*--------------------------------------------------------------------------------------------DO NOT EXIST----------------------------------------------------------------------------------------------------*/
{PORT_Pin37 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
{PORT_Pin38 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON},
/*------------------------------------------------------------------------------------------INPUT ONLY PIN---------------------------------------------------------------------------------------------------*/
{PORT_Pin39 , PORT_PIN_IN , OFF , PORT_PIN_LEVEL_LOW , Func_dependant , PORT_NORMAL_MODE , PORT_PIN_DRIVE_DEFAULT , PORT_PinInput_Default , PORT_PinOutput_DIO , GPIO_Matrix , GPIO_Function , STD_ON , STD_ON}}
};
