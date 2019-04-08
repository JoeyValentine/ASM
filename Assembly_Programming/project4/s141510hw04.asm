TITLE ADD and Sub (s141510hw04.asm)
INCLUDE Irvine32.inc
.data
INCLUDE PHW04.inc
.code
main PROC
	;eax = Eval1 , ebx = Eval2
	mov edx, Val1	;Val1
	mov eax, Val1	;Val1 in Eval1
	add edx, edx	;2*Val1
	add edx, edx	;4*Val1
	add eax, edx	;5*Val1 in Eval1
	add edx, edx	;8*Val1
	add edx, edx	;16*Val1
	mov ebx, edx	;16*Val1 in Eval2
	sub ebx, Val1	;15Val1 in Eval2
	add eax, edx	;21*Val1 in Eval1
	mov edx, Val1	;Val1
	sub edx, Val3	;Val1-Val3
	add eax, edx	;21*Val1 + (Val1-Val3) in Eval1
	add ebx, edx	;15*Val1 + (Val1-Val3) in Eval2
	add edx, edx	;2*(Val1-Val3)
	add edx, edx	;4*(Val1-Val3)
	add edx, edx	;8*(Val1-Val3)
	add ebx, edx	;15*Val1 + 9*(Val1-Val3) in Eval2
	add edx, edx	;16*(Val1-Val3)
	add edx, edx	;32*(Val1-Val3)
	sub eax, edx	;21*Val1 - 31*(Val1-Val3) in Eval1
	mov edx, Val4	;Val4
	sub edx, Val2	;Val4 - Val2
	add eax, edx	;21*Val1 - 31*(Val1-Val3) + (Val4-Val2) in Eval1
	add edx, edx	;2*(Val4-Val2)
	add edx, edx	;4*(Val4-Val2)
	add edx, edx	;8*(Val4-Val2)
	sub eax, edx	;21*Val1 - 31*(Val1-Val3) - 7*(Val4-Val2) in Eval1
	add ebx, edx	;15*Val1 + 9*(Val1-Val3) + 8*(Val4-Val2) in Eval2
	add edx, edx	;16*(Val4-Val2)
	add ebx, edx	;15*Val1 + 9*(Val1-Val3) + 24*(Val4-Val2) in Eval2
	call	DumpRegs
	exit
main ENDP
END main