extern int data_0204bd88[];
extern int data_0204bd94[];

asm void func_02020888(int idx, int v1, int v2)
{
    ldr ip, =data_0204bd88
    ldr r3, =data_0204bd94
    str r1, [ip, r0, lsl #2]
    str r2, [r3, r0, lsl #2]
    bx  lr
}
