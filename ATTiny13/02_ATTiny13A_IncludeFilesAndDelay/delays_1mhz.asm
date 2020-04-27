; delays_1mhz.inc
;-------------------------------------
delay_1s:
	rcall	delay_500ms
	rcall	delay_500ms
	ret
;-------------------------------------
;-------------------------------------
delay_500ms:
	rcall	delay_250ms
	rcall	delay_250ms
	ret
;-------------------------------------
;-------------------------------------
delay_250ms:
	rcall	delay_100ms
	rcall	delay_100ms
	rcall	delay_25ms
	rcall	delay_25ms
	ret
;-------------------------------------
;-------------------------------------
delay_100ms:
	rcall	delay_25ms
	rcall	delay_25ms
	rcall	delay_25ms
	rcall	delay_25ms
	ret
;-------------------------------------
;-------------------------------------
delay_25ms:
	rcall	delay_5ms;
	rcall	delay_5ms;
	rcall	delay_5ms;
	rcall	delay_5ms;
	rcall	delay_5ms;
	ret
;-------------------------------------
;-------------------------------------
delay_5ms:
	rcall	delay_1ms
	rcall	delay_1ms
	rcall	delay_1ms
	rcall	delay_1ms
	rcall	delay_1ms
	ret
;-------------------------------------
;-------------------------------------
delay_1ms:
	push	r16
	ldi		r16,99
delay_1ms1:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dec		r16
	brne	delay_1ms1	; [2 cycles]
	pop		r16			; restore the value of r16
	ret		
;-------------------------------------