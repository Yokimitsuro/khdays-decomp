/* NitroSDK DGT: DGTi_hash2_arm4_small, the SHA-1 block transform of the prebuilt libdgt.a
 * (sha1s-arm4cw.o, hand-written ARM for CodeWarrior -- byte-identical to this ROM). It hashes
 * 64-byte blocks of `src` (r1, `len` bytes in r2) into the five-word state at r0. The byte-swap
 * mask and the four round constants K1..K4 are the 0x14 bytes just before the function, read
 * pc-relative. */
asm void func_0200bd4c(void *state, const void *src, unsigned long len)
{
    stmdb   sp!, {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
    ldmia   r0, {r3, r9, r10, r11, ip}
    sub     sp, sp, #0x84
    str     r2, [sp, #0x80]
    @1:
    ldr     r8, [pc, #-0x28]    /* K1 0x5a827999 (rounds 0-19) */
    ldr     r7, [pc, #-0x30]    /* the byte-swap mask 0x00ff00ff */
    mov     r6, sp
    mov     r5, #0
    @2:
    ldr     r4, [r1], #4
    add     r2, r8, ip
    add     r2, r2, r3, ror #27
    and     lr, r4, r7
    and     r4, r7, r4, ror #24
    orr     r4, r4, lr, ror #8
    str     r4, [r6, #0x40]
    str     r4, [r6], #4
    add     r2, r2, r4
    eor     r4, r10, r11
    and     r4, r4, r9
    eor     r4, r4, r11
    add     r2, r2, r4
    mov     r9, r9, ror #2
    mov     ip, r11
    mov     r11, r10
    mov     r10, r9
    mov     r9, r3
    mov     r3, r2
    add     r5, r5, #4
    cmp     r5, #0x40
    blt     @2
    mov     r7, #0
    mov     r6, sp
    @3:
    ldr     r2, [r6]
    ldr     r5, [r6, #8]
    ldr     r4, [r6, #0x20]
    ldr     lr, [r6, #0x34]
    eor     r2, r2, r5
    eor     r4, r4, lr
    eor     r2, r2, r4
    mov     r2, r2, ror #0x1f
    str     r2, [r6, #0x40]
    str     r2, [r6], #4
    add     r2, r2, ip
    add     r2, r2, r8
    add     r2, r2, r3, ror #27
    eor     r4, r10, r11
    and     r4, r4, r9
    eor     r4, r4, r11
    add     r2, r2, r4
    mov     r9, r9, ror #2
    mov     ip, r11
    mov     r11, r10
    mov     r10, r9
    mov     r9, r3
    mov     r3, r2
    add     r7, r7, #4
    cmp     r7, #0x10
    blt     @3
    ldr     r8, [pc, #-0xfc]    /* K2 0x6ed9eba1 (rounds 20-39) */
    mov     r7, #0
    @4:
    ldr     r2, [r6]
    ldr     r4, [r6, #8]
    ldr     lr, [r6, #0x20]
    ldr     r5, [r6, #0x34]
    eor     r2, r2, r4
    eor     lr, lr, r5
    eor     r2, r2, lr
    mov     r2, r2, ror #0x1f
    str     r2, [r6, #0x40]
    str     r2, [r6], #4
    add     r2, r2, ip
    add     r2, r2, r8
    add     r2, r2, r3, ror #27
    eor     lr, r9, r10
    eor     lr, lr, r11
    add     r2, r2, lr
    mov     r9, r9, ror #2
    mov     ip, r11
    mov     r11, r10
    mov     r10, r9
    mov     r9, r3
    mov     r3, r2
    add     r7, r7, #1
    cmp     r7, #0xc
    moveq   r6, sp
    cmp     r7, #0x14
    blt     @4
    ldr     r8, [pc, #-0x16c]    /* K3 0x8f1bbcdc (rounds 40-59) */
    mov     r7, #0
    @5:
    ldr     r2, [r6]
    ldr     lr, [r6, #8]
    ldr     r5, [r6, #0x20]
    ldr     r4, [r6, #0x34]
    eor     r2, r2, lr
    eor     r5, r5, r4
    eor     r2, r2, r5
    mov     r2, r2, ror #0x1f
    str     r2, [r6, #0x40]
    str     r2, [r6], #4
    add     r2, r2, ip
    add     r2, r2, r8
    add     r2, r2, r3, ror #27
    orr     r5, r9, r10
    and     r5, r5, r11
    and     r4, r9, r10
    orr     r5, r5, r4
    add     r2, r2, r5
    mov     r9, r9, ror #2
    mov     ip, r11
    mov     r11, r10
    mov     r10, r9
    mov     r9, r3
    mov     r3, r2
    add     r7, r7, #1
    cmp     r7, #8
    moveq   r6, sp
    cmp     r7, #0x14
    blt     @5
    ldr     r8, [pc, #-0x1e4]    /* K4 0xca62c1d6 (rounds 60-79) */
    mov     r7, #0
    @6:
    ldr     r2, [r6]
    ldr     r5, [r6, #8]
    ldr     r4, [r6, #0x20]
    ldr     lr, [r6, #0x34]
    eor     r2, r2, r5
    eor     r4, r4, lr
    eor     r2, r2, r4
    mov     r2, r2, ror #0x1f
    str     r2, [r6, #0x40]
    str     r2, [r6], #4
    add     r2, r2, ip
    add     r2, r2, r8
    add     r2, r2, r3, ror #27
    eor     r4, r9, r10
    eor     r4, r4, r11
    add     r2, r2, r4
    mov     r9, r9, ror #2
    mov     ip, r11
    mov     r11, r10
    mov     r10, r9
    mov     r9, r3
    mov     r3, r2
    add     r7, r7, #1
    cmp     r7, #4
    moveq   r6, sp
    cmp     r7, #0x14
    blt     @6
    ldmia   r0, {r2, r4, r6, r7, lr}
    add     r3, r3, r2
    add     r9, r9, r4
    add     r10, r10, r6
    add     r11, r11, r7
    add     ip, ip, lr
    stmia   r0, {r3, r9, r10, r11, ip}
    ldr     lr, [sp, #0x80]
    subs    lr, lr, #0x40
    str     lr, [sp, #0x80]
    bgt     @1
    add     sp, sp, #0x84
    ldmia   sp!, {r4, r5, r6, r7, r8, r9, r10, r11, ip, pc}
}
