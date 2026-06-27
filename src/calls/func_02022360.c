extern void func_02021980(int arg);
extern void func_020336a4(void);
extern signed char data_020425e8;

asm int func_02022360(int arg0)
{
    push {r3, lr}
    bl  func_02021980
    mov r2, #0
    ldr  r1, =data_020425e8
    mvn r2, r2
    strb r2, [r1]
    bl  func_020336a4
    mov r0, #1
    pop  {r3, pc}
}
