.MODEL small
.STACK 100h
.DATA
	i_1 dw ?
	j_1 dw ?
	k_1 dw ?
	t_0 dw ?
	t_1 dw ?
	t_2 dw ?
	t_3 dw ?
	t_4 dw ?

.CODE
print PROC
	;check neg
	cmp ax, 8000H
	jb positive
negative:
	neg ax
	push ax
	mov ah, 2
	mov dl, '-'
	int 21h
	pop ax
positive:
	mov bx, 10
	mov cx, 0
getVals:
	mov dx, 0
	div bx
	push dx
	inc cx
	cmp ax, 0
	jne getVals
printing:
	mov ah, 2
	pop dx
	add dl, '0'
	int 21h
	dec cx
	cmp cx, 0
	jne printing
	mov dl, 0Ah
	int 21h
	mov dl, 0Dh
	int 21h
	ret 
print ENDP

main proc
	mov ax, @data
	mov ds, ax
	;i=3; 
	mov ax, 3
	mov i_1, ax
	;j=8; 
	mov ax, 8
	mov j_1, ax
	;k=6; 
	mov ax, 6
	mov k_1, ax
	;if (i==3){ println(j); } 
	mov ax, i_1
	cmp ax, 3
	jne L_0
	mov t_0, 1
	jmp L_1
L_0:
	mov t_0, 0
L_1:
	mov ax, t_0
	cmp ax, 0
	je L_2
	;{ println(j); } 
	;println(j); 
	mov ax, j_1
	call print
L_2:
	;if (j<8){ println(i); } else { println(k); } 
	mov ax, j_1
	cmp ax, 8
	jge L_3
	mov t_1, 1
	jmp L_4
L_3:
	mov t_1, 0
L_4:
	mov ax, t_1
	cmp ax, 0
	je L_5
	;{ println(i); } 
	;println(i); 
	mov ax, i_1
	call print
	jmp L_6
L_5:
	;{ println(k); } 
	;println(k); 
	mov ax, k_1
	call print
L_6:
	;if (k!=6){ println(k); } else if (j>8){ println(j); } else if (i<5){ println(i); } else { k=0; println(k); } 
	mov ax, k_1
	cmp ax, 6
	je L_7
	mov t_2, 1
	jmp L_8
L_7:
	mov t_2, 0
L_8:
	mov ax, t_2
	cmp ax, 0
	je L_17
	;{ println(k); } 
	;println(k); 
	mov ax, k_1
	call print
	jmp L_18
L_17:
	;if (j>8){ println(j); } else if (i<5){ println(i); } else { k=0; println(k); } 
	mov ax, j_1
	cmp ax, 8
	jle L_9
	mov t_3, 1
	jmp L_10
L_9:
	mov t_3, 0
L_10:
	mov ax, t_3
	cmp ax, 0
	je L_15
	;{ println(j); } 
	;println(j); 
	mov ax, j_1
	call print
	jmp L_16
L_15:
	;if (i<5){ println(i); } else { k=0; println(k); } 
	mov ax, i_1
	cmp ax, 5
	jge L_11
	mov t_4, 1
	jmp L_12
L_11:
	mov t_4, 0
L_12:
	mov ax, t_4
	cmp ax, 0
	je L_13
	;{ println(i); } 
	;println(i); 
	mov ax, i_1
	call print
	jmp L_14
L_13:
	;{ k=0; println(k); } 
	;k=0; 
	mov ax, 0
	mov k_1, ax
	;println(k); 
	mov ax, k_1
	call print
L_14:
L_16:
L_18:
	;return 0; 
	;dos exit
	mov ah, 4ch
	int 21h

main endp

END main