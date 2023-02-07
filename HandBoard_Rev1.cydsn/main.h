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
#ifndef PROJECT_H
#define PROJECT_H

#include "cytypes.h"
#include "CyLib.h"

/* Function prototypes for the limit switch functions */
void LimitSwitch_1_Start(void);
uint8 LimitSwitch_1_Read(void);
void LimitSwitch_2_Start(void);
uint8 LimitSwitch_2_Read(void);

/* Function prototypes for the encoder/potentiometer functions */
void Encoder_Start(void);
int Encoder_GetCounter(void);

/* Function prototypes for the DC motor functions */
void DCMotor_Start(void);
void DCMotor_Write(uint8 value);

/* Function prototypes for the servo functions */
void Servo_1_Start(void);
void Servo_1_Write(int value);
void Servo_2_Start(void);
void Servo_2_Write(int value);
void Servo_3_Start(void);
void Servo_3_Write(int value);
void Servo_4_Start(void);
void Servo_4_Write(int value);
void Servo_5_Start(void);
void Servo_5_Write(int value);
void Servo_6_Start(void);
void Servo_6_Write(int value);

#endif /* PROJECT_H */
/* [] END OF FILE */
