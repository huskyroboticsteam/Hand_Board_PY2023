/*******************************************************************************
* File Name: Timer_PWM.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_Timer_PWM_H)
#define CY_TIMER_Timer_PWM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Timer_PWM_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define Timer_PWM_Resolution                 24u
#define Timer_PWM_UsingFixedFunction         0u
#define Timer_PWM_UsingHWCaptureCounter      0u
#define Timer_PWM_SoftwareCaptureMode        0u
#define Timer_PWM_SoftwareTriggerMode        0u
#define Timer_PWM_UsingHWEnable              0u
#define Timer_PWM_EnableTriggerMode          0u
#define Timer_PWM_InterruptOnCaptureCount    0u
#define Timer_PWM_RunModeUsed                0u
#define Timer_PWM_ControlRegRemoved          0u

#if defined(Timer_PWM_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define Timer_PWM_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (Timer_PWM_UsingFixedFunction)
    #define Timer_PWM_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define Timer_PWM_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End Timer_PWM_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!Timer_PWM_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (Timer_PWM_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!Timer_PWM_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}Timer_PWM_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    Timer_PWM_Start(void) ;
void    Timer_PWM_Stop(void) ;

void    Timer_PWM_SetInterruptMode(uint8 interruptMode) ;
uint8   Timer_PWM_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define Timer_PWM_GetInterruptSource() Timer_PWM_ReadStatusRegister()

#if(!Timer_PWM_UDB_CONTROL_REG_REMOVED)
    uint8   Timer_PWM_ReadControlRegister(void) ;
    void    Timer_PWM_WriteControlRegister(uint8 control) ;
#endif /* (!Timer_PWM_UDB_CONTROL_REG_REMOVED) */

uint32  Timer_PWM_ReadPeriod(void) ;
void    Timer_PWM_WritePeriod(uint32 period) ;
uint32  Timer_PWM_ReadCounter(void) ;
void    Timer_PWM_WriteCounter(uint32 counter) ;
uint32  Timer_PWM_ReadCapture(void) ;
void    Timer_PWM_SoftwareCapture(void) ;

#if(!Timer_PWM_UsingFixedFunction) /* UDB Prototypes */
    #if (Timer_PWM_SoftwareCaptureMode)
        void    Timer_PWM_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!Timer_PWM_UsingFixedFunction) */

    #if (Timer_PWM_SoftwareTriggerMode)
        void    Timer_PWM_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (Timer_PWM_SoftwareTriggerMode) */

    #if (Timer_PWM_EnableTriggerMode)
        void    Timer_PWM_EnableTrigger(void) ;
        void    Timer_PWM_DisableTrigger(void) ;
    #endif /* (Timer_PWM_EnableTriggerMode) */


    #if(Timer_PWM_InterruptOnCaptureCount)
        void    Timer_PWM_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (Timer_PWM_InterruptOnCaptureCount) */

    #if (Timer_PWM_UsingHWCaptureCounter)
        void    Timer_PWM_SetCaptureCount(uint8 captureCount) ;
        uint8   Timer_PWM_ReadCaptureCount(void) ;
    #endif /* (Timer_PWM_UsingHWCaptureCounter) */

    void Timer_PWM_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void Timer_PWM_Init(void)          ;
void Timer_PWM_Enable(void)        ;
void Timer_PWM_SaveConfig(void)    ;
void Timer_PWM_RestoreConfig(void) ;
void Timer_PWM_Sleep(void)         ;
void Timer_PWM_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define Timer_PWM__B_TIMER__CM_NONE 0
#define Timer_PWM__B_TIMER__CM_RISINGEDGE 1
#define Timer_PWM__B_TIMER__CM_FALLINGEDGE 2
#define Timer_PWM__B_TIMER__CM_EITHEREDGE 3
#define Timer_PWM__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define Timer_PWM__B_TIMER__TM_NONE 0x00u
#define Timer_PWM__B_TIMER__TM_RISINGEDGE 0x04u
#define Timer_PWM__B_TIMER__TM_FALLINGEDGE 0x08u
#define Timer_PWM__B_TIMER__TM_EITHEREDGE 0x0Cu
#define Timer_PWM__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define Timer_PWM_INIT_PERIOD             999999u
#define Timer_PWM_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << Timer_PWM_CTRL_CAP_MODE_SHIFT))
#define Timer_PWM_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << Timer_PWM_CTRL_TRIG_MODE_SHIFT))
#if (Timer_PWM_UsingFixedFunction)
    #define Timer_PWM_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << Timer_PWM_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << Timer_PWM_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define Timer_PWM_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << Timer_PWM_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << Timer_PWM_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << Timer_PWM_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (Timer_PWM_UsingFixedFunction) */
#define Timer_PWM_INIT_CAPTURE_COUNT      (2u)
#define Timer_PWM_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << Timer_PWM_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (Timer_PWM_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define Timer_PWM_STATUS         (*(reg8 *) Timer_PWM_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define Timer_PWM_STATUS_MASK    (*(reg8 *) Timer_PWM_TimerHW__SR0 )
    #define Timer_PWM_CONTROL        (*(reg8 *) Timer_PWM_TimerHW__CFG0)
    #define Timer_PWM_CONTROL2       (*(reg8 *) Timer_PWM_TimerHW__CFG1)
    #define Timer_PWM_CONTROL2_PTR   ( (reg8 *) Timer_PWM_TimerHW__CFG1)
    #define Timer_PWM_RT1            (*(reg8 *) Timer_PWM_TimerHW__RT1)
    #define Timer_PWM_RT1_PTR        ( (reg8 *) Timer_PWM_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define Timer_PWM_CONTROL3       (*(reg8 *) Timer_PWM_TimerHW__CFG2)
        #define Timer_PWM_CONTROL3_PTR   ( (reg8 *) Timer_PWM_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define Timer_PWM_GLOBAL_ENABLE  (*(reg8 *) Timer_PWM_TimerHW__PM_ACT_CFG)
    #define Timer_PWM_GLOBAL_STBY_ENABLE  (*(reg8 *) Timer_PWM_TimerHW__PM_STBY_CFG)

    #define Timer_PWM_CAPTURE_LSB         (* (reg16 *) Timer_PWM_TimerHW__CAP0 )
    #define Timer_PWM_CAPTURE_LSB_PTR       ((reg16 *) Timer_PWM_TimerHW__CAP0 )
    #define Timer_PWM_PERIOD_LSB          (* (reg16 *) Timer_PWM_TimerHW__PER0 )
    #define Timer_PWM_PERIOD_LSB_PTR        ((reg16 *) Timer_PWM_TimerHW__PER0 )
    #define Timer_PWM_COUNTER_LSB         (* (reg16 *) Timer_PWM_TimerHW__CNT_CMP0 )
    #define Timer_PWM_COUNTER_LSB_PTR       ((reg16 *) Timer_PWM_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define Timer_PWM_BLOCK_EN_MASK                     Timer_PWM_TimerHW__PM_ACT_MSK
    #define Timer_PWM_BLOCK_STBY_EN_MASK                Timer_PWM_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define Timer_PWM_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define Timer_PWM_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define Timer_PWM_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define Timer_PWM_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define Timer_PWM_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define Timer_PWM_CTRL_ENABLE                        ((uint8)((uint8)0x01u << Timer_PWM_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Timer_PWM_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define Timer_PWM_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << Timer_PWM_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define Timer_PWM_CTRL_MODE_SHIFT                 0x01u
        #define Timer_PWM_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << Timer_PWM_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define Timer_PWM_CTRL_RCOD_SHIFT        0x02u
        #define Timer_PWM_CTRL_ENBL_SHIFT        0x00u
        #define Timer_PWM_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define Timer_PWM_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << Timer_PWM_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define Timer_PWM_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << Timer_PWM_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define Timer_PWM_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << Timer_PWM_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define Timer_PWM_CTRL_RCOD       ((uint8)((uint8)0x03u << Timer_PWM_CTRL_RCOD_SHIFT))
        #define Timer_PWM_CTRL_ENBL       ((uint8)((uint8)0x80u << Timer_PWM_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define Timer_PWM_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define Timer_PWM_RT1_MASK                        ((uint8)((uint8)0x03u << Timer_PWM_RT1_SHIFT))
    #define Timer_PWM_SYNC                            ((uint8)((uint8)0x03u << Timer_PWM_RT1_SHIFT))
    #define Timer_PWM_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define Timer_PWM_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << Timer_PWM_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define Timer_PWM_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << Timer_PWM_SYNCDSI_SHIFT))

    #define Timer_PWM_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << Timer_PWM_CTRL_MODE_SHIFT))
    #define Timer_PWM_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << Timer_PWM_CTRL_MODE_SHIFT))
    #define Timer_PWM_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << Timer_PWM_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Timer_PWM_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Timer_PWM_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define Timer_PWM_STATUS_TC_INT_MASK_SHIFT        (Timer_PWM_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define Timer_PWM_STATUS_CAPTURE_INT_MASK_SHIFT   (Timer_PWM_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define Timer_PWM_STATUS_TC                       ((uint8)((uint8)0x01u << Timer_PWM_STATUS_TC_SHIFT))
    #define Timer_PWM_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << Timer_PWM_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define Timer_PWM_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << Timer_PWM_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define Timer_PWM_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << Timer_PWM_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define Timer_PWM_STATUS              (* (reg8 *) Timer_PWM_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define Timer_PWM_STATUS_MASK         (* (reg8 *) Timer_PWM_TimerUDB_rstSts_stsreg__MASK_REG)
    #define Timer_PWM_STATUS_AUX_CTRL     (* (reg8 *) Timer_PWM_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define Timer_PWM_CONTROL             (* (reg8 *) Timer_PWM_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(Timer_PWM_Resolution <= 8u) /* 8-bit Timer */
        #define Timer_PWM_CAPTURE_LSB         (* (reg8 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define Timer_PWM_CAPTURE_LSB_PTR       ((reg8 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define Timer_PWM_PERIOD_LSB          (* (reg8 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define Timer_PWM_PERIOD_LSB_PTR        ((reg8 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define Timer_PWM_COUNTER_LSB         (* (reg8 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define Timer_PWM_COUNTER_LSB_PTR       ((reg8 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__A0_REG )
    #elif(Timer_PWM_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define Timer_PWM_CAPTURE_LSB         (* (reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define Timer_PWM_CAPTURE_LSB_PTR       ((reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define Timer_PWM_PERIOD_LSB          (* (reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define Timer_PWM_PERIOD_LSB_PTR        ((reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define Timer_PWM_COUNTER_LSB         (* (reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define Timer_PWM_COUNTER_LSB_PTR       ((reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define Timer_PWM_CAPTURE_LSB         (* (reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define Timer_PWM_CAPTURE_LSB_PTR       ((reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define Timer_PWM_PERIOD_LSB          (* (reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define Timer_PWM_PERIOD_LSB_PTR        ((reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define Timer_PWM_COUNTER_LSB         (* (reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
            #define Timer_PWM_COUNTER_LSB_PTR       ((reg16 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(Timer_PWM_Resolution <= 24u)/* 24-bit Timer */
        #define Timer_PWM_CAPTURE_LSB         (* (reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define Timer_PWM_CAPTURE_LSB_PTR       ((reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define Timer_PWM_PERIOD_LSB          (* (reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define Timer_PWM_PERIOD_LSB_PTR        ((reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define Timer_PWM_COUNTER_LSB         (* (reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define Timer_PWM_COUNTER_LSB_PTR       ((reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define Timer_PWM_CAPTURE_LSB         (* (reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define Timer_PWM_CAPTURE_LSB_PTR       ((reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define Timer_PWM_PERIOD_LSB          (* (reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define Timer_PWM_PERIOD_LSB_PTR        ((reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define Timer_PWM_COUNTER_LSB         (* (reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define Timer_PWM_COUNTER_LSB_PTR       ((reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define Timer_PWM_CAPTURE_LSB         (* (reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define Timer_PWM_CAPTURE_LSB_PTR       ((reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define Timer_PWM_PERIOD_LSB          (* (reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define Timer_PWM_PERIOD_LSB_PTR        ((reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define Timer_PWM_COUNTER_LSB         (* (reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
            #define Timer_PWM_COUNTER_LSB_PTR       ((reg32 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define Timer_PWM_COUNTER_LSB_PTR_8BIT       ((reg8 *) Timer_PWM_TimerUDB_sT24_timerdp_u0__A0_REG )
    
    #if (Timer_PWM_UsingHWCaptureCounter)
        #define Timer_PWM_CAP_COUNT              (*(reg8 *) Timer_PWM_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Timer_PWM_CAP_COUNT_PTR          ( (reg8 *) Timer_PWM_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define Timer_PWM_CAPTURE_COUNT_CTRL     (*(reg8 *) Timer_PWM_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define Timer_PWM_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) Timer_PWM_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (Timer_PWM_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define Timer_PWM_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define Timer_PWM_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define Timer_PWM_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define Timer_PWM_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define Timer_PWM_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define Timer_PWM_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << Timer_PWM_CTRL_INTCNT_SHIFT))
    #define Timer_PWM_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << Timer_PWM_CTRL_TRIG_MODE_SHIFT))
    #define Timer_PWM_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << Timer_PWM_CTRL_TRIG_EN_SHIFT))
    #define Timer_PWM_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << Timer_PWM_CTRL_CAP_MODE_SHIFT))
    #define Timer_PWM_CTRL_ENABLE                    ((uint8)((uint8)0x01u << Timer_PWM_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define Timer_PWM_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define Timer_PWM_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define Timer_PWM_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define Timer_PWM_STATUS_TC_INT_MASK_SHIFT       Timer_PWM_STATUS_TC_SHIFT
    #define Timer_PWM_STATUS_CAPTURE_INT_MASK_SHIFT  Timer_PWM_STATUS_CAPTURE_SHIFT
    #define Timer_PWM_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define Timer_PWM_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define Timer_PWM_STATUS_FIFOFULL_INT_MASK_SHIFT Timer_PWM_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define Timer_PWM_STATUS_TC                      ((uint8)((uint8)0x01u << Timer_PWM_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define Timer_PWM_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << Timer_PWM_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Timer_PWM_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << Timer_PWM_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Timer_PWM_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << Timer_PWM_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define Timer_PWM_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << Timer_PWM_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define Timer_PWM_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << Timer_PWM_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define Timer_PWM_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << Timer_PWM_STATUS_FIFOFULL_SHIFT))

    #define Timer_PWM_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define Timer_PWM_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define Timer_PWM_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define Timer_PWM_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define Timer_PWM_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define Timer_PWM_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_Timer_PWM_H */


/* [] END OF FILE */
