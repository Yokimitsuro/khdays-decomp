extern void WaitByLoop(int);
extern void func_020010c4(int, int);

asm void func_02003878(void)
{
    stmdb sp!, {r3, lr}
    mov r0, #1
    blx WaitByLoop
    mov r0, #1
    mov r1, r0
    bl func_020010c4
    ldmia sp!, {r3, pc}
}
