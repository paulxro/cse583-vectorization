s235:                                   # @s235
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%r13
	.cfi_def_cfa_offset 40
	pushq	%r12
	.cfi_def_cfa_offset 48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	pushq	%rax
	.cfi_def_cfa_offset 64
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	%rdi, %rbx
	leaq	.L__func__.s235(%rip), %rdi
	callq	initialise_arrays@PLT
	xorl	%ebp, %ebp
	movq	%rbx, (%rsp)                    # 8-byte Spill
	movq	%rbx, %rdi
	xorl	%esi, %esi
	callq	gettimeofday@PLT
	leaq	b(%rip), %r14
	leaq	c(%rip), %r15
	leaq	a(%rip), %r12
	leaq	aa(%rip), %r13
	leaq	e(%rip), %rbx
	.p2align	4, 0x90
.LBB49_1:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB49_2 Depth 2
                                        #       Child Loop BB49_3 Depth 3
	leaq	bb+3072(%rip), %rax
	leaq	aa+3072(%rip), %rcx
	xorl	%edx, %edx
	.p2align	4, 0x90
.LBB49_2:                               #   Parent Loop BB49_1 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB49_3 Depth 3
	movss	(%r15,%rdx,4), %xmm0            # xmm0 = mem[0],zero,zero,zero
	mulss	(%r14,%rdx,4), %xmm0
	addss	(%r12,%rdx,4), %xmm0
	movss	%xmm0, (%r12,%rdx,4)
	movss	(%r13,%rdx,4), %xmm1            # xmm1 = mem[0],zero,zero,zero
	xorl	%esi, %esi
	.p2align	4, 0x90
.LBB49_3:                               #   Parent Loop BB49_1 Depth=1
                                        #     Parent Loop BB49_2 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	movss	-2048(%rax,%rsi), %xmm2         # xmm2 = mem[0],zero,zero,zero
	mulss	%xmm0, %xmm2
	addss	%xmm1, %xmm2
	movss	%xmm2, -2048(%rcx,%rsi)
	movss	-1024(%rax,%rsi), %xmm3         # xmm3 = mem[0],zero,zero,zero
	mulss	%xmm0, %xmm3
	addss	%xmm2, %xmm3
	movss	%xmm3, -1024(%rcx,%rsi)
	movss	(%rax,%rsi), %xmm1              # xmm1 = mem[0],zero,zero,zero
	mulss	%xmm0, %xmm1
	addss	%xmm3, %xmm1
	movss	%xmm1, (%rcx,%rsi)
	addq	$3072, %rsi                     # imm = 0xC00
	cmpq	$261120, %rsi                   # imm = 0x3FC00
	jne	.LBB49_3
# %bb.4:                                #   in Loop: Header=BB49_2 Depth=2
	incq	%rdx
	addq	$4, %rcx
	addq	$4, %rax
	cmpq	$256, %rdx                      # imm = 0x100
	jne	.LBB49_2
# %bb.5:                                #   in Loop: Header=BB49_1 Depth=1
	xorps	%xmm0, %xmm0
	movq	%r12, %rdi
	movq	%r14, %rsi
	movq	%r15, %rdx
	leaq	d(%rip), %rcx
	movq	%rbx, %r8
	movq	%r13, %r9
	leaq	cc(%rip), %rax
	pushq	%rax
	.cfi_adjust_cfa_offset 8
	leaq	bb(%rip), %rax
	pushq	%rax
	.cfi_adjust_cfa_offset 8
	callq	dummy@PLT
	addq	$16, %rsp
	.cfi_adjust_cfa_offset -16
	incl	%ebp
	cmpl	$78000, %ebp                    # imm = 0x130B0
	jne	.LBB49_1
# %bb.6:
	movq	(%rsp), %rdi                    # 8-byte Reload
	addq	$16, %rdi
	xorl	%esi, %esi
	callq	gettimeofday@PLT
	leaq	.L__func__.s235(%rip), %rdi
	addq	$8, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%r12
	.cfi_def_cfa_offset 40
	popq	%r13
	.cfi_def_cfa_offset 32
	popq	%r14
	.cfi_def_cfa_offset 24
	popq	%r15
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	calc_checksum@PLT               # TAILCALL
.Lfunc_end49:
	.size	s235, .Lfunc_end49-s235
	.cfi_endproc
                                        # -- End function