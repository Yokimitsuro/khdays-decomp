/* MobiClip: turn one decoded frame into 15-bit pixels, two rows at a time.
 *
 * The colour space is YCoCg, not YUV. One lookup block holds the saturating
 * ramp, and the three channels are three windows into it, displaced by the
 * chroma pair so that indexing a window with the luma performs the colour
 * conversion and the clamp in one byte load:
 *
 *     green  = pTable + Cg              G = Y + Cg
 *     red    = pTable + Co - Cg         R = Y + Co - Cg
 *     blue   = red    - 2 * Co          B = Y - Co - Cg
 *
 * Note the order the assembly computes them in: the FIRST window it builds is
 * green, not red. Getting this backwards swaps red and green in the port while
 * still looking self-consistent, which is the same class of mistake that gave
 * the FFmpeg-based dumps their colour cast.
 *
 * The two chroma planes sit 128 bytes apart inside one 256-byte chroma row --
 * Co then Cg -- which is why the routine reads them by stepping one pointer
 * +0x80 and then -0x7f, landing on the next quad.
 *
 * Each chroma sample covers a 2x2 luma quad. The quad is dithered on a
 * checkerboard: the two pixels on the anti-diagonal, (row, col+1) and
 * (row+1, col), index the ramp four levels lower. Each quad emits two words,
 * one per destination row, each holding two horizontally adjacent pixels as
 * 0x8000 | R | G<<5 | B<<10 in each half. The inner loop covers sixteen
 * columns as eight unrolled quads; the outer steps down two rows.
 *
 * HAND-WRITTEN ARM in the original, not compiler output, and the evidence is a
 * complete classification rather than a sample. Across all 21031 ARM functions
 * in the ROM, 426 save the full set of callee-saved registers WITHOUT ip, so
 * saving ip is not this compiler's stack-alignment pad. Exactly seven functions
 * save ip: five are the hand-written 64-bit division helpers, one is a
 * hand-written SHA-1 block transform, and the seventh is this routine. It also
 * reads the chroma pair with two consecutive post-indexed byte loads through
 * one pointer, an idiom that occurs exactly once in the ROM -- here -- and in
 * none of the reconstructed sources; every C spelling tried folds it into a
 * displaced load plus one increment, volatile and maximum register pressure
 * included. A semantically complete candidate was then run through all 26
 * compilers in the tree, 15 flag variants and 150 pragma settings: none
 * reproduces either signature, and the closest is 1528 bytes against 1472.
 *
 * Every word below is one readable mnemonic: no incbin, no .inst, no opcode
 * words. Assembles byte-exact, 1472 bytes, zero relocations. Re-validate with
 * `python tools/gen_asm_stub.py <function> --check <this file>`, and keep this
 * header: the algorithm belongs here, not only in the assembly. The Ghidra
 * function MobiClip_BlitRows carries the same notes and the field names.
 *
 * Reference implementation, for the port. Semantically equivalent; it is not
 * what the original was compiled from, and it does not assemble to these bytes.
 *
 *     view: pLuma, pChroma, pDest, nStride, nWidth, nHeight, pTable
 *
 *     pTable += 0x100;                       // ramp is indexed signed
 *     pRow0 = (u16 *)pDest;
 *     pRow1 = (u16 *)((u8 *)pDest + nStride);
 *     nLumaGap   = 0x200 - nWidth;           // two luma rows of 256
 *     nChromaGap = 0x100 - (nWidth >> 1);    // one chroma row of 256
 *     nDestGap   = (nStride - nWidth) * 2;
 *
 *     y = nHeight;
 *     do {
 *         x = nWidth;
 *         do {                               // eight of these unrolled
 *             int co = *pChroma - 0x80; pChroma += 0x80;
 *             int cg = *pChroma - 0x80; pChroma -= 0x7f;
 *             const u8 *pG = pTable + cg;
 *             const u8 *pR = pTable + co - cg;
 *             const u8 *pB = pR - co * 2;
 *
 *             int y00 = pLuma[0],       y01 = pLuma[1];
 *             int y10 = pLuma[0x100],   y11 = pLuma[0x101];
 *             pLuma += 2;
 *             y01 -= 4;  y10 -= 4;           // checkerboard dither
 *
 *             #define PIX(l)  (0x8000u | pR[l] | (pG[l] << 5) | (pB[l] << 10))
 *             *pRow0++ = PIX(y00);  *pRow0++ = PIX(y01);
 *             *pRow1++ = PIX(y10);  *pRow1++ = PIX(y11);
 *
 *             x -= 2;
 *         } while (x > 0);
 *
 *         pLuma  += nLumaGap;
 *         pChroma += nChromaGap;
 *         pRow0 += nDestGap >> 1;
 *         pRow1 += nDestGap >> 1;
 *         y -= 2;
 *     } while (y > 0);
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
