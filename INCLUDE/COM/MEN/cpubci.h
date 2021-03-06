/***********************  I n c l u d e  -  F i l e  ************************/
/*!  
 *        \file  cpubci.h
 *
 *      \author  matthias.soehnlein@men.de
 * 
 *       \brief  Header file for CPU board-controller firmware interface
 *                      
 *     Switches: -
 */
/*
 *---------------------------------------------------------------------------
 * Copyright 2009-2019, MEN Mikro Elektronik GmbH
 ****************************************************************************/
/*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _CPUBCI_H
#define _CPUBCI_H

#ifdef __cplusplus
    extern "C" {
#endif


/*--------------------------------------+
|   DEFINES                             |
+--------------------------------------*/
/**
 * @defgroup _SMBCMDS firmware SMB-Cmds
 * Note:\n
 *   - (C / B / W) indicates Cmd only / Cmd+Byte / Cmd+Word access
 *   - (r / w) indicates read/write access
 * @{ */


/* 0x11 */
#define CPUBCI_WDOG_ON            (0x11)    /**< Watchdog ON (C) */

/* 0x12 */
#define CPUBCI_WDOG_OFF           (0x12)    /**< Watchdog OFF (Bw) */
#define CPUBCI_WDOG_OFF_BYTE      (0x69)    /**< Watchdog OFF keyword */

/* 0x13 */
#define CPUBCI_WDOG_TRIG          (0x13)    /**< Watchdog trigger (C) */

/* 0x14 */
#define CPUBCI_WDOG_TIME          (0x14)    /**< Get/Set Watchdog time (Wr / Ww) */
#define CPUBCI_WDOG_TIME_UNIT      (100)    /**< Unit of time in ms */
#define CPUBCI_WDOG_TIME_MIN    (0x0001)    /**< Watchdog min time */
#define CPUBCI_WDOG_TIME_MAX    (0xFFFF)    /**< Watchdog max time */

/* 0x17 */
#define CPUBCI_WDOG_STATE         (0x17)    /**< Get watchdog state, 0=OFF / 1=ON (Br) */

/* 0x18 */
#define CPUBCI_WDOG_ARM           (0x18)    /**< Arm watchdog (C) */

/* 0x19 */
#define CPUBCI_WDOG_ARM_STATE     (0x19)    /**< Get Watchdog Arming State (Br) */

/* 0x20 */
#define CPUBCI_RESUME_MODE        (0x20)    /**< Get/Set power resume mode (Br / Bw) */

/* 0x21 */
#define CPUBCI_EXT_PWR_OK_MODE    (0x21)    /**< Get/Set EXT_PWR_OK mode (Br / Bw) */
#define CPUBCI_EXT_PWR_OK_IGN     (0x00)    /**< Ignore EXT_PWR_OK failure */
#define CPUBCI_EXT_PWR_OK_ERR     (0x01)    /**< Treat EXT_PWR_OK failure as error */

/* 0x22 */
#define CPUBCI_RST_IN_MODE        (0x22)    /**< Get/Set RESET_IN Mode (Br / Bw) */
#define CPUBCI_RST_IN_ENABLED     (0x00)    /**< RESET_IN enabled */
#define CPUBCI_RST_IN_BLOCKED     (0x01)    /**< RESET_IN blocked */

/* 0x23 */
#define CPUBCI_EXT_PS_ON_MODE     (0x23)    /**< Get/Set EXT_PS_ON Mode (Br / Bw) */

/* 0x2F */
#define CPUBCI_DBG_MODE           (0x2F)    /**< Debugging mode (Br / Bw) */

/* 0x31 */
#define CPUBCI_SW_RESET           (0x31)    /**< Software reset (Ww) */

/* 0x32 */
#define CPUBCI_SW_COLD_RESET    (0x32)    	/**< Software cold reset (Ww) */
#define CPUBCI_SW_RESET_WORD    (0xdead)  	/**< Software reset keyword */

/* 0x33 */
#define CPUBCI_PWRBTN           (0x33)    	/**< Press power button (Bw) */
#define CPUBCI_PWRBTN_BYTE      (0x69)    	/**< Press power button keyword */

/* 0x34 */
#define CPUBCI_PWRBTN_OVRD      (0x34)    	/**< Power button override (Bw) */

/* 0x35 */
#define CPUBCI_SW_RTC_RESET     (0x35)    	/**< Software cold reset with 
																								 RTC Reset (Ww) */
/* 0x40 */
#define CPUBCI_VOLT_LOW(c)    	(0x40+(c))	/**< Get voltage lower bounds in mV
                                                 or 0 if not supported (Wr)
                                                 Note: c=0..CPUBCI_VOLT_NUM-1 */
/* 0x50 */
#define CPUBCI_VOLT_HIGH(c)   	(0x50+(c))  /**< Get voltage upper bounds in mV 
                                                 or 0 if not supported (Wr)
                                                 Note: c=0..CPUBCI_VOLT_NUM-1 */
/* 0x60 */
#define CPUBCI_VOLT_ACT(c)    	(0x60+(c))  /**< Get actual voltages in mV (Wr)
                                                 Note: c=0..CPUBCI_VOLT_NUM-1 */

/* 0x70 */
#define CPUBCI_ERRCNT_1(ec)  		(0x70+(ec)) /**< Get error counter 1 (Br)
                                                 Note: ec=0..CPUBCI_ERRCNT_NUM-1 */

/* 0x7F */
#define CPUBCI_ERR_CNT_CLR      (0x7f)    /**< Clear all error counters (C) */
#define CPUBCI_ERR_CNT_BYTE     (0x69)    /**< Clear all error counters keyword */

/* 0x80 */
#define CPUBCI_GETREV(fww)  (0x80+(fww))  /**< Get Firmware revision word (Wr) 
                                               Note: fww=0..CPUBCI_GETREV_NUM-1 */
/* 0x8B */
#define CPUBCI_BOARD_MODE       (0x8b)    /**< Get board mode (master/ slave) (Br) */

/* 0x8C */
#define CPUBCI_GA_ADDRESS       (0x8c)    /**< Get backplane slot geographical address (Br) */

/* 0x8D */
#define CPUBCI_NUM_ERR_CNTRS    (0x8d)    /**< Get number of error counters (Br) */

/* 0x8E */
#define CPUBCI_NUM_VOLTS        (0x8e)    /**< Get number of supervised voltages (Br) */

/* 0x8F */
#define CPUBCI_HW_VARIANT       (0x8f)    /**< Get hardware variant (Br) */

/* 0x90 */
#define CPUBCI_ERR_LAST         (0x90)    /**< Get last error (Br) */

/* 0x91 */
#define CPUBCI_ERR_PWR_FLAGS    (0x91)    /**< Get last power failure flags (Wr) */

/* 0x92 */
#define CPUBCI_ERR_RST_RSN      (0x92)    /**< Get last reset reason (Br) */

/* 0x93 */
#define CPUBCI_PWRCYCL_CNT      (0x93)    /**< Get number of power cycles (Wr) */

/* 0x94 */
#define CPUBCI_OPHRS_CNT        (0x94)    /**< Get number of operating hours (Wr) */

/* 0x9F */
#define CPUBCI_ERR_REG_CLR      (0x9f)    /**< Clear last error/flags registers (C) */
#define CPUBCI_ERR_REG_BYTE     (0x69)    /**< Clear last error/flags registers keyword */

/* 0xA0 */
#define CPUBCI_LED_CTRL         (0xa0)    /**< Get/Set LED state (Br / Bw), 0=OFF / 1=ON */
#define CPUBCI_STAT_DET_CTRL    (0xa1)    /**< Get/Set SATA_DET state (Br / Bw) */

/* 0xB0 */
#define CPUBCI_ERRCNT_2(ec)  (0xb0+(ec))    /**< Get error counters block 2 (Br) */

/* 0xF0 */
#define CPUBCI_LIVE_SIGN_1      (0xf0)    /**< First  BIOS live sign */
#define CPUBCI_LIVE_SIGN_2      (0xf1)    /**< Second BIOS live sign */
#define CPUBCI_LIVE_SIGN_BYTE		(0x69)    /**< BIOS live sign keyword */

/**@}*/

#define CPUBCI_GETREV_NUM   	(3)        /**< Number of firmware words */

#define CPUBCI_ERRCNT(ec)			((ec<15) ? (CPUBCI_ERRCNT_1(ec)) : (CPUBCI_ERRCNT_2(ec-15)))





/*-----------------------------------------+
|  MACROS                                  |
+-----------------------------------------*/

#ifndef TRUE
#define TRUE (1==1)
#endif

#ifndef FALSE
#define FALSE   (!TRUE)
#endif



/*-----------------------------------------+
|  TYPEDEFS                                |
+-----------------------------------------*/

/* Hardware variants */
typedef enum hwVariants
{
	CPUBCI_HW_VAR_INVALID 	= (0x0000),	/**< Invalid hardware variant 			*/
	CPUBCI_HW_VAR_XM01    	= (0x0001),	/**< XM1 (Firmware 01.01.00 and newer)	*/
	CPUBCI_HW_VAR_MM01    	= (0x0002),	/**< MM1 					*/
	CPUBCI_HW_VAR_XM02   	= (0x0003),	/**< XM2 					*/
	CPUBCI_HW_VAR_F019    	= (0x0004),	/**< F19 					*/
	CPUBCI_HW_VAR_G020    	= (0x0005),	/**< G20 					*/
	CPUBCI_HW_VAR_SC21    	= (0x0006),	/**< SC21 					*/
	CPUBCI_HW_VAR_F11S    	= (0x0007),	/**< F11S 					*/
	CPUBCI_HW_VAR_F021    	= (0x0008),	/**< F21 					*/
	CPUBCI_HW_VAR_MM02    	= (0x0009),	/**< MM2 					*/
	CPUBCI_HW_VAR_XM03	= (0x000A),	/**< XM3 					*/
	CPUBCI_HW_VAR_G021	= (0x000B),	/**< G21 					*/
	CPUBCI_HW_VAR_SC24	= (0x000C),	/**< SC24 					*/
	CPUBCI_HW_VAR_SC26	= (0x000D),	/**< SC26 					*/
	CPUBCI_HW_VAR_F021C	= (0x000E),	/**< F22C 					*/
	CPUBCI_HW_VAR_F022	= (0x000F),	/**< F22P 					*/
	CPUBCI_HW_VAR_G022	= (0x0010),	/**< G22 					*/
	CPUBCI_HW_VAR_SC27	= (0x0011),	/**< SC27 					*/
	CPUBCI_HW_VAR_CB70	= (0x0012),	/**< CB70 					*/
	CPUBCI_HW_VAR_SC25	= (0x0013),	/**< SC25 					*/
	CPUBCI_HW_VAR_F23P	= (0x0014),	/**< F23P 					*/
	CPUBCI_HW_VAR_A22	= (0x0015),	/**< A22 					*/
	CPUBCI_HW_VAR_XM01_1	= (0xFFFF)	/**< XM1 (Firmware prior to 01.01.00) 		*/
} hwVariants_t;



typedef enum resumeModes
{
	CPUBCI_RESUME_OFF    			 = (0x00),	/**< Power Resume Mode "Off"					*/
	CPUBCI_RESUME_ON     			 = (0x01),	/**< Power Resume Mode "On"						*/
	CPUBCI_RESUME_FORMER 			 = (0x02),	/**< Power Resume Mode "Former"				*/
	CPUBCI_RESUME_MARKER				      		/*   End of power resume modes				*/

} resumeModes_t;

#define RESUME_MODE_DFLT			 (0x01)		/* Resume Mode Default            		*/


typedef enum formerModes
{
	CPUBCI_FORMER_OFF     		 = (0x00),	/**< Former Mode "Off"								*/
	CPUBCI_FORMER_ON      		 = (0x01), 	/**< Former Mode "On"									*/
	CPUBCI_FORMER_MARKER				      		/*   End of power resume modes				*/

} formerModes_t;

#define FORMER_STATE_DFLT	     (0x01)		/* Former State Default 							*/


typedef enum backplaneModes
{
	CPUBCI_BCKPLN_INVALID      = (0x00),	/**< Invalid Backplane Mode						*/
	CPUBCI_BCKPLN_MASTER  		 = (0x01),	/**< Master  Backplane Mode						*/
	CPUBCI_BCKPLN_SLAVE   		 = (0x02),	/**< Slave   Backplane Mode						*/
	CPUBCI_BCKPLN_MARKER									/*   End of Backplane Modes						*/

} backplaneModes_t;


typedef enum extPsOnModes
{
	CPUBCI_PSON_INVALID  			 = (0x00),	/**< Invalid EXT_PS_ON Mode						*/
	CPUBCI_PSON_ALWAYS   			 = (0x01),	/**< EXT_PS_ON Mode "Always on"				*/
	CPUBCI_PSON_SWITCHED 			 = (0x02),	/**< EXT_PS_ON Mode "Off in S3/S4/S5"	*/
	CPUBCI_PSON_MARKER										/*   End of EXT_PS_ON Modes						*/

} extPsOnModes_t;

#define EXT_PS_ON_MODE_DFLT		(0x02)		/* External PSU Mode Default          */


/* Common Reset Reasons */
typedef enum rstReasons
{
	CPUBCI_RST_NONE			       = (0x00),	/**< Initial Value 										*/
	CPUBCI_RST_REGULAR		     = (0x01),  /**< Regular Reset 										*/
	CPUBCI_RST_EXT_WDOG		     = (0x02),  /**< Main CPU Watchdog Timeout        */
	CPUBCI_RST_INT_WDOG		     = (0x03),  /**< Internal Watchdog (PIC) timeout 	*/
	CPUBCI_RST_INT_BRWN_OUT	   = (0x04),  /**< Internal (PIC) Brown-out Reset 	*/
	CPUBCI_RST_EXT_RESET       = (0x05),  /**< External Reset detected 					*/
	CPUBCI_RST_PLT_RESET       = (0x06),  /**< Platform Reset detected 					*/
	CPUBCI_RST_SW_RESET        = (0x07),  /**< Software Reset Request 					*/
	CPUBCI_RST_SW_COLD_RESET   = (0x08),  /**< Software Cold Reset Request 			*/
	CPUBCI_RST_SW_RTC_RESET    = (0x09),	/**< Software RTC Reset Request       */
	CPUBCI_RST_PWR_FAILURE     = (0x0a),  /**< Power Failure 										*/
	CPUBCI_RST_HSK_TIMEOUT     = (0x0b),  /**< Chipset Handshaking Timeout 			*/
	CPUBCI_RST_PLT_RST_TIMEOUT = (0x0c),  /**< PLT_RST Timeout 								  */
	CPUBCI_RST_BIOS_TIMEOUT    = (0x0d),  /**< BIOS Live Sign Timeout 				  */
	CPUBCI_RST_MARKER											/*   End of Reset Reasons 						*/

} rstReasons_t;

#define LAST_RESET_DFLT				 (0x00)		/* Last Reset Reason Default					*/


/* Common Last Errors */
typedef enum lastErrors
{
	CPUBCI_ERR_NONE            = (0x00),  /**< No Error last error 							*/
	CPUBCI_ERR_33V             = (0x01),  /**< 3.3V failure										  */
	CPUBCI_ERR_INP             = (0x02),  /**< Input voltage failure						*/
	CPUBCI_ERR_NO_EXT_PWR_OK   = (0x03),  /**< EXT_PWR_OK failure								*/
	CPUBCI_ERR_CPU_TOO_HOT     = (0x04),  /**< CPU too hot											*/
	CPUBCI_ERR_BIOS_TIMEOUT    = (0x05),  /**< BIOS live sign timed out					*/
	CPUBCI_ERR_SYS_RST_TIMEOUT = (0x06),	/**< System Reset Timeout             */
	CPUBCI_ERR_PLT_RST_TIMEOUT = (0x07),  /**< Platform Reset Timeout     	    */
	CPUBCI_ERR_HANDSHAKE       = (0x08),  /**< Handshake Failure						    */
	CPUBCI_ERR_NO_SYS_PWROK    = (0x09),  /**< System Power Good Failure        */
	CPUBCI_ERR_MARKER,										/*   End of Last Errors 							*/
	CPUBCI_INVALID_MAIN_STATE  = (0xff)   /**< Invalid state 										*/

} lastErrors_t;

#define LAST_ERROR_DFLT				 (0x00)		/* Last Error Code Default 					  */



/* Common Debugging modes */
#define CPUBCI_DBG_NONE      	 (0x00)   /**< No debugging messages          	*/
#define CPUBCI_DBG_STATES      (0x01)   /**< Signal main states             	*/
#define CPUBCI_DBG_1MS         (0x02)   /**< Signal every 1ms               	*/
#define CPUBCI_DBG_100MS       (0x04)   /**< Signal every  100 ms            	*/
#define CPUBCI_DBG_WDOG        (0x08)   /**< Signal every  100 ms (WDOG on)  	*/
#define CPUBCI_DBG_OPHRSCNT    (0x10)   /**< Signal every   20 ms           	*/
#define CPUBCI_DBG_PIC_ALIVE   (0x20)   /**< Signal every 6400 ms (PIC Alive) */
#define CPUBCI_DBG_EEPROM      (0x40)   /**< Signal EEPROM write              */
#define CPUBCI_DBG_FULL        (0xff)   /**< Signal everything              	*/





typedef union 
{
    struct
    {
        unsigned char low;
        unsigned char high;
    } bytes;

    unsigned int value;

} unsignedInt_t;


#ifndef __PICC__
typedef enum boolean
{
	CPUBCI_FALSE = FALSE,	/**< Boolean FALSE */
	CPUBCI_TRUE  = TRUE		/**< Boolean TRUE  */

} boolean_t;
#endif



/*-----------------------------------------+
|  PROTOTYPES                              |
+-----------------------------------------*/


/*-----------------------------------------+
|  GLOBALS                                 |
+-----------------------------------------*/



#ifdef __cplusplus
    }
#endif

#endif  /* _CPUBCI_H */
