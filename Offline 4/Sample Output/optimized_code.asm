.MODEL SMALL

.STACK 400h; 1KB stack

.DATA

	
	d		DW		3 DUP(0); line no 1 : d declared
	e		DW		0; line no 1 : e declared
	f		DW		0; line no 1 : f declared
		
.CODE
		

	g  PROC
		
		PUSH BP
        MOV BP, SP
        
        ; STORING THE GPRS
        ; DX for returning results
        PUSH AX
        PUSH BX
        PUSH CX
        PUSHF
        
        
		
		MOV BX, [ e+0 ]
		PUSH BX; line no 3 : e loaded
		
		MOV BX, [ BP+4 ]
		PUSH BX; line no 3 : a loaded
		
		MOV BX, [ BP+6 ]
; peepholed 38		PUSH BX; line no 3 : b loaded

; peepholed 36		POP BX
		POP AX
		ADD BX, AX
		PUSH BX

		POP AX
		MOV [e + 0], AX; line no 3 : e assined
		MOV BX, AX
; peepholed 48		PUSH BX

; peepholed 46		POP BX; line no 3 : ; previously pushed value on stack is removed
		
		
		MOV BX, [ e+0 ]
; peepholed 53		PUSH BX; line no 4 : e loaded
; peepholed 52		POP BX; line no 4 :  return value saved in DX 
		MOV DX, BX
		JMP @L_1; line no 4 :  ; exit from the function
		
		; return point g
		@L_1:
		MOV SP, BP
		SUB SP, 8
		POPF  
        
        POP CX
        POP BX
        POP AX
        
        POP BP
		RET 4
		

	g ENDP

	main  PROC
		
		mov AX, @DATA
		mov DS, AX
		; data segment loaded
		
		PUSH BX ; line no 7 : a declared
		PUSH BX ; line no 7 : b declared
		MOV CX, 3; line no 7 : ; new array of size 3
		@L_3:
		JCXZ @L_4
		PUSH BX
		DEC CX
		JMP @L_3
		@L_4: 
		
		MOV BX, [ BP-10 ]
		PUSH BX; line no 8 : a loaded
		
		PUSH 3
		POP AX
		MOV [BP + -10], AX; line no 8 : a assined
		MOV BX, AX
; peepholed 98		PUSH BX

; peepholed 96		POP BX; line no 8 : ; previously pushed value on stack is removed
		
		MOV BX, [ BP-12 ]
		PUSH BX; line no 9 : b loaded
		
		PUSH 2
		POP AX
		MOV [BP + -12], AX; line no 9 : b assined
		MOV BX, AX
; peepholed 109		PUSH BX

; peepholed 107		POP BX; line no 9 : ; previously pushed value on stack is removed
		
		MOV BX, [ BP-10 ]
		PUSH BX; line no 10 : a loaded
		
		MOV BX, [ BP-12 ]
; peepholed 118		PUSH BX; line no 10 : b loaded
		

; peepholed 115		POP BX
		POP AX
		CMP AX, BX; line no 10 :  relop operation
		MOV BX, 1; line no 10 :  First let it assume positive
		JL @L_5
		MOV BX, 0; line no 10 :  the condition is false
		@L_5: 

; peepholed 128		PUSH BX

; peepholed 126		POP BX; line no 10 : ; previously pushed value on stack is removed
		
		; line no 14 :  starting while loop
		@L_7: 

		
		MOV BX, [ BP-10 ]
		PUSH BX; line no 11 : a loaded
		
		PUSH 3
		

		POP BX
		POP AX
		CMP AX, BX; line no 11 :  relop operation
		MOV BX, 1; line no 11 :  First let it assume positive
		JL @L_6
		MOV BX, 0; line no 11 :  the condition is false
		@L_6: 

; peepholed 150		PUSH BX

; peepholed 148		POP BX
		CMP BX, 0
		JE @L_8 ;condition false. so jump to exit
		
		MOV BX, [ BP-12 ]
		PUSH BX; line no 12 : b loaded
		
		PUSH 2
		POP AX
		MOV [BP + -12], AX; line no 12 : b assined
		MOV BX, AX
; peepholed 163		PUSH BX

; peepholed 161		POP BX; line no 12 : ; previously pushed value on stack is removed
		
		MOV BX, [ BP-10 ]
		PUSH BX; line no 13 : a loaded
		POP AX
		PUSH AX

		INC AX
		MOV [BP + -10], AX; line no 13 : 
		POP BX; line no 13 : ; previously pushed value on stack is removed
		JMP @L_7; again go to begining
		@L_8: 	; line no 14 : while loop end
		
		
		MOV BX, [ BP-10 ]
; peepholed 179		PUSH BX; line no 16 : a loaded
; peepholed 178		POP BX; line no 16 :  return value saved in DX 
		MOV DX, BX
		JMP @L_2; line no 16 :  ; exit from the function
		
		; return point main
		@L_2: 
		mov AH, 4Ch
		int 21h
		; returned control to OS
		

	main ENDP
		

	PRINT_NEWLINE PROC
        ; PRINTS A NEW LINE WITH CARRIAGE RETURN
        PUSH AX
        PUSH DX
        MOV AH, 2
        MOV DL, 0Dh
        INT 21h
        MOV DL, 0Ah
        INT 21h
        POP DX
        POP AX
        RET
    PRINT_NEWLINE ENDP
    
    PRINT_CHAR PROC
        ; PRINTS A 8 bit CHAR 
        ; INPUT : GETS A CHAR VIA STACK 
        ; OUTPUT : NONE    
        PUSH BP
        MOV BP, SP
        
        ; STORING THE GPRS
        PUSH AX
        PUSH BX
        PUSH CX
        PUSH DX
        PUSHF
        
        
        
        MOV DX, [BP + 4]
        MOV AH, 2
        INT 21H
        
        
        
        POPF  
        
        POP DX
        POP CX
        POP BX
        POP AX
        
        POP BP
        RET 2
    PRINT_CHAR ENDP 

    PRINT_DECIMAL_INTEGER PROC NEAR
        ; PRINTS SIGNED INTEGER NUMBER WHICH IS IN HEX FORM IN ONE OF THE REGISTER
        ; INPUT : CONTAINS THE NUMBER  (SIGNED 16BIT) IN STACK
        ; OUTPUT : 
        
        ; STORING THE REGISTERS
        PUSH BP
        MOV BP, SP
        
        PUSH AX
        PUSH BX
        PUSH CX
        PUSH DX
        PUSHF
        
        MOV AX, [BP+4]
        ; CHECK IF THE NUMBER IS NEGATIVE
        OR AX, AX
        JNS @POSITIVE_NUMBER
        ; PUSHING THE NUMBER INTO STACK BECAUSE A OUTPUT IS WILL BE GIVEN
        PUSH AX

        MOV AH, 2
        MOV DL, 2Dh
        INT 21h

        ; NOW IT'S TIME TO GO BACK TO OUR MAIN NUMBER
        POP AX

        ; AX IS IN 2'S COMPLEMENT FORM
        NEG AX

        @POSITIVE_NUMBER:
            ; NOW PRINTING RELATED WORK GOES HERE

            XOR CX, CX      ; CX IS OUR COUNTER INITIALIZED TO ZERO
            MOV BX, 0Ah
            @WHILE_PRINT:
                
                ; WEIRD DIV PROPERTY DX:AX / BX = VAGFOL(AX) VAGSESH(DX)
                XOR DX, DX
                ; AX IS GUARRANTEED TO BE A POSITIVE NUMBER SO DIV AND IDIV IS SAME
                DIV BX                     
                ; NOW AX CONTAINS NUM/10 
                ; AND DX CONTAINS NUM%10
                ; WE SHOULD PRINT DX IN REVERSE ORDER
                PUSH DX
                ; INCREMENTING COUNTER 
                INC CX

                ; CHECK IF THE NUM IS 0
                OR AX, AX
                JZ @BREAK_WHILE_PRINT; HERE CX IS ALWAYS > 0

                ; GO AGAIN BACK TO LOOP
                JMP @WHILE_PRINT

            @BREAK_WHILE_PRINT:

            ;MOV AH, 2
            ;MOV DL, CL 
            ;OR DL, 30H
            ;INT 21H
            @LOOP_PRINT:
                POP DX
                OR DX, 30h
                MOV AH, 2
                INT 21h

                LOOP @LOOP_PRINT

        CALL PRINT_NEWLINE
        ; RESTORE THE REGISTERS
        POPF
        POP DX
        POP CX
        POP BX
        POP AX
        
        POP BP
        
        RET


    PRINT_DECIMAL_INTEGER ENDP

END MAIN
