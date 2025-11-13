.org 0
.rodata 8421376
..begin SNES_ERROR
SNES_ERROR:
;asm
 plx
;tdebug4 = idx
stx 6
;asm
 phx
;asm
 rep #$20
;reg1 = acc
sta 8
;reg2 = idx
stx 10
;reg3 = idy
sty 12
;asm
 sep #$20
;call SNDK_PrintHexa16
ldx 8
stx @SNDK_PrintHexa16..arg0
ldx #2
stx @SNDK_PrintHexa16..arg1
ldx #8
stx @SNDK_PrintHexa16..arg2
ldx #32
stx @SNDK_PrintHexa16..arg3
jsr SNDK_PrintHexa16
;call SNDK_PrintHexa16
ldx 10
stx @SNDK_PrintHexa16..arg0
ldx #2
stx @SNDK_PrintHexa16..arg1
ldx #9
stx @SNDK_PrintHexa16..arg2
ldx #32
stx @SNDK_PrintHexa16..arg3
jsr SNDK_PrintHexa16
;call SNDK_PrintHexa16
ldx 12
stx @SNDK_PrintHexa16..arg0
ldx #2
stx @SNDK_PrintHexa16..arg1
ldx #10
stx @SNDK_PrintHexa16..arg2
ldx #32
stx @SNDK_PrintHexa16..arg3
jsr SNDK_PrintHexa16
;call SNDK_PrintHexa16
ldx 0
stx @SNDK_PrintHexa16..arg0
ldx #2
stx @SNDK_PrintHexa16..arg1
ldx #11
stx @SNDK_PrintHexa16..arg2
ldx #32
stx @SNDK_PrintHexa16..arg3
jsr SNDK_PrintHexa16
;call SNDK_PrintHexa16
ldx 2
stx @SNDK_PrintHexa16..arg0
ldx #2
stx @SNDK_PrintHexa16..arg1
ldx #12
stx @SNDK_PrintHexa16..arg2
ldx #32
stx @SNDK_PrintHexa16..arg3
jsr SNDK_PrintHexa16
;call SNDK_PrintHexa16
ldx 4
stx @SNDK_PrintHexa16..arg0
ldx #2
stx @SNDK_PrintHexa16..arg1
ldx #13
stx @SNDK_PrintHexa16..arg2
ldx #32
stx @SNDK_PrintHexa16..arg3
jsr SNDK_PrintHexa16
;call SNDK_PrintHexa16
ldx 6
stx @SNDK_PrintHexa16..arg0
ldx #2
stx @SNDK_PrintHexa16..arg1
ldx #14
stx @SNDK_PrintHexa16..arg2
ldx #32
stx @SNDK_PrintHexa16..arg3
jsr SNDK_PrintHexa16
;asm
 rti
..end
..begin SNES_IRQHV
SNES_IRQHV:
;asm
 php
;asm
 pha
;if bgmode != 0
lda 516
cmp #0
beq .label_0
;BGMODE = bgmode
lda 516
sta 8453
.label_0:
;asm
 pla
;asm
 plp
;asm
 rti
..end
..begin _start
_start:
;asm
 
	sei
	cld
	clc
	xce

	rep #$30
	ldx #$01F8
	txs
	
	phk
	pld
	lda #0
	tcd

	sep #$20
	
	;fastrom
	jml _start_jump
	_start_jump:

;NMITIMEN = 0x00
stz 16896
;INIDISP = 0x80
lda #128
sta 8448
;MEMSEL = 1
lda #1
sta 16909
;call SNDK_Init
jsr SNDK_Init
;jump main
jmp main
;jump _start
jmp _start
..end
..begin SNDK_Joypad
SNDK_Joypad:
;acc = JOYSER0
lda 16406
;joya = acc
sta 517
;if acc == 0
cmp #0
bne .label_1
rts
.label_1:
;acc = JOYSER1
lda 16407
;joyb = acc
sta 518
;if acc == 0
cmp #0
bne .label_2
rts
.label_2:
;asm
 rep #$20
;acc = pad1l ^ 0xFFFF
lda 519
eor #65535
;npad1l = acc &SSTDCONTROL1L
and 16920
sta 527
;acc = STDCONTROL1L ^ppad1l
lda 16920
eor 519
;epad1l = acc ^nnpad1l
eor 527
sta 535
;pad1l = STDCONTROL1L
lda 16920
sta 519
;acc = pad2l ^ 0xFFFF
lda 521
eor #65535
;npad2l = acc &SSTDCONTROL2L
and 16922
sta 529
;acc = STDCONTROL2L ^ppad2l
lda 16922
eor 521
;epad2l = acc ^nnpad2l
eor 529
sta 537
;pad2l = STDCONTROL2L
lda 16922
sta 521
;pad2l = STDCONTROL2L
lda 16922
sta 521
;pad3l = STDCONTROL3L
lda 16924
sta 523
;pad4l = STDCONTROL4L
lda 16926
sta 525
;asm
 sep #$20
rts
..end
..begin VBlank
VBlank:
;asm
 
		jml FastVBlank
FastVBlank:

;acc = RDNMI
lda 16912
;INIDISP = 0x80 | SNDK_Light
lda #128
ora 8315436
sta 8448
;call SNDK_VBlank
jsr SNDK_VBlank
.label_b3:
.label_3:
;while HVBJOY &  0x01
lda 16914
bit #1
bne .label_b3
;call SNDK_Joypad
jsr SNDK_Joypad
;idy = 0
ldy #0
;if wait == 0
lda 544
cmp #0
bne .label_4
.label_b5:
;idy +=1
iny
.label_5:
;while HVBJOY &  0x80
lda 16914
bit #128
bne .label_b5
.label_4:
;time = idy
sty 545
;INIDISP = SNDK_Light
lda 8315436
sta 8448
;acc = 0
lda #0
;asm
 rti
..end
LUT_ANGLE:
.db  $00, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f,
.db  $f0, $ff, $7f, $5f, $3f, $3f, $2f, $2f, $1f, $1f, $1f, $1f, $1f, $1f, $1f, $1f,
.db  $f0, $f7, $ff, $af, $7f, $6f, $5f, $4f, $3f, $3f, $3f, $2f, $2f, $2f, $2f, $2f,
.db  $f0, $f5, $fa, $ff, $bf, $9f, $7f, $6f, $5f, $5f, $4f, $4f, $3f, $3f, $3f, $3f,
.db  $f0, $f3, $f7, $fb, $ff, $cf, $af, $8f, $7f, $6f, $6f, $5f, $5f, $4f, $4f, $4f,
.db  $f0, $f3, $f6, $f9, $fc, $ff, $cf, $af, $9f, $8f, $7f, $6f, $6f, $5f, $5f, $5f,
.db  $f0, $f2, $f5, $f7, $fa, $fc, $ff, $cf, $bf, $af, $9f, $8f, $7f, $6f, $6f, $6f,
.db  $f0, $f2, $f4, $f6, $f8, $fa, $fc, $ff, $df, $bf, $af, $9f, $8f, $8f, $7f, $7f,
.db  $f0, $f1, $f3, $f5, $f7, $f9, $fb, $fd, $ff, $df, $cf, $af, $af, $9f, $8f, $8f,
.db  $f0, $f1, $f3, $f5, $f6, $f8, $fa, $fb, $fd, $ff, $df, $cf, $bf, $af, $9f, $9f,
.db  $f0, $f1, $f3, $f4, $f6, $f7, $f9, $fa, $fc, $fd, $ff, $df, $cf, $bf, $af, $af,
.db  $f0, $f1, $f2, $f4, $f5, $f6, $f8, $f9, $fa, $fc, $fd, $ff, $df, $cf, $bf, $bf,
.db  $f0, $f1, $f2, $f3, $f5, $f6, $f7, $f8, $fa, $fb, $fc, $fd, $ff, $df, $cf, $cf,
.db  $f0, $f1, $f2, $f3, $f4, $f5, $f6, $f8, $f9, $fa, $fb, $fc, $fd, $ff, $df, $df,
.db  $f0, $f1, $f2, $f3, $f4, $f5, $f6, $f7, $f8, $f9, $fa, $fb, $fc, $fd, $ff, $ef,
.db  $f0, $f1, $f2, $f3, $f4, $f5, $f6, $f7, $f8, $f9, $fa, $fb, $fc, $fd, $fe, $ff,
..begin main
main:
;INIDISP = 0x80
lda #128
sta 8448
;TM = 0x04
lda #4
sta 8492
;SNDK_AlphaMode = 0
lda #0
sta 8315438
;SNDK_Light = 0x0F
lda #15
sta 8315436
;VBlank.wait = 1
lda #1
sta 544
;call LKS_SPC_Set2
ldx #20
stx @LKS_SPC_Set2..arg0
ldx #2048
stx @LKS_SPC_Set2..arg1
jsr LKS_SPC_Set2
;call LKS_SPC_SetData
ldx #MUSIC_TRACK1
stx @LKS_SPC_SetData..arg0
ldx #:MUSIC_TRACK1
stx @LKS_SPC_SetData..arg1
ldx #8192
stx @LKS_SPC_SetData..arg2
jsr LKS_SPC_SetData
;call LKS_SPC_Set2
ldx #20
stx @LKS_SPC_Set2..arg0
ldx #16384
stx @LKS_SPC_Set2..arg1
jsr LKS_SPC_Set2
;call LKS_SPC_SetData
ldx #MUSIC_BRR1
stx @LKS_SPC_SetData..arg0
ldx #:MUSIC_BRR1
stx @LKS_SPC_SetData..arg1
ldx #32768
stx @LKS_SPC_SetData..arg2
jsr LKS_SPC_SetData
;call LKS_SPC_Set
ldx #16
stx @LKS_SPC_Set..arg0
ldx #64
stx @LKS_SPC_Set..arg1
ldx #64
stx @LKS_SPC_Set..arg2
jsr LKS_SPC_Set
;call LKS_SPC_Set
ldx #32
stx @LKS_SPC_Set..arg0
ldx #40
stx @LKS_SPC_Set..arg1
ldx #40
stx @LKS_SPC_Set..arg2
jsr LKS_SPC_Set
;call LKS_SPC_Set2
ldx #18
stx @LKS_SPC_Set2..arg0
ldx #1
stx @LKS_SPC_Set2..arg1
jsr LKS_SPC_Set2
;call SNDK_SPC_TEST
jsr SNDK_SPC_TEST
..end
..begin SNDK_SPC_TEST
SNDK_SPC_TEST:
;call SNDK_PrintLine
ldx #text_ticks
stx @SNDK_PrintLine..arg0
ldx #:text_ticks
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #1
stx @SNDK_PrintLine..arg3
ldx #36
stx @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_second
stx @SNDK_PrintLine..arg0
ldx #:text_second
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #2
stx @SNDK_PrintLine..arg3
ldx #36
stx @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_channel1
stx @SNDK_PrintLine..arg0
ldx #:text_channel1
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #10
stx @SNDK_PrintLine..arg3
ldx #36
stx @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_channel2
stx @SNDK_PrintLine..arg0
ldx #:text_channel2
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #12
stx @SNDK_PrintLine..arg3
ldx #36
stx @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_channel3
stx @SNDK_PrintLine..arg0
ldx #:text_channel3
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #14
stx @SNDK_PrintLine..arg3
ldx #36
stx @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_channel4
stx @SNDK_PrintLine..arg0
ldx #:text_channel4
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #16
stx @SNDK_PrintLine..arg3
ldx #36
stx @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_channel5
stx @SNDK_PrintLine..arg0
ldx #:text_channel5
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #18
stx @SNDK_PrintLine..arg3
ldx #36
stx @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_channel6
stx @SNDK_PrintLine..arg0
ldx #:text_channel6
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #20
stx @SNDK_PrintLine..arg3
ldx #36
stx @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_channel7
stx @SNDK_PrintLine..arg0
ldx #:text_channel7
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #22
stx @SNDK_PrintLine..arg3
ldx #36
stx @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_channel8
stx @SNDK_PrintLine..arg0
ldx #:text_channel8
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #24
stx @SNDK_PrintLine..arg3
ldx #36
stx @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;select = 0
stz 2
;pitch = 0x10
lda #16
sta 6
;srcn = 0x40
lda #64
sta 4
;volume = 0x7F
lda #127
sta 8
.label_b6:
;if select == 0
lda 2
cmp #0
bne .label_7
;font1 = 0x28
lda #40
sta 10
;else
bra .label_8
.label_7:
;font1 = 0x24
lda #36
sta 10
.label_8:
;if select == 1
lda 2
cmp #1
bne .label_9
;font2 = 0x28
lda #40
sta 11
;else
bra .label_10
.label_9:
;font2 = 0x24
lda #36
sta 11
.label_10:
;if select == 2
lda 2
cmp #2
bne .label_11
;font3 = 0x28
lda #40
sta 12
;else
bra .label_12
.label_11:
;font3 = 0x24
lda #36
sta 12
.label_12:
;if select == 3
lda 2
cmp #3
bne .label_13
;font4 = 0x28
lda #40
sta 13
;else
bra .label_14
.label_13:
;font4 = 0x24
lda #36
sta 13
.label_14:
;call SNDK_PrintLine
ldx #text_s1
stx @SNDK_PrintLine..arg0
ldx #:text_s1
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #3
stx @SNDK_PrintLine..arg3
lda 10
sta @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_s2
stx @SNDK_PrintLine..arg0
ldx #:text_s1
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #4
stx @SNDK_PrintLine..arg3
lda 11
sta @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_s3
stx @SNDK_PrintLine..arg0
ldx #:text_s1
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #5
stx @SNDK_PrintLine..arg3
lda 12
sta @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintLine
ldx #text_s7
stx @SNDK_PrintLine..arg0
ldx #:text_s1
stx @SNDK_PrintLine..arg1
ldx #1
stx @SNDK_PrintLine..arg2
ldx #6
stx @SNDK_PrintLine..arg3
lda 13
sta @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
;call SNDK_PrintHexa8
ldx 6
stx @SNDK_PrintHexa8..arg0
ldx #18
stx @SNDK_PrintHexa8..arg1
ldx #3
stx @SNDK_PrintHexa8..arg2
lda 10
sta @SNDK_PrintHexa8..arg3
jsr SNDK_PrintHexa8
;call SNDK_PrintHexa8
ldx 8
stx @SNDK_PrintHexa8..arg0
ldx #18
stx @SNDK_PrintHexa8..arg1
ldx #4
stx @SNDK_PrintHexa8..arg2
lda 11
sta @SNDK_PrintHexa8..arg3
jsr SNDK_PrintHexa8
;call SNDK_PrintHexa8
ldx 4
stx @SNDK_PrintHexa8..arg0
ldx #18
stx @SNDK_PrintHexa8..arg1
ldx #5
stx @SNDK_PrintHexa8..arg2
lda 12
sta @SNDK_PrintHexa8..arg3
jsr SNDK_PrintHexa8
;if select == 0
lda 2
cmp #0
bne .label_15
;if SNDK_Joypad.npad1h &  0x02
lda 528
bit #2
beq .label_16
;pitch -=1
dec 6
.label_16:
;if SNDK_Joypad.npad1h &  0x01
lda 528
bit #1
beq .label_17
;pitch +=1
inc 6
.label_17:
.label_15:
;if select == 1
lda 2
cmp #1
bne .label_18
;if SNDK_Joypad.npad1h &  0x02
lda 528
bit #2
beq .label_19
;volume -=1
dec 8
.label_19:
;if SNDK_Joypad.npad1h &  0x01
lda 528
bit #1
beq .label_20
;volume +=1
inc 8
.label_20:
.label_18:
;if select == 2
lda 2
cmp #2
bne .label_21
;if SNDK_Joypad.npad1h &  0x02
lda 528
bit #2
beq .label_22
;srcn -=1
dec 4
.label_22:
;if SNDK_Joypad.npad1h &  0x01
lda 528
bit #1
beq .label_23
;srcn +=1
inc 4
.label_23:
.label_21:
;if select == 3
lda 2
cmp #3
bne .label_24
;if SNDK_Joypad.npad1h &  0x10
lda 528
bit #16
beq .label_25
.label_25:
;else
bra .label_26
.label_24:
;if SNDK_Joypad.npad1h &  0x10
lda 528
bit #16
beq .label_27
;call LKS_SPC_Set
ldx #34
stx @LKS_SPC_Set..arg0
ldx 6
stx @LKS_SPC_Set..arg1
ldx 4
stx @LKS_SPC_Set..arg2
jsr LKS_SPC_Set
.label_27:
.label_26:
;if SNDK_Joypad.npad1h &  0x08
lda 528
bit #8
beq .label_28
;select -=1
dec 2
.label_28:
;if SNDK_Joypad.npad1h &  0x04
lda 528
bit #4
beq .label_29
;select +=1
inc 2
.label_29:
;select &=3
lda 2
and #3
sta 2
;call LKS_SPC_Get
ldx #26
stx @LKS_SPC_Get..arg0
jsr LKS_SPC_Get
;tmp =?APUIO2
ldy 8514
sty 0
;call SNDK_PrintHexa16
ldx 0
stx @SNDK_PrintHexa16..arg0
ldx #6
stx @SNDK_PrintHexa16..arg1
ldx #1
stx @SNDK_PrintHexa16..arg2
ldx #40
stx @SNDK_PrintHexa16..arg3
jsr SNDK_PrintHexa16
;asm
 rep #$20
;tmp8 = APUIO2 >>5
lda 8514
lsr
lsr
lsr
lsr
lsr
sta 14
;asm
 sep #$20
;call SNDK_PrintNumber8
lda 14
sta @SNDK_PrintNumber8..arg0
ldx #8
stx @SNDK_PrintNumber8..arg1
ldx #2
stx @SNDK_PrintNumber8..arg2
ldx #40
stx @SNDK_PrintNumber8..arg3
jsr SNDK_PrintNumber8
;call SNDK_PrintNumber8
lda 8315424
sta @SNDK_PrintNumber8..arg0
ldx #27
stx @SNDK_PrintNumber8..arg1
ldx #1
stx @SNDK_PrintNumber8..arg2
ldx #36
stx @SNDK_PrintNumber8..arg3
jsr SNDK_PrintNumber8
;call SNDK_WaitVBlank
jsr SNDK_WaitVBlank
.label_6:
;while 1 
jmp .label_b6
..end
..begin sks_debug
sks_debug:
;tmp8 =?0
ldy #0
sty 244
;tmp8 = 0x88 +ii
lda #136
clc
adc 242
sta 244
;call LKS_SPC_Set2
ldx #20
stx @LKS_SPC_Set2..arg0
ldx 244
stx @LKS_SPC_Set2..arg1
jsr LKS_SPC_Set2
;call LKS_SPC_Get
ldx #24
stx @LKS_SPC_Get..arg0
jsr LKS_SPC_Get
;call SNDK_PrintHexa8
lda 8514
sta @SNDK_PrintHexa8..arg0
ldx #10
stx @SNDK_PrintHexa8..arg1
ldx 240
stx @SNDK_PrintHexa8..arg2
ldx #40
stx @SNDK_PrintHexa8..arg3
jsr SNDK_PrintHexa8
;tmp8 = 0x30 + i
lda #48
clc
adc 242
sta 244
;call LKS_SPC_Set2
ldx #20
stx @LKS_SPC_Set2..arg0
ldx 244
stx @LKS_SPC_Set2..arg1
jsr LKS_SPC_Set2
;call LKS_SPC_Get
ldx #24
stx @LKS_SPC_Get..arg0
jsr LKS_SPC_Get
;call SNDK_PrintHexa8
lda 8514
sta @SNDK_PrintHexa8..arg0
ldx #14
stx @SNDK_PrintHexa8..arg1
ldx 240
stx @SNDK_PrintHexa8..arg2
ldx #40
stx @SNDK_PrintHexa8..arg3
jsr SNDK_PrintHexa8
;tmp8 = 0x38 + i
lda #56
clc
adc 242
sta 244
;call LKS_SPC_Set2
ldx #20
stx @LKS_SPC_Set2..arg0
ldx 244
stx @LKS_SPC_Set2..arg1
jsr LKS_SPC_Set2
;call LKS_SPC_Get
ldx #24
stx @LKS_SPC_Get..arg0
jsr LKS_SPC_Get
;call SNDK_PrintHexa8
lda 8514
sta @SNDK_PrintHexa8..arg0
ldx #17
stx @SNDK_PrintHexa8..arg1
ldx 240
stx @SNDK_PrintHexa8..arg2
ldx #40
stx @SNDK_PrintHexa8..arg3
jsr SNDK_PrintHexa8
rts
..end
..begin debug_stop
debug_stop:
.label_b30:
.label_30:
;while 1 == 1

jmp .label_b30
rts
..end
text_channel1:
.db 67,72,65,78,78,69,76,49,0,
text_channel2:
.db 67,72,65,78,78,69,76,50,0,
text_channel3:
.db 67,72,65,78,78,69,76,51,0,
text_channel4:
.db 67,72,65,78,78,69,76,52,0,
text_channel5:
.db 67,72,65,78,78,69,76,53,0,
text_channel6:
.db 67,72,65,78,78,69,76,54,0,
text_channel7:
.db 67,72,65,78,78,69,76,55,0,
text_channel8:
.db 67,72,65,78,78,69,76,56,0,
text_s1:
.db 83,79,85,78,68,32,66,82,82,32,80,73,84,67,72,0,
text_s2:
.db 83,79,85,78,68,32,66,82,82,32,86,79,76,85,77,69,0,
text_s3:
.db 83,79,85,78,68,32,66,82,82,32,83,82,67,78,0,
text_s7:
.db 83,79,85,78,68,32,67,79,78,84,82,79,76,0,
text_s4:
.db 80,76,65,89,0,
text_s5:
.db 83,84,79,80,0,
text_s6:
.db 76,79,79,80,0,
text_ticks:
.db 84,73,67,75,0,
text_second:
.db 83,69,67,79,78,68,0,
.org  $7FB0
.org  $7FC0
.db 83,85,80,69,82,32,75,65,78,78,65,71,73,32,83,79,85,78,68,32,0,
.db  $30,
.db  $00,
.db  $08,
.db  $00,
.db  $01,
.db  $00,
.db  $00,
.dw  $00,
.dw  $00,
.dd  $00,
.dw @SNES_ERROR,
.dw @SNES_ERROR,
.dw @SNES_ERROR,
.dw @VBlank,
.dw  $00,
.dw @SNES_IRQHV,
.dd  $00,
.dw @SNES_ERROR,
.dw  $00,
.dw @SNES_ERROR,
.dw @VBlank,
.dw @_start,
.dw @SNES_IRQHV,
.org 32768
.rodata 8486912
Super_Kannagi_Sound:
.incbin SPC/Super_Kannagi_Sound.spc
..begin SNDK_VBlank
SNDK_VBlank:
;BG12NBA = SNDK_BGNBA
lda 8315439
sta 8459
;if SNDK_BGMODE != 0
lda 8315441
cmp #0
beq .label_31
;BGMODE = SNDK_BGMODE
lda 8315441
sta 8453
.label_31:
;if SNDK_TM != 0
lda 8315437
cmp #0
beq .label_32
;TM = SNDK_TM
lda 8315437
sta 8492
.label_32:
;if SNDK_AlphaMode == 1
lda 8315438
cmp #1
bne .label_33
;call SNDK_NoModeAlpha
jsr SNDK_NoModeAlpha
.label_33:
;if SNDK_AlphaMode == 2
lda 8315438
cmp #2
bne .label_34
;call SNDK_ModeAlpha
jsr SNDK_ModeAlpha
.label_34:
;if SNDK_AlphaMode == 3
lda 8315438
cmp #3
bne .label_35
;call SNDK_ModeAlpha2
jsr SNDK_ModeAlpha2
.label_35:
;idy = 0
ldy #0
;OAMADD = idy
sty 8450
;DMA_BANK_4 = 0x7E
lda #126
sta 17220
;idy = SNDK_OAM0.x
ldy #57344
;DMA_ADD_4 = idy
sty 17218
;idy = 0x220
ldy #544
;DMA_SIZE_4 = idy
sty 17221
;MDMAEN = 0x10
lda #16
sta 16907
;BG1H0FS = SNDK_BG1_Scroll.x
lda 8315542
sta 8461
;BG1H0FS = SNDK_BG1_Scroll.x2
lda 8315543
sta 8461
;BG1V0FS = SNDK_BG1_Scroll.y
lda 8315544
sta 8462
;BG1V0FS = SNDK_BG1_Scroll.y2
lda 8315545
sta 8462
;BG2H0FS = SNDK_BG2_Scroll.x
lda 8315546
sta 8463
;BG2H0FS = SNDK_BG2_Scroll.x2
lda 8315547
sta 8463
;BG2V0FS = SNDK_BG2_Scroll.y
lda 8315548
sta 8464
;BG2V0FS = SNDK_BG2_Scroll.y2
lda 8315549
sta 8464
;asm
 rep #$20
;DMA_ADD_0 = SNDK_BUF_BG1.h1
lda 8316863
sta 17154
;DMA_ADD_1 = SNDK_BUF_BG1.h2
lda 8316865
sta 17170
;DMA_ADD_2 = SNDK_BUF_BG2.h1
lda 8316867
sta 17186
;DMA_ADD_3 = SNDK_BUF_BG2.h2
lda 8316869
sta 17202
;DMA_SIZE_0 = 0x20
lda #32
sta 17157
;DMA_SIZE_1 = acc
sta 17173
;DMA_SIZE_2 = acc
sta 17189
;DMA_SIZE_3 = acc
sta 17205
;asm
 sep #$20
;DMA_BANK_0 = 0x7F
lda #127
sta 17156
;DMA_BANK_1 = acc
sta 17172
;DMA_BANK_2 = acc
sta 17188
;DMA_BANK_3 = acc
sta 17204
;if bg &  0x01
lda 551
bit #1
beq .label_36
;idy = bg1.h
ldy 560
;VMADD = idy
sty 8470
;MDMAEN = 0x03
lda #3
sta 16907
.label_36:
;if bg &  0x04
lda 551
bit #4
beq .label_37
;idy = bg2.h
ldy 564
;VMADD = idy
sty 8470
;MDMAEN = 0x0C
lda #12
sta 16907
.label_37:
;VMAINC = 0x81
lda #129
sta 8469
;asm
 rep #$20
;DMA_ADD_0 = SNDK_BUF_BG1.v
lda #59199
sta 17154
;DMA_ADD_1 = SNDK_BUF_BG2.v
lda #59263
sta 17170
;DMA_SIZE_0 = 0x40
lda #64
sta 17157
;DMA_SIZE_1 = acc
sta 17173
;asm
 sep #$20
;DMA_BANK_0 = 0x7E
lda #126
sta 17156
;DMA_BANK_1 = acc
sta 17172
;if bg &  0x02
lda 551
bit #2
beq .label_38
;idy = bg1.v
ldy 562
;VMADD = idy
sty 8470
;MDMAEN = 0x01
lda #1
sta 16907
.label_38:
;if bg &  0x08
lda 551
bit #8
beq .label_39
;idy = bg2.v
ldy 566
;VMADD = idy
sty 8470
;MDMAEN = 0x02
lda #2
sta 16907
.label_39:
;VMAINC = 0x80
lda #128
sta 8469
;asm
 rep #$20
;DMA_ADD_0 = dma_spr0.addr
lda 568
sta 17154
;DMA_ADD_1 = acc + dma_spr0.add
clc
adc 570
sta 17170
;DMA_ADD_2 = acc + dma_spr0.add
clc
adc 570
sta 17186
;DMA_ADD_3 = acc + dma_spr0.add
clc
adc 570
sta 17202
;DMA_SIZE_0 = dma_spr0.size
lda 572
sta 17157
;DMA_SIZE_1 = acc
sta 17173
;DMA_SIZE_2 = acc
sta 17189
;DMA_SIZE_3 = acc
sta 17205
;tmp1 = dma_spr0.vmaddr
lda 576
sta 552
;tmp2 = acc + 0x100
clc
adc #256
sta 554
;tmp3 = acc + 0x100
clc
adc #256
sta 556
;tmp4 = acc + 0x100
clc
adc #256
sta 558
;asm
 sep #$20
;DMA_BANK_0 = dma_spr0.bank
lda 574
sta 17156
;DMA_BANK_1 = acc
sta 17172
;DMA_BANK_2 = acc
sta 17188
;DMA_BANK_3 = acc
sta 17204
;if dma_spr0.channel &  0x01
lda 578
bit #1
beq .label_40
;VMADD =?tmp1
ldy 552
sty 8470
;MDMAEN = 0x01
lda #1
sta 16907
.label_40:
;if dma_spr0.channel &  0x02
lda 578
bit #2
beq .label_41
;idx = tmp2
ldx 554
;VMADD = idx
stx 8470
;MDMAEN = 0x02
lda #2
sta 16907
.label_41:
;if dma_spr0.channel &  0x04
lda 578
bit #4
beq .label_42
;idx = tmp3
ldx 556
;VMADD = idx
stx 8470
;MDMAEN = 0x4
lda #4
sta 16907
.label_42:
;if dma_spr0.channel &  0x08
lda 578
bit #8
beq .label_43
;idx = tmp4
ldx 558
;VMADD = idx
stx 8470
;MDMAEN = 0x8
lda #8
sta 16907
.label_43:
;dma_spr0.channel = 0
stz 578
;asm
 rep #$20
;DMA_ADD_0 = dma_spr1.addr
lda 580
sta 17154
;DMA_ADD_1 = acc + dma_spr1.add
clc
adc 582
sta 17170
;DMA_ADD_2 = acc + dma_spr1.add
clc
adc 582
sta 17186
;DMA_ADD_3 = acc + dma_spr1.add
clc
adc 582
sta 17202
;DMA_SIZE_0 = dma_spr1.size
lda 584
sta 17157
;DMA_SIZE_1 = acc
sta 17173
;DMA_SIZE_2 = acc
sta 17189
;DMA_SIZE_3 = acc
sta 17205
;tmp1 = dma_spr1.vmaddr
lda 588
sta 552
;tmp2 = acc + 0x100
clc
adc #256
sta 554
;tmp3 = acc + 0x100
clc
adc #256
sta 556
;tmp4 = acc + 0x100
clc
adc #256
sta 558
;asm
 sep #$20
;DMA_BANK_0 = dma_spr1.bank
lda 586
sta 17156
;DMA_BANK_1 = acc
sta 17172
;DMA_BANK_2 = acc
sta 17188
;DMA_BANK_3 = acc
sta 17204
;if dma_spr1.channel &  0x01
lda 590
bit #1
beq .label_44
;VMADD =?tmp1
ldy 552
sty 8470
;MDMAEN = 0x01
lda #1
sta 16907
.label_44:
;if dma_spr1.channel &  0x02
lda 590
bit #2
beq .label_45
;VMADD =?tmp2
ldy 554
sty 8470
;MDMAEN = 0x02
lda #2
sta 16907
.label_45:
;if dma_spr1.channel &  0x04
lda 590
bit #4
beq .label_46
;VMADD =?tmp3
ldy 556
sty 8470
;MDMAEN = 0x4
lda #4
sta 16907
.label_46:
;if dma_spr1.channel &  0x08
lda 590
bit #8
beq .label_47
;VMADD =?tmp4
ldy 558
sty 8470
;MDMAEN = 0x8
lda #8
sta 16907
.label_47:
;dma_spr1.channel = 0
stz 590
;asm
 rep #$20
;DMA_ADD_0 = dma_spr2.addr
lda 592
sta 17154
;DMA_ADD_1 = acc + dma_spr2.add
clc
adc 594
sta 17170
;DMA_ADD_2 = acc + dma_spr2.add
clc
adc 594
sta 17186
;DMA_ADD_3 = acc + dma_spr2.add
clc
adc 594
sta 17202
;DMA_SIZE_0 = dma_spr2.size
lda 596
sta 17157
;DMA_SIZE_1 = acc
sta 17173
;DMA_SIZE_2 = acc
sta 17189
;DMA_SIZE_3 = acc
sta 17205
;tmp1 = dma_spr2.vmaddr
lda 600
sta 552
;tmp2 = acc + 0x100
clc
adc #256
sta 554
;tmp3 = acc + 0x100
clc
adc #256
sta 556
;tmp4 = acc + 0x100
clc
adc #256
sta 558
;asm
 sep #$20
;DMA_BANK_0 = dma_spr2.bank
lda 598
sta 17156
;DMA_BANK_1 = acc
sta 17172
;DMA_BANK_2 = acc
sta 17188
;DMA_BANK_3 = acc
sta 17204
;if dma_spr2.channel &  0x01
lda 602
bit #1
beq .label_48
;idx = tmp1
ldx 552
;VMADD = idx
stx 8470
;MDMAEN = 0x01
lda #1
sta 16907
.label_48:
;if dma_spr2.channel &  0x02
lda 602
bit #2
beq .label_49
;idx = tmp2
ldx 554
;VMADD = idx
stx 8470
;MDMAEN = 0x02
lda #2
sta 16907
.label_49:
;if dma_spr2.channel &  0x04
lda 602
bit #4
beq .label_50
;idx = tmp3
ldx 556
;VMADD = idx
stx 8470
;MDMAEN = 0x4
lda #4
sta 16907
.label_50:
;if dma_spr2.channel &  0x08
lda 602
bit #8
beq .label_51
;idx = tmp4
ldx 558
;VMADD = idx
stx 8470
;MDMAEN = 0x8
lda #8
sta 16907
.label_51:
;dma_spr2.channel = 0
stz 602
;asm
 rep #$20
;DMA_ADD_0 = dma_tile.addr
lda 604
sta 17154
;DMA_ADD_1 = acc + dma_tile.add
clc
adc 606
sta 17170
;DMA_SIZE_0 = dma_tile.size
lda 608
sta 17157
;DMA_SIZE_1 = acc
sta 17173
;tmp1 = dma_tile.vmaddr
lda 612
sta 552
;tmp2 = acc + 0x100
clc
adc #256
sta 554
;asm
 sep #$20
;DMA_BANK_0 = dma_tile.bank
lda 610
sta 17156
;DMA_BANK_1 = acc
sta 17172
;if dma_tile.channel &  0x01
lda 614
bit #1
beq .label_52
;VMADD =?tmp1
ldy 552
sty 8470
;MDMAEN = 0x01
lda #1
sta 16907
.label_52:
;if dma_tile.channel &  0x02
lda 614
bit #2
beq .label_53
;VMADD =?tmp2
ldy 554
sty 8470
;MDMAEN = 0x02
lda #2
sta 16907
.label_53:
;dma_tile.channel = 0
stz 614
;asm
 rep #$20
;acc = adrpal >>1
lda 549
lsr
;asm
 sep #$20
;CGADD = acc
sta 8481
;asm
 rep #$20
;DMA_ADD_5 = SNDK_PALBG0 + adrpal
lda #63437
clc
adc 549
sta 17234
;DMA_SIZE_5 = 0x40
lda #64
sta 17237
;adrpal +=0x40
lda 549
clc
adc #64
sta 549
;if acc == 0x200
cmp #512
bne .label_54
;acc = 0
lda #0
.label_54:
;adrpal = acc
sta 549
;SNDK.count_pal = acc
sta 8315434
;asm
 sep #$20
;DMA_BANK_5 = SNDK_PALBG0
lda #:126
sta 17236
;MDMAEN = 0x20
lda #32
sta 16907
;asm
 rep #$20
;acc = adrbg3 >>1
lda 547
lsr
;VMADD = acc + 0x5C00
clc
adc #23552
sta 8470
;DMA_ADD_0 = SNDK_BG3.t1 + adrbg3
lda #61388
clc
adc 547
sta 17154
;acc = adrbg3
lda 547
;acc +=bg3size
clc
adc 616
;if acc == 0x700
cmp #1792
bne .label_55
;acc = 0
lda #0
.label_55:
;adrbg3 = acc
sta 547
;DMA_SIZE_0 = bg3size
lda 616
sta 17157
;asm
 sep #$20
;DMA_BANK_0 = SNDK_BG3.t1
lda #:126
sta 17156
;MDMAEN = 1
lda #1
sta 16907
;asm
 rep #$20
;VMADD = tileset.vaddr
lda 618
sta 8470
;DMA_ADD_0 = tileset.addr
lda 620
sta 17154
;DMA_SIZE_0 = tileset.size
lda 622
sta 17157
;asm
 sep #$20
;DMA_BANK_0 = tileset.bank
lda 624
sta 17156
;if tileset.channel &  0x01
lda 626
bit #1
beq .label_56
;MDMAEN = 0x01
lda #1
sta 16907
;tileset.channel = 0
stz 626
.label_56:
;bg = 0
stz 551
rtl
..end
..begin SNDK_GetVBlank_adrbg3
SNDK_GetVBlank_adrbg3:
;asm
 rep #$20
;acc = SNDK_VBlank.adrbg3 >>7
lda 547
lsr
lsr
lsr
lsr
lsr
lsr
lsr
;asm
 sep #$20
rtl
..end
..begin SNDK_SetVBlank_adrbg3
SNDK_SetVBlank_adrbg3:
;asm
 rep #$20
;SNDK_VBlank.adrbg3 = val
lda 224
sta 547
;asm
 sep #$20
rtl
..end
..begin SNDK_SetVBlank_bg3size
SNDK_SetVBlank_bg3size:
;asm
 rep #$20
;SNDK_VBlank.bg3size = val
lda 224
sta 616
;asm
 sep #$20
rtl
..end
..begin SNDK_WaitVBlank
SNDK_WaitVBlank:
;acc = SNDK.clockf + 1
lda 8315427
clc
adc #1
;if acc == 60
cmp #60
bne .label_57
;acc = SNDK.clocks + 1
lda 8315428
clc
adc #1
;if acc == 60
cmp #60
bne .label_58
;acc = SNDK.clockm + 1
lda 8315429
clc
adc #1
;if acc == 60
cmp #60
bne .label_59
;SNDK.clockh +=1
lda 8315430
clc
adc #1
sta 8315430
;acc = 0
lda #0
.label_59:
;SNDK.clockm = acc
sta 8315429
;acc = 0
lda #0
.label_58:
;SNDK.clocks = acc
sta 8315428
;SNDK.pcpu = 0
lda #0
sta 8315426
;acc = 0
lda #0
.label_57:
;SNDK.clockf = acc
sta 8315427
;acc = SLHV
lda 8503
;acc = OPVCT
lda 8509
;asm
 rep #$20
;acc = acc & 0xFF
and #255
;WRDIVL = acc <<6
asl
asl
asl
asl
asl
asl
sta 16900
;asm
 sep #$20
;WRDIVB = 143
lda #143
sta 16902
;if SNDK.mcpu <  SNDK.cpu
lda 8315425
cmp 8315424
bcs .label_60
;SNDK.mcpu = SNDK.cpu
lda 8315424
sta 8315425
.label_60:
;if SNDK.pcpu <  SNDK.cpu
lda 8315426
cmp 8315424
bcs .label_61
;SNDK.pcpu = SNDK.cpu
lda 8315424
sta 8315426
.label_61:
;SNDK.cpu = RDDIVL
lda 16916
sta 8315424
;NMITIMEN = 0x81
lda #129
sta 16896
;acc = 1
lda #1
.label_b62:
.label_62:
;while acc == 1
cmp #1
beq .label_b62
;NMITIMEN = 0x00
stz 16896
rtl
..end
..begin SNDK_Sprite
SNDK_Sprite:
;DMA_7 = 0x18
lda #24
sta 17264
;DMA_BADD_7 = 0x80
lda #128
sta 17265
;oam =?0
ldy #0
sty 628
;idy = SNDK_OAM0.x
ldy #57344
;WMADD = idy
sty 8577
;WMADDH = SNDK_OAM0.x
lda #:126
sta 8579
;DMA_BANK_7 = SNDK_OAM_INIT_DATA
lda #:SNDK_OAM_INIT_DATA
sta 17268
;idy = SNDK_OAM_INIT_DATA
ldy #SNDK_OAM_INIT_DATA
;DMA_ADD_7 = idy
sty 17266
;idy = 0x200
ldy #512
;DMA_SIZE_7 = idy
sty 17269
;MDMAEN = 0x80
lda #128
sta 16907
;idy = SNDK_OAMH
ldy #57856
;WMADD = idy
sty 8577
;WMADDH = SNDK_OAMH
lda #:126
sta 8579
;DMA_BANK_7 = SNDK_OAM_INIT_DATA2
lda #:SNDK_OAM_INIT_DATA2
sta 17268
;idy = SNDK_OAM_INIT_DATA2
ldy #SNDK_OAM_INIT_DATA2
;DMA_ADD_7 = idy
sty 17266
;idy = 0x20
ldy #32
;DMA_SIZE_7 = idy
sty 17269
;MDMAEN = 0x80
lda #128
sta 16907
rtl
..end
..begin debug_stop2
debug_stop2:
;NMITIMEN = 0x00
stz 16896
.label_b63:
.label_63:
;while 1 == 1

jmp .label_b63
rtl
..end
SNDK_OAM_INIT_DATA:
.db  $E0,
SNDK_OAM_INIT_DATA2:
.db  $00,
;asm
 rep #$20
..begin SNDK_ScrollMultiBG_zoneX
SNDK_ScrollMultiBG_zoneX:
;tmp = acc
sta 132
;if bg.w == 0x100
lda 128
cmp #256
bne .label_64
;acc = tmp <<1
lda 132
asl
rtl
.label_64:
;if bg.w == 0x200
lda 128
cmp #512
bne .label_65
;acc = tmp <<2
lda 132
asl
asl
rtl
.label_65:
;if bg.w == 0x400
lda 128
cmp #1024
bne .label_66
;acc = tmp <<3
lda 132
asl
asl
asl
rtl
.label_66:
;if bg.w == 0x800
lda 128
cmp #2048
bne .label_67
;acc = tmp <<4
lda 132
asl
asl
asl
asl
rtl
.label_67:
;if bg.w == 0x1000
lda 128
cmp #4096
bne .label_68
;acc = tmp <<5
lda 132
asl
asl
asl
asl
asl
rtl
.label_68:
;if bg.w == 0x2000
lda 128
cmp #8192
bne .label_69
;acc = tmp <<6
lda 132
asl
asl
asl
asl
asl
asl
rtl
.label_69:
rtl
..end
..begin SNDK_ScrollMultiBG
SNDK_ScrollMultiBG:
;asm
 rep #$20
;bg.w = SNDK_BG.w
lda 8316871
sta 128
;bg.h = SNDK_BG.h
lda 8316873
sta 130
;zonex1 = 0
stz 146
;acc = SNDK_BG2_Scroll.x &00xFF00
lda 8315546
and #65280
;if acc != 0
cmp #0
beq .label_70
;acc +=0x100
clc
adc #256
;acc = acc >>3
lsr
lsr
lsr
;zonex1 = acc &00xFFC0
and #65472
sta 146
.label_70:
;acc = SNDK_BG2_Scroll.x &00xFE00
lda 8315546
and #65024
;zonex2 = acc >>3
lsr
lsr
lsr
sta 148
;add = SNDK_BG_Scroll.addy
lda 8315550
sta 140
;vadd = add
lda 140
sta 142
;if bg.w == 0x200
lda 128
cmp #512
bne .label_71
;vadd = vadd <<1
lda 142
asl
sta 142
.label_71:
;if bg.w == 0x400
lda 128
cmp #1024
bne .label_72
;vadd = vadd <<2
lda 142
asl
asl
sta 142
.label_72:
;if bg.w == 0x800
lda 128
cmp #2048
bne .label_73
;vadd = vadd <<3
lda 142
asl
asl
asl
sta 142
.label_73:
;if bg.w == 0x1000
lda 128
cmp #4096
bne .label_74
;vadd = vadd <<4
lda 142
asl
asl
asl
asl
sta 142
.label_74:
;if bg.w == 0x2000
lda 128
cmp #8192
bne .label_75
;vadd = vadd <<5
lda 142
asl
asl
asl
asl
asl
sta 142
.label_75:
;acc = SNDK_BG2_Scroll.y &00x1F0
lda 8315548
and #496
;acc = acc <<1
asl
;acc +=add
clc
adc 140
;py = acc & 0x3E0
and #992
sta 138
;SNDK_VBlank.bg1.h = 0x5400 +ppy
lda #21504
clc
adc 138
sta 560
;SNDK_VBlank.bg2.h = 0x5800 +ppy
lda #22528
clc
adc 138
sta 564
;acc = SNDK_BG2_Scroll.y &00xFFF0
lda 8315548
and #65520
;call SNDK_ScrollMultiBG_zoneX
jsr SNDK_ScrollMultiBG_zoneX
;x = acc
sta 136
;acc +=zonex1
clc
adc 146
;tmp = acc + vadd
clc
adc 142
sta 132
;SNDK_BUF_BG1.h1 = tmp + 0x4000
lda 132
clc
adc #16384
sta 8316863
;SNDK_BUF_BG2.h1 = tmp
lda 132
sta 8316867
;acc = x + 0x20
lda 136
clc
adc #32
;acc = acc + zonex2
clc
adc 148
;tmp = acc + vadd
clc
adc 142
sta 132
;SNDK_BUF_BG1.h2 = tmp + 0x4000
lda 132
clc
adc #16384
sta 8316865
;SNDK_BUF_BG2.h2 = tmp
lda 132
sta 8316869
;add = SNDK_BG_Scroll.addx
lda 8315552
sta 140
;vadd = acc <<1
asl
sta 142
;acc = SNDK_BG2_Scroll.x >>4
lda 8315546
lsr
lsr
lsr
lsr
;acc +=add
clc
adc 140
;py = acc & 0x1F
and #31
sta 138
;SNDK_VBlank.bg1.v = 0x5400 + py
lda #21504
clc
adc 138
sta 562
;SNDK_VBlank.bg2.v = 0x5800 + py
lda #22528
clc
adc 138
sta 566
;if flagbg &! 0x0A
lda 224
bit #10
bne .label_76
;asm
 sep #$20
;SNDK_VBlank.bg =fflagbg
lda 224
sta 551
rtl
;asm
 rep #$20
.label_76:
;zonex1 = 0
stz 146
;acc = SNDK_BG2_Scroll.y &00xFF00
lda 8315548
and #65280
;if acc != 0
cmp #0
beq .label_77
;acc +=0x100
clc
adc #256
;acc = acc & 0xFE00
and #65024
;call SNDK_ScrollMultiBG_zoneX
jsr SNDK_ScrollMultiBG_zoneX
;zonex1 = acc
sta 146
.label_77:
;acc = SNDK_BG2_Scroll.y &00xFE00
lda 8315548
and #65024
;call SNDK_ScrollMultiBG_zoneX
jsr SNDK_ScrollMultiBG_zoneX
;zonex2 = acc
sta 148
;acc = bg.w <<1
lda 128
asl
;zonex2 +=acc
sta 222
lda 148
clc
adc 222
sta 148
;adrh = 0x7F
lda #127
sta 152
;adrh2 = 0x7F
lda #127
sta 156
;acc = SNDK_BG2_Scroll.x >>4
lda 8315546
lsr
lsr
lsr
lsr
;acc = acc <<1
asl
;acc +=vadd
clc
adc 142
;tmp = acc
sta 132
;acc +=zonex1
clc
adc 146
;adr = acc + SNDK_BufferBG1
clc
adc #16384
sta 150
;acc = tmp + zonex1
lda 132
clc
adc 146
;adr2 = acc + SNDK_BufferBG2
clc
adc #0
sta 154
;add = bg.w >>3
lda 128
lsr
lsr
lsr
sta 140
;idx = 0
ldx #0
;idy = 0x10
ldy #16
.label_b78:
;.ptr = adr
lda [150]
sta 8316735,X
;.ptr = adr2
lda [154]
sta 8316799,X
;idx +=2
inx
inx
;adr +=add
lda 150
clc
adc 140
sta 150
;adr2 +=add
lda 154
clc
adc 140
sta 154
.label_78:
;loop idy == 0
dey 
bne .label_b78
;acc = tmp + zonex2
lda 132
clc
adc 148
;adr = acc + SNDK_BufferBG1
clc
adc #16384
sta 150
;acc = tmp + zonex2
lda 132
clc
adc 148
;adr2 = acc + SNDK_BufferBG2
clc
adc #0
sta 154
;idy = 0x10
ldy #16
.label_b79:
;.ptr = adr
lda [150]
sta 8316735,X
;.ptr = adr2
lda [154]
sta 8316799,X
;idx +=2
inx
inx
;adr +=add
lda 150
clc
adc 140
sta 150
;adr2 +=add
lda 154
clc
adc 140
sta 154
.label_79:
;loop idy == 0
dey 
bne .label_b79
;asm
 sep #$20
;SNDK_VBlank.bg =fflagbg
lda 224
sta 551
rtl
..end
..begin SNDK_SpriteEngineDrawMode0
SNDK_SpriteEngineDrawMode0:
;asm
 rep #$20
;tmp = SNDK_SPR_SIZE &00xFF
lda 208
and #255
sta 140
;idx = oldx
ldx 142
;posxh = .ptr
lda 8315580,X
sta 136
;.ptr = 0
lda #0
sta 8315566,X
;posx +=.ptr
lda 128
clc
adc 8315574,X
sta 128
;posy +=.ptr
lda 130
clc
adc 8315576,X
sta 130
;acc = posy + 0xC020
lda 130
clc
adc #49184
;if acc &  0x3F00
bit #16128
beq .label_80
;SNDK_Sprite.oam +=0x4
lda 628
clc
adc #4
sta 628
;asm
 rts
.label_80:
;acc = posx + 0xC000
lda 128
clc
adc #49152
;acc +=tmp
clc
adc 140
;if acc ?= 0
bcc .label_81
;acc = SNDK_Sprite.oam >>2
lda 628
lsr
lsr
;tmp = acc &33
and #3
sta 140
;if tmp == 0
lda 140
cmp #0
bne .label_82
;posxh |=0x01
lda 136
ora #1
sta 136
.label_82:
;if tmp == 1
lda 140
cmp #1
bne .label_83
;posxh |=0x04
lda 136
ora #4
sta 136
.label_83:
;if tmp == 2
lda 140
cmp #2
bne .label_84
;posxh |=0x10
lda 136
ora #16
sta 136
.label_84:
;if tmp == 3
lda 140
cmp #3
bne .label_85
;posxh |=0x40
lda 136
ora #64
sta 136
.label_85:
;else
bra .label_86
.label_81:
;acc -=tmp
sec
sbc 140
;if acc &  0x3F00
bit #16128
beq .label_87
;SNDK_Sprite.oam +=0x4
lda 628
clc
adc #4
sta 628
;asm
 rts
.label_87:
.label_86:
;draw = .ptr
lda 8315582,X
sta 134
;.ptr = 1
lda #1
sta 8315566,X
;acc = SNDK_Sprite.oam
lda 628
;idx = acc
tax
;indexh = acc >>4
lsr
lsr
lsr
lsr
sta 138
;asm
 sep #$20
;if draw != 0
lda 134
cmp #0
beq .label_88
;asm
 rep #$20
;SNDK_Sprite.oam +=0x4
lda 628
clc
adc #4
sta 628
;asm
 rts
;asm
 sep #$20
.label_88:
;.ptr = posx
lda 128
sta 8314880,X
;.ptr = posy
lda 130
sta 8314881,X
;.ptr = tile
lda 132
sta 8314882,X
;.ptr = attribute
lda 133
sta 8314883,X
;.ptr |=posxh
lda 138
tax
lda 8315392,X
ora 136
ldx 138
sta 8315392,X
;asm
 rep #$20
;SNDK_Sprite.oam +=0x4
lda 628
clc
adc #4
sta 628
;asm
 rts
..end
..begin SNDK_SpriteEngineDrawMode0z
SNDK_SpriteEngineDrawMode0z:
;asm
 rep #$20
;tmp = SNDK_SPR_SIZE2 &00xFF
lda 210
and #255
sta 140
;idx = oldx
ldx 142
;posxh = .ptr
lda 8315580,X
sta 136
;.ptr = 0
lda #0
sta 8315566,X
;posx +=.ptr
lda 128
clc
adc 8315574,X
sta 128
;posy +=.ptr
lda 130
clc
adc 8315576,X
sta 130
;acc = posy + 0xC020
lda 130
clc
adc #49184
;if acc &  0x3F00
bit #16128
beq .label_89
;SNDK_Sprite.oam +=0x4
lda 628
clc
adc #4
sta 628
;asm
 rts
.label_89:
;acc = posx + 0xC000
lda 128
clc
adc #49152
;acc +=tmp
clc
adc 140
;if acc ?= 0
bcc .label_90
;acc = SNDK_Sprite.oam >>2
lda 628
lsr
lsr
;tmp = acc &33
and #3
sta 140
;if tmp == 0
lda 140
cmp #0
bne .label_91
;posxh |=0x01
lda 136
ora #1
sta 136
.label_91:
;if tmp == 1
lda 140
cmp #1
bne .label_92
;posxh |=0x04
lda 136
ora #4
sta 136
.label_92:
;if tmp == 2
lda 140
cmp #2
bne .label_93
;posxh |=0x10
lda 136
ora #16
sta 136
.label_93:
;if tmp == 3
lda 140
cmp #3
bne .label_94
;posxh |=0x40
lda 136
ora #64
sta 136
.label_94:
;else
bra .label_95
.label_90:
;acc -=tmp
sec
sbc 140
;if acc &  0x3F00
bit #16128
beq .label_96
;SNDK_Sprite.oam +=0x4
lda 628
clc
adc #4
sta 628
;asm
 rts
.label_96:
.label_95:
;draw = .ptr
lda 8315582,X
sta 134
;.ptr = 1
lda #1
sta 8315566,X
;acc = SNDK_Sprite.oam
lda 628
;idx = acc
tax
;indexh = acc >>4
lsr
lsr
lsr
lsr
sta 138
;asm
 sep #$20
;if draw != 0
lda 134
cmp #0
beq .label_97
;asm
 rep #$20
;SNDK_Sprite.oam +=0x4
lda 628
clc
adc #4
sta 628
;asm
 rts
;asm
 sep #$20
.label_97:
;.ptr = posx
lda 128
sta 8314880,X
;.ptr = posy
lda 130
sta 8314881,X
;.ptr = tile
lda 132
sta 8314882,X
;.ptr = attribute
lda 133
sta 8314883,X
;.ptr |=posxh
lda 138
tax
lda 8315392,X
ora 136
ldx 138
sta 8315392,X
;asm
 rep #$20
;SNDK_Sprite.oam +=0x4
lda 628
clc
adc #4
sta 628
;asm
 rts
..end
..begin SNDK_SpriteEngineDraw
SNDK_SpriteEngineDraw:
;asm
 rep #$20
;idx = oldx
ldx 140
;.ptr = 0
lda #0
sta 8315566,X
;acc = posy + 0xC020
lda 130
clc
adc #49184
;if acc &  0x3F00
bit #16128
beq .label_98
rtl
.label_98:
;posxh = 0
stz 134
;acc = posx + 0xC010
lda 128
clc
adc #49168
;if acc ?= 0
bcc .label_99
;posxh = 0x11
lda #17
sta 134
;else
bra .label_100
.label_99:
;acc +=0x10
clc
adc #16
;if acc ?= 0
bcc .label_101
;posxh = 0x55
lda #85
sta 134
;else
bra .label_102
.label_101:
;acc -=0x20
sec
sbc #32
;if acc &  0x3F00
bit #16128
beq .label_103
rtl
.label_103:
.label_102:
.label_100:
;.ptr = 1
lda #1
sta 8315566,X
;idx = SNDK_Sprite.oam
ldx 628
;indexh = idx >>4
txa 
lsr
lsr
lsr
lsr
sta 136
;SNDK_Sprite.oam +=0x10
lda 628
clc
adc #16
sta 628
;asm
 sep #$20
;.ptr = posx
lda 128
sta 8314880,X
;.ptr = posy
lda 130
sta 8314881,X
;.ptr = tile
lda 132
sta 8314882,X
;.ptr = attribute
lda 133
sta 8314883,X
;.ptr = posxh
lda 136
tax
lda 134
ldx 136
sta 8315392,X
;asm
 rep #$20
rtl
..end
;asm
 sep #$20
..begin SNDK_BulletInit
SNDK_BulletInit:
;asm
 rep #$20
;idy = n
ldy 224
;idx = 0
ldx #0
.label_b104:
;acc = 0
lda #0
;.ptr = acc
sta 8317387,X
;.ptr = acc
sta 8317643,X
;.ptr = acc
sta 8317899,X
;.ptr = acc
sta 8316875,X
;.ptr = 0xE000
lda #57344
sta 8317131,X
;.ptr = 1
lda #1
sta 8318412,X
;.ptr = 1
lda #1
sta 8318668,X
;idx +=2
inx
inx
.label_104:
;loop idy == 0
dey 
bne .label_b104
;asm
 sep #$20
rtl
..end
;asm
 rep #$20
..begin SNDK_BulletEngine1
SNDK_BulletEngine1:
;.ptr = 1
lda #1
sta 8318412
.label_b105:
;call SNDK_BulletOut1
jsr SNDK_BulletOut1
;idx +=2
inx
inx
.label_105:
;loop idy == 0
dey 
bne .label_b105
rtl
..end
..begin SNDK_BulletEngine2
SNDK_BulletEngine2:
;.ptr = 1
lda #1
sta 8318668
.label_b106:
;call SNDK_BulletOut2
jsr SNDK_BulletOut2
;idx +=2
inx
inx
.label_106:
;loop idy == 0
dey 
bne .label_b106
rtl
..end
;asm
 sep #$20
..begin SNDK_BulletEngine
SNDK_BulletEngine:
;asm
 rep #$20
;oam = SNDK_Sprite.oam
lda 628
sta 128
;if n2 != 0
lda 226
cmp #0
beq .label_107
;asm
 rep #$20
;xuse = 0
stz 130
;idy = n2
ldy 226
;idx = n1 <<1
lda 224
asl
tax
;call SNDK_BulletEngine2
jsr SNDK_BulletEngine2
;asm
 rep #$20
;.ptr = 1
lda 130
tax
lda #1
ldx 130
sta 8318668,X
;SNDK_Sprite.oam = oam
lda 128
sta 628
;asm
 sep #$20
.label_107:
;if n1 != 0
lda 224
cmp #0
beq .label_108
;asm
 rep #$20
;xuse = 0
stz 130
;idy = n1
ldy 224
;idx = 0
ldx #0
;call SNDK_BulletEngine1
jsr SNDK_BulletEngine1
;asm
 rep #$20
;.ptr = 1
lda 130
tax
lda #1
ldx 130
sta 8318412,X
;SNDK_Sprite.oam = oam
lda 128
sta 628
;asm
 sep #$20
.label_108:
rtl
..end
..begin SNDK_BulletHitboxSet
SNDK_BulletHitboxSet:
;begin = beg <<1
lda 224
asl
sta 630
;count = n
lda 226
sta 632
;asm
 rep #$20
;if x &  0x2000
lda 228
bit #8192
beq .label_109
;acc = x & 0xFF
lda 228
and #255
;acc = acc ^ 0xFF
eor #255
;w -=acc
sta 222
lda 232
sec
sbc 222
sta 232
;x = 0
stz 228
.label_109:
;rect.x = x
lda 228
sta 634
;rect.y = y
lda 230
sta 636
;rect.w = x +ww
lda 228
clc
adc 232
sta 638
;rect.h = y +hh
lda 230
clc
adc 234
sta 640
;if rect.w &  0x1F00
lda 638
bit #7936
beq .label_110
;rect.w = 255
lda #255
sta 638
.label_110:
;asm
 sep #$20
rtl
..end
..begin SNDK_BulletHitbox
SNDK_BulletHitbox:
;rect.x = SNDK_BulletHitboxSet.rect.x
lda 634
sta 132
;rect.y = SNDK_BulletHitboxSet.rect.y
lda 636
sta 134
;rect.w = SNDK_BulletHitboxSet.rect.w
lda 638
sta 136
;rect.h = SNDK_BulletHitboxSet.rect.h
lda 640
sta 138
;idy = SNDK_BulletHitboxSet.count
ldy 632
;idx = SNDK_BulletHitboxSet.begin
ldx 630
;idx +=1
inx
.label_b111:
;y = .ptr
lda 8317131,X
sta 130
;if acc != 0xE0
cmp #224
beq .label_112
;acc = .ptr
lda 8316875,X
;if acc >= rect.x
cmp 132
bcc .label_113
;if acc <  rect.w
cmp 136
bcs .label_114
;x = acc
sta 128
;acc = y
lda 130
;if acc >= rect.y
cmp 134
bcc .label_115
;if acc <  rect.h
cmp 138
bcs .label_116
;asm
 rep #$20
;idx -=1
dex
;.ptr = 0xE000
lda #57344
sta 8317131,X
;acc = 0
lda #0
;.ptr =aacc
sta 8316875,X
;.ptr = acc
sta 8317387,X
;.ptr = acc
sta 8317643,X
;asm
 sep #$20
lda #1
rtl
.label_116:
.label_115:
.label_114:
.label_113:
.label_112:
;idx +=2
inx
inx
.label_111:
;loop idy == 0
dey 
bne .label_b111
lda #0
rtl
..end
..begin SNDK_BulletOut1
SNDK_BulletOut1:
;asm
 rep #$20
;.ptr +=.ptr
lda 8316875,X
clc
adc 8317387,X
sta 8316875,X
;posx = acc
sta 134
;acc = acc & 0xF800
and #63488
;if acc == 0xF800
cmp #63488
bne .label_117
;acc = 0
lda #0
;.ptr = acc
sta 8316875,X
;.ptr = acc
sta 8317387,X
;.ptr = acc
sta 8317643,X
;.ptr = 0xE000
lda #57344
sta 8317131,X
.label_117:
;.ptr +=.ptr
lda 8317131,X
clc
adc 8317643,X
sta 8317131,X
;posy = acc
sta 136
;acc = acc & 0xF000
and #61440
;if acc == 0xF000
cmp #61440
bne .label_118
;acc = 0
lda #0
;.ptr = acc
sta 8316875,X
;.ptr = acc
sta 8317387,X
;.ptr = acc
sta 8317643,X
;.ptr = 0xE000
lda #57344
sta 8317131,X
.label_118:
;tile = .ptr
lda 8317899,X
sta 138
;tmp = idx
stx 132
;asm
 phx
;if posy == 0xE000
lda 136
cmp #57344
bne .label_119
;idx = xuse
ldx 130
;.ptr = tmp
lda 132
sta 8318412,X
;idx +=2
inx
inx
;xuse = idx
stx 130
;asm
 plx
;oam +=4
lda 128
clc
adc #4
sta 128
;asm
 sep #$20
rtl
;asm
 rep #$20
.label_119:
;acc = oam
lda 128
;idx = acc
tax
;oam = acc + 4
clc
adc #4
sta 128
;.ptr = tile
lda 138
sta 8314882,X
;asm
 sep #$20
;.ptr = posx2
lda 135
sta 8314880,X
;.ptr = posy2
lda 137
sta 8314881,X
;asm
 plx
rtl
..end
..begin SNDK_BulletOut2
SNDK_BulletOut2:
;asm
 rep #$20
;.ptr +=.ptr
lda 8316875,X
clc
adc 8317387,X
sta 8316875,X
;posx = acc
sta 134
;acc = acc & 0xF800
and #63488
;if acc == 0xF800
cmp #63488
bne .label_120
;acc = 0
lda #0
;.ptr = acc
sta 8316875,X
;.ptr = acc
sta 8317387,X
;.ptr = acc
sta 8317643,X
;.ptr = 0xE000
lda #57344
sta 8317131,X
.label_120:
;.ptr +=.ptr
lda 8317131,X
clc
adc 8317643,X
sta 8317131,X
;posy = acc
sta 136
;acc = acc & 0xF000
and #61440
;if acc == 0xF000
cmp #61440
bne .label_121
;acc = 0
lda #0
;.ptr = acc
sta 8316875,X
;.ptr = acc
sta 8317387,X
;.ptr = acc
sta 8317643,X
;.ptr = 0xE000
lda #57344
sta 8317131,X
.label_121:
;tile = .ptr
lda 8317899,X
sta 138
;tmp = idx
stx 132
;asm
 phx
;if posy == 0xE000
lda 136
cmp #57344
bne .label_122
;idx = xuse
ldx 130
;.ptr = tmp
lda 132
sta 8318668,X
;idx +=2
inx
inx
;xuse = idx
stx 130
;asm
 plx
;oam +=4
lda 128
clc
adc #4
sta 128
;asm
 sep #$20
rtl
;asm
 rep #$20
.label_122:
;acc = oam
lda 128
;idx = acc
tax
;oam = acc + 4
clc
adc #4
sta 128
;.ptr = tile
lda 138
sta 8314882,X
;asm
 sep #$20
;.ptr = posx2
lda 135
sta 8314880,X
;.ptr = posy2
lda 137
sta 8314881,X
;asm
 plx
rtl
..end
..begin higueul_mul
higueul_mul:
;asm
 
	
	;lda #0
	beq .higueul_stdlib_mul_enterLoop

	.higueul_stdlib_mul_doAdd:
	clc
	adc 214

	.higueul_stdlib_mul_loop:
	asl 214
	.higueul_stdlib_mul_enterLoop:
	lsr 216
	bcs .higueul_stdlib_mul_doAdd
	bne .higueul_stdlib_mul_loop

	
rtl
..end
..begin higueul_div
higueul_div:
;result = 0
stz 160
;a = .ptr
lda 214
sta 161
;b = .ptr
lda 216
sta 162
;acc = b
lda 162
;b1 = acc <<1
asl
sta 163
;b2 = acc <<1
asl
sta 164
;b3 = acc <<1
asl
sta 165
;b4 = acc <<1
asl
sta 166
;b5 = acc <<1
asl
sta 167
;b6 = acc <<1
asl
sta 168
;b7 = acc <<1
asl
sta 169
;if a >= b7
lda 161
cmp 169
bcc .label_123
;a -=b7
lda 161
sec
sbc 169
sta 161
;result +=128
lda 160
clc
adc #128
sta 160
.label_123:
;if a >= b6
lda 161
cmp 168
bcc .label_124
;a -=b6
lda 161
sec
sbc 168
sta 161
;result +=64
lda 160
clc
adc #64
sta 160
.label_124:
;if a >= b5
lda 161
cmp 167
bcc .label_125
;a -=b5
lda 161
sec
sbc 167
sta 161
;result +=32
lda 160
clc
adc #32
sta 160
.label_125:
;if a >= b4
lda 161
cmp 166
bcc .label_126
;a -=b4
lda 161
sec
sbc 166
sta 161
;result +=16
lda 160
clc
adc #16
sta 160
.label_126:
;if a >= b3
lda 161
cmp 165
bcc .label_127
;a -=b3
lda 161
sec
sbc 165
sta 161
;result +=8
lda 160
clc
adc #8
sta 160
.label_127:
;if a >= b2
lda 161
cmp 164
bcc .label_128
;a -=b2
lda 161
sec
sbc 164
sta 161
;result +=4
lda 160
clc
adc #4
sta 160
.label_128:
;if a >= b1
lda 161
cmp 163
bcc .label_129
;a -=b1
lda 161
sec
sbc 163
sta 161
;result +=2
inc 160
inc 160
.label_129:
;if a >= b
lda 161
cmp 162
bcc .label_130
;a -=b
lda 161
sec
sbc 162
sta 161
;result +=1
inc 160
.label_130:
lda 160
rtl
..end
..begin start_logo_sndk
start_logo_sndk:
;time = 0
stz 0
;INIDISP = 0x80
lda #128
sta 8448
;SNDK_Light = 0x0
lda #0
sta 8315436
;TM = 0x10
lda #16
sta 8492
;call SNDK_LZ_VRAM
ldx #1
stx @SNDK_LZ_VRAM..arg0
jsr SNDK_LZ_VRAM
;idy = SNDK_PALSPR0
ldy #63693
;WMADD = idy
sty 8577
;WMADDH = SNDK_PALSPR0
lda #:126
sta 8579
;DMA_BANK_6 = SNDK_LOGO_PAL
lda #:SNDK_LOGO_PAL
sta 17252
;idy = SNDK_LOGO_PAL
ldy #SNDK_LOGO_PAL
;DMA_ADD_6 = idy
sty 17250
;idy = 0x40
ldy #64
;DMA_SIZE_6 = idy
sty 17253
;MDMAEN = 0x40
lda #64
sta 16907
;CGADD = 0x80
lda #128
sta 8481
;DMA_BANK_5 = SNDK_PALSPR0
lda #:126
sta 17236
;idy = SNDK_PALSPR0
ldy #63693
;DMA_ADD_5 = idy
sty 17234
;idy = 0x40
ldy #64
;DMA_SIZE_5 = idy
sty 17237
;MDMAEN = 0x20
lda #32
sta 16907
;fade = 0
stz 1
.label_b131:
;call SNDK_Sprite
jsr SNDK_Sprite
;call SNDK_SpriteDraw
ldx #64
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #0
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #64
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #64
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #96
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #4
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #96
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #68
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #128
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #8
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #128
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #72
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #160
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #12
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #160
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #76
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;if time == 100
lda 0
cmp #100
bne .label_132
;fade = 1
lda #1
sta 1
.label_132:
;call SNDK_Fade
ldx #7
stx @SNDK_Fade..arg0
lda 1
sta @SNDK_Fade..arg1
jsr SNDK_Fade
;if acc == 1
cmp #1
bne .label_133
;if fade == 0
lda 1
cmp #0
bne .label_134
;time +=1
inc 0
;else
bra .label_135
.label_134:
;INIDISP = 0x80
lda #128
sta 8448
rtl
.label_135:
.label_133:
;call SNDK_WaitVBlank
jsr SNDK_WaitVBlank
.label_131:
;while 1 == 1

jmp .label_b131
rtl
..end
..begin start_logo_pixelheart
start_logo_pixelheart:
;time = 0
stz 0
;INIDISP = 0x80
lda #128
sta 8448
;SNDK_Light = 0x0
lda #0
sta 8315436
;TM = 0x10
lda #16
sta 8492
;call SNDK_LZ_VRAM
ldx #0
stx @SNDK_LZ_VRAM..arg0
jsr SNDK_LZ_VRAM
;idy = SNDK_PALSPR0
ldy #63693
;WMADD = idy
sty 8577
;WMADDH = SNDK_PALSPR0
lda #:126
sta 8579
;DMA_BANK_6 = START_LOGO_PAL
lda #:START_LOGO_PAL
sta 17252
;idy = START_LOGO_PAL
ldy #START_LOGO_PAL
;DMA_ADD_6 = idy
sty 17250
;idy = 0x40
ldy #64
;DMA_SIZE_6 = idy
sty 17253
;MDMAEN = 0x40
lda #64
sta 16907
;CGADD = 0x80
lda #128
sta 8481
;DMA_BANK_5 = SNDK_PALSPR0
lda #:126
sta 17236
;idy = SNDK_PALSPR0
ldy #63693
;DMA_ADD_5 = idy
sty 17234
;idy = 0x40
ldy #64
;DMA_SIZE_5 = idy
sty 17237
;MDMAEN = 0x20
lda #32
sta 16907
;fade = 0
stz 1
.label_b136:
;call SNDK_Sprite
jsr SNDK_Sprite
;call SNDK_SpriteDraw
ldx #0
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #0
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #0
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #64
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #32
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #4
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #32
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #68
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #64
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #8
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #64
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #72
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #96
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #12
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #96
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #76
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #128
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #128
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #128
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #192
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #160
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #132
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #160
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #196
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #192
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #136
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #192
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #200
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #224
stx @SNDK_SpriteDraw..arg0
ldx #80
stx @SNDK_SpriteDraw..arg1
ldx #140
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;call SNDK_SpriteDraw
ldx #224
stx @SNDK_SpriteDraw..arg0
ldx #112
stx @SNDK_SpriteDraw..arg1
ldx #204
stx @SNDK_SpriteDraw..arg2
ldx #0
stx @SNDK_SpriteDraw..arg3
ldx #255
stx @SNDK_SpriteDraw..arg4
jsr SNDK_SpriteDraw
;if time == 100
lda 0
cmp #100
bne .label_137
;fade = 1
lda #1
sta 1
.label_137:
;call SNDK_Fade
ldx #7
stx @SNDK_Fade..arg0
lda 1
sta @SNDK_Fade..arg1
jsr SNDK_Fade
;if acc == 1
cmp #1
bne .label_138
;if fade == 0
lda 1
cmp #0
bne .label_139
;time +=1
inc 0
;else
bra .label_140
.label_139:
;INIDISP = 0x80
lda #128
sta 8448
rtl
.label_140:
.label_138:
;call SNDK_WaitVBlank
jsr SNDK_WaitVBlank
.label_136:
;while 1 == 1

jmp .label_b136
rtl
..end
..begin SNDK_UnpackBG
SNDK_UnpackBG:
;asm
 rep #$20
;idy = adr
lda [134]
tay
;adr +=2
inc 134
inc 134
.label_b141:
;acc = adr
lda [134]
;adr +=2
inc 134
inc 134
;if acc &1 1
bit #1
beq .label_142
;data = acc &00xFFFE
and #65534
sta 128
;rle = adr
lda [134]
sta 130
;adr +=1
inc 134
;idy -=1
dey
;asm
 phy
;idy = rle &00x3F
lda 130
and #63
tay
;idy +=1
iny
;if rle &  0x80
lda 130
bit #128
beq .label_143
;data2 = data + 2
lda 128
clc
adc #2
sta 132
;idy -=1
dey
.label_b144:
;.ptr = data
lda 128
sta 8323072,X
;idx +=2
inx
inx
;.ptr = data2
lda 132
sta 8323072,X
;idx +=2
inx
inx
.label_144:
;loop idy == 0
dey 
bne .label_b144
;else
bra .label_145
.label_143:
;if rle &  0x40
lda 130
bit #64
beq .label_146
;acc = data
lda 128
.label_b147:
;.ptr = acc
sta 8323072,X
;idx +=2
inx
inx
;acc +=2
ina
ina
.label_147:
;loop idy == 0
dey 
bne .label_b147
;else
bra .label_148
.label_146:
;acc = data
lda 128
.label_b149:
;.ptr = acc
sta 8323072,X
;idx +=2
inx
inx
.label_149:
;loop idy == 0
dey 
bne .label_b149
.label_148:
.label_145:
;asm
 ply
;else
bra .label_150
.label_142:
;.ptr = acc
sta 8323072,X
;idx +=2
inx
inx
.label_150:
;idy -=1
dey
.label_141:
;loop idy == 0
dey 
bne .label_b141
rtl
..end
..begin SNDK_UnpackBGC
SNDK_UnpackBGC:
;asm
 rep #$20
;idy = adr
lda [134]
tay
;adr +=2
inc 134
inc 134
;rle = 0
stz 130
;asm
 sep #$20
.label_b151:
;acc = adr
lda [134]
;tmp = acc
sta 138
;asm
 rep #$20
;adr +=1
inc 134
;asm
 sep #$20
;if tmp &  0x80
lda 138
bit #128
beq .label_152
;data = acc &00x7F
and #127
sta 128
;rle = adr
lda [134]
sta 130
;asm
 rep #$20
;adr +=1
inc 134
;asm
 sep #$20
;idy -=1
dey
;asm
 phy
;idy = rle
ldy 130
;idy +=1
iny
;acc = data
lda 128
.label_b153:
;.ptr = acc
sta 8323072,X
;idx +=1
inx
.label_153:
;loop idy == 0
dey 
bne .label_b153
;asm
 ply
;else
bra .label_154
.label_152:
;.ptr = acc
sta 8323072,X
;idx +=1
inx
.label_154:
.label_151:
;loop idy == 0
dey 
bne .label_b151
rtl
..end
..begin SNDK_LoadBG
SNDK_LoadBG:
;asm
 rep #$20
;idx = ilist <<4
lda 224
asl
asl
asl
asl
tax
;adr = .ptr
lda SNDK_MAPLIST,X
sta 142
;idx +=2
inx
inx
;adrh = .ptr
lda SNDK_MAPLIST,X
sta 144
;idx +=2
inx
inx
;adr2 = .ptr
lda SNDK_MAPLIST,X
sta 146
;idx +=2
inx
inx
;adrh2 = .ptr
lda SNDK_MAPLIST,X
sta 148
;idx +=2
inx
inx
;adrc = .ptr
lda SNDK_MAPLIST,X
sta 150
;idx +=2
inx
inx
;adrhc = .ptr
lda SNDK_MAPLIST,X
sta 152
;idx +=2
inx
inx
;SNDK_BG.w = .ptr
lda SNDK_MAPLIST,X
sta 8316871
;idx +=2
inx
inx
;SNDK_BG.h = .ptr
lda SNDK_MAPLIST,X
sta 8316873
;px = ipx &00xFEFF
lda 226
and #65279
sta 154
;py = ipy &00xFEFF
lda 228
and #65279
sta 156
;if ipx &  0x100
lda 226
bit #256
beq .label_155
;px |=0xFF
lda 154
ora #255
sta 154
.label_155:
;if ipy &  0x100
lda 228
bit #256
beq .label_156
;py |=0xFF
lda 156
ora #255
sta 156
.label_156:
;SNDK_BG1_Scroll.x = px
lda 154
sta 8315542
;SNDK_BG2_Scroll.x = px
lda 154
sta 8315546
;SNDK_BG1_Scroll.y = py
lda 156
sta 8315544
;SNDK_BG2_Scroll.y = py
lda 156
sta 8315548
;idx = SNDK_BufferBG2
ldx #0
;iadr = adr
lda 142
sta 134
;iadrh = adrh
lda 144
sta 136
;if adrh != 0
lda 144
cmp #0
beq .label_157
;call SNDK_LZ_BG
jsr SNDK_LZ_BG
;asm
 rep #$20
.label_157:
;idx = SNDK_BufferBG1
ldx #16384
;iadr = adr2
lda 146
sta 134
;iadrh = adrh2
lda 148
sta 136
;if adrh2 != 0
lda 148
cmp #0
beq .label_158
;call SNDK_LZ_BG
jsr SNDK_LZ_BG
;asm
 rep #$20
.label_158:
;idx = SNDK_BufferBGC
ldx #32768
;iadr = adrc
lda 150
sta 134
;iadrh = adrhc
lda 152
sta 136
;asm
 sep #$20
;if adrhc != 0
lda 152
cmp #0
beq .label_159
;call SNDK_UnpackBGC
jsr SNDK_UnpackBGC
.label_159:
;asm
 rep #$20
;bg.w = SNDK_BG.w >>3
lda 8316871
lsr
lsr
lsr
sta 138
;py = py &00xFE00
lda 156
and #65024
sta 156
;py = py <<1
lda 156
asl
sta 156
;if SNDK_BG.w == 0x200
lda 8316871
cmp #512
bne .label_160
;py = py <<1
lda 156
asl
sta 156
.label_160:
;if SNDK_BG.w == 0x400
lda 8316871
cmp #1024
bne .label_161
;py = py <<2
lda 156
asl
asl
sta 156
.label_161:
;if SNDK_BG.w == 0x800
lda 8316871
cmp #2048
bne .label_162
;py = py <<3
lda 156
asl
asl
asl
sta 156
.label_162:
;if SNDK_BG.w == 0x1000
lda 8316871
cmp #4096
bne .label_163
;py = py <<4
lda 156
asl
asl
asl
asl
sta 156
.label_163:
;if SNDK_BG.w == 0x2000
lda 8316871
cmp #8192
bne .label_164
;py = py <<5
lda 156
asl
asl
asl
asl
asl
sta 156
.label_164:
;acc = px &00xFE00
lda 154
and #65024
;px = acc >>3
lsr
lsr
lsr
sta 154
;pos = px + py
lda 154
clc
adc 156
sta 158
;VMADD = 0x5400
lda #21504
sta 8470
;if adrh2 != 0
lda 148
cmp #0
beq .label_165
;idy = 0x20
ldy #32
;add = SNDK_BufferBG1 + pos
lda #16384
clc
adc 158
sta 160
.label_b166:
;DMA_ADD_0 = add
lda 160
sta 17154
;DMA_SIZE_0 = 0x40
lda #64
sta 17157
;asm
 sep #$20
;DMA_BANK_0 = 0x7F
lda #127
sta 17156
;MDMAEN = 0x01
lda #1
sta 16907
;asm
 rep #$20
;add +=bg.w
lda 160
clc
adc 138
sta 160
.label_166:
;loop idy == 0
dey 
bne .label_b166
.label_165:
;if adrh == 0
lda 144
cmp #0
bne .label_167
;asm
 sep #$20
rtl
.label_167:
;asm
 rep #$20
;VMADD = 0x5800
lda #22528
sta 8470
;idy = 0x20
ldy #32
;add = SNDK_BufferBG2 + pos
lda #0
clc
adc 158
sta 160
.label_b168:
;DMA_ADD_0 = add
lda 160
sta 17154
;DMA_SIZE_0 = 0x40
lda #64
sta 17157
;asm
 sep #$20
;DMA_BANK_0 = 0x7F
lda #127
sta 17156
;MDMAEN = 0x01
lda #1
sta 16907
;asm
 rep #$20
;add +=bg.w
lda 160
clc
adc 138
sta 160
.label_168:
;loop idy == 0
dey 
bne .label_b168
;asm
 sep #$20
rtl
..end
..begin SNDK_LimiteBG1
SNDK_LimiteBG1:
;asm
 rep #$20
;if SNDK_BG1_Scroll.x &0 0xC000
lda 8315542
bit #49152
beq .label_169
;SNDK_BG1_Scroll.x = 0
lda #0
sta 8315542
.label_169:
;if SNDK_BG1_Scroll.y &0 0xC000
lda 8315544
bit #49152
beq .label_170
;SNDK_BG1_Scroll.y = 0
lda #0
sta 8315544
.label_170:
;tmp = SNDK_BG1_Scroll.x +2256
lda 8315542
clc
adc #256
sta 128
;if tmp >= 1024
lda 128
cmp #1024
bcc .label_171
;SNDK_BG1_Scroll.x = SNDK_BG.w -2256
lda 8316871
sec
sbc #256
sta 8315542
.label_171:
;tmp = SNDK_BG1_Scroll.y +2225
lda 8315544
clc
adc #225
sta 128
;if tmp >= 1024
lda 128
cmp #1024
bcc .label_172
;SNDK_BG1_Scroll.y = SNDK_BG.h -2225
lda 8316873
sec
sbc #225
sta 8315544
.label_172:
;asm
 sep #$20
rtl
..end
..begin SNDK_LimiteBG2
SNDK_LimiteBG2:
;asm
 rep #$20
;if SNDK_BG2_Scroll.x &0 0xC000
lda 8315546
bit #49152
beq .label_173
;SNDK_BG2_Scroll.x = 0
lda #0
sta 8315546
.label_173:
;if SNDK_BG2_Scroll.y &0 0xC000
lda 8315548
bit #49152
beq .label_174
;SNDK_BG2_Scroll.y = 0
lda #0
sta 8315548
.label_174:
;tmp = SNDK_BG2_Scroll.x +2256
lda 8315546
clc
adc #256
sta 128
;if tmp >= SNDK_BG.w
lda 128
cmp 8316871
bcc .label_175
;SNDK_BG2_Scroll.x = SNDK_BG.w -2256
lda 8316871
sec
sbc #256
sta 8315546
.label_175:
;tmp = SNDK_BG2_Scroll.y +2225
lda 8315548
clc
adc #225
sta 128
;if tmp >= SNDK_BG.h
lda 128
cmp 8316873
bcc .label_176
;SNDK_BG2_Scroll.y = SNDK_BG.h -2225
lda 8316873
sec
sbc #225
sta 8315548
.label_176:
;asm
 sep #$20
rtl
..end
..begin SNDK_LZ_VRAM
SNDK_LZ_VRAM:
;asm
 rep #$20
;nlabel = nlabel <<3
lda 224
asl
asl
asl
sta 224
;idx = nlabel + SNDK_LOAD
lda 224
clc
adc #SNDK_LOAD
tax
;adr = .ptr
lda 8519680,X
sta 128
;idx +=2
inx
inx
;adrh = .ptr
lda 8519680,X
sta 130
;tmph = acc
sta 156
;idx +=2
inx
inx
;VMADD = .ptr
lda 8519680,X
sta 8470
;adr +=6
lda 128
clc
adc #6
sta 128
;idy = adr
lda [128]
tay
;adr +=3
lda 128
clc
adc #3
sta 128
;pal1 = adr
lda [128]
sta 142
;adr +=1
inc 128
;pal2 = adr
lda [128]
sta 144
;adr +=1
inc 128
;pal3 = adr
lda [128]
sta 146
;adr +=1
inc 128
;pal1 &=0xFF
lda 142
and #255
sta 142
;pal2 &=0xFF
lda 144
and #255
sta 144
;pal3 &=0xFF
lda 146
and #255
sta 146
;pal12 = 0
stz 160
;asm
 sep #$20
;pal12 = pal1 +ppal2
lda 142
clc
adc 144
sta 160
;asm
 rep #$20
;i = 0
stz 158
;opal1 = i + adr
lda 158
clc
adc 128
sta 148
;acc = pal1 <<3
lda 142
asl
asl
asl
;i +=acc
sta 222
lda 158
clc
adc 222
sta 158
;opal2 = i + adr
lda 158
clc
adc 128
sta 150
;acc = pal2 <<2
lda 144
asl
asl
;i +=acc
sta 222
lda 158
clc
adc 222
sta 158
;opal3 = i + adr
lda 158
clc
adc 128
sta 152
;acc = pal3 <<1
lda 146
asl
;i +=acc
sta 222
lda 158
clc
adc 222
sta 158
;adr +=i
lda 128
clc
adc 158
sta 128
;index = 0
stz 140
;asm
 sep #$20
.label_b177:
;index = adr
lda [128]
sta 140
;asm
 rep #$20
;adr +=1
inc 128
;asm
 sep #$20
;if index >= 0xFB
lda 140
cmp #251
bcc .label_178
;jump SNDK_LZ_JBEG
jmp SNDK_LZ_JBEG
.label_178:
;type = 0
stz 162
;if index >= pal1
lda 140
cmp 142
bcc .label_179
;type +=1
inc 162
.label_179:
;if index >= pal12
lda 140
cmp 160
bcc .label_180
;type +=1
inc 162
.label_180:
;if type == 0
lda 162
cmp #0
bne .label_181
;asm
 rep #$20
;acc = index <<3
lda 140
asl
asl
asl
;tmp = acc + opal1
clc
adc 148
sta 154
;VMDATA = tmp
lda [154]
sta 8472
;tmp +=2
inc 154
inc 154
;VMDATA = tmp
lda [154]
sta 8472
;tmp +=2
inc 154
inc 154
;VMDATA = tmp
lda [154]
sta 8472
;tmp +=2
inc 154
inc 154
;VMDATA = tmp
lda [154]
sta 8472
;asm
 sep #$20
;jump SNDK_LZ_JEND
jmp SNDK_LZ_JEND
.label_181:
;if type == 1
lda 162
cmp #1
bne .label_182
;asm
 rep #$20
;acc = index - pal1
lda 140
sec
sbc 142
;acc = acc <<2
asl
asl
;tmp = acc + opal2
clc
adc 150
sta 154
;VMDATA = tmp
lda [154]
sta 8472
;tmp +=2
inc 154
inc 154
;VMDATA = tmp
lda [154]
sta 8472
;asm
 sep #$20
;jump SNDK_LZ_JEND
jmp SNDK_LZ_JEND
.label_182:
;if type == 2
lda 162
cmp #2
bne .label_183
;asm
 rep #$20
;acc = index - pal12
lda 140
sec
sbc 160
;acc = acc <<1
asl
;tmp = acc + opal3
clc
adc 152
sta 154
;VMDATA = tmp
lda [154]
sta 8472
;asm
 sep #$20
.label_183:
;jump SNDK_LZ_JEND
jmp SNDK_LZ_JEND
SNDK_LZ_JBEG:
;if index == 0xFB
lda 140
cmp #251
bne .label_184
;acc = adr
lda [128]
;asm
 rep #$20
;acc &=0xFF
and #255
;acc +=1
ina
;idx = acc
tax
;adr +=1
inc 128
;buf1 = adr
lda [128]
sta 132
;adr +=2
inc 128
inc 128
;buf2 = adr
lda [128]
sta 134
;adr +=2
inc 128
inc 128
;buf3 = adr
lda [128]
sta 136
;adr +=2
inc 128
inc 128
;buf4 = adr
lda [128]
sta 138
;adr +=2
inc 128
inc 128
.label_b185:
;VMDATA = buf1
lda 132
sta 8472
;VMDATA = buf2
lda 134
sta 8472
;VMDATA = buf3
lda 136
sta 8472
;VMDATA = buf4
lda 138
sta 8472
.label_185:
;loop idx == 0
dex 
bne .label_b185
;asm
 sep #$20
;jump SNDK_LZ_JEND
jmp SNDK_LZ_JEND
.label_184:
;if index == 0xFC
lda 140
cmp #252
bne .label_186
;asm
 rep #$20
;VMDATA = adr
lda [128]
sta 8472
;adr +=2
inc 128
inc 128
;asm
 sep #$20
;jump SNDK_LZ_JEND
jmp SNDK_LZ_JEND
.label_186:
;if index == 0xFD
lda 140
cmp #253
bne .label_187
;asm
 rep #$20
;VMDATA = adr
lda [128]
sta 8472
;adr +=2
inc 128
inc 128
;VMDATA = adr
lda [128]
sta 8472
;adr +=2
inc 128
inc 128
;asm
 sep #$20
;jump SNDK_LZ_JEND
jmp SNDK_LZ_JEND
.label_187:
;if index == 0xFE
lda 140
cmp #254
bne .label_188
;asm
 rep #$20
;VMDATA = adr
lda [128]
sta 8472
;adr +=2
inc 128
inc 128
;VMDATA = adr
lda [128]
sta 8472
;adr +=2
inc 128
inc 128
;VMDATA = adr
lda [128]
sta 8472
;adr +=2
inc 128
inc 128
;VMDATA = adr
lda [128]
sta 8472
;adr +=2
inc 128
inc 128
;asm
 sep #$20
;jump SNDK_LZ_JEND
jmp SNDK_LZ_JEND
.label_188:
;if index == 0xFF
lda 140
cmp #255
bne .label_189
;acc = adr
lda [128]
;asm
 rep #$20
;idx = acc & 0xFF
and #255
tax
;adr +=1
inc 128
.label_b190:
;VMDATA = adr
lda [128]
sta 8472
;adr +=2
inc 128
inc 128
.label_190:
;loop idx == 0
dex 
bne .label_b190
;asm
 sep #$20
.label_189:
SNDK_LZ_JEND:
;idy -=1
dey
;if idy == 0
cpy #0
bne .label_191
rtl
.label_191:
.label_177:
;while 1 == 1

jmp .label_b177
rtl
..end
..begin SNDK_LZ_RAM
SNDK_LZ_RAM:
;asm
 rep #$20
;nlabel = nlabel <<3
lda 224
asl
asl
asl
sta 224
;idx = nlabel + SNDK_LOADR
lda 224
clc
adc #SNDK_LOADR
tax
;adr = .ptr
lda 8519680,X
sta 134
;adrh = .ptr
lda 8519682,X
sta 136
;tmph = adrh
lda 136
sta 156
;oadr = .ptr
lda 8519684,X
sta 158
;oadrh = .ptr
lda 8519686,X
sta 160
;adr +=6
lda 134
clc
adc #6
sta 134
;idy = adr
lda [134]
tay
;adr +=3
lda 134
clc
adc #3
sta 134
;pal1 = adr
lda [134]
sta 148
;adr +=1
inc 134
;pal2 = adr
lda [134]
sta 150
;adr +=1
inc 134
;pal3 = adr
lda [134]
sta 152
;adr +=1
inc 134
;pal1 &=0xFF
lda 148
and #255
sta 148
;pal2 &=0xFF
lda 150
and #255
sta 150
;pal3 &=0xFF
lda 152
and #255
sta 152
;pal12 = 0
stz 164
;asm
 sep #$20
;pal12 = pal1 +ppal2
lda 148
clc
adc 150
sta 164
;asm
 rep #$20
;i = 0
stz 162
;opal1 = i + adr
lda 162
clc
adc 134
sta 128
;acc = pal1 <<3
lda 148
asl
asl
asl
;i +=acc
sta 222
lda 162
clc
adc 222
sta 162
;opal2 = i + adr
lda 162
clc
adc 134
sta 130
;acc = pal2 <<2
lda 150
asl
asl
;i +=acc
sta 222
lda 162
clc
adc 222
sta 162
;opal3 = i + adr
lda 162
clc
adc 134
sta 132
;acc = pal3 <<1
lda 152
asl
;i +=acc
sta 222
lda 162
clc
adc 222
sta 162
;adr +=i
lda 134
clc
adc 162
sta 134
;index = 0
stz 146
;asm
 sep #$20
.label_b192:
;index = adr
lda [134]
sta 146
;asm
 rep #$20
;adr +=1
inc 134
;asm
 sep #$20
;if index >= 0xFB
lda 146
cmp #251
bcc .label_193
;jump SNDK_LZR_JBEG
jmp SNDK_LZR_JBEG
.label_193:
;type = 0
stz 166
;if index >= pal1
lda 146
cmp 148
bcc .label_194
;type +=1
inc 166
.label_194:
;if index >= pal12
lda 146
cmp 164
bcc .label_195
;type +=1
inc 166
.label_195:
;if type == 0
lda 166
cmp #0
bne .label_196
;asm
 rep #$20
;acc = index <<3
lda 146
asl
asl
asl
;tmp = acc + opal1
clc
adc 128
sta 154
;oadr = tmp
lda [154]
sta [158]
;oadr +=2
inc 158
inc 158
;tmp +=2
inc 154
inc 154
;oadr = tmp
lda [154]
sta [158]
;oadr +=2
inc 158
inc 158
;tmp +=2
inc 154
inc 154
;oadr = tmp
lda [154]
sta [158]
;oadr +=2
inc 158
inc 158
;tmp +=2
inc 154
inc 154
;oadr = tmp
lda [154]
sta [158]
;oadr +=2
inc 158
inc 158
;asm
 sep #$20
;jump SNDK_LZR_JEND
jmp SNDK_LZR_JEND
.label_196:
;if type == 1
lda 166
cmp #1
bne .label_197
;asm
 rep #$20
;acc = index - pal1
lda 146
sec
sbc 148
;acc = acc <<2
asl
asl
;tmp = acc + opal2
clc
adc 130
sta 154
;oadr = tmp
lda [154]
sta [158]
;oadr +=2
inc 158
inc 158
;tmp +=2
inc 154
inc 154
;oadr = tmp
lda [154]
sta [158]
;oadr +=2
inc 158
inc 158
;asm
 sep #$20
;jump SNDK_LZR_JEND
jmp SNDK_LZR_JEND
.label_197:
;if type == 2
lda 166
cmp #2
bne .label_198
;asm
 rep #$20
;acc = index - pal12
lda 146
sec
sbc 164
;acc = acc <<1
asl
;tmp = acc + opal3
clc
adc 132
sta 154
;oadr = tmp
lda [154]
sta [158]
;oadr +=2
inc 158
inc 158
;asm
 sep #$20
.label_198:
;jump SNDK_LZR_JEND
jmp SNDK_LZR_JEND
SNDK_LZR_JBEG:
;if index == 0xFB
lda 146
cmp #251
bne .label_199
;acc = adr
lda [134]
;asm
 rep #$20
;acc &=0xFF
and #255
;acc +=1
ina
;idx = acc
tax
;adr +=1
inc 134
;buf1 = adr
lda [134]
sta 138
;adr +=2
inc 134
inc 134
;buf2 = adr
lda [134]
sta 140
;adr +=2
inc 134
inc 134
;buf3 = adr
lda [134]
sta 142
;adr +=2
inc 134
inc 134
;buf4 = adr
lda [134]
sta 144
;adr +=2
inc 134
inc 134
.label_b200:
;oadr = buf1
lda 138
sta [158]
;oadr +=2
inc 158
inc 158
;oadr = buf2
lda 140
sta [158]
;oadr +=2
inc 158
inc 158
;oadr = buf3
lda 142
sta [158]
;oadr +=2
inc 158
inc 158
;oadr = buf4
lda 144
sta [158]
;oadr +=2
inc 158
inc 158
.label_200:
;loop idx == 0
dex 
bne .label_b200
;asm
 sep #$20
;jump SNDK_LZR_JEND
jmp SNDK_LZR_JEND
.label_199:
;if index == 0xFC
lda 146
cmp #252
bne .label_201
;asm
 rep #$20
;oadr = adr
lda [134]
sta [158]
;oadr +=2
inc 158
inc 158
;adr +=2
inc 134
inc 134
;asm
 sep #$20
;jump SNDK_LZR_JEND
jmp SNDK_LZR_JEND
.label_201:
;if index == 0xFD
lda 146
cmp #253
bne .label_202
;asm
 rep #$20
;oadr = adr
lda [134]
sta [158]
;oadr +=2
inc 158
inc 158
;adr +=2
inc 134
inc 134
;oadr = adr
lda [134]
sta [158]
;oadr +=2
inc 158
inc 158
;adr +=2
inc 134
inc 134
;asm
 sep #$20
;jump SNDK_LZR_JEND
jmp SNDK_LZR_JEND
.label_202:
;if index == 0xFE
lda 146
cmp #254
bne .label_203
;asm
 rep #$20
;oadr = adr
lda [134]
sta [158]
;oadr +=2
inc 158
inc 158
;adr +=2
inc 134
inc 134
;oadr = adr
lda [134]
sta [158]
;oadr +=2
inc 158
inc 158
;adr +=2
inc 134
inc 134
;oadr = adr
lda [134]
sta [158]
;oadr +=2
inc 158
inc 158
;adr +=2
inc 134
inc 134
;oadr = adr
lda [134]
sta [158]
;oadr +=2
inc 158
inc 158
;adr +=2
inc 134
inc 134
;asm
 sep #$20
;jump SNDK_LZR_JEND
jmp SNDK_LZR_JEND
.label_203:
;if index == 0xFF
lda 146
cmp #255
bne .label_204
;acc = adr
lda [134]
;asm
 rep #$20
;idx = acc & 0xFF
and #255
tax
;adr +=1
inc 134
.label_b205:
;oadr = adr
lda [134]
sta [158]
;oadr +=2
inc 158
inc 158
;adr +=2
inc 134
inc 134
.label_205:
;loop idx == 0
dex 
bne .label_b205
;asm
 sep #$20
.label_204:
SNDK_LZR_JEND:
;idy -=1
dey
;if idy == 0
cpy #0
bne .label_206
rtl
.label_206:
.label_192:
;while 1 == 1

jmp .label_b192
rtl
..end
..begin SNDK_LZ_BG
SNDK_LZ_BG:
;asm
 rep #$20
;tmph = adrh
lda 136
sta 176
;oadr = idx
stx 178
;oadrh = 0x7F
lda #127
sta 180
;adr +=6
lda 134
clc
adc #6
sta 134
;idy = adr
lda [134]
tay
;adr +=3
lda 134
clc
adc #3
sta 134
;pal1 = adr
lda [134]
sta 168
;adr +=1
inc 134
;pal2 = adr
lda [134]
sta 170
;adr +=1
inc 134
;pal3 = adr
lda [134]
sta 172
;adr +=1
inc 134
;pal1 &=0xFF
lda 168
and #255
sta 168
;pal2 &=0xFF
lda 170
and #255
sta 170
;pal3 &=0xFF
lda 172
and #255
sta 172
;pal12 = 0
stz 184
;asm
 sep #$20
;pal12 = pal1 +ppal2
lda 168
clc
adc 170
sta 184
;asm
 rep #$20
;i = 0
stz 182
;opal1 = i + adr
lda 182
clc
adc 134
sta 128
;acc = pal1 <<3
lda 168
asl
asl
asl
;i +=acc
sta 222
lda 182
clc
adc 222
sta 182
;opal2 = i + adr
lda 182
clc
adc 134
sta 130
;acc = pal2 <<2
lda 170
asl
asl
;i +=acc
sta 222
lda 182
clc
adc 222
sta 182
;opal3 = i + adr
lda 182
clc
adc 134
sta 132
;acc = pal3 <<1
lda 172
asl
;i +=acc
sta 222
lda 182
clc
adc 222
sta 182
;adr +=i
lda 134
clc
adc 182
sta 134
;index = 0
stz 166
;asm
 sep #$20
.label_b207:
;index = adr
lda [134]
sta 166
;asm
 rep #$20
;adr +=1
inc 134
;asm
 sep #$20
;if index >= 0xFB
lda 166
cmp #251
bcc .label_208
;jump SNDK_LZBG_JBEG
jmp SNDK_LZBG_JBEG
.label_208:
;type = 0
stz 186
;if index >= pal1
lda 166
cmp 168
bcc .label_209
;type +=1
inc 186
.label_209:
;if index >= pal12
lda 166
cmp 184
bcc .label_210
;type +=1
inc 186
.label_210:
;if type == 0
lda 186
cmp #0
bne .label_211
;asm
 rep #$20
;acc = index <<3
lda 166
asl
asl
asl
;tmp = acc + opal1
clc
adc 128
sta 174
;oadr = tmp
lda [174]
sta [178]
;oadr +=2
inc 178
inc 178
;tmp +=2
inc 174
inc 174
;oadr = tmp
lda [174]
sta [178]
;oadr +=2
inc 178
inc 178
;tmp +=2
inc 174
inc 174
;oadr = tmp
lda [174]
sta [178]
;oadr +=2
inc 178
inc 178
;tmp +=2
inc 174
inc 174
;oadr = tmp
lda [174]
sta [178]
;oadr +=2
inc 178
inc 178
;asm
 sep #$20
;jump SNDK_LZBG_JEND
jmp SNDK_LZBG_JEND
.label_211:
;if type == 1
lda 186
cmp #1
bne .label_212
;asm
 rep #$20
;acc = index - pal1
lda 166
sec
sbc 168
;acc = acc <<2
asl
asl
;tmp = acc + opal2
clc
adc 130
sta 174
;oadr = tmp
lda [174]
sta [178]
;oadr +=2
inc 178
inc 178
;tmp +=2
inc 174
inc 174
;oadr = tmp
lda [174]
sta [178]
;oadr +=2
inc 178
inc 178
;asm
 sep #$20
;jump SNDK_LZBG_JEND
jmp SNDK_LZBG_JEND
.label_212:
;if type == 2
lda 186
cmp #2
bne .label_213
;asm
 rep #$20
;acc = index - pal12
lda 166
sec
sbc 184
;acc = acc <<1
asl
;tmp = acc + opal3
clc
adc 132
sta 174
;oadr = tmp
lda [174]
sta [178]
;oadr +=2
inc 178
inc 178
;asm
 sep #$20
.label_213:
;jump SNDK_LZBG_JEND
jmp SNDK_LZBG_JEND
SNDK_LZBG_JBEG:
;if index == 0xFB
lda 166
cmp #251
bne .label_214
;acc = adr
lda [134]
;asm
 rep #$20
;acc &=0xFF
and #255
;acc +=1
ina
;idx = acc
tax
;adr +=1
inc 134
;buf1 = adr
lda [134]
sta 158
;adr +=2
inc 134
inc 134
;buf2 = adr
lda [134]
sta 160
;adr +=2
inc 134
inc 134
;buf3 = adr
lda [134]
sta 162
;adr +=2
inc 134
inc 134
;buf4 = adr
lda [134]
sta 164
;adr +=2
inc 134
inc 134
.label_b215:
;oadr = buf1
lda 158
sta [178]
;oadr +=2
inc 178
inc 178
;oadr = buf2
lda 160
sta [178]
;oadr +=2
inc 178
inc 178
;oadr = buf3
lda 162
sta [178]
;oadr +=2
inc 178
inc 178
;oadr = buf4
lda 164
sta [178]
;oadr +=2
inc 178
inc 178
.label_215:
;loop idx == 0
dex 
bne .label_b215
;asm
 sep #$20
;jump SNDK_LZBG_JEND
jmp SNDK_LZBG_JEND
.label_214:
;if index == 0xFC
lda 166
cmp #252
bne .label_216
;asm
 rep #$20
;oadr = adr
lda [134]
sta [178]
;oadr +=2
inc 178
inc 178
;adr +=2
inc 134
inc 134
;asm
 sep #$20
;jump SNDK_LZBG_JEND
jmp SNDK_LZBG_JEND
.label_216:
;if index == 0xFD
lda 166
cmp #253
bne .label_217
;asm
 rep #$20
;oadr = adr
lda [134]
sta [178]
;oadr +=2
inc 178
inc 178
;adr +=2
inc 134
inc 134
;oadr = adr
lda [134]
sta [178]
;oadr +=2
inc 178
inc 178
;adr +=2
inc 134
inc 134
;asm
 sep #$20
;jump SNDK_LZBG_JEND
jmp SNDK_LZBG_JEND
.label_217:
;if index == 0xFE
lda 166
cmp #254
bne .label_218
;asm
 rep #$20
;oadr = adr
lda [134]
sta [178]
;oadr +=2
inc 178
inc 178
;adr +=2
inc 134
inc 134
;oadr = adr
lda [134]
sta [178]
;oadr +=2
inc 178
inc 178
;adr +=2
inc 134
inc 134
;oadr = adr
lda [134]
sta [178]
;oadr +=2
inc 178
inc 178
;adr +=2
inc 134
inc 134
;oadr = adr
lda [134]
sta [178]
;oadr +=2
inc 178
inc 178
;adr +=2
inc 134
inc 134
;asm
 sep #$20
;jump SNDK_LZBG_JEND
jmp SNDK_LZBG_JEND
.label_218:
;if index == 0xFF
lda 166
cmp #255
bne .label_219
;acc = adr
lda [134]
;asm
 rep #$20
;idx = acc & 0xFF
and #255
tax
;adr +=1
inc 134
.label_b220:
;oadr = adr
lda [134]
sta [178]
;oadr +=2
inc 178
inc 178
;adr +=2
inc 134
inc 134
.label_220:
;loop idx == 0
dex 
bne .label_b220
;asm
 sep #$20
.label_219:
SNDK_LZBG_JEND:
;idy -=1
dey
;if idy == 0
cpy #0
bne .label_221
rtl
.label_221:
.label_207:
;while 1 == 1

jmp .label_b207
rtl
..end
..begin SNDK_zorder
SNDK_zorder:
;if count == 0
lda 224
cmp #0
bne .label_222
rtl
.label_222:
;if count >= 16
lda 224
cmp #16
bcc .label_223
rtl
.label_223:
;asm
 rep #$20
;acc = count &00x1F
lda 224
and #31
;idx = acc <<1
asl
tax
;asm
 sep #$20
;tarray = 0
stz 133
;acc = 0
lda #0
.label_b224:
;.ptr = acc
sta 133,X
.label_224:
;loop idx == 0
dex 
bne .label_b224
;asm
 rep #$20
;idy = count &00x1F
lda 224
and #31
tay
;asm
 sep #$20
.label_b225:
;idx = idy
ldx 0
;ay = .ptr
lda 8315442,X
sta 129
;order = 0
stz 128
;asm
 rep #$20
;idx = count &00x1F
lda 224
and #31
tax
;asm
 sep #$20
.label_b226:
;ax = .ptr
lda 8315442,X
sta 130
;if ax <  ay
lda 130
cmp 129
bcs .label_227
;order +=1
inc 128
.label_227:
.label_226:
;loop idx == 0
dex 
bne .label_b226
;asm
 rep #$20
;idx = order &00x1F
lda 128
and #31
tax
;asm
 sep #$20
;value = 0
stz 132
;tmp = .ptr
lda 133,X
sta 131
;if acc != 0
cmp #0
beq .label_228
;value = tmp
lda 131
sta 132
.label_228:
;.ptr = tmp + 1
lda 131
clc
adc #1
sta 133,X
;idx = idy
ldx 0
;.ptr = order + value
lda 128
clc
adc 132
sta 8315490,X
.label_225:
;loop idy == 0
dey 
bne .label_b225
rtl
..end
..begin SNDK_PrintLineFill
SNDK_PrintLineFill:
;asm
 rep #$20
;idx = py <<6
lda 226
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 224
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;asm
 rep #$20
;idy = nc
ldy 228
.label_b229:
;.ptr = data
lda 230
sta 8318924,X
;idx +=2
inx
inx
.label_229:
;loop idy == 0
dey 
bne .label_b229
;asm
 sep #$20
rtl
..end
..begin SNDK_PrintLineErase
SNDK_PrintLineErase:
;asm
 rep #$20
;idx = py <<6
lda 226
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 224
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;idy = nc
ldy 228
.label_b230:
;.ptr = 0
lda #0
sta 8318924,X
;idx +=2
inx
inx
.label_230:
;loop idy == 0
dey 
bne .label_b230
rtl
..end
..begin SNDK_Printchar
SNDK_Printchar:
;asm
 rep #$20
;idx = py <<6
lda 227
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 225
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;.ptr = char
lda 224
sta 8318924,X
;.ptr = pal
lda 229
sta 8318925,X
rtl
..end
..begin SNDK_Printdata
SNDK_Printdata:
;asm
 rep #$20
;idx = py <<6
lda 229
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 227
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;asm
 rep #$20
;idy = nc &00xFF
lda 231
and #255
tay
;asm
 sep #$20
.label_b231:
;.ptr = adr
lda [224]
sta 8318924,X
;.ptr = pal
lda 233
sta 8318925,X
;asm
 rep #$20
;adr +=1
inc 224
;idx +=2
inx
inx
;asm
 sep #$20
.label_231:
;loop idy == 0
dey 
bne .label_b231
rtl
..end
..begin SNDK_PrintLine
SNDK_PrintLine:
;asm
 rep #$20
;idx = py <<6
lda 229
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 227
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;acc = adr
lda [224]
.label_b232:
;.ptr = acc -332
sec
sbc #32
sta 8318924,X
;.ptr = pal
lda 231
sta 8318925,X
;asm
 rep #$20
;adr +=1
inc 224
;idx +=2
inx
inx
;asm
 sep #$20
;acc = adr
lda [224]
.label_232:
;while acc != 0
cmp #0
bne .label_b232
rtl
..end
..begin SNDK_Print
SNDK_Print:
;idx = 2
ldx #2
;count = idx
stx 128
;asm
 rep #$20
;idx = py <<6
lda 229
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 227
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;acc = adr
lda [224]
.label_b233:
;.ptr = acc -332
sec
sbc #32
sta 8318924,X
;.ptr = pal
lda 231
sta 8318925,X
;asm
 rep #$20
;adr +=1
inc 224
;idx +=2
inx
inx
;count +=2
inc 128
inc 128
;asm
 sep #$20
;if adr == 0x0A
lda [224]
cmp #10
bne .label_234
;asm
 rep #$20
;idx +=0x40
txa 
clc
adc #64
tax
;idx -=count
txa 
sec
sbc 128
tax
;count = 2
lda #2
sta 128
;adr +=1
inc 224
;idx +=2
inx
inx
;asm
 sep #$20
.label_234:
.label_233:
;while adr != 0
lda [224]
cmp #0
bne .label_b233
rtl
..end
..begin SNDK_PrintNumber8
SNDK_PrintNumber8:
;asm
 rep #$20
;idx = py <<6
lda 227
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 225
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;tnumber = number
lda 224
sta 130
;tnumber1 = 0x10
lda #16
sta 128
;tnumber2 = acc
sta 129
;if tnumber >= 100
lda 130
cmp #100
bcc .label_235
;tnumber -=100
lda 130
sec
sbc #100
sta 130
;tnumber1 +=1
inc 128
.label_235:
;if tnumber >= 100
lda 130
cmp #100
bcc .label_236
;tnumber -=100
lda 130
sec
sbc #100
sta 130
;tnumber1 +=1
inc 128
.label_236:
;.ptr = tnumber1
lda 128
sta 8318924,X
;.ptr = pal
lda 229
sta 8318925,X
;idx +=2
inx
inx
;if tnumber >= 50
lda 130
cmp #50
bcc .label_237
;tnumber -=50
lda 130
sec
sbc #50
sta 130
;tnumber2 +=5
lda 129
clc
adc #5
sta 129
.label_237:
;if tnumber >= 20
lda 130
cmp #20
bcc .label_238
;tnumber -=20
lda 130
sec
sbc #20
sta 130
;tnumber2 +=2
inc 129
inc 129
.label_238:
;if tnumber >= 20
lda 130
cmp #20
bcc .label_239
;tnumber -=20
lda 130
sec
sbc #20
sta 130
;tnumber2 +=2
inc 129
inc 129
.label_239:
;if tnumber >= 10
lda 130
cmp #10
bcc .label_240
;tnumber -=10
lda 130
sec
sbc #10
sta 130
;tnumber2 +=1
inc 129
.label_240:
;.ptr = tnumber2
lda 129
sta 8318924,X
;.ptr = pal
lda 229
sta 8318925,X
;idx +=2
inx
inx
;.ptr = tnumber + 0x10
lda 130
clc
adc #16
sta 8318924,X
;.ptr = pal
lda 229
sta 8318925,X
rtl
..end
..begin SNDK_PrintNumber8M
SNDK_PrintNumber8M:
;asm
 rep #$20
;idx = py <<6
lda 227
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 225
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;tnumber = number
lda 224
sta 129
;tnumber2 = 0x10
lda #16
sta 128
;if tnumber >= 50
lda 129
cmp #50
bcc .label_241
;tnumber -=50
lda 129
sec
sbc #50
sta 129
;tnumber2 +=5
lda 128
clc
adc #5
sta 128
.label_241:
;if tnumber >= 20
lda 129
cmp #20
bcc .label_242
;tnumber -=20
lda 129
sec
sbc #20
sta 129
;tnumber2 +=2
inc 128
inc 128
.label_242:
;if tnumber >= 20
lda 129
cmp #20
bcc .label_243
;tnumber -=20
lda 129
sec
sbc #20
sta 129
;tnumber2 +=2
inc 128
inc 128
.label_243:
;if tnumber >= 10
lda 129
cmp #10
bcc .label_244
;tnumber -=10
lda 129
sec
sbc #10
sta 129
;tnumber2 +=1
inc 128
.label_244:
;.ptr = tnumber2
lda 128
sta 8318924,X
;.ptr = pal
lda 229
sta 8318925,X
;idx +=2
inx
inx
;.ptr = tnumber + 0x10
lda 129
clc
adc #16
sta 8318924,X
;.ptr = pal
lda 229
sta 8318925,X
rtl
..end
..begin SNDK_PrintNumber16
SNDK_PrintNumber16:
;asm
 rep #$20
;idx = py <<6
lda 228
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 226
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;asm
 rep #$20
;tnumber = number
lda 224
sta 136
;tnumber1 = 0x10
lda #16
sta 128
;tnumber2 = acc
sta 130
;tnumber3 = acc
sta 132
;tnumber4 = acc
sta 134
;if tnumber >= 50000
lda 136
cmp #50000
bcc .label_245
;tnumber -=50000
lda 136
sec
sbc #50000
sta 136
;tnumber1 +=5
lda 128
clc
adc #5
sta 128
.label_245:
;if tnumber >= 20000
lda 136
cmp #20000
bcc .label_246
;tnumber -=20000
lda 136
sec
sbc #20000
sta 136
;tnumber1 +=2
inc 128
inc 128
.label_246:
;if tnumber >= 20000
lda 136
cmp #20000
bcc .label_247
;tnumber -=20000
lda 136
sec
sbc #20000
sta 136
;tnumber1 +=2
inc 128
inc 128
.label_247:
;if tnumber >= 10000
lda 136
cmp #10000
bcc .label_248
;tnumber -=10000
lda 136
sec
sbc #10000
sta 136
;tnumber1 +=1
inc 128
.label_248:
;if tnumber >= 5000
lda 136
cmp #5000
bcc .label_249
;tnumber -=5000
lda 136
sec
sbc #5000
sta 136
;tnumber2 +=5
lda 130
clc
adc #5
sta 130
.label_249:
;if tnumber >= 2000
lda 136
cmp #2000
bcc .label_250
;tnumber -=2000
lda 136
sec
sbc #2000
sta 136
;tnumber2 +=2
inc 130
inc 130
.label_250:
;if tnumber >= 2000
lda 136
cmp #2000
bcc .label_251
;tnumber -=2000
lda 136
sec
sbc #2000
sta 136
;tnumber2 +=2
inc 130
inc 130
.label_251:
;if tnumber >= 1000
lda 136
cmp #1000
bcc .label_252
;tnumber -=1000
lda 136
sec
sbc #1000
sta 136
;tnumber2 +=1
inc 130
.label_252:
;if tnumber >= 500
lda 136
cmp #500
bcc .label_253
;tnumber -=500
lda 136
sec
sbc #500
sta 136
;tnumber3 +=5
lda 132
clc
adc #5
sta 132
.label_253:
;if tnumber >= 200
lda 136
cmp #200
bcc .label_254
;tnumber -=200
lda 136
sec
sbc #200
sta 136
;tnumber3 +=2
inc 132
inc 132
.label_254:
;if tnumber >= 200
lda 136
cmp #200
bcc .label_255
;tnumber -=200
lda 136
sec
sbc #200
sta 136
;tnumber3 +=2
inc 132
inc 132
.label_255:
;if tnumber >= 100
lda 136
cmp #100
bcc .label_256
;tnumber -=100
lda 136
sec
sbc #100
sta 136
;tnumber3 +=1
inc 132
.label_256:
;if tnumber >= 50
lda 136
cmp #50
bcc .label_257
;tnumber -=50
lda 136
sec
sbc #50
sta 136
;tnumber4 +=5
lda 134
clc
adc #5
sta 134
.label_257:
;if tnumber >= 20
lda 136
cmp #20
bcc .label_258
;tnumber -=20
lda 136
sec
sbc #20
sta 136
;tnumber4 +=2
inc 134
inc 134
.label_258:
;if tnumber >= 20
lda 136
cmp #20
bcc .label_259
;tnumber -=20
lda 136
sec
sbc #20
sta 136
;tnumber4 +=2
inc 134
inc 134
.label_259:
;if tnumber >= 10
lda 136
cmp #10
bcc .label_260
;tnumber -=10
lda 136
sec
sbc #10
sta 136
;tnumber4 +=1
inc 134
.label_260:
;asm
 sep #$20
;.ptr = tnumber1
lda 128
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
;idx +=2
inx
inx
;.ptr = tnumber2
lda 130
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
;idx +=2
inx
inx
;.ptr = tnumber3
lda 132
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
;idx +=2
inx
inx
;.ptr = tnumber4
lda 134
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
;idx +=2
inx
inx
;.ptr = tnumber + 0x10
lda 136
clc
adc #16
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
rtl
..end
..begin SNDK_PrintHexa8
SNDK_PrintHexa8:
;asm
 rep #$20
;idx = py <<6
lda 227
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 225
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;acc = number >>4
lda 224
lsr
lsr
lsr
lsr
;acc = acc & 0xF
and #15
;if acc >= 0xA
cmp #10
bcc .label_261
;acc +=7
clc
adc #7
.label_261:
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 229
sta 8318925,X
;idx +=2
inx
inx
;acc = number
lda 224
;acc = acc & 0xF
and #15
;if acc >= 0xA
cmp #10
bcc .label_262
;acc +=7
clc
adc #7
.label_262:
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 229
sta 8318925,X
rtl
..end
..begin SNDK_PrintHexa16
SNDK_PrintHexa16:
;asm
 rep #$20
;idx = py <<6
lda 228
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 226
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;asm
 rep #$20
;acc = number
lda 224
;tnumber3 = acc >>4
lsr
lsr
lsr
lsr
sta 130
;tnumber2 = acc >>4
lsr
lsr
lsr
lsr
sta 128
;acc = acc >>4
lsr
lsr
lsr
lsr
;asm
 sep #$20
;acc = acc & 0xF
and #15
;if acc >= 0xA
cmp #10
bcc .label_263
;acc +=7
clc
adc #7
.label_263:
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
;idx +=2
inx
inx
;acc = tnumber2
lda 128
;acc = acc & 0xF
and #15
;if acc >= 0xA
cmp #10
bcc .label_264
;acc +=7
clc
adc #7
.label_264:
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
;idx +=2
inx
inx
;acc = tnumber3
lda 130
;acc = acc & 0xF
and #15
;if acc >= 0xA
cmp #10
bcc .label_265
;acc +=7
clc
adc #7
.label_265:
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
;idx +=2
inx
inx
;acc = number
lda 224
;acc = acc & 0xF
and #15
;if acc >= 0xA
cmp #10
bcc .label_266
;acc +=7
clc
adc #7
.label_266:
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
rtl
..end
..begin SNDK_PrintDec2
SNDK_PrintDec2:
;asm
 rep #$20
;idx = py <<6
lda 227
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 225
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;acc = number >>4
lda 224
lsr
lsr
lsr
lsr
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 229
sta 8318925,X
;idx +=2
inx
inx
;acc = number &00x0F
lda 224
and #15
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 229
sta 8318925,X
rtl
..end
..begin SNDK_PrintDec4
SNDK_PrintDec4:
;asm
 rep #$20
;idx = py <<6
lda 228
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 226
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;asm
 rep #$20
;tnumber = number
lda 224
sta 128
;asm
 sep #$20
;acc = tnumber2 >>4
lda 129
lsr
lsr
lsr
lsr
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
;idx +=2
inx
inx
;acc = tnumber2 &00x0F
lda 129
and #15
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
;idx +=2
inx
inx
;acc = number >>4
lda 224
lsr
lsr
lsr
lsr
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
;idx +=2
inx
inx
;acc = number &00x0F
lda 224
and #15
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 230
sta 8318925,X
rtl
..end
..begin SNDK_PrintDec8
SNDK_PrintDec8:
;asm
 rep #$20
;idx = py <<6
lda 230
asl
asl
asl
asl
asl
asl
tax
;acc = px <<1
lda 228
asl
;acc = acc & 0x1FF
and #511
;idx +=acc
sta 222
txa 
clc
adc 222
tax
;asm
 sep #$20
;asm
 rep #$20
;tnumber = number
lda 224
sta 128
;asm
 sep #$20
;acc = tnumber2 >>4
lda 129
lsr
lsr
lsr
lsr
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 232
sta 8318925,X
;idx +=2
inx
inx
;acc = tnumber2 &00x0F
lda 129
and #15
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 232
sta 8318925,X
;idx +=2
inx
inx
;acc = number >>4
lda 224
lsr
lsr
lsr
lsr
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 232
sta 8318925,X
;idx +=2
inx
inx
;acc = number &00x0F
lda 224
and #15
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 232
sta 8318925,X
;idx +=2
inx
inx
;asm
 rep #$20
;tnumber = number2
lda 226
sta 128
;asm
 sep #$20
;acc = tnumber2 >>4
lda 129
lsr
lsr
lsr
lsr
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 232
sta 8318925,X
;idx +=2
inx
inx
;acc = tnumber2 &00x0F
lda 129
and #15
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 232
sta 8318925,X
;idx +=2
inx
inx
;acc = number2 >>4
lda 226
lsr
lsr
lsr
lsr
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 232
sta 8318925,X
;idx +=2
inx
inx
;acc = number2 &00x0F
lda 226
and #15
;acc +=0x10
clc
adc #16
;.ptr = acc
sta 8318924,X
;.ptr = pal
lda 232
sta 8318925,X
rtl
..end
..begin SNDK_DMA_Sprite
SNDK_DMA_Sprite:
;asm
 rep #$20
;SNDK_VBlank.dma_spr0.addr = adr
lda 224
sta 568
;SNDK_VBlank.dma_spr0.add = add
lda 231
sta 570
;SNDK_VBlank.dma_spr0.vmaddr = vmaddr
lda 229
sta 576
;SNDK_VBlank.dma_spr0.size = size
lda 227
sta 572
;asm
 sep #$20
;SNDK_VBlank.dma_spr0.bank = bank
lda 226
sta 574
;SNDK_VBlank.dma_spr0.channel = channel
lda 233
sta 578
rtl
..end
..begin SNDK_DMA_Tile
SNDK_DMA_Tile:
;asm
 rep #$20
;SNDK_VBlank.dma_tile.addr = adr
lda 224
sta 604
;SNDK_VBlank.dma_tile.add = add
lda 231
sta 606
;SNDK_VBlank.dma_tile.vmaddr = vmaddr
lda 229
sta 612
;SNDK_VBlank.dma_tile.size = size
lda 227
sta 608
;asm
 sep #$20
;SNDK_VBlank.dma_tile.bank = bank
lda 226
sta 610
;SNDK_VBlank.dma_tile.channel = channel
lda 233
sta 614
rtl
..end
..begin SNDK_DMA_TileLine
SNDK_DMA_TileLine:
;asm
 rep #$20
;SNDK_VBlank.tileset.addr = adr
lda 224
sta 620
;SNDK_VBlank.tileset.vaddr = vmaddr
lda 229
sta 618
;SNDK_VBlank.tileset.size = size
lda 227
sta 622
;asm
 sep #$20
;SNDK_VBlank.tileset.bank = bank
lda 226
sta 624
;SNDK_VBlank.tileset.channel = 1
lda #1
sta 626
rtl
..end
..begin SNDK_Sprite_SetOAM
SNDK_Sprite_SetOAM:
;asm
 rep #$20
;SNDK_Sprite.oam = oam <<2
lda 224
asl
asl
sta 628
;asm
 sep #$20
rtl
..end
..begin SNDK_SpriteEngine
SNDK_SpriteEngine:
;asm
 rep #$20
;if n >= 16
lda 226
cmp #16
bcc .label_267
;n = 16
lda #16
sta 226
.label_267:
;if n == 0
lda 226
cmp #0
bne .label_268
rtl
.label_268:
;idy = n
ldy 226
;idx = 0
ldx #0
;SNDK_Sprite.oam = oam <<2
lda 224
asl
asl
sta 628
.label_b269:
;.ptr +=.ptr
lda 8315554,X
clc
adc 8315558,X
sta 8315554,X
;posx = acc >>2
lsr
lsr
sta 128
;.ptr +=.ptr
lda 8315556,X
clc
adc 8315560,X
sta 8315556,X
;posy = acc >>2
lsr
lsr
sta 130
;tile = .ptr
lda 8315562,X
sta 132
;fptr = .ptr
lda 8315570,X
sta 140
;oldx = idx
stx 142
;call fptr
phx
ldx #0
jsr (140)
plx
;idx +=0x20
txa 
clc
adc #32
tax
.label_269:
;loop idy == 0
dey 
bne .label_b269
;idx = dma_count <<5
lda 642
asl
asl
asl
asl
asl
tax
;oldx = idx
stx 142
;index = .ptr
lda 8315568,X
sta 153
;ianim = .ptr
lda 8315572,X
sta 148
;.ptr = ianim + 2
lda 148
clc
adc #2
sta 8315572,X
;list = .ptr
lda 8315564,X
sta 144
;lista = .ptr + index
lda 144
tax
lda 8519684,X
clc
adc 153
sta 150
;nanim = .ptr
lda 150
tax
lda 8519680,X
sta 152
;idx = lista + ianim
lda 150
clc
adc 148
tax
;add = .ptr
lda 8519682,X
sta 146
;idx = list
ldx 144
;SNDK_VBlank.dma_spr1.addr = .ptr + add
lda 8519680,X
clc
adc 146
sta 580
;SNDK_VBlank.dma_spr1.size = .ptr
lda 8519690,X
sta 584
;SNDK_VBlank.dma_spr1.add = .ptr
lda 8519692,X
sta 582
;SNDK_VBlank.dma_spr1.vmaddr = .ptr
lda 8519688,X
sta 588
;asm
 sep #$20
;if ndma == 0
lda 228
cmp #0
bne .label_270
rtl
.label_270:
;SNDK_VBlank.dma_spr1.bank = .ptr
lda 8519682,X
sta 586
;SNDK_VBlank.dma_spr1.channel = .ptr
lda 8519694,X
sta 590
;.ptr = 0
lda 142
tax
lda #0
ldx 142
sta 8315581,X
;if ianim == nanim
lda 148
cmp 152
bne .label_271
;.ptr = 0
lda 142
tax
lda #0
ldx 142
sta 8315572,X
;.ptr = 1
lda 142
tax
lda #1
ldx 142
sta 8315581,X
.label_271:
;asm
 rep #$20
;oldx +=0x20
lda 142
clc
adc #32
sta 142
;idx = oldx
ldx 142
;acc = ndma &33
lda 228
and #3
;if acc == 2
cmp #2
bne .label_272
;index = .ptr
lda 8315568,X
sta 153
;ianim = .ptr
lda 8315572,X
sta 148
;.ptr = ianim + 2
lda 148
clc
adc #2
sta 8315572,X
;list = .ptr
lda 8315564,X
sta 144
;lista = .ptr + index
lda 144
tax
lda 8519684,X
clc
adc 153
sta 150
;nanim = .ptr
lda 150
tax
lda 8519680,X
sta 152
;idx = lista + ianim
lda 150
clc
adc 148
tax
;add = .ptr
lda 8519682,X
sta 146
;idx = list
ldx 144
;SNDK_VBlank.dma_spr2.addr = .ptr + add
lda 8519680,X
clc
adc 146
sta 592
;SNDK_VBlank.dma_spr2.size = .ptr
lda 8519690,X
sta 596
;SNDK_VBlank.dma_spr2.add = .ptr
lda 8519692,X
sta 594
;SNDK_VBlank.dma_spr2.vmaddr = .ptr
lda 8519688,X
sta 600
.label_272:
;asm
 sep #$20
;if ndma == 2
lda 228
cmp #2
bne .label_273
;SNDK_VBlank.dma_spr2.bank = .ptr
lda 8519682,X
sta 598
;SNDK_VBlank.dma_spr2.channel = .ptr
lda 8519694,X
sta 602
;.ptr = 0
lda 142
tax
lda #0
ldx 142
sta 8315581,X
;if ianim == nanim
lda 148
cmp 152
bne .label_274
;.ptr = 0
lda 142
tax
lda #0
ldx 142
sta 8315572,X
;.ptr = 1
lda 142
tax
lda #1
ldx 142
sta 8315581,X
.label_274:
.label_273:
;dma_count +=ndma
lda 642
clc
adc 228
sta 642
;if dma_count >= n
lda 642
cmp 226
bcc .label_275
;dma_count = 0
stz 642
.label_275:
rtl
..end
..begin SNDK_SpriteDraw
SNDK_SpriteDraw:
;idx = SNDK_Sprite.oam
ldx 628
;.ptr = position.x
lda 224
sta 8314880,X
;.ptr = position.y
lda 226
sta 8314881,X
;.ptr = tile
lda 227
sta 8314882,X
;.ptr = attribute
lda 228
sta 8314883,X
;asm
 rep #$20
;SNDK_Sprite.oam = idx + 4
txa 
clc
adc #4
sta 628
;indexh = acc >>4
lsr
lsr
lsr
lsr
sta 128
;if position.x &! 0xFF00
lda 224
bit #65280
bne .label_276
;flag = flag &00xAA
lda 229
and #170
sta 229
.label_276:
;asm
 sep #$20
;.ptr |=flag
lda 128
tax
lda 8315392,X
ora 229
ldx 128
sta 8315392,X
rtl
..end
..begin SNDK_SpriteDrawMeta2x2
SNDK_SpriteDrawMeta2x2:
;idx = SNDK_Sprite.oam
ldx 628
;.ptr = position.x
lda 224
sta 8314880,X
;.ptr = acc
sta 8314888,X
;.ptr = acc +SSNDK_SPR_SIZE
clc
adc 208
sta 8314884,X
;.ptr = acc
sta 8314892,X
;.ptr = position.y
lda 226
sta 8314881,X
;.ptr = acc
sta 8314885,X
;.ptr = acc +SSNDK_SPR_SIZE
clc
adc 208
sta 8314889,X
;.ptr = acc
sta 8314893,X
;.ptr = tile
lda 227
sta 8314882,X
;.ptr = acc +SSNDK_SPR_SIZET
clc
adc 209
sta 8314886,X
;.ptr = tile +SSNDK_SPR_DEC
lda 227
clc
adc 212
sta 8314890,X
;.ptr = acc +SSNDK_SPR_SIZET
clc
adc 209
sta 8314894,X
;if attribute &  0x80
lda 228
bit #128
beq .label_277
;if attribute &  0x40
lda 228
bit #64
beq .label_278
;.ptr = tile
lda 227
sta 8314894,X
;.ptr = acc +SSNDK_SPR_SIZET
clc
adc 209
sta 8314890,X
;.ptr = tile +SSNDK_SPR_DEC
lda 227
clc
adc 212
sta 8314886,X
;.ptr = acc +SSNDK_SPR_SIZET
clc
adc 209
sta 8314882,X
;else
bra .label_279
.label_278:
;.ptr = tile
lda 227
sta 8314890,X
;.ptr = acc +SSNDK_SPR_SIZET
clc
adc 209
sta 8314894,X
;.ptr = tile +SSNDK_SPR_DEC
lda 227
clc
adc 212
sta 8314882,X
;.ptr = acc +SSNDK_SPR_SIZET
clc
adc 209
sta 8314886,X
.label_279:
;else
bra .label_280
.label_277:
;if attribute &  0x40
lda 228
bit #64
beq .label_281
;.ptr = tile
lda 227
sta 8314886,X
;.ptr = acc +SSNDK_SPR_SIZET
clc
adc 209
sta 8314882,X
;.ptr = tile +SSNDK_SPR_DEC
lda 227
clc
adc 212
sta 8314894,X
;.ptr = acc +SSNDK_SPR_SIZET
clc
adc 209
sta 8314890,X
;else
bra .label_282
.label_281:
;.ptr = tile
lda 227
sta 8314882,X
;.ptr = acc +SSNDK_SPR_SIZET
clc
adc 209
sta 8314886,X
;.ptr = tile +SSNDK_SPR_DEC
lda 227
clc
adc 212
sta 8314890,X
;.ptr = acc +SSNDK_SPR_SIZET
clc
adc 209
sta 8314894,X
.label_282:
.label_280:
;.ptr = attribute
lda 228
sta 8314883,X
;.ptr = acc
sta 8314887,X
;.ptr = acc
sta 8314891,X
;.ptr = acc
sta 8314895,X
;asm
 rep #$20
;SNDK_Sprite.oam = idx + 16
txa 
clc
adc #16
sta 628
;indexh = acc >>4
lsr
lsr
lsr
lsr
sta 128
;if position.x &! 0xFF00
lda 224
bit #65280
bne .label_283
;flag = flag &00xAA
lda 229
and #170
sta 229
.label_283:
;asm
 sep #$20
;.ptr = flag
lda 128
tax
lda 229
ldx 128
sta 8315392,X
rtl
..end
..begin SNDK_SpriteDrawMeta2x2H
SNDK_SpriteDrawMeta2x2H:
;idx = SNDK_Sprite.oam
ldx 628
;.ptr = position.x
lda 224
sta 8314880,X
;.ptr = acc
sta 8314888,X
;.ptr = acc +SSNDK_SPR_SIZE2
clc
adc 210
sta 8314884,X
;.ptr = acc
sta 8314892,X
;.ptr = position.y
lda 226
sta 8314881,X
;.ptr = acc
sta 8314885,X
;.ptr = acc +SSNDK_SPR_SIZE2
clc
adc 210
sta 8314889,X
;.ptr = acc
sta 8314893,X
;.ptr = tile
lda 227
sta 8314882,X
;.ptr = acc +SSNDK_SPR_SIZET2
clc
adc 211
sta 8314886,X
;.ptr = tile +SSNDK_SPR_DEC2
lda 227
clc
adc 213
sta 8314890,X
;.ptr = acc +SSNDK_SPR_SIZET2
clc
adc 211
sta 8314894,X
;if attribute &  0x80
lda 228
bit #128
beq .label_284
;if attribute &  0x40
lda 228
bit #64
beq .label_285
;.ptr = tile
lda 227
sta 8314894,X
;.ptr = acc +SSNDK_SPR_SIZET2
clc
adc 211
sta 8314890,X
;.ptr = tile +SSNDK_SPR_DEC2
lda 227
clc
adc 213
sta 8314886,X
;.ptr = acc +SSNDK_SPR_SIZET2
clc
adc 211
sta 8314882,X
;else
bra .label_286
.label_285:
;.ptr = tile
lda 227
sta 8314890,X
;.ptr = acc +SSNDK_SPR_SIZET2
clc
adc 211
sta 8314894,X
;.ptr = tile +SSNDK_SPR_DEC2
lda 227
clc
adc 213
sta 8314882,X
;.ptr = acc +SSNDK_SPR_SIZET2
clc
adc 211
sta 8314886,X
.label_286:
;else
bra .label_287
.label_284:
;if attribute &  0x40
lda 228
bit #64
beq .label_288
;.ptr = tile
lda 227
sta 8314886,X
;.ptr = acc +SSNDK_SPR_SIZET2
clc
adc 211
sta 8314882,X
;.ptr = tile +SSNDK_SPR_DEC2
lda 227
clc
adc 213
sta 8314894,X
;.ptr = acc +SSNDK_SPR_SIZET2
clc
adc 211
sta 8314890,X
;else
bra .label_289
.label_288:
;.ptr = tile
lda 227
sta 8314882,X
;.ptr = acc +SSNDK_SPR_SIZET2
clc
adc 211
sta 8314886,X
;.ptr = tile +SSNDK_SPR_DEC2
lda 227
clc
adc 213
sta 8314890,X
;.ptr = acc +SSNDK_SPR_SIZET2
clc
adc 211
sta 8314894,X
.label_289:
.label_287:
;.ptr = attribute
lda 228
sta 8314883,X
;.ptr = acc
sta 8314887,X
;.ptr = acc
sta 8314891,X
;.ptr = acc
sta 8314895,X
;asm
 rep #$20
;SNDK_Sprite.oam = idx + 16
txa 
clc
adc #16
sta 628
;indexh = acc >>4
lsr
lsr
lsr
lsr
sta 128
;if position.x &! 0xFF00
lda 224
bit #65280
bne .label_290
;flag = flag &00xAA
lda 229
and #170
sta 229
.label_290:
;asm
 sep #$20
;.ptr = flag
lda 128
tax
lda 229
ldx 128
sta 8315392,X
rtl
..end
..begin SNDK_wramcopy
SNDK_wramcopy:
;asm
 rep #$20
;WMADD = dstl
lda 224
sta 8577
;DMA_ADD_6 = srcl
lda 227
sta 17250
;DMA_SIZE_6 = size
lda 230
sta 17253
;asm
 sep #$20
;WMADDH = dstb
lda 226
sta 8579
;DMA_BANK_6 = srcb
lda 229
sta 17252
;MDMAEN = 0x40
lda #64
sta 16907
rtl
..end
SNDK_str_pause:
.db 80,65,85,83,69,0,
..begin SNDK_Pause
SNDK_Pause:
;if SNDK_Joypad.npad1h &  0x10
lda 528
bit #16
beq .label_291
;SNDK_Joypad.npad1h = 0
stz 528
;SNDK_SFX1 = sfx1
lda 644
sta 8315538
;else
bra .label_292
.label_291:
;if SNDK_Joypad.npad2h &  0x10
lda 530
bit #16
beq .label_293
;SNDK_Joypad.npad2h = 0
stz 530
;SNDK_SFX1 = sfx1
lda 644
sta 8315538
;else
bra .label_294
.label_293:
rtl
.label_294:
.label_292:
;call SNDK_PrintLine
ldx #SNDK_str_pause
stx @SNDK_PrintLine..arg0
ldx #:SNDK_str_pause
stx @SNDK_PrintLine..arg1
ldx #14
stx @SNDK_PrintLine..arg2
ldx #13
stx @SNDK_PrintLine..arg3
ldx #32
stx @SNDK_PrintLine..arg4
jsr SNDK_PrintLine
.label_b295:
;if SNDK_Joypad.npad1h &  0x10
lda 528
bit #16
beq .label_296
;SNDK_SFX1 = sfx2
lda 645
sta 8315538
;call SNDK_PrintLineErase
ldx #14
stx @SNDK_PrintLineErase..arg0
ldx #13
stx @SNDK_PrintLineErase..arg1
ldx #5
stx @SNDK_PrintLineErase..arg2
jsr SNDK_PrintLineErase
rtl
.label_296:
;if SNDK_Joypad.npad2h &  0x10
lda 530
bit #16
beq .label_297
;SNDK_SFX1 = sfx2
lda 645
sta 8315538
;call SNDK_PrintLineErase
ldx #13
stx @SNDK_PrintLineErase..arg0
ldx #13
stx @SNDK_PrintLineErase..arg1
ldx #5
stx @SNDK_PrintLineErase..arg2
jsr SNDK_PrintLineErase
rtl
.label_297:
;call SNDK_SFX_Engine
ldx #3
stx @SNDK_SFX_Engine..arg0
jsr SNDK_SFX_Engine
;call SNDK_WaitVBlank
jsr SNDK_WaitVBlank
.label_295:
;while 1 
jmp .label_b295
rtl
..end
..begin SNDK_Fade
SNDK_Fade:
;if dirf == 0xFF
lda 225
cmp #255
bne .label_298
lda #2
rtl
.label_298:
;if dirf != 0
lda 225
cmp #0
beq .label_299
;if SNDK_Light == 0
lda 8315436
cmp #0
bne .label_300
lda #1
rtl
.label_300:
;else
bra .label_301
.label_299:
;if SNDK_Light == 0xF
lda 8315436
cmp #15
bne .label_302
lda #1
rtl
.label_302:
.label_301:
;count +=1
inc 647
;if count == ncount
lda 647
cmp 224
bne .label_303
;if dirf == 0
lda 225
cmp #0
bne .label_304
;SNDK_Light +=1
lda 8315436
clc
adc #1
sta 8315436
;else
bra .label_305
.label_304:
;SNDK_Light -=1
lda 8315436
sec
sbc #1
sta 8315436
.label_305:
;count = 0
stz 647
.label_303:
lda #0
rtl
..end
..begin rand
rand:
;asm
 rep #$20
;acc = SNDK_vrand
lda 8315432
;acc = acc <<5
asl
asl
asl
asl
asl
;acc ^=acc
sta 222
eor 222
;acc = acc >>6
lsr
lsr
lsr
lsr
lsr
lsr
;acc ^=acc
sta 222
eor 222
;acc = acc <<2
asl
asl
;acc ^=acc
sta 222
eor 222
;SNDK_vrand = acc
sta 8315432
;asm
 sep #$20
rtl
..end
..begin SNDK_HitboxSet
SNDK_HitboxSet:
;asm
 rep #$20
;if x &  0x2000
lda 224
bit #8192
beq .label_306
;acc = x & 0xFF
lda 224
and #255
;acc = acc ^ 0xFF
eor #255
;w -=acc
sta 222
lda 228
sec
sbc 222
sta 228
;x = 0
stz 224
.label_306:
;rect.x = x
lda 224
sta 128
;rect.y = y
lda 226
sta 130
;rect.w = x +ww
lda 224
clc
adc 228
sta 132
;rect.h = y +hh
lda 226
clc
adc 230
sta 134
;if rect.w &  0x1F00
lda 132
bit #7936
beq .label_307
;rect.w = 255
lda #255
sta 132
.label_307:
;asm
 sep #$20
rtl
..end
..begin SNDK_HitboxRectDot
SNDK_HitboxRectDot:
;acc = py
lda 225
;if acc == 0xE0
cmp #224
bne .label_308
lda #0
rtl
.label_308:
;if acc >= rect.y
cmp 130
bcc .label_309
;if acc <  rect.h
cmp 134
bcs .label_310
;acc = px
lda 224
;if acc >= rect.x
cmp 128
bcc .label_311
;if acc <  rect.w
cmp 132
bcs .label_312
lda #1
rtl
.label_312:
.label_311:
.label_310:
.label_309:
lda #0
rtl
..end
..begin Load_SKS
Load_SKS:
;asm
 
	rep #$20
	lda #$BBAA
	.Load_SKS_b0:   
		cmp $2140
	bne .Load_SKS_b0
	
	; Initialize transfer
	lda #$200 
	sta $2142

	lda #$1CC
	sta $2140
	sep #$20
	
	.Load_SKS_b1:	
		cmp $2140 
	bne .Load_SKS_b1

	; Send data
	ldx #0
	ldy #$580
	.Load_SKS_b2:	
		lda Super_Kannagi_Sound,X
		sta $2141
		txa
		sta $2140
		.Load_SKS_b3:	
			cmp $2140
		bne .Load_SKS_b3
		inx
		dey
	bne .Load_SKS_b2

	;Begin execution
	rep #$20 
	lda #$200
	sta $2142
	sep #$20
	
	lda #0
	sta $2141

	lda $2140
	adc #2
	sta $2140
	
	
rtl
..end
..begin LKS_SPC_SetData
LKS_SPC_SetData:
;idy = isize
ldy 228
;idx = 0
ldx #0
.label_b313:
;APUIO1 = 0x16
lda #22
sta 8513
;asm
 rep #$20
;APUIO2 = addr
lda [224]
sta 8514
;addr +=2
inc 224
inc 224
;asm
 sep #$20
;asm
 
		lda $104
		sta $2140
		.LKS_SPC_Wait1:
			cmp $2140
		beq .LKS_SPC_Wait1
		stz $2141
		lda $2140
		sta $104
		
;idy -=1
dey
.label_313:
;loop idy == 0
dey 
bne .label_b313
;APUIO1 = 0
stz 8513
rtl
..end
..begin LKS_SPC_Get
LKS_SPC_Get:
;APUIO1 = cmd1
lda 224
sta 8513
;asm
 
	lda $104
	sta $2140
	.LKS_SPC_Wait2:
		cmp $2140
	beq .LKS_SPC_Wait2
	stz $2141
	lda $2140
	sta $104
	
rtl
..end
..begin LKS_SPC_Set2
LKS_SPC_Set2:
;APUIO1 = cmd1
lda 224
sta 8513
;APUIO2 =?cmd2
ldy 225
sty 8514
;asm
 
	lda $104
	sta $2140
	.LKS_SPC_Wait3:
		cmp $2140
	beq .LKS_SPC_Wait3
	stz $2141
	lda $2140
	sta $104
	
rtl
..end
..begin LKS_SPC_Set
LKS_SPC_Set:
;APUIO1 = cmd1
lda 224
sta 8513
;APUIO2 = cmd2
lda 225
sta 8514
;APUIO3 = cmd3
lda 226
sta 8515
;asm
 
	lda $104
	sta $2140
	.LKS_SPC_Wait4:
		cmp $2140
	beq .LKS_SPC_Wait4
	stz $2141
	lda $2140
	sta $104
	
rtl
..end
..begin SNDK_SFX_Engine
SNDK_SFX_Engine:
;sfx1 = SNDK_SFX1
lda 8315538
sta 128
;sfx2 = SNDK_SFX2
lda 8315539
sta 129
;sfx3 = SNDK_SFX3
lda 8315540
sta 130
;sfx4 = SNDK_SFX4
lda 8315541
sta 131
;if SNDK_SFX_TIMER == 1
lda 8315431
cmp #1
bne .label_314
;call LKS_SPC_Set
ldx #38
stx @LKS_SPC_Set..arg0
lda 128
sta @LKS_SPC_Set..arg1
lda 129
sta @LKS_SPC_Set..arg2
jsr LKS_SPC_Set
;SNDK_SFX1 = 0xFF
lda #255
sta 8315538
;SNDK_SFX2 = 0xFF
lda #255
sta 8315539
.label_314:
;if SNDK_SFX_TIMER >= ntimer
lda 8315431
cmp 224
bcc .label_315
;call LKS_SPC_Set
ldx #40
stx @LKS_SPC_Set..arg0
lda 130
sta @LKS_SPC_Set..arg1
lda 131
sta @LKS_SPC_Set..arg2
jsr LKS_SPC_Set
;SNDK_SFX3 = 0xFF
lda #255
sta 8315540
;SNDK_SFX4 = 0xFF
lda #255
sta 8315541
;SNDK_SFX_TIMER = 0
lda #0
sta 8315431
.label_315:
;SNDK_SFX_TIMER +=1
lda 8315431
clc
adc #1
sta 8315431
rtl
..end
MAPMENU_SPR:
START_LOGO_SPR:
START_LOGO_PAL:
START_LOGO_SPR2:
SNDK_LOGO_SPR:
SNDK_LOGO_PAL:
MAP_START_LOGO:
..begin SNDK_Init
SNDK_Init:
;BGMODE = 0x39
lda #57
sta 8453
;MOSAIC = 0x00
stz 8454
;BG1SC = 0x54
lda #84
sta 8455
;BG2SC = 0x58
lda #88
sta 8456
;BG3SC = 0x5C
lda #92
sta 8457
;BG4SC = 0x50
lda #80
sta 8458
;BG12NBA = 0x00
stz 8459
;BG34NBA = 0x44
lda #68
sta 8460
;SNDK_BGNBA = 0x00
lda #0
sta 8315439
;BG3H0FS = 0
stz 8465
;BG3H0FS = 0
stz 8465
;BG3V0FS = 0
stz 8466
;BG3V0FS = 0
stz 8466
;BG4H0FS = 0
stz 8467
;BG4H0FS = 0
stz 8467
;BG4V0FS = 0
stz 8468
;BG4V0FS = 0
stz 8468
;VMAINC = 0x80
lda #128
sta 8469
;TM = 0x17
lda #23
sta 8492
;COLDATA = 0xE0
lda #224
sta 8498
;WRIO = 0xFF
lda #255
sta 16897
;SETINI = 0
stz 8499
;TS = 0x00
stz 8493
;CGSWSEL = 0x00
stz 8496
;CGADSUB = 0x00
stz 8497
;W12SEL = 0
stz 8483
;W34SEL = 0
stz 8484
;WOBJSEL = 0
stz 8485
;M7SEL = 0
stz 8474
;TMW = 0
stz 8494
;TSW = 0
stz 8495
;WH0 = 0
stz 8486
;WH1 = 0
stz 8487
;WH2 = 0
stz 8488
;WH3 = 0
stz 8489
;WBGLOG = 0
stz 8490
;WOBJLOG = 0
stz 8491
;M7A = 0
stz 8475
;M7B = 0
stz 8476
;M7C = 0
stz 8477
;M7D = 0
stz 8478
;M7X = 0
stz 8479
;M7Y = 0
stz 8480
;idx = 0
ldx #0
;HDMA_BANK_0 = 0
stz 17159
;HDMA_ADD_0 = idx
stx 17160
;HDMA_LINE_0 = idx
stx 17162
;HDMA_BANK_1 = 0
stz 17175
;HDMA_ADD_1 = idx
stx 17176
;HDMA_LINE_1 = idx
stx 17178
;HDMA_BANK_2 = 0
stz 17191
;HDMA_ADD_2 = idx
stx 17192
;HDMA_LINE_2 = idx
stx 17194
;HDMA_BANK_3 = 0
stz 17207
;HDMA_ADD_3 = idx
stx 17208
;HDMA_LINE_3 = idx
stx 17210
;HDMA_BANK_4 = 0
stz 17223
;HDMA_ADD_4 = idx
stx 17224
;HDMA_LINE_4 = idx
stx 17226
;HDMA_BANK_5 = 0
stz 17239
;HDMA_ADD_5 = idx
stx 17240
;HDMA_LINE_5 = idx
stx 17242
;HDMA_BANK_6 = 0
stz 17255
;HDMA_ADD_6 = idx
stx 17256
;HDMA_LINE_6 = idx
stx 17258
;HDMA_BANK_7 = 0
stz 17271
;HDMA_ADD_7 = idx
stx 17272
;HDMA_LINE_7 = idx
stx 17274
;DMA_0 = 0x01
lda #1
sta 17152
;DMA_BADD_0 = 0x18
lda #24
sta 17153
;DMA_1 = 0x01
lda #1
sta 17168
;DMA_BADD_1 = 0x18
lda #24
sta 17169
;DMA_2 = 0x01
lda #1
sta 17184
;DMA_BADD_2 = 0x18
lda #24
sta 17185
;DMA_3 = 0x01
lda #1
sta 17200
;DMA_BADD_3 = 0x18
lda #24
sta 17201
;DMA_4 = 0x02
lda #2
sta 17216
;DMA_BADD_4 = 0x04
lda #4
sta 17217
;DMA_5 = 0x02
lda #2
sta 17232
;DMA_BADD_5 = 0x22
lda #34
sta 17233
;DMA_6 = 0x00
stz 17248
;DMA_BADD_6 = 0x80
lda #128
sta 17249
;DMA_7 = 0x18
lda #24
sta 17264
;DMA_BADD_7 = 0x80
lda #128
sta 17265
;idy = SNDK_RAM
ldy #512
;WMADD = idy
sty 8577
;WMADDH = SNDK_RAM
lda #:126
sta 8579
;DMA_BANK_7 = SNDK_INIT_DATA1
lda #:SNDK_INIT_DATA1
sta 17268
;idy = SNDK_INIT_DATA1
ldy #SNDK_INIT_DATA1
;DMA_ADD_7 = idy
sty 17266
;idy = 0xFE00
ldy #65024
;DMA_SIZE_7 = idy
sty 17269
;MDMAEN = 0x80
lda #128
sta 16907
;idy = 0
ldy #0
;WMADD = idy
sty 8577
;WMADDH = 0x7F
lda #127
sta 8579
;DMA_BANK_7 = SNDK_INIT_DATA1
lda #:SNDK_INIT_DATA1
sta 17268
;idy = SNDK_INIT_DATA1
ldy #SNDK_INIT_DATA1
;DMA_ADD_7 = idy
sty 17266
;idy = 0xFF00
ldy #65280
;DMA_SIZE_7 = idy
sty 17269
;MDMAEN = 0x80
lda #128
sta 16907
;call Load_SKS
jsr Load_SKS
;.ptr = 0
lda #0
ldx 0
sta 260
;asm
 rep #$20
;idx = 0
ldx #0
;acc = 0
lda #0
;VMADD = 0
stz 8470
;idy = 4096
ldy #4096
.label_b316:
;VMDATA =aacc
sta 8472
;VMDATA =aacc
sta 8472
;VMDATA =aacc
sta 8472
;VMDATA =aacc
sta 8472
;VMDATA =aacc
sta 8472
;VMDATA =aacc
sta 8472
;VMDATA =aacc
sta 8472
;VMDATA =aacc
sta 8472
.label_316:
;loop idy == 0
dey 
bne .label_b316
;idy = 16
ldy #16
;idx = 0
ldx #0
.label_b317:
;.ptr = -128
lda #65408
sta 8315554,X
;.ptr = -128
lda #65408
sta 8315556,X
;idx +=0x20
txa 
clc
adc #32
tax
.label_317:
;loop idy == 0
dey 
bne .label_b317
;asm
 sep #$20
;call SNDK_LZ_VRAM
ldx #2
stx @SNDK_LZ_VRAM..arg0
jsr SNDK_LZ_VRAM
;idy = SNDK_PALBG0
ldy #63437
;WMADD = idy
sty 8577
;WMADDH = SNDK_PALBG0
lda #:126
sta 8579
;DMA_BANK_6 = DATA_FONT_SNDK_P
lda #:DATA_FONT_SNDK_P
sta 17252
;idy = DATA_FONT_SNDK_P
ldy #DATA_FONT_SNDK_P
;DMA_ADD_6 = idy
sty 17250
;idy = 0x20
ldy #32
;DMA_SIZE_6 = idy
sty 17253
;MDMAEN = 0x40
lda #64
sta 16907
;idy = 0
ldy #0
;OAMADD = idy
sty 8450
;DMA_BANK_4 = 0x7E
lda #126
sta 17220
;idy = SNDK_OAM0.x
ldy #57344
;DMA_ADD_4 = idy
sty 17218
;idy = 0x220
ldy #544
;DMA_SIZE_4 = idy
sty 17221
;MDMAEN = 0x10
lda #16
sta 16907
;OBJSEL = 0x63
lda #99
sta 8449
;SNDK_SPR_SIZE = 16
lda #16
sta 208
;SNDK_SPR_SIZET = 2
lda #2
sta 209
;SNDK_SPR_SIZE2 = 32
lda #32
sta 210
;SNDK_SPR_SIZET2 = 4
lda #4
sta 211
;SNDK_SPR_DEC = 32
lda #32
sta 212
;SNDK_SPR_DEC2 = 64
lda #64
sta 213
;SNDK_SFX1 = 0xFF
lda #255
sta 8315538
;SNDK_SFX2 = 0xFF
lda #255
sta 8315539
;SNDK_SFX3 = 0xFF
lda #255
sta 8315540
;SNDK_SFX4 = 0xFF
lda #255
sta 8315541
;call SNDK_SetVBlank_bg3size
ldx #128
stx @SNDK_SetVBlank_bg3size..arg0
jsr SNDK_SetVBlank_bg3size
rtl
..end
..begin SNDK_Clear_BG3
SNDK_Clear_BG3:
;DMA_7 = 0x18
lda #24
sta 17264
;DMA_BADD_7 = 0x80
lda #128
sta 17265
;idy = SNDK_BG3.t1
ldy #61388
;WMADD = idy
sty 8577
;WMADDH = SNDK_BG3.t1
lda #:126
sta 8579
;DMA_BANK_7 = SNDK_INIT_DATA1
lda #:SNDK_INIT_DATA1
sta 17268
;idy = SNDK_INIT_DATA1
ldy #SNDK_INIT_DATA1
;DMA_ADD_7 = idy
sty 17266
;idy = 0x800
ldy #2048
;DMA_SIZE_7 = idy
sty 17269
;MDMAEN = 0x80
lda #128
sta 16907
rtl
..end
SNDK_INIT_DATA1:
.db 0,
..begin SNDK_ModeAlpha
SNDK_ModeAlpha:
;TS = 0x11
lda #17
sta 8493
;CGSWSEL = 0x02
lda #2
sta 8496
;CGADSUB = 0x42
lda #66
sta 8497
rtl
..end
..begin SNDK_ModeAlpha2
SNDK_ModeAlpha2:
;TS = 0x12
lda #18
sta 8493
;CGSWSEL = 0x02
lda #2
sta 8496
;CGADSUB = 0x41
lda #65
sta 8497
rtl
..end
..begin SNDK_NoModeAlpha
SNDK_NoModeAlpha:
;TS = 0x00
stz 8493
;CGSWSEL = 0x00
stz 8496
;CGADSUB = 0x00
stz 8497
rtl
..end
DATA_FONT_SNDK_S:
.incbin SNDK/fontm.spr
DATA_FONT_SNDK_P:
.incbin SNDK/fontm.pal
.incbin SNDK/fontm2.pal
.incbin SNDK/fontm3.pal
.incbin SNDK/fontm5.pal
.org  $FFB0
.org  $FFC0
.db 83,85,80,69,82,32,75,65,78,78,65,71,73,32,83,79,85,78,68,32,0,
.db  $30,
.db  $00,
.db  $08,
.db  $00,
.db  $01,
.db  $00,
.db  $00,
.dw  $00,
.dw  $00,
.dd  $00,
.dw @SNES_ERROR,
.dw @SNES_ERROR,
.dw @SNES_ERROR,
.dw @VBlank,
.dw  $00,
.dw @SNES_IRQHV,
.dd  $00,
.dw @SNES_ERROR,
.dw  $00,
.dw @SNES_ERROR,
.dw @VBlank,
.dw @_start,
.dw @SNES_IRQHV,
.org 65536
.rodata 8552448
SNDK_LOADR:
SNDK_LOAD:
.dd @DATA_FONT_SNDK_S,
.dw  $6000,0,
.dd @DATA_FONT_SNDK_S,
.dw  $6000,0,
.dd @DATA_FONT_SNDK_S,
.dw  $4000,0,
SNDK_LIST:
LIST_SPR2:
ENNEMY_ANIM:
SNDK_MAPLIST:
.org 98304
.rodata 8617984
MUSIC_TRACK1:
.incbin ssb_opening.vgmx
.db  $00,
.org 131072
.rodata 8683520
MUSIC_BRR1:
.incbin SAMPLE_PACK.brr
.db  $FF,
.org 163840
.rodata 8749056
.org 196608
.rodata 8814592
.org  $40000
