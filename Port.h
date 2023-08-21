 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for esp32 Microcontroller - Port Driver.
 *
 * Author: Mohammed Alaa
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Mohammed Alaa's ID = 111 :) */
#define PORT_VENDOR_ID    (111U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "../../utilities/Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "../../utilities/Compiler.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((COMPILER_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (COMPILER_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (COMPILER_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Compiler.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((COMPILER_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (COMPILER_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (COMPILER_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Compiler.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "../../utilities/Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port_Init */
#define PORT_INIT_SID						(uint8)0x00

/* Service ID for Port_SetPinDirection */
#define PORT_SET_PIN_DIR_SID				(uint8)0x01

/* Service ID for Port_RefreshPortDirection */
#define PORT_REFRESH_PORT_DIR_SID			(uint8)0x02

/* Service ID for Port_GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID			(uint8)0x03

/* Service ID for Port_SetPinMode */
#define PORT_SET_PIN_MODE_SID				(uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN 					(uint8)0x0A

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE 		(uint8)0x0B

/* API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG				 	(uint8)0x0C

/* API Port_SetPinMode service called when Port Pin Mode passed not valid */
#define PORT_E_PARAM_INVALID_MODE 			(uint8)0x0D

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE 			(uint8)0x0E

/* API service called without module initialization */
#define PORT_E_UNINIT 						(uint8)0x0F

/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER 				(uint8)0x10


/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/* Description: Data type for the symbolic name of a port pin */
typedef uint8 Port_PinType;

/* Description: Possible directions of a port pin */
typedef enum
{
	PORT_PIN_DISABLE = 0U,/*  disable input and output    */
	PORT_PIN_IN = 1U,/*input only*/
	PORT_PIN_OUT = 2U,/*output only*/
	PORT_PIN_OUT_Periph = 3U,/*Force the output enable signal to be sourced from bit n of GPIO_ENABLE_REG; or use output enable signal from peripheral*/
	PORT_PIN_INPUT_OUTPUT = 4U, /* output and input mode */
	PORT_PIN_INPUT_OUTPUT_Periph = 5U /* output enable signal from peripheral and input mode */

}Port_PinDirectionType;

/* Description: Different port pin modes */
typedef uint16 Port_PinModeType;

/* Description: Port Pin Level value from Port pin list */
typedef enum
{
	PORT_PIN_LEVEL_LOW = 0U,
	PORT_PIN_LEVEL_HIGH = 1U
}Port_PinLevelValue;


/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF = 0U,
	PULL_UP = 1U,
	PULL_DOWN = 2U
}Port_InternalResistor;
/*Select the drive strength of the pad. [0-3]A higher value corresponds with a higher strength.For GPIO34-39, FUN_DRV is always 0*/
typedef enum
{
	PORT_PIN_DRIVE_0       = 0U,    /*!< Pad drive capability: weak */
	PORT_PIN_DRIVE_1       = 1U,    /*!< Pad drive capability: stronger */
	PORT_PIN_DRIVE_2       = 2U,    /*!< Pad drive capability: medium */
	PORT_PIN_DRIVE_DEFAULT = 2U,    /*!< Pad drive capability: medium */
	PORT_PIN_DRIVE_3       = 3U,    /*!< Pad drive capability: strongest */
}Port_DriveStrength;
/*Select the IO_MUX function for this signal. 0 selects Function 0, 1 selects Function 1, etc
 * look at Technical Reference Manual at table 4-3 page 57*/
typedef enum
{
	Function0=0U,
	Function1=1U,
	Function2=2U,
	GPIO_Function=2U,
	Function3=3U,
	Function4=4U,
	Function5=5U
}Port_IO_MUX_PathSelection;
/*0: normal output; 1: open drain output*/
typedef enum
{
	PORT_NORMAL_MODE = 0U,
	PORT_OPEN_DRAIN_MODE = 1U
}Port_PinDrive;
/*Bypass the GPIO Matrix. 1: route through GPIO Matrix, 0: connect signal directly to peripheral configured in the IO_MUX*/
typedef enum
{
	IO_MUX = 0U,
	GPIO_Matrix = 1U
}Port_SIG_IN_Config;
/* Selection control for peripheral input y. A value of 0-39 selects which of the 40 GPIO Matrix input pins this signal is connected to,
 *  or 0x38 for a constantly high input or 0x30 for a constantly low input */
typedef enum
{
	Func_dependant = 0U,
	const_LowInput = 0x30U,
	const_HighInput = 0x38U
}Port_FUNC_IN_Config;

/* Port pin mode from mode list for use with Port_Init() function look at Technical Reference Manual at table 4-9 page 52 */
typedef enum
{		PORT_PinInput_Default=255U,
		SPICLK_in  = 0U,
		SPIQ_in  = 1U,
		SPID_in  = 2U,
		SPIHD_in  = 3U,
		SPIWP_in  = 4U,
		SPICS0_in  = 5U,
		SPICS1_in  = 6U,
		SPICS2_in  = 7U,
		HSPICLK_in  = 8U,
		HSPIQ_in  = 9U,
		HSPID_in  = 10U,
		HSPICS0_in  = 11U,
		HSPIHD_in  = 12U,
		HSPIWP_in  = 13U,
		U0RXD_in  = 14U,
		U0CTS_in  = 15U,
		U0DSR_in  = 16U,
		U1RXD_in  = 17U,
		U1CTS_in  = 18U,
		I2S0O_BCK_in  = 23U,
		I2S1O_BCK_in  = 24U,
		I2S0O_WS_in  = 25U,
		I2S1O_WS_in  = 26U,
		I2S0I_BCK_in  = 27U,
		I2S0I_WS_in  = 28U,
		I2CEXT0_SCL_in  = 29U,
		I2CEXT0_SDA_in  = 30U,
		pwm0_sync0_in  = 31U,
		pwm0_sync1_in  = 32U,
		pwm0_sync2_in  = 33U,
		pwm0_f0_in  = 34U,
		pwm0_f1_in  = 35U,
		pwm0_f2_in  = 36U,
		pcnt_sig_ch0_in0  = 39U,
		pcnt_sig_ch1_in0  = 40U,
		pcnt_ctrl_ch0_in0  = 41U,
		pcnt_ctrl_ch1_in0  = 42U,
		pcnt_sig_ch0_in1  = 43U,
		pcnt_sig_ch1_in1  = 44U,
		pcnt_ctrl_ch0_in1  = 45U,
		pcnt_ctrl_ch1_in1  = 46U,
		pcnt_sig_ch0_in2  = 47U,
		pcnt_sig_ch1_in2  = 48U,
		pcnt_ctrl_ch0_in2  = 49U,
		pcnt_ctrl_ch1_in2  = 50U,
		pcnt_sig_ch0_in3  = 51U,
		pcnt_sig_ch1_in3  = 52U,
		pcnt_ctrl_ch0_in3  = 53U,
		pcnt_ctrl_ch1_in3  = 54U,
		pcnt_sig_ch0_in4  = 55U,
		pcnt_sig_ch1_in4  = 56U,
		pcnt_ctrl_ch0_in4  = 57U,
		pcnt_ctrl_ch1_in4  = 58U,
		HSPICS1_in  = 61U,
		HSPICS2_in  = 62U,
		VSPICLK_in  = 63U,
		VSPIQ_in  = 64U,
		VSPID_in  = 65U,
		VSPIHD_in  = 66U,
		VSPIWP_in  = 67U,
		VSPICS0_in  = 68U,
		VSPICS1_in  = 69U,
		VSPICS2_in  = 70U,
		pcnt_sig_ch0_in5  = 71U,
		pcnt_sig_ch1_in5  = 72U,
		pcnt_ctrl_ch0_in5  = 73U,
		pcnt_ctrl_ch1_in5  = 74U,
		pcnt_sig_ch0_in6  = 75U,
		pcnt_sig_ch1_in6  = 76U,
		pcnt_ctrl_ch0_in6  = 77U,
		pcnt_ctrl_ch1_in6  = 78U,
		pcnt_sig_ch0_in7  = 79U,
		pcnt_sig_ch1_in7  = 80U,
		pcnt_ctrl_ch0_in7  = 81U,
		pcnt_ctrl_ch1_in7  = 82U,
		rmt_sig_in0  = 83U,
		rmt_sig_in1  = 84U,
		rmt_sig_in2  = 85U,
		rmt_sig_in3  = 86U,
		rmt_sig_in4  = 87U,
		rmt_sig_in5  = 88U,
		rmt_sig_in6  = 89U,
		rmt_sig_in7  = 90U,
		I2CEXT1_SCL_in  = 95U,
		I2CEXT1_SDA_in  = 96U,
		host_card_detect_n_1  = 97U,
		host_card_detect_n_2  = 98U,
		host_card_write_prt_1  = 99U,
		host_card_write_prt_2  = 100U,
		host_card_int_n_1  = 101U,
		host_card_int_n_2  = 102U,
		pwm1_sync0_in  = 103U,
		pwm1_sync1_in  = 104U,
		pwm1_sync2_in  = 105U,
		pwm1_f0_in  = 106U,
		pwm1_f1_in  = 107U,
		pwm1_f2_in  = 108U,
		pwm0_cap0_in  = 109U,
		pwm0_cap1_in  = 110U,
		pwm0_cap2_in  = 111U,
		pwm1_cap0_in  = 112U,
		pwm1_cap1_in  = 113U,
		pwm1_cap2_in  = 114U,
		I2S0I_DATA_in0  = 140U,
		I2S0I_DATA_in1  = 141U,
		I2S0I_DATA_in2  = 142U,
		I2S0I_DATA_in3  = 143U,
		I2S0I_DATA_in4  = 144U,
		I2S0I_DATA_in5  = 145U,
		I2S0I_DATA_in6  = 146U,
		I2S0I_DATA_in7  = 147U,
		I2S0I_DATA_in8  = 148U,
		I2S0I_DATA_in9  = 149U,
		I2S0I_DATA_in10  = 150U,
		I2S0I_DATA_in11  = 151U,
		I2S0I_DATA_in12  = 152U,
		I2S0I_DATA_in13  = 153U,
		I2S0I_DATA_in14  = 154U,
		I2S0I_DATA_in15  = 155U,
		I2S1I_BCK_in  = 164U,
		I2S1I_WS_in  = 165U,
		I2S1I_DATA_in0  = 166U,
		I2S1I_DATA_in1  = 167U,
		I2S1I_DATA_in2  = 168U,
		I2S1I_DATA_in3  = 169U,
		I2S1I_DATA_in4  = 170U,
		I2S1I_DATA_in5  = 171U,
		I2S1I_DATA_in6  = 172U,
		I2S1I_DATA_in7  = 173U,
		I2S1I_DATA_in8  = 174U,
		I2S1I_DATA_in9  = 175U,
		I2S1I_DATA_in10  = 176U,
		I2S1I_DATA_in11  = 177U,
		I2S1I_DATA_in12  = 178U,
		I2S1I_DATA_in13  = 179U,
		I2S1I_DATA_in14  = 180U,
		I2S1I_DATA_in15  = 181U,
		I2S0I_H_SYNC  = 190U,
		I2S0I_V_SYNC  = 191U,
		I2S0I_H_ENABLE  = 192U,
		I2S1I_H_SYNC  = 193U,
		I2S1I_V_SYNC  = 194U,
		I2S1I_H_ENABLE  = 195U,
		U2RXD_in  = 198U,
		U2CTS_in  = 199U,
		emac_mdc_i  = 200U,
		emac_mdi_i  = 201U,
		emac_crs_i  = 202U,
		emac_col_i  = 203U,
		pcmfsync_in  = 204U,
		pcmclk_in  = 205U,
		pcmdin  = 206U,
}Port_Input_PinInitialMode;
typedef enum
{
		PORT_PinOutput_DIO=0x100U,
		SPICLK_out  = 0U,
		SPIQ_out  = 1U,
		SPID_out  = 2U,
		SPIHD_out  = 3U,
		SPIWP_out  = 4U,
		SPICS0_out  = 5U,
		SPICS1_out  = 6U,
		SPICS2_out  = 7U,
		HSPICLK_out  = 8U,
		HSPIQ_out  = 9U,
		HSPID_out  = 10U,
		HSPICS0_out  = 11U,
		HSPIHD_out  = 12U,
		HSPIWP_out  = 13U,
		U0TXD_out  = 14U,
		U0RTS_out  = 15U,
		U0DTR_out  = 16U,
		U1TXD_out  = 17U,
		U1RTS_out  = 18U,
		I2S0O_BCK_out  = 23U,
		I2S1O_BCK_out  = 24U,
		I2S0O_WS_out  = 25U,
		I2S1O_WS_out  = 26U,
		I2S0I_BCK_out  = 27U,
		I2S0I_WS_out  = 28U,
		I2CEXT0_SCL_out = 29U,
		I2CEXT0_SDA_out = 30U,
		sdio_tohost_int_out = 31U,
		pwm0_out0a = 32U,
		pwm0_out0b = 33U,
		pwm0_out1a = 34U,
		pwm0_out1b = 35U,
		pwm0_out2a = 36U,
		pwm0_out2b = 37U,
		HSPICS1_out = 61U,
		HSPICS2_out = 62U,
		VSPICLK_out_mux = 63U,
		VSPIQ_out = 64U,
		VSPID_out = 65U,
		VSPIHD_out = 66U,
		VSPIWP_out = 67U,
		VSPICS0_out = 68U,
		VSPICS1_out = 69U,
		VSPICS2_out = 70U,
		ledc_hs_sig_out0 = 71U,
		ledc_hs_sig_out1 = 72U,
		ledc_hs_sig_out2 = 73U,
		ledc_hs_sig_out3 = 74U,
		ledc_hs_sig_out4 = 75U,
		ledc_hs_sig_out5 = 76U,
		ledc_hs_sig_out6 = 77U,
		ledc_hs_sig_out7 = 78U,
		ledc_ls_sig_out0 = 79U,
		ledc_ls_sig_out1 = 80U,
		ledc_ls_sig_out2 = 81U,
		ledc_ls_sig_out3 = 82U,
		ledc_ls_sig_out4 = 83U,
		ledc_ls_sig_out5 = 84U,
		ledc_ls_sig_out6 = 85U,
		ledc_ls_sig_out7 = 86U,
		rmt_sig_out0 = 87U,
		rmt_sig_out1 = 88U,
		rmt_sig_out2 = 89U,
		rmt_sig_out3 = 90U,
		rmt_sig_out4 = 91U,
		rmt_sig_out5 = 92U,
		rmt_sig_out6 = 93U,
		rmt_sig_out7 = 94U,
		I2CEXT1_SCL_out = 95U,
		I2CEXT1_SDA_out = 96U,
		host_ccmd_od_pullup_en_n = 97U,
		host_rst_n_1 = 98U,
		host_rst_n_2 = 99U,
		gpio_sd0_out = 100U,
		gpio_sd1_out = 101U,
		gpio_sd2_out = 102U,
		gpio_sd3_out = 103U,
		gpio_sd4_out = 104U,
		gpio_sd5_out = 105U,
		gpio_sd6_out = 106U,
		gpio_sd7_out = 107U,
		pwm1_out0a = 108U,
		pwm1_out0b = 109U,
		pwm1_out1a = 110U,
		pwm1_out1b = 111U,
		pwm1_out2a = 112U,
		pwm1_out2b = 113U,
		I2S0O_DATA_out0 = 140U,
		I2S0O_DATA_out1 = 141U,
		I2S0O_DATA_out2 = 142U,
		I2S0O_DATA_out3 = 143U,
		I2S0O_DATA_out4 = 144U,
		I2S0O_DATA_out5 = 145U,
		I2S0O_DATA_out6 = 146U,
		I2S0O_DATA_out7 = 147U,
		I2S0O_DATA_out8 = 148U,
		I2S0O_DATA_out9 = 149U,
		I2S0O_DATA_out10 = 150U,
		I2S0O_DATA_out11 = 151U,
		I2S0O_DATA_out12 = 152U,
		I2S0O_DATA_out13 = 153U,
		I2S0O_DATA_out14 = 154U,
		I2S0O_DATA_out15 = 155U,
		I2S0O_DATA_out16 = 156U,
		I2S0O_DATA_out17 = 157U,
		I2S0O_DATA_out18 = 158U,
		I2S0O_DATA_out19 = 159U,
		I2S0O_DATA_out20 = 160U,
		I2S0O_DATA_out21 = 161U,
		I2S0O_DATA_out22 = 162U,
		I2S0O_DATA_out23 = 163U,
		I2S1I_BCK_out = 164U,
		I2S1I_WS_out = 165U,
		I2S1O_DATA_out0 = 166U,
		I2S1O_DATA_out1 = 167U,
		I2S1O_DATA_out2 = 168U,
		I2S1O_DATA_out3 = 169U,
		I2S1O_DATA_out4 = 170U,
		I2S1O_DATA_out5 = 171U,
		I2S1O_DATA_out6 = 172U,
		I2S1O_DATA_out7 = 173U,
		I2S1O_DATA_out8 = 174U,
		I2S1O_DATA_out9 = 175U,
		I2S1O_DATA_out10 = 176U,
		I2S1O_DATA_out11 = 177U,
		I2S1O_DATA_out12 = 178U,
		I2S1O_DATA_out13 = 179U,
		I2S1O_DATA_out14 = 180U,
		I2S1O_DATA_out15 = 181U,
		I2S1O_DATA_out16 = 182U,
		I2S1O_DATA_out17 = 183U,
		I2S1O_DATA_out18 = 184U,
		I2S1O_DATA_out19 = 185U,
		I2S1O_DATA_out20 = 186U,
		I2S1O_DATA_out21 = 187U,
		I2S1O_DATA_out22 = 188U,
		I2S1O_DATA_out23 = 189U,
		U2TXD_out = 198U,
		U2RTS_out = 199U,
		emac_mdc_o = 200U,
		emac_mdo_o = 201U,
		emac_crs_o = 202U,
		emac_col_o = 203U,
		bt_audio0_irq = 204U,
		bt_audio1_irq = 205U,
		bt_audio2_irq = 206U,
		ble_audio0_irq = 207U,
		ble_audio1_irq = 208U,
		ble_audio2_irq = 209U,
		pcmfsync_out = 210U,
		pcmclk_out = 211U,
		pcmdout = 212U,
		ble_audio_sync0_p = 213U,
		ble_audio_sync1_p = 214U,
		ble_audio_sync2_p = 215U,
		sig_in_func224 = 224U,
		sig_in_func225 = 225U,
		sig_in_func226 = 226U,
		sig_in_func227 = 227U,
		sig_in_func228 = 228U,
}Port_Output_PinInitialMode;
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
typedef struct
{
	uint8 pin_num;						/* PORT_Pin0, PORT_Pin1, ... , PORT_Pin38, PORT_Pin39*/
	Port_PinDirectionType direction;	/* PORT_PIN_IN, PORT_PIN_OUT ,PORT_PIN_OUT_Periph	*/
	Port_InternalResistor resistor;		/* OFF,PULL_UP,PULL_DOWN 							*/
	Port_PinLevelValue initial_value;	/* PORT_PIN_LEVEL_LOW,PORT_PIN_LEVEL_HIGH 			*/
	Port_FUNC_IN_Config func_InConfig;	/* a const_HighInput or a const_LowInput    		*/
	Port_PinDrive PinDrive;				/*0: normal output; 1: open drain output			*/
	Port_DriveStrength DriveStrength;	/*Select the drive strength of the pad. [0-3]A higher value corresponds with a higher strength.*/
	Port_Input_PinInitialMode initial_Input_mode;	/* e.g. Port_Input_PinInitialMode 		*/
	Port_Output_PinInitialMode initial_Output_mode;	/* e.g. Port_Output_PinInitialMode 		*/
	Port_SIG_IN_Config SIG_IN_Config;	/*Bypass the GPIO Matrix. 1: route through GPIO Matrix, 0: connect signal directly to peripheral configured in the IO_MUX*/
	Port_IO_MUX_PathSelection IO_MUX_Selection;/*Select the IO_MUX function for this signal		*/
	uint8 pin_dir_changeable;			/* STD_ON,STD_OFF 									*/
	uint8 pin_mode_changeable;			/* STD_ON,STD_OFF 									*/
}Port_ConfigPin;

/* Array of Port_ConfigPin */
typedef struct
{
	Port_ConfigPin Pin[PORT_CONFIGURED_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port Driver module.
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr );

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number , Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void);

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number, Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode, boolean dir);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Post build structure used with Port_Init API */
extern const Port_ConfigType Port_PinConfig;
/*this array use to map the address of the IO_MUX continuously without the need of calling every one independently*/
extern const uint32 PinIndex_to_IO_MUX_PinIndex[PORT_CONFIGURED_PINS];
/*this array use to store the pins which will be left without configuration*/
const uint8 Banned_Pins[PORT_BANNED_PINS];
#endif /* PORT_H */
