/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
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


#include "../include/usart3.h"

#if defined(__GNUC__)

int USART3_printCHAR(char character, FILE *stream)
{
    USART3_Write(character);
    return 0;
}

FILE USART3_stream = FDEV_SETUP_STREAM(USART3_printCHAR, NULL, _FDEV_SETUP_WRITE);

#elif defined(__ICCAVR__)

int putchar(int outChar)
{
    USART3_Write(outChar);
    return outChar;
}
#endif

/* Static Variables holding the ringbuffer used in IRQ mode */
static uint8_t          USART3_rxbuf[USART3_RX_BUFFER_SIZE];
static volatile uint8_t USART3_rx_head;
static volatile uint8_t USART3_rx_tail;
static volatile uint8_t USART3_rx_elements;
static uint8_t          USART3_txbuf[USART3_TX_BUFFER_SIZE];
static volatile uint8_t USART3_tx_head;
static volatile uint8_t USART3_tx_tail;
static volatile uint8_t USART3_tx_elements;

void (*USART3_rx_isr_cb)(void) = &USART3_DefaultRxIsrCb;

void (*USART3_tx_isr_cb)(void) = &USART3_DefaultTxIsrCb;

void USART3_DefaultRxIsrCb(void)
{
    uint8_t data;
    uint8_t tmphead;

    /* Read the received data */
    data = USART3.RXDATAL;
    /* Calculate buffer index */
    tmphead = (USART3_rx_head + 1) & USART3_RX_BUFFER_MASK;
        
    if (tmphead == USART3_rx_tail) {
            /* ERROR! Receive buffer overflow */
    }else {
    /*Store new index*/
    USART3_rx_head = tmphead;
    
    /* Store received data in buffer */
    USART3_rxbuf[tmphead] = data;
    USART3_rx_elements++;
    }
}

void USART3_DefaultTxIsrCb(void)
{
    uint8_t tmptail;

    /* Check if all data is transmitted */
    if (USART3_tx_elements != 0) {
        /* Calculate buffer index */
        tmptail = (USART3_tx_tail + 1) & USART3_TX_BUFFER_MASK;
        /* Store new index */
        USART3_tx_tail = tmptail;
        /* Start transmission */
        USART3.TXDATAL = USART3_txbuf[tmptail];
        
        USART3_tx_elements--;
    }

    if (USART3_tx_elements == 0) {
            /* Disable Tx interrupt */
            USART3.CTRLA &= ~(1 << USART_DREIE_bp);
    }
}

void USART3_SetISRCb(usart_callback cb, usart3_cb_t type)
{
    switch (type) {
        case USART3_RX_CB:
                USART3_rx_isr_cb = cb;
                break;
        case USART3_TX_CB:
                USART3_tx_isr_cb = cb;
                break;
        default:
                // do nothing
                break;
    }
}

void USART3_SetRXISRCb(usart_callback cb)
{
    USART3_SetISRCb(cb,USART3_RX_CB);
}

void USART3_SetTXISRCb(usart_callback cb)
{
    USART3_SetISRCb(cb,USART3_TX_CB);
}

/* Interrupt service routine for RX complete */
ISR(USART3_RXC_vect)
{
    if (USART3_rx_isr_cb != NULL)
    {
        (*USART3_rx_isr_cb)();
    }
}

/* Interrupt service routine for Data Register Empty */
ISR(USART3_DRE_vect)
{
    if (USART3_tx_isr_cb != NULL)
    {
        (*USART3_tx_isr_cb)();
    }
}

ISR(USART3_TXC_vect)
{
    USART3.STATUS |= USART_TXCIF_bm;
}

bool USART3_IsTxReady()
{
    return (USART3_tx_elements != USART3_TX_BUFFER_SIZE);
}

bool USART3_IsRxReady()
{
    return (USART3_rx_elements != 0);
}

bool USART3_IsTxBusy()
{
    return (!(USART3.STATUS & USART_TXCIF_bm));
}

bool USART3_IsTxDone()
{
    return (USART3.STATUS & USART_TXCIF_bm);
}

uint8_t USART3_Read(void)
{
    uint8_t tmptail;

    /* Wait for incoming data */
    while (USART3_rx_elements == 0)
            ;
    /* Calculate buffer index */
    tmptail = (USART3_rx_tail + 1) & USART3_RX_BUFFER_MASK;
    /* Store new index */
    USART3_rx_tail = tmptail;
    ENTER_CRITICAL(R);
    USART3_rx_elements--;
    EXIT_CRITICAL(R);

    /* Return data */
    return USART3_rxbuf[tmptail];
}

void USART3_Write(const uint8_t data)
{
    uint8_t tmphead;

    /* Calculate buffer index */
    tmphead = (USART3_tx_head + 1) & USART3_TX_BUFFER_MASK;
    /* Wait for free space in buffer */
    while (USART3_tx_elements == USART3_TX_BUFFER_SIZE)
            ;
    /* Store data in buffer */
    USART3_txbuf[tmphead] = data;
    /* Store new index */
    USART3_tx_head = tmphead;
    ENTER_CRITICAL(W);
    USART3_tx_elements++;
    EXIT_CRITICAL(W);
    /* Enable Tx interrupt */
    USART3.CTRLA |= (1 << USART_DREIE_bp);
}

void USART3_Initialize()
{
    //set baud rate register
    USART3.BAUD = (uint16_t)USART3_BAUD_RATE(115200);
	
    //RXCIE disabled; TXCIE disabled; DREIE enabled; RXSIE disabled; LBME disabled; ABEIE disabled; RS485 DISABLE; 
    USART3.CTRLA = 0x20;
	
    //RXEN disabled; TXEN enabled; SFDEN disabled; ODME disabled; RXMODE NORMAL; MPCM disabled; 
    USART3.CTRLB = 0x40;
	
    //CMODE ASYNCHRONOUS; PMODE DISABLED; SBMODE 1BIT; CHSIZE 8BIT; UDORD disabled; UCPHA disabled; 
    USART3.CTRLC = 0x03;
	
    //DBGCTRL_DBGRUN
    USART3.DBGCTRL = 0x00;
	
    //EVCTRL_IREI
    USART3.EVCTRL = 0x00;
	
    //RXPLCTRL_RXPL
    USART3.RXPLCTRL = 0x00;
	
    //TXPLCTRL_TXPL
    USART3.TXPLCTRL = 0x00;
	

    uint8_t x;

    /* Initialize ringbuffers */
    x = 0;

    USART3_rx_tail     = x;
    USART3_rx_head     = x;
    USART3_rx_elements = x;
    USART3_tx_tail     = x;
    USART3_tx_head     = x;
    USART3_tx_elements = x;

#if defined(__GNUC__)
    stdout = &USART3_stream;
#endif

}

void USART3_Enable()
{
    USART3.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void USART3_EnableRx()
{
    USART3.CTRLB |= USART_RXEN_bm;
}

void USART3_EnableTx()
{
    USART3.CTRLB |= USART_TXEN_bm;
}

void USART3_Disable()
{
    USART3.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
}

uint8_t USART3_GetData()
{
    return USART3.RXDATAL;
}