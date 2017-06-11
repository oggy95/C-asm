.286
		.model tiny
		.code
		org 100h
		start:  mov ah,4Ah  ;allow mem alloc.
			mov bx,10h  ;новый размер блока в параграфах
			int 21h     
			mov si,offset command_line
			int 2Eh ; execute a command using BASE LEVEL
			mov ah,4Ch  ;выходим из программы
			int 21h
		command_line db N,'DIR',0Dh
		N = $ - command_line - 1
		end  start