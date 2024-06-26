.MODEL SMALL
.STACK 400H
.DATA
	d[3] DW 3 DUP(?) ;declared globally at line 1
	e DW ? ;declared globally at line 1
	f DW ? ;declared globally at line 1
.CODE
	g  PROC

		PUSH BP
		MOV BP, SP

		MOV BX, e
		PUSH BX; line no 3: e loaded

		MOV BX, [BP + 6] 
		PUSH BX; line no 3: a loaded

		MOV BX, [BP + 4] 
		PUSH BX; line no 3: b loaded

		POP BX
		POP AX
		ADD BX, AX
		PUSH BX

		POP AX 	;retrieves right operand
		POP BX 	;retrieves left operand
		MOV e, AX; line no 3: e assigned 
		MOV BX, AX ;not needed probably
 		PUSH BX

		POP BX; line no 3: ; previously pushed value on stack is removed

		MOV BX, e
		PUSH BX; line no 4: e loaded

		POP BX 	;line no 4 :  return value saved in DX 
		MOV DX, BX

		EXIT_g_0:
		MOV SP, BP
		POP BP

		RET 4
	g ENDP

	main  PROC

		MOV AX, @DATA
		MOV DS, AX

		SUB SP, 2 ;line no: 7 a declared
		SUB SP, 2 ;line no: 7 b declared
		SUB SP, 10 ;line no: 7 c[3] declared
		MOV BX, [BP + -2] 
		PUSH BX; line no 8: a loaded

		PUSH 3 ;push CONST_INT 
		POP AX 	;retrieves right operand
		POP BX 	;retrieves left operand
		MOV [BP + -2], AX; line no 8: a assigned 
		MOV BX, AX ;not needed probably
 		PUSH BX

		POP BX; line no 8: ; previously pushed value on stack is removed

		MOV BX, [BP + -4] 
		PUSH BX; line no 9: b loaded

		PUSH 2 ;push CONST_INT 
		POP AX 	;retrieves right operand
		POP BX 	;retrieves left operand
		MOV [BP + -4], AX; line no 9: b assigned 
		MOV BX, AX ;not needed probably
 		PUSH BX

		POP BX; line no 9: ; previously pushed value on stack is removed

		MOV BX, [BP + -2] 
		PUSH BX; line no 10: a loaded

		MOV BX, [BP + -4] 
		PUSH BX; line no 10: b loaded

		POP BX 	;line no:10 :  retrieves right operand
		POP AX 	;line no:10 :  retrieves left operand
		CMP AX, BX 
		JL BRANCH_TRUE_1
		MOV BX, 0
		JMP BRANCH_FALSE_2
		BRANCH_TRUE_1:
		MOV BX, 1
		BRANCH_FALSE_2:
		PUSH BX

		POP BX; line no 10: ; previously pushed value on stack is removed

		MOV BX, [BP + -2] 
		PUSH BX; line no 11: a loaded

		MOV BX, [BP + -4] 
		PUSH BX; line no 11: b loaded

		POP BX 	;line no:11 :  retrieves right operand
		POP AX 	;line no:11 :  retrieves left operand
		CMP AX, BX 
		JL BRANCH_TRUE_3
		MOV BX, 0
		JMP BRANCH_FALSE_4
		BRANCH_TRUE_3:
		MOV BX, 1
		BRANCH_FALSE_4:
		PUSH BX

		;line no 11 : If block
		POP BX 
		CMP BX, 0 
		JE ELSE_LABEL_5 

		MOV BX, [BP + -2] 
		PUSH BX; line no 12: a loaded

		PUSH 3 ;push CONST_INT 
		POP AX 	;retrieves right operand
		POP BX 	;retrieves left operand
		MOV [BP + -2], AX; line no 12: a assigned 
		MOV BX, AX ;not needed probably
 		PUSH BX

		POP BX; line no 12: ; previously pushed value on stack is removed

		JMP END_IF_5
		ELSE_LABEL_5:
		MOV BX, [BP + -4] 
		PUSH BX; line no 14: b loaded

		PUSH 2 ;push CONST_INT 
		POP AX 	;retrieves right operand
		POP BX 	;retrieves left operand
		MOV [BP + -4], AX; line no 14: b assigned 
		MOV BX, AX ;not needed probably
 		PUSH BX

		POP BX; line no 14: ; previously pushed value on stack is removed

		END_IF_5:
		;line no 15 :End of If Else block

		MOV BX, [BP + -2] 
		PUSH BX; line no 18: a loaded

		POP BX 	;line no 18 :  return value saved in DX 
		MOV DX, BX

		EXIT_main_6:
		MOV AH, 4CH
		INT 21H

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
            ;INT 21Hn
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