    .syntax unified
    .arch armv5te
    .section .rodata,"a",%progbits
    .arm
    .align 2
    .global data_ov024_0208c8c4
    .type data_ov024_0208c8c4, %object
data_ov024_0208c8c4:
MobiClip_Code_0208C8C4:
    b MobiClip_Code_0208DFB4
    /* control metadata 0x0208c8c8..0x0208c8d0 */
    .global gMobiClip_payload_header
    .type gMobiClip_payload_header, %object
gMobiClip_payload_header:
    /* payload_configuration */
    .byte 0x00, 0x01, 0x00, 0x00, 0x9e, 0x00, 0x00, 0x00
    .size gMobiClip_payload_header, . - gMobiClip_payload_header
    /* control metadata 0x0208c8d0..0x0208c910 */
    .global gMobiClip_luma_interpolation_dispatch
    .type gMobiClip_luma_interpolation_dispatch, %object
gMobiClip_luma_interpolation_dispatch:
    /* luma_interpolation */
    .global gMobiClip_luma_interpolation
gMobiClip_luma_interpolation:
    .word MobiClip_Code_020912B8 - .
    .word MobiClip_Code_02091364 - . + 0x4
    .word MobiClip_Code_020914F0 - . + 0x8
    .word MobiClip_Code_02091630 - . + 0xc
    .word MobiClip_Code_02091844 - . + 0x10
    .word MobiClip_Code_02091984 - . + 0x14
    .word MobiClip_Code_02091B88 - . + 0x18
    .word MobiClip_Code_02091CB8 - . + 0x1c
    .word MobiClip_Code_020912D4 - . + 0x20
    .word MobiClip_Code_020913BC - . + 0x24
    .word MobiClip_Code_02091534 - . + 0x28
    .word MobiClip_Code_020916AC - . + 0x2c
    .word MobiClip_Code_02091888 - . + 0x30
    .word MobiClip_Code_020919FC - . + 0x34
    .word MobiClip_Code_02091BC8 - . + 0x38
    .word MobiClip_Code_02091D14 - . + 0x3c
    .size gMobiClip_luma_interpolation_dispatch, . - gMobiClip_luma_interpolation_dispatch
    /* control metadata 0x0208c910..0x0208c950 */
    .global gMobiClip_chroma_interpolation_dispatch
    .type gMobiClip_chroma_interpolation_dispatch, %object
gMobiClip_chroma_interpolation_dispatch:
    /* chroma_interpolation */
    .global gMobiClip_chroma_interpolation
gMobiClip_chroma_interpolation:
    .word MobiClip_Code_02091E50 - .
    .word MobiClip_Code_02091ED4 - . + 0x4
    .word MobiClip_Code_02091FDC - . + 0x8
    .word MobiClip_Code_020920B8 - . + 0xc
    .word MobiClip_Code_02092208 - . + 0x10
    .word MobiClip_Code_020922DC - . + 0x14
    .word MobiClip_Code_0209241C - . + 0x18
    .word MobiClip_Code_020924E8 - . + 0x1c
    .word MobiClip_Code_02091E6C - . + 0x20
    .word MobiClip_Code_02091F14 - . + 0x24
    .word MobiClip_Code_02092010 - . + 0x28
    .word MobiClip_Code_0209210C - . + 0x2c
    .word MobiClip_Code_02092238 - . + 0x30
    .word MobiClip_Code_0209232C - . + 0x34
    .word MobiClip_Code_0209244C - . + 0x38
    .word MobiClip_Code_0209252C - . + 0x3c
    .size gMobiClip_chroma_interpolation_dispatch, . - gMobiClip_chroma_interpolation_dispatch
MobiClip_Code_0208C950:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208C954:
    bl MobiClip_Code_0208E93C
MobiClip_Code_0208C958:
    mov r5, r6
MobiClip_Code_0208C95C:
    bl MobiClip_Code_0208E93C
MobiClip_Code_0208C960:
    add sb, r0, #0x3bc
MobiClip_Code_0208C964:
    ldm sb, {r7, r8}
MobiClip_Code_0208C968:
    add r5, r5, r7
MobiClip_Code_0208C96C:
    add r6, r6, r8
MobiClip_Code_0208C970:
    stm r4, {r5, r6}
MobiClip_Code_0208C974:
    add r7, r5, fp, lsl #1
MobiClip_Code_0208C978:
    and r7, r7, #7
MobiClip_Code_0208C97C:
    and r8, r6, #1
MobiClip_Code_0208C980:
    add r7, r7, r8, lsl #3
MobiClip_Code_0208C984:
    push {r0, r1, r2, r3}
MobiClip_Code_0208C988:
    ldr r2, [sp, #0x14]
MobiClip_Code_0208C98C:
    ldr r1, [r0, #0xc]
MobiClip_Code_0208C990:
    add r0, r0, r2
MobiClip_Code_0208C994:
    ldr r0, [r0, #0xc]
MobiClip_Code_0208C998:
    asr r8, r6, #1
MobiClip_Code_0208C99C:
    add r0, r0, fp
MobiClip_Code_0208C9A0:
    add r0, r0, r8, lsl #8
MobiClip_Code_0208C9A4:
    add r0, r0, r5, asr #1
MobiClip_Code_0208C9A8:
    add r1, r1, fp
MobiClip_Code_0208C9AC:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208C9B0:
    sub r3, pc, #0xe8
MobiClip_Code_0208C9B4:
    add lr, pc, #4
MobiClip_Code_0208C9B8:
    ldr r8, [r3, r7, lsl #2]
MobiClip_Code_0208C9BC:
    add pc, r8, r3
MobiClip_Code_0208C9C0:
    ldr r0, [sp]
MobiClip_Code_0208C9C4:
    ldr r2, [sp, #0x14]
MobiClip_Code_0208C9C8:
    ldr r1, [r0, #0x24]
MobiClip_Code_0208C9CC:
    add r0, r0, r2
MobiClip_Code_0208C9D0:
    ldr r0, [r0, #0x24]
MobiClip_Code_0208C9D4:
    asr r8, r6, #2
MobiClip_Code_0208C9D8:
    add r0, r0, fp, lsr #1
MobiClip_Code_0208C9DC:
    add r0, r0, r8, lsl #8
MobiClip_Code_0208C9E0:
    add r0, r0, r5, asr #2
MobiClip_Code_0208C9E4:
    add r1, r1, fp, lsr #1
MobiClip_Code_0208C9E8:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208C9EC:
    lsr r2, r2, #1
MobiClip_Code_0208C9F0:
    sub r3, pc, #0xe8
MobiClip_Code_0208C9F4:
    add r5, r5, fp, lsl #1
MobiClip_Code_0208C9F8:
    asr r5, r5, #1
MobiClip_Code_0208C9FC:
    and r5, r5, #7
MobiClip_Code_0208CA00:
    asr r8, r6, #1
MobiClip_Code_0208CA04:
    and r8, r8, #1
MobiClip_Code_0208CA08:
    add r5, r5, r8, lsl #3
MobiClip_Code_0208CA0C:
    add lr, pc, #8
MobiClip_Code_0208CA10:
    mov r6, r0
MobiClip_Code_0208CA14:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_0208CA18:
    add pc, r8, r3
MobiClip_Code_0208CA1C:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208CA20:
    lsr r2, r2, #1
MobiClip_Code_0208CA24:
    add r0, r6, #0x80
MobiClip_Code_0208CA28:
    sub r1, r1, r2, lsl #8
MobiClip_Code_0208CA2C:
    add r1, r1, #0x80
MobiClip_Code_0208CA30:
    sub r3, pc, #0x128
MobiClip_Code_0208CA34:
    add lr, pc, #4
MobiClip_Code_0208CA38:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_0208CA3C:
    add pc, r8, r3
MobiClip_Code_0208CA40:
    pop {r0, r1, r2, r3, r4, r5, r6, fp, ip, pc}
    /* control metadata 0x0208ca44..0x0208ca98 */
    .global gMobiClip_pframe_prefix_offsets_and_lengths
    .type gMobiClip_pframe_prefix_offsets_and_lengths, %object
gMobiClip_pframe_prefix_offsets_and_lengths:
    /* pframe_prefix_codes */
    .byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x08, 0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09
    .byte 0x04, 0x03, 0x02, 0x02, 0x07, 0x07, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /* pframe_macroblock */
    .global gMobiClip_pframe_macroblock
gMobiClip_pframe_macroblock:
    .word MobiClip_Code_0208CA98 - .
    .word MobiClip_Code_0208CAC0 - . + 0x4
    .word MobiClip_Code_0208CAD8 - . + 0x8
    .word MobiClip_Code_0208CAF0 - . + 0xc
    .word MobiClip_Code_0208CB08 - . + 0x10
    .word MobiClip_Code_0208CB20 - . + 0x14
    .word MobiClip_Code_0208E1C8 - . + 0x18
    .word MobiClip_Code_0208E28C - . + 0x1c
    .word MobiClip_Code_0208CB38 - . + 0x20
    .word MobiClip_Code_0208CB54 - . + 0x24
    /* pframe_code_lengths */
    .byte 0x02, 0x02, 0x04, 0x05, 0x05, 0x05, 0x05, 0x04, 0x03, 0x03, 0x00, 0x00
    .size gMobiClip_pframe_prefix_offsets_and_lengths, . - gMobiClip_pframe_prefix_offsets_and_lengths
MobiClip_Code_0208CA98:
    str lr, [sp, #-4]!
MobiClip_Code_0208CA9C:
    mov r5, #4
MobiClip_Code_0208CAA0:
    mov r6, #0x10
MobiClip_Code_0208CAA4:
    add lr, pc, #0xc
MobiClip_Code_0208CAA8:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208CAAC:
    add sb, r0, #0x3bc
MobiClip_Code_0208CAB0:
    ldm sb, {r5, r6}
MobiClip_Code_0208CAB4:
    b MobiClip_Code_0208C970
MobiClip_Code_0208CAB8:
    bl MobiClip_Code_0208E364
MobiClip_Code_0208CABC:
    pop {pc}
MobiClip_Code_0208CAC0:
    str lr, [sp, #-4]!
MobiClip_Code_0208CAC4:
    mov r5, #4
MobiClip_Code_0208CAC8:
    mov r6, #0x10
MobiClip_Code_0208CACC:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208CAD0:
    bl MobiClip_Code_0208E364
MobiClip_Code_0208CAD4:
    pop {pc}
MobiClip_Code_0208CAD8:
    str lr, [sp, #-4]!
MobiClip_Code_0208CADC:
    mov r5, #8
MobiClip_Code_0208CAE0:
    mov r6, #0x10
MobiClip_Code_0208CAE4:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208CAE8:
    bl MobiClip_Code_0208E364
MobiClip_Code_0208CAEC:
    pop {pc}
MobiClip_Code_0208CAF0:
    str lr, [sp, #-4]!
MobiClip_Code_0208CAF4:
    mov r5, #0xc
MobiClip_Code_0208CAF8:
    mov r6, #0x10
MobiClip_Code_0208CAFC:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208CB00:
    bl MobiClip_Code_0208E364
MobiClip_Code_0208CB04:
    pop {pc}
MobiClip_Code_0208CB08:
    str lr, [sp, #-4]!
MobiClip_Code_0208CB0C:
    mov r5, #0x10
MobiClip_Code_0208CB10:
    mov r6, #0x10
MobiClip_Code_0208CB14:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208CB18:
    bl MobiClip_Code_0208E364
MobiClip_Code_0208CB1C:
    pop {pc}
MobiClip_Code_0208CB20:
    str lr, [sp, #-4]!
MobiClip_Code_0208CB24:
    mov r5, #0x14
MobiClip_Code_0208CB28:
    mov r6, #0x10
MobiClip_Code_0208CB2C:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208CB30:
    bl MobiClip_Code_0208E364
MobiClip_Code_0208CB34:
    pop {pc}
MobiClip_Code_0208CB38:
    str lr, [sp, #-4]!
MobiClip_Code_0208CB3C:
    bl MobiClip_Code_0208D34C
MobiClip_Code_0208CB40:
    add fp, fp, #0x800
MobiClip_Code_0208CB44:
    bl MobiClip_Code_0208D34C
MobiClip_Code_0208CB48:
    sub fp, fp, #0x800
MobiClip_Code_0208CB4C:
    bl MobiClip_Code_0208E364
MobiClip_Code_0208CB50:
    pop {pc}
MobiClip_Code_0208CB54:
    str lr, [sp, #-4]!
MobiClip_Code_0208CB58:
    bl MobiClip_Code_0208CDC8
MobiClip_Code_0208CB5C:
    add fp, fp, #8
MobiClip_Code_0208CB60:
    bl MobiClip_Code_0208CDC8
MobiClip_Code_0208CB64:
    sub fp, fp, #8
MobiClip_Code_0208CB68:
    bl MobiClip_Code_0208E364
MobiClip_Code_0208CB6C:
    pop {pc}
MobiClip_Code_0208CB70:
    lsr r6, r3, #0x1b
MobiClip_Code_0208CB74:
    sub r5, pc, #0x138
MobiClip_Code_0208CB78:
    ldrb r5, [r5, r6]
MobiClip_Code_0208CB7C:
    sub r6, pc, #0xf8
MobiClip_Code_0208CB80:
    ldrb r6, [r6, r5]
MobiClip_Code_0208CB84:
    lsl r3, r3, r6
MobiClip_Code_0208CB88:
    subs r2, r2, r6
MobiClip_Code_0208CB8C:
    mov r8, lr
MobiClip_Code_0208CB90:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208CB94:
    sub r6, pc, #0x138
MobiClip_Code_0208CB98:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208CB9C:
    mov lr, r8
MobiClip_Code_0208CBA0:
    add pc, r5, r6
    /* control metadata 0x0208cba4..0x0208cbe4 */
    .global gMobiClip_luma_kernel_dispatch
    .type gMobiClip_luma_kernel_dispatch, %object
gMobiClip_luma_kernel_dispatch:
    /* motion16_dispatch */
    .global gMobiClip_motion16_dispatch
gMobiClip_motion16_dispatch:
    .word MobiClip_Code_020925FC - .
    .word MobiClip_Code_02092650 - . + 0x4
    .word MobiClip_Code_02092708 - . + 0x8
    .word MobiClip_Code_020927A4 - . + 0xc
    .word MobiClip_Code_02092884 - . + 0x10
    .word MobiClip_Code_02092908 - . + 0x14
    .word MobiClip_Code_020929C8 - . + 0x18
    .word MobiClip_Code_02092A44 - . + 0x1c
    .word MobiClip_Code_02092610 - . + 0x20
    .word MobiClip_Code_02092680 - . + 0x24
    .word MobiClip_Code_02092730 - . + 0x28
    .word MobiClip_Code_020927E0 - . + 0x2c
    .word MobiClip_Code_020928A4 - . + 0x30
    .word MobiClip_Code_0209293C - . + 0x34
    .word MobiClip_Code_020929E8 - . + 0x38
    .word MobiClip_Code_02092A74 - . + 0x3c
    .size gMobiClip_luma_kernel_dispatch, . - gMobiClip_luma_kernel_dispatch
MobiClip_Code_0208CBE4:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208CBE8:
    bl MobiClip_Code_0208E93C
MobiClip_Code_0208CBEC:
    mov r5, r6
MobiClip_Code_0208CBF0:
    bl MobiClip_Code_0208E93C
MobiClip_Code_0208CBF4:
    add sb, r0, #0x3bc
MobiClip_Code_0208CBF8:
    ldm sb, {r7, r8}
MobiClip_Code_0208CBFC:
    add r5, r5, r7
MobiClip_Code_0208CC00:
    add r6, r6, r8
MobiClip_Code_0208CC04:
    stm r4, {r5, r6}
MobiClip_Code_0208CC08:
    add r7, r5, fp, lsl #1
MobiClip_Code_0208CC0C:
    and r7, r7, #7
MobiClip_Code_0208CC10:
    and r8, r6, #1
MobiClip_Code_0208CC14:
    add r7, r7, r8, lsl #3
MobiClip_Code_0208CC18:
    push {r0, r1, r2, r3}
MobiClip_Code_0208CC1C:
    ldr r2, [sp, #0x14]
MobiClip_Code_0208CC20:
    ldr r1, [r0, #0xc]
MobiClip_Code_0208CC24:
    add r0, r0, r2
MobiClip_Code_0208CC28:
    ldr r0, [r0, #0xc]
MobiClip_Code_0208CC2C:
    asr r8, r6, #1
MobiClip_Code_0208CC30:
    add r0, r0, fp
MobiClip_Code_0208CC34:
    add r0, r0, r8, lsl #8
MobiClip_Code_0208CC38:
    add r0, r0, r5, asr #1
MobiClip_Code_0208CC3C:
    add r1, r1, fp
MobiClip_Code_0208CC40:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208CC44:
    sub r3, pc, #0x33c
MobiClip_Code_0208CC48:
    add lr, pc, #4
MobiClip_Code_0208CC4C:
    ldr r8, [r3, r7, lsl #2]
MobiClip_Code_0208CC50:
    add pc, r8, r3
MobiClip_Code_0208CC54:
    ldr r0, [sp]
MobiClip_Code_0208CC58:
    ldr r2, [sp, #0x14]
MobiClip_Code_0208CC5C:
    ldr r1, [r0, #0x24]
MobiClip_Code_0208CC60:
    add r0, r0, r2
MobiClip_Code_0208CC64:
    ldr r0, [r0, #0x24]
MobiClip_Code_0208CC68:
    asr r8, r6, #2
MobiClip_Code_0208CC6C:
    add r0, r0, fp, lsr #1
MobiClip_Code_0208CC70:
    add r0, r0, r8, lsl #8
MobiClip_Code_0208CC74:
    add r0, r0, r5, asr #2
MobiClip_Code_0208CC78:
    add r1, r1, fp, lsr #1
MobiClip_Code_0208CC7C:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208CC80:
    lsr r2, r2, #1
MobiClip_Code_0208CC84:
    sub r3, pc, #0xe8
MobiClip_Code_0208CC88:
    add r5, r5, fp, lsl #1
MobiClip_Code_0208CC8C:
    asr r5, r5, #1
MobiClip_Code_0208CC90:
    and r5, r5, #7
MobiClip_Code_0208CC94:
    asr r8, r6, #1
MobiClip_Code_0208CC98:
    and r8, r8, #1
MobiClip_Code_0208CC9C:
    add r5, r5, r8, lsl #3
MobiClip_Code_0208CCA0:
    add lr, pc, #8
MobiClip_Code_0208CCA4:
    mov r6, r0
MobiClip_Code_0208CCA8:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_0208CCAC:
    add pc, r8, r3
MobiClip_Code_0208CCB0:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208CCB4:
    lsr r2, r2, #1
MobiClip_Code_0208CCB8:
    add r0, r6, #0x80
MobiClip_Code_0208CCBC:
    sub r1, r1, r2, lsl #8
MobiClip_Code_0208CCC0:
    add r1, r1, #0x80
MobiClip_Code_0208CCC4:
    sub r3, pc, #0x128
MobiClip_Code_0208CCC8:
    add lr, pc, #4
MobiClip_Code_0208CCCC:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_0208CCD0:
    add pc, r8, r3
MobiClip_Code_0208CCD4:
    pop {r0, r1, r2, r3, r4, r5, r6, fp, ip, pc}
    /* control metadata 0x0208ccd8..0x0208cd1c */
    .global gMobiClip_motion16_selector_and_offsets
    .type gMobiClip_motion16_selector_and_offsets, %object
gMobiClip_motion16_selector_and_offsets:
    /* motion16_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x05, 0x04, 0x02, 0x02, 0x03, 0x08, 0x01, 0x01, 0x01, 0x01
    /* motion16_modes */
    .global gMobiClip_motion16_modes
gMobiClip_motion16_modes:
    .word MobiClip_Code_0208CD1C - .
    .word MobiClip_Code_0208CD34 - . + 0x4
    .word MobiClip_Code_0208CD48 - . + 0x8
    .word MobiClip_Code_0208CD5C - . + 0xc
    .word MobiClip_Code_0208CD70 - . + 0x10
    .word MobiClip_Code_0208CD84 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208CD98 - . + 0x20
    .word MobiClip_Code_0208CDB0 - . + 0x24
    /* motion16_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x04, 0x04, 0x04, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00
    .size gMobiClip_motion16_selector_and_offsets, . - gMobiClip_motion16_selector_and_offsets
MobiClip_Code_0208CD1C:
    mov r5, #4
MobiClip_Code_0208CD20:
    mov r6, #0x10
MobiClip_Code_0208CD24:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208CD28:
    add sb, r0, #0x3bc
MobiClip_Code_0208CD2C:
    ldm sb, {r5, r6}
MobiClip_Code_0208CD30:
    b MobiClip_Code_0208CC04
MobiClip_Code_0208CD34:
    str lr, [sp, #-4]!
MobiClip_Code_0208CD38:
    mov r5, #4
MobiClip_Code_0208CD3C:
    mov r6, #0x10
MobiClip_Code_0208CD40:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208CD44:
    pop {pc}
MobiClip_Code_0208CD48:
    str lr, [sp, #-4]!
MobiClip_Code_0208CD4C:
    mov r5, #8
MobiClip_Code_0208CD50:
    mov r6, #0x10
MobiClip_Code_0208CD54:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208CD58:
    pop {pc}
MobiClip_Code_0208CD5C:
    str lr, [sp, #-4]!
MobiClip_Code_0208CD60:
    mov r5, #0xc
MobiClip_Code_0208CD64:
    mov r6, #0x10
MobiClip_Code_0208CD68:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208CD6C:
    pop {pc}
MobiClip_Code_0208CD70:
    str lr, [sp, #-4]!
MobiClip_Code_0208CD74:
    mov r5, #0x10
MobiClip_Code_0208CD78:
    mov r6, #0x10
MobiClip_Code_0208CD7C:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208CD80:
    pop {pc}
MobiClip_Code_0208CD84:
    str lr, [sp, #-4]!
MobiClip_Code_0208CD88:
    mov r5, #0x14
MobiClip_Code_0208CD8C:
    mov r6, #0x10
MobiClip_Code_0208CD90:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208CD94:
    pop {pc}
MobiClip_Code_0208CD98:
    str lr, [sp, #-4]!
MobiClip_Code_0208CD9C:
    bl MobiClip_Code_0208D6A0
MobiClip_Code_0208CDA0:
    add fp, fp, #0x800
MobiClip_Code_0208CDA4:
    bl MobiClip_Code_0208D6A0
MobiClip_Code_0208CDA8:
    sub fp, fp, #0x800
MobiClip_Code_0208CDAC:
    pop {pc}
MobiClip_Code_0208CDB0:
    str lr, [sp, #-4]!
MobiClip_Code_0208CDB4:
    bl MobiClip_Code_0208D000
MobiClip_Code_0208CDB8:
    add fp, fp, #4
MobiClip_Code_0208CDBC:
    bl MobiClip_Code_0208D000
MobiClip_Code_0208CDC0:
    sub fp, fp, #4
MobiClip_Code_0208CDC4:
    pop {pc}
MobiClip_Code_0208CDC8:
    lsr r6, r3, #0x1c
MobiClip_Code_0208CDCC:
    sub r5, pc, #0xfc
MobiClip_Code_0208CDD0:
    ldrb r5, [r5, r6]
MobiClip_Code_0208CDD4:
    sub r6, pc, #0xcc
MobiClip_Code_0208CDD8:
    ldrb r6, [r6, r5]
MobiClip_Code_0208CDDC:
    lsl r3, r3, r6
MobiClip_Code_0208CDE0:
    subs r2, r2, r6
MobiClip_Code_0208CDE4:
    mov r8, lr
MobiClip_Code_0208CDE8:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208CDEC:
    sub r6, pc, #0x10c
MobiClip_Code_0208CDF0:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208CDF4:
    mov lr, r8
MobiClip_Code_0208CDF8:
    add pc, r5, r6
    /* control metadata 0x0208cdfc..0x0208ce1c */
    .global gMobiClip_chroma_kernel_dispatch
    .type gMobiClip_chroma_kernel_dispatch, %object
gMobiClip_chroma_kernel_dispatch:
    /* motion8x16_dispatch */
    .global gMobiClip_motion8x16_dispatch
gMobiClip_motion8x16_dispatch:
    .word MobiClip_Code_020929E4 - . + 0x114
    .word MobiClip_Code_02092A54 - . + 0x118
    .word MobiClip_Code_02092B18 - . + 0x11c
    .word MobiClip_Code_02092BA0 - . + 0x120
    .word MobiClip_Code_02092A00 - . + 0x124
    .word MobiClip_Code_02092A88 - . + 0x128
    .word MobiClip_Code_02092B3C - . + 0x12c
    .word MobiClip_Code_02092BD8 - . + 0x130
    .size gMobiClip_chroma_kernel_dispatch, . - gMobiClip_chroma_kernel_dispatch
MobiClip_Code_0208CE1C:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208CE20:
    bl MobiClip_Code_0208E93C
MobiClip_Code_0208CE24:
    mov r5, r6
MobiClip_Code_0208CE28:
    bl MobiClip_Code_0208E93C
MobiClip_Code_0208CE2C:
    add sb, r0, #0x3bc
MobiClip_Code_0208CE30:
    ldm sb, {r7, r8}
MobiClip_Code_0208CE34:
    add r5, r5, r7
MobiClip_Code_0208CE38:
    add r6, r6, r8
MobiClip_Code_0208CE3C:
    stm r4, {r5, r6}
MobiClip_Code_0208CE40:
    add r7, r5, fp, lsl #1
MobiClip_Code_0208CE44:
    and r7, r7, #7
MobiClip_Code_0208CE48:
    and r8, r6, #1
MobiClip_Code_0208CE4C:
    add r7, r7, r8, lsl #3
MobiClip_Code_0208CE50:
    push {r0, r1, r2, r3}
MobiClip_Code_0208CE54:
    ldr r2, [sp, #0x14]
MobiClip_Code_0208CE58:
    ldr r1, [r0, #0xc]
MobiClip_Code_0208CE5C:
    add r0, r0, r2
MobiClip_Code_0208CE60:
    ldr r0, [r0, #0xc]
MobiClip_Code_0208CE64:
    asr r8, r6, #1
MobiClip_Code_0208CE68:
    add r0, r0, fp
MobiClip_Code_0208CE6C:
    add r0, r0, r8, lsl #8
MobiClip_Code_0208CE70:
    add r0, r0, r5, asr #1
MobiClip_Code_0208CE74:
    add r1, r1, fp
MobiClip_Code_0208CE78:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208CE7C:
    sub r3, pc, #0x2e0
MobiClip_Code_0208CE80:
    add lr, pc, #4
MobiClip_Code_0208CE84:
    ldr r8, [r3, r7, lsl #2]
MobiClip_Code_0208CE88:
    add pc, r8, r3
MobiClip_Code_0208CE8C:
    ldr r0, [sp]
MobiClip_Code_0208CE90:
    ldr r2, [sp, #0x14]
MobiClip_Code_0208CE94:
    ldr r1, [r0, #0x24]
MobiClip_Code_0208CE98:
    add r0, r0, r2
MobiClip_Code_0208CE9C:
    ldr r0, [r0, #0x24]
MobiClip_Code_0208CEA0:
    asr r8, r6, #2
MobiClip_Code_0208CEA4:
    add r0, r0, fp, lsr #1
MobiClip_Code_0208CEA8:
    add r0, r0, r8, lsl #8
MobiClip_Code_0208CEAC:
    add r0, r0, r5, asr #2
MobiClip_Code_0208CEB0:
    add r1, r1, fp, lsr #1
MobiClip_Code_0208CEB4:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208CEB8:
    lsr r2, r2, #1
MobiClip_Code_0208CEBC:
    sub r3, pc, #0xc8
MobiClip_Code_0208CEC0:
    add r5, r5, fp, lsl #1
MobiClip_Code_0208CEC4:
    asr r5, r5, #1
MobiClip_Code_0208CEC8:
    and r5, r5, #3
MobiClip_Code_0208CECC:
    asr r8, r6, #1
MobiClip_Code_0208CED0:
    and r8, r8, #1
MobiClip_Code_0208CED4:
    add r5, r5, r8, lsl #2
MobiClip_Code_0208CED8:
    add lr, pc, #8
MobiClip_Code_0208CEDC:
    mov r6, r0
MobiClip_Code_0208CEE0:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_0208CEE4:
    add pc, r8, r3
MobiClip_Code_0208CEE8:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208CEEC:
    lsr r2, r2, #1
MobiClip_Code_0208CEF0:
    add r0, r6, #0x80
MobiClip_Code_0208CEF4:
    sub r1, r1, r2, lsl #8
MobiClip_Code_0208CEF8:
    add r1, r1, #0x80
MobiClip_Code_0208CEFC:
    sub r3, pc, #0x108
MobiClip_Code_0208CF00:
    add lr, pc, #4
MobiClip_Code_0208CF04:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_0208CF08:
    add pc, r8, r3
MobiClip_Code_0208CF0C:
    pop {r0, r1, r2, r3, r4, r5, r6, fp, ip, pc}
    /* control metadata 0x0208cf10..0x0208cf54 */
    .global gMobiClip_motion8x16_selector_and_offsets
    .type gMobiClip_motion8x16_selector_and_offsets, %object
gMobiClip_motion8x16_selector_and_offsets:
    /* motion8x16_selectors */
    .byte 0x03, 0x03, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01
    /* motion8x16_modes */
    .global gMobiClip_motion8x16_modes
gMobiClip_motion8x16_modes:
    .word MobiClip_Code_0208CF54 - .
    .word MobiClip_Code_0208CF6C - . + 0x4
    .word MobiClip_Code_0208CF80 - . + 0x8
    .word MobiClip_Code_0208CF94 - . + 0xc
    .word MobiClip_Code_0208CFA8 - . + 0x10
    .word MobiClip_Code_0208CFBC - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208CFD0 - . + 0x20
    .word MobiClip_Code_0208CFE8 - . + 0x24
    /* motion8x16_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00
    .size gMobiClip_motion8x16_selector_and_offsets, . - gMobiClip_motion8x16_selector_and_offsets
MobiClip_Code_0208CF54:
    mov r5, #4
MobiClip_Code_0208CF58:
    mov r6, #0x10
MobiClip_Code_0208CF5C:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208CF60:
    add sb, r0, #0x3bc
MobiClip_Code_0208CF64:
    ldm sb, {r5, r6}
MobiClip_Code_0208CF68:
    b MobiClip_Code_0208CE3C
MobiClip_Code_0208CF6C:
    str lr, [sp, #-4]!
MobiClip_Code_0208CF70:
    mov r5, #4
MobiClip_Code_0208CF74:
    mov r6, #0x10
MobiClip_Code_0208CF78:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208CF7C:
    pop {pc}
MobiClip_Code_0208CF80:
    str lr, [sp, #-4]!
MobiClip_Code_0208CF84:
    mov r5, #8
MobiClip_Code_0208CF88:
    mov r6, #0x10
MobiClip_Code_0208CF8C:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208CF90:
    pop {pc}
MobiClip_Code_0208CF94:
    str lr, [sp, #-4]!
MobiClip_Code_0208CF98:
    mov r5, #0xc
MobiClip_Code_0208CF9C:
    mov r6, #0x10
MobiClip_Code_0208CFA0:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208CFA4:
    pop {pc}
MobiClip_Code_0208CFA8:
    str lr, [sp, #-4]!
MobiClip_Code_0208CFAC:
    mov r5, #0x10
MobiClip_Code_0208CFB0:
    mov r6, #0x10
MobiClip_Code_0208CFB4:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208CFB8:
    pop {pc}
MobiClip_Code_0208CFBC:
    str lr, [sp, #-4]!
MobiClip_Code_0208CFC0:
    mov r5, #0x14
MobiClip_Code_0208CFC4:
    mov r6, #0x10
MobiClip_Code_0208CFC8:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208CFCC:
    pop {pc}
MobiClip_Code_0208CFD0:
    str lr, [sp, #-4]!
MobiClip_Code_0208CFD4:
    bl MobiClip_Code_0208DA00
MobiClip_Code_0208CFD8:
    add fp, fp, #0x800
MobiClip_Code_0208CFDC:
    bl MobiClip_Code_0208DA00
MobiClip_Code_0208CFE0:
    sub fp, fp, #0x800
MobiClip_Code_0208CFE4:
    pop {pc}
MobiClip_Code_0208CFE8:
    str lr, [sp, #-4]!
MobiClip_Code_0208CFEC:
    bl MobiClip_Code_0208D228
MobiClip_Code_0208CFF0:
    add fp, fp, #2
MobiClip_Code_0208CFF4:
    bl MobiClip_Code_0208D228
MobiClip_Code_0208CFF8:
    sub fp, fp, #2
MobiClip_Code_0208CFFC:
    pop {pc}
MobiClip_Code_0208D000:
    lsr r6, r3, #0x1c
MobiClip_Code_0208D004:
    sub r5, pc, #0xfc
MobiClip_Code_0208D008:
    ldrb r5, [r5, r6]
MobiClip_Code_0208D00C:
    sub r6, pc, #0xcc
MobiClip_Code_0208D010:
    ldrb r6, [r6, r5]
MobiClip_Code_0208D014:
    lsl r3, r3, r6
MobiClip_Code_0208D018:
    subs r2, r2, r6
MobiClip_Code_0208D01C:
    mov r8, lr
MobiClip_Code_0208D020:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208D024:
    sub r6, pc, #0x10c
MobiClip_Code_0208D028:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208D02C:
    mov lr, r8
MobiClip_Code_0208D030:
    add pc, r5, r6
    /* control metadata 0x0208d034..0x0208d044 */
    .global gMobiClip_chroma_narrow_kernel_dispatch
    .type gMobiClip_chroma_narrow_kernel_dispatch, %object
gMobiClip_chroma_narrow_kernel_dispatch:
    /* intra16_dispatch */
    .global gMobiClip_intra16_dispatch
gMobiClip_intra16_dispatch:
    .word MobiClip_Code_02092C78 - . + 0x114
    .word MobiClip_Code_02092CC8 - . + 0x118
    .word MobiClip_Code_02092C8C - . + 0x11c
    .word MobiClip_Code_02092CEC - . + 0x120
    .size gMobiClip_chroma_narrow_kernel_dispatch, . - gMobiClip_chroma_narrow_kernel_dispatch
MobiClip_Code_0208D044:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208D048:
    bl MobiClip_Code_0208E93C
MobiClip_Code_0208D04C:
    mov r5, r6
MobiClip_Code_0208D050:
    bl MobiClip_Code_0208E93C
MobiClip_Code_0208D054:
    add sb, r0, #0x3bc
MobiClip_Code_0208D058:
    ldm sb, {r7, r8}
MobiClip_Code_0208D05C:
    add r5, r5, r7
MobiClip_Code_0208D060:
    add r6, r6, r8
MobiClip_Code_0208D064:
    stm r4, {r5, r6}
MobiClip_Code_0208D068:
    add r7, r5, fp, lsl #1
MobiClip_Code_0208D06C:
    and r7, r7, #3
MobiClip_Code_0208D070:
    and r8, r6, #1
MobiClip_Code_0208D074:
    add r7, r7, r8, lsl #2
MobiClip_Code_0208D078:
    push {r0, r1, r2, r3}
MobiClip_Code_0208D07C:
    ldr r2, [sp, #0x14]
MobiClip_Code_0208D080:
    ldr r1, [r0, #0xc]
MobiClip_Code_0208D084:
    add r0, r0, r2
MobiClip_Code_0208D088:
    ldr r0, [r0, #0xc]
MobiClip_Code_0208D08C:
    asr r8, r6, #1
MobiClip_Code_0208D090:
    add r0, r0, fp
MobiClip_Code_0208D094:
    add r0, r0, r8, lsl #8
MobiClip_Code_0208D098:
    add r0, r0, r5, asr #1
MobiClip_Code_0208D09C:
    add r1, r1, fp
MobiClip_Code_0208D0A0:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208D0A4:
    sub r3, pc, #0x2b0
MobiClip_Code_0208D0A8:
    add lr, pc, #4
MobiClip_Code_0208D0AC:
    ldr r8, [r3, r7, lsl #2]
MobiClip_Code_0208D0B0:
    add pc, r8, r3
MobiClip_Code_0208D0B4:
    ldr r0, [sp]
MobiClip_Code_0208D0B8:
    ldr r2, [sp, #0x14]
MobiClip_Code_0208D0BC:
    ldr r1, [r0, #0x24]
MobiClip_Code_0208D0C0:
    add r0, r0, r2
MobiClip_Code_0208D0C4:
    ldr r0, [r0, #0x24]
MobiClip_Code_0208D0C8:
    asr r8, r6, #2
MobiClip_Code_0208D0CC:
    add r0, r0, fp, lsr #1
MobiClip_Code_0208D0D0:
    add r0, r0, r8, lsl #8
MobiClip_Code_0208D0D4:
    add r0, r0, r5, asr #2
MobiClip_Code_0208D0D8:
    add r1, r1, fp, lsr #1
MobiClip_Code_0208D0DC:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208D0E0:
    lsr r2, r2, #1
MobiClip_Code_0208D0E4:
    sub r3, pc, #0xb8
MobiClip_Code_0208D0E8:
    add r5, r5, fp, lsl #1
MobiClip_Code_0208D0EC:
    asr r5, r5, #1
MobiClip_Code_0208D0F0:
    and r5, r5, #1
MobiClip_Code_0208D0F4:
    asr r8, r6, #1
MobiClip_Code_0208D0F8:
    and r8, r8, #1
MobiClip_Code_0208D0FC:
    add r5, r5, r8, lsl #1
MobiClip_Code_0208D100:
    add lr, pc, #8
MobiClip_Code_0208D104:
    mov r6, r0
MobiClip_Code_0208D108:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_0208D10C:
    add pc, r8, r3
MobiClip_Code_0208D110:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208D114:
    lsr r2, r2, #1
MobiClip_Code_0208D118:
    add r0, r6, #0x80
MobiClip_Code_0208D11C:
    sub r1, r1, r2, lsl #8
MobiClip_Code_0208D120:
    add r1, r1, #0x80
MobiClip_Code_0208D124:
    sub r3, pc, #0xf8
MobiClip_Code_0208D128:
    add lr, pc, #4
MobiClip_Code_0208D12C:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_0208D130:
    add pc, r8, r3
MobiClip_Code_0208D134:
    pop {r0, r1, r2, r3, r4, r5, r6, fp, ip, pc}
    /* control metadata 0x0208d138..0x0208d194 */
    .global gMobiClip_intra16_selector_and_offsets
    .type gMobiClip_intra16_selector_and_offsets, %object
gMobiClip_intra16_selector_and_offsets:
    /* intra16_selectors */
    .byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
    .byte 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x08, 0x05, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00
    /* intra16_modes_a */
    .global gMobiClip_intra16_modes_a
gMobiClip_intra16_modes_a:
    .word MobiClip_Code_0208D194 - .
    .word MobiClip_Code_0208D1AC - . + 0x4
    .word MobiClip_Code_0208D1C0 - . + 0x8
    .word MobiClip_Code_0208D1D4 - . + 0xc
    .word MobiClip_Code_0208D1E8 - . + 0x10
    .word MobiClip_Code_0208D1FC - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208D210 - . + 0x20
    .word 0 /* reserved */
    /* intra16_code_lengths */
    .byte 0x03, 0x01, 0x03, 0x03, 0x04, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00
    .size gMobiClip_intra16_selector_and_offsets, . - gMobiClip_intra16_selector_and_offsets
MobiClip_Code_0208D194:
    mov r5, #4
MobiClip_Code_0208D198:
    mov r6, #0x10
MobiClip_Code_0208D19C:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208D1A0:
    add sb, r0, #0x3bc
MobiClip_Code_0208D1A4:
    ldm sb, {r5, r6}
MobiClip_Code_0208D1A8:
    b MobiClip_Code_0208D064
MobiClip_Code_0208D1AC:
    str lr, [sp, #-4]!
MobiClip_Code_0208D1B0:
    mov r5, #4
MobiClip_Code_0208D1B4:
    mov r6, #0x10
MobiClip_Code_0208D1B8:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208D1BC:
    pop {pc}
MobiClip_Code_0208D1C0:
    str lr, [sp, #-4]!
MobiClip_Code_0208D1C4:
    mov r5, #8
MobiClip_Code_0208D1C8:
    mov r6, #0x10
MobiClip_Code_0208D1CC:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208D1D0:
    pop {pc}
MobiClip_Code_0208D1D4:
    str lr, [sp, #-4]!
MobiClip_Code_0208D1D8:
    mov r5, #0xc
MobiClip_Code_0208D1DC:
    mov r6, #0x10
MobiClip_Code_0208D1E0:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208D1E4:
    pop {pc}
MobiClip_Code_0208D1E8:
    str lr, [sp, #-4]!
MobiClip_Code_0208D1EC:
    mov r5, #0x10
MobiClip_Code_0208D1F0:
    mov r6, #0x10
MobiClip_Code_0208D1F4:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208D1F8:
    pop {pc}
MobiClip_Code_0208D1FC:
    str lr, [sp, #-4]!
MobiClip_Code_0208D200:
    mov r5, #0x14
MobiClip_Code_0208D204:
    mov r6, #0x10
MobiClip_Code_0208D208:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208D20C:
    pop {pc}
MobiClip_Code_0208D210:
    str lr, [sp, #-4]!
MobiClip_Code_0208D214:
    bl MobiClip_Code_0208DD78
MobiClip_Code_0208D218:
    add fp, fp, #0x800
MobiClip_Code_0208D21C:
    bl MobiClip_Code_0208DD78
MobiClip_Code_0208D220:
    sub fp, fp, #0x800
MobiClip_Code_0208D224:
    pop {pc}
MobiClip_Code_0208D228:
    lsr r6, r3, #0x1b
MobiClip_Code_0208D22C:
    sub r5, pc, #0xfc
MobiClip_Code_0208D230:
    ldrb r5, [r5, r6]
MobiClip_Code_0208D234:
    sub r6, pc, #0xbc
MobiClip_Code_0208D238:
    ldrb r6, [r6, r5]
MobiClip_Code_0208D23C:
    lsl r3, r3, r6
MobiClip_Code_0208D240:
    subs r2, r2, r6
MobiClip_Code_0208D244:
    mov r8, lr
MobiClip_Code_0208D248:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208D24C:
    sub r6, pc, #0xfc
MobiClip_Code_0208D250:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208D254:
    mov lr, r8
MobiClip_Code_0208D258:
    add pc, r5, r6
    /* control metadata 0x0208d25c..0x0208d2a0 */
    .global gMobiClip_motion8x8_selector_and_offsets
    .type gMobiClip_motion8x8_selector_and_offsets, %object
gMobiClip_motion8x8_selector_and_offsets:
    /* motion8x8_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x08, 0x08, 0x02, 0x02, 0x03, 0x09, 0x01, 0x01, 0x01, 0x01
    /* intra16_modes_b */
    .global gMobiClip_intra16_modes_b
gMobiClip_intra16_modes_b:
    .word MobiClip_Code_0208D2A0 - .
    .word MobiClip_Code_0208D2B8 - . + 0x4
    .word MobiClip_Code_0208D2CC - . + 0x8
    .word MobiClip_Code_0208D2E0 - . + 0xc
    .word MobiClip_Code_0208D2F4 - . + 0x10
    .word MobiClip_Code_0208D308 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208D31C - . + 0x20
    .word MobiClip_Code_0208D334 - . + 0x24
    /* motion8x8_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x04, 0x04, 0x04, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00
    .size gMobiClip_motion8x8_selector_and_offsets, . - gMobiClip_motion8x8_selector_and_offsets
MobiClip_Code_0208D2A0:
    mov r5, #4
MobiClip_Code_0208D2A4:
    mov r6, #8
MobiClip_Code_0208D2A8:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208D2AC:
    add sb, r0, #0x3bc
MobiClip_Code_0208D2B0:
    ldm sb, {r5, r6}
MobiClip_Code_0208D2B4:
    b MobiClip_Code_0208C970
MobiClip_Code_0208D2B8:
    str lr, [sp, #-4]!
MobiClip_Code_0208D2BC:
    mov r5, #4
MobiClip_Code_0208D2C0:
    mov r6, #8
MobiClip_Code_0208D2C4:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D2C8:
    pop {pc}
MobiClip_Code_0208D2CC:
    str lr, [sp, #-4]!
MobiClip_Code_0208D2D0:
    mov r5, #8
MobiClip_Code_0208D2D4:
    mov r6, #8
MobiClip_Code_0208D2D8:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D2DC:
    pop {pc}
MobiClip_Code_0208D2E0:
    str lr, [sp, #-4]!
MobiClip_Code_0208D2E4:
    mov r5, #0xc
MobiClip_Code_0208D2E8:
    mov r6, #8
MobiClip_Code_0208D2EC:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D2F0:
    pop {pc}
MobiClip_Code_0208D2F4:
    str lr, [sp, #-4]!
MobiClip_Code_0208D2F8:
    mov r5, #0x10
MobiClip_Code_0208D2FC:
    mov r6, #8
MobiClip_Code_0208D300:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D304:
    pop {pc}
MobiClip_Code_0208D308:
    str lr, [sp, #-4]!
MobiClip_Code_0208D30C:
    mov r5, #0x14
MobiClip_Code_0208D310:
    mov r6, #8
MobiClip_Code_0208D314:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D318:
    pop {pc}
MobiClip_Code_0208D31C:
    str lr, [sp, #-4]!
MobiClip_Code_0208D320:
    bl MobiClip_Code_0208D470
MobiClip_Code_0208D324:
    add fp, fp, #0x400
MobiClip_Code_0208D328:
    bl MobiClip_Code_0208D470
MobiClip_Code_0208D32C:
    sub fp, fp, #0x400
MobiClip_Code_0208D330:
    pop {pc}
MobiClip_Code_0208D334:
    str lr, [sp, #-4]!
MobiClip_Code_0208D338:
    bl MobiClip_Code_0208D6A0
MobiClip_Code_0208D33C:
    add fp, fp, #8
MobiClip_Code_0208D340:
    bl MobiClip_Code_0208D6A0
MobiClip_Code_0208D344:
    sub fp, fp, #8
MobiClip_Code_0208D348:
    pop {pc}
MobiClip_Code_0208D34C:
    lsr r6, r3, #0x1c
MobiClip_Code_0208D350:
    sub r5, pc, #0xfc
MobiClip_Code_0208D354:
    ldrb r5, [r5, r6]
MobiClip_Code_0208D358:
    sub r6, pc, #0xcc
MobiClip_Code_0208D35C:
    ldrb r6, [r6, r5]
MobiClip_Code_0208D360:
    lsl r3, r3, r6
MobiClip_Code_0208D364:
    subs r2, r2, r6
MobiClip_Code_0208D368:
    mov r8, lr
MobiClip_Code_0208D36C:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208D370:
    sub r6, pc, #0x10c
MobiClip_Code_0208D374:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208D378:
    mov lr, r8
MobiClip_Code_0208D37C:
    add pc, r5, r6
    /* control metadata 0x0208d380..0x0208d3c4 */
    .global gMobiClip_motion16x4_selector_and_offsets
    .type gMobiClip_motion16x4_selector_and_offsets, %object
gMobiClip_motion16x4_selector_and_offsets:
    /* motion16x4_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x08, 0x04, 0x02, 0x02, 0x05, 0x09, 0x01, 0x01, 0x01, 0x01
    /* motion16x8_modes_a */
    .global gMobiClip_motion16x8_modes_a
gMobiClip_motion16x8_modes_a:
    .word MobiClip_Code_0208D3C4 - .
    .word MobiClip_Code_0208D3DC - . + 0x4
    .word MobiClip_Code_0208D3F0 - . + 0x8
    .word MobiClip_Code_0208D404 - . + 0xc
    .word MobiClip_Code_0208D418 - . + 0x10
    .word MobiClip_Code_0208D42C - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208D440 - . + 0x20
    .word MobiClip_Code_0208D458 - . + 0x24
    /* motion16x4_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00
    .size gMobiClip_motion16x4_selector_and_offsets, . - gMobiClip_motion16x4_selector_and_offsets
MobiClip_Code_0208D3C4:
    mov r5, #4
MobiClip_Code_0208D3C8:
    mov r6, #4
MobiClip_Code_0208D3CC:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208D3D0:
    add sb, r0, #0x3bc
MobiClip_Code_0208D3D4:
    ldm sb, {r5, r6}
MobiClip_Code_0208D3D8:
    b MobiClip_Code_0208C970
MobiClip_Code_0208D3DC:
    str lr, [sp, #-4]!
MobiClip_Code_0208D3E0:
    mov r5, #4
MobiClip_Code_0208D3E4:
    mov r6, #4
MobiClip_Code_0208D3E8:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D3EC:
    pop {pc}
MobiClip_Code_0208D3F0:
    str lr, [sp, #-4]!
MobiClip_Code_0208D3F4:
    mov r5, #8
MobiClip_Code_0208D3F8:
    mov r6, #4
MobiClip_Code_0208D3FC:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D400:
    pop {pc}
MobiClip_Code_0208D404:
    str lr, [sp, #-4]!
MobiClip_Code_0208D408:
    mov r5, #0xc
MobiClip_Code_0208D40C:
    mov r6, #4
MobiClip_Code_0208D410:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D414:
    pop {pc}
MobiClip_Code_0208D418:
    str lr, [sp, #-4]!
MobiClip_Code_0208D41C:
    mov r5, #0x10
MobiClip_Code_0208D420:
    mov r6, #4
MobiClip_Code_0208D424:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D428:
    pop {pc}
MobiClip_Code_0208D42C:
    str lr, [sp, #-4]!
MobiClip_Code_0208D430:
    mov r5, #0x14
MobiClip_Code_0208D434:
    mov r6, #4
MobiClip_Code_0208D438:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D43C:
    pop {pc}
MobiClip_Code_0208D440:
    str lr, [sp, #-4]!
MobiClip_Code_0208D444:
    bl MobiClip_Code_0208D57C
MobiClip_Code_0208D448:
    add fp, fp, #0x200
MobiClip_Code_0208D44C:
    bl MobiClip_Code_0208D57C
MobiClip_Code_0208D450:
    sub fp, fp, #0x200
MobiClip_Code_0208D454:
    pop {pc}
MobiClip_Code_0208D458:
    str lr, [sp, #-4]!
MobiClip_Code_0208D45C:
    bl MobiClip_Code_0208D7C4
MobiClip_Code_0208D460:
    add fp, fp, #8
MobiClip_Code_0208D464:
    bl MobiClip_Code_0208D7C4
MobiClip_Code_0208D468:
    sub fp, fp, #8
MobiClip_Code_0208D46C:
    pop {pc}
MobiClip_Code_0208D470:
    lsr r6, r3, #0x1c
MobiClip_Code_0208D474:
    sub r5, pc, #0xfc
MobiClip_Code_0208D478:
    ldrb r5, [r5, r6]
MobiClip_Code_0208D47C:
    sub r6, pc, #0xcc
MobiClip_Code_0208D480:
    ldrb r6, [r6, r5]
MobiClip_Code_0208D484:
    lsl r3, r3, r6
MobiClip_Code_0208D488:
    subs r2, r2, r6
MobiClip_Code_0208D48C:
    mov r8, lr
MobiClip_Code_0208D490:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208D494:
    sub r6, pc, #0x10c
MobiClip_Code_0208D498:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208D49C:
    mov lr, r8
MobiClip_Code_0208D4A0:
    add pc, r5, r6
    /* control metadata 0x0208d4a4..0x0208d4e8 */
    .global gMobiClip_motion16x2_selector_and_offsets
    .type gMobiClip_motion16x2_selector_and_offsets, %object
gMobiClip_motion16x2_selector_and_offsets:
    /* motion16x2_selectors */
    .byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x09, 0x04, 0x02, 0x02, 0x00, 0x00, 0x05, 0x03
    /* motion16x8_modes_b */
    .global gMobiClip_motion16x8_modes_b
gMobiClip_motion16x8_modes_b:
    .word MobiClip_Code_0208D4E8 - .
    .word MobiClip_Code_0208D500 - . + 0x4
    .word MobiClip_Code_0208D514 - . + 0x8
    .word MobiClip_Code_0208D528 - . + 0xc
    .word MobiClip_Code_0208D53C - . + 0x10
    .word MobiClip_Code_0208D550 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208D564 - . + 0x24
    /* motion16x2_code_lengths */
    .byte 0x03, 0x01, 0x03, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00
    .size gMobiClip_motion16x2_selector_and_offsets, . - gMobiClip_motion16x2_selector_and_offsets
MobiClip_Code_0208D4E8:
    mov r5, #4
MobiClip_Code_0208D4EC:
    mov r6, #2
MobiClip_Code_0208D4F0:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208D4F4:
    add sb, r0, #0x3bc
MobiClip_Code_0208D4F8:
    ldm sb, {r5, r6}
MobiClip_Code_0208D4FC:
    b MobiClip_Code_0208C970
MobiClip_Code_0208D500:
    str lr, [sp, #-4]!
MobiClip_Code_0208D504:
    mov r5, #4
MobiClip_Code_0208D508:
    mov r6, #2
MobiClip_Code_0208D50C:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D510:
    pop {pc}
MobiClip_Code_0208D514:
    str lr, [sp, #-4]!
MobiClip_Code_0208D518:
    mov r5, #8
MobiClip_Code_0208D51C:
    mov r6, #2
MobiClip_Code_0208D520:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D524:
    pop {pc}
MobiClip_Code_0208D528:
    str lr, [sp, #-4]!
MobiClip_Code_0208D52C:
    mov r5, #0xc
MobiClip_Code_0208D530:
    mov r6, #2
MobiClip_Code_0208D534:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D538:
    pop {pc}
MobiClip_Code_0208D53C:
    str lr, [sp, #-4]!
MobiClip_Code_0208D540:
    mov r5, #0x10
MobiClip_Code_0208D544:
    mov r6, #2
MobiClip_Code_0208D548:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D54C:
    pop {pc}
MobiClip_Code_0208D550:
    str lr, [sp, #-4]!
MobiClip_Code_0208D554:
    mov r5, #0x14
MobiClip_Code_0208D558:
    mov r6, #2
MobiClip_Code_0208D55C:
    bl MobiClip_Code_0208C950
MobiClip_Code_0208D560:
    pop {pc}
MobiClip_Code_0208D564:
    str lr, [sp, #-4]!
MobiClip_Code_0208D568:
    bl MobiClip_Code_0208D8D0
MobiClip_Code_0208D56C:
    add fp, fp, #8
MobiClip_Code_0208D570:
    bl MobiClip_Code_0208D8D0
MobiClip_Code_0208D574:
    sub fp, fp, #8
MobiClip_Code_0208D578:
    pop {pc}
MobiClip_Code_0208D57C:
    lsr r6, r3, #0x1c
MobiClip_Code_0208D580:
    sub r5, pc, #0xe4
MobiClip_Code_0208D584:
    ldrb r5, [r5, r6]
MobiClip_Code_0208D588:
    sub r6, pc, #0xb4
MobiClip_Code_0208D58C:
    ldrb r6, [r6, r5]
MobiClip_Code_0208D590:
    lsl r3, r3, r6
MobiClip_Code_0208D594:
    subs r2, r2, r6
MobiClip_Code_0208D598:
    mov r8, lr
MobiClip_Code_0208D59C:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208D5A0:
    sub r6, pc, #0xf4
MobiClip_Code_0208D5A4:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208D5A8:
    mov lr, r8
MobiClip_Code_0208D5AC:
    add pc, r5, r6
    /* control metadata 0x0208d5b0..0x0208d5f4 */
    .global gMobiClip_motion8x8_alt_selector_and_offsets
    .type gMobiClip_motion8x8_alt_selector_and_offsets, %object
gMobiClip_motion8x8_alt_selector_and_offsets:
    /* motion8x8_alt_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x05, 0x09, 0x04, 0x08, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01
    /* motion16x8_modes_c */
    .global gMobiClip_motion16x8_modes_c
gMobiClip_motion16x8_modes_c:
    .word MobiClip_Code_0208D5F4 - .
    .word MobiClip_Code_0208D60C - . + 0x4
    .word MobiClip_Code_0208D620 - . + 0x8
    .word MobiClip_Code_0208D634 - . + 0xc
    .word MobiClip_Code_0208D648 - . + 0x10
    .word MobiClip_Code_0208D65C - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208D670 - . + 0x20
    .word MobiClip_Code_0208D688 - . + 0x24
    /* motion8x8_alt_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00
    .size gMobiClip_motion8x8_alt_selector_and_offsets, . - gMobiClip_motion8x8_alt_selector_and_offsets
MobiClip_Code_0208D5F4:
    mov r5, #4
MobiClip_Code_0208D5F8:
    mov r6, #8
MobiClip_Code_0208D5FC:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208D600:
    add sb, r0, #0x3bc
MobiClip_Code_0208D604:
    ldm sb, {r5, r6}
MobiClip_Code_0208D608:
    b MobiClip_Code_0208CC04
MobiClip_Code_0208D60C:
    str lr, [sp, #-4]!
MobiClip_Code_0208D610:
    mov r5, #4
MobiClip_Code_0208D614:
    mov r6, #8
MobiClip_Code_0208D618:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D61C:
    pop {pc}
MobiClip_Code_0208D620:
    str lr, [sp, #-4]!
MobiClip_Code_0208D624:
    mov r5, #8
MobiClip_Code_0208D628:
    mov r6, #8
MobiClip_Code_0208D62C:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D630:
    pop {pc}
MobiClip_Code_0208D634:
    str lr, [sp, #-4]!
MobiClip_Code_0208D638:
    mov r5, #0xc
MobiClip_Code_0208D63C:
    mov r6, #8
MobiClip_Code_0208D640:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D644:
    pop {pc}
MobiClip_Code_0208D648:
    str lr, [sp, #-4]!
MobiClip_Code_0208D64C:
    mov r5, #0x10
MobiClip_Code_0208D650:
    mov r6, #8
MobiClip_Code_0208D654:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D658:
    pop {pc}
MobiClip_Code_0208D65C:
    str lr, [sp, #-4]!
MobiClip_Code_0208D660:
    mov r5, #0x14
MobiClip_Code_0208D664:
    mov r6, #8
MobiClip_Code_0208D668:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D66C:
    pop {pc}
MobiClip_Code_0208D670:
    str lr, [sp, #-4]!
MobiClip_Code_0208D674:
    bl MobiClip_Code_0208D7C4
MobiClip_Code_0208D678:
    add fp, fp, #0x400
MobiClip_Code_0208D67C:
    bl MobiClip_Code_0208D7C4
MobiClip_Code_0208D680:
    sub fp, fp, #0x400
MobiClip_Code_0208D684:
    pop {pc}
MobiClip_Code_0208D688:
    str lr, [sp, #-4]!
MobiClip_Code_0208D68C:
    bl MobiClip_Code_0208DA00
MobiClip_Code_0208D690:
    add fp, fp, #4
MobiClip_Code_0208D694:
    bl MobiClip_Code_0208DA00
MobiClip_Code_0208D698:
    sub fp, fp, #4
MobiClip_Code_0208D69C:
    pop {pc}
MobiClip_Code_0208D6A0:
    lsr r6, r3, #0x1c
MobiClip_Code_0208D6A4:
    sub r5, pc, #0xfc
MobiClip_Code_0208D6A8:
    ldrb r5, [r5, r6]
MobiClip_Code_0208D6AC:
    sub r6, pc, #0xcc
MobiClip_Code_0208D6B0:
    ldrb r6, [r6, r5]
MobiClip_Code_0208D6B4:
    lsl r3, r3, r6
MobiClip_Code_0208D6B8:
    subs r2, r2, r6
MobiClip_Code_0208D6BC:
    mov r8, lr
MobiClip_Code_0208D6C0:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208D6C4:
    sub r6, pc, #0x10c
MobiClip_Code_0208D6C8:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208D6CC:
    mov lr, r8
MobiClip_Code_0208D6D0:
    add pc, r5, r6
    /* control metadata 0x0208d6d4..0x0208d718 */
    .global gMobiClip_predicted_mode_a_selector_and_offsets
    .type gMobiClip_predicted_mode_a_selector_and_offsets, %object
gMobiClip_predicted_mode_a_selector_and_offsets:
    /* predicted_mode_a_selectors */
    .byte 0x02, 0x02, 0x02, 0x02, 0x08, 0x09, 0x03, 0x03, 0x05, 0x04, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_a */
    .global gMobiClip_predicted_intra_modes_a
gMobiClip_predicted_intra_modes_a:
    .word MobiClip_Code_0208D718 - .
    .word MobiClip_Code_0208D730 - . + 0x4
    .word MobiClip_Code_0208D744 - . + 0x8
    .word MobiClip_Code_0208D758 - . + 0xc
    .word MobiClip_Code_0208D76C - . + 0x10
    .word MobiClip_Code_0208D780 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208D794 - . + 0x20
    .word MobiClip_Code_0208D7AC - . + 0x24
    /* predicted_mode_a_code_lengths */
    .byte 0x03, 0x02, 0x02, 0x03, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00
    .size gMobiClip_predicted_mode_a_selector_and_offsets, . - gMobiClip_predicted_mode_a_selector_and_offsets
MobiClip_Code_0208D718:
    mov r5, #4
MobiClip_Code_0208D71C:
    mov r6, #4
MobiClip_Code_0208D720:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208D724:
    add sb, r0, #0x3bc
MobiClip_Code_0208D728:
    ldm sb, {r5, r6}
MobiClip_Code_0208D72C:
    b MobiClip_Code_0208CC04
MobiClip_Code_0208D730:
    str lr, [sp, #-4]!
MobiClip_Code_0208D734:
    mov r5, #4
MobiClip_Code_0208D738:
    mov r6, #4
MobiClip_Code_0208D73C:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D740:
    pop {pc}
MobiClip_Code_0208D744:
    str lr, [sp, #-4]!
MobiClip_Code_0208D748:
    mov r5, #8
MobiClip_Code_0208D74C:
    mov r6, #4
MobiClip_Code_0208D750:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D754:
    pop {pc}
MobiClip_Code_0208D758:
    str lr, [sp, #-4]!
MobiClip_Code_0208D75C:
    mov r5, #0xc
MobiClip_Code_0208D760:
    mov r6, #4
MobiClip_Code_0208D764:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D768:
    pop {pc}
MobiClip_Code_0208D76C:
    str lr, [sp, #-4]!
MobiClip_Code_0208D770:
    mov r5, #0x10
MobiClip_Code_0208D774:
    mov r6, #4
MobiClip_Code_0208D778:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D77C:
    pop {pc}
MobiClip_Code_0208D780:
    str lr, [sp, #-4]!
MobiClip_Code_0208D784:
    mov r5, #0x14
MobiClip_Code_0208D788:
    mov r6, #4
MobiClip_Code_0208D78C:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D790:
    pop {pc}
MobiClip_Code_0208D794:
    str lr, [sp, #-4]!
MobiClip_Code_0208D798:
    bl MobiClip_Code_0208D8D0
MobiClip_Code_0208D79C:
    add fp, fp, #0x200
MobiClip_Code_0208D7A0:
    bl MobiClip_Code_0208D8D0
MobiClip_Code_0208D7A4:
    sub fp, fp, #0x200
MobiClip_Code_0208D7A8:
    pop {pc}
MobiClip_Code_0208D7AC:
    str lr, [sp, #-4]!
MobiClip_Code_0208D7B0:
    bl MobiClip_Code_0208DB40
MobiClip_Code_0208D7B4:
    add fp, fp, #4
MobiClip_Code_0208D7B8:
    bl MobiClip_Code_0208DB40
MobiClip_Code_0208D7BC:
    sub fp, fp, #4
MobiClip_Code_0208D7C0:
    pop {pc}
MobiClip_Code_0208D7C4:
    lsr r6, r3, #0x1c
MobiClip_Code_0208D7C8:
    sub r5, pc, #0xfc
MobiClip_Code_0208D7CC:
    ldrb r5, [r5, r6]
MobiClip_Code_0208D7D0:
    sub r6, pc, #0xcc
MobiClip_Code_0208D7D4:
    ldrb r6, [r6, r5]
MobiClip_Code_0208D7D8:
    lsl r3, r3, r6
MobiClip_Code_0208D7DC:
    subs r2, r2, r6
MobiClip_Code_0208D7E0:
    mov r8, lr
MobiClip_Code_0208D7E4:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208D7E8:
    sub r6, pc, #0x10c
MobiClip_Code_0208D7EC:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208D7F0:
    mov lr, r8
MobiClip_Code_0208D7F4:
    add pc, r5, r6
    /* control metadata 0x0208d7f8..0x0208d83c */
    .global gMobiClip_predicted_mode_b_selector_and_offsets
    .type gMobiClip_predicted_mode_b_selector_and_offsets, %object
gMobiClip_predicted_mode_b_selector_and_offsets:
    /* predicted_mode_b_selectors */
    .byte 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x09, 0x05, 0x03, 0x03, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_b */
    .global gMobiClip_predicted_intra_modes_b
gMobiClip_predicted_intra_modes_b:
    .word MobiClip_Code_0208D83C - .
    .word MobiClip_Code_0208D854 - . + 0x4
    .word MobiClip_Code_0208D868 - . + 0x8
    .word MobiClip_Code_0208D87C - . + 0xc
    .word MobiClip_Code_0208D890 - . + 0x10
    .word MobiClip_Code_0208D8A4 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208D8B8 - . + 0x24
    /* predicted_mode_b_code_lengths */
    .byte 0x03, 0x02, 0x02, 0x03, 0x03, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00
    .size gMobiClip_predicted_mode_b_selector_and_offsets, . - gMobiClip_predicted_mode_b_selector_and_offsets
MobiClip_Code_0208D83C:
    mov r5, #4
MobiClip_Code_0208D840:
    mov r6, #2
MobiClip_Code_0208D844:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208D848:
    add sb, r0, #0x3bc
MobiClip_Code_0208D84C:
    ldm sb, {r5, r6}
MobiClip_Code_0208D850:
    b MobiClip_Code_0208CC04
MobiClip_Code_0208D854:
    str lr, [sp, #-4]!
MobiClip_Code_0208D858:
    mov r5, #4
MobiClip_Code_0208D85C:
    mov r6, #2
MobiClip_Code_0208D860:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D864:
    pop {pc}
MobiClip_Code_0208D868:
    str lr, [sp, #-4]!
MobiClip_Code_0208D86C:
    mov r5, #8
MobiClip_Code_0208D870:
    mov r6, #2
MobiClip_Code_0208D874:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D878:
    pop {pc}
MobiClip_Code_0208D87C:
    str lr, [sp, #-4]!
MobiClip_Code_0208D880:
    mov r5, #0xc
MobiClip_Code_0208D884:
    mov r6, #2
MobiClip_Code_0208D888:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D88C:
    pop {pc}
MobiClip_Code_0208D890:
    str lr, [sp, #-4]!
MobiClip_Code_0208D894:
    mov r5, #0x10
MobiClip_Code_0208D898:
    mov r6, #2
MobiClip_Code_0208D89C:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D8A0:
    pop {pc}
MobiClip_Code_0208D8A4:
    str lr, [sp, #-4]!
MobiClip_Code_0208D8A8:
    mov r5, #0x14
MobiClip_Code_0208D8AC:
    mov r6, #2
MobiClip_Code_0208D8B0:
    bl MobiClip_Code_0208CBE4
MobiClip_Code_0208D8B4:
    pop {pc}
MobiClip_Code_0208D8B8:
    str lr, [sp, #-4]!
MobiClip_Code_0208D8BC:
    bl MobiClip_Code_0208DC58
MobiClip_Code_0208D8C0:
    add fp, fp, #4
MobiClip_Code_0208D8C4:
    bl MobiClip_Code_0208DC58
MobiClip_Code_0208D8C8:
    sub fp, fp, #4
MobiClip_Code_0208D8CC:
    pop {pc}
MobiClip_Code_0208D8D0:
    lsr r6, r3, #0x1c
MobiClip_Code_0208D8D4:
    sub r5, pc, #0xe4
MobiClip_Code_0208D8D8:
    ldrb r5, [r5, r6]
MobiClip_Code_0208D8DC:
    sub r6, pc, #0xb4
MobiClip_Code_0208D8E0:
    ldrb r6, [r6, r5]
MobiClip_Code_0208D8E4:
    lsl r3, r3, r6
MobiClip_Code_0208D8E8:
    subs r2, r2, r6
MobiClip_Code_0208D8EC:
    mov r8, lr
MobiClip_Code_0208D8F0:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208D8F4:
    sub r6, pc, #0xf4
MobiClip_Code_0208D8F8:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208D8FC:
    mov lr, r8
MobiClip_Code_0208D900:
    add pc, r5, r6
    /* control metadata 0x0208d904..0x0208d954 */
    .global gMobiClip_predicted_mode_c_selector_and_offsets
    .type gMobiClip_predicted_mode_c_selector_and_offsets, %object
gMobiClip_predicted_mode_c_selector_and_offsets:
    /* predicted_mode_c_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x09, 0x05, 0x08, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_c */
    .global gMobiClip_predicted_intra_modes_c
gMobiClip_predicted_intra_modes_c:
    .word MobiClip_Code_0208D954 - .
    .word MobiClip_Code_0208D96C - . + 0x4
    .word MobiClip_Code_0208D980 - . + 0x8
    .word MobiClip_Code_0208D994 - . + 0xc
    .word MobiClip_Code_0208D9A8 - . + 0x10
    .word MobiClip_Code_0208D9BC - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208D9D0 - . + 0x20
    .word MobiClip_Code_0208D9E8 - . + 0x24
    /* predicted_mode_c_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .size gMobiClip_predicted_mode_c_selector_and_offsets, . - gMobiClip_predicted_mode_c_selector_and_offsets
MobiClip_Code_0208D954:
    mov r5, #4
MobiClip_Code_0208D958:
    mov r6, #8
MobiClip_Code_0208D95C:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208D960:
    add sb, r0, #0x3bc
MobiClip_Code_0208D964:
    ldm sb, {r5, r6}
MobiClip_Code_0208D968:
    b MobiClip_Code_0208CE3C
MobiClip_Code_0208D96C:
    str lr, [sp, #-4]!
MobiClip_Code_0208D970:
    mov r5, #4
MobiClip_Code_0208D974:
    mov r6, #8
MobiClip_Code_0208D978:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208D97C:
    pop {pc}
MobiClip_Code_0208D980:
    str lr, [sp, #-4]!
MobiClip_Code_0208D984:
    mov r5, #8
MobiClip_Code_0208D988:
    mov r6, #8
MobiClip_Code_0208D98C:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208D990:
    pop {pc}
MobiClip_Code_0208D994:
    str lr, [sp, #-4]!
MobiClip_Code_0208D998:
    mov r5, #0xc
MobiClip_Code_0208D99C:
    mov r6, #8
MobiClip_Code_0208D9A0:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208D9A4:
    pop {pc}
MobiClip_Code_0208D9A8:
    str lr, [sp, #-4]!
MobiClip_Code_0208D9AC:
    mov r5, #0x10
MobiClip_Code_0208D9B0:
    mov r6, #8
MobiClip_Code_0208D9B4:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208D9B8:
    pop {pc}
MobiClip_Code_0208D9BC:
    str lr, [sp, #-4]!
MobiClip_Code_0208D9C0:
    mov r5, #0x14
MobiClip_Code_0208D9C4:
    mov r6, #8
MobiClip_Code_0208D9C8:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208D9CC:
    pop {pc}
MobiClip_Code_0208D9D0:
    str lr, [sp, #-4]!
MobiClip_Code_0208D9D4:
    bl MobiClip_Code_0208DB40
MobiClip_Code_0208D9D8:
    add fp, fp, #0x400
MobiClip_Code_0208D9DC:
    bl MobiClip_Code_0208DB40
MobiClip_Code_0208D9E0:
    sub fp, fp, #0x400
MobiClip_Code_0208D9E4:
    pop {pc}
MobiClip_Code_0208D9E8:
    str lr, [sp, #-4]!
MobiClip_Code_0208D9EC:
    bl MobiClip_Code_0208DD78
MobiClip_Code_0208D9F0:
    add fp, fp, #2
MobiClip_Code_0208D9F4:
    bl MobiClip_Code_0208DD78
MobiClip_Code_0208D9F8:
    sub fp, fp, #2
MobiClip_Code_0208D9FC:
    pop {pc}
MobiClip_Code_0208DA00:
    lsr r6, r3, #0x1c
MobiClip_Code_0208DA04:
    sub r5, pc, #0x108
MobiClip_Code_0208DA08:
    ldrb r5, [r5, r6]
MobiClip_Code_0208DA0C:
    sub r6, pc, #0xd8
MobiClip_Code_0208DA10:
    ldrb r6, [r6, r5]
MobiClip_Code_0208DA14:
    lsl r3, r3, r6
MobiClip_Code_0208DA18:
    subs r2, r2, r6
MobiClip_Code_0208DA1C:
    mov r8, lr
MobiClip_Code_0208DA20:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208DA24:
    sub r6, pc, #0x118
MobiClip_Code_0208DA28:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208DA2C:
    mov lr, r8
MobiClip_Code_0208DA30:
    add pc, r5, r6
    /* control metadata 0x0208da34..0x0208da94 */
    .global gMobiClip_predicted_mode_d_selector_and_offsets
    .type gMobiClip_predicted_mode_d_selector_and_offsets, %object
gMobiClip_predicted_mode_d_selector_and_offsets:
    /* predicted_mode_d_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03
    .byte 0x08, 0x09, 0x05, 0x05, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_d */
    .global gMobiClip_predicted_intra_modes_d
gMobiClip_predicted_intra_modes_d:
    .word MobiClip_Code_0208DA94 - .
    .word MobiClip_Code_0208DAAC - . + 0x4
    .word MobiClip_Code_0208DAC0 - . + 0x8
    .word MobiClip_Code_0208DAD4 - . + 0xc
    .word MobiClip_Code_0208DAE8 - . + 0x10
    .word MobiClip_Code_0208DAFC - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208DB10 - . + 0x20
    .word MobiClip_Code_0208DB28 - . + 0x24
    /* predicted_mode_d_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x03, 0x04, 0x00, 0x00, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .size gMobiClip_predicted_mode_d_selector_and_offsets, . - gMobiClip_predicted_mode_d_selector_and_offsets
MobiClip_Code_0208DA94:
    mov r5, #4
MobiClip_Code_0208DA98:
    mov r6, #4
MobiClip_Code_0208DA9C:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208DAA0:
    add sb, r0, #0x3bc
MobiClip_Code_0208DAA4:
    ldm sb, {r5, r6}
MobiClip_Code_0208DAA8:
    b MobiClip_Code_0208CE3C
MobiClip_Code_0208DAAC:
    str lr, [sp, #-4]!
MobiClip_Code_0208DAB0:
    mov r5, #4
MobiClip_Code_0208DAB4:
    mov r6, #4
MobiClip_Code_0208DAB8:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208DABC:
    pop {pc}
MobiClip_Code_0208DAC0:
    str lr, [sp, #-4]!
MobiClip_Code_0208DAC4:
    mov r5, #8
MobiClip_Code_0208DAC8:
    mov r6, #4
MobiClip_Code_0208DACC:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208DAD0:
    pop {pc}
MobiClip_Code_0208DAD4:
    str lr, [sp, #-4]!
MobiClip_Code_0208DAD8:
    mov r5, #0xc
MobiClip_Code_0208DADC:
    mov r6, #4
MobiClip_Code_0208DAE0:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208DAE4:
    pop {pc}
MobiClip_Code_0208DAE8:
    str lr, [sp, #-4]!
MobiClip_Code_0208DAEC:
    mov r5, #0x10
MobiClip_Code_0208DAF0:
    mov r6, #4
MobiClip_Code_0208DAF4:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208DAF8:
    pop {pc}
MobiClip_Code_0208DAFC:
    str lr, [sp, #-4]!
MobiClip_Code_0208DB00:
    mov r5, #0x14
MobiClip_Code_0208DB04:
    mov r6, #4
MobiClip_Code_0208DB08:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208DB0C:
    pop {pc}
MobiClip_Code_0208DB10:
    str lr, [sp, #-4]!
MobiClip_Code_0208DB14:
    bl MobiClip_Code_0208DC58
MobiClip_Code_0208DB18:
    add fp, fp, #0x200
MobiClip_Code_0208DB1C:
    bl MobiClip_Code_0208DC58
MobiClip_Code_0208DB20:
    sub fp, fp, #0x200
MobiClip_Code_0208DB24:
    pop {pc}
MobiClip_Code_0208DB28:
    str lr, [sp, #-4]!
MobiClip_Code_0208DB2C:
    bl MobiClip_Code_0208DE88
MobiClip_Code_0208DB30:
    add fp, fp, #2
MobiClip_Code_0208DB34:
    bl MobiClip_Code_0208DE88
MobiClip_Code_0208DB38:
    sub fp, fp, #2
MobiClip_Code_0208DB3C:
    pop {pc}
MobiClip_Code_0208DB40:
    lsr r6, r3, #0x1b
MobiClip_Code_0208DB44:
    sub r5, pc, #0x118
MobiClip_Code_0208DB48:
    ldrb r5, [r5, r6]
MobiClip_Code_0208DB4C:
    sub r6, pc, #0xd8
MobiClip_Code_0208DB50:
    ldrb r6, [r6, r5]
MobiClip_Code_0208DB54:
    lsl r3, r3, r6
MobiClip_Code_0208DB58:
    subs r2, r2, r6
MobiClip_Code_0208DB5C:
    mov r8, lr
MobiClip_Code_0208DB60:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208DB64:
    sub r6, pc, #0x118
MobiClip_Code_0208DB68:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208DB6C:
    mov lr, r8
MobiClip_Code_0208DB70:
    add pc, r5, r6
    /* control metadata 0x0208db74..0x0208dbc4 */
    .global gMobiClip_predicted_mode_e_selector_and_offsets
    .type gMobiClip_predicted_mode_e_selector_and_offsets, %object
gMobiClip_predicted_mode_e_selector_and_offsets:
    /* predicted_mode_e_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x09, 0x05, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_e */
    .global gMobiClip_predicted_intra_modes_e
gMobiClip_predicted_intra_modes_e:
    .word MobiClip_Code_0208DBC4 - .
    .word MobiClip_Code_0208DBDC - . + 0x4
    .word MobiClip_Code_0208DBF0 - . + 0x8
    .word MobiClip_Code_0208DC04 - . + 0xc
    .word MobiClip_Code_0208DC18 - . + 0x10
    .word MobiClip_Code_0208DC2C - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208DC40 - . + 0x24
    /* predicted_mode_e_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x03, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .size gMobiClip_predicted_mode_e_selector_and_offsets, . - gMobiClip_predicted_mode_e_selector_and_offsets
MobiClip_Code_0208DBC4:
    mov r5, #4
MobiClip_Code_0208DBC8:
    mov r6, #2
MobiClip_Code_0208DBCC:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208DBD0:
    add sb, r0, #0x3bc
MobiClip_Code_0208DBD4:
    ldm sb, {r5, r6}
MobiClip_Code_0208DBD8:
    b MobiClip_Code_0208CE3C
MobiClip_Code_0208DBDC:
    str lr, [sp, #-4]!
MobiClip_Code_0208DBE0:
    mov r5, #4
MobiClip_Code_0208DBE4:
    mov r6, #2
MobiClip_Code_0208DBE8:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208DBEC:
    pop {pc}
MobiClip_Code_0208DBF0:
    str lr, [sp, #-4]!
MobiClip_Code_0208DBF4:
    mov r5, #8
MobiClip_Code_0208DBF8:
    mov r6, #2
MobiClip_Code_0208DBFC:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208DC00:
    pop {pc}
MobiClip_Code_0208DC04:
    str lr, [sp, #-4]!
MobiClip_Code_0208DC08:
    mov r5, #0xc
MobiClip_Code_0208DC0C:
    mov r6, #2
MobiClip_Code_0208DC10:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208DC14:
    pop {pc}
MobiClip_Code_0208DC18:
    str lr, [sp, #-4]!
MobiClip_Code_0208DC1C:
    mov r5, #0x10
MobiClip_Code_0208DC20:
    mov r6, #2
MobiClip_Code_0208DC24:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208DC28:
    pop {pc}
MobiClip_Code_0208DC2C:
    str lr, [sp, #-4]!
MobiClip_Code_0208DC30:
    mov r5, #0x14
MobiClip_Code_0208DC34:
    mov r6, #2
MobiClip_Code_0208DC38:
    bl MobiClip_Code_0208CE1C
MobiClip_Code_0208DC3C:
    pop {pc}
MobiClip_Code_0208DC40:
    str lr, [sp, #-4]!
MobiClip_Code_0208DC44:
    bl MobiClip_Code_0208DF80
MobiClip_Code_0208DC48:
    add fp, fp, #2
MobiClip_Code_0208DC4C:
    bl MobiClip_Code_0208DF80
MobiClip_Code_0208DC50:
    sub fp, fp, #2
MobiClip_Code_0208DC54:
    pop {pc}
MobiClip_Code_0208DC58:
    lsr r6, r3, #0x1c
MobiClip_Code_0208DC5C:
    sub r5, pc, #0xf0
MobiClip_Code_0208DC60:
    ldrb r5, [r5, r6]
MobiClip_Code_0208DC64:
    sub r6, pc, #0xc0
MobiClip_Code_0208DC68:
    ldrb r6, [r6, r5]
MobiClip_Code_0208DC6C:
    lsl r3, r3, r6
MobiClip_Code_0208DC70:
    subs r2, r2, r6
MobiClip_Code_0208DC74:
    mov r8, lr
MobiClip_Code_0208DC78:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208DC7C:
    sub r6, pc, #0x100
MobiClip_Code_0208DC80:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208DC84:
    mov lr, r8
MobiClip_Code_0208DC88:
    add pc, r5, r6
    /* control metadata 0x0208dc8c..0x0208dce4 */
    .global gMobiClip_predicted_mode_f_selector_and_offsets
    .type gMobiClip_predicted_mode_f_selector_and_offsets, %object
gMobiClip_predicted_mode_f_selector_and_offsets:
    /* predicted_mode_f_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02
    .byte 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x08, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_f */
    .global gMobiClip_predicted_intra_modes_f
gMobiClip_predicted_intra_modes_f:
    .word MobiClip_Code_0208DCE4 - .
    .word MobiClip_Code_0208DCFC - . + 0x4
    .word MobiClip_Code_0208DD10 - . + 0x8
    .word MobiClip_Code_0208DD24 - . + 0xc
    .word MobiClip_Code_0208DD38 - . + 0x10
    .word MobiClip_Code_0208DD4C - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208DD60 - . + 0x20
    .word 0 /* reserved */
    /* predicted_mode_f_code_lengths */
    .byte 0x02, 0x02, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .size gMobiClip_predicted_mode_f_selector_and_offsets, . - gMobiClip_predicted_mode_f_selector_and_offsets
MobiClip_Code_0208DCE4:
    mov r5, #4
MobiClip_Code_0208DCE8:
    mov r6, #8
MobiClip_Code_0208DCEC:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208DCF0:
    add sb, r0, #0x3bc
MobiClip_Code_0208DCF4:
    ldm sb, {r5, r6}
MobiClip_Code_0208DCF8:
    b MobiClip_Code_0208D064
MobiClip_Code_0208DCFC:
    str lr, [sp, #-4]!
MobiClip_Code_0208DD00:
    mov r5, #4
MobiClip_Code_0208DD04:
    mov r6, #8
MobiClip_Code_0208DD08:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DD0C:
    pop {pc}
MobiClip_Code_0208DD10:
    str lr, [sp, #-4]!
MobiClip_Code_0208DD14:
    mov r5, #8
MobiClip_Code_0208DD18:
    mov r6, #8
MobiClip_Code_0208DD1C:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DD20:
    pop {pc}
MobiClip_Code_0208DD24:
    str lr, [sp, #-4]!
MobiClip_Code_0208DD28:
    mov r5, #0xc
MobiClip_Code_0208DD2C:
    mov r6, #8
MobiClip_Code_0208DD30:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DD34:
    pop {pc}
MobiClip_Code_0208DD38:
    str lr, [sp, #-4]!
MobiClip_Code_0208DD3C:
    mov r5, #0x10
MobiClip_Code_0208DD40:
    mov r6, #8
MobiClip_Code_0208DD44:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DD48:
    pop {pc}
MobiClip_Code_0208DD4C:
    str lr, [sp, #-4]!
MobiClip_Code_0208DD50:
    mov r5, #0x14
MobiClip_Code_0208DD54:
    mov r6, #8
MobiClip_Code_0208DD58:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DD5C:
    pop {pc}
MobiClip_Code_0208DD60:
    str lr, [sp, #-4]!
MobiClip_Code_0208DD64:
    bl MobiClip_Code_0208DE88
MobiClip_Code_0208DD68:
    add fp, fp, #0x400
MobiClip_Code_0208DD6C:
    bl MobiClip_Code_0208DE88
MobiClip_Code_0208DD70:
    sub fp, fp, #0x400
MobiClip_Code_0208DD74:
    pop {pc}
MobiClip_Code_0208DD78:
    lsr r6, r3, #0x1b
MobiClip_Code_0208DD7C:
    sub r5, pc, #0xf8
MobiClip_Code_0208DD80:
    ldrb r5, [r5, r6]
MobiClip_Code_0208DD84:
    sub r6, pc, #0xb8
MobiClip_Code_0208DD88:
    ldrb r6, [r6, r5]
MobiClip_Code_0208DD8C:
    lsl r3, r3, r6
MobiClip_Code_0208DD90:
    subs r2, r2, r6
MobiClip_Code_0208DD94:
    mov r8, lr
MobiClip_Code_0208DD98:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208DD9C:
    sub r6, pc, #0xf8
MobiClip_Code_0208DDA0:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208DDA4:
    mov lr, r8
MobiClip_Code_0208DDA8:
    add pc, r5, r6
    /* control metadata 0x0208ddac..0x0208ddf4 */
    .global gMobiClip_predicted_mode_g_selector_and_offsets
    .type gMobiClip_predicted_mode_g_selector_and_offsets, %object
gMobiClip_predicted_mode_g_selector_and_offsets:
    /* predicted_mode_g_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x08, 0x05, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_g */
    .global gMobiClip_predicted_intra_modes_g
gMobiClip_predicted_intra_modes_g:
    .word MobiClip_Code_0208DDF4 - .
    .word MobiClip_Code_0208DE0C - . + 0x4
    .word MobiClip_Code_0208DE20 - . + 0x8
    .word MobiClip_Code_0208DE34 - . + 0xc
    .word MobiClip_Code_0208DE48 - . + 0x10
    .word MobiClip_Code_0208DE5C - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_0208DE70 - . + 0x20
    .word 0 /* reserved */
    /* predicted_mode_g_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x03, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .size gMobiClip_predicted_mode_g_selector_and_offsets, . - gMobiClip_predicted_mode_g_selector_and_offsets
MobiClip_Code_0208DDF4:
    mov r5, #4
MobiClip_Code_0208DDF8:
    mov r6, #4
MobiClip_Code_0208DDFC:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208DE00:
    add sb, r0, #0x3bc
MobiClip_Code_0208DE04:
    ldm sb, {r5, r6}
MobiClip_Code_0208DE08:
    b MobiClip_Code_0208D064
MobiClip_Code_0208DE0C:
    str lr, [sp, #-4]!
MobiClip_Code_0208DE10:
    mov r5, #4
MobiClip_Code_0208DE14:
    mov r6, #4
MobiClip_Code_0208DE18:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DE1C:
    pop {pc}
MobiClip_Code_0208DE20:
    str lr, [sp, #-4]!
MobiClip_Code_0208DE24:
    mov r5, #8
MobiClip_Code_0208DE28:
    mov r6, #4
MobiClip_Code_0208DE2C:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DE30:
    pop {pc}
MobiClip_Code_0208DE34:
    str lr, [sp, #-4]!
MobiClip_Code_0208DE38:
    mov r5, #0xc
MobiClip_Code_0208DE3C:
    mov r6, #4
MobiClip_Code_0208DE40:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DE44:
    pop {pc}
MobiClip_Code_0208DE48:
    str lr, [sp, #-4]!
MobiClip_Code_0208DE4C:
    mov r5, #0x10
MobiClip_Code_0208DE50:
    mov r6, #4
MobiClip_Code_0208DE54:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DE58:
    pop {pc}
MobiClip_Code_0208DE5C:
    str lr, [sp, #-4]!
MobiClip_Code_0208DE60:
    mov r5, #0x14
MobiClip_Code_0208DE64:
    mov r6, #4
MobiClip_Code_0208DE68:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DE6C:
    pop {pc}
MobiClip_Code_0208DE70:
    str lr, [sp, #-4]!
MobiClip_Code_0208DE74:
    bl MobiClip_Code_0208DF80
MobiClip_Code_0208DE78:
    add fp, fp, #0x200
MobiClip_Code_0208DE7C:
    bl MobiClip_Code_0208DF80
MobiClip_Code_0208DE80:
    sub fp, fp, #0x200
MobiClip_Code_0208DE84:
    pop {pc}
MobiClip_Code_0208DE88:
    lsr r6, r3, #0x1c
MobiClip_Code_0208DE8C:
    sub r5, pc, #0xe8
MobiClip_Code_0208DE90:
    ldrb r5, [r5, r6]
MobiClip_Code_0208DE94:
    sub r6, pc, #0xb8
MobiClip_Code_0208DE98:
    ldrb r6, [r6, r5]
MobiClip_Code_0208DE9C:
    lsl r3, r3, r6
MobiClip_Code_0208DEA0:
    subs r2, r2, r6
MobiClip_Code_0208DEA4:
    mov r8, lr
MobiClip_Code_0208DEA8:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208DEAC:
    sub r6, pc, #0xf8
MobiClip_Code_0208DEB0:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208DEB4:
    mov lr, r8
MobiClip_Code_0208DEB8:
    add pc, r5, r6
    /* control metadata 0x0208debc..0x0208df04 */
    .global gMobiClip_predicted_mode_h_selector_and_offsets
    .type gMobiClip_predicted_mode_h_selector_and_offsets, %object
gMobiClip_predicted_mode_h_selector_and_offsets:
    /* predicted_mode_h_selectors */
    .byte 0x05, 0x04, 0x01, 0x01, 0x00, 0x00, 0x03, 0x02
    /* predicted_intra_modes_h */
    .global gMobiClip_predicted_intra_modes_h
gMobiClip_predicted_intra_modes_h:
    .word MobiClip_Code_0208DF04 - .
    .word MobiClip_Code_0208DF1C - . + 0x4
    .word MobiClip_Code_0208DF30 - . + 0x8
    .word MobiClip_Code_0208DF44 - . + 0xc
    .word MobiClip_Code_0208DF58 - . + 0x10
    .word MobiClip_Code_0208DF6C - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word 0 /* reserved */
    /* predicted_mode_h_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .size gMobiClip_predicted_mode_h_selector_and_offsets, . - gMobiClip_predicted_mode_h_selector_and_offsets
MobiClip_Code_0208DF04:
    mov r5, #4
MobiClip_Code_0208DF08:
    mov r6, #2
MobiClip_Code_0208DF0C:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_0208DF10:
    add sb, r0, #0x3bc
MobiClip_Code_0208DF14:
    ldm sb, {r5, r6}
MobiClip_Code_0208DF18:
    b MobiClip_Code_0208D064
MobiClip_Code_0208DF1C:
    str lr, [sp, #-4]!
MobiClip_Code_0208DF20:
    mov r5, #4
MobiClip_Code_0208DF24:
    mov r6, #2
MobiClip_Code_0208DF28:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DF2C:
    pop {pc}
MobiClip_Code_0208DF30:
    str lr, [sp, #-4]!
MobiClip_Code_0208DF34:
    mov r5, #8
MobiClip_Code_0208DF38:
    mov r6, #2
MobiClip_Code_0208DF3C:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DF40:
    pop {pc}
MobiClip_Code_0208DF44:
    str lr, [sp, #-4]!
MobiClip_Code_0208DF48:
    mov r5, #0xc
MobiClip_Code_0208DF4C:
    mov r6, #2
MobiClip_Code_0208DF50:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DF54:
    pop {pc}
MobiClip_Code_0208DF58:
    str lr, [sp, #-4]!
MobiClip_Code_0208DF5C:
    mov r5, #0x10
MobiClip_Code_0208DF60:
    mov r6, #2
MobiClip_Code_0208DF64:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DF68:
    pop {pc}
MobiClip_Code_0208DF6C:
    str lr, [sp, #-4]!
MobiClip_Code_0208DF70:
    mov r5, #0x14
MobiClip_Code_0208DF74:
    mov r6, #2
MobiClip_Code_0208DF78:
    bl MobiClip_Code_0208D044
MobiClip_Code_0208DF7C:
    pop {pc}
MobiClip_Code_0208DF80:
    lsr r6, r3, #0x1d
MobiClip_Code_0208DF84:
    sub r5, pc, #0xd0
MobiClip_Code_0208DF88:
    ldrb r5, [r5, r6]
MobiClip_Code_0208DF8C:
    sub r6, pc, #0xa8
MobiClip_Code_0208DF90:
    ldrb r6, [r6, r5]
MobiClip_Code_0208DF94:
    lsl r3, r3, r6
MobiClip_Code_0208DF98:
    subs r2, r2, r6
MobiClip_Code_0208DF9C:
    mov r8, lr
MobiClip_Code_0208DFA0:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208DFA4:
    sub r6, pc, #0xe8
MobiClip_Code_0208DFA8:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_0208DFAC:
    mov lr, r8
MobiClip_Code_0208DFB0:
    add pc, r5, r6
MobiClip_Code_0208DFB4:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_0208DFB8:
    ldr r1, [r0]
MobiClip_Code_0208DFBC:
    mov r2, #0
MobiClip_Code_0208DFC0:
    ldrh r3, [r1], #2
MobiClip_Code_0208DFC4:
    lsl r3, r3, #0x10
MobiClip_Code_0208DFC8:
    adds r3, r3, r3
MobiClip_Code_0208DFCC:
    bhs MobiClip_Code_0208E0E0
MobiClip_Code_0208DFD0:
    subs r2, r2, #1
MobiClip_Code_0208DFD4:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208DFD8:
    bl MobiClip_Code_0208E93C
MobiClip_Code_0208DFDC:
    cmp r6, #0
MobiClip_Code_0208DFE0:
    ldrne r4, [r0, #0x3b4]
MobiClip_Code_0208DFE4:
    addne r4, r4, r6
MobiClip_Code_0208DFE8:
    blne MobiClip_Code_02091218
MobiClip_Code_0208DFEC:
    ldr fp, [r0, #0x3c]
MobiClip_Code_0208DFF0:
    str fp, [r0, #0x3b8]
MobiClip_Code_0208DFF4:
    add r4, r0, #0x3c4
MobiClip_Code_0208DFF8:
    mov r5, #0
MobiClip_Code_0208DFFC:
    mov r6, #0
MobiClip_Code_0208E000:
    ldr ip, [r0, #4]
MobiClip_Code_0208E004:
    add ip, ip, #0x20
MobiClip_Code_0208E008:
    stm r4!, {r5, r6}
MobiClip_Code_0208E00C:
    subs ip, ip, #0x10
MobiClip_Code_0208E010:
    bne MobiClip_Code_0208E008
MobiClip_Code_0208E014:
    mov fp, #0
MobiClip_Code_0208E018:
    ldr ip, [r0, #8]
MobiClip_Code_0208E01C:
    str ip, [sp, #-4]!
MobiClip_Code_0208E020:
    add r4, r0, #0x3c4
MobiClip_Code_0208E024:
    ldr ip, [r0, #4]
MobiClip_Code_0208E028:
    ldm r4, {r5, r6, r7, r8, sb, sl}
MobiClip_Code_0208E02C:
    add r4, r4, #8
MobiClip_Code_0208E030:
    cmp r5, r7
MobiClip_Code_0208E034:
    movgt lr, r5
MobiClip_Code_0208E038:
    movgt r5, r7
MobiClip_Code_0208E03C:
    movgt r7, lr
MobiClip_Code_0208E040:
    cmp r7, sb
MobiClip_Code_0208E044:
    movgt lr, r7
MobiClip_Code_0208E048:
    movgt r7, sb
MobiClip_Code_0208E04C:
    movgt sb, lr
MobiClip_Code_0208E050:
    cmp r5, r7
MobiClip_Code_0208E054:
    movgt lr, r5
MobiClip_Code_0208E058:
    movgt r5, r7
MobiClip_Code_0208E05C:
    movgt r7, lr
MobiClip_Code_0208E060:
    cmp r6, r8
MobiClip_Code_0208E064:
    movgt lr, r6
MobiClip_Code_0208E068:
    movgt r6, r8
MobiClip_Code_0208E06C:
    movgt r8, lr
MobiClip_Code_0208E070:
    cmp r8, sl
MobiClip_Code_0208E074:
    movgt lr, r8
MobiClip_Code_0208E078:
    movgt r8, sl
MobiClip_Code_0208E07C:
    movgt sl, lr
MobiClip_Code_0208E080:
    cmp r6, r8
MobiClip_Code_0208E084:
    movgt lr, r6
MobiClip_Code_0208E088:
    movgt r6, r8
MobiClip_Code_0208E08C:
    movgt r8, lr
MobiClip_Code_0208E090:
    add lr, r0, #0x3bc
MobiClip_Code_0208E094:
    stm lr, {r7, r8}
MobiClip_Code_0208E098:
    mov r7, #0
MobiClip_Code_0208E09C:
    mov r8, #0
MobiClip_Code_0208E0A0:
    stm r4, {r7, r8}
MobiClip_Code_0208E0A4:
    bl MobiClip_Code_0208CB70
MobiClip_Code_0208E0A8:
    add fp, fp, #0x10
MobiClip_Code_0208E0AC:
    subs ip, ip, #0x10
MobiClip_Code_0208E0B0:
    bne MobiClip_Code_0208E028
MobiClip_Code_0208E0B4:
    pop {ip}
MobiClip_Code_0208E0B8:
    ldr sl, [r0, #4]
MobiClip_Code_0208E0BC:
    add fp, fp, #0x1000
MobiClip_Code_0208E0C0:
    sub fp, fp, sl
MobiClip_Code_0208E0C4:
    subs ip, ip, #0x10
MobiClip_Code_0208E0C8:
    bne MobiClip_Code_0208E01C
MobiClip_Code_0208E0CC:
    ldr r2, [r0]
MobiClip_Code_0208E0D0:
    sub r0, r1, r2
MobiClip_Code_0208E0D4:
    sub r0, r0, #2
MobiClip_Code_0208E0D8:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_0208E0DC:
    bx lr
MobiClip_Code_0208E0E0:
    adds r3, r3, r3
MobiClip_Code_0208E0E4:
    movhs fp, #1
MobiClip_Code_0208E0E8:
    movlo fp, #0
MobiClip_Code_0208E0EC:
    str fp, [r0, #0x48]
MobiClip_Code_0208E0F0:
    adds r3, r3, r3
MobiClip_Code_0208E0F4:
    ldrlo fp, [r0, #0x3c]
MobiClip_Code_0208E0F8:
    ldrhs fp, [r0, #0x40]
MobiClip_Code_0208E0FC:
    str fp, [r0, #0x3b8]
MobiClip_Code_0208E100:
    subs r2, r2, #3
MobiClip_Code_0208E104:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208E108:
    lsr r4, r3, #0x1a
MobiClip_Code_0208E10C:
    lsl r3, r3, #6
MobiClip_Code_0208E110:
    subs r2, r2, #6
MobiClip_Code_0208E114:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208E118:
    ldr r5, [r0, #0x3b4]
MobiClip_Code_0208E11C:
    cmp r5, r4
MobiClip_Code_0208E120:
    blne MobiClip_Code_02091218
MobiClip_Code_0208E124:
    mov fp, #0
MobiClip_Code_0208E128:
    ldr ip, [r0, #8]
MobiClip_Code_0208E12C:
    str ip, [sp, #-4]!
MobiClip_Code_0208E130:
    ldr ip, [r0, #4]
MobiClip_Code_0208E134:
    adds r3, r3, r3
MobiClip_Code_0208E138:
    addhs r4, pc, #0x14c
MobiClip_Code_0208E13C:
    addlo r4, pc, #0x84
MobiClip_Code_0208E140:
    subs r2, r2, #1
MobiClip_Code_0208E144:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208E148:
    add lr, pc, #0
MobiClip_Code_0208E14C:
    bx r4
MobiClip_Code_0208E150:
    add fp, fp, #0x10
MobiClip_Code_0208E154:
    subs ip, ip, #0x10
MobiClip_Code_0208E158:
    bne MobiClip_Code_0208E134
MobiClip_Code_0208E15C:
    pop {ip}
MobiClip_Code_0208E160:
    ldr sl, [r0, #4]
MobiClip_Code_0208E164:
    add fp, fp, #0x1000
MobiClip_Code_0208E168:
    sub fp, fp, sl
MobiClip_Code_0208E16C:
    subs ip, ip, #0x10
MobiClip_Code_0208E170:
    bne MobiClip_Code_0208E12C
MobiClip_Code_0208E174:
    ldr r2, [r0]
MobiClip_Code_0208E178:
    sub r0, r1, r2
MobiClip_Code_0208E17C:
    sub r0, r0, #2
MobiClip_Code_0208E180:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_0208E184:
    bx lr
    /* semantic constants 0x0208e188..0x0208e1c8 */
    .global gMobiClipIFrameResidualPermutation
    .type gMobiClipIFrameResidualPermutation, %object
gMobiClipIFrameResidualPermutation:
    .byte 0x00, 0x1f, 0x3f, 0x0f, 0x08, 0x04, 0x02, 0x01, 0x0b, 0x0e, 0x1b, 0x0d, 0x03, 0x07, 0x0c, 0x17
    .byte 0x1d, 0x0a, 0x1e, 0x05, 0x10, 0x2f, 0x37, 0x3b, 0x13, 0x3d, 0x3e, 0x09, 0x1c, 0x06, 0x15, 0x1a
    .byte 0x33, 0x11, 0x12, 0x14, 0x18, 0x20, 0x3c, 0x35, 0x19, 0x16, 0x3a, 0x30, 0x31, 0x32, 0x27, 0x34
    .byte 0x2b, 0x2d, 0x39, 0x38, 0x23, 0x36, 0x2e, 0x21, 0x25, 0x22, 0x24, 0x2c, 0x2a, 0x28, 0x29, 0x26
    .size gMobiClipIFrameResidualPermutation, . - gMobiClipIFrameResidualPermutation
MobiClip_Code_0208E1C8:
    push {r4, ip, lr}
MobiClip_Code_0208E1CC:
    bl MobiClip_Code_0208E8F8
MobiClip_Code_0208E1D0:
    sub r4, pc, #0x50
MobiClip_Code_0208E1D4:
    ldrb r4, [r4, r6]
MobiClip_Code_0208E1D8:
    lsr ip, r3, #0x1d
MobiClip_Code_0208E1DC:
    lsl r3, r3, #3
MobiClip_Code_0208E1E0:
    subs r2, r2, #3
MobiClip_Code_0208E1E4:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208E1E8:
    ldr sl, [r0, #0xc]
MobiClip_Code_0208E1EC:
    add fp, fp, sl
MobiClip_Code_0208E1F0:
    cmp ip, #2
MobiClip_Code_0208E1F4:
    moveq ip, #9
MobiClip_Code_0208E1F8:
    bleq MobiClip_Code_0208E97C
MobiClip_Code_0208E1FC:
    str r4, [sp, #-4]!
MobiClip_Code_0208E200:
    tst r4, #1
MobiClip_Code_0208E204:
    add lr, pc, #0xc
MobiClip_Code_0208E208:
    bne MobiClip_Code_0208E6CC
MobiClip_Code_0208E20C:
    add r5, pc, #0x2c8
MobiClip_Code_0208E210:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_0208E214:
    add pc, r6, r5
MobiClip_Code_0208E218:
    add fp, fp, #8
MobiClip_Code_0208E21C:
    ldr r4, [sp]
MobiClip_Code_0208E220:
    tst r4, #2
MobiClip_Code_0208E224:
    add lr, pc, #0xc
MobiClip_Code_0208E228:
    bne MobiClip_Code_0208E6CC
MobiClip_Code_0208E22C:
    add r5, pc, #0x2a8
MobiClip_Code_0208E230:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_0208E234:
    add pc, r6, r5
MobiClip_Code_0208E238:
    add fp, fp, #0x800
MobiClip_Code_0208E23C:
    sub fp, fp, #8
MobiClip_Code_0208E240:
    ldr r4, [sp]
MobiClip_Code_0208E244:
    tst r4, #4
MobiClip_Code_0208E248:
    add lr, pc, #0xc
MobiClip_Code_0208E24C:
    bne MobiClip_Code_0208E6CC
MobiClip_Code_0208E250:
    add r5, pc, #0x284
MobiClip_Code_0208E254:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_0208E258:
    add pc, r6, r5
MobiClip_Code_0208E25C:
    add fp, fp, #8
MobiClip_Code_0208E260:
    ldr r4, [sp]
MobiClip_Code_0208E264:
    tst r4, #8
MobiClip_Code_0208E268:
    add lr, pc, #0xc
MobiClip_Code_0208E26C:
    bne MobiClip_Code_0208E6CC
MobiClip_Code_0208E270:
    add r5, pc, #0x264
MobiClip_Code_0208E274:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_0208E278:
    add pc, r6, r5
MobiClip_Code_0208E27C:
    sub fp, fp, #0x800
MobiClip_Code_0208E280:
    sub fp, fp, #8
MobiClip_Code_0208E284:
    sub fp, fp, sl
MobiClip_Code_0208E288:
    b MobiClip_Code_0208E454
MobiClip_Code_0208E28C:
    push {r4, ip, lr}
MobiClip_Code_0208E290:
    bl MobiClip_Code_0208E8F8
MobiClip_Code_0208E294:
    sub r4, pc, #0x114
MobiClip_Code_0208E298:
    ldrb r4, [r4, r6]
MobiClip_Code_0208E29C:
    ldr sl, [r0, #0xc]
MobiClip_Code_0208E2A0:
    add fp, fp, sl
MobiClip_Code_0208E2A4:
    str r4, [sp, #-4]!
MobiClip_Code_0208E2A8:
    add r5, r0, #0x55
MobiClip_Code_0208E2AC:
    tst r4, #1
MobiClip_Code_0208E2B0:
    add lr, pc, #4
MobiClip_Code_0208E2B4:
    beq MobiClip_Code_0208E3E4
MobiClip_Code_0208E2B8:
    bne MobiClip_Code_0208E52C
MobiClip_Code_0208E2BC:
    add fp, fp, #8
MobiClip_Code_0208E2C0:
    add r5, r0, #0x57
MobiClip_Code_0208E2C4:
    ldr r4, [sp]
MobiClip_Code_0208E2C8:
    tst r4, #2
MobiClip_Code_0208E2CC:
    add lr, pc, #4
MobiClip_Code_0208E2D0:
    beq MobiClip_Code_0208E3E4
MobiClip_Code_0208E2D4:
    bne MobiClip_Code_0208E52C
MobiClip_Code_0208E2D8:
    add fp, fp, #0x800
MobiClip_Code_0208E2DC:
    sub fp, fp, #8
MobiClip_Code_0208E2E0:
    add r5, r0, #0x65
MobiClip_Code_0208E2E4:
    ldr r4, [sp]
MobiClip_Code_0208E2E8:
    tst r4, #4
MobiClip_Code_0208E2EC:
    add lr, pc, #4
MobiClip_Code_0208E2F0:
    beq MobiClip_Code_0208E3E4
MobiClip_Code_0208E2F4:
    bne MobiClip_Code_0208E52C
MobiClip_Code_0208E2F8:
    add fp, fp, #8
MobiClip_Code_0208E2FC:
    add r5, r0, #0x67
MobiClip_Code_0208E300:
    ldr r4, [sp]
MobiClip_Code_0208E304:
    tst r4, #8
MobiClip_Code_0208E308:
    add lr, pc, #4
MobiClip_Code_0208E30C:
    beq MobiClip_Code_0208E3E4
MobiClip_Code_0208E310:
    bne MobiClip_Code_0208E52C
MobiClip_Code_0208E314:
    sub fp, fp, #0x800
MobiClip_Code_0208E318:
    sub fp, fp, #8
MobiClip_Code_0208E31C:
    sub fp, fp, sl
MobiClip_Code_0208E320:
    b MobiClip_Code_0208E454
    /* semantic constants 0x0208e324..0x0208e364 */
    .global gMobiClipPFrameResidualMask
    .type gMobiClipPFrameResidualMask, %object
gMobiClipPFrameResidualMask:
    .byte 0x00, 0x0f, 0x04, 0x01, 0x08, 0x02, 0x0c, 0x03, 0x05, 0x0a, 0x0d, 0x07, 0x0e, 0x0b, 0x1f, 0x09
    .byte 0x06, 0x10, 0x3f, 0x1e, 0x17, 0x1d, 0x1b, 0x1c, 0x13, 0x18, 0x1a, 0x12, 0x11, 0x14, 0x15, 0x20
    .byte 0x2f, 0x16, 0x19, 0x37, 0x3d, 0x3e, 0x3b, 0x3c, 0x33, 0x35, 0x21, 0x24, 0x22, 0x28, 0x23, 0x2c
    .byte 0x30, 0x27, 0x2d, 0x25, 0x3a, 0x2b, 0x2e, 0x2a, 0x31, 0x34, 0x38, 0x32, 0x29, 0x26, 0x39, 0x36
    .size gMobiClipPFrameResidualMask, . - gMobiClipPFrameResidualMask
MobiClip_Code_0208E364:
    push {r4, ip, lr}
MobiClip_Code_0208E368:
    bl MobiClip_Code_0208E8F8
MobiClip_Code_0208E36C:
    sub ip, pc, #0x50
MobiClip_Code_0208E370:
    ldrb ip, [ip, r6]
MobiClip_Code_0208E374:
    ldr sl, [r0, #0xc]
MobiClip_Code_0208E378:
    add fp, fp, sl
MobiClip_Code_0208E37C:
    tst ip, #1
MobiClip_Code_0208E380:
    blne MobiClip_Code_0208E6F0
MobiClip_Code_0208E384:
    add fp, fp, #8
MobiClip_Code_0208E388:
    tst ip, #2
MobiClip_Code_0208E38C:
    blne MobiClip_Code_0208E6F0
MobiClip_Code_0208E390:
    add fp, fp, #0x800
MobiClip_Code_0208E394:
    sub fp, fp, #8
MobiClip_Code_0208E398:
    tst ip, #4
MobiClip_Code_0208E39C:
    blne MobiClip_Code_0208E6F0
MobiClip_Code_0208E3A0:
    add fp, fp, #8
MobiClip_Code_0208E3A4:
    tst ip, #8
MobiClip_Code_0208E3A8:
    blne MobiClip_Code_0208E6F0
MobiClip_Code_0208E3AC:
    sub fp, fp, #0x800
MobiClip_Code_0208E3B0:
    sub fp, fp, #8
MobiClip_Code_0208E3B4:
    sub fp, fp, sl
MobiClip_Code_0208E3B8:
    ldr sl, [r0, #0x24]
MobiClip_Code_0208E3BC:
    add fp, sl, fp, lsr #1
MobiClip_Code_0208E3C0:
    tst ip, #0x10
MobiClip_Code_0208E3C4:
    blne MobiClip_Code_0208E6F0
MobiClip_Code_0208E3C8:
    add sl, sl, #0x80
MobiClip_Code_0208E3CC:
    add fp, fp, #0x80
MobiClip_Code_0208E3D0:
    tst ip, #0x20
MobiClip_Code_0208E3D4:
    blne MobiClip_Code_0208E6F0
MobiClip_Code_0208E3D8:
    sub fp, fp, sl
MobiClip_Code_0208E3DC:
    lsl fp, fp, #1
MobiClip_Code_0208E3E0:
    pop {r4, ip, pc}
MobiClip_Code_0208E3E4:
    ldrb ip, [r5, #-8]
MobiClip_Code_0208E3E8:
    ldrb r6, [r5, #-1]
MobiClip_Code_0208E3EC:
    cmp ip, r6
MobiClip_Code_0208E3F0:
    movgt ip, r6
MobiClip_Code_0208E3F4:
    cmp ip, #9
MobiClip_Code_0208E3F8:
    moveq ip, #3
MobiClip_Code_0208E3FC:
    lsr r6, r3, #0x1c
MobiClip_Code_0208E400:
    cmp r6, ip
MobiClip_Code_0208E404:
    addge r6, r6, #1
MobiClip_Code_0208E408:
    cmp r6, #9
MobiClip_Code_0208E40C:
    movlt ip, r6
MobiClip_Code_0208E410:
    movlt r7, #4
MobiClip_Code_0208E414:
    movge r7, #1
MobiClip_Code_0208E418:
    strb ip, [r5]
MobiClip_Code_0208E41C:
    strb ip, [r5, #1]
MobiClip_Code_0208E420:
    strb ip, [r5, #8]
MobiClip_Code_0208E424:
    strb ip, [r5, #9]
MobiClip_Code_0208E428:
    add r6, pc, #0xac
MobiClip_Code_0208E42C:
    ldr ip, [r6, ip, lsl #2]
MobiClip_Code_0208E430:
    add r6, r6, ip
MobiClip_Code_0208E434:
    lsl r3, r3, r7
MobiClip_Code_0208E438:
    subs r2, r2, r7
MobiClip_Code_0208E43C:
    mov r8, sl
MobiClip_Code_0208E440:
    mov ip, lr
MobiClip_Code_0208E444:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208E448:
    mov sl, r8
MobiClip_Code_0208E44C:
    mov lr, ip
MobiClip_Code_0208E450:
    mov pc, r6
MobiClip_Code_0208E454:
    lsr ip, r3, #0x1d
MobiClip_Code_0208E458:
    lsl r3, r3, #3
MobiClip_Code_0208E45C:
    subs r2, r2, #3
MobiClip_Code_0208E460:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208E464:
    ldr sl, [r0, #0x24]
MobiClip_Code_0208E468:
    add fp, sl, fp, lsr #1
MobiClip_Code_0208E46C:
    cmp ip, #2
MobiClip_Code_0208E470:
    bne MobiClip_Code_0208E490
MobiClip_Code_0208E474:
    mov ip, #9
MobiClip_Code_0208E478:
    bl MobiClip_Code_0208EE8C
MobiClip_Code_0208E47C:
    add sl, sl, #0x80
MobiClip_Code_0208E480:
    add fp, fp, #0x80
MobiClip_Code_0208E484:
    bl MobiClip_Code_0208EE8C
MobiClip_Code_0208E488:
    sub sl, sl, #0x80
MobiClip_Code_0208E48C:
    sub fp, fp, #0x80
MobiClip_Code_0208E490:
    ldr r4, [sp]
MobiClip_Code_0208E494:
    tst r4, #0x10
MobiClip_Code_0208E498:
    add lr, pc, #0xc
MobiClip_Code_0208E49C:
    bne MobiClip_Code_0208E6CC
MobiClip_Code_0208E4A0:
    add r5, pc, #0x34
MobiClip_Code_0208E4A4:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_0208E4A8:
    add pc, r6, r5
MobiClip_Code_0208E4AC:
    add sl, sl, #0x80
MobiClip_Code_0208E4B0:
    add fp, fp, #0x80
MobiClip_Code_0208E4B4:
    pop {r4}
MobiClip_Code_0208E4B8:
    tst r4, #0x20
MobiClip_Code_0208E4BC:
    add lr, pc, #0xc
MobiClip_Code_0208E4C0:
    bne MobiClip_Code_0208E6CC
MobiClip_Code_0208E4C4:
    add r5, pc, #0x10
MobiClip_Code_0208E4C8:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_0208E4CC:
    add pc, r6, r5
MobiClip_Code_0208E4D0:
    sub fp, fp, sl
MobiClip_Code_0208E4D4:
    lsl fp, fp, #1
MobiClip_Code_0208E4D8:
    pop {r4, ip, pc}
    /* control metadata 0x0208e4dc..0x0208e52c */
    .global gMobiClip_intra_prediction_dispatch
    .type gMobiClip_intra_prediction_dispatch, %object
gMobiClip_intra_prediction_dispatch:
    /* intra_prediction */
    .global gMobiClip_intra_prediction
gMobiClip_intra_prediction:
    .word MobiClip_Code_0208ED78 - .
    .word MobiClip_Code_0208EDC4 - . + 0x4
    .word MobiClip_Code_0208EE8C - . + 0x8
    .word MobiClip_Code_0208F308 - . + 0xc
    .word MobiClip_Code_0208F32C - . + 0x10
    .word MobiClip_Code_0208F4D0 - . + 0x14
    .word MobiClip_Code_0208F728 - . + 0x18
    .word MobiClip_Code_0208FA7C - . + 0x1c
    .word MobiClip_Code_0208FCB4 - . + 0x20
    .word MobiClip_Code_0208E978 - . + 0x24
    .word MobiClip_Code_0208FFF4 - . + 0x28
    .word MobiClip_Code_02090010 - . + 0x2c
    .word MobiClip_Code_02090058 - . + 0x30
    .word MobiClip_Code_020902BC - . + 0x34
    .word MobiClip_Code_020902E0 - . + 0x38
    .word MobiClip_Code_02090380 - . + 0x3c
    .word MobiClip_Code_02090484 - . + 0x40
    .word MobiClip_Code_0209058C - . + 0x44
    .word MobiClip_Code_02090674 - . + 0x48
    .word MobiClip_Code_0208E978 - . + 0x4c
    .size gMobiClip_intra_prediction_dispatch, . - gMobiClip_intra_prediction_dispatch
MobiClip_Code_0208E52C:
    tst r3, #0x80000000
MobiClip_Code_0208E530:
    beq MobiClip_Code_0208E5F8
MobiClip_Code_0208E534:
    add r3, r3, r3
MobiClip_Code_0208E538:
    sub r2, r2, #1
MobiClip_Code_0208E53C:
    ldrb ip, [r5, #-8]
MobiClip_Code_0208E540:
    ldrb r6, [r5, #-1]
MobiClip_Code_0208E544:
    cmp ip, r6
MobiClip_Code_0208E548:
    movgt ip, r6
MobiClip_Code_0208E54C:
    cmp ip, #9
MobiClip_Code_0208E550:
    moveq ip, #3
MobiClip_Code_0208E554:
    lsr r6, r3, #0x1c
MobiClip_Code_0208E558:
    cmp r6, ip
MobiClip_Code_0208E55C:
    addge r6, r6, #1
MobiClip_Code_0208E560:
    cmp r6, #9
MobiClip_Code_0208E564:
    movlt ip, r6
MobiClip_Code_0208E568:
    movlt r7, #4
MobiClip_Code_0208E56C:
    movge r7, #1
MobiClip_Code_0208E570:
    lsl r3, r3, r7
MobiClip_Code_0208E574:
    subs r2, r2, r7
MobiClip_Code_0208E578:
    mov r7, lr
MobiClip_Code_0208E57C:
    mov r8, sl
MobiClip_Code_0208E580:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208E584:
    mov lr, r7
MobiClip_Code_0208E588:
    mov sl, r8
MobiClip_Code_0208E58C:
    strb ip, [r5]
MobiClip_Code_0208E590:
    strb ip, [r5, #1]
MobiClip_Code_0208E594:
    strb ip, [r5, #8]
MobiClip_Code_0208E598:
    strb ip, [r5, #9]
MobiClip_Code_0208E59C:
    b MobiClip_Code_0208E6DC
MobiClip_Code_0208E5A0:
    ldrb ip, [r5, #-8]
MobiClip_Code_0208E5A4:
    ldrb r6, [r5, #-1]
MobiClip_Code_0208E5A8:
    cmp ip, r6
MobiClip_Code_0208E5AC:
    movgt ip, r6
MobiClip_Code_0208E5B0:
    cmp ip, #9
MobiClip_Code_0208E5B4:
    moveq ip, #3
MobiClip_Code_0208E5B8:
    lsr r6, r3, #0x1c
MobiClip_Code_0208E5BC:
    cmp r6, ip
MobiClip_Code_0208E5C0:
    addge r6, r6, #1
MobiClip_Code_0208E5C4:
    cmp r6, #9
MobiClip_Code_0208E5C8:
    movlt ip, r6
MobiClip_Code_0208E5CC:
    movlt r7, #4
MobiClip_Code_0208E5D0:
    movge r7, #1
MobiClip_Code_0208E5D4:
    strb ip, [r5]
MobiClip_Code_0208E5D8:
    add ip, ip, #0xa
MobiClip_Code_0208E5DC:
    lsl r3, r3, r7
MobiClip_Code_0208E5E0:
    subs r2, r2, r7
MobiClip_Code_0208E5E4:
    mov r8, sl
MobiClip_Code_0208E5E8:
    mov r6, lr
MobiClip_Code_0208E5EC:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0208E5F0:
    mov sl, r8
MobiClip_Code_0208E5F4:
    mov pc, r6
MobiClip_Code_0208E5F8:
    push {r5, lr}
MobiClip_Code_0208E5FC:
    mov r8, sl
MobiClip_Code_0208E600:
    bl MobiClip_Code_0208E8F8
MobiClip_Code_0208E604:
    add r4, pc, #0xac
MobiClip_Code_0208E608:
    ldrb r4, [r4, r6]
MobiClip_Code_0208E60C:
    mov sl, r8
MobiClip_Code_0208E610:
    str r4, [sp, #-4]!
MobiClip_Code_0208E614:
    bl MobiClip_Code_0208E5A0
MobiClip_Code_0208E618:
    tst r4, #1
MobiClip_Code_0208E61C:
    add lr, pc, #0xc
MobiClip_Code_0208E620:
    bne MobiClip_Code_0208E894
MobiClip_Code_0208E624:
    sub r6, pc, #0x150
MobiClip_Code_0208E628:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_0208E62C:
    add pc, r6, r7
MobiClip_Code_0208E630:
    add fp, fp, #4
MobiClip_Code_0208E634:
    ldm sp, {r4, r5}
MobiClip_Code_0208E638:
    add r5, r5, #1
MobiClip_Code_0208E63C:
    bl MobiClip_Code_0208E5A0
MobiClip_Code_0208E640:
    tst r4, #2
MobiClip_Code_0208E644:
    add lr, pc, #0xc
MobiClip_Code_0208E648:
    bne MobiClip_Code_0208E894
MobiClip_Code_0208E64C:
    sub r6, pc, #0x178
MobiClip_Code_0208E650:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_0208E654:
    add pc, r6, r7
MobiClip_Code_0208E658:
    add fp, fp, #0x400
MobiClip_Code_0208E65C:
    sub fp, fp, #4
MobiClip_Code_0208E660:
    ldm sp, {r4, r5}
MobiClip_Code_0208E664:
    add r5, r5, #8
MobiClip_Code_0208E668:
    bl MobiClip_Code_0208E5A0
MobiClip_Code_0208E66C:
    tst r4, #4
MobiClip_Code_0208E670:
    add lr, pc, #0xc
MobiClip_Code_0208E674:
    bne MobiClip_Code_0208E894
MobiClip_Code_0208E678:
    sub r6, pc, #0x1a4
MobiClip_Code_0208E67C:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_0208E680:
    add pc, r6, r7
MobiClip_Code_0208E684:
    add fp, fp, #4
MobiClip_Code_0208E688:
    pop {r4, r5}
MobiClip_Code_0208E68C:
    add r5, r5, #9
MobiClip_Code_0208E690:
    bl MobiClip_Code_0208E5A0
MobiClip_Code_0208E694:
    tst r4, #8
MobiClip_Code_0208E698:
    add lr, pc, #0xc
MobiClip_Code_0208E69C:
    bne MobiClip_Code_0208E894
MobiClip_Code_0208E6A0:
    sub r6, pc, #0x1cc
MobiClip_Code_0208E6A4:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_0208E6A8:
    add pc, r6, r7
MobiClip_Code_0208E6AC:
    sub fp, fp, #0x400
MobiClip_Code_0208E6B0:
    sub fp, fp, #4
MobiClip_Code_0208E6B4:
    pop {pc}
    /* semantic constants 0x0208e6b8..0x0208e6cc */
    .global gMobiClipIntraCoefficientMaskPadded
    .type gMobiClipIntraCoefficientMaskPadded, %object
gMobiClipIntraCoefficientMaskPadded:
    .byte 0x00, 0x0f, 0x00, 0x02, 0x01, 0x04, 0x08, 0x0c, 0x03, 0x0b, 0x0d, 0x0e, 0x07, 0x0a, 0x05, 0x09
    .byte 0x06, 0x00, 0x00, 0x00
    .size gMobiClipIntraCoefficientMaskPadded, . - gMobiClipIntraCoefficientMaskPadded
MobiClip_Code_0208E6CC:
    tst r3, #0x80000000
MobiClip_Code_0208E6D0:
    beq MobiClip_Code_0208E7EC
MobiClip_Code_0208E6D4:
    add r3, r3, r3
MobiClip_Code_0208E6D8:
    sub r2, r2, #1
MobiClip_Code_0208E6DC:
    push {sl, fp, ip, lr}
MobiClip_Code_0208E6E0:
    add lr, pc, #0x1c
MobiClip_Code_0208E6E4:
    sub r5, pc, #0x210
MobiClip_Code_0208E6E8:
    ldr ip, [r5, ip, lsl #2]
MobiClip_Code_0208E6EC:
    add pc, ip, r5
MobiClip_Code_0208E6F0:
    tst r3, #0x80000000
MobiClip_Code_0208E6F4:
    beq MobiClip_Code_0208E798
MobiClip_Code_0208E6F8:
    add r3, r3, r3
MobiClip_Code_0208E6FC:
    sub r2, r2, #1
MobiClip_Code_0208E700:
    push {sl, fp, ip, lr}
MobiClip_Code_0208E704:
    mov r4, #0
MobiClip_Code_0208E708:
    mov r5, #0
MobiClip_Code_0208E70C:
    mov r6, #0
MobiClip_Code_0208E710:
    mov r7, #0
MobiClip_Code_0208E714:
    mov r8, #0
MobiClip_Code_0208E718:
    mov sb, #0
MobiClip_Code_0208E71C:
    mov sl, #0
MobiClip_Code_0208E720:
    mov fp, #0
MobiClip_Code_0208E724:
    add ip, r0, #0x1b4
MobiClip_Code_0208E728:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_0208E72C:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_0208E730:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_0208E734:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_0208E738:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_0208E73C:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_0208E740:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_0208E744:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_0208E748:
    add ip, r0, #0x74
MobiClip_Code_0208E74C:
    bl MobiClip_Code_02090860
MobiClip_Code_0208E750:
    sub ip, ip, r0
MobiClip_Code_0208E754:
    add r4, pc, #0x38
MobiClip_Code_0208E758:
    add r4, r4, #0x2600
MobiClip_Code_0208E75C:
    cmp ip, #0x78
MobiClip_Code_0208E760:
    movle pc, r4
MobiClip_Code_0208E764:
    add r4, pc, #8
MobiClip_Code_0208E768:
    add r4, r4, #0x2500
MobiClip_Code_0208E76C:
    cmp ip, #0x80
MobiClip_Code_0208E770:
    movle pc, r4
MobiClip_Code_0208E774:
    add r4, pc, #0x4c
MobiClip_Code_0208E778:
    add r4, r4, #0x2300
MobiClip_Code_0208E77C:
    cmp ip, #0x9c
MobiClip_Code_0208E780:
    movle pc, r4
MobiClip_Code_0208E784:
    b MobiClip_Code_020908D0
    /* semantic constants 0x0208e788..0x0208e798 */
    .global gMobiClipPFrameCoefficientMask
    .type gMobiClipPFrameCoefficientMask, %object
gMobiClipPFrameCoefficientMask:
    .byte 0x00, 0x04, 0x01, 0x08, 0x02, 0x0c, 0x03, 0x05, 0x0a, 0x0f, 0x07, 0x0d, 0x0e, 0x0b, 0x09, 0x06
    .size gMobiClipPFrameCoefficientMask, . - gMobiClipPFrameCoefficientMask
MobiClip_Code_0208E798:
    push {ip, lr}
MobiClip_Code_0208E79C:
    mov r8, sl
MobiClip_Code_0208E7A0:
    bl MobiClip_Code_0208E8F8
MobiClip_Code_0208E7A4:
    mov sl, r8
MobiClip_Code_0208E7A8:
    sub ip, pc, #0x28
MobiClip_Code_0208E7AC:
    ldrb ip, [ip, r6]
MobiClip_Code_0208E7B0:
    tst ip, #1
MobiClip_Code_0208E7B4:
    blne MobiClip_Code_0208E8A8
MobiClip_Code_0208E7B8:
    add fp, fp, #4
MobiClip_Code_0208E7BC:
    tst ip, #2
MobiClip_Code_0208E7C0:
    blne MobiClip_Code_0208E8A8
MobiClip_Code_0208E7C4:
    add fp, fp, #0x400
MobiClip_Code_0208E7C8:
    sub fp, fp, #4
MobiClip_Code_0208E7CC:
    tst ip, #4
MobiClip_Code_0208E7D0:
    blne MobiClip_Code_0208E8A8
MobiClip_Code_0208E7D4:
    add fp, fp, #4
MobiClip_Code_0208E7D8:
    tst ip, #8
MobiClip_Code_0208E7DC:
    blne MobiClip_Code_0208E8A8
MobiClip_Code_0208E7E0:
    sub fp, fp, #0x400
MobiClip_Code_0208E7E4:
    sub fp, fp, #4
MobiClip_Code_0208E7E8:
    pop {ip, pc}
MobiClip_Code_0208E7EC:
    push {ip, lr}
MobiClip_Code_0208E7F0:
    add ip, ip, #0xa
MobiClip_Code_0208E7F4:
    mov r8, sl
MobiClip_Code_0208E7F8:
    bl MobiClip_Code_0208E8F8
MobiClip_Code_0208E7FC:
    sub r4, pc, #0x14c
MobiClip_Code_0208E800:
    ldrb r4, [r4, r6]
MobiClip_Code_0208E804:
    mov sl, r8
MobiClip_Code_0208E808:
    str r4, [sp, #-4]!
MobiClip_Code_0208E80C:
    tst r4, #1
MobiClip_Code_0208E810:
    add lr, pc, #0xc
MobiClip_Code_0208E814:
    bne MobiClip_Code_0208E894
MobiClip_Code_0208E818:
    sub r6, pc, #0x344
MobiClip_Code_0208E81C:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_0208E820:
    add pc, r6, r7
MobiClip_Code_0208E824:
    add fp, fp, #4
MobiClip_Code_0208E828:
    ldr r4, [sp]
MobiClip_Code_0208E82C:
    tst r4, #2
MobiClip_Code_0208E830:
    add lr, pc, #0xc
MobiClip_Code_0208E834:
    bne MobiClip_Code_0208E894
MobiClip_Code_0208E838:
    sub r6, pc, #0x364
MobiClip_Code_0208E83C:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_0208E840:
    add pc, r6, r7
MobiClip_Code_0208E844:
    add fp, fp, #0x400
MobiClip_Code_0208E848:
    sub fp, fp, #4
MobiClip_Code_0208E84C:
    ldr r4, [sp]
MobiClip_Code_0208E850:
    tst r4, #4
MobiClip_Code_0208E854:
    add lr, pc, #0xc
MobiClip_Code_0208E858:
    bne MobiClip_Code_0208E894
MobiClip_Code_0208E85C:
    sub r6, pc, #0x388
MobiClip_Code_0208E860:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_0208E864:
    add pc, r6, r7
MobiClip_Code_0208E868:
    add fp, fp, #4
MobiClip_Code_0208E86C:
    pop {r4}
MobiClip_Code_0208E870:
    tst r4, #8
MobiClip_Code_0208E874:
    add lr, pc, #0xc
MobiClip_Code_0208E878:
    bne MobiClip_Code_0208E894
MobiClip_Code_0208E87C:
    sub r6, pc, #0x3a8
MobiClip_Code_0208E880:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_0208E884:
    add pc, r6, r7
MobiClip_Code_0208E888:
    sub fp, fp, #0x400
MobiClip_Code_0208E88C:
    sub fp, fp, #4
MobiClip_Code_0208E890:
    pop {ip, pc}
MobiClip_Code_0208E894:
    push {sl, fp, ip, lr}
MobiClip_Code_0208E898:
    add lr, pc, #0xc
MobiClip_Code_0208E89C:
    sub r6, pc, #0x3c8
MobiClip_Code_0208E8A0:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_0208E8A4:
    add pc, r6, r7
MobiClip_Code_0208E8A8:
    push {sl, fp, ip, lr}
MobiClip_Code_0208E8AC:
    mov r4, #0
MobiClip_Code_0208E8B0:
    mov r5, #0
MobiClip_Code_0208E8B4:
    mov r6, #0
MobiClip_Code_0208E8B8:
    mov r7, #0
MobiClip_Code_0208E8BC:
    mov r8, #0
MobiClip_Code_0208E8C0:
    mov sb, #0
MobiClip_Code_0208E8C4:
    mov sl, #0
MobiClip_Code_0208E8C8:
    mov fp, #0
MobiClip_Code_0208E8CC:
    add ip, r0, #0x1b4
MobiClip_Code_0208E8D0:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_0208E8D4:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_0208E8D8:
    add ip, r0, #0x174
MobiClip_Code_0208E8DC:
    bl MobiClip_Code_02090860
MobiClip_Code_0208E8E0:
    sub ip, ip, r0
MobiClip_Code_0208E8E4:
    add r4, pc, #0x28
MobiClip_Code_0208E8E8:
    add r4, r4, #0x2600
MobiClip_Code_0208E8EC:
    cmp ip, #0x178
MobiClip_Code_0208E8F0:
    movle pc, r4
MobiClip_Code_0208E8F4:
    b MobiClip_Code_02090E40
MobiClip_Code_0208E8F8:
    clz sl, r3
MobiClip_Code_0208E8FC:
    lsl r3, r3, sl
MobiClip_Code_0208E900:
    add r3, r3, r3
MobiClip_Code_0208E904:
    rsb sb, sl, #0x20
MobiClip_Code_0208E908:
    lsr r6, r3, sb
MobiClip_Code_0208E90C:
    mov sb, #1
MobiClip_Code_0208E910:
    add r6, r6, sb, lsl sl
MobiClip_Code_0208E914:
    sub r6, r6, #1
MobiClip_Code_0208E918:
    lsl r3, r3, sl
MobiClip_Code_0208E91C:
    sub r2, r2, sl, lsl #1
MobiClip_Code_0208E920:
    subs r2, r2, #1
MobiClip_Code_0208E924:
    movge pc, lr
MobiClip_Code_0208E928:
    ldrh sl, [r1], #2
MobiClip_Code_0208E92C:
    add r2, r2, #0x10
MobiClip_Code_0208E930:
    rsb sb, r2, #0x10
MobiClip_Code_0208E934:
    orr r3, r3, sl, lsl sb
MobiClip_Code_0208E938:
    mov pc, lr
MobiClip_Code_0208E93C:
    clz sl, r3
MobiClip_Code_0208E940:
    lsl r3, r3, sl
MobiClip_Code_0208E944:
    add r3, r3, r3
MobiClip_Code_0208E948:
    rsb sb, sl, #0x20
MobiClip_Code_0208E94C:
    lsr r6, r3, sb
MobiClip_Code_0208E950:
    mov sb, #1
MobiClip_Code_0208E954:
    add r6, r6, sb, lsl sl
MobiClip_Code_0208E958:
    tst r6, #1
MobiClip_Code_0208E95C:
    rsbne r6, r6, #1
MobiClip_Code_0208E960:
    asr r6, r6, #1
MobiClip_Code_0208E964:
    lsl r3, r3, sl
MobiClip_Code_0208E968:
    sub r2, r2, sl, lsl #1
MobiClip_Code_0208E96C:
    subs r2, r2, #1
MobiClip_Code_0208E970:
    movge pc, lr
MobiClip_Code_0208E974:
    b MobiClip_Code_0208E928
MobiClip_Code_0208E978:
    mov pc, lr
MobiClip_Code_0208E97C:
    push {r4, sl, ip, lr}
MobiClip_Code_0208E980:
    bl MobiClip_Code_0208E93C
MobiClip_Code_0208E984:
    push {r0, r1, r2, r3}
MobiClip_Code_0208E988:
    sub lr, fp, #0x100
MobiClip_Code_0208E98C:
    ldm lr, {r0, r1, r2, r3}
MobiClip_Code_0208E990:
    add lr, fp, #0xf00
MobiClip_Code_0208E994:
    ldrb r4, [lr, #-1]
MobiClip_Code_0208E998:
    lsr sl, r3, #0x18
MobiClip_Code_0208E99C:
    add r5, r4, sl
MobiClip_Code_0208E9A0:
    add r5, r5, #1
MobiClip_Code_0208E9A4:
    asr r5, r5, #1
MobiClip_Code_0208E9A8:
    add r5, r5, r6, lsl #1
MobiClip_Code_0208E9AC:
    sub r6, r5, r4
MobiClip_Code_0208E9B0:
    add r6, r6, #1
MobiClip_Code_0208E9B4:
    lsl r4, r4, #3
MobiClip_Code_0208E9B8:
    sub sp, sp, #0x80
MobiClip_Code_0208E9BC:
    mov lr, sp
MobiClip_Code_0208E9C0:
    add r4, r4, r6, asr #1
MobiClip_Code_0208E9C4:
    mov r8, #0xff
MobiClip_Code_0208E9C8:
    and r7, r8, r0
MobiClip_Code_0208E9CC:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208E9D0:
    add r8, r8, #1
MobiClip_Code_0208E9D4:
    lsl r7, r7, #6
MobiClip_Code_0208E9D8:
    add r4, r4, r6, asr #1
MobiClip_Code_0208E9DC:
    mov ip, #0xff
MobiClip_Code_0208E9E0:
    and sb, ip, r0, lsr #8
MobiClip_Code_0208E9E4:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208E9E8:
    add ip, ip, #1
MobiClip_Code_0208E9EC:
    lsl sb, sb, #6
MobiClip_Code_0208E9F0:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208E9F4:
    add r4, r4, r6, asr #1
MobiClip_Code_0208E9F8:
    mov r8, #0xff
MobiClip_Code_0208E9FC:
    and r7, r8, r0, lsr #16
MobiClip_Code_0208EA00:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208EA04:
    add r8, r8, #1
MobiClip_Code_0208EA08:
    lsl r7, r7, #6
MobiClip_Code_0208EA0C:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EA10:
    mov ip, #0xff
MobiClip_Code_0208EA14:
    and sb, ip, r0, lsr #24
MobiClip_Code_0208EA18:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208EA1C:
    add ip, ip, #1
MobiClip_Code_0208EA20:
    lsl sb, sb, #6
MobiClip_Code_0208EA24:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208EA28:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EA2C:
    mov r8, #0xff
MobiClip_Code_0208EA30:
    and r7, r8, r1
MobiClip_Code_0208EA34:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208EA38:
    add r8, r8, #1
MobiClip_Code_0208EA3C:
    lsl r7, r7, #6
MobiClip_Code_0208EA40:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EA44:
    mov ip, #0xff
MobiClip_Code_0208EA48:
    and sb, ip, r1, lsr #8
MobiClip_Code_0208EA4C:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208EA50:
    add ip, ip, #1
MobiClip_Code_0208EA54:
    lsl sb, sb, #6
MobiClip_Code_0208EA58:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208EA5C:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EA60:
    mov r8, #0xff
MobiClip_Code_0208EA64:
    and r7, r8, r1, lsr #16
MobiClip_Code_0208EA68:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208EA6C:
    add r8, r8, #1
MobiClip_Code_0208EA70:
    lsl r7, r7, #6
MobiClip_Code_0208EA74:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EA78:
    mov ip, #0xff
MobiClip_Code_0208EA7C:
    and sb, ip, r1, lsr #24
MobiClip_Code_0208EA80:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208EA84:
    add ip, ip, #1
MobiClip_Code_0208EA88:
    lsl sb, sb, #6
MobiClip_Code_0208EA8C:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208EA90:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EA94:
    mov r8, #0xff
MobiClip_Code_0208EA98:
    and r7, r8, r2
MobiClip_Code_0208EA9C:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208EAA0:
    add r8, r8, #1
MobiClip_Code_0208EAA4:
    lsl r7, r7, #6
MobiClip_Code_0208EAA8:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EAAC:
    mov ip, #0xff
MobiClip_Code_0208EAB0:
    and sb, ip, r2, lsr #8
MobiClip_Code_0208EAB4:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208EAB8:
    add ip, ip, #1
MobiClip_Code_0208EABC:
    lsl sb, sb, #6
MobiClip_Code_0208EAC0:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208EAC4:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EAC8:
    mov r8, #0xff
MobiClip_Code_0208EACC:
    and r7, r8, r2, lsr #16
MobiClip_Code_0208EAD0:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208EAD4:
    add r8, r8, #1
MobiClip_Code_0208EAD8:
    lsl r7, r7, #6
MobiClip_Code_0208EADC:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EAE0:
    mov ip, #0xff
MobiClip_Code_0208EAE4:
    and sb, ip, r2, lsr #24
MobiClip_Code_0208EAE8:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208EAEC:
    add ip, ip, #1
MobiClip_Code_0208EAF0:
    lsl sb, sb, #6
MobiClip_Code_0208EAF4:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208EAF8:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EAFC:
    mov r8, #0xff
MobiClip_Code_0208EB00:
    and r7, r8, r3
MobiClip_Code_0208EB04:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208EB08:
    add r8, r8, #1
MobiClip_Code_0208EB0C:
    lsl r7, r7, #6
MobiClip_Code_0208EB10:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EB14:
    mov ip, #0xff
MobiClip_Code_0208EB18:
    and sb, ip, r3, lsr #8
MobiClip_Code_0208EB1C:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208EB20:
    add ip, ip, #1
MobiClip_Code_0208EB24:
    lsl sb, sb, #6
MobiClip_Code_0208EB28:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208EB2C:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EB30:
    mov r8, #0xff
MobiClip_Code_0208EB34:
    and r7, r8, r3, lsr #16
MobiClip_Code_0208EB38:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208EB3C:
    add r8, r8, #1
MobiClip_Code_0208EB40:
    lsl r7, r7, #6
MobiClip_Code_0208EB44:
    add r4, r4, r6, asr #1
MobiClip_Code_0208EB48:
    mov ip, #0xff
MobiClip_Code_0208EB4C:
    and sb, ip, r3, lsr #24
MobiClip_Code_0208EB50:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208EB54:
    add ip, ip, #1
MobiClip_Code_0208EB58:
    lsl sb, sb, #6
MobiClip_Code_0208EB5C:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208EB60:
    sub sb, r5, sl
MobiClip_Code_0208EB64:
    add sb, sb, #1
MobiClip_Code_0208EB68:
    lsl sl, sl, #3
MobiClip_Code_0208EB6C:
    mov lr, #0x10
MobiClip_Code_0208EB70:
    add sl, sl, sb, asr #1
MobiClip_Code_0208EB74:
    ldrb r8, [fp, #-1]
MobiClip_Code_0208EB78:
    sub r7, sl, r8, lsl #3
MobiClip_Code_0208EB7C:
    add r7, r7, #1
MobiClip_Code_0208EB80:
    lsl r8, r8, #6
MobiClip_Code_0208EB84:
    add ip, sp, #0
MobiClip_Code_0208EB88:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_0208EB8C:
    add r0, r0, r1, asr #1
MobiClip_Code_0208EB90:
    add r2, r2, r3, asr #1
MobiClip_Code_0208EB94:
    add r4, r4, r5, asr #1
MobiClip_Code_0208EB98:
    add r6, r6, ip, asr #1
MobiClip_Code_0208EB9C:
    str r0, [sp]
MobiClip_Code_0208EBA0:
    str r2, [sp, #8]
MobiClip_Code_0208EBA4:
    str r4, [sp, #0x10]
MobiClip_Code_0208EBA8:
    str r6, [sp, #0x18]
MobiClip_Code_0208EBAC:
    add r8, r8, r7, asr #1
MobiClip_Code_0208EBB0:
    add r5, r0, r8
MobiClip_Code_0208EBB4:
    add r5, r5, #0x40
MobiClip_Code_0208EBB8:
    asr r5, r5, #7
MobiClip_Code_0208EBBC:
    add r8, r8, r7, asr #1
MobiClip_Code_0208EBC0:
    add ip, r2, r8
MobiClip_Code_0208EBC4:
    add ip, ip, #0x40
MobiClip_Code_0208EBC8:
    asr ip, ip, #7
MobiClip_Code_0208EBCC:
    orr r5, r5, ip, lsl #8
MobiClip_Code_0208EBD0:
    add r8, r8, r7, asr #1
MobiClip_Code_0208EBD4:
    add ip, r4, r8
MobiClip_Code_0208EBD8:
    add ip, ip, #0x40
MobiClip_Code_0208EBDC:
    asr ip, ip, #7
MobiClip_Code_0208EBE0:
    orr r5, r5, ip, lsl #16
MobiClip_Code_0208EBE4:
    add r8, r8, r7, asr #1
MobiClip_Code_0208EBE8:
    add ip, r6, r8
MobiClip_Code_0208EBEC:
    add ip, ip, #0x40
MobiClip_Code_0208EBF0:
    asr ip, ip, #7
MobiClip_Code_0208EBF4:
    orr r5, r5, ip, lsl #24
MobiClip_Code_0208EBF8:
    str r5, [fp], #4
MobiClip_Code_0208EBFC:
    add ip, sp, #0x20
MobiClip_Code_0208EC00:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_0208EC04:
    add r0, r0, r1, asr #1
MobiClip_Code_0208EC08:
    add r2, r2, r3, asr #1
MobiClip_Code_0208EC0C:
    add r4, r4, r5, asr #1
MobiClip_Code_0208EC10:
    add r6, r6, ip, asr #1
MobiClip_Code_0208EC14:
    str r0, [sp, #0x20]
MobiClip_Code_0208EC18:
    str r2, [sp, #0x28]
MobiClip_Code_0208EC1C:
    str r4, [sp, #0x30]
MobiClip_Code_0208EC20:
    str r6, [sp, #0x38]
MobiClip_Code_0208EC24:
    add r8, r8, r7, asr #1
MobiClip_Code_0208EC28:
    add r5, r0, r8
MobiClip_Code_0208EC2C:
    add r5, r5, #0x40
MobiClip_Code_0208EC30:
    asr r5, r5, #7
MobiClip_Code_0208EC34:
    add r8, r8, r7, asr #1
MobiClip_Code_0208EC38:
    add ip, r2, r8
MobiClip_Code_0208EC3C:
    add ip, ip, #0x40
MobiClip_Code_0208EC40:
    asr ip, ip, #7
MobiClip_Code_0208EC44:
    orr r5, r5, ip, lsl #8
MobiClip_Code_0208EC48:
    add r8, r8, r7, asr #1
MobiClip_Code_0208EC4C:
    add ip, r4, r8
MobiClip_Code_0208EC50:
    add ip, ip, #0x40
MobiClip_Code_0208EC54:
    asr ip, ip, #7
MobiClip_Code_0208EC58:
    orr r5, r5, ip, lsl #16
MobiClip_Code_0208EC5C:
    add r8, r8, r7, asr #1
MobiClip_Code_0208EC60:
    add ip, r6, r8
MobiClip_Code_0208EC64:
    add ip, ip, #0x40
MobiClip_Code_0208EC68:
    asr ip, ip, #7
MobiClip_Code_0208EC6C:
    orr r5, r5, ip, lsl #24
MobiClip_Code_0208EC70:
    str r5, [fp], #4
MobiClip_Code_0208EC74:
    add ip, sp, #0x40
MobiClip_Code_0208EC78:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_0208EC7C:
    add r0, r0, r1, asr #1
MobiClip_Code_0208EC80:
    add r2, r2, r3, asr #1
MobiClip_Code_0208EC84:
    add r4, r4, r5, asr #1
MobiClip_Code_0208EC88:
    add r6, r6, ip, asr #1
MobiClip_Code_0208EC8C:
    str r0, [sp, #0x40]
MobiClip_Code_0208EC90:
    str r2, [sp, #0x48]
MobiClip_Code_0208EC94:
    str r4, [sp, #0x50]
MobiClip_Code_0208EC98:
    str r6, [sp, #0x58]
MobiClip_Code_0208EC9C:
    add r8, r8, r7, asr #1
MobiClip_Code_0208ECA0:
    add r5, r0, r8
MobiClip_Code_0208ECA4:
    add r5, r5, #0x40
MobiClip_Code_0208ECA8:
    asr r5, r5, #7
MobiClip_Code_0208ECAC:
    add r8, r8, r7, asr #1
MobiClip_Code_0208ECB0:
    add ip, r2, r8
MobiClip_Code_0208ECB4:
    add ip, ip, #0x40
MobiClip_Code_0208ECB8:
    asr ip, ip, #7
MobiClip_Code_0208ECBC:
    orr r5, r5, ip, lsl #8
MobiClip_Code_0208ECC0:
    add r8, r8, r7, asr #1
MobiClip_Code_0208ECC4:
    add ip, r4, r8
MobiClip_Code_0208ECC8:
    add ip, ip, #0x40
MobiClip_Code_0208ECCC:
    asr ip, ip, #7
MobiClip_Code_0208ECD0:
    orr r5, r5, ip, lsl #16
MobiClip_Code_0208ECD4:
    add r8, r8, r7, asr #1
MobiClip_Code_0208ECD8:
    add ip, r6, r8
MobiClip_Code_0208ECDC:
    add ip, ip, #0x40
MobiClip_Code_0208ECE0:
    asr ip, ip, #7
MobiClip_Code_0208ECE4:
    orr r5, r5, ip, lsl #24
MobiClip_Code_0208ECE8:
    str r5, [fp], #4
MobiClip_Code_0208ECEC:
    add ip, sp, #0x60
MobiClip_Code_0208ECF0:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_0208ECF4:
    add r0, r0, r1, asr #1
MobiClip_Code_0208ECF8:
    add r2, r2, r3, asr #1
MobiClip_Code_0208ECFC:
    add r4, r4, r5, asr #1
MobiClip_Code_0208ED00:
    add r6, r6, ip, asr #1
MobiClip_Code_0208ED04:
    str r0, [sp, #0x60]
MobiClip_Code_0208ED08:
    str r2, [sp, #0x68]
MobiClip_Code_0208ED0C:
    str r4, [sp, #0x70]
MobiClip_Code_0208ED10:
    str r6, [sp, #0x78]
MobiClip_Code_0208ED14:
    add r8, r8, r7, asr #1
MobiClip_Code_0208ED18:
    add r5, r0, r8
MobiClip_Code_0208ED1C:
    add r5, r5, #0x40
MobiClip_Code_0208ED20:
    asr r5, r5, #7
MobiClip_Code_0208ED24:
    add r8, r8, r7, asr #1
MobiClip_Code_0208ED28:
    add ip, r2, r8
MobiClip_Code_0208ED2C:
    add ip, ip, #0x40
MobiClip_Code_0208ED30:
    asr ip, ip, #7
MobiClip_Code_0208ED34:
    orr r5, r5, ip, lsl #8
MobiClip_Code_0208ED38:
    add r8, r8, r7, asr #1
MobiClip_Code_0208ED3C:
    add ip, r4, r8
MobiClip_Code_0208ED40:
    add ip, ip, #0x40
MobiClip_Code_0208ED44:
    asr ip, ip, #7
MobiClip_Code_0208ED48:
    orr r5, r5, ip, lsl #16
MobiClip_Code_0208ED4C:
    add r8, r8, r7, asr #1
MobiClip_Code_0208ED50:
    add ip, r6, r8
MobiClip_Code_0208ED54:
    add ip, ip, #0x40
MobiClip_Code_0208ED58:
    asr ip, ip, #7
MobiClip_Code_0208ED5C:
    orr r5, r5, ip, lsl #24
MobiClip_Code_0208ED60:
    str r5, [fp], #0xf4
MobiClip_Code_0208ED64:
    subs lr, lr, #1
MobiClip_Code_0208ED68:
    bne MobiClip_Code_0208EB70
MobiClip_Code_0208ED6C:
    add sp, sp, #0x80
MobiClip_Code_0208ED70:
    sub fp, fp, #0x1000
MobiClip_Code_0208ED74:
    pop {r0, r1, r2, r3, r4, sl, ip, pc}
MobiClip_Code_0208ED78:
    sub r7, fp, #0x100
MobiClip_Code_0208ED7C:
    ldm r7, {r4, r5}
MobiClip_Code_0208ED80:
    add r7, r7, #0x100
MobiClip_Code_0208ED84:
    stm r7, {r4, r5}
MobiClip_Code_0208ED88:
    add r7, r7, #0x100
MobiClip_Code_0208ED8C:
    stm r7, {r4, r5}
MobiClip_Code_0208ED90:
    add r7, r7, #0x100
MobiClip_Code_0208ED94:
    stm r7, {r4, r5}
MobiClip_Code_0208ED98:
    add r7, r7, #0x100
MobiClip_Code_0208ED9C:
    stm r7, {r4, r5}
MobiClip_Code_0208EDA0:
    add r7, r7, #0x100
MobiClip_Code_0208EDA4:
    stm r7, {r4, r5}
MobiClip_Code_0208EDA8:
    add r7, r7, #0x100
MobiClip_Code_0208EDAC:
    stm r7, {r4, r5}
MobiClip_Code_0208EDB0:
    add r7, r7, #0x100
MobiClip_Code_0208EDB4:
    stm r7, {r4, r5}
MobiClip_Code_0208EDB8:
    add r7, r7, #0x100
MobiClip_Code_0208EDBC:
    stm r7, {r4, r5}
MobiClip_Code_0208EDC0:
    mov pc, lr
MobiClip_Code_0208EDC4:
    ldrb r6, [fp, #-1]
MobiClip_Code_0208EDC8:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208EDCC:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208EDD0:
    mov r7, r6
MobiClip_Code_0208EDD4:
    stm fp, {r6, r7}
MobiClip_Code_0208EDD8:
    add fp, fp, #0x100
MobiClip_Code_0208EDDC:
    ldrb r6, [fp, #-1]
MobiClip_Code_0208EDE0:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208EDE4:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208EDE8:
    mov r7, r6
MobiClip_Code_0208EDEC:
    stm fp, {r6, r7}
MobiClip_Code_0208EDF0:
    add fp, fp, #0x100
MobiClip_Code_0208EDF4:
    ldrb r6, [fp, #-1]
MobiClip_Code_0208EDF8:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208EDFC:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208EE00:
    mov r7, r6
MobiClip_Code_0208EE04:
    stm fp, {r6, r7}
MobiClip_Code_0208EE08:
    add fp, fp, #0x100
MobiClip_Code_0208EE0C:
    ldrb r6, [fp, #-1]
MobiClip_Code_0208EE10:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208EE14:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208EE18:
    mov r7, r6
MobiClip_Code_0208EE1C:
    stm fp, {r6, r7}
MobiClip_Code_0208EE20:
    add fp, fp, #0x100
MobiClip_Code_0208EE24:
    ldrb r6, [fp, #-1]
MobiClip_Code_0208EE28:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208EE2C:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208EE30:
    mov r7, r6
MobiClip_Code_0208EE34:
    stm fp, {r6, r7}
MobiClip_Code_0208EE38:
    add fp, fp, #0x100
MobiClip_Code_0208EE3C:
    ldrb r6, [fp, #-1]
MobiClip_Code_0208EE40:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208EE44:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208EE48:
    mov r7, r6
MobiClip_Code_0208EE4C:
    stm fp, {r6, r7}
MobiClip_Code_0208EE50:
    add fp, fp, #0x100
MobiClip_Code_0208EE54:
    ldrb r6, [fp, #-1]
MobiClip_Code_0208EE58:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208EE5C:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208EE60:
    mov r7, r6
MobiClip_Code_0208EE64:
    stm fp, {r6, r7}
MobiClip_Code_0208EE68:
    add fp, fp, #0x100
MobiClip_Code_0208EE6C:
    ldrb r6, [fp, #-1]
MobiClip_Code_0208EE70:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208EE74:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208EE78:
    mov r7, r6
MobiClip_Code_0208EE7C:
    stm fp, {r6, r7}
MobiClip_Code_0208EE80:
    add fp, fp, #0x100
MobiClip_Code_0208EE84:
    sub fp, fp, #0x800
MobiClip_Code_0208EE88:
    mov pc, lr
MobiClip_Code_0208EE8C:
    push {r4, sl, ip, lr}
MobiClip_Code_0208EE90:
    bl MobiClip_Code_0208E93C
MobiClip_Code_0208EE94:
    push {r0, r1, r2, r3}
MobiClip_Code_0208EE98:
    sub lr, fp, #0x100
MobiClip_Code_0208EE9C:
    ldm lr, {r0, r1}
MobiClip_Code_0208EEA0:
    add lr, fp, #0x700
MobiClip_Code_0208EEA4:
    ldrb r4, [lr, #-1]
MobiClip_Code_0208EEA8:
    lsr sl, r1, #0x18
MobiClip_Code_0208EEAC:
    add r5, r4, sl
MobiClip_Code_0208EEB0:
    add r5, r5, #1
MobiClip_Code_0208EEB4:
    asr r5, r5, #1
MobiClip_Code_0208EEB8:
    add r5, r5, r6, lsl #1
MobiClip_Code_0208EEBC:
    sub r6, r5, r4
MobiClip_Code_0208EEC0:
    lsl r4, r4, #3
MobiClip_Code_0208EEC4:
    sub sp, sp, #0x40
MobiClip_Code_0208EEC8:
    mov lr, sp
MobiClip_Code_0208EECC:
    mov r2, #0xff
MobiClip_Code_0208EED0:
    add r4, r4, r6
MobiClip_Code_0208EED4:
    and r7, r2, r0
MobiClip_Code_0208EED8:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208EEDC:
    lsl r7, r7, #6
MobiClip_Code_0208EEE0:
    add r4, r4, r6
MobiClip_Code_0208EEE4:
    and sb, r2, r0, lsr #8
MobiClip_Code_0208EEE8:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208EEEC:
    lsl sb, sb, #6
MobiClip_Code_0208EEF0:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208EEF4:
    add r4, r4, r6
MobiClip_Code_0208EEF8:
    and r7, r2, r0, lsr #16
MobiClip_Code_0208EEFC:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208EF00:
    lsl r7, r7, #6
MobiClip_Code_0208EF04:
    add r4, r4, r6
MobiClip_Code_0208EF08:
    and sb, r2, r0, lsr #24
MobiClip_Code_0208EF0C:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208EF10:
    lsl sb, sb, #6
MobiClip_Code_0208EF14:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208EF18:
    add r4, r4, r6
MobiClip_Code_0208EF1C:
    and r7, r2, r1
MobiClip_Code_0208EF20:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208EF24:
    lsl r7, r7, #6
MobiClip_Code_0208EF28:
    add r4, r4, r6
MobiClip_Code_0208EF2C:
    and sb, r2, r1, lsr #8
MobiClip_Code_0208EF30:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208EF34:
    lsl sb, sb, #6
MobiClip_Code_0208EF38:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208EF3C:
    add r4, r4, r6
MobiClip_Code_0208EF40:
    and r7, r2, r1, lsr #16
MobiClip_Code_0208EF44:
    sub r8, r4, r7, lsl #3
MobiClip_Code_0208EF48:
    lsl r7, r7, #6
MobiClip_Code_0208EF4C:
    add r4, r4, r6
MobiClip_Code_0208EF50:
    and sb, r2, r1, lsr #24
MobiClip_Code_0208EF54:
    sub ip, r4, sb, lsl #3
MobiClip_Code_0208EF58:
    lsl sb, sb, #6
MobiClip_Code_0208EF5C:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_0208EF60:
    sub sb, r5, sl
MobiClip_Code_0208EF64:
    lsl sl, sl, #3
MobiClip_Code_0208EF68:
    mov lr, #8
MobiClip_Code_0208EF6C:
    add sl, sl, sb
MobiClip_Code_0208EF70:
    ldrb r8, [fp, #-1]
MobiClip_Code_0208EF74:
    sub r7, sl, r8, lsl #3
MobiClip_Code_0208EF78:
    lsl r8, r8, #6
MobiClip_Code_0208EF7C:
    add ip, sp, #0
MobiClip_Code_0208EF80:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_0208EF84:
    add r0, r0, r1
MobiClip_Code_0208EF88:
    add r2, r2, r3
MobiClip_Code_0208EF8C:
    add r4, r4, r5
MobiClip_Code_0208EF90:
    add r6, r6, ip
MobiClip_Code_0208EF94:
    str r0, [sp]
MobiClip_Code_0208EF98:
    str r2, [sp, #8]
MobiClip_Code_0208EF9C:
    str r4, [sp, #0x10]
MobiClip_Code_0208EFA0:
    str r6, [sp, #0x18]
MobiClip_Code_0208EFA4:
    add r8, r8, r7
MobiClip_Code_0208EFA8:
    add r5, r0, r8
MobiClip_Code_0208EFAC:
    add r5, r5, #0x40
MobiClip_Code_0208EFB0:
    asr r5, r5, #7
MobiClip_Code_0208EFB4:
    add r8, r8, r7
MobiClip_Code_0208EFB8:
    add ip, r2, r8
MobiClip_Code_0208EFBC:
    add ip, ip, #0x40
MobiClip_Code_0208EFC0:
    asr ip, ip, #7
MobiClip_Code_0208EFC4:
    orr r5, r5, ip, lsl #8
MobiClip_Code_0208EFC8:
    add r8, r8, r7
MobiClip_Code_0208EFCC:
    add ip, r4, r8
MobiClip_Code_0208EFD0:
    add ip, ip, #0x40
MobiClip_Code_0208EFD4:
    asr ip, ip, #7
MobiClip_Code_0208EFD8:
    orr r5, r5, ip, lsl #16
MobiClip_Code_0208EFDC:
    add r8, r8, r7
MobiClip_Code_0208EFE0:
    add ip, r6, r8
MobiClip_Code_0208EFE4:
    add ip, ip, #0x40
MobiClip_Code_0208EFE8:
    asr ip, ip, #7
MobiClip_Code_0208EFEC:
    orr r5, r5, ip, lsl #24
MobiClip_Code_0208EFF0:
    str r5, [fp], #4
MobiClip_Code_0208EFF4:
    add ip, sp, #0x20
MobiClip_Code_0208EFF8:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_0208EFFC:
    add r0, r0, r1
MobiClip_Code_0208F000:
    add r2, r2, r3
MobiClip_Code_0208F004:
    add r4, r4, r5
MobiClip_Code_0208F008:
    add r6, r6, ip
MobiClip_Code_0208F00C:
    str r0, [sp, #0x20]
MobiClip_Code_0208F010:
    str r2, [sp, #0x28]
MobiClip_Code_0208F014:
    str r4, [sp, #0x30]
MobiClip_Code_0208F018:
    str r6, [sp, #0x38]
MobiClip_Code_0208F01C:
    add r8, r8, r7
MobiClip_Code_0208F020:
    add r5, r0, r8
MobiClip_Code_0208F024:
    add r5, r5, #0x40
MobiClip_Code_0208F028:
    asr r5, r5, #7
MobiClip_Code_0208F02C:
    add r8, r8, r7
MobiClip_Code_0208F030:
    add ip, r2, r8
MobiClip_Code_0208F034:
    add ip, ip, #0x40
MobiClip_Code_0208F038:
    asr ip, ip, #7
MobiClip_Code_0208F03C:
    orr r5, r5, ip, lsl #8
MobiClip_Code_0208F040:
    add r8, r8, r7
MobiClip_Code_0208F044:
    add ip, r4, r8
MobiClip_Code_0208F048:
    add ip, ip, #0x40
MobiClip_Code_0208F04C:
    asr ip, ip, #7
MobiClip_Code_0208F050:
    orr r5, r5, ip, lsl #16
MobiClip_Code_0208F054:
    add r8, r8, r7
MobiClip_Code_0208F058:
    add ip, r6, r8
MobiClip_Code_0208F05C:
    add ip, ip, #0x40
MobiClip_Code_0208F060:
    asr ip, ip, #7
MobiClip_Code_0208F064:
    orr r5, r5, ip, lsl #24
MobiClip_Code_0208F068:
    str r5, [fp], #0xfc
MobiClip_Code_0208F06C:
    subs lr, lr, #1
MobiClip_Code_0208F070:
    bne MobiClip_Code_0208EF6C
MobiClip_Code_0208F074:
    add sp, sp, #0x40
MobiClip_Code_0208F078:
    sub fp, fp, #0x800
MobiClip_Code_0208F07C:
    pop {r0, r1, r2, r3, r4, sl, ip, pc}
MobiClip_Code_0208F080:
    mov r6, #0
MobiClip_Code_0208F084:
    sub r7, fp, #0x100
MobiClip_Code_0208F088:
    ldm r7, {r4, r5}
MobiClip_Code_0208F08C:
    add r6, r6, r4, lsr #24
MobiClip_Code_0208F090:
    lsl r4, r4, #8
MobiClip_Code_0208F094:
    add r6, r6, r4, lsr #24
MobiClip_Code_0208F098:
    lsl r4, r4, #8
MobiClip_Code_0208F09C:
    add r6, r6, r4, lsr #24
MobiClip_Code_0208F0A0:
    lsl r4, r4, #8
MobiClip_Code_0208F0A4:
    add r6, r6, r4, lsr #24
MobiClip_Code_0208F0A8:
    add r6, r6, r5, lsr #24
MobiClip_Code_0208F0AC:
    lsl r5, r5, #8
MobiClip_Code_0208F0B0:
    add r6, r6, r5, lsr #24
MobiClip_Code_0208F0B4:
    lsl r5, r5, #8
MobiClip_Code_0208F0B8:
    add r6, r6, r5, lsr #24
MobiClip_Code_0208F0BC:
    lsl r5, r5, #8
MobiClip_Code_0208F0C0:
    add r6, r6, r5, lsr #24
MobiClip_Code_0208F0C4:
    sub fp, fp, #1
MobiClip_Code_0208F0C8:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F0CC:
    add r6, r6, r4
MobiClip_Code_0208F0D0:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F0D4:
    add r6, r6, r4
MobiClip_Code_0208F0D8:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F0DC:
    add r6, r6, r4
MobiClip_Code_0208F0E0:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F0E4:
    add r6, r6, r4
MobiClip_Code_0208F0E8:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F0EC:
    add r6, r6, r4
MobiClip_Code_0208F0F0:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F0F4:
    add r6, r6, r4
MobiClip_Code_0208F0F8:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F0FC:
    add r6, r6, r4
MobiClip_Code_0208F100:
    ldrb r4, [fp], #1
MobiClip_Code_0208F104:
    add r6, r6, r4
MobiClip_Code_0208F108:
    add r6, r6, #8
MobiClip_Code_0208F10C:
    asr r6, r6, #4
MobiClip_Code_0208F110:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208F114:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208F118:
    mov r7, r6
MobiClip_Code_0208F11C:
    sub fp, fp, #0x700
MobiClip_Code_0208F120:
    stm fp, {r6, r7}
MobiClip_Code_0208F124:
    add fp, fp, #0x100
MobiClip_Code_0208F128:
    stm fp, {r6, r7}
MobiClip_Code_0208F12C:
    add fp, fp, #0x100
MobiClip_Code_0208F130:
    stm fp, {r6, r7}
MobiClip_Code_0208F134:
    add fp, fp, #0x100
MobiClip_Code_0208F138:
    stm fp, {r6, r7}
MobiClip_Code_0208F13C:
    add fp, fp, #0x100
MobiClip_Code_0208F140:
    stm fp, {r6, r7}
MobiClip_Code_0208F144:
    add fp, fp, #0x100
MobiClip_Code_0208F148:
    stm fp, {r6, r7}
MobiClip_Code_0208F14C:
    add fp, fp, #0x100
MobiClip_Code_0208F150:
    stm fp, {r6, r7}
MobiClip_Code_0208F154:
    add fp, fp, #0x100
MobiClip_Code_0208F158:
    stm fp, {r6, r7}
MobiClip_Code_0208F15C:
    sub fp, fp, #0x700
MobiClip_Code_0208F160:
    mov pc, lr
MobiClip_Code_0208F164:
    mov r6, #0
MobiClip_Code_0208F168:
    sub fp, fp, #1
MobiClip_Code_0208F16C:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F170:
    add r6, r6, r4
MobiClip_Code_0208F174:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F178:
    add r6, r6, r4
MobiClip_Code_0208F17C:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F180:
    add r6, r6, r4
MobiClip_Code_0208F184:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F188:
    add r6, r6, r4
MobiClip_Code_0208F18C:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F190:
    add r6, r6, r4
MobiClip_Code_0208F194:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F198:
    add r6, r6, r4
MobiClip_Code_0208F19C:
    ldrb r4, [fp], #0x100
MobiClip_Code_0208F1A0:
    add r6, r6, r4
MobiClip_Code_0208F1A4:
    ldrb r4, [fp], #1
MobiClip_Code_0208F1A8:
    add r6, r6, r4
MobiClip_Code_0208F1AC:
    add r6, r6, #4
MobiClip_Code_0208F1B0:
    asr r6, r6, #3
MobiClip_Code_0208F1B4:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208F1B8:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208F1BC:
    mov r7, r6
MobiClip_Code_0208F1C0:
    sub fp, fp, #0x700
MobiClip_Code_0208F1C4:
    stm fp, {r6, r7}
MobiClip_Code_0208F1C8:
    add fp, fp, #0x100
MobiClip_Code_0208F1CC:
    stm fp, {r6, r7}
MobiClip_Code_0208F1D0:
    add fp, fp, #0x100
MobiClip_Code_0208F1D4:
    stm fp, {r6, r7}
MobiClip_Code_0208F1D8:
    add fp, fp, #0x100
MobiClip_Code_0208F1DC:
    stm fp, {r6, r7}
MobiClip_Code_0208F1E0:
    add fp, fp, #0x100
MobiClip_Code_0208F1E4:
    stm fp, {r6, r7}
MobiClip_Code_0208F1E8:
    add fp, fp, #0x100
MobiClip_Code_0208F1EC:
    stm fp, {r6, r7}
MobiClip_Code_0208F1F0:
    add fp, fp, #0x100
MobiClip_Code_0208F1F4:
    stm fp, {r6, r7}
MobiClip_Code_0208F1F8:
    add fp, fp, #0x100
MobiClip_Code_0208F1FC:
    stm fp, {r6, r7}
MobiClip_Code_0208F200:
    sub fp, fp, #0x700
MobiClip_Code_0208F204:
    mov pc, lr
MobiClip_Code_0208F208:
    mov r6, #0
MobiClip_Code_0208F20C:
    sub r7, fp, #0x100
MobiClip_Code_0208F210:
    ldm r7, {r4, r5}
MobiClip_Code_0208F214:
    add r6, r6, r4, lsr #24
MobiClip_Code_0208F218:
    lsl r4, r4, #8
MobiClip_Code_0208F21C:
    add r6, r6, r4, lsr #24
MobiClip_Code_0208F220:
    lsl r4, r4, #8
MobiClip_Code_0208F224:
    add r6, r6, r4, lsr #24
MobiClip_Code_0208F228:
    lsl r4, r4, #8
MobiClip_Code_0208F22C:
    add r6, r6, r4, lsr #24
MobiClip_Code_0208F230:
    add r6, r6, r5, lsr #24
MobiClip_Code_0208F234:
    lsl r5, r5, #8
MobiClip_Code_0208F238:
    add r6, r6, r5, lsr #24
MobiClip_Code_0208F23C:
    lsl r5, r5, #8
MobiClip_Code_0208F240:
    add r6, r6, r5, lsr #24
MobiClip_Code_0208F244:
    lsl r5, r5, #8
MobiClip_Code_0208F248:
    add r6, r6, r5, lsr #24
MobiClip_Code_0208F24C:
    add r6, r6, #4
MobiClip_Code_0208F250:
    asr r6, r6, #3
MobiClip_Code_0208F254:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208F258:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208F25C:
    mov r7, r6
MobiClip_Code_0208F260:
    stm fp, {r6, r7}
MobiClip_Code_0208F264:
    add fp, fp, #0x100
MobiClip_Code_0208F268:
    stm fp, {r6, r7}
MobiClip_Code_0208F26C:
    add fp, fp, #0x100
MobiClip_Code_0208F270:
    stm fp, {r6, r7}
MobiClip_Code_0208F274:
    add fp, fp, #0x100
MobiClip_Code_0208F278:
    stm fp, {r6, r7}
MobiClip_Code_0208F27C:
    add fp, fp, #0x100
MobiClip_Code_0208F280:
    stm fp, {r6, r7}
MobiClip_Code_0208F284:
    add fp, fp, #0x100
MobiClip_Code_0208F288:
    stm fp, {r6, r7}
MobiClip_Code_0208F28C:
    add fp, fp, #0x100
MobiClip_Code_0208F290:
    stm fp, {r6, r7}
MobiClip_Code_0208F294:
    add fp, fp, #0x100
MobiClip_Code_0208F298:
    stm fp, {r6, r7}
MobiClip_Code_0208F29C:
    sub fp, fp, #0x700
MobiClip_Code_0208F2A0:
    mov pc, lr
MobiClip_Code_0208F2A4:
    mov r6, #0x80
MobiClip_Code_0208F2A8:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0208F2AC:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0208F2B0:
    mov r7, r6
MobiClip_Code_0208F2B4:
    stm fp, {r6, r7}
MobiClip_Code_0208F2B8:
    add fp, fp, #0x100
MobiClip_Code_0208F2BC:
    stm fp, {r6, r7}
MobiClip_Code_0208F2C0:
    add fp, fp, #0x100
MobiClip_Code_0208F2C4:
    stm fp, {r6, r7}
MobiClip_Code_0208F2C8:
    add fp, fp, #0x100
MobiClip_Code_0208F2CC:
    stm fp, {r6, r7}
MobiClip_Code_0208F2D0:
    add fp, fp, #0x100
MobiClip_Code_0208F2D4:
    stm fp, {r6, r7}
MobiClip_Code_0208F2D8:
    add fp, fp, #0x100
MobiClip_Code_0208F2DC:
    stm fp, {r6, r7}
MobiClip_Code_0208F2E0:
    add fp, fp, #0x100
MobiClip_Code_0208F2E4:
    stm fp, {r6, r7}
MobiClip_Code_0208F2E8:
    add fp, fp, #0x100
MobiClip_Code_0208F2EC:
    stm fp, {r6, r7}
MobiClip_Code_0208F2F0:
    sub fp, fp, #0x700
MobiClip_Code_0208F2F4:
    mov pc, lr
    /* control metadata 0x0208f2f8..0x0208f308 */
    .global gMobiClip_intra8_neighbor_dispatch
    .type gMobiClip_intra8_neighbor_dispatch, %object
gMobiClip_intra8_neighbor_dispatch:
    /* intra8_neighbor */
    .global gMobiClip_intra8_neighbor
gMobiClip_intra8_neighbor:
    .word MobiClip_Code_0208F2A4 - .
    .word MobiClip_Code_0208F208 - . + 0x4
    .word MobiClip_Code_0208F164 - . + 0x8
    .word MobiClip_Code_0208F080 - . + 0xc
    .size gMobiClip_intra8_neighbor_dispatch, . - gMobiClip_intra8_neighbor_dispatch
MobiClip_Code_0208F308:
    sub r5, pc, #0x18
MobiClip_Code_0208F30C:
    mov r8, #0
MobiClip_Code_0208F310:
    sub r6, fp, sl
MobiClip_Code_0208F314:
    lsls r7, r6, #0x18
MobiClip_Code_0208F318:
    addne r8, r8, #8
MobiClip_Code_0208F31C:
    cmp r6, #0x100
MobiClip_Code_0208F320:
    addge r8, r8, #4
MobiClip_Code_0208F324:
    ldr r6, [r5, r8]
MobiClip_Code_0208F328:
    add pc, r5, r6
MobiClip_Code_0208F32C:
    push {r3, ip, lr}
MobiClip_Code_0208F330:
    ldrb r3, [fp, #-1]!
MobiClip_Code_0208F334:
    ldrb ip, [fp, #0x100]!
MobiClip_Code_0208F338:
    ldrb sb, [fp, #0x100]!
MobiClip_Code_0208F33C:
    ldrb r6, [fp, #0x100]!
MobiClip_Code_0208F340:
    add r8, r3, ip
MobiClip_Code_0208F344:
    add r3, sb, r3
MobiClip_Code_0208F348:
    add r3, r3, ip, lsl #1
MobiClip_Code_0208F34C:
    add r3, r3, #2
MobiClip_Code_0208F350:
    asr lr, r3, #2
MobiClip_Code_0208F354:
    add r3, ip, sb
MobiClip_Code_0208F358:
    add ip, r6, ip
MobiClip_Code_0208F35C:
    add r8, r8, #1
MobiClip_Code_0208F360:
    asr r8, r8, #1
MobiClip_Code_0208F364:
    add ip, ip, sb, lsl #1
MobiClip_Code_0208F368:
    add r3, r3, #1
MobiClip_Code_0208F36C:
    asr r3, r3, #1
MobiClip_Code_0208F370:
    add ip, ip, #2
MobiClip_Code_0208F374:
    orr r8, r8, lr, lsl #8
MobiClip_Code_0208F378:
    orr r8, r8, r3, lsl #16
MobiClip_Code_0208F37C:
    asr ip, ip, #2
MobiClip_Code_0208F380:
    orr r8, r8, ip, lsl #24
MobiClip_Code_0208F384:
    sub lr, fp, #0x300
MobiClip_Code_0208F388:
    str r8, [lr, #1]
MobiClip_Code_0208F38C:
    add r8, sb, r6
MobiClip_Code_0208F390:
    add r8, r8, #1
MobiClip_Code_0208F394:
    asr lr, r8, #1
MobiClip_Code_0208F398:
    ldrb r8, [fp, #0x100]!
MobiClip_Code_0208F39C:
    orr r3, r3, ip, lsl #8
MobiClip_Code_0208F3A0:
    orr r3, r3, lr, lsl #16
MobiClip_Code_0208F3A4:
    add sb, r8, sb
MobiClip_Code_0208F3A8:
    add sb, sb, r6, lsl #1
MobiClip_Code_0208F3AC:
    add sb, sb, #2
MobiClip_Code_0208F3B0:
    asr r4, sb, #2
MobiClip_Code_0208F3B4:
    add sb, r6, r8
MobiClip_Code_0208F3B8:
    add sb, sb, #1
MobiClip_Code_0208F3BC:
    asr r5, sb, #1
MobiClip_Code_0208F3C0:
    ldrb sb, [fp, #0x100]!
MobiClip_Code_0208F3C4:
    orr r3, r3, r4, lsl #24
MobiClip_Code_0208F3C8:
    sub r7, fp, #0x400
MobiClip_Code_0208F3CC:
    str r3, [r7, #1]
MobiClip_Code_0208F3D0:
    add r6, sb, r6
MobiClip_Code_0208F3D4:
    add r6, r6, r8, lsl #1
MobiClip_Code_0208F3D8:
    add r6, r6, #2
MobiClip_Code_0208F3DC:
    orr r7, lr, r4, lsl #8
MobiClip_Code_0208F3E0:
    asr r6, r6, #2
MobiClip_Code_0208F3E4:
    orr r7, r7, r5, lsl #16
MobiClip_Code_0208F3E8:
    add r3, r8, sb
MobiClip_Code_0208F3EC:
    add r3, r3, #1
MobiClip_Code_0208F3F0:
    orr r7, r7, r6, lsl #24
MobiClip_Code_0208F3F4:
    sub ip, fp, #0x500
MobiClip_Code_0208F3F8:
    str r7, [ip, #5]
MobiClip_Code_0208F3FC:
    asr ip, r3, #1
MobiClip_Code_0208F400:
    ldrb r3, [fp, #0x100]!
MobiClip_Code_0208F404:
    orr lr, r5, r6, lsl #8
MobiClip_Code_0208F408:
    orr lr, lr, ip, lsl #16
MobiClip_Code_0208F40C:
    add r8, r3, r8
MobiClip_Code_0208F410:
    add r8, r8, sb, lsl #1
MobiClip_Code_0208F414:
    add r8, r8, #2
MobiClip_Code_0208F418:
    asr r8, r8, #2
MobiClip_Code_0208F41C:
    add r4, sb, r3
MobiClip_Code_0208F420:
    add r4, r4, #1
MobiClip_Code_0208F424:
    orr lr, lr, r8, lsl #24
MobiClip_Code_0208F428:
    sub r5, fp, #0x400
MobiClip_Code_0208F42C:
    str r7, [r5, #1]
MobiClip_Code_0208F430:
    str lr, [r5, #-0xfb]
MobiClip_Code_0208F434:
    asr r5, r4, #1
MobiClip_Code_0208F438:
    ldrb r4, [fp, #0x100]
MobiClip_Code_0208F43C:
    orr r8, ip, r8, lsl #8
MobiClip_Code_0208F440:
    orr r8, r8, r5, lsl #16
MobiClip_Code_0208F444:
    add sb, r4, sb
MobiClip_Code_0208F448:
    add sb, sb, r3, lsl #1
MobiClip_Code_0208F44C:
    add ip, r3, r4
MobiClip_Code_0208F450:
    add sb, sb, #2
MobiClip_Code_0208F454:
    asr sb, sb, #2
MobiClip_Code_0208F458:
    orr r8, r8, sb, lsl #24
MobiClip_Code_0208F45C:
    add r3, r4, r3
MobiClip_Code_0208F460:
    add r3, r3, r4, lsl #1
MobiClip_Code_0208F464:
    add ip, ip, #1
MobiClip_Code_0208F468:
    asr ip, ip, #1
MobiClip_Code_0208F46C:
    add r3, r3, #2
MobiClip_Code_0208F470:
    orr sb, r5, sb, lsl #8
MobiClip_Code_0208F474:
    orr sb, sb, ip, lsl #16
MobiClip_Code_0208F478:
    asr r3, r3, #2
MobiClip_Code_0208F47C:
    orr sb, sb, r3, lsl #24
MobiClip_Code_0208F480:
    sub r7, fp, #0x200
MobiClip_Code_0208F484:
    str r8, [r7, #-0x1fb]
MobiClip_Code_0208F488:
    str sb, [r7, #-0xfb]
MobiClip_Code_0208F48C:
    str lr, [r7, #-0xff]
MobiClip_Code_0208F490:
    str r8, [r7, #1]
MobiClip_Code_0208F494:
    orr r8, ip, r3, lsl #8
MobiClip_Code_0208F498:
    str sb, [fp, #-0xff]
MobiClip_Code_0208F49C:
    orr sb, r4, r4, lsl #8
MobiClip_Code_0208F4A0:
    orr r8, r8, r4, lsl #16
MobiClip_Code_0208F4A4:
    orr r8, r8, r4, lsl #24
MobiClip_Code_0208F4A8:
    orr sb, sb, r4, lsl #16
MobiClip_Code_0208F4AC:
    orr sb, sb, r4, lsl #24
MobiClip_Code_0208F4B0:
    str r8, [fp, #-0x1fb]
MobiClip_Code_0208F4B4:
    str sb, [fp, #-0xfb]
MobiClip_Code_0208F4B8:
    add fp, fp, #1
MobiClip_Code_0208F4BC:
    stm fp, {r8, sb}
MobiClip_Code_0208F4C0:
    str sb, [fp, #0x100]
MobiClip_Code_0208F4C4:
    str sb, [fp, #0x104]
MobiClip_Code_0208F4C8:
    sub fp, fp, #0x600
MobiClip_Code_0208F4CC:
    pop {r3, ip, pc}
MobiClip_Code_0208F4D0:
    push {r0, r1, r2, r3, sl, ip, lr}
MobiClip_Code_0208F4D4:
    sub r0, fp, #0x100
MobiClip_Code_0208F4D8:
    ldm r0, {r3, ip}
MobiClip_Code_0208F4DC:
    add r0, r0, #0x100
MobiClip_Code_0208F4E0:
    ldrb r1, [r0, #-1]
MobiClip_Code_0208F4E4:
    ldrb r2, [r0, #-0x101]
MobiClip_Code_0208F4E8:
    add r4, r1, r2
MobiClip_Code_0208F4EC:
    add r4, r4, #1
MobiClip_Code_0208F4F0:
    asr lr, r4, #1
MobiClip_Code_0208F4F4:
    and r7, r3, #0xff
MobiClip_Code_0208F4F8:
    add r4, r7, r1
MobiClip_Code_0208F4FC:
    add r4, r4, r2, lsl #1
MobiClip_Code_0208F500:
    add r4, r4, #2
MobiClip_Code_0208F504:
    asr r5, r4, #2
MobiClip_Code_0208F508:
    lsl r4, r3, #0x10
MobiClip_Code_0208F50C:
    lsr r4, r4, #0x18
MobiClip_Code_0208F510:
    add r6, r2, r4
MobiClip_Code_0208F514:
    lsl r8, r3, #8
MobiClip_Code_0208F518:
    add r6, r6, r7, lsl #1
MobiClip_Code_0208F51C:
    lsr sb, r8, #0x18
MobiClip_Code_0208F520:
    add r7, r7, sb
MobiClip_Code_0208F524:
    add r7, r7, r4, lsl #1
MobiClip_Code_0208F528:
    add r6, r6, #2
MobiClip_Code_0208F52C:
    lsr r3, r3, #0x18
MobiClip_Code_0208F530:
    add r4, r4, r3
MobiClip_Code_0208F534:
    asr r6, r6, #2
MobiClip_Code_0208F538:
    add r7, r7, #2
MobiClip_Code_0208F53C:
    orr r8, lr, r5, lsl #8
MobiClip_Code_0208F540:
    orr r8, r8, r6, lsl #16
MobiClip_Code_0208F544:
    asr r7, r7, #2
MobiClip_Code_0208F548:
    add r4, r4, sb, lsl #1
MobiClip_Code_0208F54C:
    add r4, r4, #2
MobiClip_Code_0208F550:
    orr fp, r8, r7, lsl #24
MobiClip_Code_0208F554:
    asr r8, r4, #2
MobiClip_Code_0208F558:
    and r4, ip, #0xff
MobiClip_Code_0208F55C:
    lsl sl, ip, #0x10
MobiClip_Code_0208F560:
    lsr sl, sl, #0x18
MobiClip_Code_0208F564:
    add sb, sb, r4
MobiClip_Code_0208F568:
    add sb, sb, r3, lsl #1
MobiClip_Code_0208F56C:
    lsl ip, ip, #8
MobiClip_Code_0208F570:
    add ip, r4, ip, lsr #24
MobiClip_Code_0208F574:
    add r3, r3, sl
MobiClip_Code_0208F578:
    add r3, r3, r4, lsl #1
MobiClip_Code_0208F57C:
    add sb, sb, #2
MobiClip_Code_0208F580:
    asr sb, sb, #2
MobiClip_Code_0208F584:
    add r3, r3, #2
MobiClip_Code_0208F588:
    add ip, ip, sl, lsl #1
MobiClip_Code_0208F58C:
    add ip, ip, #2
MobiClip_Code_0208F590:
    asr r3, r3, #2
MobiClip_Code_0208F594:
    orr r4, r8, sb, lsl #8
MobiClip_Code_0208F598:
    orr r3, r4, r3, lsl #16
MobiClip_Code_0208F59C:
    asr ip, ip, #2
MobiClip_Code_0208F5A0:
    orr ip, r3, ip, lsl #24
MobiClip_Code_0208F5A4:
    stm r0, {fp, ip}
MobiClip_Code_0208F5A8:
    ldrb ip, [r0, #0xff]
MobiClip_Code_0208F5AC:
    add r2, r2, ip
MobiClip_Code_0208F5B0:
    add r2, r2, r1, lsl #1
MobiClip_Code_0208F5B4:
    add r3, ip, r1
MobiClip_Code_0208F5B8:
    add r3, r3, #1
MobiClip_Code_0208F5BC:
    add r2, r2, #2
MobiClip_Code_0208F5C0:
    asr r2, r2, #2
MobiClip_Code_0208F5C4:
    asr r3, r3, #1
MobiClip_Code_0208F5C8:
    orr r4, r3, r2, lsl #8
MobiClip_Code_0208F5CC:
    orr r4, r4, lr, lsl #16
MobiClip_Code_0208F5D0:
    orr lr, r6, r7, lsl #8
MobiClip_Code_0208F5D4:
    orr lr, lr, r8, lsl #16
MobiClip_Code_0208F5D8:
    orr lr, lr, sb, lsl #24
MobiClip_Code_0208F5DC:
    orr r4, r4, r5, lsl #24
MobiClip_Code_0208F5E0:
    add r0, r0, #0x100
MobiClip_Code_0208F5E4:
    stm r0, {r4, lr}
MobiClip_Code_0208F5E8:
    ldrb lr, [r0, #0xff]
MobiClip_Code_0208F5EC:
    add r1, r1, lr
MobiClip_Code_0208F5F0:
    add r1, r1, ip, lsl #1
MobiClip_Code_0208F5F4:
    add r5, lr, ip
MobiClip_Code_0208F5F8:
    add r5, r5, #1
MobiClip_Code_0208F5FC:
    add r1, r1, #2
MobiClip_Code_0208F600:
    asr r1, r1, #2
MobiClip_Code_0208F604:
    asr r5, r5, #1
MobiClip_Code_0208F608:
    orr r6, r5, r1, lsl #8
MobiClip_Code_0208F60C:
    orr r3, r6, r3, lsl #16
MobiClip_Code_0208F610:
    orr r2, r3, r2, lsl #24
MobiClip_Code_0208F614:
    add r6, r0, #0x100
MobiClip_Code_0208F618:
    stm r6, {r2, fp}
MobiClip_Code_0208F61C:
    ldrb r3, [r0, #0x1ff]
MobiClip_Code_0208F620:
    add ip, ip, r3
MobiClip_Code_0208F624:
    add ip, ip, lr, lsl #1
MobiClip_Code_0208F628:
    add r6, r3, lr
MobiClip_Code_0208F62C:
    add r6, r6, #1
MobiClip_Code_0208F630:
    add ip, ip, #2
MobiClip_Code_0208F634:
    asr ip, ip, #2
MobiClip_Code_0208F638:
    asr r6, r6, #1
MobiClip_Code_0208F63C:
    orr r7, r6, ip, lsl #8
MobiClip_Code_0208F640:
    orr r5, r7, r5, lsl #16
MobiClip_Code_0208F644:
    orr r1, r5, r1, lsl #24
MobiClip_Code_0208F648:
    add r0, r0, #0x200
MobiClip_Code_0208F64C:
    stm r0, {r1, r4}
MobiClip_Code_0208F650:
    ldrb r4, [r0, #0xff]
MobiClip_Code_0208F654:
    str r2, [r0, #0x104]
MobiClip_Code_0208F658:
    add lr, lr, r4
MobiClip_Code_0208F65C:
    add lr, lr, r3, lsl #1
MobiClip_Code_0208F660:
    add r5, r4, r3
MobiClip_Code_0208F664:
    add r5, r5, #1
MobiClip_Code_0208F668:
    add lr, lr, #2
MobiClip_Code_0208F66C:
    asr lr, lr, #2
MobiClip_Code_0208F670:
    asr r5, r5, #1
MobiClip_Code_0208F674:
    orr r7, r5, lr, lsl #8
MobiClip_Code_0208F678:
    orr r6, r7, r6, lsl #16
MobiClip_Code_0208F67C:
    orr ip, r6, ip, lsl #24
MobiClip_Code_0208F680:
    str ip, [r0, #0x100]!
MobiClip_Code_0208F684:
    ldrb r2, [r0, #0xff]
MobiClip_Code_0208F688:
    str r1, [r0, #0x104]
MobiClip_Code_0208F68C:
    add r3, r3, r2
MobiClip_Code_0208F690:
    add r3, r3, r4, lsl #1
MobiClip_Code_0208F694:
    add r6, r2, r4
MobiClip_Code_0208F698:
    add r6, r6, #1
MobiClip_Code_0208F69C:
    add r3, r3, #2
MobiClip_Code_0208F6A0:
    asr r3, r3, #2
MobiClip_Code_0208F6A4:
    asr r6, r6, #1
MobiClip_Code_0208F6A8:
    orr r7, r6, r3, lsl #8
MobiClip_Code_0208F6AC:
    orr r5, r7, r5, lsl #16
MobiClip_Code_0208F6B0:
    orr lr, r5, lr, lsl #24
MobiClip_Code_0208F6B4:
    str lr, [r0, #0x100]!
MobiClip_Code_0208F6B8:
    ldrb r1, [r0, #0xff]
MobiClip_Code_0208F6BC:
    str ip, [r0, #0x104]
MobiClip_Code_0208F6C0:
    add r4, r4, r1
MobiClip_Code_0208F6C4:
    add r4, r4, r2, lsl #1
MobiClip_Code_0208F6C8:
    add r5, r1, r2
MobiClip_Code_0208F6CC:
    add r5, r5, #1
MobiClip_Code_0208F6D0:
    add r4, r4, #2
MobiClip_Code_0208F6D4:
    asr r4, r4, #2
MobiClip_Code_0208F6D8:
    asr r5, r5, #1
MobiClip_Code_0208F6DC:
    orr r7, r5, r4, lsl #8
MobiClip_Code_0208F6E0:
    orr r6, r7, r6, lsl #16
MobiClip_Code_0208F6E4:
    orr r3, r6, r3, lsl #24
MobiClip_Code_0208F6E8:
    str r3, [r0, #0x100]
MobiClip_Code_0208F6EC:
    ldrb ip, [r0, #0x1ff]
MobiClip_Code_0208F6F0:
    add r3, ip, r1
MobiClip_Code_0208F6F4:
    add r2, r2, ip
MobiClip_Code_0208F6F8:
    add r1, r2, r1, lsl #1
MobiClip_Code_0208F6FC:
    add r1, r1, #2
MobiClip_Code_0208F700:
    add r3, r3, #1
MobiClip_Code_0208F704:
    asr r3, r3, #1
MobiClip_Code_0208F708:
    asr r1, r1, #2
MobiClip_Code_0208F70C:
    orr r1, r3, r1, lsl #8
MobiClip_Code_0208F710:
    orr r1, r1, r5, lsl #16
MobiClip_Code_0208F714:
    orr r1, r1, r4, lsl #24
MobiClip_Code_0208F718:
    add r2, r0, #0x200
MobiClip_Code_0208F71C:
    stm r2, {r1, lr}
MobiClip_Code_0208F720:
    sub fp, r0, #0x500
MobiClip_Code_0208F724:
    pop {r0, r1, r2, r3, sl, ip, pc}
MobiClip_Code_0208F728:
    push {r0, r1, r2, r3, sl, ip, lr}
MobiClip_Code_0208F72C:
    sub r0, fp, #0x100
MobiClip_Code_0208F730:
    ldm r0, {r2, r7}
MobiClip_Code_0208F734:
    ldrb r3, [r0, #-1]
MobiClip_Code_0208F738:
    and sb, r2, #0xff
MobiClip_Code_0208F73C:
    sub sp, sp, #0x34
MobiClip_Code_0208F740:
    add r1, r3, sb
MobiClip_Code_0208F744:
    add r1, r1, #1
MobiClip_Code_0208F748:
    str r3, [sp, #0x30]
MobiClip_Code_0208F74C:
    asr r3, r1, #1
MobiClip_Code_0208F750:
    lsl r1, r2, #0x10
MobiClip_Code_0208F754:
    lsr sl, r1, #0x18
MobiClip_Code_0208F758:
    add r1, sb, sl
MobiClip_Code_0208F75C:
    add r1, r1, #1
MobiClip_Code_0208F760:
    str r3, [sp, #0x2c]
MobiClip_Code_0208F764:
    asr r3, r1, #1
MobiClip_Code_0208F768:
    lsl r1, r2, #8
MobiClip_Code_0208F76C:
    str r3, [sp, #0x28]
MobiClip_Code_0208F770:
    lsr r1, r1, #0x18
MobiClip_Code_0208F774:
    add r3, sl, r1
MobiClip_Code_0208F778:
    add r3, r3, #1
MobiClip_Code_0208F77C:
    asr lr, r3, #1
MobiClip_Code_0208F780:
    lsr r2, r2, #0x18
MobiClip_Code_0208F784:
    add r3, r1, r2
MobiClip_Code_0208F788:
    add r3, r3, #1
MobiClip_Code_0208F78C:
    asr r4, r3, #1
MobiClip_Code_0208F790:
    ldr r3, [sp, #0x2c]
MobiClip_Code_0208F794:
    ldr fp, [sp, #0x28]
MobiClip_Code_0208F798:
    orr r3, r3, fp, lsl #8
MobiClip_Code_0208F79C:
    orr r3, r3, lr, lsl #16
MobiClip_Code_0208F7A0:
    orr r3, r3, r4, lsl #24
MobiClip_Code_0208F7A4:
    str r3, [r0, #0x100]!
MobiClip_Code_0208F7A8:
    and r3, r7, #0xff
MobiClip_Code_0208F7AC:
    add ip, r2, r3
MobiClip_Code_0208F7B0:
    add ip, ip, #1
MobiClip_Code_0208F7B4:
    asr r5, ip, #1
MobiClip_Code_0208F7B8:
    lsl ip, r7, #0x10
MobiClip_Code_0208F7BC:
    lsr ip, ip, #0x18
MobiClip_Code_0208F7C0:
    add r6, r3, ip
MobiClip_Code_0208F7C4:
    add r6, r6, #1
MobiClip_Code_0208F7C8:
    asr r8, r6, #1
MobiClip_Code_0208F7CC:
    lsl r6, r7, #8
MobiClip_Code_0208F7D0:
    lsr r6, r6, #0x18
MobiClip_Code_0208F7D4:
    str r8, [sp, #0x24]
MobiClip_Code_0208F7D8:
    add r8, ip, r6
MobiClip_Code_0208F7DC:
    add r8, r8, #1
MobiClip_Code_0208F7E0:
    asr fp, r8, #1
MobiClip_Code_0208F7E4:
    add r8, sp, #0x1c
MobiClip_Code_0208F7E8:
    lsr r7, r7, #0x18
MobiClip_Code_0208F7EC:
    stm r8, {r7, fp}
MobiClip_Code_0208F7F0:
    ldr r8, [sp, #0x24]
MobiClip_Code_0208F7F4:
    add r7, r6, r7
MobiClip_Code_0208F7F8:
    add r7, r7, #1
MobiClip_Code_0208F7FC:
    orr r8, r5, r8, lsl #8
MobiClip_Code_0208F800:
    orr r8, r8, fp, lsl #16
MobiClip_Code_0208F804:
    asr r7, r7, #1
MobiClip_Code_0208F808:
    orr r7, r8, r7, lsl #24
MobiClip_Code_0208F80C:
    str r7, [r0, #4]
MobiClip_Code_0208F810:
    ldrb r7, [r0, #-1]
MobiClip_Code_0208F814:
    ldr r8, [sp, #0x30]
MobiClip_Code_0208F818:
    str r7, [sp, #0x18]
MobiClip_Code_0208F81C:
    add r7, r7, sb
MobiClip_Code_0208F820:
    add r7, r7, r8, lsl #1
MobiClip_Code_0208F824:
    add r8, r8, sl
MobiClip_Code_0208F828:
    add r8, r8, sb, lsl #1
MobiClip_Code_0208F82C:
    add sb, sb, r1
MobiClip_Code_0208F830:
    add sb, sb, sl, lsl #1
MobiClip_Code_0208F834:
    add sl, sl, r2
MobiClip_Code_0208F838:
    add sl, sl, r1, lsl #1
MobiClip_Code_0208F83C:
    add r1, r1, r3
MobiClip_Code_0208F840:
    add r8, r8, #2
MobiClip_Code_0208F844:
    add r7, r7, #2
MobiClip_Code_0208F848:
    asr r7, r7, #2
MobiClip_Code_0208F84C:
    asr r8, r8, #2
MobiClip_Code_0208F850:
    add r1, r1, r2, lsl #1
MobiClip_Code_0208F854:
    add sb, sb, #2
MobiClip_Code_0208F858:
    asr sb, sb, #2
MobiClip_Code_0208F85C:
    add r2, r2, ip
MobiClip_Code_0208F860:
    orr fp, r7, r8, lsl #8
MobiClip_Code_0208F864:
    add sl, sl, #2
MobiClip_Code_0208F868:
    asr sl, sl, #2
MobiClip_Code_0208F86C:
    orr fp, fp, sb, lsl #16
MobiClip_Code_0208F870:
    add r2, r2, r3, lsl #1
MobiClip_Code_0208F874:
    add r2, r2, #2
MobiClip_Code_0208F878:
    orr fp, fp, sl, lsl #24
MobiClip_Code_0208F87C:
    str fp, [r0, #0x100]!
MobiClip_Code_0208F880:
    asr r2, r2, #2
MobiClip_Code_0208F884:
    str r2, [sp, #0x14]
MobiClip_Code_0208F888:
    add r2, r3, r6
MobiClip_Code_0208F88C:
    add r2, r2, ip, lsl #1
MobiClip_Code_0208F890:
    add r2, r2, #2
MobiClip_Code_0208F894:
    asr r2, r2, #2
MobiClip_Code_0208F898:
    str r2, [sp, #0x10]
MobiClip_Code_0208F89C:
    ldr r2, [sp, #0x1c]
MobiClip_Code_0208F8A0:
    add r1, r1, #2
MobiClip_Code_0208F8A4:
    add r2, ip, r2
MobiClip_Code_0208F8A8:
    add r2, r2, r6, lsl #1
MobiClip_Code_0208F8AC:
    add r2, r2, #2
MobiClip_Code_0208F8B0:
    asr r3, r2, #2
MobiClip_Code_0208F8B4:
    ldr r2, [sp, #0x14]
MobiClip_Code_0208F8B8:
    asr r1, r1, #2
MobiClip_Code_0208F8BC:
    orr ip, r1, r2, lsl #8
MobiClip_Code_0208F8C0:
    ldr r2, [sp, #0x10]
MobiClip_Code_0208F8C4:
    orr r6, sl, r1, lsl #8
MobiClip_Code_0208F8C8:
    orr r2, ip, r2, lsl #16
MobiClip_Code_0208F8CC:
    orr r2, r2, r3, lsl #24
MobiClip_Code_0208F8D0:
    str r2, [r0, #4]
MobiClip_Code_0208F8D4:
    ldrb r2, [r0, #-1]
MobiClip_Code_0208F8D8:
    ldr r3, [sp, #0x30]
MobiClip_Code_0208F8DC:
    str r2, [sp, #0xc]
MobiClip_Code_0208F8E0:
    add r2, r2, r3
MobiClip_Code_0208F8E4:
    ldr r3, [sp, #0x18]
MobiClip_Code_0208F8E8:
    add r2, r2, r3, lsl #1
MobiClip_Code_0208F8EC:
    add r2, r2, #2
MobiClip_Code_0208F8F0:
    asr r2, r2, #2
MobiClip_Code_0208F8F4:
    ldr r3, [sp, #0x2c]
MobiClip_Code_0208F8F8:
    str r2, [sp, #8]
MobiClip_Code_0208F8FC:
    orr r2, r2, r3, lsl #8
MobiClip_Code_0208F900:
    ldr r3, [sp, #0x28]
MobiClip_Code_0208F904:
    orr r2, r2, r3, lsl #16
MobiClip_Code_0208F908:
    orr r2, r2, lr, lsl #24
MobiClip_Code_0208F90C:
    str r2, [r0, #0x100]!
MobiClip_Code_0208F910:
    ldr r3, [sp, #0x24]
MobiClip_Code_0208F914:
    orr r2, r4, r5, lsl #8
MobiClip_Code_0208F918:
    ldr fp, [sp, #0x20]
MobiClip_Code_0208F91C:
    orr r2, r2, r3, lsl #16
MobiClip_Code_0208F920:
    orr r2, r2, fp, lsl #24
MobiClip_Code_0208F924:
    str r2, [r0, #4]
MobiClip_Code_0208F928:
    ldrb r3, [r0, #-1]
MobiClip_Code_0208F92C:
    ldr r2, [sp, #0x18]
MobiClip_Code_0208F930:
    add ip, r3, r2
MobiClip_Code_0208F934:
    ldr r2, [sp, #0xc]
MobiClip_Code_0208F938:
    add r2, ip, r2, lsl #1
MobiClip_Code_0208F93C:
    add r2, r2, #2
MobiClip_Code_0208F940:
    asr ip, r2, #2
MobiClip_Code_0208F944:
    orr r2, ip, r7, lsl #8
MobiClip_Code_0208F948:
    orr r2, r2, r8, lsl #16
MobiClip_Code_0208F94C:
    orr r2, r2, sb, lsl #24
MobiClip_Code_0208F950:
    str r2, [r0, #0x100]!
MobiClip_Code_0208F954:
    ldr r2, [sp, #0x14]
MobiClip_Code_0208F958:
    orr r6, r6, r2, lsl #16
MobiClip_Code_0208F95C:
    ldr r2, [sp, #0x10]
MobiClip_Code_0208F960:
    orr r2, r6, r2, lsl #24
MobiClip_Code_0208F964:
    str r2, [r0, #4]
MobiClip_Code_0208F968:
    ldrb r6, [r0, #-1]
MobiClip_Code_0208F96C:
    ldr r2, [sp, #0xc]
MobiClip_Code_0208F970:
    ldr fp, [sp, #8]
MobiClip_Code_0208F974:
    add r2, r6, r2
MobiClip_Code_0208F978:
    add r2, r2, r3, lsl #1
MobiClip_Code_0208F97C:
    add r2, r2, #2
MobiClip_Code_0208F980:
    asr r2, r2, #2
MobiClip_Code_0208F984:
    str r2, [sp, #4]
MobiClip_Code_0208F988:
    orr r2, r2, fp, lsl #8
MobiClip_Code_0208F98C:
    ldr fp, [sp, #0x2c]
MobiClip_Code_0208F990:
    orr r2, r2, fp, lsl #16
MobiClip_Code_0208F994:
    ldr fp, [sp, #0x28]
MobiClip_Code_0208F998:
    orr r2, r2, fp, lsl #24
MobiClip_Code_0208F99C:
    str r2, [r0, #0x100]!
MobiClip_Code_0208F9A0:
    orr r2, lr, r4, lsl #8
MobiClip_Code_0208F9A4:
    ldr fp, [sp, #0x24]
MobiClip_Code_0208F9A8:
    orr r2, r2, r5, lsl #16
MobiClip_Code_0208F9AC:
    orr r2, r2, fp, lsl #24
MobiClip_Code_0208F9B0:
    str r2, [r0, #4]
MobiClip_Code_0208F9B4:
    ldrb fp, [r0, #-1]
MobiClip_Code_0208F9B8:
    add r2, fp, r3
MobiClip_Code_0208F9BC:
    add r2, r2, r6, lsl #1
MobiClip_Code_0208F9C0:
    add r2, r2, #2
MobiClip_Code_0208F9C4:
    asr r2, r2, #2
MobiClip_Code_0208F9C8:
    str r2, [sp]
MobiClip_Code_0208F9CC:
    orr r2, r2, ip, lsl #8
MobiClip_Code_0208F9D0:
    orr r2, r2, r7, lsl #16
MobiClip_Code_0208F9D4:
    orr r2, r2, r8, lsl #24
MobiClip_Code_0208F9D8:
    str r2, [r0, #0x100]!
MobiClip_Code_0208F9DC:
    orr r2, sb, sl, lsl #8
MobiClip_Code_0208F9E0:
    orr r3, r2, r1, lsl #16
MobiClip_Code_0208F9E4:
    ldr r2, [sp, #0x14]
MobiClip_Code_0208F9E8:
    orr r2, r3, r2, lsl #24
MobiClip_Code_0208F9EC:
    str r2, [r0, #4]
MobiClip_Code_0208F9F0:
    ldrb r2, [r0, #-1]
MobiClip_Code_0208F9F4:
    add r3, r2, r6
MobiClip_Code_0208F9F8:
    add r3, r3, fp, lsl #1
MobiClip_Code_0208F9FC:
    add r3, r3, #2
MobiClip_Code_0208FA00:
    ldr r6, [sp, #4]
MobiClip_Code_0208FA04:
    asr r3, r3, #2
MobiClip_Code_0208FA08:
    orr r3, r3, r6, lsl #8
MobiClip_Code_0208FA0C:
    ldr r6, [sp, #8]
MobiClip_Code_0208FA10:
    orr r3, r3, r6, lsl #16
MobiClip_Code_0208FA14:
    ldr r6, [sp, #0x2c]
MobiClip_Code_0208FA18:
    orr r3, r3, r6, lsl #24
MobiClip_Code_0208FA1C:
    str r3, [r0, #0x100]!
MobiClip_Code_0208FA20:
    ldr r3, [sp, #0x28]
MobiClip_Code_0208FA24:
    orr r3, r3, lr, lsl #8
MobiClip_Code_0208FA28:
    orr r3, r3, r4, lsl #16
MobiClip_Code_0208FA2C:
    orr r3, r3, r5, lsl #24
MobiClip_Code_0208FA30:
    str r3, [r0, #4]
MobiClip_Code_0208FA34:
    ldrb r3, [r0, #-1]
MobiClip_Code_0208FA38:
    add r3, r3, fp
MobiClip_Code_0208FA3C:
    add r2, r3, r2, lsl #1
MobiClip_Code_0208FA40:
    add r2, r2, #2
MobiClip_Code_0208FA44:
    asr r2, r2, #2
MobiClip_Code_0208FA48:
    ldr r3, [sp]
MobiClip_Code_0208FA4C:
    orr r2, r2, r3, lsl #8
MobiClip_Code_0208FA50:
    orr r2, r2, ip, lsl #16
MobiClip_Code_0208FA54:
    orr r2, r2, r7, lsl #24
MobiClip_Code_0208FA58:
    add r0, r0, #0x100
MobiClip_Code_0208FA5C:
    str r2, [r0]
MobiClip_Code_0208FA60:
    orr r2, r8, sb, lsl #8
MobiClip_Code_0208FA64:
    orr r2, r2, sl, lsl #16
MobiClip_Code_0208FA68:
    orr r1, r2, r1, lsl #24
MobiClip_Code_0208FA6C:
    str r1, [r0, #4]
MobiClip_Code_0208FA70:
    add sp, sp, #0x34
MobiClip_Code_0208FA74:
    sub fp, r0, #0x700
MobiClip_Code_0208FA78:
    pop {r0, r1, r2, r3, sl, ip, pc}
MobiClip_Code_0208FA7C:
    push {r0, r1, r2, r3, sl, ip, lr}
MobiClip_Code_0208FA80:
    sub sp, sp, #4
MobiClip_Code_0208FA84:
    ldr r6, [fp, #-0x100]
MobiClip_Code_0208FA88:
    ldrb r5, [fp, #-1]
MobiClip_Code_0208FA8C:
    ldrb r4, [fp, #-0x101]
MobiClip_Code_0208FA90:
    and r3, r6, #0xff
MobiClip_Code_0208FA94:
    lsl r2, r6, #0x10
MobiClip_Code_0208FA98:
    lsr ip, r2, #0x18
MobiClip_Code_0208FA9C:
    add r2, r4, ip
MobiClip_Code_0208FAA0:
    add r1, r5, r3
MobiClip_Code_0208FAA4:
    add r2, r2, r3, lsl #1
MobiClip_Code_0208FAA8:
    lsl lr, r6, #8
MobiClip_Code_0208FAAC:
    lsr lr, lr, #0x18
MobiClip_Code_0208FAB0:
    add r3, r3, lr
MobiClip_Code_0208FAB4:
    add r3, r3, ip, lsl #1
MobiClip_Code_0208FAB8:
    lsr r6, r6, #0x18
MobiClip_Code_0208FABC:
    add r1, r1, r4, lsl #1
MobiClip_Code_0208FAC0:
    add r1, r1, #2
MobiClip_Code_0208FAC4:
    add ip, ip, r6
MobiClip_Code_0208FAC8:
    add r2, r2, #2
MobiClip_Code_0208FACC:
    asr r2, r2, #2
MobiClip_Code_0208FAD0:
    add ip, ip, lr, lsl #1
MobiClip_Code_0208FAD4:
    asr r1, r1, #2
MobiClip_Code_0208FAD8:
    add r3, r3, #2
MobiClip_Code_0208FADC:
    asr r3, r3, #2
MobiClip_Code_0208FAE0:
    orr r8, r1, r2, lsl #8
MobiClip_Code_0208FAE4:
    add ip, ip, #2
MobiClip_Code_0208FAE8:
    asr ip, ip, #2
MobiClip_Code_0208FAEC:
    orr r8, r8, r3, lsl #16
MobiClip_Code_0208FAF0:
    orr r8, r8, ip, lsl #24
MobiClip_Code_0208FAF4:
    str r8, [sp]
MobiClip_Code_0208FAF8:
    str r8, [fp]
MobiClip_Code_0208FAFC:
    sub r7, fp, #0x100
MobiClip_Code_0208FB00:
    ldr r7, [r7, #4]
MobiClip_Code_0208FB04:
    orr r0, r3, ip, lsl #8
MobiClip_Code_0208FB08:
    and r8, r7, #0xff
MobiClip_Code_0208FB0C:
    lsl sb, r7, #0x10
MobiClip_Code_0208FB10:
    lsr sb, sb, #0x18
MobiClip_Code_0208FB14:
    add lr, lr, r8
MobiClip_Code_0208FB18:
    add lr, lr, r6, lsl #1
MobiClip_Code_0208FB1C:
    lsl sl, r7, #8
MobiClip_Code_0208FB20:
    lsr sl, sl, #0x18
MobiClip_Code_0208FB24:
    add r6, r6, sb
MobiClip_Code_0208FB28:
    add r6, r6, r8, lsl #1
MobiClip_Code_0208FB2C:
    add r8, r8, sl
MobiClip_Code_0208FB30:
    add r7, sb, r7, lsr #24
MobiClip_Code_0208FB34:
    add lr, lr, #2
MobiClip_Code_0208FB38:
    asr lr, lr, #2
MobiClip_Code_0208FB3C:
    add r7, r7, sl, lsl #1
MobiClip_Code_0208FB40:
    add r8, r8, sb, lsl #1
MobiClip_Code_0208FB44:
    add r6, r6, #2
MobiClip_Code_0208FB48:
    asr r6, r6, #2
MobiClip_Code_0208FB4C:
    add r8, r8, #2
MobiClip_Code_0208FB50:
    asr r8, r8, #2
MobiClip_Code_0208FB54:
    orr sb, lr, r6, lsl #8
MobiClip_Code_0208FB58:
    add r7, r7, #2
MobiClip_Code_0208FB5C:
    asr r7, r7, #2
MobiClip_Code_0208FB60:
    orr sb, sb, r8, lsl #16
MobiClip_Code_0208FB64:
    orr r7, sb, r7, lsl #24
MobiClip_Code_0208FB68:
    str r7, [fp, #4]
MobiClip_Code_0208FB6C:
    ldrb r7, [fp, #0xff]
MobiClip_Code_0208FB70:
    orr sl, ip, lr, lsl #8
MobiClip_Code_0208FB74:
    orr sl, sl, r6, lsl #16
MobiClip_Code_0208FB78:
    add r4, r7, r4
MobiClip_Code_0208FB7C:
    add r4, r4, r5, lsl #1
MobiClip_Code_0208FB80:
    add r4, r4, #2
MobiClip_Code_0208FB84:
    asr r4, r4, #2
MobiClip_Code_0208FB88:
    orr sb, r4, r1, lsl #8
MobiClip_Code_0208FB8C:
    orr sb, sb, r2, lsl #16
MobiClip_Code_0208FB90:
    orr r8, sl, r8, lsl #24
MobiClip_Code_0208FB94:
    str r8, [fp, #0x104]
MobiClip_Code_0208FB98:
    orr sb, sb, r3, lsl #24
MobiClip_Code_0208FB9C:
    str sb, [fp, #0x100]!
MobiClip_Code_0208FBA0:
    ldrb r8, [fp, #0xff]
MobiClip_Code_0208FBA4:
    orr r0, r0, lr, lsl #16
MobiClip_Code_0208FBA8:
    orr r6, r0, r6, lsl #24
MobiClip_Code_0208FBAC:
    add r5, r8, r5
MobiClip_Code_0208FBB0:
    add r5, r5, r7, lsl #1
MobiClip_Code_0208FBB4:
    add r5, r5, #2
MobiClip_Code_0208FBB8:
    asr r5, r5, #2
MobiClip_Code_0208FBBC:
    orr sl, r5, r4, lsl #8
MobiClip_Code_0208FBC0:
    orr sl, sl, r1, lsl #16
MobiClip_Code_0208FBC4:
    orr sl, sl, r2, lsl #24
MobiClip_Code_0208FBC8:
    str r6, [fp, #0x104]
MobiClip_Code_0208FBCC:
    str sl, [fp, #0x100]!
MobiClip_Code_0208FBD0:
    ldrb r6, [fp, #0xff]
MobiClip_Code_0208FBD4:
    orr r2, r2, r3, lsl #8
MobiClip_Code_0208FBD8:
    orr r2, r2, ip, lsl #16
MobiClip_Code_0208FBDC:
    add r7, r6, r7
MobiClip_Code_0208FBE0:
    add r7, r7, r8, lsl #1
MobiClip_Code_0208FBE4:
    add r7, r7, #2
MobiClip_Code_0208FBE8:
    asr r7, r7, #2
MobiClip_Code_0208FBEC:
    orr r0, r7, r5, lsl #8
MobiClip_Code_0208FBF0:
    orr r0, r0, r4, lsl #16
MobiClip_Code_0208FBF4:
    orr r1, r0, r1, lsl #24
MobiClip_Code_0208FBF8:
    orr r2, r2, lr, lsl #24
MobiClip_Code_0208FBFC:
    add fp, fp, #0x100
MobiClip_Code_0208FC00:
    stm fp, {r1, r2}
MobiClip_Code_0208FC04:
    ldrb r2, [fp, #0xff]
MobiClip_Code_0208FC08:
    add r3, r2, r8
MobiClip_Code_0208FC0C:
    add r3, r3, r6, lsl #1
MobiClip_Code_0208FC10:
    add r3, r3, #2
MobiClip_Code_0208FC14:
    asr r3, r3, #2
MobiClip_Code_0208FC18:
    orr ip, r3, r7, lsl #8
MobiClip_Code_0208FC1C:
    orr ip, ip, r5, lsl #16
MobiClip_Code_0208FC20:
    orr ip, ip, r4, lsl #24
MobiClip_Code_0208FC24:
    str ip, [fp, #0x100]!
MobiClip_Code_0208FC28:
    ldr r8, [sp]
MobiClip_Code_0208FC2C:
    str r8, [fp, #4]
MobiClip_Code_0208FC30:
    ldrb ip, [fp, #0xff]
MobiClip_Code_0208FC34:
    add lr, ip, r6
MobiClip_Code_0208FC38:
    add lr, lr, r2, lsl #1
MobiClip_Code_0208FC3C:
    add lr, lr, #2
MobiClip_Code_0208FC40:
    asr lr, lr, #2
MobiClip_Code_0208FC44:
    orr r4, lr, r3, lsl #8
MobiClip_Code_0208FC48:
    orr r4, r4, r7, lsl #16
MobiClip_Code_0208FC4C:
    orr r4, r4, r5, lsl #24
MobiClip_Code_0208FC50:
    add fp, fp, #0x100
MobiClip_Code_0208FC54:
    stm fp, {r4, sb}
MobiClip_Code_0208FC58:
    ldrb r4, [fp, #0xff]
MobiClip_Code_0208FC5C:
    add fp, fp, #0x100
MobiClip_Code_0208FC60:
    add r2, r4, r2
MobiClip_Code_0208FC64:
    add r2, r2, ip, lsl #1
MobiClip_Code_0208FC68:
    add r2, r2, #2
MobiClip_Code_0208FC6C:
    asr r2, r2, #2
MobiClip_Code_0208FC70:
    orr r5, r2, lr, lsl #8
MobiClip_Code_0208FC74:
    orr r5, r5, r3, lsl #16
MobiClip_Code_0208FC78:
    orr r5, r5, r7, lsl #24
MobiClip_Code_0208FC7C:
    stm fp, {r5, sl}
MobiClip_Code_0208FC80:
    ldrb r5, [fp, #0xff]
MobiClip_Code_0208FC84:
    add ip, r5, ip
MobiClip_Code_0208FC88:
    add ip, ip, r4, lsl #1
MobiClip_Code_0208FC8C:
    add ip, ip, #2
MobiClip_Code_0208FC90:
    asr ip, ip, #2
MobiClip_Code_0208FC94:
    orr r2, ip, r2, lsl #8
MobiClip_Code_0208FC98:
    orr r2, r2, lr, lsl #16
MobiClip_Code_0208FC9C:
    orr r2, r2, r3, lsl #24
MobiClip_Code_0208FCA0:
    str r2, [fp, #0x100]
MobiClip_Code_0208FCA4:
    str r1, [fp, #0x104]
MobiClip_Code_0208FCA8:
    sub fp, fp, #0x600
MobiClip_Code_0208FCAC:
    add sp, sp, #4
MobiClip_Code_0208FCB0:
    pop {r0, r1, r2, r3, sl, ip, pc}
MobiClip_Code_0208FCB4:
    push {r0, r1, r2, r3, sl, ip, lr}
MobiClip_Code_0208FCB8:
    mov r0, fp
MobiClip_Code_0208FCBC:
    ldr r2, [r0, #-0x100]
MobiClip_Code_0208FCC0:
    sub sp, sp, #0x30
MobiClip_Code_0208FCC4:
    lsl r1, r2, #0x10
MobiClip_Code_0208FCC8:
    lsr fp, r1, #0x18
MobiClip_Code_0208FCCC:
    and sl, r2, #0xff
MobiClip_Code_0208FCD0:
    add r1, sl, fp
MobiClip_Code_0208FCD4:
    add r1, r1, #1
MobiClip_Code_0208FCD8:
    asr ip, r1, #1
MobiClip_Code_0208FCDC:
    lsl r1, r2, #8
MobiClip_Code_0208FCE0:
    lsr r1, r1, #0x18
MobiClip_Code_0208FCE4:
    add lr, fp, r1
MobiClip_Code_0208FCE8:
    add lr, lr, #1
MobiClip_Code_0208FCEC:
    str sl, [sp, #0x2c]
MobiClip_Code_0208FCF0:
    asr sl, lr, #1
MobiClip_Code_0208FCF4:
    lsr r2, r2, #0x18
MobiClip_Code_0208FCF8:
    add lr, r1, r2
MobiClip_Code_0208FCFC:
    add lr, lr, #1
MobiClip_Code_0208FD00:
    str fp, [sp, #0x28]
MobiClip_Code_0208FD04:
    asr fp, lr, #1
MobiClip_Code_0208FD08:
    sub sb, r0, #0x100
MobiClip_Code_0208FD0C:
    str fp, [sp, #0x20]
MobiClip_Code_0208FD10:
    str sl, [sp, #0x24]
MobiClip_Code_0208FD14:
    ldr r4, [sb, #4]
MobiClip_Code_0208FD18:
    and r3, r4, #0xff
MobiClip_Code_0208FD1C:
    add lr, r2, r3
MobiClip_Code_0208FD20:
    ldr sl, [sp, #0x24]
MobiClip_Code_0208FD24:
    add lr, lr, #1
MobiClip_Code_0208FD28:
    asr r5, lr, #1
MobiClip_Code_0208FD2C:
    orr ip, ip, sl, lsl #8
MobiClip_Code_0208FD30:
    orr ip, ip, fp, lsl #16
MobiClip_Code_0208FD34:
    orr ip, ip, r5, lsl #24
MobiClip_Code_0208FD38:
    str r5, [sp, #0x1c]
MobiClip_Code_0208FD3C:
    str ip, [r0]
MobiClip_Code_0208FD40:
    lsl ip, r4, #0x10
MobiClip_Code_0208FD44:
    lsr ip, ip, #0x18
MobiClip_Code_0208FD48:
    add lr, r3, ip
MobiClip_Code_0208FD4C:
    add lr, lr, #1
MobiClip_Code_0208FD50:
    asr r8, lr, #1
MobiClip_Code_0208FD54:
    lsl lr, r4, #8
MobiClip_Code_0208FD58:
    lsr lr, lr, #0x18
MobiClip_Code_0208FD5C:
    add r5, ip, lr
MobiClip_Code_0208FD60:
    add r5, r5, #1
MobiClip_Code_0208FD64:
    asr r6, r5, #1
MobiClip_Code_0208FD68:
    lsr r4, r4, #0x18
MobiClip_Code_0208FD6C:
    str r8, [sp, #0x18]
MobiClip_Code_0208FD70:
    ldr r8, [sb, #8]
MobiClip_Code_0208FD74:
    add r5, lr, r4
MobiClip_Code_0208FD78:
    add r5, r5, #1
MobiClip_Code_0208FD7C:
    asr r7, r5, #1
MobiClip_Code_0208FD80:
    and r5, r8, #0xff
MobiClip_Code_0208FD84:
    ldr sl, [sp, #0x18]
MobiClip_Code_0208FD88:
    add sb, r4, r5
MobiClip_Code_0208FD8C:
    add sb, sb, #1
MobiClip_Code_0208FD90:
    orr sl, sl, r6, lsl #8
MobiClip_Code_0208FD94:
    orr sl, sl, r7, lsl #16
MobiClip_Code_0208FD98:
    asr sb, sb, #1
MobiClip_Code_0208FD9C:
    orr sl, sl, sb, lsl #24
MobiClip_Code_0208FDA0:
    str sl, [r0, #4]
MobiClip_Code_0208FDA4:
    ldr sl, [sp, #0x2c]
MobiClip_Code_0208FDA8:
    ldr fp, [sp, #0x28]
MobiClip_Code_0208FDAC:
    add sl, sl, r1
MobiClip_Code_0208FDB0:
    add sl, sl, fp, lsl #1
MobiClip_Code_0208FDB4:
    add sl, sl, #2
MobiClip_Code_0208FDB8:
    asr sl, sl, #2
MobiClip_Code_0208FDBC:
    str sl, [sp, #0x14]
MobiClip_Code_0208FDC0:
    add sl, fp, r2
MobiClip_Code_0208FDC4:
    add sl, sl, r1, lsl #1
MobiClip_Code_0208FDC8:
    add r1, r1, r3
MobiClip_Code_0208FDCC:
    add r1, r1, r2, lsl #1
MobiClip_Code_0208FDD0:
    add r1, r1, #2
MobiClip_Code_0208FDD4:
    add sl, sl, #2
MobiClip_Code_0208FDD8:
    asr sl, sl, #2
MobiClip_Code_0208FDDC:
    asr r1, r1, #2
MobiClip_Code_0208FDE0:
    add fp, sp, #0xc
MobiClip_Code_0208FDE4:
    stm fp, {r1, sl}
MobiClip_Code_0208FDE8:
    add r1, r2, ip
MobiClip_Code_0208FDEC:
    add sl, sp, #0x10
MobiClip_Code_0208FDF0:
    ldm sl, {r2, sl}
MobiClip_Code_0208FDF4:
    add r1, r1, r3, lsl #1
MobiClip_Code_0208FDF8:
    orr r2, sl, r2, lsl #8
MobiClip_Code_0208FDFC:
    ldr sl, [sp, #0xc]
MobiClip_Code_0208FE00:
    add r1, r1, #2
MobiClip_Code_0208FE04:
    asr r1, r1, #2
MobiClip_Code_0208FE08:
    orr r2, r2, sl, lsl #16
MobiClip_Code_0208FE0C:
    orr r2, r2, r1, lsl #24
MobiClip_Code_0208FE10:
    str r2, [r0, #0x100]!
MobiClip_Code_0208FE14:
    add r2, r3, lr
MobiClip_Code_0208FE18:
    add r3, ip, r4
MobiClip_Code_0208FE1C:
    add r2, r2, ip, lsl #1
MobiClip_Code_0208FE20:
    add r3, r3, lr, lsl #1
MobiClip_Code_0208FE24:
    add ip, lr, r5
MobiClip_Code_0208FE28:
    add ip, ip, r4, lsl #1
MobiClip_Code_0208FE2C:
    add ip, ip, #2
MobiClip_Code_0208FE30:
    asr lr, ip, #2
MobiClip_Code_0208FE34:
    lsl ip, r8, #0x10
MobiClip_Code_0208FE38:
    lsr ip, ip, #0x18
MobiClip_Code_0208FE3C:
    add r4, r4, ip
MobiClip_Code_0208FE40:
    add r3, r3, #2
MobiClip_Code_0208FE44:
    add r2, r2, #2
MobiClip_Code_0208FE48:
    asr r2, r2, #2
MobiClip_Code_0208FE4C:
    asr r3, r3, #2
MobiClip_Code_0208FE50:
    add r4, r4, r5, lsl #1
MobiClip_Code_0208FE54:
    add r4, r4, #2
MobiClip_Code_0208FE58:
    orr sl, r2, r3, lsl #8
MobiClip_Code_0208FE5C:
    orr sl, sl, lr, lsl #16
MobiClip_Code_0208FE60:
    asr r4, r4, #2
MobiClip_Code_0208FE64:
    orr sl, sl, r4, lsl #24
MobiClip_Code_0208FE68:
    str sl, [r0, #4]
MobiClip_Code_0208FE6C:
    ldr sl, [sp, #0x24]
MobiClip_Code_0208FE70:
    ldr fp, [sp, #0x20]
MobiClip_Code_0208FE74:
    orr sl, sl, fp, lsl #8
MobiClip_Code_0208FE78:
    ldr fp, [sp, #0x1c]
MobiClip_Code_0208FE7C:
    orr sl, sl, fp, lsl #16
MobiClip_Code_0208FE80:
    ldr fp, [sp, #0x18]
MobiClip_Code_0208FE84:
    orr sl, sl, fp, lsl #24
MobiClip_Code_0208FE88:
    str sl, [r0, #0x100]!
MobiClip_Code_0208FE8C:
    add sl, r5, ip
MobiClip_Code_0208FE90:
    add sl, sl, #1
MobiClip_Code_0208FE94:
    asr fp, sl, #1
MobiClip_Code_0208FE98:
    orr sl, r6, r7, lsl #8
MobiClip_Code_0208FE9C:
    orr sl, sl, sb, lsl #16
MobiClip_Code_0208FEA0:
    orr sl, sl, fp, lsl #24
MobiClip_Code_0208FEA4:
    str fp, [sp, #8]
MobiClip_Code_0208FEA8:
    str sl, [r0, #4]
MobiClip_Code_0208FEAC:
    ldr sl, [sp, #0x10]
MobiClip_Code_0208FEB0:
    ldr fp, [sp, #0xc]
MobiClip_Code_0208FEB4:
    orr sl, sl, fp, lsl #8
MobiClip_Code_0208FEB8:
    orr sl, sl, r1, lsl #16
MobiClip_Code_0208FEBC:
    orr sl, sl, r2, lsl #24
MobiClip_Code_0208FEC0:
    str sl, [r0, #0x100]!
MobiClip_Code_0208FEC4:
    lsl sl, r8, #8
MobiClip_Code_0208FEC8:
    lsr sl, sl, #0x18
MobiClip_Code_0208FECC:
    add r5, r5, sl
MobiClip_Code_0208FED0:
    add r5, r5, ip, lsl #1
MobiClip_Code_0208FED4:
    add r5, r5, #2
MobiClip_Code_0208FED8:
    asr fp, r5, #2
MobiClip_Code_0208FEDC:
    orr r5, r3, lr, lsl #8
MobiClip_Code_0208FEE0:
    orr r5, r5, r4, lsl #16
MobiClip_Code_0208FEE4:
    orr r5, r5, fp, lsl #24
MobiClip_Code_0208FEE8:
    str fp, [sp, #4]
MobiClip_Code_0208FEEC:
    str r5, [r0, #4]
MobiClip_Code_0208FEF0:
    add fp, sp, #0x1c
MobiClip_Code_0208FEF4:
    ldm fp, {r5, fp}
MobiClip_Code_0208FEF8:
    orr r5, fp, r5, lsl #8
MobiClip_Code_0208FEFC:
    ldr fp, [sp, #0x18]
MobiClip_Code_0208FF00:
    orr r5, r5, fp, lsl #16
MobiClip_Code_0208FF04:
    orr r5, r5, r6, lsl #24
MobiClip_Code_0208FF08:
    str r5, [r0, #0x100]!
MobiClip_Code_0208FF0C:
    add r5, ip, sl
MobiClip_Code_0208FF10:
    add r5, r5, #1
MobiClip_Code_0208FF14:
    asr fp, r5, #1
MobiClip_Code_0208FF18:
    str fp, [sp]
MobiClip_Code_0208FF1C:
    ldr fp, [sp, #8]
MobiClip_Code_0208FF20:
    orr r5, r7, sb, lsl #8
MobiClip_Code_0208FF24:
    orr r5, r5, fp, lsl #16
MobiClip_Code_0208FF28:
    ldr fp, [sp]
MobiClip_Code_0208FF2C:
    orr r5, r5, fp, lsl #24
MobiClip_Code_0208FF30:
    str r5, [r0, #4]
MobiClip_Code_0208FF34:
    ldr fp, [sp, #0xc]
MobiClip_Code_0208FF38:
    orr r5, fp, r1, lsl #8
MobiClip_Code_0208FF3C:
    orr r5, r5, r2, lsl #16
MobiClip_Code_0208FF40:
    orr r5, r5, r3, lsl #24
MobiClip_Code_0208FF44:
    str r5, [r0, #0x100]!
MobiClip_Code_0208FF48:
    lsr r5, r8, #0x18
MobiClip_Code_0208FF4C:
    add ip, ip, r5
MobiClip_Code_0208FF50:
    ldr fp, [sp, #4]
MobiClip_Code_0208FF54:
    add ip, ip, sl, lsl #1
MobiClip_Code_0208FF58:
    orr r8, lr, r4, lsl #8
MobiClip_Code_0208FF5C:
    orr r8, r8, fp, lsl #16
MobiClip_Code_0208FF60:
    add ip, ip, #2
MobiClip_Code_0208FF64:
    asr ip, ip, #2
MobiClip_Code_0208FF68:
    orr r8, r8, ip, lsl #24
MobiClip_Code_0208FF6C:
    str r8, [r0, #4]
MobiClip_Code_0208FF70:
    add fp, sp, #0x18
MobiClip_Code_0208FF74:
    ldm fp, {r8, fp}
MobiClip_Code_0208FF78:
    orr r1, r1, r2, lsl #8
MobiClip_Code_0208FF7C:
    orr r8, fp, r8, lsl #8
MobiClip_Code_0208FF80:
    orr r6, r8, r6, lsl #16
MobiClip_Code_0208FF84:
    orr r6, r6, r7, lsl #24
MobiClip_Code_0208FF88:
    str r6, [r0, #0x100]!
MobiClip_Code_0208FF8C:
    ldr fp, [sp, #8]
MobiClip_Code_0208FF90:
    add r6, sl, r5
MobiClip_Code_0208FF94:
    orr r7, sb, fp, lsl #8
MobiClip_Code_0208FF98:
    ldr fp, [sp]
MobiClip_Code_0208FF9C:
    add r6, r6, #1
MobiClip_Code_0208FFA0:
    orr r1, r1, r3, lsl #16
MobiClip_Code_0208FFA4:
    orr r1, r1, lr, lsl #24
MobiClip_Code_0208FFA8:
    asr r6, r6, #1
MobiClip_Code_0208FFAC:
    orr r7, r7, fp, lsl #16
MobiClip_Code_0208FFB0:
    orr r6, r7, r6, lsl #24
MobiClip_Code_0208FFB4:
    str r1, [r0, #0x100]
MobiClip_Code_0208FFB8:
    str r6, [r0, #4]
MobiClip_Code_0208FFBC:
    sub fp, r0, #0x700
MobiClip_Code_0208FFC0:
    ldrb r1, [fp, #0xc]
MobiClip_Code_0208FFC4:
    ldr fp, [sp, #4]
MobiClip_Code_0208FFC8:
    add r1, sl, r1
MobiClip_Code_0208FFCC:
    add r1, r1, r5, lsl #1
MobiClip_Code_0208FFD0:
    add r1, r1, #2
MobiClip_Code_0208FFD4:
    asr r1, r1, #2
MobiClip_Code_0208FFD8:
    orr r2, r4, fp, lsl #8
MobiClip_Code_0208FFDC:
    orr r2, r2, ip, lsl #16
MobiClip_Code_0208FFE0:
    orr r1, r2, r1, lsl #24
MobiClip_Code_0208FFE4:
    str r1, [r0, #0x104]
MobiClip_Code_0208FFE8:
    add sp, sp, #0x30
MobiClip_Code_0208FFEC:
    sub fp, r0, #0x600
MobiClip_Code_0208FFF0:
    pop {r0, r1, r2, r3, sl, ip, pc}
MobiClip_Code_0208FFF4:
    ldr r4, [fp, #-0x100]
MobiClip_Code_0208FFF8:
    str r4, [fp], #0x100
MobiClip_Code_0208FFFC:
    str r4, [fp], #0x100
MobiClip_Code_02090000:
    str r4, [fp], #0x100
MobiClip_Code_02090004:
    str r4, [fp], #0x100
MobiClip_Code_02090008:
    sub fp, fp, #0x400
MobiClip_Code_0209000C:
    mov pc, lr
MobiClip_Code_02090010:
    ldrb r6, [fp, #-1]
MobiClip_Code_02090014:
    orr r6, r6, r6, lsl #8
MobiClip_Code_02090018:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0209001C:
    str r6, [fp], #0x100
MobiClip_Code_02090020:
    ldrb r6, [fp, #-1]
MobiClip_Code_02090024:
    orr r6, r6, r6, lsl #8
MobiClip_Code_02090028:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0209002C:
    str r6, [fp], #0x100
MobiClip_Code_02090030:
    ldrb r6, [fp, #-1]
MobiClip_Code_02090034:
    orr r6, r6, r6, lsl #8
MobiClip_Code_02090038:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0209003C:
    str r6, [fp], #0x100
MobiClip_Code_02090040:
    ldrb r6, [fp, #-1]
MobiClip_Code_02090044:
    orr r6, r6, r6, lsl #8
MobiClip_Code_02090048:
    orr r6, r6, r6, lsl #16
MobiClip_Code_0209004C:
    str r6, [fp], #0x100
MobiClip_Code_02090050:
    sub fp, fp, #0x400
MobiClip_Code_02090054:
    mov pc, lr
MobiClip_Code_02090058:
    push {sl, lr}
MobiClip_Code_0209005C:
    bl MobiClip_Code_0208E93C
MobiClip_Code_02090060:
    push {r0, r1, r2, r3}
MobiClip_Code_02090064:
    ldr r0, [fp, #-0x100]
MobiClip_Code_02090068:
    add lr, fp, #0x300
MobiClip_Code_0209006C:
    ldrb r4, [lr, #-1]
MobiClip_Code_02090070:
    lsr sl, r0, #0x18
MobiClip_Code_02090074:
    add r5, r4, sl
MobiClip_Code_02090078:
    add r5, r5, #1
MobiClip_Code_0209007C:
    asr r5, r5, #1
MobiClip_Code_02090080:
    add r5, r5, r6, lsl #1
MobiClip_Code_02090084:
    sub r6, r5, r4
MobiClip_Code_02090088:
    lsl r4, r4, #2
MobiClip_Code_0209008C:
    sub sp, sp, #0x20
MobiClip_Code_02090090:
    mov lr, sp
MobiClip_Code_02090094:
    mov r2, #0xff
MobiClip_Code_02090098:
    add r4, r4, r6
MobiClip_Code_0209009C:
    and r7, r2, r0
MobiClip_Code_020900A0:
    sub r8, r4, r7, lsl #2
MobiClip_Code_020900A4:
    lsl r7, r7, #4
MobiClip_Code_020900A8:
    add r4, r4, r6
MobiClip_Code_020900AC:
    and sb, r2, r0, lsr #8
MobiClip_Code_020900B0:
    sub ip, r4, sb, lsl #2
MobiClip_Code_020900B4:
    lsl sb, sb, #4
MobiClip_Code_020900B8:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020900BC:
    add r4, r4, r6
MobiClip_Code_020900C0:
    and r7, r2, r0, lsr #16
MobiClip_Code_020900C4:
    sub r8, r4, r7, lsl #2
MobiClip_Code_020900C8:
    lsl r7, r7, #4
MobiClip_Code_020900CC:
    add r4, r4, r6
MobiClip_Code_020900D0:
    and sb, r2, r0, lsr #24
MobiClip_Code_020900D4:
    sub ip, r4, sb, lsl #2
MobiClip_Code_020900D8:
    lsl sb, sb, #4
MobiClip_Code_020900DC:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020900E0:
    sub sb, r5, sl
MobiClip_Code_020900E4:
    lsl sl, sl, #2
MobiClip_Code_020900E8:
    mov lr, #4
MobiClip_Code_020900EC:
    add sl, sl, sb
MobiClip_Code_020900F0:
    ldrb r8, [fp, #-1]
MobiClip_Code_020900F4:
    sub r7, sl, r8, lsl #2
MobiClip_Code_020900F8:
    lsl r8, r8, #4
MobiClip_Code_020900FC:
    ldm sp, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_02090100:
    add r0, r0, r1
MobiClip_Code_02090104:
    add r2, r2, r3
MobiClip_Code_02090108:
    add r4, r4, r5
MobiClip_Code_0209010C:
    add r6, r6, ip
MobiClip_Code_02090110:
    str r0, [sp]
MobiClip_Code_02090114:
    str r2, [sp, #8]
MobiClip_Code_02090118:
    str r4, [sp, #0x10]
MobiClip_Code_0209011C:
    str r6, [sp, #0x18]
MobiClip_Code_02090120:
    add r8, r8, r7
MobiClip_Code_02090124:
    add r5, r0, r8
MobiClip_Code_02090128:
    add r5, r5, #0x10
MobiClip_Code_0209012C:
    asr r5, r5, #5
MobiClip_Code_02090130:
    add r8, r8, r7
MobiClip_Code_02090134:
    add ip, r2, r8
MobiClip_Code_02090138:
    add ip, ip, #0x10
MobiClip_Code_0209013C:
    asr ip, ip, #5
MobiClip_Code_02090140:
    orr r5, r5, ip, lsl #8
MobiClip_Code_02090144:
    add r8, r8, r7
MobiClip_Code_02090148:
    add ip, r4, r8
MobiClip_Code_0209014C:
    add ip, ip, #0x10
MobiClip_Code_02090150:
    asr ip, ip, #5
MobiClip_Code_02090154:
    orr r5, r5, ip, lsl #16
MobiClip_Code_02090158:
    add r8, r8, r7
MobiClip_Code_0209015C:
    add ip, r6, r8
MobiClip_Code_02090160:
    add ip, ip, #0x10
MobiClip_Code_02090164:
    asr ip, ip, #5
MobiClip_Code_02090168:
    orr r5, r5, ip, lsl #24
MobiClip_Code_0209016C:
    str r5, [fp], #0x100
MobiClip_Code_02090170:
    subs lr, lr, #1
MobiClip_Code_02090174:
    bne MobiClip_Code_020900EC
MobiClip_Code_02090178:
    add sp, sp, #0x20
MobiClip_Code_0209017C:
    sub fp, fp, #0x400
MobiClip_Code_02090180:
    pop {r0, r1, r2, r3, sl, pc}
MobiClip_Code_02090184:
    mov r6, #0
MobiClip_Code_02090188:
    ldr r4, [fp, #-0x100]
MobiClip_Code_0209018C:
    add r6, r6, r4, lsr #24
MobiClip_Code_02090190:
    lsl r4, r4, #8
MobiClip_Code_02090194:
    add r6, r6, r4, lsr #24
MobiClip_Code_02090198:
    lsl r4, r4, #8
MobiClip_Code_0209019C:
    add r6, r6, r4, lsr #24
MobiClip_Code_020901A0:
    lsl r4, r4, #8
MobiClip_Code_020901A4:
    add r6, r6, r4, lsr #24
MobiClip_Code_020901A8:
    sub fp, fp, #1
MobiClip_Code_020901AC:
    ldrb r4, [fp], #0x100
MobiClip_Code_020901B0:
    add r6, r6, r4
MobiClip_Code_020901B4:
    ldrb r4, [fp], #0x100
MobiClip_Code_020901B8:
    add r6, r6, r4
MobiClip_Code_020901BC:
    ldrb r4, [fp], #0x100
MobiClip_Code_020901C0:
    add r6, r6, r4
MobiClip_Code_020901C4:
    ldrb r4, [fp], #1
MobiClip_Code_020901C8:
    add r6, r6, r4
MobiClip_Code_020901CC:
    add r6, r6, #4
MobiClip_Code_020901D0:
    asr r6, r6, #3
MobiClip_Code_020901D4:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020901D8:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020901DC:
    str r6, [fp], #-0x100
MobiClip_Code_020901E0:
    str r6, [fp], #-0x100
MobiClip_Code_020901E4:
    str r6, [fp], #-0x100
MobiClip_Code_020901E8:
    str r6, [fp]
MobiClip_Code_020901EC:
    mov pc, lr
MobiClip_Code_020901F0:
    mov r6, #0
MobiClip_Code_020901F4:
    sub fp, fp, #1
MobiClip_Code_020901F8:
    ldrb r4, [fp], #0x100
MobiClip_Code_020901FC:
    add r6, r6, r4
MobiClip_Code_02090200:
    ldrb r4, [fp], #0x100
MobiClip_Code_02090204:
    add r6, r6, r4
MobiClip_Code_02090208:
    ldrb r4, [fp], #0x100
MobiClip_Code_0209020C:
    add r6, r6, r4
MobiClip_Code_02090210:
    ldrb r4, [fp], #1
MobiClip_Code_02090214:
    add r6, r6, r4
MobiClip_Code_02090218:
    add r6, r6, #2
MobiClip_Code_0209021C:
    asr r6, r6, #2
MobiClip_Code_02090220:
    orr r6, r6, r6, lsl #8
MobiClip_Code_02090224:
    orr r6, r6, r6, lsl #16
MobiClip_Code_02090228:
    str r6, [fp], #-0x100
MobiClip_Code_0209022C:
    str r6, [fp], #-0x100
MobiClip_Code_02090230:
    str r6, [fp], #-0x100
MobiClip_Code_02090234:
    str r6, [fp]
MobiClip_Code_02090238:
    mov pc, lr
MobiClip_Code_0209023C:
    mov r6, #0
MobiClip_Code_02090240:
    ldr r4, [fp, #-0x100]
MobiClip_Code_02090244:
    add r6, r6, r4, lsr #24
MobiClip_Code_02090248:
    lsl r4, r4, #8
MobiClip_Code_0209024C:
    add r6, r6, r4, lsr #24
MobiClip_Code_02090250:
    lsl r4, r4, #8
MobiClip_Code_02090254:
    add r6, r6, r4, lsr #24
MobiClip_Code_02090258:
    lsl r4, r4, #8
MobiClip_Code_0209025C:
    add r6, r6, r4, lsr #24
MobiClip_Code_02090260:
    add r6, r6, #2
MobiClip_Code_02090264:
    asr r6, r6, #2
MobiClip_Code_02090268:
    orr r6, r6, r6, lsl #8
MobiClip_Code_0209026C:
    orr r6, r6, r6, lsl #16
MobiClip_Code_02090270:
    str r6, [fp], #0x100
MobiClip_Code_02090274:
    str r6, [fp], #0x100
MobiClip_Code_02090278:
    str r6, [fp], #0x100
MobiClip_Code_0209027C:
    str r6, [fp], #0x100
MobiClip_Code_02090280:
    sub fp, fp, #0x400
MobiClip_Code_02090284:
    mov pc, lr
MobiClip_Code_02090288:
    mov r6, #0x80
MobiClip_Code_0209028C:
    orr r6, r6, r6, lsl #8
MobiClip_Code_02090290:
    orr r6, r6, r6, lsl #16
MobiClip_Code_02090294:
    str r6, [fp], #0x100
MobiClip_Code_02090298:
    str r6, [fp], #0x100
MobiClip_Code_0209029C:
    str r6, [fp], #0x100
MobiClip_Code_020902A0:
    str r6, [fp], #0x100
MobiClip_Code_020902A4:
    sub fp, fp, #0x400
MobiClip_Code_020902A8:
    mov pc, lr
    /* control metadata 0x020902ac..0x020902bc */
    .global gMobiClip_intra4_neighbor_dispatch
    .type gMobiClip_intra4_neighbor_dispatch, %object
gMobiClip_intra4_neighbor_dispatch:
    /* intra4_neighbor */
    .global gMobiClip_intra4_neighbor
gMobiClip_intra4_neighbor:
    .word MobiClip_Code_02090288 - .
    .word MobiClip_Code_0209023C - . + 0x4
    .word MobiClip_Code_020901F0 - . + 0x8
    .word MobiClip_Code_02090184 - . + 0xc
    .size gMobiClip_intra4_neighbor_dispatch, . - gMobiClip_intra4_neighbor_dispatch
MobiClip_Code_020902BC:
    sub r5, pc, #0x18
MobiClip_Code_020902C0:
    mov r8, #0
MobiClip_Code_020902C4:
    sub r6, fp, sl
MobiClip_Code_020902C8:
    lsls r7, r6, #0x18
MobiClip_Code_020902CC:
    addne r8, r8, #8
MobiClip_Code_020902D0:
    cmp r6, #0x100
MobiClip_Code_020902D4:
    addge r8, r8, #4
MobiClip_Code_020902D8:
    ldr r6, [r5, r8]
MobiClip_Code_020902DC:
    add pc, r5, r6
MobiClip_Code_020902E0:
    ldrb r5, [fp, #-1]
MobiClip_Code_020902E4:
    ldrb r6, [fp, #0xff]
MobiClip_Code_020902E8:
    add r4, r5, r6
MobiClip_Code_020902EC:
    add r4, r4, #1
MobiClip_Code_020902F0:
    asr r4, r4, #1
MobiClip_Code_020902F4:
    ldrb r7, [fp, #0x1ff]!
MobiClip_Code_020902F8:
    add r5, r5, r6, lsl #1
MobiClip_Code_020902FC:
    add r5, r5, r7
MobiClip_Code_02090300:
    add r5, r5, #2
MobiClip_Code_02090304:
    asr r5, r5, #2
MobiClip_Code_02090308:
    orr r4, r4, r5, lsl #8
MobiClip_Code_0209030C:
    add r5, r6, r7
MobiClip_Code_02090310:
    add r5, r5, #1
MobiClip_Code_02090314:
    asr r5, r5, #1
MobiClip_Code_02090318:
    orr r4, r4, r5, lsl #16
MobiClip_Code_0209031C:
    ldrb r8, [fp, #0x100]!
MobiClip_Code_02090320:
    add r6, r6, r7, lsl #1
MobiClip_Code_02090324:
    add r6, r6, r8
MobiClip_Code_02090328:
    add r6, r6, #2
MobiClip_Code_0209032C:
    asr r6, r6, #2
MobiClip_Code_02090330:
    orr r4, r4, r6, lsl #24
MobiClip_Code_02090334:
    orr r5, r5, r6, lsl #8
MobiClip_Code_02090338:
    add r6, r7, r8
MobiClip_Code_0209033C:
    add r6, r6, #1
MobiClip_Code_02090340:
    asr r6, r6, #1
MobiClip_Code_02090344:
    orr r5, r5, r6, lsl #16
MobiClip_Code_02090348:
    add r7, r7, r8, lsl #1
MobiClip_Code_0209034C:
    add r7, r7, r8
MobiClip_Code_02090350:
    add r7, r7, #2
MobiClip_Code_02090354:
    asr r7, r7, #2
MobiClip_Code_02090358:
    orr r5, r5, r7, lsl #24
MobiClip_Code_0209035C:
    orr r6, r6, r7, lsl #8
MobiClip_Code_02090360:
    orr r8, r8, r8, lsl #8
MobiClip_Code_02090364:
    orr r6, r6, r8, lsl #16
MobiClip_Code_02090368:
    orr r8, r8, r8, lsl #16
MobiClip_Code_0209036C:
    str r8, [fp, #1]!
MobiClip_Code_02090370:
    str r6, [fp, #-0x100]!
MobiClip_Code_02090374:
    str r5, [fp, #-0x100]!
MobiClip_Code_02090378:
    str r4, [fp, #-0x100]!
MobiClip_Code_0209037C:
    mov pc, lr
MobiClip_Code_02090380:
    push {ip, lr}
MobiClip_Code_02090384:
    ldrb r8, [fp, #-0x101]
MobiClip_Code_02090388:
    ldrb r7, [fp, #-1]
MobiClip_Code_0209038C:
    ldr sb, [fp, #-0x100]
MobiClip_Code_02090390:
    add ip, r8, r7
MobiClip_Code_02090394:
    add ip, ip, #1
MobiClip_Code_02090398:
    asr lr, ip, #1
MobiClip_Code_0209039C:
    and ip, sb, #0xff
MobiClip_Code_020903A0:
    lsl r5, sb, #0x10
MobiClip_Code_020903A4:
    lsr r5, r5, #0x18
MobiClip_Code_020903A8:
    add r6, r8, ip, lsl #1
MobiClip_Code_020903AC:
    add r4, r7, r8, lsl #1
MobiClip_Code_020903B0:
    add r4, r4, ip
MobiClip_Code_020903B4:
    add ip, ip, r5, lsl #1
MobiClip_Code_020903B8:
    lsl sb, sb, #8
MobiClip_Code_020903BC:
    add sb, ip, sb, lsr #24
MobiClip_Code_020903C0:
    add r4, r4, #2
MobiClip_Code_020903C4:
    add r6, r6, r5
MobiClip_Code_020903C8:
    add r6, r6, #2
MobiClip_Code_020903CC:
    asr r4, r4, #2
MobiClip_Code_020903D0:
    orr ip, lr, r4, lsl #8
MobiClip_Code_020903D4:
    asr r6, r6, #2
MobiClip_Code_020903D8:
    add sb, sb, #2
MobiClip_Code_020903DC:
    asr sb, sb, #2
MobiClip_Code_020903E0:
    orr ip, ip, r6, lsl #16
MobiClip_Code_020903E4:
    orr sb, ip, sb, lsl #24
MobiClip_Code_020903E8:
    str sb, [fp]
MobiClip_Code_020903EC:
    ldrb sb, [fp, #0xff]
MobiClip_Code_020903F0:
    add r8, r8, r7, lsl #1
MobiClip_Code_020903F4:
    add r8, r8, sb
MobiClip_Code_020903F8:
    add ip, r7, sb
MobiClip_Code_020903FC:
    add ip, ip, #1
MobiClip_Code_02090400:
    add r8, r8, #2
MobiClip_Code_02090404:
    asr r8, r8, #2
MobiClip_Code_02090408:
    asr ip, ip, #1
MobiClip_Code_0209040C:
    orr r5, ip, r8, lsl #8
MobiClip_Code_02090410:
    orr lr, r5, lr, lsl #16
MobiClip_Code_02090414:
    orr lr, lr, r4, lsl #24
MobiClip_Code_02090418:
    str lr, [fp, #0x100]!
MobiClip_Code_0209041C:
    ldrb lr, [fp, #0xff]
MobiClip_Code_02090420:
    add r7, r7, sb, lsl #1
MobiClip_Code_02090424:
    add r7, r7, lr
MobiClip_Code_02090428:
    add r4, sb, lr
MobiClip_Code_0209042C:
    add r4, r4, #1
MobiClip_Code_02090430:
    add r7, r7, #2
MobiClip_Code_02090434:
    asr r7, r7, #2
MobiClip_Code_02090438:
    asr r4, r4, #1
MobiClip_Code_0209043C:
    orr r5, r4, r7, lsl #8
MobiClip_Code_02090440:
    orr ip, r5, ip, lsl #16
MobiClip_Code_02090444:
    orr r8, ip, r8, lsl #24
MobiClip_Code_02090448:
    str r8, [fp, #0x100]!
MobiClip_Code_0209044C:
    ldrb r8, [fp, #0xff]
MobiClip_Code_02090450:
    add sb, sb, lr, lsl #1
MobiClip_Code_02090454:
    add ip, lr, r8
MobiClip_Code_02090458:
    add r8, sb, r8
MobiClip_Code_0209045C:
    add r8, r8, #2
MobiClip_Code_02090460:
    add ip, ip, #1
MobiClip_Code_02090464:
    asr ip, ip, #1
MobiClip_Code_02090468:
    asr r8, r8, #2
MobiClip_Code_0209046C:
    orr r8, ip, r8, lsl #8
MobiClip_Code_02090470:
    orr r8, r8, r4, lsl #16
MobiClip_Code_02090474:
    orr r7, r8, r7, lsl #24
MobiClip_Code_02090478:
    str r7, [fp, #0x100]
MobiClip_Code_0209047C:
    sub fp, fp, #0x200
MobiClip_Code_02090480:
    pop {ip, pc}
MobiClip_Code_02090484:
    push {r1, r2, r3, ip, lr}
MobiClip_Code_02090488:
    ldr lr, [fp, #-0x100]
MobiClip_Code_0209048C:
    ldrb r3, [fp, #-0x101]
MobiClip_Code_02090490:
    and r1, lr, #0xff
MobiClip_Code_02090494:
    lsr r7, lr, #0x18
MobiClip_Code_02090498:
    add r2, r3, r1
MobiClip_Code_0209049C:
    add r2, r2, #1
MobiClip_Code_020904A0:
    asr r4, r2, #1
MobiClip_Code_020904A4:
    lsl r2, lr, #0x10
MobiClip_Code_020904A8:
    lsr r2, r2, #0x18
MobiClip_Code_020904AC:
    add ip, r1, r2
MobiClip_Code_020904B0:
    add ip, ip, #1
MobiClip_Code_020904B4:
    asr r5, ip, #1
MobiClip_Code_020904B8:
    lsl ip, lr, #8
MobiClip_Code_020904BC:
    lsr ip, ip, #0x18
MobiClip_Code_020904C0:
    add r6, r2, ip
MobiClip_Code_020904C4:
    add r6, r6, #1
MobiClip_Code_020904C8:
    add lr, ip, r7
MobiClip_Code_020904CC:
    add lr, lr, #1
MobiClip_Code_020904D0:
    asr r6, r6, #1
MobiClip_Code_020904D4:
    orr r8, r4, r5, lsl #8
MobiClip_Code_020904D8:
    orr r8, r8, r6, lsl #16
MobiClip_Code_020904DC:
    asr lr, lr, #1
MobiClip_Code_020904E0:
    orr lr, r8, lr, lsl #24
MobiClip_Code_020904E4:
    str lr, [fp]
MobiClip_Code_020904E8:
    ldrb lr, [fp, #-1]
MobiClip_Code_020904EC:
    add sb, r3, r1, lsl #1
MobiClip_Code_020904F0:
    add sb, sb, r2
MobiClip_Code_020904F4:
    add r8, lr, r3, lsl #1
MobiClip_Code_020904F8:
    add r8, r8, r1
MobiClip_Code_020904FC:
    add r1, r1, r2, lsl #1
MobiClip_Code_02090500:
    add r2, r2, ip, lsl #1
MobiClip_Code_02090504:
    add r1, r1, ip
MobiClip_Code_02090508:
    add r8, r8, #2
MobiClip_Code_0209050C:
    add sb, sb, #2
MobiClip_Code_02090510:
    asr sb, sb, #2
MobiClip_Code_02090514:
    asr r8, r8, #2
MobiClip_Code_02090518:
    add r1, r1, #2
MobiClip_Code_0209051C:
    add r2, r2, r7
MobiClip_Code_02090520:
    add r2, r2, #2
MobiClip_Code_02090524:
    asr r1, r1, #2
MobiClip_Code_02090528:
    orr ip, r8, sb, lsl #8
MobiClip_Code_0209052C:
    orr ip, ip, r1, lsl #16
MobiClip_Code_02090530:
    asr r2, r2, #2
MobiClip_Code_02090534:
    orr r2, ip, r2, lsl #24
MobiClip_Code_02090538:
    str r2, [fp, #0x100]!
MobiClip_Code_0209053C:
    ldrb r2, [fp, #-1]
MobiClip_Code_02090540:
    add r3, r3, lr, lsl #1
MobiClip_Code_02090544:
    add r3, r3, r2
MobiClip_Code_02090548:
    add r3, r3, #2
MobiClip_Code_0209054C:
    asr r3, r3, #2
MobiClip_Code_02090550:
    orr r3, r3, r4, lsl #8
MobiClip_Code_02090554:
    orr r3, r3, r5, lsl #16
MobiClip_Code_02090558:
    orr r3, r3, r6, lsl #24
MobiClip_Code_0209055C:
    str r3, [fp, #0x100]!
MobiClip_Code_02090560:
    ldrb r3, [fp, #-1]
MobiClip_Code_02090564:
    add r2, lr, r2, lsl #1
MobiClip_Code_02090568:
    add r2, r2, r3
MobiClip_Code_0209056C:
    add r2, r2, #2
MobiClip_Code_02090570:
    asr r2, r2, #2
MobiClip_Code_02090574:
    orr r2, r2, r8, lsl #8
MobiClip_Code_02090578:
    orr r2, r2, sb, lsl #16
MobiClip_Code_0209057C:
    orr r1, r2, r1, lsl #24
MobiClip_Code_02090580:
    str r1, [fp, #0x100]
MobiClip_Code_02090584:
    sub fp, fp, #0x200
MobiClip_Code_02090588:
    pop {r1, r2, r3, ip, pc}
MobiClip_Code_0209058C:
    push {ip, lr}
MobiClip_Code_02090590:
    ldr r7, [fp, #-0x100]
MobiClip_Code_02090594:
    ldrb ip, [fp, #-0x101]
MobiClip_Code_02090598:
    and lr, r7, #0xff
MobiClip_Code_0209059C:
    ldrb sb, [fp, #-1]
MobiClip_Code_020905A0:
    lsl r4, r7, #0x10
MobiClip_Code_020905A4:
    lsr r4, r4, #0x18
MobiClip_Code_020905A8:
    add r5, ip, lr, lsl #1
MobiClip_Code_020905AC:
    add r8, sb, ip, lsl #1
MobiClip_Code_020905B0:
    add r8, r8, lr
MobiClip_Code_020905B4:
    lsl r6, r7, #8
MobiClip_Code_020905B8:
    lsr r6, r6, #0x18
MobiClip_Code_020905BC:
    add lr, lr, r4, lsl #1
MobiClip_Code_020905C0:
    add r5, r5, r4
MobiClip_Code_020905C4:
    add r4, r4, r6, lsl #1
MobiClip_Code_020905C8:
    add r7, r4, r7, lsr #24
MobiClip_Code_020905CC:
    add r5, r5, #2
MobiClip_Code_020905D0:
    add lr, lr, r6
MobiClip_Code_020905D4:
    add r8, r8, #2
MobiClip_Code_020905D8:
    asr r8, r8, #2
MobiClip_Code_020905DC:
    add lr, lr, #2
MobiClip_Code_020905E0:
    asr r5, r5, #2
MobiClip_Code_020905E4:
    orr r4, r8, r5, lsl #8
MobiClip_Code_020905E8:
    asr lr, lr, #2
MobiClip_Code_020905EC:
    add r7, r7, #2
MobiClip_Code_020905F0:
    asr r7, r7, #2
MobiClip_Code_020905F4:
    orr r4, r4, lr, lsl #16
MobiClip_Code_020905F8:
    orr r7, r4, r7, lsl #24
MobiClip_Code_020905FC:
    str r7, [fp]
MobiClip_Code_02090600:
    ldrb r7, [fp, #0xff]
MobiClip_Code_02090604:
    add r4, r7, sb, lsl #1
MobiClip_Code_02090608:
    add ip, r4, ip
MobiClip_Code_0209060C:
    add ip, ip, #2
MobiClip_Code_02090610:
    asr ip, ip, #2
MobiClip_Code_02090614:
    orr r4, ip, r8, lsl #8
MobiClip_Code_02090618:
    orr r4, r4, r5, lsl #16
MobiClip_Code_0209061C:
    orr lr, r4, lr, lsl #24
MobiClip_Code_02090620:
    str lr, [fp, #0x100]!
MobiClip_Code_02090624:
    ldrb lr, [fp, #0xff]
MobiClip_Code_02090628:
    add r4, lr, r7, lsl #1
MobiClip_Code_0209062C:
    add sb, r4, sb
MobiClip_Code_02090630:
    add sb, sb, #2
MobiClip_Code_02090634:
    asr sb, sb, #2
MobiClip_Code_02090638:
    orr r4, sb, ip, lsl #8
MobiClip_Code_0209063C:
    orr r4, r4, r8, lsl #16
MobiClip_Code_02090640:
    orr r4, r4, r5, lsl #24
MobiClip_Code_02090644:
    str r4, [fp, #0x100]!
MobiClip_Code_02090648:
    ldrb r4, [fp, #0xff]
MobiClip_Code_0209064C:
    add lr, r4, lr, lsl #1
MobiClip_Code_02090650:
    add r7, lr, r7
MobiClip_Code_02090654:
    add r7, r7, #2
MobiClip_Code_02090658:
    asr r7, r7, #2
MobiClip_Code_0209065C:
    orr r7, r7, sb, lsl #8
MobiClip_Code_02090660:
    orr r7, r7, ip, lsl #16
MobiClip_Code_02090664:
    orr r7, r7, r8, lsl #24
MobiClip_Code_02090668:
    str r7, [fp, #0x100]
MobiClip_Code_0209066C:
    sub fp, fp, #0x200
MobiClip_Code_02090670:
    pop {ip, pc}
MobiClip_Code_02090674:
    push {r2, r3, sl, lr}
MobiClip_Code_02090678:
    ldr sb, [fp, #-0x100]
MobiClip_Code_0209067C:
    sub r2, fp, #0x100
MobiClip_Code_02090680:
    lsl r3, sb, #0x10
MobiClip_Code_02090684:
    lsr r6, r3, #0x18
MobiClip_Code_02090688:
    and r7, sb, #0xff
MobiClip_Code_0209068C:
    add r3, r7, r6
MobiClip_Code_02090690:
    add r3, r3, #1
MobiClip_Code_02090694:
    asr r8, r3, #1
MobiClip_Code_02090698:
    lsl r3, sb, #8
MobiClip_Code_0209069C:
    lsr ip, r3, #0x18
MobiClip_Code_020906A0:
    add r3, r6, ip
MobiClip_Code_020906A4:
    lsr sb, sb, #0x18
MobiClip_Code_020906A8:
    add r3, r3, #1
MobiClip_Code_020906AC:
    asr lr, r3, #1
MobiClip_Code_020906B0:
    add r3, ip, sb
MobiClip_Code_020906B4:
    add r3, r3, #1
MobiClip_Code_020906B8:
    asr r4, r3, #1
MobiClip_Code_020906BC:
    ldr r3, [r2, #4]
MobiClip_Code_020906C0:
    add r7, r7, r6, lsl #1
MobiClip_Code_020906C4:
    and r2, r3, #0xff
MobiClip_Code_020906C8:
    add r5, sb, r2
MobiClip_Code_020906CC:
    add r6, r6, ip, lsl #1
MobiClip_Code_020906D0:
    add r7, r7, ip
MobiClip_Code_020906D4:
    orr r8, r8, lr, lsl #8
MobiClip_Code_020906D8:
    add r5, r5, #1
MobiClip_Code_020906DC:
    asr r5, r5, #1
MobiClip_Code_020906E0:
    orr r8, r8, r4, lsl #16
MobiClip_Code_020906E4:
    orr r8, r8, r5, lsl #24
MobiClip_Code_020906E8:
    add ip, ip, sb, lsl #1
MobiClip_Code_020906EC:
    str r8, [fp]
MobiClip_Code_020906F0:
    add r7, r7, #2
MobiClip_Code_020906F4:
    asr r8, r7, #2
MobiClip_Code_020906F8:
    add ip, ip, r2
MobiClip_Code_020906FC:
    add ip, ip, #2
MobiClip_Code_02090700:
    add r6, r6, sb
MobiClip_Code_02090704:
    asr r7, ip, #2
MobiClip_Code_02090708:
    lsl ip, r3, #0x10
MobiClip_Code_0209070C:
    lsr ip, ip, #0x18
MobiClip_Code_02090710:
    add r6, r6, #2
MobiClip_Code_02090714:
    add sb, sb, r2, lsl #1
MobiClip_Code_02090718:
    add sb, sb, ip
MobiClip_Code_0209071C:
    asr r6, r6, #2
MobiClip_Code_02090720:
    orr r8, r8, r6, lsl #8
MobiClip_Code_02090724:
    add sb, sb, #2
MobiClip_Code_02090728:
    asr sb, sb, #2
MobiClip_Code_0209072C:
    orr r8, r8, r7, lsl #16
MobiClip_Code_02090730:
    orr r8, r8, sb, lsl #24
MobiClip_Code_02090734:
    str r8, [fp, #0x100]!
MobiClip_Code_02090738:
    add r8, r2, ip
MobiClip_Code_0209073C:
    add r2, r2, ip, lsl #1
MobiClip_Code_02090740:
    lsl r3, r3, #8
MobiClip_Code_02090744:
    add r2, r2, r3, lsr #24
MobiClip_Code_02090748:
    add r8, r8, #1
MobiClip_Code_0209074C:
    orr lr, lr, r4, lsl #8
MobiClip_Code_02090750:
    orr lr, lr, r5, lsl #16
MobiClip_Code_02090754:
    asr r8, r8, #1
MobiClip_Code_02090758:
    add r2, r2, #2
MobiClip_Code_0209075C:
    orr r3, r6, r7, lsl #8
MobiClip_Code_02090760:
    orr sb, r3, sb, lsl #16
MobiClip_Code_02090764:
    asr r2, r2, #2
MobiClip_Code_02090768:
    orr lr, lr, r8, lsl #24
MobiClip_Code_0209076C:
    str lr, [fp, #0x100]!
MobiClip_Code_02090770:
    orr sb, sb, r2, lsl #24
MobiClip_Code_02090774:
    str sb, [fp, #0x100]
MobiClip_Code_02090778:
    sub fp, fp, #0x200
MobiClip_Code_0209077C:
    pop {r2, r3, sl, pc}
MobiClip_Code_02090780:
    lsls r3, r3, #8
MobiClip_Code_02090784:
    bhs MobiClip_Code_020907D4
MobiClip_Code_02090788:
    subs r2, r2, #8
MobiClip_Code_0209078C:
    bllt MobiClip_Code_0208E928
MobiClip_Code_02090790:
    lsr r4, r3, #0x14
MobiClip_Code_02090794:
    add r4, fp, r4, lsl #1
MobiClip_Code_02090798:
    ldrh r4, [r4]
MobiClip_Code_0209079C:
    add r7, fp, #0x2000
MobiClip_Code_020907A0:
    ldrb r7, [r7, r4, lsr #9]
MobiClip_Code_020907A4:
    and r5, r4, #0xf
MobiClip_Code_020907A8:
    lsr r4, r4, #4
MobiClip_Code_020907AC:
    and r6, r4, #0x1f
MobiClip_Code_020907B0:
    add r6, r6, r7
MobiClip_Code_020907B4:
    lsr r4, r4, #5
MobiClip_Code_020907B8:
    lsls r3, r3, r5
MobiClip_Code_020907BC:
    rsbhs r6, r6, #0
MobiClip_Code_020907C0:
    subs r2, r2, r5
MobiClip_Code_020907C4:
    bllt MobiClip_Code_0208E928
MobiClip_Code_020907C8:
    and r5, r4, #0x3f
MobiClip_Code_020907CC:
    lsr r4, r4, #6
MobiClip_Code_020907D0:
    b MobiClip_Code_020908A8
MobiClip_Code_020907D4:
    adds r3, r3, r3
MobiClip_Code_020907D8:
    bhs MobiClip_Code_0209082C
MobiClip_Code_020907DC:
    subs r2, r2, #9
MobiClip_Code_020907E0:
    bllt MobiClip_Code_0208E928
MobiClip_Code_020907E4:
    lsr r4, r3, #0x14
MobiClip_Code_020907E8:
    add r4, fp, r4, lsl #1
MobiClip_Code_020907EC:
    ldrh r4, [r4]
MobiClip_Code_020907F0:
    and r5, r4, #0xf
MobiClip_Code_020907F4:
    lsr r4, r4, #4
MobiClip_Code_020907F8:
    and r6, r4, #0x1f
MobiClip_Code_020907FC:
    lsr r4, r4, #5
MobiClip_Code_02090800:
    and r8, r4, #0x3f
MobiClip_Code_02090804:
    lsr r4, r4, #6
MobiClip_Code_02090808:
    add r7, fp, #0x2080
MobiClip_Code_0209080C:
    add r7, r7, r6
MobiClip_Code_02090810:
    ldrb r7, [r7, r4, lsl #6]
MobiClip_Code_02090814:
    lsls r3, r3, r5
MobiClip_Code_02090818:
    rsbhs r6, r6, #0
MobiClip_Code_0209081C:
    subs r2, r2, r5
MobiClip_Code_02090820:
    bllt MobiClip_Code_0208E928
MobiClip_Code_02090824:
    add r5, r8, r7
MobiClip_Code_02090828:
    b MobiClip_Code_020908A8
MobiClip_Code_0209082C:
    subs r2, r2, #9
MobiClip_Code_02090830:
    bllt MobiClip_Code_0208E928
MobiClip_Code_02090834:
    lsr r4, r3, #0x1f
MobiClip_Code_02090838:
    lsl r3, r3, #1
MobiClip_Code_0209083C:
    lsr r5, r3, #0x1a
MobiClip_Code_02090840:
    lsl r3, r3, #6
MobiClip_Code_02090844:
    subs r2, r2, #7
MobiClip_Code_02090848:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0209084C:
    asr r6, r3, #0x14
MobiClip_Code_02090850:
    lsl r3, r3, #0xc
MobiClip_Code_02090854:
    subs r2, r2, #0xc
MobiClip_Code_02090858:
    bllt MobiClip_Code_0208E928
MobiClip_Code_0209085C:
    b MobiClip_Code_020908A8
MobiClip_Code_02090860:
    str lr, [sp, #-4]!
MobiClip_Code_02090864:
    ldr fp, [r0, #0x3b8]
MobiClip_Code_02090868:
    lsr r4, r3, #0x19
MobiClip_Code_0209086C:
    cmp r4, #3
MobiClip_Code_02090870:
    beq MobiClip_Code_02090780
MobiClip_Code_02090874:
    lsr r4, r3, #0x14
MobiClip_Code_02090878:
    add r4, fp, r4, lsl #1
MobiClip_Code_0209087C:
    ldrh r4, [r4]
MobiClip_Code_02090880:
    and r5, r4, #0xf
MobiClip_Code_02090884:
    lsr r4, r4, #4
MobiClip_Code_02090888:
    and r6, r4, #0x1f
MobiClip_Code_0209088C:
    lsr r4, r4, #5
MobiClip_Code_02090890:
    lsls r3, r3, r5
MobiClip_Code_02090894:
    rsbhs r6, r6, #0
MobiClip_Code_02090898:
    subs r2, r2, r5
MobiClip_Code_0209089C:
    bllt MobiClip_Code_0208E928
MobiClip_Code_020908A0:
    and r5, r4, #0x3f
MobiClip_Code_020908A4:
    lsr r4, r4, #6
MobiClip_Code_020908A8:
    add ip, ip, r5, lsl #2
MobiClip_Code_020908AC:
    ldr r8, [ip], #4
MobiClip_Code_020908B0:
    and r5, r8, #0xff
MobiClip_Code_020908B4:
    lsr r7, r8, #8
MobiClip_Code_020908B8:
    smulbb r7, r6, r7
MobiClip_Code_020908BC:
    add r8, r0, #0x1b4
MobiClip_Code_020908C0:
    str r7, [r8, r5, lsl #2]
MobiClip_Code_020908C4:
    tst r4, #1
MobiClip_Code_020908C8:
    beq MobiClip_Code_02090868
MobiClip_Code_020908CC:
    pop {pc}
MobiClip_Code_020908D0:
    push {r0, r1, r2, r3}
MobiClip_Code_020908D4:
    add lr, r0, #0x1b4
MobiClip_Code_020908D8:
    add fp, lr, #0x100
MobiClip_Code_020908DC:
    ldm lr!, {r0, r1, r2, r3, r4, r5, r6, r7}
MobiClip_Code_020908E0:
    add r0, r0, #0x20
MobiClip_Code_020908E4:
    mov ip, #8
MobiClip_Code_020908E8:
    add r8, r0, r4
MobiClip_Code_020908EC:
    sub sb, r0, r4
MobiClip_Code_020908F0:
    add r0, r2, r6, asr #1
MobiClip_Code_020908F4:
    rsb r4, r6, r2, asr #1
MobiClip_Code_020908F8:
    add r2, sb, r4
MobiClip_Code_020908FC:
    sub r4, sb, r4
MobiClip_Code_02090900:
    sub r6, r8, r0
MobiClip_Code_02090904:
    add r0, r8, r0
MobiClip_Code_02090908:
    add r8, r1, r7
MobiClip_Code_0209090C:
    sub r8, r8, r3
MobiClip_Code_02090910:
    sub r8, r8, r3, asr #1
MobiClip_Code_02090914:
    sub sb, r7, r1
MobiClip_Code_02090918:
    add sb, sb, r5
MobiClip_Code_0209091C:
    add sb, sb, r5, asr #1
MobiClip_Code_02090920:
    add r7, r7, r7, asr #1
MobiClip_Code_02090924:
    sub r7, r5, r7
MobiClip_Code_02090928:
    sub r7, r7, r3
MobiClip_Code_0209092C:
    add r3, r3, r5
MobiClip_Code_02090930:
    add r3, r3, r1
MobiClip_Code_02090934:
    add r3, r3, r1, asr #1
MobiClip_Code_02090938:
    add r1, r7, r3, asr #2
MobiClip_Code_0209093C:
    sub r7, r3, r7, asr #2
MobiClip_Code_02090940:
    add r3, r8, sb, asr #2
MobiClip_Code_02090944:
    rsb r5, sb, r8, asr #2
MobiClip_Code_02090948:
    add r0, r0, r7
MobiClip_Code_0209094C:
    sub r7, r0, r7, lsl #1
MobiClip_Code_02090950:
    add r8, r2, r5
MobiClip_Code_02090954:
    sub sb, r2, r5
MobiClip_Code_02090958:
    add r2, r4, r3
MobiClip_Code_0209095C:
    sub r5, r4, r3
MobiClip_Code_02090960:
    add r3, r6, r1
MobiClip_Code_02090964:
    sub r4, r6, r1
MobiClip_Code_02090968:
    mov r1, r8
MobiClip_Code_0209096C:
    mov r6, sb
MobiClip_Code_02090970:
    str r7, [fp, #0xe0]
MobiClip_Code_02090974:
    str r6, [fp, #0xc0]
MobiClip_Code_02090978:
    str r5, [fp, #0xa0]
MobiClip_Code_0209097C:
    str r4, [fp, #0x80]
MobiClip_Code_02090980:
    str r3, [fp, #0x60]
MobiClip_Code_02090984:
    str r2, [fp, #0x40]
MobiClip_Code_02090988:
    str r1, [fp, #0x20]
MobiClip_Code_0209098C:
    str r0, [fp], #4
MobiClip_Code_02090990:
    subs ip, ip, #1
MobiClip_Code_02090994:
    ldmne lr!, {r0, r1, r2, r3, r4, r5, r6, r7}
MobiClip_Code_02090998:
    bne MobiClip_Code_020908E8
MobiClip_Code_0209099C:
    sub fp, fp, #0x20
MobiClip_Code_020909A0:
    ldr lr, [sp, #0x14]
MobiClip_Code_020909A4:
    mov ip, #8
MobiClip_Code_020909A8:
    ldr r8, [fp, #-0x270]
MobiClip_Code_020909AC:
    ldm fp!, {r0, r1, r2, r3, r4, r5, r6, r7}
MobiClip_Code_020909B0:
    add sb, r0, r4
MobiClip_Code_020909B4:
    sub sl, r0, r4
MobiClip_Code_020909B8:
    add r0, r2, r6, asr #1
MobiClip_Code_020909BC:
    rsb r4, r6, r2, asr #1
MobiClip_Code_020909C0:
    add r2, sl, r4
MobiClip_Code_020909C4:
    sub r4, sl, r4
MobiClip_Code_020909C8:
    sub r6, sb, r0
MobiClip_Code_020909CC:
    add r0, sb, r0
MobiClip_Code_020909D0:
    add sb, r1, r7
MobiClip_Code_020909D4:
    sub sb, sb, r3
MobiClip_Code_020909D8:
    sub sb, sb, r3, asr #1
MobiClip_Code_020909DC:
    sub sl, r7, r1
MobiClip_Code_020909E0:
    add sl, sl, r5
MobiClip_Code_020909E4:
    add sl, sl, r5, asr #1
MobiClip_Code_020909E8:
    add r7, r7, r7, asr #1
MobiClip_Code_020909EC:
    sub r7, r5, r7
MobiClip_Code_020909F0:
    sub r7, r7, r3
MobiClip_Code_020909F4:
    add r3, r3, r5
MobiClip_Code_020909F8:
    add r3, r3, r1
MobiClip_Code_020909FC:
    add r3, r3, r1, asr #1
MobiClip_Code_02090A00:
    add r1, r7, r3, asr #2
MobiClip_Code_02090A04:
    sub r7, r3, r7, asr #2
MobiClip_Code_02090A08:
    add r3, sb, sl, asr #2
MobiClip_Code_02090A0C:
    rsb r5, sl, sb, asr #2
MobiClip_Code_02090A10:
    add r0, r0, r7
MobiClip_Code_02090A14:
    sub r7, r0, r7, lsl #1
MobiClip_Code_02090A18:
    add sb, r2, r5
MobiClip_Code_02090A1C:
    sub sl, r2, r5
MobiClip_Code_02090A20:
    add r2, r4, r3
MobiClip_Code_02090A24:
    sub r5, r4, r3
MobiClip_Code_02090A28:
    add r3, r6, r1
MobiClip_Code_02090A2C:
    sub r4, r6, r1
MobiClip_Code_02090A30:
    mov r1, sb
MobiClip_Code_02090A34:
    mov r6, sl
MobiClip_Code_02090A38:
    ldrb sb, [lr]
MobiClip_Code_02090A3C:
    ldrb sl, [lr, #1]
MobiClip_Code_02090A40:
    add sb, sb, r0, asr #6
MobiClip_Code_02090A44:
    ldrb sb, [r8, sb]
MobiClip_Code_02090A48:
    ldrb r0, [lr, #2]
MobiClip_Code_02090A4C:
    add sl, sl, r1, asr #6
MobiClip_Code_02090A50:
    ldrb sl, [r8, sl]
MobiClip_Code_02090A54:
    strb sb, [lr]
MobiClip_Code_02090A58:
    ldrb r1, [lr, #3]
MobiClip_Code_02090A5C:
    add r0, r0, r2, asr #6
MobiClip_Code_02090A60:
    ldrb r0, [r8, r0]
MobiClip_Code_02090A64:
    strb sl, [lr, #1]
MobiClip_Code_02090A68:
    ldrb r2, [lr, #4]
MobiClip_Code_02090A6C:
    add r1, r1, r3, asr #6
MobiClip_Code_02090A70:
    ldrb r1, [r8, r1]
MobiClip_Code_02090A74:
    strb r0, [lr, #2]
MobiClip_Code_02090A78:
    ldrb r3, [lr, #5]
MobiClip_Code_02090A7C:
    add r2, r2, r4, asr #6
MobiClip_Code_02090A80:
    ldrb r2, [r8, r2]
MobiClip_Code_02090A84:
    strb r1, [lr, #3]
MobiClip_Code_02090A88:
    ldrb r4, [lr, #6]
MobiClip_Code_02090A8C:
    add r3, r3, r5, asr #6
MobiClip_Code_02090A90:
    ldrb r3, [r8, r3]
MobiClip_Code_02090A94:
    strb r2, [lr, #4]
MobiClip_Code_02090A98:
    ldrb r5, [lr, #7]
MobiClip_Code_02090A9C:
    add r4, r4, r6, asr #6
MobiClip_Code_02090AA0:
    ldrb r4, [r8, r4]
MobiClip_Code_02090AA4:
    strb r3, [lr, #5]
MobiClip_Code_02090AA8:
    add r5, r5, r7, asr #6
MobiClip_Code_02090AAC:
    ldrb r5, [r8, r5]
MobiClip_Code_02090AB0:
    strb r4, [lr, #6]
MobiClip_Code_02090AB4:
    subs ip, ip, #1
MobiClip_Code_02090AB8:
    strb r5, [lr, #7]
MobiClip_Code_02090ABC:
    add lr, lr, #0x100
MobiClip_Code_02090AC0:
    bne MobiClip_Code_020909AC
MobiClip_Code_02090AC4:
    pop {r0, r1, r2, r3, sl, fp, ip, pc}
MobiClip_Code_02090AC8:
    push {r0, r1, r2, r3}
MobiClip_Code_02090ACC:
    add lr, r0, #0x1b4
MobiClip_Code_02090AD0:
    add fp, lr, #0x100
MobiClip_Code_02090AD4:
    ldm lr!, {r0, r1, r2, r3}
MobiClip_Code_02090AD8:
    add r0, r0, #0x20
MobiClip_Code_02090ADC:
    mov ip, #4
MobiClip_Code_02090AE0:
    add lr, lr, #0x10
MobiClip_Code_02090AE4:
    sub r4, r0, r2, asr #1
MobiClip_Code_02090AE8:
    sub r6, r0, r2
MobiClip_Code_02090AEC:
    add sb, r0, r2, asr #1
MobiClip_Code_02090AF0:
    add r0, r0, r2
MobiClip_Code_02090AF4:
    sub r8, r1, r3
MobiClip_Code_02090AF8:
    sub r8, r8, r3, asr #1
MobiClip_Code_02090AFC:
    add r7, r3, r1
MobiClip_Code_02090B00:
    add r7, r7, r1, asr #1
MobiClip_Code_02090B04:
    rsb r2, r3, #0
MobiClip_Code_02090B08:
    add r5, r1, r8, asr #2
MobiClip_Code_02090B0C:
    rsb r3, r1, #0
MobiClip_Code_02090B10:
    add r3, r8, r3, asr #2
MobiClip_Code_02090B14:
    add r1, r2, r7, asr #2
MobiClip_Code_02090B18:
    sub r7, r7, r2, asr #2
MobiClip_Code_02090B1C:
    add r0, r0, r7
MobiClip_Code_02090B20:
    sub r7, r0, r7, lsl #1
MobiClip_Code_02090B24:
    add r8, sb, r5
MobiClip_Code_02090B28:
    sub sb, sb, r5
MobiClip_Code_02090B2C:
    add r2, r4, r3
MobiClip_Code_02090B30:
    sub r5, r4, r3
MobiClip_Code_02090B34:
    add r3, r6, r1
MobiClip_Code_02090B38:
    sub r4, r6, r1
MobiClip_Code_02090B3C:
    mov r1, r8
MobiClip_Code_02090B40:
    mov r6, sb
MobiClip_Code_02090B44:
    str r7, [fp, #0x70]
MobiClip_Code_02090B48:
    str r6, [fp, #0x60]
MobiClip_Code_02090B4C:
    str r5, [fp, #0x50]
MobiClip_Code_02090B50:
    str r4, [fp, #0x40]
MobiClip_Code_02090B54:
    str r3, [fp, #0x30]
MobiClip_Code_02090B58:
    str r2, [fp, #0x20]
MobiClip_Code_02090B5C:
    str r1, [fp, #0x10]
MobiClip_Code_02090B60:
    str r0, [fp], #4
MobiClip_Code_02090B64:
    subs ip, ip, #1
MobiClip_Code_02090B68:
    ldmne lr!, {r0, r1, r2, r3}
MobiClip_Code_02090B6C:
    bne MobiClip_Code_02090AE0
MobiClip_Code_02090B70:
    sub fp, fp, #0x10
MobiClip_Code_02090B74:
    ldr lr, [sp, #0x14]
MobiClip_Code_02090B78:
    mov ip, #8
MobiClip_Code_02090B7C:
    ldr r8, [fp, #-0x270]
MobiClip_Code_02090B80:
    ldm fp!, {r0, r1, r2, r3}
MobiClip_Code_02090B84:
    sub r4, r0, r2, asr #1
MobiClip_Code_02090B88:
    sub r6, r0, r2
MobiClip_Code_02090B8C:
    add sl, r0, r2, asr #1
MobiClip_Code_02090B90:
    add r0, r0, r2
MobiClip_Code_02090B94:
    sub sb, r1, r3
MobiClip_Code_02090B98:
    sub sb, sb, r3, asr #1
MobiClip_Code_02090B9C:
    add r7, r3, r1
MobiClip_Code_02090BA0:
    add r7, r7, r1, asr #1
MobiClip_Code_02090BA4:
    rsb r2, r3, #0
MobiClip_Code_02090BA8:
    add r5, r1, sb, asr #2
MobiClip_Code_02090BAC:
    rsb r3, r1, #0
MobiClip_Code_02090BB0:
    add r3, sb, r3, asr #2
MobiClip_Code_02090BB4:
    add r1, r2, r7, asr #2
MobiClip_Code_02090BB8:
    sub r7, r7, r2, asr #2
MobiClip_Code_02090BBC:
    add r0, r0, r7
MobiClip_Code_02090BC0:
    sub r7, r0, r7, lsl #1
MobiClip_Code_02090BC4:
    add sb, sl, r5
MobiClip_Code_02090BC8:
    sub sl, sl, r5
MobiClip_Code_02090BCC:
    add r2, r4, r3
MobiClip_Code_02090BD0:
    sub r5, r4, r3
MobiClip_Code_02090BD4:
    add r3, r6, r1
MobiClip_Code_02090BD8:
    sub r4, r6, r1
MobiClip_Code_02090BDC:
    mov r1, sb
MobiClip_Code_02090BE0:
    mov r6, sl
MobiClip_Code_02090BE4:
    ldrb sb, [lr]
MobiClip_Code_02090BE8:
    ldrb sl, [lr, #1]
MobiClip_Code_02090BEC:
    add sb, sb, r0, asr #6
MobiClip_Code_02090BF0:
    ldrb sb, [r8, sb]
MobiClip_Code_02090BF4:
    ldrb r0, [lr, #2]
MobiClip_Code_02090BF8:
    add sl, sl, r1, asr #6
MobiClip_Code_02090BFC:
    ldrb sl, [r8, sl]
MobiClip_Code_02090C00:
    strb sb, [lr]
MobiClip_Code_02090C04:
    ldrb r1, [lr, #3]
MobiClip_Code_02090C08:
    add r0, r0, r2, asr #6
MobiClip_Code_02090C0C:
    ldrb r0, [r8, r0]
MobiClip_Code_02090C10:
    strb sl, [lr, #1]
MobiClip_Code_02090C14:
    ldrb r2, [lr, #4]
MobiClip_Code_02090C18:
    add r1, r1, r3, asr #6
MobiClip_Code_02090C1C:
    ldrb r1, [r8, r1]
MobiClip_Code_02090C20:
    strb r0, [lr, #2]
MobiClip_Code_02090C24:
    ldrb r3, [lr, #5]
MobiClip_Code_02090C28:
    add r2, r2, r4, asr #6
MobiClip_Code_02090C2C:
    ldrb r2, [r8, r2]
MobiClip_Code_02090C30:
    strb r1, [lr, #3]
MobiClip_Code_02090C34:
    ldrb r4, [lr, #6]
MobiClip_Code_02090C38:
    add r3, r3, r5, asr #6
MobiClip_Code_02090C3C:
    ldrb r3, [r8, r3]
MobiClip_Code_02090C40:
    strb r2, [lr, #4]
MobiClip_Code_02090C44:
    ldrb r5, [lr, #7]
MobiClip_Code_02090C48:
    add r4, r4, r6, asr #6
MobiClip_Code_02090C4C:
    ldrb r4, [r8, r4]
MobiClip_Code_02090C50:
    strb r3, [lr, #5]
MobiClip_Code_02090C54:
    add r5, r5, r7, asr #6
MobiClip_Code_02090C58:
    ldrb r5, [r8, r5]
MobiClip_Code_02090C5C:
    strb r4, [lr, #6]
MobiClip_Code_02090C60:
    subs ip, ip, #1
MobiClip_Code_02090C64:
    strb r5, [lr, #7]
MobiClip_Code_02090C68:
    add lr, lr, #0x100
MobiClip_Code_02090C6C:
    bne MobiClip_Code_02090B80
MobiClip_Code_02090C70:
    pop {r0, r1, r2, r3, sl, fp, ip, pc}
MobiClip_Code_02090C74:
    push {r0, r1, r2, r3}
MobiClip_Code_02090C78:
    add lr, r0, #0x1b4
MobiClip_Code_02090C7C:
    ldm lr, {r8, sb}
MobiClip_Code_02090C80:
    ldr sl, [lr, #0x20]
MobiClip_Code_02090C84:
    add r8, r8, #0x20
MobiClip_Code_02090C88:
    add r7, sb, sb, asr #1
MobiClip_Code_02090C8C:
    asr fp, r7, #2
MobiClip_Code_02090C90:
    rsb r3, sb, #0
MobiClip_Code_02090C94:
    add r3, sb, r3, asr #2
MobiClip_Code_02090C98:
    add r5, sb, sb, asr #2
MobiClip_Code_02090C9C:
    add r0, r8, r7
MobiClip_Code_02090CA0:
    sub r7, r8, r7
MobiClip_Code_02090CA4:
    add r1, r8, r5
MobiClip_Code_02090CA8:
    sub r6, r8, r5
MobiClip_Code_02090CAC:
    add r2, r8, r3
MobiClip_Code_02090CB0:
    sub r5, r8, r3
MobiClip_Code_02090CB4:
    add r3, r8, fp
MobiClip_Code_02090CB8:
    sub r4, r8, fp
MobiClip_Code_02090CBC:
    stm lr, {r0, r1, r2, r3, r4, r5, r6, r7}
MobiClip_Code_02090CC0:
    add r7, sl, sl, asr #1
MobiClip_Code_02090CC4:
    asr r1, r7, #2
MobiClip_Code_02090CC8:
    rsb r3, sl, #0
MobiClip_Code_02090CCC:
    add r3, sl, r3, asr #2
MobiClip_Code_02090CD0:
    add r5, sl, sl, asr #2
MobiClip_Code_02090CD4:
    ldr fp, [sp, #0x14]
MobiClip_Code_02090CD8:
    mov ip, #8
MobiClip_Code_02090CDC:
    ldr r8, [lr, #-0x170]
MobiClip_Code_02090CE0:
    ldr r0, [lr], #4
MobiClip_Code_02090CE4:
    ldrb sb, [fp]
MobiClip_Code_02090CE8:
    ldrb sl, [fp, #1]
MobiClip_Code_02090CEC:
    add r2, r0, r7
MobiClip_Code_02090CF0:
    add sb, sb, r2, asr #6
MobiClip_Code_02090CF4:
    ldrb sb, [r8, sb]
MobiClip_Code_02090CF8:
    ldrb r4, [fp, #2]
MobiClip_Code_02090CFC:
    add r2, r0, r5
MobiClip_Code_02090D00:
    add sl, sl, r2, asr #6
MobiClip_Code_02090D04:
    ldrb sl, [r8, sl]
MobiClip_Code_02090D08:
    strb sb, [fp]
MobiClip_Code_02090D0C:
    ldrb r6, [fp, #3]
MobiClip_Code_02090D10:
    add r2, r0, r3
MobiClip_Code_02090D14:
    add r4, r4, r2, asr #6
MobiClip_Code_02090D18:
    ldrb r4, [r8, r4]
MobiClip_Code_02090D1C:
    strb sl, [fp, #1]
MobiClip_Code_02090D20:
    ldrb sb, [fp, #4]
MobiClip_Code_02090D24:
    add r2, r0, r1
MobiClip_Code_02090D28:
    add r6, r6, r2, asr #6
MobiClip_Code_02090D2C:
    ldrb r6, [r8, r6]
MobiClip_Code_02090D30:
    strb r4, [fp, #2]
MobiClip_Code_02090D34:
    ldrb sl, [fp, #5]
MobiClip_Code_02090D38:
    sub r2, r0, r1
MobiClip_Code_02090D3C:
    add sb, sb, r2, asr #6
MobiClip_Code_02090D40:
    ldrb sb, [r8, sb]
MobiClip_Code_02090D44:
    strb r6, [fp, #3]
MobiClip_Code_02090D48:
    ldrb r4, [fp, #6]
MobiClip_Code_02090D4C:
    sub r2, r0, r3
MobiClip_Code_02090D50:
    add sl, sl, r2, asr #6
MobiClip_Code_02090D54:
    ldrb sl, [r8, sl]
MobiClip_Code_02090D58:
    strb sb, [fp, #4]
MobiClip_Code_02090D5C:
    ldrb r6, [fp, #7]
MobiClip_Code_02090D60:
    sub r2, r0, r5
MobiClip_Code_02090D64:
    add r4, r4, r2, asr #6
MobiClip_Code_02090D68:
    ldrb r4, [r8, r4]
MobiClip_Code_02090D6C:
    strb sl, [fp, #5]
MobiClip_Code_02090D70:
    sub r2, r0, r7
MobiClip_Code_02090D74:
    add r6, r6, r2, asr #6
MobiClip_Code_02090D78:
    ldrb r6, [r8, r6]
MobiClip_Code_02090D7C:
    strb r4, [fp, #6]
MobiClip_Code_02090D80:
    subs ip, ip, #1
MobiClip_Code_02090D84:
    strb r6, [fp, #7]
MobiClip_Code_02090D88:
    add fp, fp, #0x100
MobiClip_Code_02090D8C:
    bne MobiClip_Code_02090CE0
MobiClip_Code_02090D90:
    pop {r0, r1, r2, r3, sl, fp, ip, pc}
MobiClip_Code_02090D94:
    push {r0, r1, r2, r3}
MobiClip_Code_02090D98:
    add lr, r0, #0x1b4
MobiClip_Code_02090D9C:
    ldr sb, [lr]
MobiClip_Code_02090DA0:
    add sb, sb, #0x20
MobiClip_Code_02090DA4:
    asr sb, sb, #6
MobiClip_Code_02090DA8:
    ldr lr, [sp, #0x14]
MobiClip_Code_02090DAC:
    mov ip, #8
MobiClip_Code_02090DB0:
    ldr r8, [r0, #0x44]
MobiClip_Code_02090DB4:
    ldrb r0, [lr]
MobiClip_Code_02090DB8:
    ldrb r1, [lr, #1]
MobiClip_Code_02090DBC:
    ldrb r2, [lr, #2]
MobiClip_Code_02090DC0:
    ldrb r3, [lr, #3]
MobiClip_Code_02090DC4:
    ldrb r4, [lr, #4]
MobiClip_Code_02090DC8:
    ldrb r5, [lr, #5]
MobiClip_Code_02090DCC:
    ldrb r6, [lr, #6]
MobiClip_Code_02090DD0:
    ldrb r7, [lr, #7]
MobiClip_Code_02090DD4:
    add r0, r0, sb
MobiClip_Code_02090DD8:
    add r1, r1, sb
MobiClip_Code_02090DDC:
    add r2, r2, sb
MobiClip_Code_02090DE0:
    add r3, r3, sb
MobiClip_Code_02090DE4:
    add r4, r4, sb
MobiClip_Code_02090DE8:
    add r5, r5, sb
MobiClip_Code_02090DEC:
    add r6, r6, sb
MobiClip_Code_02090DF0:
    add r7, r7, sb
MobiClip_Code_02090DF4:
    ldrb r0, [r8, r0]
MobiClip_Code_02090DF8:
    ldrb r1, [r8, r1]
MobiClip_Code_02090DFC:
    ldrb r2, [r8, r2]
MobiClip_Code_02090E00:
    ldrb r3, [r8, r3]
MobiClip_Code_02090E04:
    ldrb r4, [r8, r4]
MobiClip_Code_02090E08:
    ldrb r5, [r8, r5]
MobiClip_Code_02090E0C:
    ldrb r6, [r8, r6]
MobiClip_Code_02090E10:
    ldrb r7, [r8, r7]
MobiClip_Code_02090E14:
    strb r7, [lr, #7]
MobiClip_Code_02090E18:
    strb r6, [lr, #6]
MobiClip_Code_02090E1C:
    strb r5, [lr, #5]
MobiClip_Code_02090E20:
    strb r4, [lr, #4]
MobiClip_Code_02090E24:
    strb r3, [lr, #3]
MobiClip_Code_02090E28:
    strb r2, [lr, #2]
MobiClip_Code_02090E2C:
    strb r1, [lr, #1]
MobiClip_Code_02090E30:
    strb r0, [lr], #0x100
MobiClip_Code_02090E34:
    subs ip, ip, #1
MobiClip_Code_02090E38:
    bne MobiClip_Code_02090DB4
MobiClip_Code_02090E3C:
    pop {r0, r1, r2, r3, sl, fp, ip, pc}
MobiClip_Code_02090E40:
    push {r0, r1, r2, r3}
MobiClip_Code_02090E44:
    add lr, r0, #0x1b4
MobiClip_Code_02090E48:
    add fp, lr, #0x40
MobiClip_Code_02090E4C:
    ldm lr!, {r0, r1, r2, r3}
MobiClip_Code_02090E50:
    add r0, r0, #0x20
MobiClip_Code_02090E54:
    mov ip, #4
MobiClip_Code_02090E58:
    add r0, r0, r2
MobiClip_Code_02090E5C:
    sub r2, r0, r2, lsl #1
MobiClip_Code_02090E60:
    rsb r8, r3, r1, asr #1
MobiClip_Code_02090E64:
    add sb, r1, r3, asr #1
MobiClip_Code_02090E68:
    sub r3, r0, sb
MobiClip_Code_02090E6C:
    add r0, r0, sb
MobiClip_Code_02090E70:
    add r1, r2, r8
MobiClip_Code_02090E74:
    sub r2, r2, r8
MobiClip_Code_02090E78:
    str r3, [fp, #0x30]
MobiClip_Code_02090E7C:
    str r2, [fp, #0x20]
MobiClip_Code_02090E80:
    str r1, [fp, #0x10]
MobiClip_Code_02090E84:
    str r0, [fp], #4
MobiClip_Code_02090E88:
    subs ip, ip, #1
MobiClip_Code_02090E8C:
    ldmne lr!, {r0, r1, r2, r3}
MobiClip_Code_02090E90:
    bne MobiClip_Code_02090E58
MobiClip_Code_02090E94:
    sub fp, fp, #0x10
MobiClip_Code_02090E98:
    ldr lr, [sp, #0x14]
MobiClip_Code_02090E9C:
    mov ip, #4
MobiClip_Code_02090EA0:
    ldr r8, [fp, #-0x1b0]
MobiClip_Code_02090EA4:
    ldm fp!, {r0, r1, r2, r3}
MobiClip_Code_02090EA8:
    add r0, r0, r2
MobiClip_Code_02090EAC:
    sub r2, r0, r2, lsl #1
MobiClip_Code_02090EB0:
    rsb sb, r3, r1, asr #1
MobiClip_Code_02090EB4:
    add sl, r1, r3, asr #1
MobiClip_Code_02090EB8:
    sub r3, r0, sl
MobiClip_Code_02090EBC:
    add r0, r0, sl
MobiClip_Code_02090EC0:
    add r1, r2, sb
MobiClip_Code_02090EC4:
    sub r2, r2, sb
MobiClip_Code_02090EC8:
    ldrb r4, [lr]
MobiClip_Code_02090ECC:
    ldrb r5, [lr, #1]
MobiClip_Code_02090ED0:
    ldrb r6, [lr, #2]
MobiClip_Code_02090ED4:
    ldrb r7, [lr, #3]
MobiClip_Code_02090ED8:
    add r4, r4, r0, asr #6
MobiClip_Code_02090EDC:
    add r5, r5, r1, asr #6
MobiClip_Code_02090EE0:
    add r6, r6, r2, asr #6
MobiClip_Code_02090EE4:
    add r7, r7, r3, asr #6
MobiClip_Code_02090EE8:
    ldrb r4, [r8, r4]
MobiClip_Code_02090EEC:
    ldrb r5, [r8, r5]
MobiClip_Code_02090EF0:
    ldrb r6, [r8, r6]
MobiClip_Code_02090EF4:
    ldrb r7, [r8, r7]
MobiClip_Code_02090EF8:
    strb r7, [lr, #3]
MobiClip_Code_02090EFC:
    strb r6, [lr, #2]
MobiClip_Code_02090F00:
    strb r5, [lr, #1]
MobiClip_Code_02090F04:
    strb r4, [lr], #0x100
MobiClip_Code_02090F08:
    subs ip, ip, #1
MobiClip_Code_02090F0C:
    bne MobiClip_Code_02090EA4
MobiClip_Code_02090F10:
    pop {r0, r1, r2, r3, sl, fp, ip, pc}
MobiClip_Code_02090F14:
    add lr, r0, #0x1b4
MobiClip_Code_02090F18:
    ldr sb, [lr]
MobiClip_Code_02090F1C:
    add sb, sb, #0x20
MobiClip_Code_02090F20:
    asr sb, sb, #6
MobiClip_Code_02090F24:
    ldr lr, [sp, #4]
MobiClip_Code_02090F28:
    mov ip, #4
MobiClip_Code_02090F2C:
    ldr r8, [r0, #0x44]
MobiClip_Code_02090F30:
    ldrb r4, [lr]
MobiClip_Code_02090F34:
    ldrb r5, [lr, #1]
MobiClip_Code_02090F38:
    ldrb r6, [lr, #2]
MobiClip_Code_02090F3C:
    ldrb r7, [lr, #3]
MobiClip_Code_02090F40:
    add r4, r4, sb
MobiClip_Code_02090F44:
    add r5, r5, sb
MobiClip_Code_02090F48:
    add r6, r6, sb
MobiClip_Code_02090F4C:
    add r7, r7, sb
MobiClip_Code_02090F50:
    ldrb r4, [r8, r4]
MobiClip_Code_02090F54:
    ldrb r5, [r8, r5]
MobiClip_Code_02090F58:
    ldrb r6, [r8, r6]
MobiClip_Code_02090F5C:
    ldrb r7, [r8, r7]
MobiClip_Code_02090F60:
    strb r7, [lr, #3]
MobiClip_Code_02090F64:
    strb r6, [lr, #2]
MobiClip_Code_02090F68:
    strb r5, [lr, #1]
MobiClip_Code_02090F6C:
    strb r4, [lr], #0x100
MobiClip_Code_02090F70:
    subs ip, ip, #1
MobiClip_Code_02090F74:
    bne MobiClip_Code_02090F30
MobiClip_Code_02090F78:
    pop {sl, fp, ip, pc}
    /* semantic constants 0x02090f7c..0x020910fc */
    .global gMobiClipQuant8BaseMatrices
    .type gMobiClipQuant8BaseMatrices, %object
gMobiClipQuant8BaseMatrices:
    .byte 0x14, 0x13, 0x13, 0x19, 0x12, 0x19, 0x13, 0x18, 0x18, 0x13, 0x14, 0x12, 0x20, 0x12, 0x14, 0x13
    .byte 0x13, 0x18, 0x18, 0x13, 0x13, 0x19, 0x12, 0x19, 0x12, 0x19, 0x12, 0x19, 0x13, 0x18, 0x18, 0x13
    .byte 0x13, 0x18, 0x18, 0x13, 0x12, 0x20, 0x12, 0x14, 0x12, 0x20, 0x12, 0x18, 0x18, 0x13, 0x13, 0x18
    .byte 0x18, 0x12, 0x19, 0x12, 0x19, 0x12, 0x13, 0x18, 0x18, 0x13, 0x12, 0x20, 0x12, 0x18, 0x18, 0x12
    .byte 0x16, 0x15, 0x15, 0x1c, 0x13, 0x1c, 0x15, 0x1a, 0x1a, 0x15, 0x16, 0x13, 0x23, 0x13, 0x16, 0x15
    .byte 0x15, 0x1a, 0x1a, 0x15, 0x15, 0x1c, 0x13, 0x1c, 0x13, 0x1c, 0x13, 0x1c, 0x15, 0x1a, 0x1a, 0x15
    .byte 0x15, 0x1a, 0x1a, 0x15, 0x13, 0x23, 0x13, 0x16, 0x13, 0x23, 0x13, 0x1a, 0x1a, 0x15, 0x15, 0x1a
    .byte 0x1a, 0x13, 0x1c, 0x13, 0x1c, 0x13, 0x15, 0x1a, 0x1a, 0x15, 0x13, 0x23, 0x13, 0x1a, 0x1a, 0x13
    .byte 0x1a, 0x18, 0x18, 0x21, 0x17, 0x21, 0x18, 0x1f, 0x1f, 0x18, 0x1a, 0x17, 0x2a, 0x17, 0x1a, 0x18
    .byte 0x18, 0x1f, 0x1f, 0x18, 0x18, 0x21, 0x17, 0x21, 0x17, 0x21, 0x17, 0x21, 0x18, 0x1f, 0x1f, 0x18
    .byte 0x18, 0x1f, 0x1f, 0x18, 0x17, 0x2a, 0x17, 0x1a, 0x17, 0x2a, 0x17, 0x1f, 0x1f, 0x18, 0x18, 0x1f
    .byte 0x1f, 0x17, 0x21, 0x17, 0x21, 0x17, 0x18, 0x1f, 0x1f, 0x18, 0x17, 0x2a, 0x17, 0x1f, 0x1f, 0x17
    .byte 0x1c, 0x1a, 0x1a, 0x23, 0x19, 0x23, 0x1a, 0x21, 0x21, 0x1a, 0x1c, 0x19, 0x2d, 0x19, 0x1c, 0x1a
    .byte 0x1a, 0x21, 0x21, 0x1a, 0x1a, 0x23, 0x19, 0x23, 0x19, 0x23, 0x19, 0x23, 0x1a, 0x21, 0x21, 0x1a
    .byte 0x1a, 0x21, 0x21, 0x1a, 0x19, 0x2d, 0x19, 0x1c, 0x19, 0x2d, 0x19, 0x21, 0x21, 0x1a, 0x1a, 0x21
    .byte 0x21, 0x19, 0x23, 0x19, 0x23, 0x19, 0x1a, 0x21, 0x21, 0x1a, 0x19, 0x2d, 0x19, 0x21, 0x21, 0x19
    .byte 0x20, 0x1e, 0x1e, 0x28, 0x1c, 0x28, 0x1e, 0x26, 0x26, 0x1e, 0x20, 0x1c, 0x33, 0x1c, 0x20, 0x1e
    .byte 0x1e, 0x26, 0x26, 0x1e, 0x1e, 0x28, 0x1c, 0x28, 0x1c, 0x28, 0x1c, 0x28, 0x1e, 0x26, 0x26, 0x1e
    .byte 0x1e, 0x26, 0x26, 0x1e, 0x1c, 0x33, 0x1c, 0x20, 0x1c, 0x33, 0x1c, 0x26, 0x26, 0x1e, 0x1e, 0x26
    .byte 0x26, 0x1c, 0x28, 0x1c, 0x28, 0x1c, 0x1e, 0x26, 0x26, 0x1e, 0x1c, 0x33, 0x1c, 0x26, 0x26, 0x1c
    .byte 0x24, 0x22, 0x22, 0x2e, 0x20, 0x2e, 0x22, 0x2b, 0x2b, 0x22, 0x24, 0x20, 0x3a, 0x20, 0x24, 0x22
    .byte 0x22, 0x2b, 0x2b, 0x22, 0x22, 0x2e, 0x20, 0x2e, 0x20, 0x2e, 0x20, 0x2e, 0x22, 0x2b, 0x2b, 0x22
    .byte 0x22, 0x2b, 0x2b, 0x22, 0x20, 0x3a, 0x20, 0x24, 0x20, 0x3a, 0x20, 0x2b, 0x2b, 0x22, 0x22, 0x2b
    .byte 0x2b, 0x20, 0x2e, 0x20, 0x2e, 0x20, 0x22, 0x2b, 0x2b, 0x22, 0x20, 0x3a, 0x20, 0x2b, 0x2b, 0x20
    .size gMobiClipQuant8BaseMatrices, . - gMobiClipQuant8BaseMatrices
    /* semantic constants 0x020910fc..0x0209113c */
    .global gMobiClipScan8
    .type gMobiClipScan8, %object
gMobiClipScan8:
    .byte 0x00, 0x01, 0x08, 0x10, 0x09, 0x02, 0x03, 0x0a, 0x11, 0x18, 0x20, 0x19, 0x12, 0x0b, 0x04, 0x05
    .byte 0x0c, 0x13, 0x1a, 0x21, 0x28, 0x30, 0x29, 0x22, 0x1b, 0x14, 0x0d, 0x06, 0x07, 0x0e, 0x15, 0x1c
    .byte 0x23, 0x2a, 0x31, 0x38, 0x39, 0x32, 0x2b, 0x24, 0x1d, 0x16, 0x0f, 0x17, 0x1e, 0x25, 0x2c, 0x33
    .byte 0x3a, 0x3b, 0x34, 0x2d, 0x26, 0x1f, 0x27, 0x2e, 0x35, 0x3c, 0x3d, 0x36, 0x2f, 0x37, 0x3e, 0x3f
    .size gMobiClipScan8, . - gMobiClipScan8
    /* semantic constants 0x0209113c..0x0209119c */
    .global gMobiClipQuant4BaseMatrices
    .type gMobiClipQuant4BaseMatrices, %object
gMobiClipQuant4BaseMatrices:
    .byte 0x0a, 0x0d, 0x0d, 0x0a, 0x10, 0x0a, 0x0d, 0x0d, 0x0d, 0x0d, 0x10, 0x0a, 0x10, 0x0d, 0x0d, 0x10
    .byte 0x0b, 0x0e, 0x0e, 0x0b, 0x12, 0x0b, 0x0e, 0x0e, 0x0e, 0x0e, 0x12, 0x0b, 0x12, 0x0e, 0x0e, 0x12
    .byte 0x0d, 0x10, 0x10, 0x0d, 0x14, 0x0d, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0d, 0x14, 0x10, 0x10, 0x14
    .byte 0x0e, 0x12, 0x12, 0x0e, 0x17, 0x0e, 0x12, 0x12, 0x12, 0x12, 0x17, 0x0e, 0x17, 0x12, 0x12, 0x17
    .byte 0x10, 0x14, 0x14, 0x10, 0x19, 0x10, 0x14, 0x14, 0x14, 0x14, 0x19, 0x10, 0x19, 0x14, 0x14, 0x19
    .byte 0x12, 0x17, 0x17, 0x12, 0x1d, 0x12, 0x17, 0x17, 0x17, 0x17, 0x1d, 0x12, 0x1d, 0x17, 0x17, 0x1d
    .size gMobiClipQuant4BaseMatrices, . - gMobiClipQuant4BaseMatrices
    /* semantic constants 0x0209119c..0x020911ac */
    .global gMobiClipScan4
    .type gMobiClipScan4, %object
gMobiClipScan4:
    .byte 0x00, 0x04, 0x01, 0x02, 0x05, 0x08, 0x0c, 0x09, 0x06, 0x03, 0x07, 0x0a, 0x0d, 0x0e, 0x0b, 0x0f
    .size gMobiClipScan4, . - gMobiClipScan4
    /* semantic constants 0x020911ac..0x020911e2 */
    .global gMobiClipQpShift
    .type gMobiClipQpShift, %object
gMobiClipQpShift:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02
    .byte 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05
    .byte 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07
    .byte 0x08, 0x08, 0x08, 0x08, 0x08, 0x08
    .size gMobiClipQpShift, . - gMobiClipQpShift
    /* semantic constants 0x020911e2..0x02091218 */
    .global gMobiClipQpMatrixSelector
    .type gMobiClipQpMatrixSelector, %object
gMobiClipQpMatrixSelector:
    .byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x02, 0x03
    .byte 0x04, 0x05, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01
    .byte 0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05
    .byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05
    .size gMobiClipQpMatrixSelector, . - gMobiClipQpMatrixSelector
MobiClip_Code_02091218:
    str r4, [r0, #0x3b4]
MobiClip_Code_0209121C:
    sub r5, pc, #0x78
MobiClip_Code_02091220:
    ldrb r6, [r5, r4]
MobiClip_Code_02091224:
    add r6, r6, #8
MobiClip_Code_02091228:
    sub r5, pc, #0x4e
MobiClip_Code_0209122C:
    ldrb r5, [r5, r4]
MobiClip_Code_02091230:
    sub r4, pc, #0xfc
MobiClip_Code_02091234:
    add r4, r4, r5, lsl #4
MobiClip_Code_02091238:
    sub r7, pc, #0xa4
MobiClip_Code_0209123C:
    add r8, r0, #0x174
MobiClip_Code_02091240:
    mov sb, #0x10
MobiClip_Code_02091244:
    ldrb sl, [r4], #1
MobiClip_Code_02091248:
    ldrb fp, [r7], #1
MobiClip_Code_0209124C:
    orr fp, fp, sl, lsl r6
MobiClip_Code_02091250:
    str fp, [r8], #4
MobiClip_Code_02091254:
    subs sb, sb, #1
MobiClip_Code_02091258:
    bne MobiClip_Code_02091244
MobiClip_Code_0209125C:
    sub r6, r6, #2
MobiClip_Code_02091260:
    sub r4, pc, #0x2ec
MobiClip_Code_02091264:
    add r4, r4, r5, lsl #6
MobiClip_Code_02091268:
    sub r7, pc, #0x174
MobiClip_Code_0209126C:
    add r8, r0, #0x74
MobiClip_Code_02091270:
    mov sb, #0x40
MobiClip_Code_02091274:
    ldrb sl, [r4], #1
MobiClip_Code_02091278:
    ldrb fp, [r7], #1
MobiClip_Code_0209127C:
    orr fp, fp, sl, lsl r6
MobiClip_Code_02091280:
    str fp, [r8], #4
MobiClip_Code_02091284:
    subs sb, sb, #1
MobiClip_Code_02091288:
    bne MobiClip_Code_02091274
MobiClip_Code_0209128C:
    add r4, r0, #0x4c
MobiClip_Code_02091290:
    mov r5, #9
MobiClip_Code_02091294:
    strb r5, [r4, #1]
MobiClip_Code_02091298:
    strb r5, [r4, #2]
MobiClip_Code_0209129C:
    strb r5, [r4, #3]
MobiClip_Code_020912A0:
    strb r5, [r4, #4]
MobiClip_Code_020912A4:
    strb r5, [r4, #8]
MobiClip_Code_020912A8:
    strb r5, [r4, #0x10]
MobiClip_Code_020912AC:
    strb r5, [r4, #0x18]
MobiClip_Code_020912B0:
    strb r5, [r4, #0x20]
MobiClip_Code_020912B4:
    mov pc, lr
MobiClip_Code_020912B8:
    ldm r0, {r3, r4, r7, r8}
MobiClip_Code_020912BC:
    add r0, r0, #0x100
MobiClip_Code_020912C0:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_020912C4:
    add r1, r1, #0x100
MobiClip_Code_020912C8:
    subs r2, r2, #1
MobiClip_Code_020912CC:
    bne MobiClip_Code_020912B8
MobiClip_Code_020912D0:
    mov pc, lr
MobiClip_Code_020912D4:
    push {r5, r6}
MobiClip_Code_020912D8:
    ldr ip, [pc, #0xb6c]
MobiClip_Code_020912DC:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020912E0:
    add r0, r0, #0x100
MobiClip_Code_020912E4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020912E8:
    and r4, ip, r4, lsr #1
MobiClip_Code_020912EC:
    and r5, ip, r5, lsr #1
MobiClip_Code_020912F0:
    and r6, ip, r6, lsr #1
MobiClip_Code_020912F4:
    ldm r0, {r7, r8, sb, sl}
MobiClip_Code_020912F8:
    add r0, r0, #0x100
MobiClip_Code_020912FC:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091300:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091304:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091308:
    and sl, ip, sl, lsr #1
MobiClip_Code_0209130C:
    add r3, r3, r7
MobiClip_Code_02091310:
    add r4, r4, r8
MobiClip_Code_02091314:
    add r5, r5, sb
MobiClip_Code_02091318:
    add r6, r6, sl
MobiClip_Code_0209131C:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_02091320:
    add r1, r1, #0x100
MobiClip_Code_02091324:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_02091328:
    add r0, r0, #0x100
MobiClip_Code_0209132C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091330:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091334:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091338:
    and r6, ip, r6, lsr #1
MobiClip_Code_0209133C:
    add r7, r7, r3
MobiClip_Code_02091340:
    add r8, r8, r4
MobiClip_Code_02091344:
    add sb, sb, r5
MobiClip_Code_02091348:
    add sl, sl, r6
MobiClip_Code_0209134C:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_02091350:
    add r1, r1, #0x100
MobiClip_Code_02091354:
    subs r2, r2, #2
MobiClip_Code_02091358:
    bne MobiClip_Code_020912F4
MobiClip_Code_0209135C:
    pop {r5, r6}
MobiClip_Code_02091360:
    mov pc, lr
MobiClip_Code_02091364:
    ldr ip, [pc, #0xae0]
MobiClip_Code_02091368:
    ldm r0, {r3, r4, r7, r8}
MobiClip_Code_0209136C:
    ldrb sb, [r0, #0x10]
MobiClip_Code_02091370:
    add r0, r0, #0x100
MobiClip_Code_02091374:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091378:
    and r4, ip, r4, lsr #1
MobiClip_Code_0209137C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091380:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091384:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091388:
    add r3, r3, r3, lsr #8
MobiClip_Code_0209138C:
    add r3, r3, r4, lsl #24
MobiClip_Code_02091390:
    add r4, r4, r4, lsr #8
MobiClip_Code_02091394:
    add r4, r4, r7, lsl #24
MobiClip_Code_02091398:
    add r7, r7, r7, lsr #8
MobiClip_Code_0209139C:
    add r7, r7, r8, lsl #24
MobiClip_Code_020913A0:
    add r8, r8, r8, lsr #8
MobiClip_Code_020913A4:
    add r8, r8, sb, lsl #24
MobiClip_Code_020913A8:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_020913AC:
    add r1, r1, #0x100
MobiClip_Code_020913B0:
    subs r2, r2, #1
MobiClip_Code_020913B4:
    bne MobiClip_Code_02091368
MobiClip_Code_020913B8:
    mov pc, lr
MobiClip_Code_020913BC:
    push {r5, r6, lr}
MobiClip_Code_020913C0:
    ldr ip, [pc, #0xa84]
MobiClip_Code_020913C4:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020913C8:
    ldrb lr, [r0, #0x10]
MobiClip_Code_020913CC:
    add r0, r0, #0x100
MobiClip_Code_020913D0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020913D4:
    and r4, ip, r4, lsr #1
MobiClip_Code_020913D8:
    and r5, ip, r5, lsr #1
MobiClip_Code_020913DC:
    and r6, ip, r6, lsr #1
MobiClip_Code_020913E0:
    and lr, ip, lr, lsr #1
MobiClip_Code_020913E4:
    add r3, r3, r3, lsr #8
MobiClip_Code_020913E8:
    add r3, r3, r4, lsl #24
MobiClip_Code_020913EC:
    add r4, r4, r4, lsr #8
MobiClip_Code_020913F0:
    add r4, r4, r5, lsl #24
MobiClip_Code_020913F4:
    add r5, r5, r5, lsr #8
MobiClip_Code_020913F8:
    add r5, r5, r6, lsl #24
MobiClip_Code_020913FC:
    add r6, r6, r6, lsr #8
MobiClip_Code_02091400:
    add r6, r6, lr, lsl #24
MobiClip_Code_02091404:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091408:
    and r4, ip, r4, lsr #1
MobiClip_Code_0209140C:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091410:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091414:
    ldm r0, {r7, r8, sb, sl}
MobiClip_Code_02091418:
    ldrb lr, [r0, #0x10]
MobiClip_Code_0209141C:
    add r0, r0, #0x100
MobiClip_Code_02091420:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091424:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091428:
    and sb, ip, sb, lsr #1
MobiClip_Code_0209142C:
    and sl, ip, sl, lsr #1
MobiClip_Code_02091430:
    and lr, ip, lr, lsr #1
MobiClip_Code_02091434:
    add r7, r7, r7, lsr #8
MobiClip_Code_02091438:
    add r7, r7, r8, lsl #24
MobiClip_Code_0209143C:
    add r8, r8, r8, lsr #8
MobiClip_Code_02091440:
    add r8, r8, sb, lsl #24
MobiClip_Code_02091444:
    add sb, sb, sb, lsr #8
MobiClip_Code_02091448:
    add sb, sb, sl, lsl #24
MobiClip_Code_0209144C:
    add sl, sl, sl, lsr #8
MobiClip_Code_02091450:
    add sl, sl, lr, lsl #24
MobiClip_Code_02091454:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091458:
    and r8, ip, r8, lsr #1
MobiClip_Code_0209145C:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091460:
    and sl, ip, sl, lsr #1
MobiClip_Code_02091464:
    add r3, r3, r7
MobiClip_Code_02091468:
    add r4, r4, r8
MobiClip_Code_0209146C:
    add r5, r5, sb
MobiClip_Code_02091470:
    add r6, r6, sl
MobiClip_Code_02091474:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_02091478:
    add r1, r1, #0x100
MobiClip_Code_0209147C:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_02091480:
    ldrb lr, [r0, #0x10]
MobiClip_Code_02091484:
    add r0, r0, #0x100
MobiClip_Code_02091488:
    and r3, ip, r3, lsr #1
MobiClip_Code_0209148C:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091490:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091494:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091498:
    and lr, ip, lr, lsr #1
MobiClip_Code_0209149C:
    add r3, r3, r3, lsr #8
MobiClip_Code_020914A0:
    add r3, r3, r4, lsl #24
MobiClip_Code_020914A4:
    add r4, r4, r4, lsr #8
MobiClip_Code_020914A8:
    add r4, r4, r5, lsl #24
MobiClip_Code_020914AC:
    add r5, r5, r5, lsr #8
MobiClip_Code_020914B0:
    add r5, r5, r6, lsl #24
MobiClip_Code_020914B4:
    add r6, r6, r6, lsr #8
MobiClip_Code_020914B8:
    add r6, r6, lr, lsl #24
MobiClip_Code_020914BC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020914C0:
    and r4, ip, r4, lsr #1
MobiClip_Code_020914C4:
    and r5, ip, r5, lsr #1
MobiClip_Code_020914C8:
    and r6, ip, r6, lsr #1
MobiClip_Code_020914CC:
    add r7, r7, r3
MobiClip_Code_020914D0:
    add r8, r8, r4
MobiClip_Code_020914D4:
    add sb, sb, r5
MobiClip_Code_020914D8:
    add sl, sl, r6
MobiClip_Code_020914DC:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_020914E0:
    add r1, r1, #0x100
MobiClip_Code_020914E4:
    subs r2, r2, #2
MobiClip_Code_020914E8:
    bne MobiClip_Code_02091414
MobiClip_Code_020914EC:
    pop {r5, r6, pc}
MobiClip_Code_020914F0:
    sub r0, r0, #1
MobiClip_Code_020914F4:
    ldm r0, {r3, r4, r7, r8}
MobiClip_Code_020914F8:
    ldrb sb, [r0, #0x10]
MobiClip_Code_020914FC:
    add r0, r0, #0x100
MobiClip_Code_02091500:
    lsr r3, r3, #8
MobiClip_Code_02091504:
    add r3, r3, r4, lsl #24
MobiClip_Code_02091508:
    lsr r4, r4, #8
MobiClip_Code_0209150C:
    add r4, r4, r7, lsl #24
MobiClip_Code_02091510:
    lsr r7, r7, #8
MobiClip_Code_02091514:
    add r7, r7, r8, lsl #24
MobiClip_Code_02091518:
    lsr r8, r8, #8
MobiClip_Code_0209151C:
    add r8, r8, sb, lsl #24
MobiClip_Code_02091520:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_02091524:
    add r1, r1, #0x100
MobiClip_Code_02091528:
    subs r2, r2, #1
MobiClip_Code_0209152C:
    bne MobiClip_Code_020914F4
MobiClip_Code_02091530:
    mov pc, lr
MobiClip_Code_02091534:
    push {r5, r6, lr}
MobiClip_Code_02091538:
    sub r0, r0, #1
MobiClip_Code_0209153C:
    ldr ip, [pc, #0x908]
MobiClip_Code_02091540:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_02091544:
    ldrb lr, [r0, #0x10]
MobiClip_Code_02091548:
    add r0, r0, #0x100
MobiClip_Code_0209154C:
    lsr r3, r3, #8
MobiClip_Code_02091550:
    add r3, r3, r4, lsl #24
MobiClip_Code_02091554:
    lsr r4, r4, #8
MobiClip_Code_02091558:
    add r4, r4, r5, lsl #24
MobiClip_Code_0209155C:
    lsr r5, r5, #8
MobiClip_Code_02091560:
    add r5, r5, r6, lsl #24
MobiClip_Code_02091564:
    lsr r6, r6, #8
MobiClip_Code_02091568:
    add r6, r6, lr, lsl #24
MobiClip_Code_0209156C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091570:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091574:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091578:
    and r6, ip, r6, lsr #1
MobiClip_Code_0209157C:
    ldm r0, {r7, r8, sb, sl}
MobiClip_Code_02091580:
    ldrb lr, [r0, #0x10]
MobiClip_Code_02091584:
    add r0, r0, #0x100
MobiClip_Code_02091588:
    lsr r7, r7, #8
MobiClip_Code_0209158C:
    add r7, r7, r8, lsl #24
MobiClip_Code_02091590:
    lsr r8, r8, #8
MobiClip_Code_02091594:
    add r8, r8, sb, lsl #24
MobiClip_Code_02091598:
    lsr sb, sb, #8
MobiClip_Code_0209159C:
    add sb, sb, sl, lsl #24
MobiClip_Code_020915A0:
    lsr sl, sl, #8
MobiClip_Code_020915A4:
    add sl, sl, lr, lsl #24
MobiClip_Code_020915A8:
    and r7, ip, r7, lsr #1
MobiClip_Code_020915AC:
    and r8, ip, r8, lsr #1
MobiClip_Code_020915B0:
    and sb, ip, sb, lsr #1
MobiClip_Code_020915B4:
    and sl, ip, sl, lsr #1
MobiClip_Code_020915B8:
    add r3, r3, r7
MobiClip_Code_020915BC:
    add r4, r4, r8
MobiClip_Code_020915C0:
    add r5, r5, sb
MobiClip_Code_020915C4:
    add r6, r6, sl
MobiClip_Code_020915C8:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_020915CC:
    add r1, r1, #0x100
MobiClip_Code_020915D0:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020915D4:
    ldrb lr, [r0, #0x10]
MobiClip_Code_020915D8:
    add r0, r0, #0x100
MobiClip_Code_020915DC:
    lsr r3, r3, #8
MobiClip_Code_020915E0:
    add r3, r3, r4, lsl #24
MobiClip_Code_020915E4:
    lsr r4, r4, #8
MobiClip_Code_020915E8:
    add r4, r4, r5, lsl #24
MobiClip_Code_020915EC:
    lsr r5, r5, #8
MobiClip_Code_020915F0:
    add r5, r5, r6, lsl #24
MobiClip_Code_020915F4:
    lsr r6, r6, #8
MobiClip_Code_020915F8:
    add r6, r6, lr, lsl #24
MobiClip_Code_020915FC:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091600:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091604:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091608:
    and r6, ip, r6, lsr #1
MobiClip_Code_0209160C:
    add r7, r7, r3
MobiClip_Code_02091610:
    add r8, r8, r4
MobiClip_Code_02091614:
    add sb, sb, r5
MobiClip_Code_02091618:
    add sl, sl, r6
MobiClip_Code_0209161C:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_02091620:
    add r1, r1, #0x100
MobiClip_Code_02091624:
    subs r2, r2, #2
MobiClip_Code_02091628:
    bne MobiClip_Code_0209157C
MobiClip_Code_0209162C:
    pop {r5, r6, pc}
MobiClip_Code_02091630:
    ldr ip, [pc, #0x814]
MobiClip_Code_02091634:
    sub r0, r0, #1
MobiClip_Code_02091638:
    ldm r0, {r3, r4, r7, r8}
MobiClip_Code_0209163C:
    ldrh sb, [r0, #0x10]
MobiClip_Code_02091640:
    add r0, r0, #0x100
MobiClip_Code_02091644:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091648:
    and r4, ip, r4, lsr #1
MobiClip_Code_0209164C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091650:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091654:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091658:
    lsr sl, r3, #0x10
MobiClip_Code_0209165C:
    add sl, sl, r4, lsl #16
MobiClip_Code_02091660:
    add sl, sl, r3, lsr #8
MobiClip_Code_02091664:
    add r3, sl, r4, lsl #24
MobiClip_Code_02091668:
    lsr sl, r4, #0x10
MobiClip_Code_0209166C:
    add sl, sl, r7, lsl #16
MobiClip_Code_02091670:
    add sl, sl, r4, lsr #8
MobiClip_Code_02091674:
    add r4, sl, r7, lsl #24
MobiClip_Code_02091678:
    lsr sl, r7, #0x10
MobiClip_Code_0209167C:
    add sl, sl, r8, lsl #16
MobiClip_Code_02091680:
    add sl, sl, r7, lsr #8
MobiClip_Code_02091684:
    add r7, sl, r8, lsl #24
MobiClip_Code_02091688:
    lsr sl, r8, #0x10
MobiClip_Code_0209168C:
    add sl, sl, sb, lsl #16
MobiClip_Code_02091690:
    add sl, sl, r8, lsr #8
MobiClip_Code_02091694:
    add r8, sl, sb, lsl #24
MobiClip_Code_02091698:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_0209169C:
    add r1, r1, #0x100
MobiClip_Code_020916A0:
    subs r2, r2, #1
MobiClip_Code_020916A4:
    bne MobiClip_Code_02091638
MobiClip_Code_020916A8:
    mov pc, lr
MobiClip_Code_020916AC:
    push {r5, r6, fp, lr}
MobiClip_Code_020916B0:
    ldr ip, [pc, #0x794]
MobiClip_Code_020916B4:
    sub r0, r0, #1
MobiClip_Code_020916B8:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020916BC:
    ldrh lr, [r0, #0x10]
MobiClip_Code_020916C0:
    add r0, r0, #0x100
MobiClip_Code_020916C4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020916C8:
    and r4, ip, r4, lsr #1
MobiClip_Code_020916CC:
    and r5, ip, r5, lsr #1
MobiClip_Code_020916D0:
    and r6, ip, r6, lsr #1
MobiClip_Code_020916D4:
    and lr, ip, lr, lsr #1
MobiClip_Code_020916D8:
    lsr fp, r3, #0x10
MobiClip_Code_020916DC:
    add fp, fp, r4, lsl #16
MobiClip_Code_020916E0:
    add fp, fp, r3, lsr #8
MobiClip_Code_020916E4:
    add r3, fp, r4, lsl #24
MobiClip_Code_020916E8:
    lsr fp, r4, #0x10
MobiClip_Code_020916EC:
    add fp, fp, r5, lsl #16
MobiClip_Code_020916F0:
    add fp, fp, r4, lsr #8
MobiClip_Code_020916F4:
    add r4, fp, r5, lsl #24
MobiClip_Code_020916F8:
    lsr fp, r5, #0x10
MobiClip_Code_020916FC:
    add fp, fp, r6, lsl #16
MobiClip_Code_02091700:
    add fp, fp, r5, lsr #8
MobiClip_Code_02091704:
    add r5, fp, r6, lsl #24
MobiClip_Code_02091708:
    lsr fp, r6, #0x10
MobiClip_Code_0209170C:
    add fp, fp, lr, lsl #16
MobiClip_Code_02091710:
    add fp, fp, r6, lsr #8
MobiClip_Code_02091714:
    add r6, fp, lr, lsl #24
MobiClip_Code_02091718:
    and r3, ip, r3, lsr #1
MobiClip_Code_0209171C:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091720:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091724:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091728:
    ldm r0, {r7, r8, sb, sl}
MobiClip_Code_0209172C:
    ldrh lr, [r0, #0x10]
MobiClip_Code_02091730:
    add r0, r0, #0x100
MobiClip_Code_02091734:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091738:
    and r8, ip, r8, lsr #1
MobiClip_Code_0209173C:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091740:
    and sl, ip, sl, lsr #1
MobiClip_Code_02091744:
    and lr, ip, lr, lsr #1
MobiClip_Code_02091748:
    lsr fp, r7, #0x10
MobiClip_Code_0209174C:
    add fp, fp, r8, lsl #16
MobiClip_Code_02091750:
    add fp, fp, r7, lsr #8
MobiClip_Code_02091754:
    add r7, fp, r8, lsl #24
MobiClip_Code_02091758:
    lsr fp, r8, #0x10
MobiClip_Code_0209175C:
    add fp, fp, sb, lsl #16
MobiClip_Code_02091760:
    add fp, fp, r8, lsr #8
MobiClip_Code_02091764:
    add r8, fp, sb, lsl #24
MobiClip_Code_02091768:
    lsr fp, sb, #0x10
MobiClip_Code_0209176C:
    add fp, fp, sl, lsl #16
MobiClip_Code_02091770:
    add fp, fp, sb, lsr #8
MobiClip_Code_02091774:
    add sb, fp, sl, lsl #24
MobiClip_Code_02091778:
    lsr fp, sl, #0x10
MobiClip_Code_0209177C:
    add fp, fp, lr, lsl #16
MobiClip_Code_02091780:
    add fp, fp, sl, lsr #8
MobiClip_Code_02091784:
    add sl, fp, lr, lsl #24
MobiClip_Code_02091788:
    and r7, ip, r7, lsr #1
MobiClip_Code_0209178C:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091790:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091794:
    and sl, ip, sl, lsr #1
MobiClip_Code_02091798:
    add r3, r3, r7
MobiClip_Code_0209179C:
    add r4, r4, r8
MobiClip_Code_020917A0:
    add r5, r5, sb
MobiClip_Code_020917A4:
    add r6, r6, sl
MobiClip_Code_020917A8:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_020917AC:
    add r1, r1, #0x100
MobiClip_Code_020917B0:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020917B4:
    ldrh lr, [r0, #0x10]
MobiClip_Code_020917B8:
    add r0, r0, #0x100
MobiClip_Code_020917BC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020917C0:
    and r4, ip, r4, lsr #1
MobiClip_Code_020917C4:
    and r5, ip, r5, lsr #1
MobiClip_Code_020917C8:
    and r6, ip, r6, lsr #1
MobiClip_Code_020917CC:
    and lr, ip, lr, lsr #1
MobiClip_Code_020917D0:
    lsr fp, r3, #0x10
MobiClip_Code_020917D4:
    add fp, fp, r4, lsl #16
MobiClip_Code_020917D8:
    add fp, fp, r3, lsr #8
MobiClip_Code_020917DC:
    add r3, fp, r4, lsl #24
MobiClip_Code_020917E0:
    lsr fp, r4, #0x10
MobiClip_Code_020917E4:
    add fp, fp, r5, lsl #16
MobiClip_Code_020917E8:
    add fp, fp, r4, lsr #8
MobiClip_Code_020917EC:
    add r4, fp, r5, lsl #24
MobiClip_Code_020917F0:
    lsr fp, r5, #0x10
MobiClip_Code_020917F4:
    add fp, fp, r6, lsl #16
MobiClip_Code_020917F8:
    add fp, fp, r5, lsr #8
MobiClip_Code_020917FC:
    add r5, fp, r6, lsl #24
MobiClip_Code_02091800:
    lsr fp, r6, #0x10
MobiClip_Code_02091804:
    add fp, fp, lr, lsl #16
MobiClip_Code_02091808:
    add fp, fp, r6, lsr #8
MobiClip_Code_0209180C:
    add r6, fp, lr, lsl #24
MobiClip_Code_02091810:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091814:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091818:
    and r5, ip, r5, lsr #1
MobiClip_Code_0209181C:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091820:
    add r7, r7, r3
MobiClip_Code_02091824:
    add r8, r8, r4
MobiClip_Code_02091828:
    add sb, sb, r5
MobiClip_Code_0209182C:
    add sl, sl, r6
MobiClip_Code_02091830:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_02091834:
    add r1, r1, #0x100
MobiClip_Code_02091838:
    subs r2, r2, #2
MobiClip_Code_0209183C:
    bne MobiClip_Code_02091728
MobiClip_Code_02091840:
    pop {r5, r6, fp, pc}
MobiClip_Code_02091844:
    add r0, r0, #2
MobiClip_Code_02091848:
    ldrh r3, [r0, #-2]
MobiClip_Code_0209184C:
    ldm r0, {r4, r7, r8}
MobiClip_Code_02091850:
    ldrh sb, [r0, #0xc]
MobiClip_Code_02091854:
    add r0, r0, #0x100
MobiClip_Code_02091858:
    add r3, r3, r4, lsl #16
MobiClip_Code_0209185C:
    lsr r4, r4, #0x10
MobiClip_Code_02091860:
    add r4, r4, r7, lsl #16
MobiClip_Code_02091864:
    lsr r7, r7, #0x10
MobiClip_Code_02091868:
    add r7, r7, r8, lsl #16
MobiClip_Code_0209186C:
    lsr r8, r8, #0x10
MobiClip_Code_02091870:
    add r8, r8, sb, lsl #16
MobiClip_Code_02091874:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_02091878:
    add r1, r1, #0x100
MobiClip_Code_0209187C:
    subs r2, r2, #1
MobiClip_Code_02091880:
    bne MobiClip_Code_02091848
MobiClip_Code_02091884:
    mov pc, lr
MobiClip_Code_02091888:
    push {r5, r6, lr}
MobiClip_Code_0209188C:
    ldr ip, [pc, #0x5b8]
MobiClip_Code_02091890:
    add r0, r0, #2
MobiClip_Code_02091894:
    ldrh r3, [r0, #-2]
MobiClip_Code_02091898:
    ldm r0, {r4, r5, r6}
MobiClip_Code_0209189C:
    ldrh lr, [r0, #0xc]
MobiClip_Code_020918A0:
    add r0, r0, #0x100
MobiClip_Code_020918A4:
    add r3, r3, r4, lsl #16
MobiClip_Code_020918A8:
    lsr r4, r4, #0x10
MobiClip_Code_020918AC:
    add r4, r4, r5, lsl #16
MobiClip_Code_020918B0:
    lsr r5, r5, #0x10
MobiClip_Code_020918B4:
    add r5, r5, r6, lsl #16
MobiClip_Code_020918B8:
    lsr r6, r6, #0x10
MobiClip_Code_020918BC:
    add r6, r6, lr, lsl #16
MobiClip_Code_020918C0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020918C4:
    and r4, ip, r4, lsr #1
MobiClip_Code_020918C8:
    and r5, ip, r5, lsr #1
MobiClip_Code_020918CC:
    and r6, ip, r6, lsr #1
MobiClip_Code_020918D0:
    ldrh r7, [r0, #-2]
MobiClip_Code_020918D4:
    ldm r0, {r8, sb, sl}
MobiClip_Code_020918D8:
    ldrh lr, [r0, #0xc]
MobiClip_Code_020918DC:
    add r0, r0, #0x100
MobiClip_Code_020918E0:
    add r7, r7, r8, lsl #16
MobiClip_Code_020918E4:
    lsr r8, r8, #0x10
MobiClip_Code_020918E8:
    add r8, r8, sb, lsl #16
MobiClip_Code_020918EC:
    lsr sb, sb, #0x10
MobiClip_Code_020918F0:
    add sb, sb, sl, lsl #16
MobiClip_Code_020918F4:
    lsr sl, sl, #0x10
MobiClip_Code_020918F8:
    add sl, sl, lr, lsl #16
MobiClip_Code_020918FC:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091900:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091904:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091908:
    and sl, ip, sl, lsr #1
MobiClip_Code_0209190C:
    add r3, r3, r7
MobiClip_Code_02091910:
    add r4, r4, r8
MobiClip_Code_02091914:
    add r5, r5, sb
MobiClip_Code_02091918:
    add r6, r6, sl
MobiClip_Code_0209191C:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_02091920:
    add r1, r1, #0x100
MobiClip_Code_02091924:
    ldrh r3, [r0, #-2]
MobiClip_Code_02091928:
    ldm r0, {r4, r5, r6}
MobiClip_Code_0209192C:
    ldrh lr, [r0, #0xc]
MobiClip_Code_02091930:
    add r0, r0, #0x100
MobiClip_Code_02091934:
    add r3, r3, r4, lsl #16
MobiClip_Code_02091938:
    lsr r4, r4, #0x10
MobiClip_Code_0209193C:
    add r4, r4, r5, lsl #16
MobiClip_Code_02091940:
    lsr r5, r5, #0x10
MobiClip_Code_02091944:
    add r5, r5, r6, lsl #16
MobiClip_Code_02091948:
    lsr r6, r6, #0x10
MobiClip_Code_0209194C:
    add r6, r6, lr, lsl #16
MobiClip_Code_02091950:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091954:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091958:
    and r5, ip, r5, lsr #1
MobiClip_Code_0209195C:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091960:
    add r7, r7, r3
MobiClip_Code_02091964:
    add r8, r8, r4
MobiClip_Code_02091968:
    add sb, sb, r5
MobiClip_Code_0209196C:
    add sl, sl, r6
MobiClip_Code_02091970:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_02091974:
    add r1, r1, #0x100
MobiClip_Code_02091978:
    subs r2, r2, #2
MobiClip_Code_0209197C:
    bne MobiClip_Code_020918D0
MobiClip_Code_02091980:
    pop {r5, r6, pc}
MobiClip_Code_02091984:
    ldr ip, [pc, #0x4c0]
MobiClip_Code_02091988:
    add r0, r0, #2
MobiClip_Code_0209198C:
    ldrh r3, [r0, #-2]
MobiClip_Code_02091990:
    ldm r0, {r4, r7, r8, sb}
MobiClip_Code_02091994:
    add r0, r0, #0x100
MobiClip_Code_02091998:
    and r3, ip, r3, lsr #1
MobiClip_Code_0209199C:
    and r4, ip, r4, lsr #1
MobiClip_Code_020919A0:
    and r7, ip, r7, lsr #1
MobiClip_Code_020919A4:
    and r8, ip, r8, lsr #1
MobiClip_Code_020919A8:
    and sb, ip, sb, lsr #1
MobiClip_Code_020919AC:
    add sl, r3, r4, lsl #16
MobiClip_Code_020919B0:
    add sl, sl, r3, lsr #8
MobiClip_Code_020919B4:
    add r3, sl, r4, lsl #8
MobiClip_Code_020919B8:
    lsr r4, r4, #0x10
MobiClip_Code_020919BC:
    add sl, r4, r7, lsl #16
MobiClip_Code_020919C0:
    add sl, sl, r4, lsr #8
MobiClip_Code_020919C4:
    add r4, sl, r7, lsl #8
MobiClip_Code_020919C8:
    lsr r7, r7, #0x10
MobiClip_Code_020919CC:
    add sl, r7, r8, lsl #16
MobiClip_Code_020919D0:
    add sl, sl, r7, lsr #8
MobiClip_Code_020919D4:
    add r7, sl, r8, lsl #8
MobiClip_Code_020919D8:
    lsr r8, r8, #0x10
MobiClip_Code_020919DC:
    add sl, r8, sb, lsl #16
MobiClip_Code_020919E0:
    add sl, sl, r8, lsr #8
MobiClip_Code_020919E4:
    add r8, sl, sb, lsl #8
MobiClip_Code_020919E8:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_020919EC:
    add r1, r1, #0x100
MobiClip_Code_020919F0:
    subs r2, r2, #1
MobiClip_Code_020919F4:
    bne MobiClip_Code_0209198C
MobiClip_Code_020919F8:
    mov pc, lr
MobiClip_Code_020919FC:
    push {r5, r6, fp, lr}
MobiClip_Code_02091A00:
    ldr ip, [pc, #0x444]
MobiClip_Code_02091A04:
    add r0, r0, #2
MobiClip_Code_02091A08:
    ldrh r3, [r0, #-2]
MobiClip_Code_02091A0C:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_02091A10:
    add r0, r0, #0x100
MobiClip_Code_02091A14:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091A18:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091A1C:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091A20:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091A24:
    and lr, ip, lr, lsr #1
MobiClip_Code_02091A28:
    add fp, r3, r4, lsl #16
MobiClip_Code_02091A2C:
    add fp, fp, r3, lsr #8
MobiClip_Code_02091A30:
    add r3, fp, r4, lsl #8
MobiClip_Code_02091A34:
    lsr r4, r4, #0x10
MobiClip_Code_02091A38:
    add fp, r4, r5, lsl #16
MobiClip_Code_02091A3C:
    add fp, fp, r4, lsr #8
MobiClip_Code_02091A40:
    add r4, fp, r5, lsl #8
MobiClip_Code_02091A44:
    lsr r5, r5, #0x10
MobiClip_Code_02091A48:
    add fp, r5, r6, lsl #16
MobiClip_Code_02091A4C:
    add fp, fp, r5, lsr #8
MobiClip_Code_02091A50:
    add r5, fp, r6, lsl #8
MobiClip_Code_02091A54:
    lsr r6, r6, #0x10
MobiClip_Code_02091A58:
    add fp, r6, lr, lsl #16
MobiClip_Code_02091A5C:
    add fp, fp, r6, lsr #8
MobiClip_Code_02091A60:
    add r6, fp, lr, lsl #8
MobiClip_Code_02091A64:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091A68:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091A6C:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091A70:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091A74:
    ldrh r7, [r0, #-2]
MobiClip_Code_02091A78:
    ldm r0, {r8, sb, sl, lr}
MobiClip_Code_02091A7C:
    add r0, r0, #0x100
MobiClip_Code_02091A80:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091A84:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091A88:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091A8C:
    and sl, ip, sl, lsr #1
MobiClip_Code_02091A90:
    and lr, ip, lr, lsr #1
MobiClip_Code_02091A94:
    add fp, r7, r8, lsl #16
MobiClip_Code_02091A98:
    add fp, fp, r7, lsr #8
MobiClip_Code_02091A9C:
    add r7, fp, r8, lsl #8
MobiClip_Code_02091AA0:
    lsr r8, r8, #0x10
MobiClip_Code_02091AA4:
    add fp, r8, sb, lsl #16
MobiClip_Code_02091AA8:
    add fp, fp, r8, lsr #8
MobiClip_Code_02091AAC:
    add r8, fp, sb, lsl #8
MobiClip_Code_02091AB0:
    lsr sb, sb, #0x10
MobiClip_Code_02091AB4:
    add fp, sb, sl, lsl #16
MobiClip_Code_02091AB8:
    add fp, fp, sb, lsr #8
MobiClip_Code_02091ABC:
    add sb, fp, sl, lsl #8
MobiClip_Code_02091AC0:
    lsr sl, sl, #0x10
MobiClip_Code_02091AC4:
    add fp, sl, lr, lsl #16
MobiClip_Code_02091AC8:
    add fp, fp, sl, lsr #8
MobiClip_Code_02091ACC:
    add sl, fp, lr, lsl #8
MobiClip_Code_02091AD0:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091AD4:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091AD8:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091ADC:
    and sl, ip, sl, lsr #1
MobiClip_Code_02091AE0:
    add r3, r3, r7
MobiClip_Code_02091AE4:
    add r4, r4, r8
MobiClip_Code_02091AE8:
    add r5, r5, sb
MobiClip_Code_02091AEC:
    add r6, r6, sl
MobiClip_Code_02091AF0:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_02091AF4:
    add r1, r1, #0x100
MobiClip_Code_02091AF8:
    ldrh r3, [r0, #-2]
MobiClip_Code_02091AFC:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_02091B00:
    add r0, r0, #0x100
MobiClip_Code_02091B04:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091B08:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091B0C:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091B10:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091B14:
    and lr, ip, lr, lsr #1
MobiClip_Code_02091B18:
    add fp, r3, r4, lsl #16
MobiClip_Code_02091B1C:
    add fp, fp, r3, lsr #8
MobiClip_Code_02091B20:
    add r3, fp, r4, lsl #8
MobiClip_Code_02091B24:
    lsr r4, r4, #0x10
MobiClip_Code_02091B28:
    add fp, r4, r5, lsl #16
MobiClip_Code_02091B2C:
    add fp, fp, r4, lsr #8
MobiClip_Code_02091B30:
    add r4, fp, r5, lsl #8
MobiClip_Code_02091B34:
    lsr r5, r5, #0x10
MobiClip_Code_02091B38:
    add fp, r5, r6, lsl #16
MobiClip_Code_02091B3C:
    add fp, fp, r5, lsr #8
MobiClip_Code_02091B40:
    add r5, fp, r6, lsl #8
MobiClip_Code_02091B44:
    lsr r6, r6, #0x10
MobiClip_Code_02091B48:
    add fp, r6, lr, lsl #16
MobiClip_Code_02091B4C:
    add fp, fp, r6, lsr #8
MobiClip_Code_02091B50:
    add r6, fp, lr, lsl #8
MobiClip_Code_02091B54:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091B58:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091B5C:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091B60:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091B64:
    add r7, r7, r3
MobiClip_Code_02091B68:
    add r8, r8, r4
MobiClip_Code_02091B6C:
    add sb, sb, r5
MobiClip_Code_02091B70:
    add sl, sl, r6
MobiClip_Code_02091B74:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_02091B78:
    add r1, r1, #0x100
MobiClip_Code_02091B7C:
    subs r2, r2, #2
MobiClip_Code_02091B80:
    bne MobiClip_Code_02091A74
MobiClip_Code_02091B84:
    pop {r5, r6, fp, pc}
MobiClip_Code_02091B88:
    add r0, r0, #1
MobiClip_Code_02091B8C:
    ldrb r3, [r0, #-1]
MobiClip_Code_02091B90:
    ldm r0, {r4, r7, r8, sb}
MobiClip_Code_02091B94:
    add r0, r0, #0x100
MobiClip_Code_02091B98:
    add r3, r3, r4, lsl #8
MobiClip_Code_02091B9C:
    lsr r4, r4, #0x18
MobiClip_Code_02091BA0:
    add r4, r4, r7, lsl #8
MobiClip_Code_02091BA4:
    lsr r7, r7, #0x18
MobiClip_Code_02091BA8:
    add r7, r7, r8, lsl #8
MobiClip_Code_02091BAC:
    lsr r8, r8, #0x18
MobiClip_Code_02091BB0:
    add r8, r8, sb, lsl #8
MobiClip_Code_02091BB4:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_02091BB8:
    add r1, r1, #0x100
MobiClip_Code_02091BBC:
    subs r2, r2, #1
MobiClip_Code_02091BC0:
    bne MobiClip_Code_02091B8C
MobiClip_Code_02091BC4:
    mov pc, lr
MobiClip_Code_02091BC8:
    push {r5, r6, lr}
MobiClip_Code_02091BCC:
    ldr ip, [pc, #0x278]
MobiClip_Code_02091BD0:
    add r0, r0, #1
MobiClip_Code_02091BD4:
    ldrb r3, [r0, #-1]
MobiClip_Code_02091BD8:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_02091BDC:
    add r0, r0, #0x100
MobiClip_Code_02091BE0:
    add r3, r3, r4, lsl #8
MobiClip_Code_02091BE4:
    lsr r4, r4, #0x18
MobiClip_Code_02091BE8:
    add r4, r4, r5, lsl #8
MobiClip_Code_02091BEC:
    lsr r5, r5, #0x18
MobiClip_Code_02091BF0:
    add r5, r5, r6, lsl #8
MobiClip_Code_02091BF4:
    lsr r6, r6, #0x18
MobiClip_Code_02091BF8:
    add r6, r6, lr, lsl #8
MobiClip_Code_02091BFC:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091C00:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091C04:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091C08:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091C0C:
    ldrb r7, [r0, #-1]
MobiClip_Code_02091C10:
    ldm r0, {r8, sb, sl, lr}
MobiClip_Code_02091C14:
    add r0, r0, #0x100
MobiClip_Code_02091C18:
    add r7, r7, r8, lsl #8
MobiClip_Code_02091C1C:
    lsr r8, r8, #0x18
MobiClip_Code_02091C20:
    add r8, r8, sb, lsl #8
MobiClip_Code_02091C24:
    lsr sb, sb, #0x18
MobiClip_Code_02091C28:
    add sb, sb, sl, lsl #8
MobiClip_Code_02091C2C:
    lsr sl, sl, #0x18
MobiClip_Code_02091C30:
    add sl, sl, lr, lsl #8
MobiClip_Code_02091C34:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091C38:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091C3C:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091C40:
    and sl, ip, sl, lsr #1
MobiClip_Code_02091C44:
    add r3, r3, r7
MobiClip_Code_02091C48:
    add r4, r4, r8
MobiClip_Code_02091C4C:
    add r5, r5, sb
MobiClip_Code_02091C50:
    add r6, r6, sl
MobiClip_Code_02091C54:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_02091C58:
    add r1, r1, #0x100
MobiClip_Code_02091C5C:
    ldrb r3, [r0, #-1]
MobiClip_Code_02091C60:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_02091C64:
    add r0, r0, #0x100
MobiClip_Code_02091C68:
    add r3, r3, r4, lsl #8
MobiClip_Code_02091C6C:
    lsr r4, r4, #0x18
MobiClip_Code_02091C70:
    add r4, r4, r5, lsl #8
MobiClip_Code_02091C74:
    lsr r5, r5, #0x18
MobiClip_Code_02091C78:
    add r5, r5, r6, lsl #8
MobiClip_Code_02091C7C:
    lsr r6, r6, #0x18
MobiClip_Code_02091C80:
    add r6, r6, lr, lsl #8
MobiClip_Code_02091C84:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091C88:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091C8C:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091C90:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091C94:
    add r7, r7, r3
MobiClip_Code_02091C98:
    add r8, r8, r4
MobiClip_Code_02091C9C:
    add sb, sb, r5
MobiClip_Code_02091CA0:
    add sl, sl, r6
MobiClip_Code_02091CA4:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_02091CA8:
    add r1, r1, #0x100
MobiClip_Code_02091CAC:
    subs r2, r2, #2
MobiClip_Code_02091CB0:
    bne MobiClip_Code_02091C0C
MobiClip_Code_02091CB4:
    pop {r5, r6, pc}
MobiClip_Code_02091CB8:
    ldr ip, [pc, #0x18c]
MobiClip_Code_02091CBC:
    add r0, r0, #1
MobiClip_Code_02091CC0:
    ldrb r3, [r0, #-1]
MobiClip_Code_02091CC4:
    ldm r0, {r4, r7, r8, sb}
MobiClip_Code_02091CC8:
    add r0, r0, #0x100
MobiClip_Code_02091CCC:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091CD0:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091CD4:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091CD8:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091CDC:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091CE0:
    add r3, r3, r4, lsl #8
MobiClip_Code_02091CE4:
    add r3, r3, r4
MobiClip_Code_02091CE8:
    add r4, r7, r4, lsr #24
MobiClip_Code_02091CEC:
    add r4, r4, r7, lsl #8
MobiClip_Code_02091CF0:
    add r7, r8, r7, lsr #24
MobiClip_Code_02091CF4:
    add r7, r7, r8, lsl #8
MobiClip_Code_02091CF8:
    add r8, sb, r8, lsr #24
MobiClip_Code_02091CFC:
    add r8, r8, sb, lsl #8
MobiClip_Code_02091D00:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_02091D04:
    add r1, r1, #0x100
MobiClip_Code_02091D08:
    subs r2, r2, #1
MobiClip_Code_02091D0C:
    bne MobiClip_Code_02091CC0
MobiClip_Code_02091D10:
    mov pc, lr
MobiClip_Code_02091D14:
    push {r5, r6, lr}
MobiClip_Code_02091D18:
    ldr ip, [pc, #0x12c]
MobiClip_Code_02091D1C:
    add r0, r0, #1
MobiClip_Code_02091D20:
    ldrb r3, [r0, #-1]
MobiClip_Code_02091D24:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_02091D28:
    add r0, r0, #0x100
MobiClip_Code_02091D2C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091D30:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091D34:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091D38:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091D3C:
    and lr, ip, lr, lsr #1
MobiClip_Code_02091D40:
    add r3, r3, r4, lsl #8
MobiClip_Code_02091D44:
    add r3, r3, r4
MobiClip_Code_02091D48:
    add r4, r5, r4, lsr #24
MobiClip_Code_02091D4C:
    add r4, r4, r5, lsl #8
MobiClip_Code_02091D50:
    add r5, r6, r5, lsr #24
MobiClip_Code_02091D54:
    add r5, r5, r6, lsl #8
MobiClip_Code_02091D58:
    add r6, lr, r6, lsr #24
MobiClip_Code_02091D5C:
    add r6, r6, lr, lsl #8
MobiClip_Code_02091D60:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091D64:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091D68:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091D6C:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091D70:
    ldrb r7, [r0, #-1]
MobiClip_Code_02091D74:
    ldm r0, {r8, sb, sl, lr}
MobiClip_Code_02091D78:
    add r0, r0, #0x100
MobiClip_Code_02091D7C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091D80:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091D84:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091D88:
    and sl, ip, sl, lsr #1
MobiClip_Code_02091D8C:
    and lr, ip, lr, lsr #1
MobiClip_Code_02091D90:
    add r7, r7, r8, lsl #8
MobiClip_Code_02091D94:
    add r7, r7, r8
MobiClip_Code_02091D98:
    add r8, sb, r8, lsr #24
MobiClip_Code_02091D9C:
    add r8, r8, sb, lsl #8
MobiClip_Code_02091DA0:
    add sb, sl, sb, lsr #24
MobiClip_Code_02091DA4:
    add sb, sb, sl, lsl #8
MobiClip_Code_02091DA8:
    add sl, lr, sl, lsr #24
MobiClip_Code_02091DAC:
    add sl, sl, lr, lsl #8
MobiClip_Code_02091DB0:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091DB4:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091DB8:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091DBC:
    and sl, ip, sl, lsr #1
MobiClip_Code_02091DC0:
    add r3, r3, r7
MobiClip_Code_02091DC4:
    add r4, r4, r8
MobiClip_Code_02091DC8:
    add r5, r5, sb
MobiClip_Code_02091DCC:
    add r6, r6, sl
MobiClip_Code_02091DD0:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_02091DD4:
    add r1, r1, #0x100
MobiClip_Code_02091DD8:
    ldrb r3, [r0, #-1]
MobiClip_Code_02091DDC:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_02091DE0:
    add r0, r0, #0x100
MobiClip_Code_02091DE4:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091DE8:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091DEC:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091DF0:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091DF4:
    and lr, ip, lr, lsr #1
MobiClip_Code_02091DF8:
    add r3, r3, r4, lsl #8
MobiClip_Code_02091DFC:
    add r3, r3, r4
MobiClip_Code_02091E00:
    add r4, r5, r4, lsr #24
MobiClip_Code_02091E04:
    add r4, r4, r5, lsl #8
MobiClip_Code_02091E08:
    add r5, r6, r5, lsr #24
MobiClip_Code_02091E0C:
    add r5, r5, r6, lsl #8
MobiClip_Code_02091E10:
    add r6, lr, r6, lsr #24
MobiClip_Code_02091E14:
    add r6, r6, lr, lsl #8
MobiClip_Code_02091E18:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091E1C:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091E20:
    and r5, ip, r5, lsr #1
MobiClip_Code_02091E24:
    and r6, ip, r6, lsr #1
MobiClip_Code_02091E28:
    add r7, r7, r3
MobiClip_Code_02091E2C:
    add r8, r8, r4
MobiClip_Code_02091E30:
    add sb, sb, r5
MobiClip_Code_02091E34:
    add sl, sl, r6
MobiClip_Code_02091E38:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_02091E3C:
    add r1, r1, #0x100
MobiClip_Code_02091E40:
    subs r2, r2, #2
MobiClip_Code_02091E44:
    bne MobiClip_Code_02091D70
MobiClip_Code_02091E48:
    pop {r5, r6, pc}
    /* semantic constants 0x02091e4c..0x02091e50 */
    .global gMobiClipPackedAverageLaneMask
    .type gMobiClipPackedAverageLaneMask, %object
gMobiClipPackedAverageLaneMask:
    .byte 0x7f, 0x7f, 0x7f, 0x7f
    .size gMobiClipPackedAverageLaneMask, . - gMobiClipPackedAverageLaneMask
MobiClip_Code_02091E50:
    ldm r0, {r3, r4}
MobiClip_Code_02091E54:
    add r0, r0, #0x100
MobiClip_Code_02091E58:
    stm r1, {r3, r4}
MobiClip_Code_02091E5C:
    add r1, r1, #0x100
MobiClip_Code_02091E60:
    subs r2, r2, #1
MobiClip_Code_02091E64:
    bne MobiClip_Code_02091E50
MobiClip_Code_02091E68:
    mov pc, lr
MobiClip_Code_02091E6C:
    ldr ip, [pc, #0x784]
MobiClip_Code_02091E70:
    ldm r0, {r3, r4}
MobiClip_Code_02091E74:
    add r0, r0, #0x100
MobiClip_Code_02091E78:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091E7C:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091E80:
    ldm r0, {r7, r8}
MobiClip_Code_02091E84:
    add r0, r0, #0x100
MobiClip_Code_02091E88:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091E8C:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091E90:
    add r3, r3, r7
MobiClip_Code_02091E94:
    add r4, r4, r8
MobiClip_Code_02091E98:
    stm r1, {r3, r4}
MobiClip_Code_02091E9C:
    add r1, r1, #0x100
MobiClip_Code_02091EA0:
    subs r2, r2, #1
MobiClip_Code_02091EA4:
    moveq pc, lr
MobiClip_Code_02091EA8:
    ldm r0, {r3, r4}
MobiClip_Code_02091EAC:
    add r0, r0, #0x100
MobiClip_Code_02091EB0:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091EB4:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091EB8:
    add r7, r7, r3
MobiClip_Code_02091EBC:
    add r8, r8, r4
MobiClip_Code_02091EC0:
    stm r1, {r7, r8}
MobiClip_Code_02091EC4:
    add r1, r1, #0x100
MobiClip_Code_02091EC8:
    subs r2, r2, #1
MobiClip_Code_02091ECC:
    bne MobiClip_Code_02091E80
MobiClip_Code_02091ED0:
    mov pc, lr
MobiClip_Code_02091ED4:
    ldr ip, [pc, #0x71c]
MobiClip_Code_02091ED8:
    ldm r0, {r3, r4}
MobiClip_Code_02091EDC:
    ldrb sb, [r0, #8]
MobiClip_Code_02091EE0:
    add r0, r0, #0x100
MobiClip_Code_02091EE4:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091EE8:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091EEC:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091EF0:
    add r3, r3, r3, lsr #8
MobiClip_Code_02091EF4:
    add r3, r3, r4, lsl #24
MobiClip_Code_02091EF8:
    add r4, r4, r4, lsr #8
MobiClip_Code_02091EFC:
    add r4, r4, sb, lsl #24
MobiClip_Code_02091F00:
    stm r1, {r3, r4}
MobiClip_Code_02091F04:
    add r1, r1, #0x100
MobiClip_Code_02091F08:
    subs r2, r2, #1
MobiClip_Code_02091F0C:
    bne MobiClip_Code_02091ED8
MobiClip_Code_02091F10:
    mov pc, lr
MobiClip_Code_02091F14:
    ldr ip, [pc, #0x6dc]
MobiClip_Code_02091F18:
    ldm r0, {r3, r4}
MobiClip_Code_02091F1C:
    ldrb sb, [r0, #8]
MobiClip_Code_02091F20:
    add r0, r0, #0x100
MobiClip_Code_02091F24:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091F28:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091F2C:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091F30:
    add r3, r3, r3, lsr #8
MobiClip_Code_02091F34:
    add r3, r3, r4, lsl #24
MobiClip_Code_02091F38:
    add r4, r4, r4, lsr #8
MobiClip_Code_02091F3C:
    add r4, r4, sb, lsl #24
MobiClip_Code_02091F40:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091F44:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091F48:
    ldm r0, {r7, r8}
MobiClip_Code_02091F4C:
    ldrb sb, [r0, #8]
MobiClip_Code_02091F50:
    add r0, r0, #0x100
MobiClip_Code_02091F54:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091F58:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091F5C:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091F60:
    add r7, r7, r7, lsr #8
MobiClip_Code_02091F64:
    add r7, r7, r8, lsl #24
MobiClip_Code_02091F68:
    add r8, r8, r8, lsr #8
MobiClip_Code_02091F6C:
    add r8, r8, sb, lsl #24
MobiClip_Code_02091F70:
    and r7, ip, r7, lsr #1
MobiClip_Code_02091F74:
    and r8, ip, r8, lsr #1
MobiClip_Code_02091F78:
    add r3, r3, r7
MobiClip_Code_02091F7C:
    add r4, r4, r8
MobiClip_Code_02091F80:
    stm r1, {r3, r4}
MobiClip_Code_02091F84:
    add r1, r1, #0x100
MobiClip_Code_02091F88:
    subs r2, r2, #1
MobiClip_Code_02091F8C:
    moveq pc, lr
MobiClip_Code_02091F90:
    ldm r0, {r3, r4}
MobiClip_Code_02091F94:
    ldrb sb, [r0, #8]
MobiClip_Code_02091F98:
    add r0, r0, #0x100
MobiClip_Code_02091F9C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091FA0:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091FA4:
    and sb, ip, sb, lsr #1
MobiClip_Code_02091FA8:
    add r3, r3, r3, lsr #8
MobiClip_Code_02091FAC:
    add r3, r3, r4, lsl #24
MobiClip_Code_02091FB0:
    add r4, r4, r4, lsr #8
MobiClip_Code_02091FB4:
    add r4, r4, sb, lsl #24
MobiClip_Code_02091FB8:
    and r3, ip, r3, lsr #1
MobiClip_Code_02091FBC:
    and r4, ip, r4, lsr #1
MobiClip_Code_02091FC0:
    add r7, r7, r3
MobiClip_Code_02091FC4:
    add r8, r8, r4
MobiClip_Code_02091FC8:
    stm r1, {r7, r8}
MobiClip_Code_02091FCC:
    add r1, r1, #0x100
MobiClip_Code_02091FD0:
    subs r2, r2, #1
MobiClip_Code_02091FD4:
    bne MobiClip_Code_02091F48
MobiClip_Code_02091FD8:
    mov pc, lr
MobiClip_Code_02091FDC:
    sub r0, r0, #1
MobiClip_Code_02091FE0:
    ldm r0, {r3, r4}
MobiClip_Code_02091FE4:
    ldrb sb, [r0, #8]
MobiClip_Code_02091FE8:
    add r0, r0, #0x100
MobiClip_Code_02091FEC:
    lsr r3, r3, #8
MobiClip_Code_02091FF0:
    add r3, r3, r4, lsl #24
MobiClip_Code_02091FF4:
    lsr r4, r4, #8
MobiClip_Code_02091FF8:
    add r4, r4, sb, lsl #24
MobiClip_Code_02091FFC:
    stm r1, {r3, r4}
MobiClip_Code_02092000:
    add r1, r1, #0x100
MobiClip_Code_02092004:
    subs r2, r2, #1
MobiClip_Code_02092008:
    bne MobiClip_Code_02091FE0
MobiClip_Code_0209200C:
    mov pc, lr
MobiClip_Code_02092010:
    sub r0, r0, #1
MobiClip_Code_02092014:
    ldr ip, [pc, #0x5dc]
MobiClip_Code_02092018:
    ldm r0, {r3, r4}
MobiClip_Code_0209201C:
    ldrb sb, [r0, #8]
MobiClip_Code_02092020:
    add r0, r0, #0x100
MobiClip_Code_02092024:
    lsr r3, r3, #8
MobiClip_Code_02092028:
    add r3, r3, r4, lsl #24
MobiClip_Code_0209202C:
    lsr r4, r4, #8
MobiClip_Code_02092030:
    add r4, r4, sb, lsl #24
MobiClip_Code_02092034:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092038:
    and r4, ip, r4, lsr #1
MobiClip_Code_0209203C:
    ldm r0, {r7, r8}
MobiClip_Code_02092040:
    ldrb sb, [r0, #8]
MobiClip_Code_02092044:
    add r0, r0, #0x100
MobiClip_Code_02092048:
    lsr r7, r7, #8
MobiClip_Code_0209204C:
    add r7, r7, r8, lsl #24
MobiClip_Code_02092050:
    lsr r8, r8, #8
MobiClip_Code_02092054:
    add r8, r8, sb, lsl #24
MobiClip_Code_02092058:
    and r7, ip, r7, lsr #1
MobiClip_Code_0209205C:
    and r8, ip, r8, lsr #1
MobiClip_Code_02092060:
    add r3, r3, r7
MobiClip_Code_02092064:
    add r4, r4, r8
MobiClip_Code_02092068:
    stm r1, {r3, r4}
MobiClip_Code_0209206C:
    add r1, r1, #0x100
MobiClip_Code_02092070:
    subs r2, r2, #1
MobiClip_Code_02092074:
    moveq pc, lr
MobiClip_Code_02092078:
    ldm r0, {r3, r4}
MobiClip_Code_0209207C:
    ldrb sb, [r0, #8]
MobiClip_Code_02092080:
    add r0, r0, #0x100
MobiClip_Code_02092084:
    lsr r3, r3, #8
MobiClip_Code_02092088:
    add r3, r3, r4, lsl #24
MobiClip_Code_0209208C:
    lsr r4, r4, #8
MobiClip_Code_02092090:
    add r4, r4, sb, lsl #24
MobiClip_Code_02092094:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092098:
    and r4, ip, r4, lsr #1
MobiClip_Code_0209209C:
    add r7, r7, r3
MobiClip_Code_020920A0:
    add r8, r8, r4
MobiClip_Code_020920A4:
    stm r1, {r7, r8}
MobiClip_Code_020920A8:
    add r1, r1, #0x100
MobiClip_Code_020920AC:
    subs r2, r2, #1
MobiClip_Code_020920B0:
    bne MobiClip_Code_0209203C
MobiClip_Code_020920B4:
    mov pc, lr
MobiClip_Code_020920B8:
    ldr ip, [pc, #0x538]
MobiClip_Code_020920BC:
    sub r0, r0, #1
MobiClip_Code_020920C0:
    ldm r0, {r3, r4}
MobiClip_Code_020920C4:
    ldrh sb, [r0, #8]
MobiClip_Code_020920C8:
    add r0, r0, #0x100
MobiClip_Code_020920CC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020920D0:
    and r4, ip, r4, lsr #1
MobiClip_Code_020920D4:
    and sb, ip, sb, lsr #1
MobiClip_Code_020920D8:
    lsr sl, r3, #0x10
MobiClip_Code_020920DC:
    add sl, sl, r4, lsl #16
MobiClip_Code_020920E0:
    add sl, sl, r3, lsr #8
MobiClip_Code_020920E4:
    add r3, sl, r4, lsl #24
MobiClip_Code_020920E8:
    lsr sl, r4, #0x10
MobiClip_Code_020920EC:
    add sl, sl, sb, lsl #16
MobiClip_Code_020920F0:
    add sl, sl, r4, lsr #8
MobiClip_Code_020920F4:
    add r4, sl, sb, lsl #24
MobiClip_Code_020920F8:
    stm r1, {r3, r4}
MobiClip_Code_020920FC:
    add r1, r1, #0x100
MobiClip_Code_02092100:
    subs r2, r2, #1
MobiClip_Code_02092104:
    bne MobiClip_Code_020920C0
MobiClip_Code_02092108:
    mov pc, lr
MobiClip_Code_0209210C:
    ldr ip, [pc, #0x4e4]
MobiClip_Code_02092110:
    sub r0, r0, #1
MobiClip_Code_02092114:
    ldm r0, {r3, r4}
MobiClip_Code_02092118:
    ldrh sb, [r0, #8]
MobiClip_Code_0209211C:
    add r0, r0, #0x100
MobiClip_Code_02092120:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092124:
    and r4, ip, r4, lsr #1
MobiClip_Code_02092128:
    and sb, ip, sb, lsr #1
MobiClip_Code_0209212C:
    lsr sl, r3, #0x10
MobiClip_Code_02092130:
    add sl, sl, r4, lsl #16
MobiClip_Code_02092134:
    add sl, sl, r3, lsr #8
MobiClip_Code_02092138:
    add r3, sl, r4, lsl #24
MobiClip_Code_0209213C:
    lsr sl, r4, #0x10
MobiClip_Code_02092140:
    add sl, sl, sb, lsl #16
MobiClip_Code_02092144:
    add sl, sl, r4, lsr #8
MobiClip_Code_02092148:
    add r4, sl, sb, lsl #24
MobiClip_Code_0209214C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092150:
    and r4, ip, r4, lsr #1
MobiClip_Code_02092154:
    ldm r0, {r7, r8}
MobiClip_Code_02092158:
    ldrh sb, [r0, #8]
MobiClip_Code_0209215C:
    add r0, r0, #0x100
MobiClip_Code_02092160:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092164:
    and r8, ip, r8, lsr #1
MobiClip_Code_02092168:
    and sb, ip, sb, lsr #1
MobiClip_Code_0209216C:
    lsr sl, r7, #0x10
MobiClip_Code_02092170:
    add sl, sl, r8, lsl #16
MobiClip_Code_02092174:
    add sl, sl, r7, lsr #8
MobiClip_Code_02092178:
    add r7, sl, r8, lsl #24
MobiClip_Code_0209217C:
    lsr sl, r8, #0x10
MobiClip_Code_02092180:
    add sl, sl, sb, lsl #16
MobiClip_Code_02092184:
    add sl, sl, r8, lsr #8
MobiClip_Code_02092188:
    add r8, sl, sb, lsl #24
MobiClip_Code_0209218C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092190:
    and r8, ip, r8, lsr #1
MobiClip_Code_02092194:
    add r3, r3, r7
MobiClip_Code_02092198:
    add r4, r4, r8
MobiClip_Code_0209219C:
    stm r1, {r3, r4}
MobiClip_Code_020921A0:
    add r1, r1, #0x100
MobiClip_Code_020921A4:
    subs r2, r2, #1
MobiClip_Code_020921A8:
    moveq pc, lr
MobiClip_Code_020921AC:
    ldm r0, {r3, r4}
MobiClip_Code_020921B0:
    ldrh sb, [r0, #8]
MobiClip_Code_020921B4:
    add r0, r0, #0x100
MobiClip_Code_020921B8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020921BC:
    and r4, ip, r4, lsr #1
MobiClip_Code_020921C0:
    and sb, ip, sb, lsr #1
MobiClip_Code_020921C4:
    lsr sl, r3, #0x10
MobiClip_Code_020921C8:
    add sl, sl, r4, lsl #16
MobiClip_Code_020921CC:
    add sl, sl, r3, lsr #8
MobiClip_Code_020921D0:
    add r3, sl, r4, lsl #24
MobiClip_Code_020921D4:
    lsr sl, r4, #0x10
MobiClip_Code_020921D8:
    add sl, sl, sb, lsl #16
MobiClip_Code_020921DC:
    add sl, sl, r4, lsr #8
MobiClip_Code_020921E0:
    add r4, sl, sb, lsl #24
MobiClip_Code_020921E4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020921E8:
    and r4, ip, r4, lsr #1
MobiClip_Code_020921EC:
    add r7, r7, r3
MobiClip_Code_020921F0:
    add r8, r8, r4
MobiClip_Code_020921F4:
    stm r1, {r7, r8}
MobiClip_Code_020921F8:
    add r1, r1, #0x100
MobiClip_Code_020921FC:
    subs r2, r2, #1
MobiClip_Code_02092200:
    bne MobiClip_Code_02092154
MobiClip_Code_02092204:
    mov pc, lr
MobiClip_Code_02092208:
    ldrh r3, [r0], #2
MobiClip_Code_0209220C:
    ldr r4, [r0], #4
MobiClip_Code_02092210:
    ldrh sb, [r0], #-6
MobiClip_Code_02092214:
    add r0, r0, #0x100
MobiClip_Code_02092218:
    add r3, r3, r4, lsl #16
MobiClip_Code_0209221C:
    lsr r4, r4, #0x10
MobiClip_Code_02092220:
    add r4, r4, sb, lsl #16
MobiClip_Code_02092224:
    stm r1, {r3, r4}
MobiClip_Code_02092228:
    add r1, r1, #0x100
MobiClip_Code_0209222C:
    subs r2, r2, #1
MobiClip_Code_02092230:
    bne MobiClip_Code_02092208
MobiClip_Code_02092234:
    mov pc, lr
MobiClip_Code_02092238:
    ldr ip, [pc, #0x3b8]
MobiClip_Code_0209223C:
    ldrh r3, [r0], #2
MobiClip_Code_02092240:
    ldr r4, [r0], #4
MobiClip_Code_02092244:
    ldrh sb, [r0], #-6
MobiClip_Code_02092248:
    add r0, r0, #0x100
MobiClip_Code_0209224C:
    add r3, r3, r4, lsl #16
MobiClip_Code_02092250:
    lsr r4, r4, #0x10
MobiClip_Code_02092254:
    add r4, r4, sb, lsl #16
MobiClip_Code_02092258:
    and r3, ip, r3, lsr #1
MobiClip_Code_0209225C:
    and r4, ip, r4, lsr #1
MobiClip_Code_02092260:
    ldrh r7, [r0], #2
MobiClip_Code_02092264:
    ldr r8, [r0], #4
MobiClip_Code_02092268:
    ldrh sb, [r0], #-6
MobiClip_Code_0209226C:
    add r0, r0, #0x100
MobiClip_Code_02092270:
    add r7, r7, r8, lsl #16
MobiClip_Code_02092274:
    lsr r8, r8, #0x10
MobiClip_Code_02092278:
    add r8, r8, sb, lsl #16
MobiClip_Code_0209227C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092280:
    and r8, ip, r8, lsr #1
MobiClip_Code_02092284:
    add r3, r3, r7
MobiClip_Code_02092288:
    add r4, r4, r8
MobiClip_Code_0209228C:
    stm r1, {r3, r4}
MobiClip_Code_02092290:
    add r1, r1, #0x100
MobiClip_Code_02092294:
    subs r2, r2, #1
MobiClip_Code_02092298:
    moveq pc, lr
MobiClip_Code_0209229C:
    ldrh r3, [r0], #2
MobiClip_Code_020922A0:
    ldr r4, [r0], #4
MobiClip_Code_020922A4:
    ldrh sb, [r0], #-6
MobiClip_Code_020922A8:
    add r0, r0, #0x100
MobiClip_Code_020922AC:
    add r3, r3, r4, lsl #16
MobiClip_Code_020922B0:
    lsr r4, r4, #0x10
MobiClip_Code_020922B4:
    add r4, r4, sb, lsl #16
MobiClip_Code_020922B8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020922BC:
    and r4, ip, r4, lsr #1
MobiClip_Code_020922C0:
    add r7, r7, r3
MobiClip_Code_020922C4:
    add r8, r8, r4
MobiClip_Code_020922C8:
    stm r1, {r7, r8}
MobiClip_Code_020922CC:
    add r1, r1, #0x100
MobiClip_Code_020922D0:
    subs r2, r2, #1
MobiClip_Code_020922D4:
    bne MobiClip_Code_02092260
MobiClip_Code_020922D8:
    mov pc, lr
MobiClip_Code_020922DC:
    ldr ip, [pc, #0x314]
MobiClip_Code_020922E0:
    add r0, r0, #2
MobiClip_Code_020922E4:
    ldrh r3, [r0, #-2]
MobiClip_Code_020922E8:
    ldm r0, {r4, sb}
MobiClip_Code_020922EC:
    add r0, r0, #0x100
MobiClip_Code_020922F0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020922F4:
    and r4, ip, r4, lsr #1
MobiClip_Code_020922F8:
    and sb, ip, sb, lsr #1
MobiClip_Code_020922FC:
    add sl, r3, r4, lsl #16
MobiClip_Code_02092300:
    add sl, sl, r3, lsr #8
MobiClip_Code_02092304:
    add r3, sl, r4, lsl #8
MobiClip_Code_02092308:
    lsr r4, r4, #0x10
MobiClip_Code_0209230C:
    add sl, r4, sb, lsl #16
MobiClip_Code_02092310:
    add sl, sl, r4, lsr #8
MobiClip_Code_02092314:
    add r4, sl, sb, lsl #8
MobiClip_Code_02092318:
    stm r1, {r3, r4}
MobiClip_Code_0209231C:
    add r1, r1, #0x100
MobiClip_Code_02092320:
    subs r2, r2, #1
MobiClip_Code_02092324:
    bne MobiClip_Code_020922E4
MobiClip_Code_02092328:
    mov pc, lr
MobiClip_Code_0209232C:
    ldr ip, [pc, #0x2c4]
MobiClip_Code_02092330:
    add r0, r0, #2
MobiClip_Code_02092334:
    ldrh r3, [r0, #-2]
MobiClip_Code_02092338:
    ldm r0, {r4, sb}
MobiClip_Code_0209233C:
    add r0, r0, #0x100
MobiClip_Code_02092340:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092344:
    and r4, ip, r4, lsr #1
MobiClip_Code_02092348:
    and sb, ip, sb, lsr #1
MobiClip_Code_0209234C:
    add sl, r3, r4, lsl #16
MobiClip_Code_02092350:
    add sl, sl, r3, lsr #8
MobiClip_Code_02092354:
    add r3, sl, r4, lsl #8
MobiClip_Code_02092358:
    lsr r4, r4, #0x10
MobiClip_Code_0209235C:
    add sl, r4, sb, lsl #16
MobiClip_Code_02092360:
    add sl, sl, r4, lsr #8
MobiClip_Code_02092364:
    add r4, sl, sb, lsl #8
MobiClip_Code_02092368:
    and r3, ip, r3, lsr #1
MobiClip_Code_0209236C:
    and r4, ip, r4, lsr #1
MobiClip_Code_02092370:
    ldrh r7, [r0, #-2]
MobiClip_Code_02092374:
    ldm r0, {r8, sb}
MobiClip_Code_02092378:
    add r0, r0, #0x100
MobiClip_Code_0209237C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092380:
    and r8, ip, r8, lsr #1
MobiClip_Code_02092384:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092388:
    add sl, r7, r8, lsl #16
MobiClip_Code_0209238C:
    add sl, sl, r7, lsr #8
MobiClip_Code_02092390:
    add r7, sl, r8, lsl #8
MobiClip_Code_02092394:
    lsr r8, r8, #0x10
MobiClip_Code_02092398:
    add sl, r8, sb, lsl #16
MobiClip_Code_0209239C:
    add sl, sl, r8, lsr #8
MobiClip_Code_020923A0:
    add r8, sl, sb, lsl #8
MobiClip_Code_020923A4:
    and r7, ip, r7, lsr #1
MobiClip_Code_020923A8:
    and r8, ip, r8, lsr #1
MobiClip_Code_020923AC:
    add r3, r3, r7
MobiClip_Code_020923B0:
    add r4, r4, r8
MobiClip_Code_020923B4:
    stm r1, {r3, r4}
MobiClip_Code_020923B8:
    add r1, r1, #0x100
MobiClip_Code_020923BC:
    subs r2, r2, #1
MobiClip_Code_020923C0:
    moveq pc, lr
MobiClip_Code_020923C4:
    ldrh r3, [r0, #-2]
MobiClip_Code_020923C8:
    ldm r0, {r4, sb}
MobiClip_Code_020923CC:
    add r0, r0, #0x100
MobiClip_Code_020923D0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020923D4:
    and r4, ip, r4, lsr #1
MobiClip_Code_020923D8:
    and sb, ip, sb, lsr #1
MobiClip_Code_020923DC:
    add sl, r3, r4, lsl #16
MobiClip_Code_020923E0:
    add sl, sl, r3, lsr #8
MobiClip_Code_020923E4:
    add r3, sl, r4, lsl #8
MobiClip_Code_020923E8:
    lsr r4, r4, #0x10
MobiClip_Code_020923EC:
    add sl, r4, sb, lsl #16
MobiClip_Code_020923F0:
    add sl, sl, r4, lsr #8
MobiClip_Code_020923F4:
    add r4, sl, sb, lsl #8
MobiClip_Code_020923F8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020923FC:
    and r4, ip, r4, lsr #1
MobiClip_Code_02092400:
    add r7, r7, r3
MobiClip_Code_02092404:
    add r8, r8, r4
MobiClip_Code_02092408:
    stm r1, {r7, r8}
MobiClip_Code_0209240C:
    add r1, r1, #0x100
MobiClip_Code_02092410:
    subs r2, r2, #1
MobiClip_Code_02092414:
    bne MobiClip_Code_02092370
MobiClip_Code_02092418:
    mov pc, lr
MobiClip_Code_0209241C:
    add r0, r0, #1
MobiClip_Code_02092420:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092424:
    ldm r0, {r4, sb}
MobiClip_Code_02092428:
    add r0, r0, #0x100
MobiClip_Code_0209242C:
    add r3, r3, r4, lsl #8
MobiClip_Code_02092430:
    lsr r4, r4, #0x18
MobiClip_Code_02092434:
    add r4, r4, sb, lsl #8
MobiClip_Code_02092438:
    stm r1, {r3, r4}
MobiClip_Code_0209243C:
    add r1, r1, #0x100
MobiClip_Code_02092440:
    subs r2, r2, #1
MobiClip_Code_02092444:
    bne MobiClip_Code_02092420
MobiClip_Code_02092448:
    mov pc, lr
MobiClip_Code_0209244C:
    ldr ip, [pc, #0x1a4]
MobiClip_Code_02092450:
    add r0, r0, #1
MobiClip_Code_02092454:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092458:
    ldm r0, {r4, sb}
MobiClip_Code_0209245C:
    add r0, r0, #0x100
MobiClip_Code_02092460:
    add r3, r3, r4, lsl #8
MobiClip_Code_02092464:
    lsr r4, r4, #0x18
MobiClip_Code_02092468:
    add r4, r4, sb, lsl #8
MobiClip_Code_0209246C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092470:
    and r4, ip, r4, lsr #1
MobiClip_Code_02092474:
    ldrb r7, [r0, #-1]
MobiClip_Code_02092478:
    ldm r0, {r8, sb}
MobiClip_Code_0209247C:
    add r0, r0, #0x100
MobiClip_Code_02092480:
    add r7, r7, r8, lsl #8
MobiClip_Code_02092484:
    lsr r8, r8, #0x18
MobiClip_Code_02092488:
    add r8, r8, sb, lsl #8
MobiClip_Code_0209248C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092490:
    and r8, ip, r8, lsr #1
MobiClip_Code_02092494:
    add r3, r3, r7
MobiClip_Code_02092498:
    add r4, r4, r8
MobiClip_Code_0209249C:
    stm r1, {r3, r4}
MobiClip_Code_020924A0:
    add r1, r1, #0x100
MobiClip_Code_020924A4:
    subs r2, r2, #1
MobiClip_Code_020924A8:
    moveq pc, lr
MobiClip_Code_020924AC:
    ldrb r3, [r0, #-1]
MobiClip_Code_020924B0:
    ldm r0, {r4, sb}
MobiClip_Code_020924B4:
    add r0, r0, #0x100
MobiClip_Code_020924B8:
    add r3, r3, r4, lsl #8
MobiClip_Code_020924BC:
    lsr r4, r4, #0x18
MobiClip_Code_020924C0:
    add r4, r4, sb, lsl #8
MobiClip_Code_020924C4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020924C8:
    and r4, ip, r4, lsr #1
MobiClip_Code_020924CC:
    add r7, r7, r3
MobiClip_Code_020924D0:
    add r8, r8, r4
MobiClip_Code_020924D4:
    stm r1, {r7, r8}
MobiClip_Code_020924D8:
    add r1, r1, #0x100
MobiClip_Code_020924DC:
    subs r2, r2, #1
MobiClip_Code_020924E0:
    bne MobiClip_Code_02092474
MobiClip_Code_020924E4:
    mov pc, lr
MobiClip_Code_020924E8:
    ldr ip, [pc, #0x108]
MobiClip_Code_020924EC:
    add r0, r0, #1
MobiClip_Code_020924F0:
    ldrb r3, [r0, #-1]
MobiClip_Code_020924F4:
    ldm r0, {r4, sb}
MobiClip_Code_020924F8:
    add r0, r0, #0x100
MobiClip_Code_020924FC:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092500:
    and r4, ip, r4, lsr #1
MobiClip_Code_02092504:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092508:
    add r3, r3, r4, lsl #8
MobiClip_Code_0209250C:
    add r3, r3, r4
MobiClip_Code_02092510:
    add r4, sb, r4, lsr #24
MobiClip_Code_02092514:
    add r4, r4, sb, lsl #8
MobiClip_Code_02092518:
    stm r1, {r3, r4}
MobiClip_Code_0209251C:
    add r1, r1, #0x100
MobiClip_Code_02092520:
    subs r2, r2, #1
MobiClip_Code_02092524:
    bne MobiClip_Code_020924F0
MobiClip_Code_02092528:
    mov pc, lr
MobiClip_Code_0209252C:
    ldr ip, [pc, #0xc4]
MobiClip_Code_02092530:
    add r0, r0, #1
MobiClip_Code_02092534:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092538:
    ldm r0, {r4, sb}
MobiClip_Code_0209253C:
    add r0, r0, #0x100
MobiClip_Code_02092540:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092544:
    and r4, ip, r4, lsr #1
MobiClip_Code_02092548:
    and sb, ip, sb, lsr #1
MobiClip_Code_0209254C:
    add r3, r3, r4, lsl #8
MobiClip_Code_02092550:
    add r3, r3, r4
MobiClip_Code_02092554:
    add r4, sb, r4, lsr #24
MobiClip_Code_02092558:
    add r4, r4, sb, lsl #8
MobiClip_Code_0209255C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092560:
    and r4, ip, r4, lsr #1
MobiClip_Code_02092564:
    ldrb r7, [r0, #-1]
MobiClip_Code_02092568:
    ldm r0, {r8, sb}
MobiClip_Code_0209256C:
    add r0, r0, #0x100
MobiClip_Code_02092570:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092574:
    and r8, ip, r8, lsr #1
MobiClip_Code_02092578:
    and sb, ip, sb, lsr #1
MobiClip_Code_0209257C:
    add r7, r7, r8, lsl #8
MobiClip_Code_02092580:
    add r7, r7, r8
MobiClip_Code_02092584:
    add r8, sb, r8, lsr #24
MobiClip_Code_02092588:
    add r8, r8, sb, lsl #8
MobiClip_Code_0209258C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092590:
    and r8, ip, r8, lsr #1
MobiClip_Code_02092594:
    add r3, r3, r7
MobiClip_Code_02092598:
    add r4, r4, r8
MobiClip_Code_0209259C:
    stm r1, {r3, r4}
MobiClip_Code_020925A0:
    add r1, r1, #0x100
MobiClip_Code_020925A4:
    subs r2, r2, #1
MobiClip_Code_020925A8:
    moveq pc, lr
MobiClip_Code_020925AC:
    ldrb r3, [r0, #-1]
MobiClip_Code_020925B0:
    ldm r0, {r4, sb}
MobiClip_Code_020925B4:
    add r0, r0, #0x100
MobiClip_Code_020925B8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020925BC:
    and r4, ip, r4, lsr #1
MobiClip_Code_020925C0:
    and sb, ip, sb, lsr #1
MobiClip_Code_020925C4:
    add r3, r3, r4, lsl #8
MobiClip_Code_020925C8:
    add r3, r3, r4
MobiClip_Code_020925CC:
    add r4, sb, r4, lsr #24
MobiClip_Code_020925D0:
    add r4, r4, sb, lsl #8
MobiClip_Code_020925D4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020925D8:
    and r4, ip, r4, lsr #1
MobiClip_Code_020925DC:
    add r7, r7, r3
MobiClip_Code_020925E0:
    add r8, r8, r4
MobiClip_Code_020925E4:
    stm r1, {r7, r8}
MobiClip_Code_020925E8:
    add r1, r1, #0x100
MobiClip_Code_020925EC:
    subs r2, r2, #1
MobiClip_Code_020925F0:
    bne MobiClip_Code_02092564
MobiClip_Code_020925F4:
    mov pc, lr
    /* semantic constants 0x020925f8..0x020925fc */
    .global gMobiClipPackedAverageLaneMask1
    .type gMobiClipPackedAverageLaneMask1, %object
gMobiClipPackedAverageLaneMask1:
    .byte 0x7f, 0x7f, 0x7f, 0x7f
    .size gMobiClipPackedAverageLaneMask1, . - gMobiClipPackedAverageLaneMask1
MobiClip_Code_020925FC:
    ldr r3, [r0], #0x100
MobiClip_Code_02092600:
    str r3, [r1], #0x100
MobiClip_Code_02092604:
    subs r2, r2, #1
MobiClip_Code_02092608:
    bne MobiClip_Code_020925FC
MobiClip_Code_0209260C:
    mov pc, lr
MobiClip_Code_02092610:
    ldr ip, [pc, #0x4dc]
MobiClip_Code_02092614:
    ldr r3, [r0], #0x100
MobiClip_Code_02092618:
    and r3, ip, r3, lsr #1
MobiClip_Code_0209261C:
    ldr r7, [r0], #0x100
MobiClip_Code_02092620:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092624:
    add r3, r3, r7
MobiClip_Code_02092628:
    str r3, [r1], #0x100
MobiClip_Code_0209262C:
    subs r2, r2, #1
MobiClip_Code_02092630:
    moveq pc, lr
MobiClip_Code_02092634:
    ldr r3, [r0], #0x100
MobiClip_Code_02092638:
    and r3, ip, r3, lsr #1
MobiClip_Code_0209263C:
    add r7, r7, r3
MobiClip_Code_02092640:
    str r7, [r1], #0x100
MobiClip_Code_02092644:
    subs r2, r2, #1
MobiClip_Code_02092648:
    bne MobiClip_Code_0209261C
MobiClip_Code_0209264C:
    mov pc, lr
MobiClip_Code_02092650:
    ldr ip, [pc, #0x49c]
MobiClip_Code_02092654:
    ldr r3, [r0]
MobiClip_Code_02092658:
    ldrb sb, [r0, #4]
MobiClip_Code_0209265C:
    add r0, r0, #0x100
MobiClip_Code_02092660:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092664:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092668:
    add r3, r3, r3, lsr #8
MobiClip_Code_0209266C:
    add r3, r3, sb, lsl #24
MobiClip_Code_02092670:
    str r3, [r1], #0x100
MobiClip_Code_02092674:
    subs r2, r2, #1
MobiClip_Code_02092678:
    bne MobiClip_Code_02092654
MobiClip_Code_0209267C:
    mov pc, lr
MobiClip_Code_02092680:
    ldr ip, [pc, #0x46c]
MobiClip_Code_02092684:
    ldr r3, [r0]
MobiClip_Code_02092688:
    ldrb sb, [r0, #4]
MobiClip_Code_0209268C:
    add r0, r0, #0x100
MobiClip_Code_02092690:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092694:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092698:
    add r3, r3, r3, lsr #8
MobiClip_Code_0209269C:
    add r3, r3, sb, lsl #24
MobiClip_Code_020926A0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020926A4:
    ldr r7, [r0]
MobiClip_Code_020926A8:
    ldrb sb, [r0, #4]
MobiClip_Code_020926AC:
    add r0, r0, #0x100
MobiClip_Code_020926B0:
    and r7, ip, r7, lsr #1
MobiClip_Code_020926B4:
    and sb, ip, sb, lsr #1
MobiClip_Code_020926B8:
    add r7, r7, r7, lsr #8
MobiClip_Code_020926BC:
    add r7, r7, sb, lsl #24
MobiClip_Code_020926C0:
    and r7, ip, r7, lsr #1
MobiClip_Code_020926C4:
    add r3, r3, r7
MobiClip_Code_020926C8:
    str r3, [r1], #0x100
MobiClip_Code_020926CC:
    subs r2, r2, #1
MobiClip_Code_020926D0:
    moveq pc, lr
MobiClip_Code_020926D4:
    ldr r3, [r0]
MobiClip_Code_020926D8:
    ldrb sb, [r0, #4]
MobiClip_Code_020926DC:
    add r0, r0, #0x100
MobiClip_Code_020926E0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020926E4:
    and sb, ip, sb, lsr #1
MobiClip_Code_020926E8:
    add r3, r3, r3, lsr #8
MobiClip_Code_020926EC:
    add r3, r3, sb, lsl #24
MobiClip_Code_020926F0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020926F4:
    add r7, r7, r3
MobiClip_Code_020926F8:
    str r7, [r1], #0x100
MobiClip_Code_020926FC:
    subs r2, r2, #1
MobiClip_Code_02092700:
    bne MobiClip_Code_020926A4
MobiClip_Code_02092704:
    mov pc, lr
MobiClip_Code_02092708:
    sub r0, r0, #1
MobiClip_Code_0209270C:
    ldr r3, [r0]
MobiClip_Code_02092710:
    ldrb sb, [r0, #4]
MobiClip_Code_02092714:
    add r0, r0, #0x100
MobiClip_Code_02092718:
    lsr r3, r3, #8
MobiClip_Code_0209271C:
    add r3, r3, sb, lsl #24
MobiClip_Code_02092720:
    str r3, [r1], #0x100
MobiClip_Code_02092724:
    subs r2, r2, #1
MobiClip_Code_02092728:
    bne MobiClip_Code_0209270C
MobiClip_Code_0209272C:
    mov pc, lr
MobiClip_Code_02092730:
    sub r0, r0, #1
MobiClip_Code_02092734:
    ldr ip, [pc, #0x3b8]
MobiClip_Code_02092738:
    ldr r3, [r0]
MobiClip_Code_0209273C:
    ldrb sb, [r0, #4]
MobiClip_Code_02092740:
    add r0, r0, #0x100
MobiClip_Code_02092744:
    lsr r3, r3, #8
MobiClip_Code_02092748:
    add r3, r3, sb, lsl #24
MobiClip_Code_0209274C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092750:
    ldr r7, [r0]
MobiClip_Code_02092754:
    ldrb sb, [r0, #4]
MobiClip_Code_02092758:
    add r0, r0, #0x100
MobiClip_Code_0209275C:
    lsr r7, r7, #8
MobiClip_Code_02092760:
    add r7, r7, sb, lsl #24
MobiClip_Code_02092764:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092768:
    add r3, r3, r7
MobiClip_Code_0209276C:
    str r3, [r1], #0x100
MobiClip_Code_02092770:
    subs r2, r2, #1
MobiClip_Code_02092774:
    moveq pc, lr
MobiClip_Code_02092778:
    ldr r3, [r0]
MobiClip_Code_0209277C:
    ldrb sb, [r0, #4]
MobiClip_Code_02092780:
    add r0, r0, #0x100
MobiClip_Code_02092784:
    lsr r3, r3, #8
MobiClip_Code_02092788:
    add r3, r3, sb, lsl #24
MobiClip_Code_0209278C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092790:
    add r7, r7, r3
MobiClip_Code_02092794:
    str r7, [r1], #0x100
MobiClip_Code_02092798:
    subs r2, r2, #1
MobiClip_Code_0209279C:
    bne MobiClip_Code_02092750
MobiClip_Code_020927A0:
    mov pc, lr
MobiClip_Code_020927A4:
    ldr ip, [pc, #0x348]
MobiClip_Code_020927A8:
    sub r0, r0, #1
MobiClip_Code_020927AC:
    ldr r3, [r0]
MobiClip_Code_020927B0:
    ldrh sb, [r0, #4]
MobiClip_Code_020927B4:
    add r0, r0, #0x100
MobiClip_Code_020927B8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020927BC:
    and sb, ip, sb, lsr #1
MobiClip_Code_020927C0:
    lsr sl, r3, #0x10
MobiClip_Code_020927C4:
    add sl, sl, sb, lsl #16
MobiClip_Code_020927C8:
    add sl, sl, r3, lsr #8
MobiClip_Code_020927CC:
    add r3, sl, sb, lsl #24
MobiClip_Code_020927D0:
    str r3, [r1], #0x100
MobiClip_Code_020927D4:
    subs r2, r2, #1
MobiClip_Code_020927D8:
    bne MobiClip_Code_020927AC
MobiClip_Code_020927DC:
    mov pc, lr
MobiClip_Code_020927E0:
    ldr ip, [pc, #0x30c]
MobiClip_Code_020927E4:
    sub r0, r0, #1
MobiClip_Code_020927E8:
    ldr r3, [r0]
MobiClip_Code_020927EC:
    ldrh sb, [r0, #4]
MobiClip_Code_020927F0:
    add r0, r0, #0x100
MobiClip_Code_020927F4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020927F8:
    and sb, ip, sb, lsr #1
MobiClip_Code_020927FC:
    lsr sl, r3, #0x10
MobiClip_Code_02092800:
    add sl, sl, sb, lsl #16
MobiClip_Code_02092804:
    add sl, sl, r3, lsr #8
MobiClip_Code_02092808:
    add r3, sl, sb, lsl #24
MobiClip_Code_0209280C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092810:
    ldr r7, [r0]
MobiClip_Code_02092814:
    ldrh sb, [r0, #4]
MobiClip_Code_02092818:
    add r0, r0, #0x100
MobiClip_Code_0209281C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092820:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092824:
    lsr sl, r7, #0x10
MobiClip_Code_02092828:
    add sl, sl, sb, lsl #16
MobiClip_Code_0209282C:
    add sl, sl, r7, lsr #8
MobiClip_Code_02092830:
    add r7, sl, sb, lsl #24
MobiClip_Code_02092834:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092838:
    add r3, r3, r7
MobiClip_Code_0209283C:
    str r3, [r1], #0x100
MobiClip_Code_02092840:
    subs r2, r2, #1
MobiClip_Code_02092844:
    moveq pc, lr
MobiClip_Code_02092848:
    ldr r3, [r0]
MobiClip_Code_0209284C:
    ldrh sb, [r0, #4]
MobiClip_Code_02092850:
    add r0, r0, #0x100
MobiClip_Code_02092854:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092858:
    and sb, ip, sb, lsr #1
MobiClip_Code_0209285C:
    lsr sl, r3, #0x10
MobiClip_Code_02092860:
    add sl, sl, sb, lsl #16
MobiClip_Code_02092864:
    add sl, sl, r3, lsr #8
MobiClip_Code_02092868:
    add r3, sl, sb, lsl #24
MobiClip_Code_0209286C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092870:
    add r7, r7, r3
MobiClip_Code_02092874:
    str r7, [r1], #0x100
MobiClip_Code_02092878:
    subs r2, r2, #1
MobiClip_Code_0209287C:
    bne MobiClip_Code_02092810
MobiClip_Code_02092880:
    mov pc, lr
MobiClip_Code_02092884:
    ldrh r3, [r0], #2
MobiClip_Code_02092888:
    ldrh sb, [r0], #-2
MobiClip_Code_0209288C:
    add r0, r0, #0x100
MobiClip_Code_02092890:
    add r3, r3, sb, lsl #16
MobiClip_Code_02092894:
    str r3, [r1], #0x100
MobiClip_Code_02092898:
    subs r2, r2, #1
MobiClip_Code_0209289C:
    bne MobiClip_Code_02092884
MobiClip_Code_020928A0:
    mov pc, lr
MobiClip_Code_020928A4:
    ldr ip, [pc, #0x248]
MobiClip_Code_020928A8:
    ldrh r3, [r0], #2
MobiClip_Code_020928AC:
    ldrh sb, [r0], #-2
MobiClip_Code_020928B0:
    add r0, r0, #0x100
MobiClip_Code_020928B4:
    add r3, r3, sb, lsl #16
MobiClip_Code_020928B8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020928BC:
    ldrh r7, [r0], #2
MobiClip_Code_020928C0:
    ldrh sb, [r0], #-2
MobiClip_Code_020928C4:
    add r0, r0, #0x100
MobiClip_Code_020928C8:
    add r7, r7, sb, lsl #16
MobiClip_Code_020928CC:
    and r7, ip, r7, lsr #1
MobiClip_Code_020928D0:
    add r3, r3, r7
MobiClip_Code_020928D4:
    str r3, [r1], #0x100
MobiClip_Code_020928D8:
    subs r2, r2, #1
MobiClip_Code_020928DC:
    moveq pc, lr
MobiClip_Code_020928E0:
    ldrh r3, [r0], #2
MobiClip_Code_020928E4:
    ldrh sb, [r0], #-2
MobiClip_Code_020928E8:
    add r0, r0, #0x100
MobiClip_Code_020928EC:
    add r3, r3, sb, lsl #16
MobiClip_Code_020928F0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020928F4:
    add r7, r7, r3
MobiClip_Code_020928F8:
    str r7, [r1], #0x100
MobiClip_Code_020928FC:
    subs r2, r2, #1
MobiClip_Code_02092900:
    bne MobiClip_Code_020928BC
MobiClip_Code_02092904:
    mov pc, lr
MobiClip_Code_02092908:
    ldr ip, [pc, #0x1e4]
MobiClip_Code_0209290C:
    add r0, r0, #2
MobiClip_Code_02092910:
    ldrh r3, [r0, #-2]
MobiClip_Code_02092914:
    ldr sb, [r0], #0x100
MobiClip_Code_02092918:
    and r3, ip, r3, lsr #1
MobiClip_Code_0209291C:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092920:
    add sl, r3, sb, lsl #16
MobiClip_Code_02092924:
    add sl, sl, r3, lsr #8
MobiClip_Code_02092928:
    add r3, sl, sb, lsl #8
MobiClip_Code_0209292C:
    str r3, [r1], #0x100
MobiClip_Code_02092930:
    subs r2, r2, #1
MobiClip_Code_02092934:
    bne MobiClip_Code_02092910
MobiClip_Code_02092938:
    mov pc, lr
MobiClip_Code_0209293C:
    ldr ip, [pc, #0x1b0]
MobiClip_Code_02092940:
    add r0, r0, #2
MobiClip_Code_02092944:
    ldrh r3, [r0, #-2]
MobiClip_Code_02092948:
    ldr sb, [r0], #0x100
MobiClip_Code_0209294C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092950:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092954:
    add sl, r3, sb, lsl #16
MobiClip_Code_02092958:
    add sl, sl, r3, lsr #8
MobiClip_Code_0209295C:
    add r3, sl, sb, lsl #8
MobiClip_Code_02092960:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092964:
    ldrh r7, [r0, #-2]
MobiClip_Code_02092968:
    ldr sb, [r0], #0x100
MobiClip_Code_0209296C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092970:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092974:
    add sl, r7, sb, lsl #16
MobiClip_Code_02092978:
    add sl, sl, r7, lsr #8
MobiClip_Code_0209297C:
    add r7, sl, sb, lsl #8
MobiClip_Code_02092980:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092984:
    add r3, r3, r7
MobiClip_Code_02092988:
    str r3, [r1], #0x100
MobiClip_Code_0209298C:
    subs r2, r2, #1
MobiClip_Code_02092990:
    moveq pc, lr
MobiClip_Code_02092994:
    ldrh r3, [r0, #-2]
MobiClip_Code_02092998:
    ldr sb, [r0], #0x100
MobiClip_Code_0209299C:
    and r3, ip, r3, lsr #1
MobiClip_Code_020929A0:
    and sb, ip, sb, lsr #1
MobiClip_Code_020929A4:
    add sl, r3, sb, lsl #16
MobiClip_Code_020929A8:
    add sl, sl, r3, lsr #8
MobiClip_Code_020929AC:
    add r3, sl, sb, lsl #8
MobiClip_Code_020929B0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020929B4:
    add r7, r7, r3
MobiClip_Code_020929B8:
    str r7, [r1], #0x100
MobiClip_Code_020929BC:
    subs r2, r2, #1
MobiClip_Code_020929C0:
    bne MobiClip_Code_02092964
MobiClip_Code_020929C4:
    mov pc, lr
MobiClip_Code_020929C8:
    add r0, r0, #1
MobiClip_Code_020929CC:
    ldrb r3, [r0, #-1]
MobiClip_Code_020929D0:
    ldr sb, [r0], #0x100
MobiClip_Code_020929D4:
    add r3, r3, sb, lsl #8
MobiClip_Code_020929D8:
    str r3, [r1], #0x100
MobiClip_Code_020929DC:
    subs r2, r2, #1
MobiClip_Code_020929E0:
    bne MobiClip_Code_020929CC
MobiClip_Code_020929E4:
    mov pc, lr
MobiClip_Code_020929E8:
    ldr ip, [pc, #0x104]
MobiClip_Code_020929EC:
    add r0, r0, #1
MobiClip_Code_020929F0:
    ldrb r3, [r0, #-1]
MobiClip_Code_020929F4:
    ldr sb, [r0], #0x100
MobiClip_Code_020929F8:
    add r3, r3, sb, lsl #8
MobiClip_Code_020929FC:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092A00:
    ldrb r7, [r0, #-1]
MobiClip_Code_02092A04:
    ldr sb, [r0], #0x100
MobiClip_Code_02092A08:
    add r7, r7, sb, lsl #8
MobiClip_Code_02092A0C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092A10:
    add r3, r3, r7
MobiClip_Code_02092A14:
    str r3, [r1], #0x100
MobiClip_Code_02092A18:
    subs r2, r2, #1
MobiClip_Code_02092A1C:
    moveq pc, lr
MobiClip_Code_02092A20:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092A24:
    ldr sb, [r0], #0x100
MobiClip_Code_02092A28:
    add r3, r3, sb, lsl #8
MobiClip_Code_02092A2C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092A30:
    add r7, r7, r3
MobiClip_Code_02092A34:
    str r7, [r1], #0x100
MobiClip_Code_02092A38:
    subs r2, r2, #1
MobiClip_Code_02092A3C:
    bne MobiClip_Code_02092A00
MobiClip_Code_02092A40:
    mov pc, lr
MobiClip_Code_02092A44:
    ldr ip, [pc, #0xa8]
MobiClip_Code_02092A48:
    add r0, r0, #1
MobiClip_Code_02092A4C:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092A50:
    ldr sb, [r0], #0x100
MobiClip_Code_02092A54:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092A58:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092A5C:
    add r3, r3, sb, lsl #8
MobiClip_Code_02092A60:
    add r3, r3, sb
MobiClip_Code_02092A64:
    str r3, [r1], #0x100
MobiClip_Code_02092A68:
    subs r2, r2, #1
MobiClip_Code_02092A6C:
    bne MobiClip_Code_02092A4C
MobiClip_Code_02092A70:
    mov pc, lr
MobiClip_Code_02092A74:
    ldr ip, [pc, #0x78]
MobiClip_Code_02092A78:
    add r0, r0, #1
MobiClip_Code_02092A7C:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092A80:
    ldr sb, [r0], #0x100
MobiClip_Code_02092A84:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092A88:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092A8C:
    add r3, r3, sb, lsl #8
MobiClip_Code_02092A90:
    add r3, r3, sb
MobiClip_Code_02092A94:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092A98:
    ldrb r7, [r0, #-1]
MobiClip_Code_02092A9C:
    ldr sb, [r0], #0x100
MobiClip_Code_02092AA0:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092AA4:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092AA8:
    add r7, r7, sb, lsl #8
MobiClip_Code_02092AAC:
    add r7, r7, sb
MobiClip_Code_02092AB0:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092AB4:
    add r3, r3, r7
MobiClip_Code_02092AB8:
    str r3, [r1], #0x100
MobiClip_Code_02092ABC:
    subs r2, r2, #1
MobiClip_Code_02092AC0:
    moveq pc, lr
MobiClip_Code_02092AC4:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092AC8:
    ldr sb, [r0], #0x100
MobiClip_Code_02092ACC:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092AD0:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092AD4:
    add r3, r3, sb, lsl #8
MobiClip_Code_02092AD8:
    add r3, r3, sb
MobiClip_Code_02092ADC:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092AE0:
    add r7, r7, r3
MobiClip_Code_02092AE4:
    str r7, [r1], #0x100
MobiClip_Code_02092AE8:
    subs r2, r2, #1
MobiClip_Code_02092AEC:
    bne MobiClip_Code_02092A98
MobiClip_Code_02092AF0:
    mov pc, lr
    /* semantic constants 0x02092af4..0x02092af8 */
    .global gMobiClipPackedAverageLaneMask2
    .type gMobiClipPackedAverageLaneMask2, %object
gMobiClipPackedAverageLaneMask2:
    .byte 0x7f, 0x7f, 0x7f, 0x7f
    .size gMobiClipPackedAverageLaneMask2, . - gMobiClipPackedAverageLaneMask2
MobiClip_Code_02092AF8:
    ldrh r3, [r0]
MobiClip_Code_02092AFC:
    add r0, r0, #0x100
MobiClip_Code_02092B00:
    strh r3, [r1]
MobiClip_Code_02092B04:
    add r1, r1, #0x100
MobiClip_Code_02092B08:
    subs r2, r2, #1
MobiClip_Code_02092B0C:
    bne MobiClip_Code_02092AF8
MobiClip_Code_02092B10:
    mov pc, lr
MobiClip_Code_02092B14:
    ldr ip, [pc, #0x26c]
MobiClip_Code_02092B18:
    ldrh r3, [r0]
MobiClip_Code_02092B1C:
    add r0, r0, #0x100
MobiClip_Code_02092B20:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092B24:
    ldrh r7, [r0]
MobiClip_Code_02092B28:
    add r0, r0, #0x100
MobiClip_Code_02092B2C:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092B30:
    add r3, r3, r7
MobiClip_Code_02092B34:
    strh r3, [r1]
MobiClip_Code_02092B38:
    add r1, r1, #0x100
MobiClip_Code_02092B3C:
    subs r2, r2, #1
MobiClip_Code_02092B40:
    moveq pc, lr
MobiClip_Code_02092B44:
    ldrh r3, [r0]
MobiClip_Code_02092B48:
    add r0, r0, #0x100
MobiClip_Code_02092B4C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092B50:
    add r7, r7, r3
MobiClip_Code_02092B54:
    strh r7, [r1]
MobiClip_Code_02092B58:
    add r1, r1, #0x100
MobiClip_Code_02092B5C:
    subs r2, r2, #1
MobiClip_Code_02092B60:
    bne MobiClip_Code_02092B24
MobiClip_Code_02092B64:
    mov pc, lr
MobiClip_Code_02092B68:
    ldr ip, [pc, #0x218]
MobiClip_Code_02092B6C:
    ldrh r3, [r0]
MobiClip_Code_02092B70:
    ldrb sb, [r0, #2]
MobiClip_Code_02092B74:
    add r0, r0, #0x100
MobiClip_Code_02092B78:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092B7C:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092B80:
    add r3, r3, r3, lsr #8
MobiClip_Code_02092B84:
    add r3, r3, sb, lsl #8
MobiClip_Code_02092B88:
    strh r3, [r1]
MobiClip_Code_02092B8C:
    add r1, r1, #0x100
MobiClip_Code_02092B90:
    subs r2, r2, #1
MobiClip_Code_02092B94:
    bne MobiClip_Code_02092B6C
MobiClip_Code_02092B98:
    mov pc, lr
MobiClip_Code_02092B9C:
    ldr ip, [pc, #0x1e4]
MobiClip_Code_02092BA0:
    ldrh r3, [r0]
MobiClip_Code_02092BA4:
    ldrb sb, [r0, #2]
MobiClip_Code_02092BA8:
    add r0, r0, #0x100
MobiClip_Code_02092BAC:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092BB0:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092BB4:
    add r3, r3, r3, lsr #8
MobiClip_Code_02092BB8:
    add r3, r3, sb, lsl #8
MobiClip_Code_02092BBC:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092BC0:
    ldrh r7, [r0]
MobiClip_Code_02092BC4:
    ldrb sb, [r0, #2]
MobiClip_Code_02092BC8:
    add r0, r0, #0x100
MobiClip_Code_02092BCC:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092BD0:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092BD4:
    add r7, r7, r7, lsr #8
MobiClip_Code_02092BD8:
    add r7, r7, sb, lsl #8
MobiClip_Code_02092BDC:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092BE0:
    add r3, r3, r7
MobiClip_Code_02092BE4:
    strh r3, [r1]
MobiClip_Code_02092BE8:
    add r1, r1, #0x100
MobiClip_Code_02092BEC:
    subs r2, r2, #1
MobiClip_Code_02092BF0:
    moveq pc, lr
MobiClip_Code_02092BF4:
    ldrh r3, [r0]
MobiClip_Code_02092BF8:
    ldrb sb, [r0, #2]
MobiClip_Code_02092BFC:
    add r0, r0, #0x100
MobiClip_Code_02092C00:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092C04:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092C08:
    add r3, r3, r3, lsr #8
MobiClip_Code_02092C0C:
    add r3, r3, sb, lsl #8
MobiClip_Code_02092C10:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092C14:
    add r7, r7, r3
MobiClip_Code_02092C18:
    strh r7, [r1]
MobiClip_Code_02092C1C:
    add r1, r1, #0x100
MobiClip_Code_02092C20:
    subs r2, r2, #1
MobiClip_Code_02092C24:
    bne MobiClip_Code_02092BC0
MobiClip_Code_02092C28:
    mov pc, lr
MobiClip_Code_02092C2C:
    add r0, r0, #1
MobiClip_Code_02092C30:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092C34:
    ldrb sb, [r0], #0x100
MobiClip_Code_02092C38:
    add r3, r3, sb, lsl #8
MobiClip_Code_02092C3C:
    strh r3, [r1]
MobiClip_Code_02092C40:
    add r1, r1, #0x100
MobiClip_Code_02092C44:
    subs r2, r2, #1
MobiClip_Code_02092C48:
    bne MobiClip_Code_02092C30
MobiClip_Code_02092C4C:
    mov pc, lr
MobiClip_Code_02092C50:
    add r0, r0, #1
MobiClip_Code_02092C54:
    ldr ip, [pc, #0x12c]
MobiClip_Code_02092C58:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092C5C:
    ldrb sb, [r0], #0x100
MobiClip_Code_02092C60:
    add r3, r3, sb, lsl #8
MobiClip_Code_02092C64:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092C68:
    ldrb r7, [r0, #-1]
MobiClip_Code_02092C6C:
    ldrb sb, [r0], #0x100
MobiClip_Code_02092C70:
    add r7, r7, sb, lsl #8
MobiClip_Code_02092C74:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092C78:
    add r3, r3, r7
MobiClip_Code_02092C7C:
    strh r3, [r1]
MobiClip_Code_02092C80:
    add r1, r1, #0x100
MobiClip_Code_02092C84:
    subs r2, r2, #1
MobiClip_Code_02092C88:
    moveq pc, lr
MobiClip_Code_02092C8C:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092C90:
    ldrb sb, [r0], #0x100
MobiClip_Code_02092C94:
    add r3, r3, sb, lsl #8
MobiClip_Code_02092C98:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092C9C:
    add r7, r7, r3
MobiClip_Code_02092CA0:
    strh r7, [r1]
MobiClip_Code_02092CA4:
    add r1, r1, #0x100
MobiClip_Code_02092CA8:
    subs r2, r2, #1
MobiClip_Code_02092CAC:
    bne MobiClip_Code_02092C68
MobiClip_Code_02092CB0:
    mov pc, lr
MobiClip_Code_02092CB4:
    ldr ip, [pc, #0xcc]
MobiClip_Code_02092CB8:
    ldrb r3, [r0]
MobiClip_Code_02092CBC:
    ldrh sb, [r0, #1]
MobiClip_Code_02092CC0:
    add r0, r0, #0x100
MobiClip_Code_02092CC4:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092CC8:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092CCC:
    lsl sl, sb, #0x18
MobiClip_Code_02092CD0:
    add sl, r3, sl, lsr #16
MobiClip_Code_02092CD4:
    add r3, sl, sb
MobiClip_Code_02092CD8:
    strh r3, [r1]
MobiClip_Code_02092CDC:
    add r1, r1, #0x100
MobiClip_Code_02092CE0:
    subs r2, r2, #1
MobiClip_Code_02092CE4:
    bne MobiClip_Code_02092CB8
MobiClip_Code_02092CE8:
    mov pc, lr
MobiClip_Code_02092CEC:
    ldr ip, [pc, #0x94]
MobiClip_Code_02092CF0:
    ldrb r3, [r0]
MobiClip_Code_02092CF4:
    ldrh sb, [r0, #1]
MobiClip_Code_02092CF8:
    add r0, r0, #0x100
MobiClip_Code_02092CFC:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092D00:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092D04:
    lsl sl, sb, #0x18
MobiClip_Code_02092D08:
    add sl, r3, sl, lsr #16
MobiClip_Code_02092D0C:
    add r3, sl, sb
MobiClip_Code_02092D10:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092D14:
    ldrb r7, [r0]
MobiClip_Code_02092D18:
    ldrh sb, [r0, #1]
MobiClip_Code_02092D1C:
    add r0, r0, #0x100
MobiClip_Code_02092D20:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092D24:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092D28:
    lsl sl, sb, #0x18
MobiClip_Code_02092D2C:
    add sl, r7, sl, lsr #16
MobiClip_Code_02092D30:
    add r7, sl, sb
MobiClip_Code_02092D34:
    and r7, ip, r7, lsr #1
MobiClip_Code_02092D38:
    add r3, r3, r7
MobiClip_Code_02092D3C:
    strh r3, [r1]
MobiClip_Code_02092D40:
    add r1, r1, #0x100
MobiClip_Code_02092D44:
    subs r2, r2, #1
MobiClip_Code_02092D48:
    moveq pc, lr
MobiClip_Code_02092D4C:
    ldrb r3, [r0]
MobiClip_Code_02092D50:
    ldrh sb, [r0, #1]
MobiClip_Code_02092D54:
    add r0, r0, #0x100
MobiClip_Code_02092D58:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092D5C:
    and sb, ip, sb, lsr #1
MobiClip_Code_02092D60:
    lsl sl, sb, #0x18
MobiClip_Code_02092D64:
    add sl, r3, sl, lsr #16
MobiClip_Code_02092D68:
    add r3, sl, sb
MobiClip_Code_02092D6C:
    and r3, ip, r3, lsr #1
MobiClip_Code_02092D70:
    add r7, r7, r3
MobiClip_Code_02092D74:
    strh r7, [r1]
MobiClip_Code_02092D78:
    add r1, r1, #0x100
MobiClip_Code_02092D7C:
    subs r2, r2, #1
MobiClip_Code_02092D80:
    bne MobiClip_Code_02092D14
MobiClip_Code_02092D84:
    mov pc, lr
    /* semantic constants 0x02092d88..0x02092d8c */
    .global gMobiClipPackedAverageLaneMask3
    .type gMobiClipPackedAverageLaneMask3, %object
gMobiClipPackedAverageLaneMask3:
    .byte 0x7f, 0x7f, 0x7f, 0x7f
    .size gMobiClipPackedAverageLaneMask3, . - gMobiClipPackedAverageLaneMask3
MobiClip_Code_02092D8C:
    ldrb r3, [r0], #0x100
MobiClip_Code_02092D90:
    strb r3, [r1], #0x100
MobiClip_Code_02092D94:
    subs r2, r2, #1
MobiClip_Code_02092D98:
    bne MobiClip_Code_02092D8C
MobiClip_Code_02092D9C:
    mov pc, lr
MobiClip_Code_02092DA0:
    ldrb r3, [r0], #0x100
MobiClip_Code_02092DA4:
    lsr r3, r3, #1
MobiClip_Code_02092DA8:
    ldrb r7, [r0], #0x100
MobiClip_Code_02092DAC:
    lsr r7, r7, #1
MobiClip_Code_02092DB0:
    add r3, r3, r7
MobiClip_Code_02092DB4:
    strb r3, [r1], #0x100
MobiClip_Code_02092DB8:
    subs r2, r2, #1
MobiClip_Code_02092DBC:
    moveq pc, lr
MobiClip_Code_02092DC0:
    ldrb r3, [r0], #0x100
MobiClip_Code_02092DC4:
    lsr r3, r3, #1
MobiClip_Code_02092DC8:
    add r7, r7, r3
MobiClip_Code_02092DCC:
    strb r7, [r1], #0x100
MobiClip_Code_02092DD0:
    subs r2, r2, #1
MobiClip_Code_02092DD4:
    bne MobiClip_Code_02092DA8
MobiClip_Code_02092DD8:
    mov pc, lr
MobiClip_Code_02092DDC:
    add r0, r0, #1
MobiClip_Code_02092DE0:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092DE4:
    ldrb sb, [r0], #0x100
MobiClip_Code_02092DE8:
    lsr r3, r3, #1
MobiClip_Code_02092DEC:
    add r3, r3, sb, lsr #1
MobiClip_Code_02092DF0:
    strb r3, [r1], #0x100
MobiClip_Code_02092DF4:
    subs r2, r2, #1
MobiClip_Code_02092DF8:
    bne MobiClip_Code_02092DE0
MobiClip_Code_02092DFC:
    mov pc, lr
MobiClip_Code_02092E00:
    ldrb r3, [r0], #1
MobiClip_Code_02092E04:
    ldrb sb, [r0], #0x100
MobiClip_Code_02092E08:
    lsr r3, r3, #1
MobiClip_Code_02092E0C:
    add r3, r3, sb, lsr #1
MobiClip_Code_02092E10:
    lsr r3, r3, #1
MobiClip_Code_02092E14:
    ldrb r7, [r0, #-1]
MobiClip_Code_02092E18:
    ldrb sb, [r0], #0x100
MobiClip_Code_02092E1C:
    lsr r7, r7, #1
MobiClip_Code_02092E20:
    add r7, r7, sb, lsr #1
MobiClip_Code_02092E24:
    lsr r7, r7, #1
MobiClip_Code_02092E28:
    add r3, r3, r7
MobiClip_Code_02092E2C:
    strb r3, [r1], #0x100
MobiClip_Code_02092E30:
    subs r2, r2, #1
MobiClip_Code_02092E34:
    moveq pc, lr
MobiClip_Code_02092E38:
    ldrb r3, [r0, #-1]
MobiClip_Code_02092E3C:
    ldrb sb, [r0], #0x100
MobiClip_Code_02092E40:
    lsr r3, r3, #1
MobiClip_Code_02092E44:
    add r3, r3, sb, lsr #1
MobiClip_Code_02092E48:
    lsr r3, r3, #1
MobiClip_Code_02092E4C:
    add r7, r7, r3
MobiClip_Code_02092E50:
    strb r7, [r1], #0x100
MobiClip_Code_02092E54:
    subs r2, r2, #1
MobiClip_Code_02092E58:
    bne MobiClip_Code_02092E14
MobiClip_Code_02092E5C:
    mov pc, lr
    .size data_ov024_0208c8c4, . - data_ov024_0208c8c4
