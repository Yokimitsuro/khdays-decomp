/* func_02012da4 (ARM): sibling of func_02012d64; same shape, but with
 * table=data_02041a24 and callee=func_02012ca8.
 */
extern void *func_02012880(void *a, void *b, void *c);
extern int   func_02012ca8(void *a, void *b, int c, void *d, void *e);
extern char  data_02041a24[];
extern void *data_02047390;

asm void func_02012da4(void *a, void *b, void *c, void *d)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov   r5, r0
    ldr   r0, =data_02041a24
    mov   r4, r3
    bl    func_02012880
    ldr   r1, [sp, #0x10]
    ldr   r2, =data_02047390
    str   r1, [sp]
    ldrh  r1, [r0, #4]
    ldr   r2, [r2]
    mov   r0, r5
    mov   r3, r4
    bl    func_02012ca8
    ldmia sp!, {r3, r4, r5, pc}
}
