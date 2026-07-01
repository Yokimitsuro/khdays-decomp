extern void func_02015b70(void);
extern int data_02047394[];
extern void *data_020474cc;

asm void *func_02015c00(void)
{
    stmdb sp!, {r3, lr}
    ldr   r0, =data_02047394
    ldr   r0, [r0, #0xd4]
    tst   r0, #0x80
    bne   _skip
    bl    func_02015b70
    ldr   r0, =data_02047394
    ldr   r1, [r0, #0xd4]
    orr   r1, r1, #0x80
    str   r1, [r0, #0xd4]
_skip:
    ldr   r0, =data_020474cc
    ldmia sp!, {r3, pc}
}
