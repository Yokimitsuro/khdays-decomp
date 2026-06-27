extern void func_ov098_020bb928(void *, void *, int);
extern void func_ov098_020bb99c(void *, void *);

asm void func_ov098_020bac04(char *)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r5, r0
    add r1, r5, #0x2a00
    ldrsh r2, [r1, #0xba]
    add r4, r5, #0x2c
    add r1, r4, #0x2c00
    bl func_ov098_020bb928
    mov r0, r5
    add r1, r4, #0x2c00
    bl func_ov098_020bb99c
    ldmia sp!, {r3, r4, r5, pc}
}
