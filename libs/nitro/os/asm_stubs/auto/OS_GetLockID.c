/* NitroSDK original assembly: allocates a lock id from the two shared flag words.
 *
 * A set bit means the id is still free. OS_InitLock seeds the words with 0xffffffff
 * and 0xffff0000, so ids run from 0x40 to 0x6f; CLZ picks the highest free bit,
 * the bit is cleared, and 0xfffffffd, OS_LOCK_ID_ERROR, comes back when both words
 * are full.
 *
 * Not a decompilation. Two separate instructions here are unreachable from C with
 * this toolchain. The count itself has no intrinsic: __builtin_clz, __clz, _clz,
 * __CLZ, __count_leading_zeros and __cntlzw are all accepted only as implicit
 * external declarations and compile to a call. The flag clear needs bic with a
 * register operand, which no build emits: fourteen bit-clear idioms, the opaque
 * parameter case where a single bic would be strictly shorter, and all 26 compiler
 * builds in the tree all give mvn followed by and. Across the whole ARM9 image,
 * bic with an immediate appears in 6,919 functions already matched as real C and
 * bic with a register in none of them, occurring in only three places overall.
 * See codegen-cracks.md.
 */

asm void OS_GetLockID(void)
{
    ldr     r3, =0x027fffb0
    ldr     r1, [r3]
    clz     r2, r1
    cmp     r2, #0x20
    movne   r0, #0x40
    bne     @found
    add     r3, r3, #4
    ldr     r1, [r3]
    clz     r2, r1
    cmp     r2, #0x20
    ldr     r0, =0xfffffffd
    bxeq    lr
    mov     r0, #0x60
@found:
    add     r0, r0, r2
    mov     r1, #0x80000000
    mov     r1, r1, lsr r2
    ldr     r2, [r3]
    bic     r2, r2, r1
    str     r2, [r3]
    bx      lr
}
