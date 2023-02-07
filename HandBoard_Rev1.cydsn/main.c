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
#include "project.h" // edit this
#include "Pin_Limit_1.h"
#include "Pin_Limit_2.h"
#include "Pin_Encoder_A.h"

int main(void){
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /* Initialize the limit switches */
   // LimitSwitch_1_Start();
   // LimitSwitch_2_Start();
    // DO WE NEED TO INITIALIZE THIS?? 

    /* Initialize the encoder/potentiometer */
  //  Encoder_Start();

    /* Initialize the DC motor */
    DCMotor_Start();

    /* Initialize the servos */
    Servo_1_Start();
    Servo_2_Start();
    Servo_3_Start();
    Servo_4_Start();
    Servo_5_Start();
    Servo_6_Start();

    for(;;)
    {
        /* Check the state of the first limit switch */
        if (Pin_Limit_1_Read() == 0) {
            /* The first limit switch is pressed */
            /* Perform some action */
        }
        else {
            /* The first limit switch is not pressed */
            /* Perform some other action */
        }

        /* Check the state of the second limit switch */
        if (Pin_Limit_2_Read() == 0) {
            /* The second limit switch is pressed */
            /* Perform some action */
        }
        else {
            /* The second limit switch is not pressed */
            /* Perform some other action */
        }

        /* Read the value of the encoder/potentiometer */
        int value = Pin_Encoder_A_Read();
        /* The value will be in the range 0-1023, depending on the position of the encoder/potentiometer */

        /* Perform some action based on the value of the encoder/potentiometer */
        if (value < 100) {
            /* The encoder/potentiometer is in the lower range */
            /* Perform some action */
        }
        else if (value > 900) {
            /* The encoder/potentiometer is in the upper range */
            /* Perform some action */
        }
        else {
            /* The encoder/potentiometer is in the middle range */
            /* Perform some action */
        }

        /* Control the DC motor */
        if (value < 500) {
            /* Set the DC motor to run forward */
            DCMotor_Write(1);
        }
        else {
            /* Set the DC motor to run backward */
            DCMotor_Write(0);
        }

        /* Control the servos */
        Servo_1_Write(value);
        Servo_2_Write(value);
        Servo_3_Write(value);
        Servo_4_Write(value);
        Servo_5_Write(value);
        Servo_6_Write(value);
    }
}



/* [] END OF FILE */
