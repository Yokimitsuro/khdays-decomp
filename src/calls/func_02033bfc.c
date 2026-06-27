extern void func_0201a0fc(int a, int b);
extern int *data_0204c234;

asm void func_02033bfc(int arg0)
{
    ldr r1, =data_0204c234
    ldr r2, =0xb44c8
    ldr r3, [r1]
    ldr ip, =func_0201a0fc
    mov r1, r0
    add r0, r3, r2
    bx  ip
}
