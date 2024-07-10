.intel_syntax noprefix

.text  # Start the code section

.globl gcd
gcd:
    push rbp
    mov rbp, rsp
    sub rsp, 16
L0:
    mov rax, [rbp + 24]
    mov rbx, [rbp + 32]
    cmp rax, rbx
    setne al
    movzx rax, al
cmp rax, 0
je L1
    mov rax, [rbp + 24]
    mov rbx, [rbp + 32]
    cmp rax, rbx
    setg al
    movzx rax, al
    cmp rax, 0
    je L2
    mov rax, [rbp + 24]
    mov rbx, [rbp + 32]
    sub rax, rbx
    mov [rbp + 24], rax
    jmp L3
  L2:
    mov rax, [rbp + 32]
    mov rcx, [rbp + 24]
    sub rax, rcx
    mov [rbp + 32], rax
  L3:
jmp L0
L1:
    mov rax, [rbp + 24]
    mov rax, rax
    leave
    ret

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    lea rdi, L4
    call printf
    lea rdi, L5
    mov rdx, 48
    mov rsi, 18
    push rsi
    push rdx
    push rax
    call gcd
    mov rdx, rax
    pop rax
    add rsp, 16
    mov rsi, rdx
    call printf
    mov rsi, 0
    mov rax, rsi
    leave
    ret

.data
L4:
	.string "GCD Tests\n"
L5:
	.string "%d\n"

