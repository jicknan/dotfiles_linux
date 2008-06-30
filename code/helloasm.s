	.file	"helloasm.c"
.globl message
	.data
	.type	message, @object
	.size	message, 15
message:
	.string	"Hello, world!\n"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	subl	$16, %esp
	movl	$message, %ecx
	movl	$4, %eax
	movl	$1, %ebx
	movl	$15, %edx
#APP
# 15 "helloasm.c" 1
	int $0x80
# 0 "" 2
#NO_APP
	movl	%eax, -12(%ebp)
	movl	$0, %eax
	addl	$16, %esp
	popl	%ecx
	popl	%ebx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.3.0"
	.section	.note.GNU-stack,"",@progbits
