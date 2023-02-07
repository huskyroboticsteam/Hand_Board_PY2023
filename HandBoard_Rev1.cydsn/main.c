/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "main.h" 
#include "Pin_Limit_1.h"
#include "Pin_Limit_2.h"
#include "Pin_Encoder_A.h"

int main(void){
  Initialize();

    
  
}

void Initialize(void) {
     // Enable global interrupts. LED arrays need this first
    CyGlobalIntEnable;
    
    #ifdef RGB_LED_ARRAY
    initalize_LEDs(LOW_LED_POWER);
    #endif
    
    Status_Reg_Switches_InterruptEnable();
    
    address = Can_addr_Read();
    
    #ifdef ENABLE_DEBUG_UART
    UART_Start();
    sprintf(txData, "Dip Addr: %x \r\n", address);
    UART_UartPutString(txData);
    #endif
    
    #ifdef ERROR_LED
    ERROR_LED_Write(~(address >> 3 & 1));
    #endif
    #ifdef DEBUG_LED2
    Debug_2_Write(~(address >> 2) & 1);
    #endif
    #ifdef DEBUG_LED1
    Debug_1_Write(~(address >> 1) & 1);
    #endif 
    #ifdef CAN_LED
    CAN_LED_Write(~address & 1);
    #endif
    
    InitCAN(0x4, (int)address);
    Timer_PWM_Start();
    QuadDec_Start();
    PWM_Motor_Start();  

    isr_Limit_1_StartEx(Pin_Limit_Handler);
    isr_period_PWM_StartEx(Period_Reset_Handler);
}

/* [] END OF FILE */
