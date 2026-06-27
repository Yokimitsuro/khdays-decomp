extern void func_ov098_020bbbfc(void *);

asm void func_ov098_020bb99c(void *, char *)
{
    stmdb sp!, {r3, r4, r5, lr}
    add r5, r1, #0x14
    mov r4, #0
loop:
    mov r0, r5
    bl func_ov098_020bbbfc
    add r4, r4, #1
    cmp r4, #7
    add r5, r5, #0x10c
    blt loop
    ldmia sp!, {r3, r4, r5, pc}
}
