section .data
fmp_input: db "=======select the menu=======",10,"[1] print 1~19 GuGuDAN",10,"[2] print N DAN",10,"[3] exit Program",10,"=========================",10,0
fms_format: db "%d",0


fmp_whatdan: db "What Dan you want",10,0
fmp_gugusplit: db "==========%d Dan==========",10,0
fmp_gugusplit1: db "==========================",10,0
fmp_guguenter: db 10,0
fmf_gugu: db "%d * %d = %d",10,0

fmp_failed: db "please type valid menu!",10,0

section .text
extern printf
extern scanf
extern exit

global main,_start

main:
_start:
	sub rsp,24
	
	mov rdi, fmp_input
	mov rsi, 0
	mov rax, 0
	call printf

	mov rdi, fms_format
	lea rsi, [rsp+8]
	mov al,0
	call scanf

	cmp DWORD [rsp+8],1
	je menu1
	cmp DWORD [rsp+8],2
	je menu2
	cmp DWORD [rsp+8],3
	je break1

	jmp failed

		menu1:
			mov QWORD [rsp+8],1

			for1:
			mov	QWORD [rsp+16],1
			
			mov rdi, fmp_gugusplit
			mov rsi, [rsp+8]
			xor rax, rax
			call printf

				for2:
					mov rdi, fmf_gugu
					mov rsi, [rsp+8]
					
					mov rax, [rsp+8]
					mul DWORD [rsp+16]
					mov rcx, rax
					xor	 rax,rax
					mov rdx, [rsp+16]
					mov al,0
					call printf

					inc DWORD [rsp+16]
					cmp DWORD [rsp+16],19
					jle for2
			mov rdi, fmp_guguenter
			xor rax, rax
			call printf

			inc QWORD [rsp+8]
			cmp QWORD [rsp+8],19
			jle for1
			
			mov rdi, fmp_gugusplit1
			xor rax, rax
			call printf

			jmp break1
			
		menu2:
			mov rdi, fmp_whatdan
			mov rsi, 0
			mov rax, 0
			call printf

			mov rdi, fms_format
			lea rsi, [rsp+8]
			mov al,0
			call scanf
			
			mov DWORD [rsp+16], 0
			for3:
				inc DWORD [rsp+16]
				cmp DWORD [rsp+16],9
				jg break1

				mov rdi, fmf_gugu
				mov rsi, [rsp+8]	
				mov rax, [rsp+8]
				mul DWORD [rsp+16]
				mov rcx, rax
				xor	 rax,rax
				mov rdx, [rsp+16]
				mov al,0
				call printf

				jmp for3

		failed:
			mov rdi, fmp_failed
			mov rsi, 0
			call printf
			jmp break1
	break1:

	call exit

section .bss
	buf resb 128
