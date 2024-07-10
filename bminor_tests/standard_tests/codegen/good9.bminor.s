.intel_syntax noprefix

.text  # Start the code section

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rax, 0
    cmp rax, 0
    je L0
    mov rax, 15
    mov x, rax
    jmp L1
  L0:
    mov rax, 10
    mov x, rax
  L1:
    mov rax, 1
    cmp rax, 0
    je L2
    mov rax, x
    mov rax, rax
    jmp L3
  L2:
    mov rax, 1
    mov rax, rax
  L3:
    leave
    ret

.data
x:
	.quad 5

