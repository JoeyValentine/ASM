TITLE PASSWORD GENERATOR (s141510hw05.asm)
INCLUDE Irvine32.inc

.data
filename BYTE "s141510hw05.txt",0
passwordNum DWORD ?
passwordSize DWORD ?
prompt1 BYTE "Enter the number of passwrods to create(<=255) : ",0
prompt2 BYTE "Enter the password size(<=32) : ",0
complete BYTE "Generated!",0
filehand DWORD ?
temp DWORD ?
tempEsi DWORD ?
newline BYTE 13,10
String_buf BYTE 32 dup(?)

.code
main PROC

	mov edx, OFFSET prompt1		; save a string's address
	call WriteString			; print a message
	call ReadInt				; input an integer
	mov passwordNum, eax		; save a data to memory
	
	mov edx, OFFSET prompt2		; get data
	call WriteString			; print a message
	call ReadInt				; input an integer
	mov passwordSize, eax		; save data to memory
	
	mov edx, OFFSET filename	; create a File
	call CreateOutputFile
	mov filehand, eax			; save file's address

	call Randomize				; initialize a seed value
	mov esi, OFFSET String_buf	; points to string
	mov tempEsi, esi

	mov edx, OFFSET String_buf	; save string's address to edx
	mov ecx, passwordNum
	sub ecx, 1

	L3: mov temp, ecx			; store iteration variable

	mov eax, passwordSize
	mov esi, tempEsi
	pushad						; pushad and pushfd is used to protect general registers from changing
	pushfd
	call CreateRandomString
	popfd						; restore all general registers
	popad

	mov ecx, passwordSize		; store a string's size
	mov eax, filehand
	mov edx, OFFSET String_buf
	pushad						
	call WriteToFile			; write a stirng
	popad

	pushad						
	mov ecx, 2;
	mov edx, OFFSET newline		; write a newline
	call WriteToFile
	popad
	
	mov ecx, temp				; restore an iteration variable
	;add edx, passwordSize
	loop L3
			
	mov eax, passwordSize
	mov esi, tempEsi
	pushad						; pushad and pushfd is used to protect general registers from changing
	pushfd
	call CreateRandomString
	popfd						; restore all general registers
	popad

	mov eax, filehand
	mov ecx, passwordSize
	mov edx, OFFSET String_buf
	pushad
	call WriteToFile			;write a last line
	popad

	call CloseFile				; closing a file

	mov edx, OFFSET complete	; print a last message
	call WriteString

	exit
main ENDP
;----------------------------------------------------------
;	CreateRandomString USES eax, esi
;
;	input: eax the number of strings, esi points to array
;	ouput: a string which consists of uppercase alphabet
;----------------------------------------------------------
CreateRandomString PROC
	mov ecx, eax			; save a repeating number
	L2 : mov eax, 26		; set the number's range from 0 to 25
	call RandomRange		; get random number
	add al, 65				; add 65 to get uppercase alphabet
	mov [esi], al			; store a character in memory
	inc esi
	loop L2
	ret
CreateRandomString ENDP
END main