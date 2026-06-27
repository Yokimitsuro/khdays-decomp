extern void *func_02012880(void *a, void *b, void *c);
extern int   func_02012b98(void *a, void *b, void *c, int d, void *e);
extern char  data_02041a54[];

asm void func_02012d24(void *a, void *b, void *c, void *d)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov   r5, r0
    mov   r4, r1
    mov   r1, r2
    ldr   r0, =data_02041a54
    mov   r2, r3
    bl    func_02012880
    ldr   r1, [sp, #0x14]
    ldr   r3, [sp, #0x10]
    str   r1, [sp]
    ldrh  r1, [r0, #4]
    mov   r0, r5
    mov   r2, r4
    bl    func_02012b98
    ldmia sp!, {r3, r4, r5, pc}
}
