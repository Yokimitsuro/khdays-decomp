extern int  func_02011390(void *p);
extern int  func_02011358(void *p, unsigned short v);

asm void func_02011558(void *p)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    bl    func_02011390
    cmp   r0, #0
    movne r0, #0
    ldmneia sp!, {r4, pc}
    ldrh  r1, [r4, #8]
    mov   r0, r4
    bl    func_02011358
    strh  r0, [r4, #8]
    ldrh  r1, [r4, #0xc]
    mov   r0, #1
    sub   r1, r1, #1
    strh  r1, [r4, #0xc]
    ldmia sp!, {r4, pc}
}
