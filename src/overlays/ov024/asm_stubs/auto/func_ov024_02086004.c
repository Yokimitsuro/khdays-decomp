/* MobiClip: turn one decoded frame into 15-bit pixels, two rows at a time.
 *
 * The colour tables are three windows into one lookup block, offset by the
 * chroma pair: red by Cr, green by Cb-Cr, blue by that minus twice Cb. Each
 * chroma sample covers a 2x2 luma quad, dithered on a checkerboard -- the two
 * pixels on one diagonal look their luma up four levels lower. Each pass emits
 * four pixels as two words, one into each of the two rows being written, so the
 * outer loop steps down two rows and the inner one covers sixteen columns per
 * pass, eight passes unrolled.
 *
 * HAND-WRITTEN ARM in the original, not compiler output. Six measurements say
 * so: the prologue is the idiomatic `stmfd sp!, {r4-r12, lr}`, and only seven
 * functions in the whole ROM save ip -- none reconstructed, the other six being
 * the toolchain's own hand-written 64-bit helpers. It reads the chroma pair
 * with two consecutive post-indexed byte loads through one pointer, an idiom
 * that occurs exactly once in the ROM (here) and in none of the reconstructed
 * sources; the compiler folds that pattern into a displaced load plus a single
 * increment in every form tried, volatile and maximum register pressure
 * included. A semantically complete C candidate was then run through all 26
 * compilers in the tree, 15 flag variants and 150 pragma settings: none
 * reproduces either signature, and the closest is 1528 bytes against 1472.
 *
 * Every word below is one readable mnemonic: no incbin, no .inst, no opcode
 * words. Assembles byte-exact, 1472 bytes, zero relocations.
 * See MobiClip_BlitRows in Ghidra for the algorithm and the field names, and
 * build/try/func_ov024_02086004.cpp for the readable C the port can use.
 */
struct MobiClipBlitView;

asm void func_ov024_02086004(struct MobiClipBlitView *pView)
{
    stmfd     sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
    ldr       r8, [r0, #0xc]
    ldr       r9, [r0, #0x10]
    ldr       r10, [r0, #0x14]
    ldr       r3, [r0, #0x18]
    mov       r4, #0x100
    rsb       r5, r9, r4, lsl #1
    sub       r6, r4, r9, lsr #1
    sub       r7, r8, r9
    mov       r7, r7, lsl #1
    stmfd     sp!, {r5, r6, r7, r8, r9, r10}
    ldr       r1, [r0, #4]
    ldr       r2, [r0, #8]
    ldr       r0, [r0]
    add       r3, r3, #0x100
    add       lr, r2, r8
L040:
    str       r10, [sp, #-4]!
    ldr       r10, [sp, #0x14]
L048:
    ldrb      r5, [r1], #0x80
    ldrb      r6, [r1], #-0x7f
    ldrb      r4, [r0], #1
    sub       r5, r5, #0x80
    sub       r6, r6, #0x80
    add       r7, r3, r6
    sub       r6, r5, r6
    add       r6, r6, r3
    sub       r5, r6, r5, lsl #1
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    sub       r4, r4, #4
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #1
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [r2], #4
    sub       r4, r4, #4
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #-0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [lr], #4
    ldrb      r5, [r1], #0x80
    ldrb      r6, [r1], #-0x7f
    ldrb      r4, [r0], #1
    sub       r5, r5, #0x80
    sub       r6, r6, #0x80
    add       r7, r3, r6
    sub       r6, r5, r6
    add       r6, r6, r3
    sub       r5, r6, r5, lsl #1
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    sub       r4, r4, #4
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #1
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [r2], #4
    sub       r4, r4, #4
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #-0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [lr], #4
    ldrb      r5, [r1], #0x80
    ldrb      r6, [r1], #-0x7f
    ldrb      r4, [r0], #1
    sub       r5, r5, #0x80
    sub       r6, r6, #0x80
    add       r7, r3, r6
    sub       r6, r5, r6
    add       r6, r6, r3
    sub       r5, r6, r5, lsl #1
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    sub       r4, r4, #4
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #1
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [r2], #4
    sub       r4, r4, #4
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #-0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [lr], #4
    ldrb      r5, [r1], #0x80
    ldrb      r6, [r1], #-0x7f
    ldrb      r4, [r0], #1
    sub       r5, r5, #0x80
    sub       r6, r6, #0x80
    add       r7, r3, r6
    sub       r6, r5, r6
    add       r6, r6, r3
    sub       r5, r6, r5, lsl #1
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    sub       r4, r4, #4
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #1
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [r2], #4
    sub       r4, r4, #4
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #-0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [lr], #4
    ldrb      r5, [r1], #0x80
    ldrb      r6, [r1], #-0x7f
    ldrb      r4, [r0], #1
    sub       r5, r5, #0x80
    sub       r6, r6, #0x80
    add       r7, r3, r6
    sub       r6, r5, r6
    add       r6, r6, r3
    sub       r5, r6, r5, lsl #1
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    sub       r4, r4, #4
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #1
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [r2], #4
    sub       r4, r4, #4
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #-0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [lr], #4
    ldrb      r5, [r1], #0x80
    ldrb      r6, [r1], #-0x7f
    ldrb      r4, [r0], #1
    sub       r5, r5, #0x80
    sub       r6, r6, #0x80
    add       r7, r3, r6
    sub       r6, r5, r6
    add       r6, r6, r3
    sub       r5, r6, r5, lsl #1
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    sub       r4, r4, #4
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #1
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [r2], #4
    sub       r4, r4, #4
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #-0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [lr], #4
    ldrb      r5, [r1], #0x80
    ldrb      r6, [r1], #-0x7f
    ldrb      r4, [r0], #1
    sub       r5, r5, #0x80
    sub       r6, r6, #0x80
    add       r7, r3, r6
    sub       r6, r5, r6
    add       r6, r6, r3
    sub       r5, r6, r5, lsl #1
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    sub       r4, r4, #4
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #1
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [r2], #4
    sub       r4, r4, #4
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #-0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [lr], #4
    ldrb      r5, [r1], #0x80
    ldrb      r6, [r1], #-0x7f
    ldrb      r4, [r0], #1
    sub       r5, r5, #0x80
    sub       r6, r6, #0x80
    add       r7, r3, r6
    sub       r6, r5, r6
    add       r6, r6, r3
    sub       r5, r6, r5, lsl #1
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    sub       r4, r4, #4
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #1
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [r2], #4
    sub       r4, r4, #4
    ldrb      r8, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    ldrb      r4, [r0], #-0xff
    add       r8, r11, r8, lsl #5
    add       r8, r8, r12, lsl #10
    orr       r8, r8, #0x8000
    ldrb      r9, [r7, r4]
    ldrb      r11, [r6, r4]
    ldrb      r12, [r5, r4]
    add       r8, r8, r9, lsl #21
    add       r8, r8, r11, lsl #16
    add       r8, r8, r12, lsl #26
    orr       r8, r8, #0x80000000
    str       r8, [lr], #4
    subs      r10, r10, #0x10
    bgt       L048
    ldr       r10, [sp], #4
    ldr       r5, [sp]
    ldr       r6, [sp, #4]
    ldr       r7, [sp, #8]
    add       r0, r0, r5
    add       r1, r1, r6
    add       r2, r2, r7
    add       lr, lr, r7
    subs      r10, r10, #2
    bgt       L040
    add       sp, sp, #0x18
    ldmfd     sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, pc}
}
