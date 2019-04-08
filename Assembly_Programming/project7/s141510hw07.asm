TITLE : Alternating Word Reverse (s141510hw07.asm)
INCLUDE Irvine32.inc

.data
inputString BYTE 62 dup(?)
resultString BYTE 62 dup(?)
prompt1 BYTE "Type a string: ",0
prompt2 BYTE "Bye!",0
wordCount BYTE ?	; which is need to count words in a string
odd BYTE 1
wordLen BYTE ?
temp BYTE ?
 
.code
main PROC

	TOP:
		L1:
		cmp ebx, esi					; if esi and ebx(string's length) have same value, then it calls writeString
		jne next7
		mov edx, OFFSET resultString	; prints the result
		call WriteString
		call Crlf
		next7:
		mov edx, OFFSET prompt1
		call WriteString
		call Crlf
		mov edx, OFFSET inputString
		mov ecx, SIZEOF inputString
		call ReadString
		mov ebx, eax					; length of input string in ebx
		cmp eax, 0						; check whether an user type something or not
		je	L2
		cmp eax, 61						; check whether an user type more than 60 words
		jb next			
		jmp L1

		next:

		mov wordCount, 0				; initialize wordCound
		mov esi, 0
		mov ecx, ebx
		inc ecx							; initialize loop index

		L3:
		mov al, inputString[esi]		; strcpy(inputString,resultString)
		mov resultString[esi], al 
		inc esi
		loop L3

		mov esi, 0

		L4:								; word reverse process
		mov al, inputString[esi]
		cmp al, ' '		; space
		je next2
		cmp al, '	'	; tap
		je next2
		inc wordCount
		movzx eax, wordCount
		and eax, 1						; same as eax %= 2
		cmp eax, 1						; if it is odd numbe, word is reversed
		jne next5
		mov wordLen, 0
			L5:							;count a word's length
				mov al, inputString[esi]
				cmp al, ' '			; space
				je next3
				cmp al, '	'		; tap
				je next3
				cmp al, 0
				je next3
				movzx eax, inputString[esi]
				push eax
				inc wordLen
				inc esi
			jmp L5
		next3:

		movzx eax, wordLen
		sub esi, eax
		movzx ecx, wordLen
		cmp ecx, 0				; if ecx==0(if it ends,), then the loop is over
		je L1

		L6:						; reverse a word
		pop eax
		mov resultString[esi], al
		inc esi
		loop L6

		cmp esi, ebx			; if it ends, then the loop is over
		jne next4
		mov inputString[ebx+1], 0
		jmp TOP
		next4:

		next2:
		inc esi
		cmp esi, ebx	;check if it is ends
		je L1
		jmp L4

		next5:

		L7:
			movzx eax, inputString[esi]
			cmp eax, ' '		; space
			je next6
			cmp eax, '	'		; tab
			je next6
			cmp eax, 0			; if it ends, then the loop is over
			je L1
			inc esi
			jmp L7
		jmp L7

		next6:	; go to a next word
		inc esi

		jmp L4

	jmp TOP

	L2:

	mov edx, OFFSET prompt2		; prints "bye!"
	call WriteString
	call Crlf

	exit
main ENDP
END main