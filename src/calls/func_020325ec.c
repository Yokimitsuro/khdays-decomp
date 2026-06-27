extern void func_020124b8(int a, int b);

asm void func_020325ec(int arg0, int arg1, int arg2)
{
    stmdb sp!, {r3, lr}
    cmp r1, #0
    ldmltia sp!, {r3, pc}
    add r3, r0, #0x18
    mov r0, #0x8c
    mla r0, r1, r0, r3
    mov r1, r2
    bl  func_020124b8
    ldmia sp!, {r3, pc}
}
