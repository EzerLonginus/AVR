;
; 02_ATTiny13A_IncludeFilesAndDelay.asm
;
; Created: 4/26/2020 3:05:18 PM
; Author : Ezer Longinus
;

.org		0x0000
	ldi		r16,0b00001111	; Make the lower 4 bits output
	out		ddrb,r16		; for Port B
top:
	sbi		portb,3			; Set bit 3 immediate of port b
	rcall	delay_1s		; Calling a subroutine

	cbi		portb,3			; Clear bit 3 immediate of port b
	rcall	delay_1s		; 

	rjmp	top

.include "delays_1mhz.asm"	
