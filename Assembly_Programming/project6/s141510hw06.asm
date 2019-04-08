TITLE from9RadixToDecimal (s141510hw06.asm)
INCLUDE Irvine32.inc

.data
buffer BYTE 9 dup(0)
prompt1 BYTE "Enter a radix 9 number string(<=7 digits) : ",0
prompt2 BYTE "Enter y to repeat(otherwise enter anything) : ",0
prompt3 BYTE "Bye!",0
errorMessage1 BYTE "The string size must be less than 8.",0
errorMessage2 BYTE "The input is not a radix-9 number.",0
opt BYTE 'y'			; What to do next
count DWORD ?			; The loop index
n DWORD ?				; 9^n
result DWORD ?			; Decimal number

.code
main PROC
	mov ebx, 'y'
	top: cmp bl, opt				; Check a loop condition
		 jne next1					; False? Then exit the loop

		 mov edx, OFFSET prompt1	; Receive an input from a user
		 call WriteString
		 mov edx, OFFSET buffer
		 mov ecx, SIZEOF buffer
		 call ReadString

		 cmp buffer, 0				; If an user only type an enter, then repeat the loop
		 je top

		 call StrLength				; Check if an user type more than 7 digits
		 cmp eax, 8
		 jb next2
		 mov edx, OFFSET errorMessage1
		 call WriteString
		 call Crlf
		 jmp top
		 next2:

		 mov ecx, eax				; Check if an user type a wrong character
		 mov esi, OFFSET buffer
		 L1:
			mov al, [esi]
			inc esi
			cmp al, '0'
			jb next3
			cmp al, '9'
			jae next3
			jmp next4
			next3:
			mov edx, OFFSET errorMessage2
			call WriteString
			call Crlf
			mov ebx, 'y'
			jmp top
			next4:
		 loop L1

		 call StrLength				; Call from9_radixToDecimal to convert 9 radix number to decimal number
		 mov esi, OFFSET buffer
		 add esi, eax
		 dec esi
		 call from9_radixToDecimal;

		 mov esi, OFFSET result		; Print the result
		 mov eax, result
		 call WriteDec
		 call Crlf

		 mov edx, OFFSET prompt2	; If an user type 'y',then repeat the loop
		 call WriteString			; If an user type anything else,then the loop ends
		 call ReadChar
		 mov bl, al	

		 call WriteChar				; Using Readchar, we cannot see an user's input.
		 call Crlf					; So, we call WriteChar to see the input

	jmp top			; repeat the loop
	next1:			; exit for the loop

	mov edx, OFFSET prompt3
	call WriteString
	
	exit
main ENDP

;input : esi = string's address  eax = string's length
;output : ebx : result

from9_radixToDecimal PROC

	mov ecx, eax	; Stores loop index
	dec ecx
	mov n, 1
	mov result, 0

	mov eax, 0
	mov al, [esi]
	sub eax, '0'
	dec esi
	add result, eax

	cmp ecx, 0
	je next6

	L2:
	mov count, ecx	; save outer loop count
	mov eax, 0
	mov al, [esi]
	sub al, '0'
	mov ecx, n

	L3:
	call mulNine
	loop L3
	add result, eax

	dec esi
	inc n
	mov ecx, count
	loop L2

	next6:
	ret
from9_radixToDecimal ENDP

; input : eax = number
; output : eax = 9 * number

mulNine PROC
	mov ebx, eax	; ebx = x
	add eax, eax	; eax = 2x
	add eax, eax	; eax = 4x
	add eax, eax	; eax = 8x
	add eax, ebx	; eax = 9x = 8x + x
	ret
mulNine ENDP
END main