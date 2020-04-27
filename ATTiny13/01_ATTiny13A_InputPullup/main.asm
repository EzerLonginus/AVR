;
; 01_ATTiny13A_InputPullup.asm
;
; Created: 4/26/2020 3:32:32 PM
; Author : Ezer Longinus
; 
; This program shows input and output of a port
.org		0x0000		; Store in memory starting here
	ldi		r16,0b1000	; Make Port B bit 3 output (1), and
	out		ddrb,r16	; make Port B bit 1 input (0);
	ldi		r17,0b0010	; Enable Input Pull-Up
	out		portb,r17	; on pin 1
	nop					; Allow time for ddrb to change
poll_input:
	in		r0,pinb		; Read Port B as input
	mov		r16,r0		; Transfer r0 into r16
	;in		r16,pinb	; This register also works for reading inputs
	andi	r16,0b10	; Isolate bit1, zero all other bits in that register
	lsl		r16			; Logical shift left one
	lsl		r16			; Logical shift left one
	ori		r16,0b10	; Maintain Enabled Input Pull-Up
	out		portb, r16	; Output r16 to Port B
	rjmp	poll_input	; Back to main loop		
