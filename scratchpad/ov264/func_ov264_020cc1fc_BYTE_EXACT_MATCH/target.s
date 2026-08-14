.text
	.syntax unified
	.arm
	.global func_ov264_020cc1fc
func_ov264_020cc1fc:
	push {r3, r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x4c
	ldr r5, _020CC570
	mov r4, r0
	ldm r5!, {r0, r1, r2, r3}
	add r6, sp, #0x38
	stm r6!, {r0, r1, r2, r3}
	ldr r5, [r5]
	ldr r8, _020CC574
	str r5, [r6]
	ldr r3, _020CC578
	ldr r1, _020CC57C
	ldr r0, _020CC580
	str r1, [r4, #8]
	str r0, [r4, #0xc]
	mvn ip, #5
	ldr r7, _020CC584
	add r0, r8, #0x17
	add r2, r0, #0x3200
	add r5, r3, #0x97
	add r0, r5, #0x2500
	str r7, [r4, #0x1c]
	ldr r6, _020CC588
	add r1, ip, #0xc3
	str r6, [r4, #0x30]
	ldr r5, _020CC58C
	add r1, r1, #0x2c00
	str r5, [r4, #0x34]
	ldr r6, _020CC590
	ldr r5, _020CC594
	str r6, [r4, #0x1d0]
	str r5, [r4, #0x1dc]
	ldr r6, _020CC598
	ldr r5, _020CC59C
	str r6, [r4, #0x1e0]
	str r5, [r4, #0x1e4]
	mov r6, #0x1400
	str r6, [r4, #0x70]
	mov r5, #0
	str r5, [r4, #0x64]
	str r6, [r4, #0x68]
	str r8, [sp, #0x20]
	add r7, sp, #0x20
	str ip, [sp, #0x24]
	str r5, [r4, #0x6c]
	add r6, r4, #0x1fc
	str r3, [sp, #0x28]
	str r2, [sp, #0x2c]
	str r1, [sp, #0x30]
	str r0, [sp, #0x34]
	ldm r7!, {r0, r1, r2, r3}
	stm r6!, {r0, r1, r2, r3}
	ldm r7, {r0, r1}
	stm r6, {r0, r1}
	mov r0, #1
	strb r0, [r4, #0x1c9]
	ldrh r3, [r4, #0x60]
	mov r1, r5
	add r2, r4, #0x100
	bic r5, r3, #0xff00
	lsl r3, r3, #0x10
	lsr r3, r3, #0x18
	orr r3, r3, #0x20
	lsl r3, r3, #0x18
	orr r3, r5, r3, lsr #16
	strh r3, [r4, #0x60]
	ldrh r3, [r2, #0xae]
	mov r0, r4
	orr r3, r3, #8
	strh r3, [r2, #0xae]
	bl func_ov107_020c9440
	bl func_0203b898
	ldr r1, _020CC5A0
	str r0, [r4, #0x384]
	str r1, [r0, #0x74]
	ldr r0, [r4, #0x384]
	str r4, [r0, #0x84]
	ldr r0, [r4, #0x9c]
	ldr r1, [r4, #0x384]
	bl func_0203bfb4
	mov r0, r4
	mov r1, #1
	bl func_ov107_020c9440
	ldr r1, [r4, #0x384]
	mov r2, r0
	ldr r1, [r1, #0x88]
	add r0, r4, #0x388
	mov r3, #0xc
	bl func_0202a388
	ldr r0, [r4, #0x384]
	add r1, r4, #0x388
	bl func_0203b9ac
	ldr r0, [r4, #0x384]
	ldr r1, _020CC5A4
	bl func_0203bdfc
	str r0, [r4, #0x438]
	mov r0, r4
	mov r1, #0xa
	bl func_ov107_020c9440
	bl func_0203b898
	ldr r1, _020CC5A8
	str r0, [r4, #0x420]
	str r1, [r0, #0x6c]
	ldr r0, [r4, #0x420]
	mov r1, #0
	str r4, [r0, #0x84]
	ldr r0, [r4, #0x420]
	bl func_0203c7ac
	ldr r0, [r4, #0x420]
	ldr r1, _020CC5AC
	bl func_0203bdfc
	str r0, [r4, #0x434]
	mov r1, #0
	mov r0, #0x1400
	str r0, [sp, #8]
	str r1, [sp, #4]
	str r1, [sp, #0xc]
	mov r0, #0xc00
	str r0, [sp]
	mov r0, r4
	mov r2, #2
	add r3, sp, #4
	bl func_ov107_020c92b0
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #0xc]
	sub r0, r0, #0x1400
	str r0, [sp, #8]
	ldr r1, _020CC5B0
	mov r0, r4
	str r1, [sp]
	mov r1, #2
	mov r2, #3
	add r3, sp, #4
	bl func_ov107_020c92b0
	ldr r1, _020CC5B4
	mov r0, r4
	str r1, [sp]
	mov r1, #1
	mov r2, #2
	mov r3, #0
	bl func_ov107_020c92b0
	lsr r7, r8, #0x17
	ldr r8, _020CC5B8
	mov r6, #0
	add r5, sp, #0x38
_020CC444:
	cmp r6, #0
	bgt _020CC478
	bl OS_IsThreadAvailable_0x020c9848
	ldr r0, [r0, #0x88]
	ldr r1, [r5, r6, lsl #2]
	add r0, r0, #0x8000
	and r0, r0, r8
	lsl r0, r0, #7
	and r1, r1, r7
	orr r0, r0, #0x80000000
	orr r0, r1, r0
	bl func_0203b898
	b _020CC488
_020CC478:
	ldr r1, [r5, r6, lsl #2]
	mov r0, r4
	bl func_ov107_020c9440
	bl func_0203b898
_020CC488:
	add r1, r4, r6, lsl #3
	str r0, [r1, #0x440]
	mov r1, r0
	mov r0, r4
	bl func_ov107_020c9074
	add r0, r4, r6, lsl #3
	ldr r1, [r0, #0x440]
	add r6, r6, #1
	ldr r0, [r1, #0x5c]
	cmp r6, #5
	orr r0, r0, #2
	str r0, [r1, #0x5c]
	blt _020CC444
	mov r0, r4
	mov r1, #0xe
	bl func_ov107_020c9440
	mov r1, #0x22
	bl func_0203c1b0
	str r0, [r4, #0x3c4]
	mov r1, r0
	mov r0, r4
	bl func_ov107_020c9074
	ldr r2, [r4, #0x3c4]
	mov r0, r4
	ldr r1, [r2, #0x5c]
	orr r1, r1, #2
	str r1, [r2, #0x5c]
	bl func_ov264_020ce9fc
	str r0, [r4, #0x3c0]
	add r0, r4, #0x64
	add r6, sp, #0x10
	ldm r0, {r0, r1, r2, r3}
	stm r6, {r0, r1, r2, r3}
	ldr r5, _020CC5BC
	ldm r5, {r0, r1, r2}
	stm r6, {r0, r1, r2}
	add r0, r4, #0x22c
	mov r1, #0x10
	mov r2, #0x64
	bl func_01fffca8
	str r0, [r4, #0x3ac]
	mov r0, r6
	bl func_ov107_020c319c
	ldr r2, [r4, #0x3ac]
	mov r1, #4
	str r0, [r2]
	add r0, r4, #0x144
	mov r2, #0x64
	bl func_01fffca8
	mov r5, r0
	mov r0, r6
	bl func_ov107_020c319c
	str r0, [r5]
	str r0, [r4, #0x3b0]
	ldr r0, _020CC5C0
	bl func_0203355c
	add sp, sp, #0x4c
	pop {r3, r4, r5, r6, r7, r8, pc}
	.align 2, 0
_020CC570: .word data_ov264_020cebc4
_020CC574: .word 0xFFFFE6F5
_020CC578: .word 0xFFFFE03C
_020CC57C: .word func_ov264_020cc5c4
_020CC580: .word func_ov264_020cc61c
_020CC584: .word func_ov264_020cc6a8
_020CC588: .word func_ov264_020cca58
_020CC58C: .word func_ov264_020cc8e4
_020CC590: .word func_ov264_020ccab4
_020CC594: .word func_ov264_020cc9e0
_020CC598: .word func_ov264_020ccde8
_020CC59C: .word func_ov264_020cce14
_020CC5A0: .word func_ov264_020cbfc8
_020CC5A4: .word data_ov264_020cec2c
_020CC5A8: .word func_ov264_020cc09c
_020CC5AC: .word data_ov264_020cec38
_020CC5B0: .word 0x0000099A
_020CC5B4: .word 0x00000CCD
_020CC5B8: .word 0x00FFFFFC
_020CC5BC: .word data_02041dc8
_020CC5C0: .word 0x0000015D