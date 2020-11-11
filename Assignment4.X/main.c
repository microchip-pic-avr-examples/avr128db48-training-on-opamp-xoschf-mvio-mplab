/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "data_stream.h"
#include <math.h>

#define DEGREE 0.0245   //2pi /256 = 6.28/ 256.

#define SINE_WAVE_TIMER                  TCB0

/* VREF Startup time */
#define VREF_STARTUP_MICROS              (25)

/*Amplitude Volts*/
#define SINE_WAVE_AMPLITUDE_VOLTS		(0.128)
/*Offset Volts*/
#define SINE_DC_OFFSET_VOLTS			(0.825)
/*Offset Volts*/
#define VDD_DIV_2_VOLTS                 (1650)

/*DAC Voltage Reference*/
#define DAC_VOLTAGE_REF					(2.048)
/* Number of steps for a sine wave period */
#define SINE_WAVE_STEPS                  (92)
/* Sine wave amplitude */
#define SINE_AMPLITUDE                   (uint16_t)(SINE_WAVE_AMPLITUDE_VOLTS/DAC_VOLTAGE_REF*0x3FF)
/* Sine wave DC offset */
#define SINE_DC_OFFSET                   (uint16_t)(SINE_DC_OFFSET_VOLTS/DAC_VOLTAGE_REF*0x3FF)
/* 2*PI */
#define M_2PI                            (2 * M_PI)
/* Frequency of the sine wave */
#define OUTPUT_FREQ                      (25)

/* Buffer to store the sine wave samples */
uint16_t sine_wave[SINE_WAVE_STEPS];

void myRTCISR(void);
void myTCB0ISR(void);
void myTCB1ISR (void);


void sine_wave_table_init(void);

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    
    sine_wave_table_init();
    
    RTC_SetOVFIsrCallback(myRTCISR);
    TCB0_SetCaptIsrCallback(myTCB0ISR);
    USART3_SetTXISRCb(myUSART_3_ISR);
    data_stream.start_token = START_TOKEN;
    data_stream.end_token = (~START_TOKEN);
    TCB1_SetCaptIsrCallback(myTCB1ISR);

    /* Replace with your application code */
    while (1){
    }
}

void myRTCISR(void){
    LED0_Toggle(); //Control LED
}

void myTCB0ISR(void){
    
    volatile static uint16_t sine_wave_index = 0;
    
    DAC0_SetOutput(sine_wave[sine_wave_index]); //Control LED
    data_stream.diff_input = VDD_DIV_2_VOLTS - (sine_wave[sine_wave_index] << 1);
    sine_wave_index++;
    sine_wave_index = sine_wave_index % SINE_WAVE_STEPS;
}

void sine_wave_table_init(void)
{
  for(uint16_t i = 0; i < SINE_WAVE_STEPS; i++)
  {
    sine_wave[i] = SINE_DC_OFFSET + SINE_AMPLITUDE * sin(i * M_2PI / SINE_WAVE_STEPS);
  }
  
}

void myTCB1ISR (void){
    if (data_stream.data_available == 0) {
        /* Start ADC conversion */
        ADC0.COMMAND = ADC_STCONV_bm;
    }

    /* Clear interrupt flag */
    TCB1.INTFLAGS = 0xFF;
}

ISR (ADC0_RESRDY_vect)
{
    data_stream.data_available = 1;
    data_stream.opampVal = (int16_t)((int16_t)ADC0.RES >> 3);
    data_stream.opampVal = ((int16_t)(data_stream.opampVal*32)/10);
    DS_sendData();
    ADC0.INTFLAGS = ADC_RESRDY_bm;
}

/**
    End of File
*/