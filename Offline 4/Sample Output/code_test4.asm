.MODEL SMALL
.STACK 1000H
.DATA
FIXED_POINT_MULTIPLIER DW 64H
a DW 1 DUP (0000H)
b DW 1 DUP (0000H)
c DW 1 DUP (0000H)
.CODE
func_a PROC
;>>
	PUSH BP
	MOV BP , SP
	;Line 4: integar = 7
	MOV CX , 7
	MOV a , CX
	;Line 4: CX = assigned value
	func_a_exit:
	POP BP
	RET 0
	;<<
func_a ENDP
foo PROC
;>>
	PUSH BP
	MOV BP , SP
	MOV CX , 4[BP]
	PUSH CX
	;Line 8: integar = 3
	MOV CX , 3
	POP AX
	ADD AX , CX
	MOV CX , AX
	MOV 4[BP] , CX
	;Line 8: CX = assigned value
	MOV CX , 4[BP]
	SUB SP , 0
	JMP foo_exit
	foo_exit:
	POP BP
	RET 2
	;<<
foo ENDP
bar PROC
;>>
	PUSH BP
	MOV BP , SP
	SUB SP , 2
	;>>
		;Line 14: *
		;Line 14: integar = 4
		MOV CX , 4
		PUSH CX
		MOV CX , 4[BP]
		POP AX
		IMUL CX
		MOV CX , AX
		;<<
	PUSH CX
	;>>
		;Line 14: *
		;Line 14: integar = 2
		MOV CX , 2
		PUSH CX
		MOV CX , 6[BP]
		POP AX
		IMUL CX
		MOV CX , AX
		;<<
	POP AX
	ADD AX , CX
	MOV CX , AX
	MOV -2[BP] , CX
	;Line 14: CX = assigned value
	MOV CX , -2[BP]
	SUB SP , -2
	JMP bar_exit
	ADD SP , 2
	bar_exit:
	POP BP
	RET 4
	;<<
bar ENDP
main PROC
;>>
	PUSH BP
	MOV BP , SP
	;Line 40: DATA SEGMENT INITIALIZATION
	MOV AX, @DATA
	MOV DS, AX
	SUB SP , 2
	SUB SP , 2
	SUB SP , 2
	SUB SP , 2
	;Line 23: integar = 5
	MOV CX , 5
	MOV -2[BP] , CX
	;Line 23: CX = assigned value
	;Line 24: integar = 6
	MOV CX , 6
	MOV -4[BP] , CX
	;Line 24: CX = assigned value
	CALL func_a
	MOV CX , a
	PUSH CX
	CALL println_int
	MOV CX , -2[BP]
	PUSH CX
	CALL foo
	MOV -6[BP] , CX
	;Line 29: CX = assigned value
	MOV CX , -6[BP]
	PUSH CX
	CALL println_int
	MOV CX , -4[BP]
	PUSH CX
	MOV CX , -2[BP]
	PUSH CX
	CALL bar
	MOV -8[BP] , CX
	;Line 32: CX = assigned value
	MOV CX , -8[BP]
	PUSH CX
	CALL println_int
	;>>
		;Line 35: *
		;Line 35: integar = 6
		MOV CX , 6
		PUSH CX
		MOV CX , -4[BP]
		PUSH CX
		MOV CX , -2[BP]
		PUSH CX
		CALL bar
		POP AX
		IMUL CX
		MOV CX , AX
		;<<
	PUSH CX
	;Line 35: integar = 2
	MOV CX , 2
	POP AX
	ADD AX , CX
	MOV CX , AX
	PUSH CX
	;>>
		;Line 35: *
		;Line 35: integar = 3
		MOV CX , 3
		PUSH CX
		MOV CX , -2[BP]
		PUSH CX
		CALL foo
		POP AX
		IMUL CX
		MOV CX , AX
		;<<
	POP AX
	SUB AX , CX
	MOV CX , AX
	MOV -4[BP] , CX
	;Line 35: CX = assigned value
	MOV CX , -4[BP]
	PUSH CX
	CALL println_int
	;Line 39: integar = 0
	MOV CX , 0
	SUB SP , -8
	JMP main_exit
	ADD SP , 8
	main_exit:
	POP BP
	;Line 40: EXIT 0
	MOV AH, 4CH
	INT 21H
	RET 0
	;<<
main ENDP
END main
