.intel_syntax noprefix
.data
x:
   .quad 5

.text  # Start the code section


.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    # Allocate space for local variable y
    mov rax, 2
    mov qword ptr [rbp-8], rax
    mov rax, 10
    mov rax, rax
    leave
    ret
