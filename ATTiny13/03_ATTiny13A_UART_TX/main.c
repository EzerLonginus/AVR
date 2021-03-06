/*  Software ("bit-bang") UART Transmitter (8 data bits, 1 stop bit, no parity)
    for Attiny24A/44A/84A using the internal 8MHz oscillator as clock source
    (c) 2018 Marcel Meyer-Garcia
    see LICENCE.txt

	timing modifications by Ezer Longinus
 */

 /* NOTE: since the internal 9.6MHz oscillator is not very accurate, the value for OCR0A can be tuned
    to achieve the desired baud rate.
 */

#define F_CPU 9600000

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// change these to use another pin
#define TX_PORT PORTB
#define TX_PIN  PB0
#define TX_DDR  DDRB
#define TX_DDR_PIN DDB0

volatile uint16_t tx_shift_reg = 0;


void UART_tx(char character)
{
   uint16_t local_tx_shift_reg = tx_shift_reg;
   //if sending the previous character is not yet finished, return
   //transmission is finished when tx_shift_reg == 0
   if(local_tx_shift_reg){return;}
   //fill the TX shift register witch the character to be sent and the start & stop bits (start bit (1<<0) is already 0)
   local_tx_shift_reg = (character<<1) | (1<<9); //stop bit (1<<9)
   tx_shift_reg = local_tx_shift_reg;
   //start timer0 with no prescaling
   TCCR0B = (1<<CS00);
}

void UART_tx_str(char* string){
    while( *string ){
        UART_tx( *string++ );
        //wait until transmission is finished
        while(tx_shift_reg);
    }
}

void UART_init(){
   //set TX pin as output
   TX_DDR |= (1<<TX_DDR_PIN);
   TX_PORT |= (1<<TX_PIN);
   //set timer0 to CTC mode
   TCCR0A = (1<<WGM01);
   //enable output compare 0 A interrupt
   TIMSK0 |= (1<<OCF0A);
   //set compare value to 79 to achieve a 115200 baud rate (approximately 83.3�s)
   //together with the 9.6MHz timer0 clock
   /*NOTE: since the internal 9.6MHz oscillator is not very accurate, this value can be tuned
     to achieve the desired baud rate, so if it doesn't work with the nominal value (79), try
     increasing or decreasing the value by 1 or 2 or 4 */
   OCR0A = 79; // Seems to work well with 115200 baud rate (should be around 83.3�s, but the internal clock is a little iffy)
   //OCR0A = 160; // Seems to work well with 57600 baud rate (should be around  166.6�s, but the internal clock...)
   //enable interrupts
   sei();
}

int main(void)
{
   UART_init();

   unsigned long count = 0; // Count the transmissions
   char charBuffer [10]; // char buffer for the printed string
   
   while(1)
   {
    count++;
	ltoa(count, charBuffer, 10);
	UART_tx_str(charBuffer);
    UART_tx_str(".) Hello world!\n");
    _delay_ms(1000);
   }

   return 0;
}

//timer0 compare A match interrupt
ISR(TIM0_COMPA_vect )
{
   uint16_t local_tx_shift_reg = tx_shift_reg;
   //output LSB of the TX shift register at the TX pin
   if( local_tx_shift_reg & 0x01 )
   {
      TX_PORT |= (1<<TX_PIN);
   }
   else
   {
      TX_PORT &=~ (1<<TX_PIN);
   }
   //shift the TX shift register one bit to the right
   local_tx_shift_reg >>= 1;
   tx_shift_reg = local_tx_shift_reg;
   //if the stop bit has been sent, the shift register will be 0
   //and the transmission is completed, so we can stop & reset timer0
   if(!local_tx_shift_reg)
   {
      TCCR0B = 0;
      TCNT0 = 0;
   }
}


