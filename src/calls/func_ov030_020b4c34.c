extern void func_0202a7dc(void *p);
extern void func_ov030_020b3edc(void *p);

asm void func_ov030_020b4c34(void *r0)
{
    push    {r4, lr}
    mov     r4, r0
    add     r0, #0x18
    bl      func_0202a7dc
    mov     r0, #0x4a
    lsl     r0, r0, #0x2
    add     r0, r4, r0
    bl      func_0202a7dc
    mov     r0, r4
    bl      func_ov030_020b3edc
    pop     {r4, pc}
}
