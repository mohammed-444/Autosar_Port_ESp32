 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for esp32 Microcontroller - Port Driver.
 *
 * Author: Mohammed Alaa
 ******************************************************************************/

#include "Port.h"
#include "Port_MemMap.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "../../utilities/Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------ACCESSING REGISTER FUNCTIONS----------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/* Set the IO_MUX_x_REG register corresponding to GPIO pad X. Enable the input by setting the FUN_IE bit.*/
LOCAL_INLINE void Input_Enable(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/************************************************************************************
	* Parameters (reg): the register as type uint32 (IO_MUX_REG(n))
	* Parameters (start_position): the bit number to write in(FUN_IE).
	* Return value: None
	* Description: set the bit selected to 1.
	************************************************************************************/
	SET_BIT(REG(PinIndex_to_IO_MUX_PinIndex[ConfigPtr->Pin[index].pin_num]),FUN_IE_BIT_START_POSITION);

}

/* Set the IO_MUX_x_REG register corresponding to GPIO pad X. Disable the input by setting the FUN_IE bit.*/
LOCAL_INLINE void Input_Disable(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/************************************************************************************
	* Parameters (reg): the register as type uint32 (IO_MUX_REG(n))
	* Parameters (start_position): the bit number to write in(FUN_IE).
	* Return value: None
	* Description: set the bit selected to 0.
	************************************************************************************/
	CLEAR_BIT(REG(PinIndex_to_IO_MUX_PinIndex[ConfigPtr->Pin[index].pin_num]),FUN_IE_BIT_START_POSITION);

}


/* If the signal should always be enabled as an output, set the GPIO_FUNCx_OEN_SEL bit in the GPIO_FUN Cx_OUT_SEL_CFG register
 * and the GPIO_ENABLE_DATA[x] field in the GPIO_ENABLE_REG register corresponding to GPIO pad X*/
LOCAL_INLINE void Output_Enable(Port_PinType index,const Port_ConfigType* ConfigPtr){

	/*set the GPIO_FUNCx_OEN_SEL bit in the GPIO_FUN Cx_OUT_SEL_CFG register*/

	/************************************************************************************
	* Parameters (reg): the register as type uint32 (GPIO_FUNC_OUT_SEL_CFG_REG(n))
	* Parameters (start_position): the bit number to write in(GPIO_FUNCx_OEN_SEL).
	* Return value: None
	* Description: set the bit selected to 1.
	************************************************************************************/

	SET_BIT(REG(GPIO_FUNC_OUT_SEL_CFG_REG(ConfigPtr->Pin[index].pin_num)),GPIO_FUNC_OEN_SEL_START_POSITION);

	/*Set the GPIO_ENABLE_DATA[x] field in the GPIO_ENABLE_REG register corresponding to GPIO pad X*/
	if((ConfigPtr->Pin[index].pin_num)<REG_SIZE)
	{
		/************************************************************************************
		* Parameters (reg): the register as type uint32 (GPIO_ENABLE_REG(n))
		* Parameters (start_position): the bit number to write in(the pin number).
		* Return value: None
		* Description: set the bit selected to 1.
		************************************************************************************/

		SET_BIT(REG(GPIO_ENABLE_REG),ConfigPtr->Pin[index].pin_num);
	}
	else if((ConfigPtr->Pin[index].pin_num)<PORT_CONFIGURED_PINS)

	{	/************************************************************************************
		* Parameters (reg): the register as type uint32 (GPIO_ENABLE1_REG(n))
		* Parameters (start_position): the bit number to write in(the pin number).
		* Return value: None
		* Description: set the bit selected to 1.
		************************************************************************************/
		SET_BIT(REG(GPIO_ENABLE1_REG),(ConfigPtr->Pin[index].pin_num)-REG_SIZE);
	}
	else
	{
		/*Do nothing*/
	}
}



/*Configure the GPIO_FUNCx_OUT_SEL_CFG register and clear the GPIO_ENABLE_DATA[x] field corresponding to GPIO pad X in the GPIO Matrix:
• Set the GPIO_FUNCx_OEN_SEL bit in the GPIO_FUNCx_OUT_SEL_CFG register to force the pin’s
	output state to be determined always by the GPIO_ENABLE_DATA[x] field.
• The GPIO_ENABLE_DATA[x] field is a bit in either GPIO_ENABLE_REG (GPIOs 0-31) or GPIO_ENABLE1_REG
	(GPIOs 32-39). Clear this bit to disable the output driver for the GPIO pad*/
LOCAL_INLINE void Output_Disable(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/*Set the GPIO_FUNCx_OEN_SEL bit in the GPIO_FUNCx_OUT_SEL_CFG register to force the pin’s
	output state to be determined always by the GPIO_ENABLE_DATA[x] field.*/
	/************************************************************************************
	* Parameters (reg): the register as type uint32 (GPIO_FUNC_OUT_SEL_CFG_REG(n))
	* Parameters (start_position): the bit number to write in(GPIO_FUNCx_OEN_SEL).
	* Return value: None
	* Description: set the bit selected to 1.
	************************************************************************************/

	SET_BIT(REG(GPIO_FUNC_OUT_SEL_CFG_REG(ConfigPtr->Pin[index].pin_num)),GPIO_FUNC_OEN_SEL_START_POSITION);

	/*The GPIO_ENABLE_DATA[x] field is a bit in either GPIO_ENABLE_REG (GPIOs 0-31) or GPIO_ENABLE1_REG
	(GPIOs 32-39). Clear this bit to disable the output driver for the GPIO pad*/
	if((ConfigPtr->Pin[index].pin_num)<REG_SIZE)
	{/************************************************************************************
		* Parameters (reg): the register as type uint32 (GPIO_ENABLE_REG(n))
		* Parameters (start_position): the bit number to write in(the pin number).
		* Return value: None
		* Description: set the bit selected to 0.
		************************************************************************************/
		CLEAR_BIT(REG(GPIO_ENABLE_REG),ConfigPtr->Pin[index].pin_num);
	}
	else if((ConfigPtr->Pin[index].pin_num)<PORT_CONFIGURED_PINS)
	{/************************************************************************************
		* Parameters (reg): the register as type uint32 (GPIO_ENABLE_REG(n))
		* Parameters (start_position): the bit number to write in(the pin number).
		* Return value: None
		* Description: set the bit selected to 0.
		************************************************************************************/
		CLEAR_BIT(REG(GPIO_ENABLE1_REG),(ConfigPtr->Pin[index].pin_num)-REG_SIZE);
	}
	else
	{
		/*Do nothing*/
	}
}


/*To have the output enable signal decided by internal logic, clear the GPIO_FUNCx_OEN_SEL bit instead.*/
LOCAL_INLINE void Output_DependOn_Periph(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/************************************************************************************
		* Parameters (reg): the register as type uint32 (GPIO_FUNC_OUT_SEL_CFG_REG(n))
		* Parameters (start_position): the bit number to write in(GPIO_FUNCx_OEN_SEL).
		* Return value: None
		* Description: set the bit selected to 0.
		************************************************************************************/

	CLEAR_BIT(REG(GPIO_FUNC_OUT_SEL_CFG_REG(ConfigPtr->Pin[index].pin_num)),GPIO_FUNC_OEN_SEL_START_POSITION);

}



LOCAL_INLINE void PullUp_Enable(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/************************************************************************************
	* Parameters (reg): the register as type uint32 (IO_MUX_REG(n))
	* Parameters (start_position): the bit number to write in (FUN_WPU_BIT).
	* Return value: None
	* Description: set the bit selected to 1.
	************************************************************************************/
	SET_BIT(REG(PinIndex_to_IO_MUX_PinIndex[ConfigPtr->Pin[index].pin_num]),FUN_WPU_BIT_START_POSITION);

}


LOCAL_INLINE void PullUp_Disable(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/************************************************************************************
	* Parameters (reg): the register as type uint32 (IO_MUX_REG(n))
	* Parameters (start_position): the bit number to write in (FUN_WPU_BIT).
	* Return value: None
	* Description: set the bit selected to 0.
	************************************************************************************/

	CLEAR_BIT(REG(PinIndex_to_IO_MUX_PinIndex[ConfigPtr->Pin[index].pin_num]),FUN_WPU_BIT_START_POSITION);

}



LOCAL_INLINE void PullDown_Enable(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/************************************************************************************
	* Parameters (reg): the register as type uint32 (IO_MUX_REG(n))
	* Parameters (start_position): the bit number to write in (FUN_WPD_BIT).
	* Return value: None
	* Description: set the bit selected to 1.
	************************************************************************************/
	SET_BIT(REG(PinIndex_to_IO_MUX_PinIndex[ConfigPtr->Pin[index].pin_num]),FUN_WPD_BIT_START_POSITION);

}


LOCAL_INLINE void PullDown_Disable(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/************************************************************************************
	* Parameters (reg): the register as type uint32 (IO_MUX_REG(n))
	* Parameters (start_position): the bit number to write in (FUN_WPD_BIT).
	* Return value: None
	* Description: set the bit selected to 0.
	************************************************************************************/

	CLEAR_BIT(REG(PinIndex_to_IO_MUX_PinIndex[ConfigPtr->Pin[index].pin_num]),FUN_WPD_BIT_START_POSITION);

}



/*write in the GPIO_OUT_REG to set high output or low*/
LOCAL_INLINE void PinLevelValue(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/************************************************************************************
	* Parameters (reg): the register as type uint32 (GPIO_OUT_REG)
	* Parameters (interval_size): 1
	* Parameters (start_position): the bit number to write in (pin number).
	* Parameters (value): initial_value
	* Return value: None
	* Description: Write a region without affecting other region.
	************************************************************************************/

	if((ConfigPtr->Pin[index].pin_num)<REG_SIZE)
	{
		WRITE_REGION(REG(GPIO_OUT_REG),BIT_INTERVAL_SIZE,(ConfigPtr->Pin[index].pin_num),(ConfigPtr->Pin[index].initial_value));
	}
	else if((ConfigPtr->Pin[index].pin_num)<PORT_CONFIGURED_PINS)
	{
		WRITE_REGION(REG(GPIO_OUT1_REG),BIT_INTERVAL_SIZE,(ConfigPtr->Pin[index].pin_num)-REG_SIZE,(ConfigPtr->Pin[index].initial_value));
	}
	else
	{
		/*Do nothing*/
	}
}

/*For an open drain output, set the GPIO_PINx_PAD_DRIVER bit in the GPIO_PINx register corresponding to GPIO pad X.
 For push/pull mode (default), clear this bit*/
LOCAL_INLINE void PinDrive(Port_PinType index,const Port_ConfigType* ConfigPtr){


	if((ConfigPtr->Pin[index].PinDrive)==PORT_NORMAL_MODE)
	{
		/************************************************************************************
		* Parameters (reg): the register as type uint32 (GPIO_PIN_REG(n))
		* Parameters (start_position): the bit number to write in (GPIO_PINx_PAD_DRIVER bit).
		* Return value: None
		* Description: set the bit selected to 0.
		************************************************************************************/
		CLEAR_BIT(REG(GPIO_PIN_REG(ConfigPtr->Pin[index].pin_num)),GPIO_PIN_DRIVER_BIT_START_POSITION);
	}
	else if((ConfigPtr->Pin[index].PinDrive)==PORT_OPEN_DRAIN_MODE)
	{
		/************************************************************************************
		* Parameters (reg): the register as type uint32 (GPIO_PIN_REG(n))
		* Parameters (start_position): the bit number to write in (GPIO_PINx_PAD_DRIVER bit).
		* Return value: None
		* Description: set the bit selected to 1.
		************************************************************************************/
		SET_BIT(REG(GPIO_PIN_REG(ConfigPtr->Pin[index].pin_num)),GPIO_PIN_DRIVER_BIT_START_POSITION);
	}
	else
	{
		/*DO nothing*/
	}
}

/*• Set the FUN_DRV field to the desired value for output strength (0-3). The higher the drive strength, the
more current can be sourced/sunk from the pin.*/
LOCAL_INLINE void DriveStrength(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/************************************************************************************
	* Parameters (reg): the register as type uint32 (IO_MUX_REG(n))
	* Parameters (interval_size): 2
	* Parameters (start_position): the bit number to write in (FUN_DRV bit 10).
	* Parameters (value): initial_value
	* Return value: None
	* Description:Write a region without affecting other region.
	************************************************************************************/

	WRITE_REGION(REG(PinIndex_to_IO_MUX_PinIndex[ConfigPtr->Pin[index].pin_num]),FUN_DRV_BIT_INTERVAL_SIZE,FUN_DRV_BIT_START_POSITION,ConfigPtr->Pin[index].DriveStrength);
}


/* Configure the GPIO_FUNCy_IN_SEL_CFG register corresponding to peripheral signal Y in the GPIO Matrix:
• Set the GPIO_FUNCy_IN_SEL field in this register, corresponding to the GPIO pad X to read from.*/
LOCAL_INLINE void Input_PinInitialMode(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/************************************************************************************
	* Parameters (reg): the register as type uint32 (GPIO_FUNC_IN_SEL_CFG_REG)
	* Parameters (interval_size): 6
	* Parameters (start_position): the bits number to write in (GPIO_FUNCy_IN_SEL) start from 0.
	* Parameters (value): pin number
	* Return value: None
	* Description: Write a region without affecting other region.
	************************************************************************************/
	if((ConfigPtr->Pin[index].func_InConfig) == Func_dependant)
	{
	/*Set the GPIO_FUNCy_IN_SEL field in this register, corresponding to the GPIO pad X to read from.*/
	WRITE_REGION(REG(GPIO_FUNC_IN_SEL_CFG_REG(ConfigPtr->Pin[index].initial_Input_mode)),GPIO_FUNC_IN_SEL_INTERVAL_SIZE,GPIO_FUNC_IN_SEL_START_POSITION,ConfigPtr->Pin[index].pin_num);
	}
	else if(((ConfigPtr->Pin[index].func_InConfig) == const_LowInput)||((ConfigPtr->Pin[index].func_InConfig) == const_HighInput))
	{
		/*0x38 for a constantly high input or 0x30 for a constantly low input */
	WRITE_REGION(REG(GPIO_FUNC_IN_SEL_CFG_REG(ConfigPtr->Pin[index].initial_Input_mode)),GPIO_FUNC_IN_SEL_INTERVAL_SIZE,GPIO_FUNC_IN_SEL_START_POSITION,ConfigPtr->Pin[index].func_InConfig);
	}
	else
	{
		/*Do nothing*/
	}
}

/* Set the GPIO_FUNCx_OUT_SEL field in GPIO_FUNCx_OUT_SEL_CFG to the numeric index (Y) of desired peripheral output signal Y.*/
LOCAL_INLINE void Output_PinInitialMode(Port_PinType index,const Port_ConfigType* ConfigPtr){

	/************************************************************************************
	* Parameters (reg): the register as type uint32 (GPIO_FUNC_IN_SEL_CFG_REG)
	* Parameters (interval_size): 6
	* Parameters (start_position): the bits number to write in (GPIO_FUNCy_IN_SEL) start from 0.
	* Parameters (value): initial_Output_mode
	* Return value: None
	* Description: Write a region without affecting other region.
	************************************************************************************/
	WRITE_REGION(REG(GPIO_FUNC_OUT_SEL_CFG_REG(ConfigPtr->Pin[index].pin_num)),GPIO_FUNC_OUT_SEL_INTERVAL_SIZE,GPIO_FUNC_OUT_SEL_START_POSITION,ConfigPtr->Pin[index].initial_Output_mode);

}


/*Bypass the GPIO Matrix. 1: route through GPIO Matrix, 0: connect signal directly to peripheral configured in the IO_MUX*/
LOCAL_INLINE void SIG_IN_Config(Port_PinType index,const Port_ConfigType* ConfigPtr){


	if((ConfigPtr->Pin[index].SIG_IN_Config)==IO_MUX)
	{
		/************************************************************************************
		* Parameters (reg): the register as type uint32 (GPIO_FUNC_IN_SEL_CFG_REG(n))
		* Parameters (start_position): the bit number to write in (GPIO_SIG_IN_SEL bit).
		* Return value: None
		* Description: set the bit selected to 0.
		************************************************************************************/
		CLEAR_BIT(REG(GPIO_FUNC_IN_SEL_CFG_REG(ConfigPtr->Pin[index].initial_Input_mode)),GPIO_SIG_IN_SEL_START_POSITION);
	}
	else if((ConfigPtr->Pin[index].SIG_IN_Config)==GPIO_Matrix)
	{
		/************************************************************************************
		* Parameters (reg): the register as type uint32 (GPIO_FUNC_IN_SEL_CFG_REG(n))
		* Parameters (start_position): the bit number to write in (GPIO_SIG_IN_SEL bit).
		* Return value: None
		* Description: set the bit selected to 1.
		************************************************************************************/
		SET_BIT(REG(GPIO_FUNC_IN_SEL_CFG_REG(ConfigPtr->Pin[index].initial_Input_mode)),GPIO_SIG_IN_SEL_START_POSITION);
	}
	else
	{
		/*Do nothing*/
	}
}


/*Select the IO_MUX function for this signal. 0 selects Function 0, 1 selects Function 1, etc
 * look at Technical Reference Manual at table 4-3 page 57*/
LOCAL_INLINE void IO_MUX_PathSelection(Port_PinType index,const Port_ConfigType* ConfigPtr){
	/************************************************************************************
	* Parameters (reg): the register as type uint32 (GPIO_FUNC_IN_SEL_CFG_REG)
	* Parameters (interval_size): 3
	* Parameters (start_position): the bits number to write in (MCU_SEL).
	* Parameters (value):IO_MUX function Selection
	* Return value: None
	* Description: Write a region without affecting other region.
	************************************************************************************/

	WRITE_REGION(REG(PinIndex_to_IO_MUX_PinIndex[ConfigPtr->Pin[index].pin_num]),MCU_SEL_BIT_INTERVAL_SIZE,MCU_SEL_BIT_START_POSITION,ConfigPtr->Pin[index].IO_MUX_Selection);

}


/* This function check if the wanted pin is in the banned pins array or n't if it is in the array it will activate the flag */
LOCAL_INLINE void Banned_Pins_Checking(Port_PinType index,const Port_ConfigType* ConfigPtr,uint8* flag){

	*flag = STD_IDLE;

	for (uint8 var = 0; var < PORT_BANNED_PINS; ++var) {

		if( (ConfigPtr->Pin[index].pin_num)== Banned_Pins[var])
		{
			*flag = STD_ACTIVE;
		}
		else
		{
			/*Do nothing*/
		}
	}

}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------To read GPIO pad X into peripheral signal Y, follow the steps below:---------------------------------------*/

/*1. Configure the GPIO_FUNCy_IN_SEL_CFG register corresponding to peripheral signal Y in the GPIO Matrix:
	• Set GPIO_SIGy_IN_SEL to enable peripheral signal input via GPIO matrix.
	• Set the GPIO_FUNCy_IN_SEL field in this register, corresponding to the GPIO pad X to read from.

2. Configure the GPIO_FUNCx_OUT_SEL_CFG register and clear the GPIO_ENABLE_DATA[x] field corresponding to GPIO pad X in the GPIO Matrix:
	• Set the GPIO_FUNCx_OEN_SEL bit in the GPIO_FUNCx_OUT_SEL_CFG register to force the pin’s
	output state to be determined always by the GPIO_ENABLE_DATA[x] field.
	• The GPIO_ENABLE_DATA[x] field is a bit in either GPIO_ENABLE_REG (GPIOs 0-31) or GPIO_ENABLE1_REG
	(GPIOs 32-39). Clear this bit to disable the output driver for the GPIO pad.

3. Configure the IO_MUX to select the GPIO Matrix. Set the IO_MUX_x_REG register corresponding to GPIO
pad X as follows:
	• Set the function field (MCU_SEL) to the IO_MUX function corresponding to GPIO X (this is Function
	2—numeric value 2—for all pins).
	• Enable the input by setting the FUN_IE bit.
	• Set or clear the FUN_WPU and FUN_WPD bits, as desired, to enable/disable internal pull-up/pull-down
	resistors.
	*/

/*------------------------------------------------------------------Simple GPIO Input---------------------------------------------------------------------------------*/

/*The GPIO_IN_REG/GPIO_IN1_REG register holds the input values of each GPIO pad. The input value of any GPIO pin can be read at any time
 * without configuring the GPIO Matrix for a particular peripheral signal. However, it is necessary to enable the input in the IO_MUX by
 * setting the FUN_IE bit in the IO_MUX_x_REG register corresponding to pad X, as mentioned in Section*/


/*  the code will be :
 *
 * 	Input_Enable();
 * 	Output_Disable();
 *
 *then read GPIO_IN_REG/GPIO_IN1_REG register
 * 	*/



/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------To output peripheral signal Y to particular GPIO pad X, follow these steps:----------------------------------------------*/

/*1. Configure the GPIO_FUNCx_OUT_SEL_CFG register and GPIO_ENABLE_DATA[x] field corresponding to
GPIO X in the GPIO Matrix:
	• Set the GPIO_FUNCx_OUT_SEL field in GPIO_FUNCx_OUT_SEL_CFG to the numeric index (Y) of desired peripheral output signal Y.
	• If the signal should always be enabled as an output, set the GPIO_FUNCx_OEN_SEL bit in the GPIO_FUN
	Cx_OUT_SEL_CFG register and the GPIO_ENABLE_DATA[x] field in the GPIO_ENABLE_REG register
	corresponding to GPIO pad X. To have the output enable signal decided by internal logic, clear the
	GPIO_FUNCx_OEN_SEL bit instead.
	• The GPIO_ENABLE_DATA[x] field is a bit in either GPIO_ENABLE_REG (GPIOs 0-31) or GPIO_ENABLE1
	_REG (GPIOs 32-39). Clear this bit to disable the output driver for the GPIO pad.

2. For an open drain output, set the GPIO_PINx_PAD_DRIVER bit in the GPIO_PINx register corresponding to
GPIO pad X. For push/pull mode (default), clear this bit.

3. Configure the IO_MUX to select the GPIO Matrix. Set the IO_MUX_x_REG register corresponding to GPIO
pad X as follows:
	• Set the function field (MCU_SEL) to the IO_MUX function corresponding to GPIO X (this is Function
	2—numeric value 2—for all pins).
	• Set the FUN_DRV field to the desired value for output strength (0-3). The higher the drive strength, the
	more current can be sourced/sunk from the pin.
	• If using open drain mode, set/clear the FUN_WPU and FUN_WPD bits to enable/disable the internal
	pull-up/down resistors*/

/*------------------------------------------------------------------Simple GPIO Output---------------------------------------------------------------------------------*/



/*The GPIO Matrix can also be used for simple GPIO output – setting a bit in the GPIO_OUT_DATA register will write to the corresponding GPIO pad.
To configure a pad as simple GPIO output, the GPIO Matrix GPIO_FUNCx_OUT_SEL register is configured with a special peripheral index value (0x100).*/


/*  the code will be :
 *
 * 	Output_Enable();
 * 	Input_Disable();
 *	PinLevelValue();
 *	Output_PinInitialMode();
 *	IO_MUX_PathSelection();
 * 	*/



/*------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Holds the status of the Port
 * options: 	PORT_NOT_INITIALIZED
 * 				PORT_INITIALIZED		( set by Port_Init() )
*/
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/* Holds the pointer of the Port_PinConfig */
STATIC const Port_ConfigType* Port_ConfigPtr = NULL_PTR;

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
void Port_Init(const Port_ConfigType* ConfigPtr)
{
	boolean error = FALSE;
	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* check if the input configuration pointer is not a NULL_PTR */
		if(ConfigPtr == NULL_PTR)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
			error = TRUE;
		}
		else
		{	/* Do Nothing */	}
	#endif

	Port_Status = PORT_INITIALIZED;
	Port_ConfigPtr = ConfigPtr;
	uint8 Banned_Pins_Flag = STD_IDLE;

if(FALSE == error){
	for(Port_PinType index = ZERO; index < PORT_CONFIGURED_PINS; index++)
	{


		/* This function check if the wanted pin is in the banned pins array or n't if it is in the array it will activate the flag */
		Banned_Pins_Checking(index,Port_ConfigPtr,&Banned_Pins_Flag);

		/* if the flag is 1 skip this pin and enter another loop*/
		if(Banned_Pins_Flag == STD_ACTIVE)
		{
			continue;
		}
		else
		{
			/*Do nothing*/
		}


		/*configure the pin direction*/
		switch (Port_ConfigPtr->Pin[index].direction)
		{

			case PORT_PIN_DISABLE:

				Input_Disable(index,Port_ConfigPtr);
				Output_Disable(index,Port_ConfigPtr);
				break;

			case PORT_PIN_IN:

				Input_Enable(index,Port_ConfigPtr);
				Output_Disable(index,Port_ConfigPtr);
				break;

			case PORT_PIN_OUT:

				Output_Enable(index,Port_ConfigPtr);
				Input_Disable(index,Port_ConfigPtr);
				break;

			case PORT_PIN_OUT_Periph:
				Output_DependOn_Periph(index,Port_ConfigPtr);
				Input_Disable(index,Port_ConfigPtr);
				break;

			case PORT_PIN_INPUT_OUTPUT:

				Input_Enable(index,Port_ConfigPtr);
				Output_Enable(index,Port_ConfigPtr);
				break;

			case PORT_PIN_INPUT_OUTPUT_Periph:

				Input_Enable(index,Port_ConfigPtr);
				Output_DependOn_Periph(index,Port_ConfigPtr);
				break;

			default:
				/*Do nothing*/
				break;
		}


		/* configure the pull up or pull down */
		switch (Port_ConfigPtr->Pin[index].resistor)
		{

			case OFF:

				PullUp_Disable(index,Port_ConfigPtr);
				PullDown_Disable(index,Port_ConfigPtr);
				break;

			case PULL_UP:

				PullUp_Enable(index,Port_ConfigPtr);
				PullDown_Disable(index,Port_ConfigPtr);
				break;

			case PULL_DOWN:

				PullUp_Disable(index,Port_ConfigPtr);
				PullDown_Enable(index,Port_ConfigPtr);
				break;

			default:
				/*Do nothing*/
				break;
		}

		/*Select the IO_MUX function for this signal. 0 selects Function 0, 1 selects Function 1, etc
		 * look at Technical Reference Manual at table 4-3 page 57*/
		IO_MUX_PathSelection(index,Port_ConfigPtr);

		/* Configure the GPIO_FUNCy_IN_SEL_CFG register corresponding to peripheral signal Y in the GPIO Matrix:
		• Set the GPIO_FUNCy_IN_SEL field in this register, corresponding to the GPIO pad X to read from.*/
		Input_PinInitialMode(index,Port_ConfigPtr);

		/*Bypass the GPIO Matrix for the input function. 1: route through GPIO Matrix, 0: connect signal directly to peripheral configured in the IO_MUX*/
		SIG_IN_Config(index,Port_ConfigPtr);

		/* Set the GPIO_FUNCx_OUT_SEL field in GPIO_FUNCx_OUT_SEL_CFG to the numeric index (Y) of desired peripheral output signal Y.*/
		Output_PinInitialMode(index,Port_ConfigPtr);

		/*For an open drain output, set the GPIO_PINx_PAD_DRIVER bit in the GPIO_PINx register corresponding to GPIO pad X.
		 For push/pull mode (default), clear this bit*/
		PinDrive(index,Port_ConfigPtr);

		/*• Set the FUN_DRV field to the desired value for output strength (0-3). The higher the drive strength, the
		more current can be sourced/sunk from the pin.*/
		DriveStrength(index,Port_ConfigPtr);

		/*write in the GPIO_OUT_REG to set high output or low*/
		PinLevelValue(index,Port_ConfigPtr);
	}

}
else{
	/*Do nothing*/
}

}


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
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
	boolean error = FALSE;
	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* Check if the Driver is initialized before using this function */
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_UNINIT);
			error = TRUE;
		}
		else
		{	/* Do Nothing */	}

		/* check if incorrect Port Pin ID passed */
		if(Pin >= PORT_CONFIGURED_PINS)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_PARAM_PIN);
			error = TRUE;
		}
		else
		{	/* Do Nothing */	}

		/* check if Port Pin not configured as changeable */
		if(Port_ConfigPtr->Pin[Pin].pin_dir_changeable == STD_OFF)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_DIRECTION_UNCHANGEABLE);
			error = TRUE;
		}
		else
		{	/* Do Nothing */	}
	#endif
if(FALSE == error){
		uint8 Banned_Pins_Flag = STD_IDLE;


			/* This function check if the wanted pin is in the banned pins array or n't if it is in the array it will activate the flag */
			Banned_Pins_Checking(Pin,Port_ConfigPtr,&Banned_Pins_Flag);

			/* if the flag is 0 then the Pin is n't banned*/
			if(Banned_Pins_Flag == STD_IDLE)
			{
				/*configure the pin direction*/
				switch (Direction)
				{

					case PORT_PIN_DISABLE:

						Input_Disable(Pin,Port_ConfigPtr);
						Output_Disable(Pin,Port_ConfigPtr);
						break;

					case PORT_PIN_IN:

						Input_Enable(Pin,Port_ConfigPtr);
						Output_Disable(Pin,Port_ConfigPtr);
						break;

					case PORT_PIN_OUT:

						Output_Enable(Pin,Port_ConfigPtr);
						Input_Disable(Pin,Port_ConfigPtr);
						break;

					case PORT_PIN_OUT_Periph:
						Output_DependOn_Periph(Pin,Port_ConfigPtr);
						Input_Disable(Pin,Port_ConfigPtr);
						break;

					case PORT_PIN_INPUT_OUTPUT:

						Input_Enable(Pin,Port_ConfigPtr);
						Output_Enable(Pin,Port_ConfigPtr);
						break;

					case PORT_PIN_INPUT_OUTPUT_Periph:

						Input_Enable(Pin,Port_ConfigPtr);
						Output_DependOn_Periph(Pin,Port_ConfigPtr);
						break;

					default:
						/*Do nothing*/
						break;
				}
			}
			else
			{
				/*Do nothing*/
			}
}
else
{
	/*Do nothing*/
}

}
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
void Port_RefreshPortDirection(void)
{
	boolean error =FALSE;
	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* Check if the Driver is initialized before using this function */
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIR_SID, PORT_E_UNINIT);
			error = TRUE;
		}
		else
		{	/* Do Nothing */	}
	#endif
if(FALSE == error){
	uint8 Banned_Pins_Flag = STD_IDLE;

	for(Port_PinType index = ZERO; index < PORT_CONFIGURED_PINS; index++)
		{


		/* This function check if the wanted pin is in the banned pins array or n't if it is in the array it will activate the flag */
		Banned_Pins_Checking(index,Port_ConfigPtr,&Banned_Pins_Flag);

		/* if the flag is 1 skip this pin and enter another loop*/
		if(Banned_Pins_Flag == STD_ACTIVE)
		{
			continue;
		}
		else
		{
			/*Do nothing*/
		}




			/* PORT061: The function Port_RefreshPortDirection shall exclude those port pins from
			 * refreshing that are configured as �pin direction changeable during runtime� */
			if (Port_ConfigPtr->Pin[index].pin_dir_changeable == STD_ON)
			{
				/*configure the pin direction*/
				switch (Port_ConfigPtr->Pin[index].direction)
				{

					case PORT_PIN_DISABLE:

						Input_Disable(index,Port_ConfigPtr);
						Output_Disable(index,Port_ConfigPtr);
						break;

					case PORT_PIN_IN:

						Input_Enable(index,Port_ConfigPtr);
						Output_Disable(index,Port_ConfigPtr);
						break;

					case PORT_PIN_OUT:

						Output_Enable(index,Port_ConfigPtr);
						Input_Disable(index,Port_ConfigPtr);
						break;

					case PORT_PIN_OUT_Periph:
						Output_DependOn_Periph(index,Port_ConfigPtr);
						Input_Disable(index,Port_ConfigPtr);
						break;

					case PORT_PIN_INPUT_OUTPUT:

						Input_Enable(index,Port_ConfigPtr);
						Output_Enable(index,Port_ConfigPtr);
						break;

					case PORT_PIN_INPUT_OUTPUT_Periph:

						Input_Enable(index,Port_ConfigPtr);
						Output_DependOn_Periph(index,Port_ConfigPtr);
						break;

					default:
						/*Do nothing*/
						break;
				}
			}
			else
			{	/* Do Nothing */	}
		}

}
else
{	/* Do Nothing */	}
}

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
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* check if the input configuration pointer is not a NULL_PTR */
		if(versioninfo == NULL_PTR)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);

		}
		else
		{	/* Do Nothing */	}

		/* Check if the Driver is initialized before using this function */
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);

		}
		else
		{	/* Do Nothing */	}
	#endif

		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
}
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
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode, boolean dir)
{
	boolean error = FALSE;
	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* Check if the Driver is initialized before using this function */
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
			error = TRUE;
		}
		else
		{	/* Do Nothing */	}

		/* check if incorrect Port Pin ID passed */
		if(Pin >= PORT_CONFIGURED_PINS)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
			error = TRUE;
		}
		else
		{	/* Do Nothing */	}

		/* check if the Port Pin Mode passed not valid */
		if(Mode > PORT_MAX_MODE_SIZE)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
			error = TRUE;
		}
		else
		{	/* Do Nothing */	}

		/* check if the API called when the mode is unchangeable */
		if(Port_ConfigPtr->Pin[Pin].pin_mode_changeable == STD_OFF)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
			error = TRUE;
		}
		else
		{
			/* Do Nothing */
		}
	#endif
if(FALSE == error){
		uint8 Banned_Pins_Flag = STD_IDLE;


			/* This function check if the wanted pin is in the banned pins array or n't if it is in the array it will activate the flag */
			Banned_Pins_Checking(Pin,Port_ConfigPtr,&Banned_Pins_Flag);

			/* if the flag is 0 then the Pin is n't banned*/
			if(Banned_Pins_Flag == STD_IDLE)
			{
				if(dir == INPUT)
				{
					/* Configure the GPIO_FUNCy_IN_SEL_CFG register corresponding to peripheral signal Y in the GPIO Matrix:
					• Set the GPIO_FUNCy_IN_SEL field in this register, corresponding to the GPIO pad X to read from.*/

					WRITE_REGION(REG(GPIO_FUNC_IN_SEL_CFG_REG(Mode)),GPIO_FUNC_IN_SEL_INTERVAL_SIZE,GPIO_FUNC_IN_SEL_START_POSITION,Pin);
				}
				else if(dir == OUTPUT)
				{
					/************************************************************************************
					* Parameters (reg): the register as type uint32 (GPIO_FUNC_IN_SEL_CFG_REG)
					* Parameters (interval_size): 6
					* Parameters (start_position): the bits number to write in (GPIO_FUNCy_IN_SEL) start from 0.
					* Parameters (value): initial_Output_mode
					* Return value: None
					* Description: Write a region without affecting other region.
					************************************************************************************/
					WRITE_REGION(REG(GPIO_FUNC_OUT_SEL_CFG_REG(Pin)),GPIO_FUNC_OUT_SEL_INTERVAL_SIZE,GPIO_FUNC_OUT_SEL_START_POSITION,Mode);

				}
				else
				{
					/* Do Nothing */
				}
			}
			else
			{
				/* Do Nothing */
			}

}
else
{
	/* Do Nothing */
}

}
#endif




