/* SCRN chunk opener (NSCR Screen sub-chunk), sibling of FindNitroChunk family. Slim 2-reg variant. */
extern void *func_02011aa0(void *a, int magic);

asm void func_02011a6c(void *a, void **out)
{
    stmdb sp!, {r4, lr}
    mov   r4, r1
    ldr   r1, =0x5343524e
    bl    func_02011aa0
    cmp   r0, #0
    moveq r0, #0
    streq r0, [r4]
    ldmeqia sp!, {r4, pc}
    add   r0, r0, #8
    str   r0, [r4]
    mov   r0, #1
    ldmia sp!, {r4, pc}
}
