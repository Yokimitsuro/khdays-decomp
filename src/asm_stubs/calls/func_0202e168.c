extern void func_0202e0ec(void);

asm void func_0202e168(void *p, int arg1)
{
    mov  r3, #0
    str  r3, [r0]
    str  r1, [r0, #8]
    str  r3, [r0, #0x10]
    mov  r2, #0x7f
    strb r2, [r0, #0x18]
    mov  r2, #0x1000
    str  r2, [r0, #4]
    ldr  ip, =func_0202e0ec
    str  r3, [r0, #0x14]
    bx   ip
}
