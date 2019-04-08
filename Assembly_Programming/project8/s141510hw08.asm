TITLE : Finding Max (s141510hw08.asm)
INCLUDE Irvine32.inc

.data
inputString BYTE 32 dup(?)
max BYTE ?	;result of this program
prompt1 BYTE "Numbers? ",0
prompt2 BYTE "Max: ",0
prompt3 BYTE "Bye."
stringLen BYTE ?
maxVal	BYTE 0
temp BYTE ?
flag BYTE 0
.code
main PROC

	Top:
		mov temp, 0
		mov flag, 0
		mov maxVal, 0
		mov edx, OFFSET prompt1
		call WriteString
		mov edx, OFFSET inputString
		mov ecx, 31
		call ReadString
		mov stringLen, al

		cmp eax, 32 ; check whether a string has more than 32 characters or not
		je TOP
		cmp eax, 0
		je L7
		

		mov esi, 0		; check if there are other characters
		mov ecx, 0
		mov cl, stringLen

		L1:
			cmp inputString[esi], ' '	; space
			je next1
			cmp inputString[esi], '	'	; tap
			je next1
			cmp inputString[esi], '0'
			jb TOP 
			cmp inputString[esi], '9'
			ja TOP
			next1: inc esi
		loop L1


		mov ebx, 0		; initialize the ebx to 0
		mov esi, 0		; initialize the esi to 0
		mov ecx, 0
		mov cl, stringLen	; ecx = the number of characters in string

		L3:
			cmp inputString[esi], ' '	;space
			je next2 					;ebx is used to count the number of characters
			cmp inputString[esi], '	'	;tap
			je next2
			inc ebx
			jmp L4
			next2:
			mov ebx, 0
			L4: inc esi
			cmp ebx, 3
			je TOP
		loop L3

		
		mov esi, 0		; initialize the esi to 0
		mov ecx, 0
		mov cl, stringLen	; ecx = the number of characters in string

		mov ecx, 0
		mov cl, stringLen
		call findMax
		cmp flag, 1
		je TOP
		mov edx, OFFSET prompt2
		call WriteString
		mov eax, 0
		mov al, maxVal
		call WriteDec
		call Crlf

	jmp TOP

	L7:
	mov edx, OFFSET prompt3	; print "Bye."
	call WriteString

	exit
main ENDP

	; input ecx = string's length
findMax PROC
	L6:
		mov temp, 0
		cmp inputString[esi], ' ' ; space
		je next5
		cmp inputString[esi], '	' ; tap
		je next5
		cmp inputString[esi+1], ' ' ;space
		je next6
		cmp inputString[esi+1], '	' ; tab
		je next6
		cmp inputString[esi+1], 0
		je next6

		dec ecx
		movzx eax, inputString[esi]; 두 자리수인 경우
		sub eax, '0'
		call mulTen
		mov temp, al
		mov bl, inputString[esi+1]
		sub bl, '0'
		add temp, bl
		inc esi
		cmp temp, 0
		jne next8
		mov flag, 1
		jmp next9
		next8: mov bl, temp
		cmp maxVal, bl
		ja next5
		mov bl, temp
		mov maxVal, bl
		jmp next5

		next6: mov bl, inputString[esi]
		sub bl, '0'
		mov temp, bl	;한 자리수인 경우
		cmp temp, 0
		jne next7
		mov flag, 1
		jmp next9

		next7: mov bl, temp
		cmp maxVal, bl
		ja next5
		mov bl, temp
		mov maxVal, bl
		next5:
		dec ecx
		cmp ecx, 0
		je next9
		inc esi
	jmp L6
	next9:
	ret
findMax ENDP

	; input eax
	; output 10*eax
mulTen PROC
	mov ebx, eax
	add ebx, eax	; ebx = 2*eax
	mov eax, ebx	; eax = 2*eax
	add eax, eax	; eax = 4*eax
	add eax, eax	; eax = 8*eax
	add eax, ebx	; eax = 10*eax
	ret
mulTen ENDP
END main