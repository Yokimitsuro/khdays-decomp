/* NitroSDK original assembly: returns a lock id to the free pool.
 *
 * A set bit means the id is free again. Ids 0x40 to 0x5f live in the first flag
 * word and 0x60 to 0x6f in the second, and the bit position is
 * 0x80000000 >> (id - base), the same encoding OS_GetLockID scans with CLZ.
 *
 * Not a decompilation, and the same idiom as its allocator sibling. The shift is
 * left standing in its own register, where mwccarm always folds it into the
 * barrel shifter of the instruction that consumes it. That fold survived every
 * axis tried: eight ways of forcing the shifted value into its own register,
 * five condition spellings, four tail spellings, operand order, a volatile
 * declaration of the shared table, five parameter widths, an enum parameter,
 * five optimisation settings, eight processor cost models, sixty-three pragma
 * combinations, five helper and argument formulations, and all 26 compiler
 * builds, which give byte-identical output. Across the image 165 functions
 * already matched as real C fold the shift and none leaves it standing; the
 * unfolded form survives in exactly two, this one and OS_GetLockID. The ROM also
 * predicates on the sign flag, which a signed comparison in C will not produce.
 * See codegen-cracks.md.
 */

asm void OS_ReleaseLockID(int nLockId)
{
    ldr     r3, =0x027fffb0
    cmp     r0, #0x60
    addpl   r3, r3, #4
    subpl   r0, r0, #0x60
    submi   r0, r0, #0x40
    mov     r1, #0x80000000
    mov     r1, r1, lsr r0
    ldr     r2, [r3]
    orr     r2, r2, r1
    str     r2, [r3]
    bx      lr
}
