/**
 * OPAMP Generated Driver File
 * 
 * @file opamp.c
 * 
 * @ingroup opamp
 * 
 * @brief This is the generated driver implementation file for the OPAMP driver using AVR MCUs
 *
 * @version OPAMP Driver Version v1.0.0
*/
/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../opamp.h"

void OPAMP_Initialize(void)
{
    OPAMP_DisableSystem();
    
    //TIMEBASE 3; 
    OPAMP.TIMEBASE = OPAMP_TIMEBASE_VALUE << OPAMP_TIMEBASE_gp;
    
    //DBGRUN disabled; 
    OPAMP.DBGCTRL = 0x0;
    
    //IRSEL FULL; 
    OPAMP.PWRCTRL = 0x0;
    
    //OP0 Configuration : Instrumentation Amplifier
    //Instrumentation Amplifier Gain : 3
    
    //MUXNEG OPn output (unity gain); MUXPOS VDD/2; 
    OPAMP.OP0INMUX = 0x24;
    
    //MUXBOT Ground; MUXTOP OPn output; MUXWIP R1 = 12R, R2 = 4R, R2/R1 = 0.33; 
    OPAMP.OP0RESMUX = 0x55;
    
    //ALWAYSON enabled; EVENTEN disabled; OUTMODE Output Driver in Normal Mode; RUNSTBY disabled; 
    OPAMP.OP0CTRLA = 0x5;
    
    //SETTLE 127; 
    OPAMP.OP0SETTLE = 0x7F;
    
    //OP1 Configuration : Instrumentation Amplifier
    //Instrumentation Amplifier Gain : 3
    
    //MUXNEG OPn output (unity gain); MUXPOS DAC output; 
    OPAMP.OP1INMUX = 0x22;
    
    //MUXBOT Multiplexer off; MUXTOP Multiplexer off; MUXWIP R1 = 15R, R2 = 1R, R2/R1 = 0.07; 
    OPAMP.OP1RESMUX = 0x0;
    
    //ALWAYSON enabled; EVENTEN disabled; OUTMODE Output Driver in Normal Mode; RUNSTBY disabled; 
    OPAMP.OP1CTRLA = 0x5;
    
    //SETTLE 127; 
    OPAMP.OP1SETTLE = 0x7F;
    
    //OP2 Configuration : Instrumentation Amplifier
    //Instrumentation Amplifier Gain : 3
    
    //MUXNEG Wiper from OPn's resistor ladder; MUXPOS Wiper from OP0's resistor ladder; 
    OPAMP.OP2INMUX = 0x16;
    
    //MUXBOT Link OP[n-1] output; MUXTOP OPn output; MUXWIP R1 = 4R, R2 = 12R, R2/R1 = 3; 
    OPAMP.OP2RESMUX = 0xB1;
    
    //ALWAYSON enabled; EVENTEN disabled; OUTMODE Output Driver in Normal Mode; RUNSTBY disabled; 
    OPAMP.OP2CTRLA = 0x5;
    
    //SETTLE 127; 
    OPAMP.OP2SETTLE = 0x7F;
    
    OPAMP_EnableSystem();
}

void OPAMP_EnableSystem(void)
{
    OPAMP.CTRLA |= OPAMP_ENABLE_bm;
}

void OPAMP_DisableSystem(void)
{
    OPAMP.CTRLA &= ~OPAMP_ENABLE_bm;
}

//OP0 Instrumentation Amplifier APIs

void OPAMP_SetOP0PositiveInMux(OPAMP_OP0INMUX_MUXPOS_t value)
{
    OPAMP.OP0INMUX = (OPAMP.OP0INMUX & ~OPAMP_MUXPOS_gm) | value;
}

void OPAMP_SetOP0WiperResMux(OPAMP_OP0RESMUX_MUXWIP_t value)
{
    OPAMP.OP0RESMUX = (OPAMP.OP0RESMUX & ~OPAMP_MUXWIP_gm) | value;
}

void OPAMP_SetOP0SettleTime(uint8_t settleTime)
{
    if (settleTime > 127) {
        settleTime = 127;
    }
    OPAMP.OP0SETTLE = settleTime;
}

bool OPAMP_IsOP0Settled(void)
{
    return OPAMP.OP0STATUS > 0;
}

void OPAMP_SetOP0OffsetCalibration(uint8_t calValue)
{
    OPAMP.OP0CAL = calValue;
}

//OP1 Instrumentation Amplifier APIs

void OPAMP_SetOP1PositiveInMux(OPAMP_OP1INMUX_MUXPOS_t value)
{
    OPAMP.OP1INMUX = (OPAMP.OP1INMUX & ~OPAMP_MUXPOS_gm) | value;
}

void OPAMP_SetOP1SettleTime(uint8_t settleTime)
{
    if (settleTime > 127) {
        settleTime = 127;
    }
    OPAMP.OP1SETTLE = settleTime;
}

bool OPAMP_IsOP1Settled(void)
{
    return OPAMP.OP1STATUS > 0;
}

void OPAMP_SetOP1OffsetCalibration(uint8_t calValue)
{
    OPAMP.OP1CAL = calValue;
}

//OP2 Instrumentation Amplifier APIs

void OPAMP_SetOP2WiperResMux(OPAMP_OP2RESMUX_MUXWIP_t value)
{
    OPAMP.OP2RESMUX = (OPAMP.OP2RESMUX & ~OPAMP_MUXWIP_gm) | value;
}

void OPAMP_SetOP2SettleTime(uint8_t settleTime)
{
    if (settleTime > 127) {
        settleTime = 127;
    }
    OPAMP.OP2SETTLE = settleTime;
}

bool OPAMP_IsOP2Settled(void)
{
    return OPAMP.OP2STATUS > 0;
}

void OPAMP_SetOP2OffsetCalibration(uint8_t calValue)
{
    OPAMP.OP2CAL = calValue;
}
