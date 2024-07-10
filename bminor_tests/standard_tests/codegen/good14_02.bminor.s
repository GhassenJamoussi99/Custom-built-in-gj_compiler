.intel_syntax noprefix

.text  # Start the code section

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    # Allocate space for local variable y
    mov rax, 0
    mov [rbp-8], rax

  L0:
    mov rax, [rbp-8]
    mov rbx, 10
    cmp rax, rbx
    setl al
    movzx rax, al
    cmp rax, 0
    je L1
    lea rdi, L2
    mov rax, [rbp-8]
    mov rsi, rax
    call printf
    mov rbx, [rbp-8]
    mov rcx, 1
    add rbx, rcx
    mov [rbp-8], rbx
    jmp L0
  L1:
    mov rbx, 0
    mov rax, rbx
    leave
    ret

.data
L2:
	.string "%d\n"

