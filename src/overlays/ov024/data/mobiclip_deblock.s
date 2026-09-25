/* MobiClip deblocking post-filter, ov024 .rodata 0x02092e60-0x020933ac. */
/* Hand-written ARM that the player calls in place (func_ov024_02085ab8, display modes 1/2; KH Days */
/* always uses mode 0). Semantic model and replay: tools/mobiclip_deblock.py. Request block: */
/* {src luma, src chroma, dst luma, dst chroma, width, height, quantiser, clip table, vertical-only}. */
/* Planes use a 256-byte stride; chroma rows hold Co at +0 and Cg at +0x80. */
    .syntax unified
    .arch armv5te
    .section .rodata,"a",%progbits
    .arm
    .align 2
    .global func_ov024_02092e60_unk
    .type func_ov024_02092e60_unk, %object
func_ov024_02092e60_unk:
    /* MobiClip_DeblockFrame */
MobiClip_Code_02092E60:
    push {r4, r5, r6, r7, r8, sb, lr}
MobiClip_Code_02092E64:
    sub sp, sp, #0x18
MobiClip_Code_02092E68:
    mov r4, r0
MobiClip_Code_02092E6C:
    ldr r5, [r4, #0x18]
MobiClip_Code_02092E70:
    add r6, pc, #0xc0
MobiClip_Code_02092E74:
    ldrb r6, [r6, r5]
MobiClip_Code_02092E78:
    add r7, pc, #0xdd
MobiClip_Code_02092E7C:
    ldrb r7, [r7, r5]
MobiClip_Code_02092E80:
    orr r6, r6, r7, lsl #8
MobiClip_Code_02092E84:
    str r6, [sp, #0x10]
MobiClip_Code_02092E88:
    ldr r5, [r4]
MobiClip_Code_02092E8C:
    ldr r6, [r4, #8]
MobiClip_Code_02092E90:
    ldr r7, [r4, #0x10]
MobiClip_Code_02092E94:
    ldr r8, [r4, #0x14]
MobiClip_Code_02092E98:
    ldr sb, [r4, #0x1c]
MobiClip_Code_02092E9C:
    str r5, [sp]
MobiClip_Code_02092EA0:
    str r6, [sp, #4]
MobiClip_Code_02092EA4:
    str r7, [sp, #8]
MobiClip_Code_02092EA8:
    str r8, [sp, #0xc]
MobiClip_Code_02092EAC:
    add sb, sb, #0x40
MobiClip_Code_02092EB0:
    str sb, [sp, #0x14]
MobiClip_Code_02092EB4:
    mov r0, sp
MobiClip_Code_02092EB8:
    bl MobiClip_Code_02092F90
MobiClip_Code_02092EBC:
    ldr r0, [r4, #0x20]
MobiClip_Code_02092EC0:
    cmp r0, #1
MobiClip_Code_02092EC4:
    movne r0, sp
MobiClip_Code_02092EC8:
    blne MobiClip_Code_020930C8
MobiClip_Code_02092ECC:
    ldr r5, [r4, #4]
MobiClip_Code_02092ED0:
    ldr r6, [r4, #0xc]
MobiClip_Code_02092ED4:
    ldr r7, [r4, #0x10]
MobiClip_Code_02092ED8:
    ldr r8, [r4, #0x14]
MobiClip_Code_02092EDC:
    str r5, [sp]
MobiClip_Code_02092EE0:
    str r6, [sp, #4]
MobiClip_Code_02092EE4:
    asr r7, r7, #1
MobiClip_Code_02092EE8:
    asr r8, r8, #1
MobiClip_Code_02092EEC:
    str r7, [sp, #8]
MobiClip_Code_02092EF0:
    str r8, [sp, #0xc]
MobiClip_Code_02092EF4:
    mov r0, sp
MobiClip_Code_02092EF8:
    bl MobiClip_Code_020931BC
MobiClip_Code_02092EFC:
    ldr r0, [r4, #0x20]
MobiClip_Code_02092F00:
    cmp r0, #1
MobiClip_Code_02092F04:
    movne r0, sp
MobiClip_Code_02092F08:
    blne MobiClip_Code_020932C4
MobiClip_Code_02092F0C:
    ldr r5, [r4, #4]
MobiClip_Code_02092F10:
    ldr r6, [r4, #0xc]
MobiClip_Code_02092F14:
    add r5, r5, #0x80
MobiClip_Code_02092F18:
    add r6, r6, #0x80
MobiClip_Code_02092F1C:
    str r5, [sp]
MobiClip_Code_02092F20:
    str r6, [sp, #4]
MobiClip_Code_02092F24:
    mov r0, sp
MobiClip_Code_02092F28:
    bl MobiClip_Code_020931BC
MobiClip_Code_02092F2C:
    ldr r0, [r4, #0x20]
MobiClip_Code_02092F30:
    cmp r0, #1
MobiClip_Code_02092F34:
    movne r0, sp
MobiClip_Code_02092F38:
    blne MobiClip_Code_020932C4
MobiClip_Code_02092F3C:
    add sp, sp, #0x18
MobiClip_Code_02092F40:
    pop {r4, r5, r6, r7, r8, sb, pc}
    /* |p0 - q0| threshold, qp 12..48 (read from base - 12) */
    .global gMobiClipDeblockAlpha
    .type gMobiClipDeblockAlpha, %object
gMobiClipDeblockAlpha:
    .byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x05, 0x05, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0d, 0x0f, 0x11
    .byte 0x13, 0x16, 0x19, 0x1d, 0x21, 0x26, 0x2c, 0x32, 0x39, 0x42, 0x4b, 0x56, 0x62, 0x70, 0x80, 0x93
    .byte 0xa8, 0xc0, 0xdb, 0xfb, 0xff
    /* |p1 - p0| and |q1 - q0| threshold, qp 12..48 (read from base - 12) */
    .global gMobiClipDeblockBeta
    .type gMobiClipDeblockBeta, %object
gMobiClipDeblockBeta:
    .byte 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x07
    .byte 0x07, 0x08, 0x08, 0x09, 0x09, 0x0a, 0x0b, 0x0b, 0x0c, 0x0c, 0x0d, 0x0d, 0x0e, 0x0e, 0x0f, 0x0f
    .byte 0x10, 0x10, 0x11, 0x11, 0x12
    /* word-alignment fill before the luma vertical-edge routine */
    .global gMobiClipDeblockPad
    .type gMobiClipDeblockPad, %object
gMobiClipDeblockPad:
    .byte 0x00, 0x00
    /* MobiClip_DeblockLumaVerticalEdges */
MobiClip_Code_02092F90:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_02092F94:
    ldr lr, [r0, #0x10]
MobiClip_Code_02092F98:
    ldr ip, [r0, #0x14]
MobiClip_Code_02092F9C:
    ldr r1, [r0, #4]
MobiClip_Code_02092FA0:
    ldr fp, [r0]
MobiClip_Code_02092FA4:
    ldr r3, [r0, #0xc]
MobiClip_Code_02092FA8:
    ldr r2, [fp], #4
MobiClip_Code_02092FAC:
    ldr sl, [r0, #8]
MobiClip_Code_02092FB0:
    str r3, [sp, #-4]!
MobiClip_Code_02092FB4:
    str r2, [r1], #4
MobiClip_Code_02092FB8:
    sub sl, sl, #8
MobiClip_Code_02092FBC:
    str sl, [sp, #-4]!
MobiClip_Code_02092FC0:
    ldrb r2, [fp], #1
MobiClip_Code_02092FC4:
    ldrb r3, [fp], #1
MobiClip_Code_02092FC8:
    ldrb r4, [fp], #1
MobiClip_Code_02092FCC:
    ldrb r5, [fp], #1
MobiClip_Code_02092FD0:
    ldrb r6, [fp], #1
MobiClip_Code_02092FD4:
    ldrb r7, [fp], #1
MobiClip_Code_02092FD8:
    ldrb r8, [fp], #1
MobiClip_Code_02092FDC:
    and sb, lr, #0xff
MobiClip_Code_02092FE0:
    subs sl, r5, r6
MobiClip_Code_02092FE4:
    rsblt sl, sl, #0
MobiClip_Code_02092FE8:
    cmp sl, sb
MobiClip_Code_02092FEC:
    bge MobiClip_Code_02093064
MobiClip_Code_02092FF0:
    subs sl, r4, r5
MobiClip_Code_02092FF4:
    rsblt sl, sl, #0
MobiClip_Code_02092FF8:
    cmp sl, lr, lsr #8
MobiClip_Code_02092FFC:
    bge MobiClip_Code_02093064
MobiClip_Code_02093000:
    subs sl, r7, r6
MobiClip_Code_02093004:
    rsblt sl, sl, #0
MobiClip_Code_02093008:
    cmp sl, lr, lsr #8
MobiClip_Code_0209300C:
    bge MobiClip_Code_02093064
MobiClip_Code_02093010:
    add sl, r5, r6
MobiClip_Code_02093014:
    add sl, sl, #1
MobiClip_Code_02093018:
    subs sb, r3, r5
MobiClip_Code_0209301C:
    sub r5, r4, r7
MobiClip_Code_02093020:
    add r5, r5, #4
MobiClip_Code_02093024:
    asr r5, r5, #3
MobiClip_Code_02093028:
    rsblt sb, sb, #0
MobiClip_Code_0209302C:
    cmp sb, lr, lsr #8
MobiClip_Code_02093030:
    addlt r4, r3, sl, asr #1
MobiClip_Code_02093034:
    addlt r4, r4, #1
MobiClip_Code_02093038:
    asrlt r4, r4, #1
MobiClip_Code_0209303C:
    subs sb, r8, r6
MobiClip_Code_02093040:
    rsblt sb, sb, #0
MobiClip_Code_02093044:
    cmp sb, lr, lsr #8
MobiClip_Code_02093048:
    addlt r7, r8, sl, asr #1
MobiClip_Code_0209304C:
    addlt r7, r7, #1
MobiClip_Code_02093050:
    asrlt r7, r7, #1
MobiClip_Code_02093054:
    rsb r6, r5, sl, asr #1
MobiClip_Code_02093058:
    ldrb r6, [ip, r6]
MobiClip_Code_0209305C:
    add r5, r5, sl, asr #1
MobiClip_Code_02093060:
    ldrb r5, [ip, r5]
MobiClip_Code_02093064:
    ldrb sb, [fp], #1
MobiClip_Code_02093068:
    orr r2, r2, r3, lsl #8
MobiClip_Code_0209306C:
    orr r2, r2, r4, lsl #16
MobiClip_Code_02093070:
    orr r2, r2, r5, lsl #24
MobiClip_Code_02093074:
    orr r6, r6, r7, lsl #8
MobiClip_Code_02093078:
    orr r6, r6, r8, lsl #16
MobiClip_Code_0209307C:
    orr r6, r6, sb, lsl #24
MobiClip_Code_02093080:
    stm r1!, {r2, r6}
MobiClip_Code_02093084:
    pop {sl}
MobiClip_Code_02093088:
    subs sl, sl, #8
MobiClip_Code_0209308C:
    bne MobiClip_Code_02092FBC
MobiClip_Code_02093090:
    pop {r3}
MobiClip_Code_02093094:
    ldr r2, [fp], #4
MobiClip_Code_02093098:
    ldr sl, [r0, #8]
MobiClip_Code_0209309C:
    add fp, fp, #0x100
MobiClip_Code_020930A0:
    str r2, [r1], #0x104
MobiClip_Code_020930A4:
    sub fp, fp, sl
MobiClip_Code_020930A8:
    sub r1, r1, sl
MobiClip_Code_020930AC:
    subs r3, r3, #1
MobiClip_Code_020930B0:
    ldrne r2, [fp], #4
MobiClip_Code_020930B4:
    strne r3, [sp, #-4]!
MobiClip_Code_020930B8:
    subne sl, sl, #8
MobiClip_Code_020930BC:
    strne r2, [r1], #4
MobiClip_Code_020930C0:
    bne MobiClip_Code_02092FBC
MobiClip_Code_020930C4:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
    /* MobiClip_DeblockLumaHorizontalEdges */
MobiClip_Code_020930C8:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020930CC:
    ldr r1, [r0, #8]
MobiClip_Code_020930D0:
    ldr r2, [r0, #0xc]
MobiClip_Code_020930D4:
    ldr r3, [r0, #0x10]
MobiClip_Code_020930D8:
    ldr r4, [r0, #0x14]
MobiClip_Code_020930DC:
    ldr r0, [r0, #4]
MobiClip_Code_020930E0:
    mov r5, r1
MobiClip_Code_020930E4:
    add r0, r0, #0x800
MobiClip_Code_020930E8:
    subs r2, r2, #8
MobiClip_Code_020930EC:
    ldrb r7, [r0, #-0x100]
MobiClip_Code_020930F0:
    ldrb r8, [r0]
MobiClip_Code_020930F4:
    ldrb r6, [r0, #-0x200]
MobiClip_Code_020930F8:
    ldrb sb, [r0, #0x100]
MobiClip_Code_020930FC:
    and lr, r3, #0xff
MobiClip_Code_02093100:
    subs sl, r7, r8
MobiClip_Code_02093104:
    rsblt sl, sl, #0
MobiClip_Code_02093108:
    cmp sl, lr
MobiClip_Code_0209310C:
    bge MobiClip_Code_02093198
MobiClip_Code_02093110:
    subs sl, r6, r7
MobiClip_Code_02093114:
    rsblt sl, sl, #0
MobiClip_Code_02093118:
    cmp sl, r3, lsr #8
MobiClip_Code_0209311C:
    bge MobiClip_Code_02093198
MobiClip_Code_02093120:
    subs sl, r8, sb
MobiClip_Code_02093124:
    rsblt sl, sl, #0
MobiClip_Code_02093128:
    cmp sl, r3, lsr #8
MobiClip_Code_0209312C:
    bge MobiClip_Code_02093198
MobiClip_Code_02093130:
    ldrb ip, [r0, #-0x300]
MobiClip_Code_02093134:
    ldrb lr, [r0, #0x200]
MobiClip_Code_02093138:
    sub r6, r6, sb
MobiClip_Code_0209313C:
    add sb, r7, r8
MobiClip_Code_02093140:
    add r6, r6, #4
MobiClip_Code_02093144:
    add sb, sb, #1
MobiClip_Code_02093148:
    asr sb, sb, #1
MobiClip_Code_0209314C:
    adds sl, sb, r6, asr #3
MobiClip_Code_02093150:
    subs fp, sb, r6, asr #3
MobiClip_Code_02093154:
    ldrb sl, [r4, sl]
MobiClip_Code_02093158:
    ldrb fp, [r4, fp]
MobiClip_Code_0209315C:
    add sb, sb, #1
MobiClip_Code_02093160:
    subs r7, ip, r7
MobiClip_Code_02093164:
    rsblt r7, r7, #0
MobiClip_Code_02093168:
    cmp r7, r3, lsr #8
MobiClip_Code_0209316C:
    addlt ip, ip, sb
MobiClip_Code_02093170:
    asrlt ip, ip, #1
MobiClip_Code_02093174:
    strblt ip, [r0, #-0x200]
MobiClip_Code_02093178:
    subs r8, lr, r8
MobiClip_Code_0209317C:
    rsblt r8, r8, #0
MobiClip_Code_02093180:
    cmp r8, r3, lsr #8
MobiClip_Code_02093184:
    addlt lr, lr, sb
MobiClip_Code_02093188:
    asrlt lr, lr, #1
MobiClip_Code_0209318C:
    strblt lr, [r0, #0x100]
MobiClip_Code_02093190:
    strb sl, [r0, #-0x100]
MobiClip_Code_02093194:
    strb fp, [r0]
MobiClip_Code_02093198:
    add r0, r0, #1
MobiClip_Code_0209319C:
    subs r5, r5, #1
MobiClip_Code_020931A0:
    bne MobiClip_Code_020930EC
MobiClip_Code_020931A4:
    add r0, r0, #0x800
MobiClip_Code_020931A8:
    sub r0, r0, r1
MobiClip_Code_020931AC:
    mov r5, r1
MobiClip_Code_020931B0:
    subs r2, r2, #8
MobiClip_Code_020931B4:
    bne MobiClip_Code_020930EC
MobiClip_Code_020931B8:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
    /* MobiClip_DeblockChromaVerticalEdges */
MobiClip_Code_020931BC:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020931C0:
    ldr lr, [r0, #0x10]
MobiClip_Code_020931C4:
    ldr ip, [r0, #0x14]
MobiClip_Code_020931C8:
    ldr r1, [r0, #4]
MobiClip_Code_020931CC:
    ldr fp, [r0]
MobiClip_Code_020931D0:
    ldr r3, [r0, #0xc]
MobiClip_Code_020931D4:
    ldr r2, [fp], #4
MobiClip_Code_020931D8:
    ldr sl, [r0, #8]
MobiClip_Code_020931DC:
    str r3, [sp, #-4]!
MobiClip_Code_020931E0:
    str r2, [r1], #4
MobiClip_Code_020931E4:
    sub sl, sl, #8
MobiClip_Code_020931E8:
    str sl, [sp, #-4]!
MobiClip_Code_020931EC:
    ldrb r2, [fp], #1
MobiClip_Code_020931F0:
    ldrb r3, [fp], #1
MobiClip_Code_020931F4:
    ldrb r4, [fp], #1
MobiClip_Code_020931F8:
    ldrb r5, [fp], #1
MobiClip_Code_020931FC:
    ldrb r6, [fp], #1
MobiClip_Code_02093200:
    ldrb r7, [fp], #1
MobiClip_Code_02093204:
    ldrb r8, [fp], #1
MobiClip_Code_02093208:
    and sb, lr, #0xff
MobiClip_Code_0209320C:
    subs sl, r5, r6
MobiClip_Code_02093210:
    rsblt sl, sl, #0
MobiClip_Code_02093214:
    cmp sl, sb
MobiClip_Code_02093218:
    bge MobiClip_Code_02093260
MobiClip_Code_0209321C:
    subs sl, r4, r5
MobiClip_Code_02093220:
    rsblt sl, sl, #0
MobiClip_Code_02093224:
    cmp sl, lr, lsr #8
MobiClip_Code_02093228:
    bge MobiClip_Code_02093260
MobiClip_Code_0209322C:
    subs sl, r7, r6
MobiClip_Code_02093230:
    rsblt sl, sl, #0
MobiClip_Code_02093234:
    cmp sl, lr, lsr #8
MobiClip_Code_02093238:
    bge MobiClip_Code_02093260
MobiClip_Code_0209323C:
    add sl, r5, r6
MobiClip_Code_02093240:
    add sl, sl, #1
MobiClip_Code_02093244:
    sub sb, r4, r7
MobiClip_Code_02093248:
    add sb, sb, #4
MobiClip_Code_0209324C:
    asr sb, sb, #3
MobiClip_Code_02093250:
    add r5, sb, sl, asr #1
MobiClip_Code_02093254:
    ldrb r5, [ip, r5]
MobiClip_Code_02093258:
    rsb r6, sb, sl, asr #1
MobiClip_Code_0209325C:
    ldrb r6, [ip, r6]
MobiClip_Code_02093260:
    ldrb sb, [fp], #1
MobiClip_Code_02093264:
    orr r2, r2, r3, lsl #8
MobiClip_Code_02093268:
    orr r2, r2, r4, lsl #16
MobiClip_Code_0209326C:
    orr r2, r2, r5, lsl #24
MobiClip_Code_02093270:
    orr r6, r6, r7, lsl #8
MobiClip_Code_02093274:
    orr r6, r6, r8, lsl #16
MobiClip_Code_02093278:
    orr r6, r6, sb, lsl #24
MobiClip_Code_0209327C:
    stm r1!, {r2, r6}
MobiClip_Code_02093280:
    pop {sl}
MobiClip_Code_02093284:
    subs sl, sl, #8
MobiClip_Code_02093288:
    bne MobiClip_Code_020931E8
MobiClip_Code_0209328C:
    pop {r3}
MobiClip_Code_02093290:
    ldr r2, [fp], #4
MobiClip_Code_02093294:
    ldr sl, [r0, #8]
MobiClip_Code_02093298:
    add fp, fp, #0x100
MobiClip_Code_0209329C:
    str r2, [r1], #0x104
MobiClip_Code_020932A0:
    sub fp, fp, sl
MobiClip_Code_020932A4:
    sub r1, r1, sl
MobiClip_Code_020932A8:
    subs r3, r3, #1
MobiClip_Code_020932AC:
    ldrne r2, [fp], #4
MobiClip_Code_020932B0:
    strne r3, [sp, #-4]!
MobiClip_Code_020932B4:
    subne sl, sl, #8
MobiClip_Code_020932B8:
    strne r2, [r1], #4
MobiClip_Code_020932BC:
    bne MobiClip_Code_020931E8
MobiClip_Code_020932C0:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
    /* MobiClip_DeblockChromaHorizontalEdges */
MobiClip_Code_020932C4:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020932C8:
    ldr r1, [r0, #8]
MobiClip_Code_020932CC:
    ldr r2, [r0, #0xc]
MobiClip_Code_020932D0:
    ldr r3, [r0, #0x10]
MobiClip_Code_020932D4:
    ldr r4, [r0, #0x14]
MobiClip_Code_020932D8:
    ldr r0, [r0, #4]
MobiClip_Code_020932DC:
    mov r5, r1
MobiClip_Code_020932E0:
    add r0, r0, #0x800
MobiClip_Code_020932E4:
    subs r2, r2, #8
MobiClip_Code_020932E8:
    ldrb r7, [r0, #-0x100]
MobiClip_Code_020932EC:
    ldrb r8, [r0]
MobiClip_Code_020932F0:
    ldrb r6, [r0, #-0x200]
MobiClip_Code_020932F4:
    ldrb sb, [r0, #0x100]
MobiClip_Code_020932F8:
    and lr, r3, #0xff
MobiClip_Code_020932FC:
    subs sl, r7, r8
MobiClip_Code_02093300:
    rsblt sl, sl, #0
MobiClip_Code_02093304:
    cmp sl, lr
MobiClip_Code_02093308:
    bge MobiClip_Code_02093378
MobiClip_Code_0209330C:
    subs sl, r6, r7
MobiClip_Code_02093310:
    rsblt sl, sl, #0
MobiClip_Code_02093314:
    cmp sl, r3, lsr #8
MobiClip_Code_02093318:
    bge MobiClip_Code_02093378
MobiClip_Code_0209331C:
    subs sl, r8, sb
MobiClip_Code_02093320:
    rsblt sl, sl, #0
MobiClip_Code_02093324:
    cmp sl, r3, lsr #8
MobiClip_Code_02093328:
    bge MobiClip_Code_02093378
MobiClip_Code_0209332C:
    sub r6, r6, sb
MobiClip_Code_02093330:
    add sb, r7, r8
MobiClip_Code_02093334:
    add r6, r6, #4
MobiClip_Code_02093338:
    add sb, sb, #1
MobiClip_Code_0209333C:
    asr sb, sb, #1
MobiClip_Code_02093340:
    adds sl, sb, r6, asr #3
MobiClip_Code_02093344:
    ldrb sl, [r4, sl]
MobiClip_Code_02093348:
    subs fp, sb, r6, asr #3
MobiClip_Code_0209334C:
    ldrb fp, [r4, fp]
MobiClip_Code_02093350:
    subs r5, r5, #1
MobiClip_Code_02093354:
    strb sl, [r0, #-0x100]
MobiClip_Code_02093358:
    strb fp, [r0], #1
MobiClip_Code_0209335C:
    bne MobiClip_Code_020932E8
MobiClip_Code_02093360:
    add r0, r0, #0x800
MobiClip_Code_02093364:
    sub r0, r0, r1
MobiClip_Code_02093368:
    mov r5, r1
MobiClip_Code_0209336C:
    subs r2, r2, #8
MobiClip_Code_02093370:
    bne MobiClip_Code_020932E8
MobiClip_Code_02093374:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
MobiClip_Code_02093378:
    add r0, r0, #1
MobiClip_Code_0209337C:
    subs r5, r5, #1
MobiClip_Code_02093380:
    bne MobiClip_Code_020932E8
MobiClip_Code_02093384:
    add r0, r0, #0x800
MobiClip_Code_02093388:
    sub r0, r0, r1
MobiClip_Code_0209338C:
    mov r5, r1
MobiClip_Code_02093390:
    subs r2, r2, #8
MobiClip_Code_02093394:
    bne MobiClip_Code_020932E8
MobiClip_Code_02093398:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
    /* four words no code reads */
    .global gMobiClipDeblockTailWords
    .type gMobiClipDeblockTailWords, %object
gMobiClipDeblockTailWords:
    .byte 0x14, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00
    .size func_ov024_02092e60_unk, . - func_ov024_02092e60_unk
