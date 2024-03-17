	.file	"main.c"
	.text
	.globl	maxValues
	.type	maxValues, @function
maxValues:
.LFB7:
	.cfi_startproc
	movq	%rdi, %r9
	movq	%rsi, %r8
	movq	%rdx, %rdi
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	xorl	%edx, %edx
.L4:
	movb	(%r9,%rcx), %sil
	cmpb	%dl, %sil
	ja	.L5
	je	.L2
	cmpb	%al, %sil
	cmova	%esi, %eax
	jmp	.L2
.L5:
	movl	%edx, %eax
	movl	%esi, %edx
.L2:
	incq	%rcx
	cmpq	$256, %rcx
	jne	.L4
	movb	%dl, (%r8)
	movb	%al, (%rdi)
	ret
	.cfi_endproc
.LFE7:
	.size	maxValues, .-maxValues
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"r"
.LC1:
	.string	"Impossible to open the file : %s\n"
.LC2:
	.string	"Empty file: %s\n"
.LC3:
	.string	"Memory allocation error :%s /%d\n"
.LC4:
	.string	"Error reading file : %s\n"
	.text
	.globl	loadFile
	.type	loadFile, @function
loadFile:
.LFB8:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rsi, %r14
	leaq	.LC0(%rip), %rsi
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movq	%rdi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	pushq	%rcx
	.cfi_def_cfa_offset 64
	call	fopen@PLT
	testq	%rax, %rax
	jne	.L13
	movq	stderr(%rip), %rdi
	movq	%r13, %rdx
	leaq	.LC1(%rip), %rsi
	xorl	%eax, %eax
	call	fprintf@PLT
	jmp	.L19
.L13:
	xorl	%esi, %esi
	movq	%rax, %rbp
	movl	$2, %edx
	movq	%rax, %rdi
	call	fseek@PLT
	movq	%rbp, %rdi
	call	ftell@PLT
	xorl	%edx, %edx
	xorl	%esi, %esi
	movq	%rbp, %rdi
	movq	%rax, %rbx
	call	fseek@PLT
	testl	%ebx, %ebx
	jg	.L15
	movq	stderr(%rip), %rdi
	movq	%r13, %rdx
	leaq	.LC2(%rip), %rsi
	xorl	%eax, %eax
	call	fprintf@PLT
	movq	%rbp, %rdi
	call	fclose@PLT
.L19:
	xorl	%r12d, %r12d
	jmp	.L12
.L15:
	leal	2(%rbx), %edi
	movslq	%edi, %rdi
	call	malloc@PLT
	movq	%rax, %r12
	testq	%rax, %rax
	jne	.L16
	movq	stderr(%rip), %rdi
	movl	%ebx, %ecx
	movq	%r13, %rdx
	xorl	%eax, %eax
	leaq	.LC3(%rip), %rsi
	call	fprintf@PLT
	movq	%rbp, %rdi
	call	fclose@PLT
	jmp	.L12
.L16:
	movslq	%ebx, %r15
	movq	%rbp, %rcx
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	call	fread@PLT
	cmpl	%eax, %ebx
	je	.L17
	movq	stderr(%rip), %rdi
	movq	%r13, %rdx
	leaq	.LC4(%rip), %rsi
	xorl	%eax, %eax
	call	fprintf@PLT
	movq	%rbp, %rdi
	call	fclose@PLT
	movq	%r12, %rdi
	call	free@PLT
	jmp	.L19
.L17:
	movq	%rbp, %rdi
	call	fclose@PLT
	movl	%ebx, (%r14)
	movb	$0, (%r12,%r15)
.L12:
	popq	%rdx
	.cfi_def_cfa_offset 56
	movq	%r12, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE8:
	.size	loadFile, .-loadFile
	.section	.rodata.str1.1
.LC5:
	.string	"fontm.spr"
.LC6:
	.string	"%d/%x\n"
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	leaq	.LC5(%rip), %rdi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$272, %rsp
	.cfi_def_cfa_offset 304
	leaq	12(%rsp), %rsi
	leaq	16(%rsp), %r12
	call	loadFile
	movl	12(%rsp), %esi
	leaq	.LC6(%rip), %rdi
	movq	%rax, %rbx
	xorl	%eax, %eax
	movl	%esi, %edx
	movq	%rbx, %rbp
	call	printf@PLT
.L21:
	movl	%ebp, %r10d
	subl	%ebx, %r10d
	cmpl	%r10d, 12(%rsp)
	jle	.L26
	xorl	%eax, %eax
	movl	$64, %ecx
	movq	%r12, %rdi
	rep stosl
	xorl	%eax, %eax
.L22:
	movsbq	0(%rbp,%rax), %rdx
	incq	%rax
	incb	16(%rsp,%rdx)
	cmpq	$16, %rax
	jne	.L22
	leaq	11(%rsp), %rdx
	leaq	10(%rsp), %rsi
	movq	%r12, %rdi
	addq	$16, %rbp
	call	maxValues
	movzbl	10(%rsp), %edx
	movl	%r10d, %esi
	xorl	%eax, %eax
	leaq	.LC6(%rip), %rdi
	call	printf@PLT
	jmp	.L21
.L26:
	addq	$272, %rsp
	.cfi_def_cfa_offset 32
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
