.intel_syntax noprefix

.text  # Start the code section

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    # Allocate space for local variable str3
    lea rax, L0
    mov [rbp-8], rax

    lea rbx, str
    mov rcx, [rbp-8]
    cmp rbx, rcx
    sete al
    movzx rbx, al
    cmp rbx, 0
    je L1
    lea rdi, L3
    lea rbx, str
    mov rsi, rbx
    call printf
    jmp L2
  L1:
  L2:
    mov rcx, 0
    mov rax, rcx
    leave
    ret

.data
str:
	.string "hello"
str2:
	.string " world"
L0:
	.string 
L3:
	.string "%s\n"

