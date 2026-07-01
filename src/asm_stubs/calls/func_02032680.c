extern void func_020124d8(int a, int b);

asm void func_02032680(int arg0, int arg1, int arg2)
{
    stmdb sp!, {r3, lr}
    add r3, r0, #4
    mov r0, #0x8c
    mla r0, r1, r0, r3
    cmp r1, #0
    ldmltia sp!, {r3, pc}
    mov r1, r2
    add r0, r0, #0x14
    bl  func_020124d8
    ldmia sp!, {r3, pc}
}
