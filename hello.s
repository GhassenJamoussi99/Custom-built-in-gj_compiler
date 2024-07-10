.intel_syntax noprefix
.text

.global main
	main:
	push rbx
	mov ebx, edi
	lea rdi, h[rip]
	call puts
	movsx rdi, ebx
	lea rax, b[rip]
	mov rax, [rax+rdi*8]
	lea rdx, a[rip]
	add eax, [rdx+rdi*8]
	pop rbx
	ret

.data
h:
	.string "Hello world"
b:
	.quad 42
	.quad 73
	.zero 784
a:
	.zero 800