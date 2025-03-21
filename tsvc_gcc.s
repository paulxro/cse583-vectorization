s235:
.LFB88:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leaq	1024+bb(%rip), %r15
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	leaq	__func__.103(%rip), %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movl	$78000, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	leaq	c(%rip), %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	leaq	a(%rip), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdi, %rbx
	movq	%r14, %rdi
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	call	initialise_arrays@PLT
	xorl	%esi, %esi
	movq	%rbx, %rdi
	call	gettimeofday@PLT
	leaq	aa(%rip), %r9
	leaq	b(%rip), %rsi
	leaq	1024(%r9), %r10
	leaq	d(%rip), %rcx
.L584:
	xorl	%r11d, %r11d
.L586:
	movaps	(%r12,%r11), %xmm1
	mulps	(%rsi,%r11), %xmm1
	leaq	(%r10,%r11), %r8
	xorl	%eax, %eax
	addps	0(%rbp,%r11), %xmm1
	leaq	(%r15,%r11), %rdi
	leaq	(%r9,%r11), %rdx
	movaps	%xmm1, 0(%rbp,%r11)
	.p2align 4,,10
	.p2align 3
.L585:
	movaps	(%rdi,%rax), %xmm0
	mulps	%xmm1, %xmm0
	addps	(%rdx,%rax), %xmm0
	movaps	%xmm0, (%r8,%rax)
	addq	$1024, %rax
	cmpq	$261120, %rax
	jne	.L585
	addq	$16, %r11
	cmpq	$1024, %r11
	jne	.L586
	leaq	cc(%rip), %rax
	movq	%r12, %rdx
	pxor	%xmm0, %xmm0
	movq	%rbp, %rdi
	pushq	%rax
	.cfi_def_cfa_offset 72
	leaq	bb(%rip), %rax
	leaq	e(%rip), %r8
	pushq	%rax
	.cfi_def_cfa_offset 80
	call	dummy@PLT
	leaq	aa(%rip), %r9
	subl	$1, %r13d
	popq	%rax
	.cfi_def_cfa_offset 72
	leaq	b(%rip), %rsi
	popq	%rdx
	.cfi_def_cfa_offset 64
	leaq	d(%rip), %rcx
	leaq	1024(%r9), %r10
	jne	.L584
	leaq	16(%rbx), %rdi
	xorl	%esi, %esi
	call	gettimeofday@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 56
	movq	%r14, %rdi
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
	jmp	calc_checksum@PLT
	.cfi_endproc
.LFE88:
	.size	s235, .-s235
	.p2align 4
	.globl	s241
	.type	s241, @function