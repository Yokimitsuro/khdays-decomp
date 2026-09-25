/* MobiClip audio, coding 1: dequantise and inverse-transform one channel's 128 coefficients into
 * 256 signed 16-bit PCM samples (func_ov024_02085c8c's first decoder).
 *
 * The `b` at +0 jumps over the inline subroutines to the entry at +0x810. A header u16 >> 9 gives
 * the first live coefficient (127 means the whole block is coded); the coefficients are scaled by
 * their running index (2, 3, 4, ... -- the DC term is not scaled) and shifted down by 4, the
 * subroutine at +0x10 clears the 512-byte coefficient block (stmia of four zero registers x32), and
 * the transform itself is add/sub/shift butterflies with no multiplies. The output stage saturates
 * to [-32768, 32767] and stores halfwords with the per-channel stride at ctx+0x14f4.
 *
 * Hand-written ARM from the MobiClip library (Actimagine), not compiled C: the routines return with
 * `mov pc, lr`, constants and padding words sit between them, and r4-r11 carry data across the
 * inner calls. KH Days' streams use IMA ADPCM (coding 3), so this decoder never runs in the shipped
 * game. Code and data follow the control flow; the three relocated call targets are global labels
 * (mobiclip_02086d38, mobiclip_02086d88, mobiclip_02087058) because the ROM relocates those calls. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global func_ov024_02086958
    .type func_ov024_02086958, %function
func_ov024_02086958:
    b .L_02087168
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
.L_02086968:
    mov r6, #0x20
    add r7, r3, #0x200
    mov r8, #0
    mov sb, #0
    mov sl, #0
    mov fp, #0
.L_02086980:
    stm r7!, {r8, sb, sl, fp}
    subs r6, r6, #1
    bne .L_02086980
    mov pc, lr
    .word 0x00000000
    .word 0x00000000
.L_02086998:
    push {r1, r3, r4}
    add r3, r3, #0x200
    rsb ip, r6, #0x7f
    add r4, r4, ip, lsl #2
    ldr r2, [r4], #4
    mov r1, #2
    asr r2, r2, #4
    str r2, [r3], #4
    ldr r2, [r4], #4
    ldr r7, [r4], #4
    ldr r8, [r4], #4
    ldr sb, [r4], #4
    ldr sl, [r4], #4
    ldr fp, [r4], #4
    mul ip, r2, r1
    add r1, r1, #1
    asr ip, ip, #4
    str ip, [r3], #4
    mul ip, r7, r1
    add r1, r1, #1
    asr ip, ip, #4
    str ip, [r3], #4
    mul ip, r8, r1
    add r1, r1, #1
    asr ip, ip, #4
    str ip, [r3], #4
    mul ip, sb, r1
    add r1, r1, #1
    asr ip, ip, #4
    str ip, [r3], #4
    mul ip, sl, r1
    add r1, r1, #1
    asr ip, ip, #4
    str ip, [r3], #4
    mul ip, fp, r1
    asr ip, ip, #4
    str ip, [r3], #4
    mov ip, #0x72
.L_02086a30:
    ldm r4!, {r6, r7, r8, sb, sl, fp}
    asr r6, r6, #1
    asr r7, r7, #1
    asr r8, r8, #1
    asr sb, sb, #1
    asr sl, sl, #1
    asr fp, fp, #1
    stm r3!, {r6, r7, r8, sb, sl, fp}
    subs ip, ip, #6
    bne .L_02086a30
    ldr r2, [r4], #4
    ldr r7, [r4], #4
    ldr r8, [r4], #4
    ldr sb, [r4], #4
    ldr sl, [r4], #4
    ldr fp, [r4], #4
    mul ip, r2, r1
    sub r1, r1, #1
    asr ip, ip, #4
    str ip, [r3], #4
    mul ip, r7, r1
    sub r1, r1, #1
    asr ip, ip, #4
    str ip, [r3], #4
    mul ip, r8, r1
    sub r1, r1, #1
    asr ip, ip, #4
    str ip, [r3], #4
    mul ip, sb, r1
    sub r1, r1, #1
    asr ip, ip, #4
    str ip, [r3], #4
    mul ip, sl, r1
    sub r1, r1, #1
    asr ip, ip, #4
    str ip, [r3], #4
    mul ip, fp, r1
    ldr r2, [r4], #4
    asr ip, ip, #4
    str ip, [r3], #4
    asr r2, r2, #4
    str r2, [r3], #4
    pop {r1, r3, r4}
    mov pc, lr
    .word 0x00000000
    .word 0x00000000
.L_02086ae8:
    add r1, r3, #0x200
    add r1, r1, r7, lsl #2
    rsb r7, r6, #0
    lsl r6, r6, #1
    sub r7, r7, r6
.L_02086afc:
    ldrh r5, [r0], #2
    mov fp, #0xe
.L_02086b04:
    ldr sl, [r1]
    lsr r2, r5, fp
    and r2, r2, #3
    mla r2, r6, r2, r7
    add sl, sl, r2
    str sl, [r1], sb
    subs fp, fp, #2
    bge .L_02086b04
    subs r8, r8, #1
    bne .L_02086afc
    pop {r1, pc}
    .word 0x00000000
    .word 0x00000000
.L_02086b38:
    add r1, r3, #0x200
    add r1, r1, r7, lsl #2
    rsb r7, r6, #0
    lsl r6, r6, #1
    sub r7, r7, r6, lsl #1
    sub r7, r7, r6
    mov sb, #0
    mov r8, #8
.L_02086b58:
    ldrh r5, [r0], #2
    mov fp, #0xd
.L_02086b60:
    ldr sl, [r1]
    lsr r2, r5, fp
    and r2, r2, #7
    mla r2, r6, r2, r7
    add sl, sl, r2
    str sl, [r1], #0xc
    subs fp, fp, #3
    bge .L_02086b60
    and r5, r5, #1
    orr sb, r5, sb, lsl #1
    subs r8, r8, #1
    bne .L_02086b58
    ldr sl, [r1]
    lsr r2, sb, #5
    and r2, r2, #7
    mla r2, r6, r2, r7
    add sl, sl, r2
    str sl, [r1], #0xc
    ldr sl, [r1]
    lsr r2, sb, #2
    and r2, r2, #7
    mla r2, r6, r2, r7
    add sl, sl, r2
    str sl, [r1]
    pop {r1, pc}
    .word 0x00000000
.L_02086bc8:
    push {r3, r4, lr}
    ldm r2, {r5, r6, r7, r8, sb, sl, fp, ip}
    add r3, r1, #0x70
    ldrb r4, [r3]
    add r2, r1, #0x8c0
    add r4, r2, r4, lsl #4
    bl mobiclip_02086d38
    add r3, r1, #0x71
    ldrb r4, [r3]
    add r2, r1, #0xcc0
    add r4, r2, r4, lsl #4
    bl mobiclip_02086d38
    add r3, r1, #0x72
    ldrb r4, [r3]
    add r2, r1, #0x10c0
    add r4, r2, r4, lsl #4
    bl mobiclip_02086d38
    add r2, r1, #8
    stm r2, {r5, r6, r7, r8, sb, sl, fp, ip}
    mul r3, r5, r6
    add r5, r5, r3, asr #15
    mul r3, r6, r7
    mul r4, r5, r7
    add r5, r5, r3, asr #15
    add r6, r6, r4, asr #15
    mul r3, r7, r8
    mul r4, r5, r8
    add r5, r5, r3, asr #15
    mul r3, r6, r8
    add r7, r7, r4, asr #15
    add r6, r6, r3, asr #15
    mul r3, r8, sb
    mul r4, r5, sb
    add r5, r5, r3, asr #15
    add r8, r8, r4, asr #15
    mul r3, r7, sb
    mul r4, r6, sb
    add r6, r6, r3, asr #15
    add r7, r7, r4, asr #15
    mul r3, sb, sl
    mul r4, r5, sl
    add r5, r5, r3, asr #15
    add sb, sb, r4, asr #15
    mul r3, r8, sl
    mul r4, r6, sl
    add r6, r6, r3, asr #15
    mul r3, r7, sl
    add r8, r8, r4, asr #15
    add r7, r7, r3, asr #15
    mul r3, sl, fp
    mul r4, r5, fp
    add r5, r5, r3, asr #15
    add sl, sl, r4, asr #15
    mul r3, sb, fp
    mul r4, r6, fp
    add r6, r6, r3, asr #15
    add sb, sb, r4, asr #15
    mul r3, r8, fp
    mul r4, r7, fp
    add r7, r7, r3, asr #15
    add r8, r8, r4, asr #15
    mul r3, fp, ip
    mul r4, r5, ip
    add r5, r5, r3, asr #15
    add fp, fp, r4, asr #15
    mul r3, sl, ip
    mul r4, r6, ip
    add r6, r6, r3, asr #15
    add sl, sl, r4, asr #15
    mul r3, sb, ip
    mul r4, r7, ip
    add r7, r7, r3, asr #15
    mul r3, r8, ip
    add sb, sb, r4, asr #15
    add r8, r8, r3, asr #15
    asr r5, r5, #1
    rsb r5, r5, #0
    asr r6, r6, #1
    rsb r6, r6, #0
    asr r7, r7, #1
    rsb r7, r7, #0
    asr r8, r8, #1
    rsb r8, r8, #0
    asr sb, sb, #1
    rsb sb, sb, #0
    asr sl, sl, #1
    rsb sl, sl, #0
    asr fp, fp, #1
    rsb fp, fp, #0
    asr ip, ip, #1
    rsb ip, ip, #0
    pop {r3, r4, pc}
    .global mobiclip_02086d38
mobiclip_02086d38:
.L_02086d38:
    ldrsh r0, [r4], #2
    ldrsh r3, [r4], #2
    ldrsh r2, [r4], #2
    add r5, r5, r0
    add r6, r6, r3
    add r7, r7, r2
    ldrsh r0, [r4], #2
    ldrsh r3, [r4], #2
    ldrsh r2, [r4], #2
    add r8, r8, r0
    add sb, sb, r3
    add sl, sl, r2
    ldrsh r0, [r4], #2
    ldrsh r3, [r4], #2
    add fp, fp, r0
    add ip, ip, r3
    mov pc, lr
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
    .global mobiclip_02086d88
mobiclip_02086d88:
.L_02086d88:
    push {r1, r3, r4, lr}
    add lr, r1, #0x78
    ldr r1, [r1, #0x74]
.L_02086d94:
    str r2, [sp, #-4]!
    ldr r4, [r0], #4
    ldr r3, [lr, #0x1c]
    lsl r4, r4, #0xe
    ldr r2, [lr, #0x18]
    mla r4, r5, r3, r4
    ldr r3, [lr, #0x14]
    mla r4, r6, r2, r4
    ldr r2, [lr, #0x10]
    mla r4, r7, r3, r4
    ldr r3, [lr, #0xc]
    mla r4, r8, r2, r4
    ldr r2, [lr, #8]
    mla r4, sb, r3, r4
    ldr r3, [lr, #4]
    mla r4, sl, r2, r4
    ldr r2, [lr]
    mla r4, fp, r3, r4
    mla r4, ip, r2, r4
    asr r4, r4, #0xe
    str r4, [lr]
    str r4, [r1], #4
    ldr r4, [r0], #4
    ldr r3, [lr]
    lsl r4, r4, #0xe
    ldr r2, [lr, #0x1c]
    mla r4, r5, r3, r4
    ldr r3, [lr, #0x18]
    mla r4, r6, r2, r4
    ldr r2, [lr, #0x14]
    mla r4, r7, r3, r4
    ldr r3, [lr, #0x10]
    mla r4, r8, r2, r4
    ldr r2, [lr, #0xc]
    mla r4, sb, r3, r4
    ldr r3, [lr, #8]
    mla r4, sl, r2, r4
    ldr r2, [lr, #4]
    mla r4, fp, r3, r4
    mla r4, ip, r2, r4
    asr r4, r4, #0xe
    str r4, [lr, #4]
    str r4, [r1], #4
    ldr r4, [r0], #4
    ldr r3, [lr, #4]
    lsl r4, r4, #0xe
    ldr r2, [lr]
    mla r4, r5, r3, r4
    ldr r3, [lr, #0x1c]
    mla r4, r6, r2, r4
    ldr r2, [lr, #0x18]
    mla r4, r7, r3, r4
    ldr r3, [lr, #0x14]
    mla r4, r8, r2, r4
    ldr r2, [lr, #0x10]
    mla r4, sb, r3, r4
    ldr r3, [lr, #0xc]
    mla r4, sl, r2, r4
    ldr r2, [lr, #8]
    mla r4, fp, r3, r4
    mla r4, ip, r2, r4
    asr r4, r4, #0xe
    str r4, [lr, #8]
    str r4, [r1], #4
    ldr r4, [r0], #4
    ldr r3, [lr, #8]
    lsl r4, r4, #0xe
    ldr r2, [lr, #4]
    mla r4, r5, r3, r4
    ldr r3, [lr]
    mla r4, r6, r2, r4
    ldr r2, [lr, #0x1c]
    mla r4, r7, r3, r4
    ldr r3, [lr, #0x18]
    mla r4, r8, r2, r4
    ldr r2, [lr, #0x14]
    mla r4, sb, r3, r4
    ldr r3, [lr, #0x10]
    mla r4, sl, r2, r4
    ldr r2, [lr, #0xc]
    mla r4, fp, r3, r4
    mla r4, ip, r2, r4
    asr r4, r4, #0xe
    str r4, [lr, #0xc]
    str r4, [r1], #4
    ldr r4, [r0], #4
    ldr r3, [lr, #0xc]
    lsl r4, r4, #0xe
    ldr r2, [lr, #8]
    mla r4, r5, r3, r4
    ldr r3, [lr, #4]
    mla r4, r6, r2, r4
    ldr r2, [lr]
    mla r4, r7, r3, r4
    ldr r3, [lr, #0x1c]
    mla r4, r8, r2, r4
    ldr r2, [lr, #0x18]
    mla r4, sb, r3, r4
    ldr r3, [lr, #0x14]
    mla r4, sl, r2, r4
    ldr r2, [lr, #0x10]
    mla r4, fp, r3, r4
    mla r4, ip, r2, r4
    asr r4, r4, #0xe
    str r4, [lr, #0x10]
    str r4, [r1], #4
    ldr r4, [r0], #4
    ldr r3, [lr, #0x10]
    lsl r4, r4, #0xe
    ldr r2, [lr, #0xc]
    mla r4, r5, r3, r4
    ldr r3, [lr, #8]
    mla r4, r6, r2, r4
    ldr r2, [lr, #4]
    mla r4, r7, r3, r4
    ldr r3, [lr]
    mla r4, r8, r2, r4
    ldr r2, [lr, #0x1c]
    mla r4, sb, r3, r4
    ldr r3, [lr, #0x18]
    mla r4, sl, r2, r4
    ldr r2, [lr, #0x14]
    mla r4, fp, r3, r4
    mla r4, ip, r2, r4
    asr r4, r4, #0xe
    str r4, [lr, #0x14]
    str r4, [r1], #4
    ldr r4, [r0], #4
    ldr r3, [lr, #0x14]
    lsl r4, r4, #0xe
    ldr r2, [lr, #0x10]
    mla r4, r5, r3, r4
    ldr r3, [lr, #0xc]
    mla r4, r6, r2, r4
    ldr r2, [lr, #8]
    mla r4, r7, r3, r4
    ldr r3, [lr, #4]
    mla r4, r8, r2, r4
    ldr r2, [lr]
    mla r4, sb, r3, r4
    ldr r3, [lr, #0x1c]
    mla r4, sl, r2, r4
    ldr r2, [lr, #0x18]
    mla r4, fp, r3, r4
    mla r4, ip, r2, r4
    asr r4, r4, #0xe
    str r4, [lr, #0x18]
    str r4, [r1], #4
    ldr r4, [r0], #4
    ldr r3, [lr, #0x18]
    lsl r4, r4, #0xe
    ldr r2, [lr, #0x14]
    mla r4, r5, r3, r4
    ldr r3, [lr, #0x10]
    mla r4, r6, r2, r4
    ldr r2, [lr, #0xc]
    mla r4, r7, r3, r4
    ldr r3, [lr, #8]
    mla r4, r8, r2, r4
    ldr r2, [lr, #4]
    mla r4, sb, r3, r4
    ldr r3, [lr]
    mla r4, sl, r2, r4
    ldr r2, [lr, #0x1c]
    mla r4, fp, r3, r4
    mla r4, ip, r2, r4
    asr r4, r4, #0xe
    str r4, [lr, #0x1c]
    str r4, [r1], #4
    pop {r2}
    subs r2, r2, #8
    bne .L_02086d94
    ldr r4, [sp]
    str r1, [r4, #0x74]
    pop {r1, r3, r4, pc}
    .word 0x00000000
    .word 0x00000000
    .global mobiclip_02087058
mobiclip_02087058:
.L_02087058:
    push {r0, lr}
    ldr r0, [r2], #4
    ldr lr, [r2], #4
    add r5, r5, r0
    add r6, r6, lr
    ldr r0, [r2], #4
    ldr lr, [r2], #4
    add r7, r7, r0
    add r8, r8, lr
    ldr r0, [r2], #4
    ldr lr, [r2], #4
    add sb, sb, r0
    add sl, sl, lr
    ldr r0, [r2], #4
    ldr lr, [r2], #4
    add fp, fp, r0
    add ip, ip, lr
    asr r5, r5, #1
    asr r6, r6, #1
    asr r7, r7, #1
    asr r8, r8, #1
    asr sb, sb, #1
    asr sl, sl, #1
    asr fp, fp, #1
    asr ip, ip, #1
    pop {r0, pc}
    .word 0x00000000
    .word 0x00000000
.L_020870c8:
    push {r1, r4, lr}
    ldr r2, [r1, #0x6c]
    cmp r2, #1
    add r0, r3, #0x200
    str r4, [r1, #0x74]
    addne r3, r1, #0x28
    addne r4, r3, #0x20
    addeq r4, r1, #0x28
    addeq r3, r4, #0x20
    stm r3, {r5, r6, r7, r8, sb, sl, fp, ip}
    mov r2, r4
    bl mobiclip_02087058
    push {r5, r6, r7, r8, sb, sl, fp, ip}
    mov r2, r4
    bl mobiclip_02087058
    mov r2, #0x20
    bl mobiclip_02086d88
    pop {r5, r6, r7, r8, sb, sl, fp, ip}
    mov r2, #0x20
    bl mobiclip_02086d88
    mov r2, r3
    bl mobiclip_02087058
    mov r2, #0x20
    bl mobiclip_02086d88
    ldm r3, {r5, r6, r7, r8, sb, sl, fp, ip}
    mov r2, #0x20
    bl mobiclip_02086d88
    pop {r1, r4, pc}
.L_02087138:
    add r8, r1, #0x8c0
    ldr r7, [r8, #0xc30]
    mov sb, #1
    str r7, [r1, #0x68]
    mov r7, #8
    str sb, [r1, #0x6c]
    add r8, r1, #0x78
    mov sb, #0
.L_02087158:
    str sb, [r8], #4
    subs r7, r7, #1
    bne .L_02087158
    mov pc, lr
.L_02087168:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
    mov r1, r0
    ldr r0, [r0]
    ldrh r5, [r0], #2
    lsr r6, r5, #9
    cmp r6, #0x7f
    bleq .L_02087278
    blne .L_020872b8
    ldr r7, [r1, #0x6c]
    eor r7, r7, #1
    str r7, [r1, #0x6c]
    add r3, r1, #0x1000
    ldr r2, [r1, #4]
    mov r0, #0x80
    ldr r5, [pc, #0x168]
    ldr r6, [pc, #0x168]
    ldr r3, [r3, #0x4f4]
.L_020871ac:
    ldr r7, [r4], #4
    cmp r7, r5
    movgt r7, r5
    cmp r7, r6
    movlt r7, r6
    strh r7, [r2], r3
    subs r0, r0, #1
    bne .L_020871ac
    ldrb r0, [r1, #0x73]
    add r2, pc, #0xe
    ldrb r0, [r2, r0]
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
    bx lr
    .word 0x10040c05
    .word 0x0e141403
    .word 0x00000a0c
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
.L_020871f8:
    push {r1, lr}
    add ip, r1, #0x70
    lsr r6, r5, #6
    and r6, r6, #7
    and r5, r5, #0x3f
    strb r5, [ip], #1
    ldrh r5, [r0], #2
    add r8, r1, #0x14c0
    lsr r7, r5, #0xe
    and r7, r7, #3
    add r6, r8, r6, lsl #1
    ldrsh r8, [r6]
    ldr r6, [r1, #0x68]
    lsr fp, r5, #0xc
    mul r6, r8, r6
    lsr sl, r5, #6
    asr r6, r6, #0xd
    str r6, [r1, #0x68]
    and sl, sl, #0x3f
    strb sl, [ip], #1
    and r5, r5, #0x3f
    strb r5, [ip]
    ands fp, fp, #3
    strb fp, [r1, #0x73]
    beq .L_02086b38
    sub sl, pc, #0x86
    add sl, sl, fp, lsl #1
    ldrb r8, [sl]
    ldrb sb, [sl, #1]
    b .L_02086ae8
    .word 0x00000000
    .word 0x00000000
.L_02087278:
    push {r1, lr}
    bl .L_02087138
    add r4, r1, #0xc0
    add r3, r4, #0x400
    bl .L_02086968
    bl .L_020871f8
    add r2, r1, #0x8c0
    add r2, r2, #0xc10
    bl .L_02086bc8
    add r2, r1, #0x48
    stm r2, {r5, r6, r7, r8, sb, sl, fp, ip}
    str r4, [r1, #0x74]
    add r0, r3, #0x200
    mov r2, #0x80
    bl .L_02086d88
    pop {r1, pc}
.L_020872b8:
    push {r1, lr}
    mov r7, #0x400
    ldr r2, [r1, #0x6c]
    add r8, r1, #0xc0
    mla r3, r2, r7, r8
    eor r2, r2, #1
    mla r4, r2, r7, r8
    mov r8, r3
    add r7, r4, #0x200
    mov r2, #0x20
.L_020872e0:
    ldm r7!, {sb, sl, fp, ip}
    stm r8!, {sb, sl, fp, ip}
    subs r2, r2, #1
    bne .L_020872e0
    cmp r6, #0x7e
    bleq .L_02086968
    blne .L_02086998
    bl .L_020871f8
    add r2, r1, #8
    bl .L_02086bc8
    bl .L_020870c8
    pop {r1, pc}
    .word 0x00007fff
    .word 0xffff8000
    .size func_ov024_02086958, .-func_ov024_02086958
