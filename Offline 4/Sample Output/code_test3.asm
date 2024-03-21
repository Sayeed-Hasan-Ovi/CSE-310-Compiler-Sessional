.MODEL SMALL

.STACK 100H

.DATA
	i_1_1 DW ?
	j_1_1 DW ?
	k_1_1 DW ?
	ll_1_1 DW ?
	t1 DW ?
	t2 DW ?
	t3 DW ?
	t4 DW ?
	t5 DW ?
	t6 DW ?


.CODE

	main PROC

		;initialize DS
		MOV AX, @DATA
		MOV DX, AX

		; int i,j,k,ll;

		; for(i=0; i<6;i++) {
		; println(i);
		; }
		MOV t1, 0
		MOV AX, t1
		MOV i_1_1, AX
		L2:
		MOV t1, 6
		MOV AX, i_1_1
		CMP AX, t1
		JL L0
		MOV t1, 0
		JMP L1
		L0:
		MOV t1, 1
		L1:
		CMP t1, 0
		JE L3

		; println(i);
		PUSH i_1_1
		CALL integerOutput

		MOV AX, i_1_1
		MOV t2, AX
		INC i_1_1
		JMP L2
		L3:

		; k=4;
		MOV t3, 4
		MOV AX, t3
		MOV k_1_1, AX

		; ll=6;
		MOV t3, 6
		MOV AX, t3
		MOV ll_1_1, AX

		; while(k>0) {
		; ll=ll+3;
		; k--;
		; }
		L6:
		MOV t3, 0
		MOV AX, k_1_1
		CMP AX, t3
		JG L4
		MOV t3, 0
		JMP L5
		L4:
		MOV t3, 1
		L5:
		CMP t3, 0
		JE L7

		; ll=ll+3;
		MOV t4, 3
		MOV AX, ll_1_1
		ADD AX, t4
		MOV t4, AX
		MOV AX, t4
		MOV ll_1_1, AX

		; k--;
		MOV AX, k_1_1
		MOV t4, AX
		DEC k_1_1

		JMP L6
		L7:

		; println(ll);
		PUSH ll_1_1
		CALL integerOutput

		; println(k);
		PUSH k_1_1
		CALL integerOutput

		; k=4;
		MOV t5, 4
		MOV AX, t5
		MOV k_1_1, AX

		; ll=6;
		MOV t5, 6
		MOV AX, t5
		MOV ll_1_1, AX

		; while(k--) {
		; ll=ll+3;
		; }
		L8:
		MOV AX, k_1_1
		MOV t5, AX
		DEC k_1_1
		CMP t5, 0
		JE L9

		; ll=ll+3;
		MOV t6, 3
		MOV AX, ll_1_1
		ADD AX, t6
		MOV t6, AX
		MOV AX, t6
		MOV ll_1_1, AX

		JMP L8
		L9:

		; println(ll);
		PUSH ll_1_1
		CALL integerOutput

		; println(k);
		PUSH k_1_1
		CALL integerOutput

		; return 0;
		MOV t6, 0
		MOV BP, SP
		MOV AX, t6
		MOV [BP+2], AX
		   

		;DOS EXIT
		MOV AH, 4CH
		INT 21H

	main ENDP

	integerOutput PROC
		;save registers to stack
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		PUSH BP

		;extract number
		MOV BP, SP
		MOV AX, [BP+12]

		;check if negative
		CMP AX, 0
		JGE POSITIVE2
		PUSH AX
		MOV DL, '-'
		MOV AH, 2
		INT 21H
		POP AX
		NEG AX

		;extract digits
		POSITIVE2:
		MOV CX, 0
		MOV BX, 10D

		WHILE_2:
			MOV DX, 0
			DIV BX
			PUSH DX
			INC CX
			CMP AX, 0
			JNE WHILE_2

		;print digits
		MOV AH, 2

		WHILE_3:
			POP DX
			ADD DL, '0'
			INT 21H
			LOOP WHILE_3
		MOV DL, 20H
		INT 21H

		;restore saved registers from stack
		POP BP
		POP DX
		POP CX
		POP BX
		POP AX

		RET 2

	integerOutput ENDP

END MAIN

