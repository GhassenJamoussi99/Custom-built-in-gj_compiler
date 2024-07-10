.intel_syntax noprefix

.text  # Start the code section

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    # Allocate space for local variable str2
    lea rax, L0
    mov [rbp-8], rax

    lea rdi, L1
    mov rbx, [rbp-8]
    mov rsi, rbx
    call printf
    mov rcx, 0
    mov rax, rcx
    leave
    ret

.data
L0:
	.string " world"
L1:
	.string "%s\n"

