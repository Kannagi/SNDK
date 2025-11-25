	.zeropage	__rc0
	.zeropage	__rc1
	.zeropage	__rc2
	.zeropage	__rc3
	.zeropage	__rc4
	.zeropage	__rc5
	.zeropage	__rc6
	.zeropage	__rc7
	.zeropage	__rc8
	.zeropage	__rc9
	.zeropage	__rc10
	.zeropage	__rc11
	.zeropage	__rc12
	.zeropage	__rc13
	.zeropage	__rc14
	.zeropage	__rc15
	.zeropage	__rc16
	.zeropage	__rc17
	.zeropage	__rc18
	.zeropage	__rc19
	.zeropage	__rc20
	.zeropage	__rc21
	.zeropage	__rc22
	.zeropage	__rc23
	.zeropage	__rc24
	.zeropage	__rc25
	.zeropage	__rc26
	.zeropage	__rc27
	.zeropage	__rc28
	.zeropage	__rc29
	.zeropage	__rc30
	.zeropage	__rc31
	.file	"make.c"
	.section	.text.main,"ax",@progbits
	.globl	main                            ; -- Begin function main
	.type	main,@function
main:                                   ; @main
; %bb.0:
	jsr	CSNDK_FORCED_BLANK
	jsr	CSNDK_Init
	ldx	#100
	stx	_sndk_arg1
	ldx	#2
	stx	_sndk_arg2
	ldy	#0
	sty	_sndk_arg3
	stx	_sndk_arg4
	sty	_sndk_arg5
	sty	_sndk_arg6
	jsr	SNDK_PrintNumber8
.LBB0_1:                                ; =>This Inner Loop Header: Depth=1
	jsr	SNDK_WaitVBlank
	jmp	.LBB0_1
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
                                        ; -- End function
	.ident	"clang version 22.0.0git (https://github.com/llvm-mos/llvm-mos 77aede75c53fa4adf0086d87e4861fe43b55f0aa)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	;Declaring this symbol tells the CRT that the stack pointer needs to be initialized.
	.globl	__do_init_stack
