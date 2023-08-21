 /******************************************************************************
 *
 * Module: PORT
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for esp32 - Port Driver
 *
 * Author: Mohammed Alaa
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT               (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API               (STD_ON)

/* Pre-compile option for presence of Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API			(STD_ON)

/* Pre-compile option for presence of Port_SetPinMode API */
#define PORT_SET_PIN_MODE_API				(STD_ON)

/* Number of PINS */
#define PORT_CONFIGURED_PINS				(40U)

#define PORT_BANNED_PINS					(20U)

#define PORT_MAX_MODE_SIZE                  (255U)

#define INPUT                               (0U)

#define OUTPUT                              (1U)

#define ZERO 	(0U)
/* esp32 Pins */
#define PORT_Pin0                	(0U)
#define PORT_Pin1                	(1U)
#define PORT_Pin2                	(2U)
#define PORT_Pin3                	(3U)
#define PORT_Pin4                	(4U)
#define PORT_Pin5                	(5U)
#define PORT_Pin6                	(6U)
#define PORT_Pin7                	(7U)
#define PORT_Pin8                	(8U)
#define PORT_Pin9                	(9U)
#define PORT_Pin10                	(10U)
#define PORT_Pin11                	(11U)
#define PORT_Pin12               	(12U)
#define PORT_Pin13               	(13U)
#define PORT_Pin14               	(14U)
#define PORT_Pin15                	(15U)
#define PORT_Pin16                	(16U)
#define PORT_Pin17                	(17U)
#define PORT_Pin18               	(18U)
#define PORT_Pin19               	(19U)
#define PORT_Pin20               	(20U)
#define PORT_Pin21                	(21U)
#define PORT_Pin22               	(22U)
#define PORT_Pin23                	(23U)
#define PORT_Pin24                	(24U)
#define PORT_Pin25               	(25U)
#define PORT_Pin26                	(26U)
#define PORT_Pin27                	(27U)
#define PORT_Pin28               	(28U)
#define PORT_Pin29                	(29U)
#define PORT_Pin30               	(30U)
#define PORT_Pin31                	(31U)
#define PORT_Pin32                	(32U)
#define PORT_Pin33                	(33U)
#define PORT_Pin34               	(34U)
#define PORT_Pin35                	(35U)
#define PORT_Pin36                	(36U)
#define PORT_Pin37                	(37U)
#define PORT_Pin38                	(38U)
#define PORT_Pin39                	(39U)

#endif /* PORT_CFG_H */
