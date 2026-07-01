/* Resolve & translate: handle->ctx; if (!ctx) return 0; ctx2 = *handle;
 * if (ctx2->byte_2d == 0) { *out = 0xFFFF; return 1; }
 * else                    { *out = (u16)func_02008d1c(ctx2->byte_3c); return 1; }
 * (Boolean success, halfword result via out-param.)
 */
extern int func_02008d1c(int v);

asm int func_0201a238(int **handle, int arg1, unsigned short *out)
{
    stmdb sp!, {r4, lr}
    ldr   r3, [r0]
    mov   r4, r2
    cmp   r3, #0
    moveq r0, #0
    ldmeqia sp!, {r4, pc}
    ldr   r2, [r0]
    ldrb  r0, [r2, #0x2d]
    cmp   r0, #0
    bne   slow
    mvn   r0, #0
    strh  r0, [r4]
    mov   r0, #1
    ldmia sp!, {r4, pc}
slow:
    ldrb  r0, [r2, #0x3c]
    bl    func_02008d1c
    strh  r0, [r4]
    mov   r0, #1
    ldmia sp!, {r4, pc}
}
