	.file	"1.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$3223851, -38(%rbp)
	movw	$0, -34(%rbp)
	movzbl	-38(%rbp), %eax
	cmpb	$43, %al
	jne	.L2
	movb	$43, -32(%rbp)
	jmp	.L3
.L2:
	movb	$45, -32(%rbp)
.L3:
	movl	$1, -44(%rbp)
	jmp	.L4
.L7:
	movl	-44(%rbp), %eax
	cltq
	movzbl	-38(%rbp,%rax), %eax
	testb	%al, %al
	je	.L10
	movl	-44(%rbp), %eax
	cltq
	movzbl	-38(%rbp,%rax), %eax
	movzbl	%al, %eax
	subl	$48, %eax
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	movl	%eax, %ecx
	movl	-44(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	addl	$1, %eax
	leal	48(%rcx), %edx
	cltq
	movb	%dl, -32(%rbp,%rax)
	movl	-44(%rbp), %eax
	cltq
	movzbl	-38(%rbp,%rax), %eax
	movzbl	%al, %eax
	leal	-48(%rax), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$30, %eax
	addl	%eax, %edx
	andl	$3, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, %ecx
	movl	-44(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	addl	$2, %eax
	leal	48(%rcx), %edx
	cltq
	movb	%dl, -32(%rbp,%rax)
	movl	-44(%rbp), %eax
	cltq
	movzbl	-38(%rbp,%rax), %eax
	movzbl	%al, %eax
	leal	-48(%rax), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$31, %eax
	addl	%eax, %edx
	andl	$1, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %ecx
	movl	-44(%rbp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	leal	48(%rcx), %edx
	cltq
	movb	%dl, -32(%rbp,%rax)
	jmp	.L6
.L10:
	nop
.L6:
	addl	$1, -44(%rbp)
.L4:
	cmpl	$4, -44(%rbp)
	jle	.L7
	movb	$0, -19(%rbp)
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L9
	call	__stack_chk_fail@PLT
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 13.2.1 20230801"
	.section	.note.GNU-stack,"",@progbits
