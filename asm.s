.intel_syntax noprefix

.text  # Start the code section

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rax, 0
    mov x, rax
  L0:
    mov rax, x
    mov rbx, 11
    cmp rax, rbx
    setl al
    movzx rax, al
    cmp rax, 0
    je L1
    lea rdi, L2
    mov rax, x
    mov rsi, rax
    call printf
    mov rbx, x
    mov rcx, 1
    add rbx, rcx
    mov x, rbx
    jmp L0
  L1:
    mov rbx, 0
    mov rax, rbx
    leave
    ret

.data
x:
	.quad 1
L2:
	.string "%d\n"

