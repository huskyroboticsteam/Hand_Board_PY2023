/*******************************************************************************
* File Name: isr_period_PWM.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_period_PWM_H)
#define CY_ISR_isr_period_PWM_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_period_PWM_Start(void);
void isr_period_PWM_StartEx(cyisraddress address);
void isr_period_PWM_Stop(void);

CY_ISR_PROTO(isr_period_PWM_Interrupt);

void isr_period_PWM_SetVector(cyisraddress address);
cyisraddress isr_period_PWM_GetVector(void);

void isr_period_PWM_SetPriority(uint8 priority);
uint8 isr_period_PWM_GetPriority(void);

void isr_period_PWM_Enable(void);
uint8 isr_period_PWM_GetState(void);
void isr_period_PWM_Disable(void);

void isr_period_PWM_SetPending(void);
void isr_period_PWM_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_period_PWM ISR. */
#define isr_period_PWM_INTC_VECTOR            ((reg32 *) isr_period_PWM__INTC_VECT)

/* Address of the isr_period_PWM ISR priority. */
#define isr_period_PWM_INTC_PRIOR             ((reg32 *) isr_period_PWM__INTC_PRIOR_REG)

/* Priority of the isr_period_PWM interrupt. */
#define isr_period_PWM_INTC_PRIOR_NUMBER      isr_period_PWM__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_period_PWM interrupt. */
#define isr_period_PWM_INTC_SET_EN            ((reg32 *) isr_period_PWM__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_period_PWM interrupt. */
#define isr_period_PWM_INTC_CLR_EN            ((reg32 *) isr_period_PWM__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_period_PWM interrupt state to pending. */
#define isr_period_PWM_INTC_SET_PD            ((reg32 *) isr_period_PWM__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_period_PWM interrupt. */
#define isr_period_PWM_INTC_CLR_PD            ((reg32 *) isr_period_PWM__INTC_CLR_PD_REG)



#endif /* CY_ISR_isr_period_PWM_H */


/* [] END OF FILE */
