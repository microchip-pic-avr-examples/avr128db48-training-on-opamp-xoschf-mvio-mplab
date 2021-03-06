/**
 * \file main.c
 *
 * \brief Fuses settings source file.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.
    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */
#ifndef FUSE_H
#define	FUSE_H

#include <avr/io.h>

/**
 * \Configures Fuse bits
 */

FUSES = 
{
	.BODCFG = FUSE_BODCFG_DEFAULT,
	.BOOTSIZE = FUSE_BOOTSIZE_DEFAULT,
	.CODESIZE = FUSE_CODESIZE_DEFAULT,
	.OSCCFG = FUSE_OSCCFG_DEFAULT,
	.SYSCFG0 = FUSE_SYSCFG0_DEFAULT,
	.SYSCFG1 = FUSE_SYSCFG1_DEFAULT,
	.WDTCFG = FUSE_WDTCFG_DEFAULT,
};


#endif	/* FUSE_H */


