extern int func_02030670(void);
extern int func_02001030(void);

asm int func_020306b4(void)
{
    stmdb sp!, {r4, lr}
    mov r4, #0
    bl func_02030670
    cmp r0, #0
    moveq r0, r4
    ldmeqia sp!, {r4, pc}
    bl func_02001030
    cmp r0, #9
    bgt check10
    bge set1
    cmp r0, #1
    bgt end
    cmp r0, #0
    blt end
    cmpne r0, #1
    beq set1
    b end
check10:
    cmp r0, #0xa
    bne end
set1:
    mov r4, #1
end:
    mov r0, r4
    ldmia sp!, {r4, pc}
}
