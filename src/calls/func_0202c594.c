extern int func_02028724(void *p);

asm void func_0202c594(unsigned char *arg0)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    add r0, r4, #0xc
    bl func_02028724
    cmp r0, #0
    ldrneb r1, [r4, #8]
    orrne r1, r1, #0x41
    strneb r1, [r4, #8]
    ldmia sp!, {r4, pc}
}
