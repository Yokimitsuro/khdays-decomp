extern int func_020093e8(int a, int b, int c, int d, int e);

asm void PXIi_SendCommand(int arg0)
{
    stmdb sp!, {r4, r5, r6, lr}
    mov r6, r0
    mov r5, #8
    mov r4, #0
_loop:
    mov r0, r5
    mov r1, r6
    mov r2, r4
    bl  func_020093e8
    cmp r0, #0
    bne _loop
    ldmia sp!, {r4, r5, r6, pc}
}
