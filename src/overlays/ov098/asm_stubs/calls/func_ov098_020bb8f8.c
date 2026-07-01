extern void func_ov098_020bb5dc(void *);

asm void func_ov098_020bb8f8(void *, int *)
{
    stmdb sp!, {r4, lr}
    mov r4, r1
    ldr r1, [r4]
    cmp r1, #0
    cmpne r1, #2
    ldmneia sp!, {r4, pc}
    cmp r1, #0
    bne done_call
    bl func_ov098_020bb5dc
done_call:
    mov r0, #1
    str r0, [r4]
    ldmia sp!, {r4, pc}
}
