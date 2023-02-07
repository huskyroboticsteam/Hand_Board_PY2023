// Main c file for HandBoard 2023

#include "main.h" 


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

CY_ISR(Pin_Limit_Handler){
    #ifdef PRINT_LIMIT_SW_TRIGGER
    sprintf(txData,"LimitSW triggerd Stat: %x \r\n", Status_Reg_Switches_Read() & 0b11);
    UART_UartPutString(txData);
    #endif
    
    set_PWM(GetCurrentPWM(), ignoreLimSw, Status_Reg_Switches_Read());
    
    #ifdef CAN_TELEM_SEND
    AssembleLimitSwitchAlertPacket(&can_send, DEVICE_GROUP_JETSON, 
        DEVICE_SERIAL_JETSON, Status_Reg_Switches_Read() & 0b11);
    SendCANPacket(&can_send);
    #endif
    //TODO: Select Which Encoder zeros
    //QuadDec_SetCounter(0);
    if (bound_set1 && ~Pin_Limit_1_Read()) {
        QuadDec_SetCounter(enc_lim_1);
    } else {
        QuadDec_SetCounter(enc_lim_2);
    }
}

CY_ISR(Period_Reset_Handler) {
    int timer = Timer_PWM_ReadStatusRegister();
    invalidate++;
    CAN_time_LED++;
    CAN_check_delay ++;
    ERRORTimeLED++;
    encoderTimeOut++;
    if (encoderTimeOut >= 2){
        encoderTimeOut = 0;
        SendEncoderData(&can_send);
    }
    if (invalidate >= 20){
        set_PWM(0, 0, 0);   
    }
    if (ERRORTimeLED >= 3) {
        #ifdef ERROR_LED
        ERROR_LED_Write(LED_OFF);
        #endif
        #ifdef DEBUG_LED1   
        Debug_1_Write(LED_OFF);
        #endif
        #ifdef DEBUG_LED2
        Debug_2_Write(LED_OFF);
        #endif
    }
    if (CAN_time_LED >= 3){
        #ifdef CAN_LED
        CAN_LED_Write(LED_OFF);
        #endif
    }
}

