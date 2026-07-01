extern int strncmp(void *a, void *b, int n);

asm void *func_02028df0(void *p, void *key)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, sb, lr}
    ldrh r8, [r0, #0x82]
    mov sb, r1
    mov r5, #0
    cmp r8, #0
    ble end
    ldr r7, [r0, #0xac]
    mov r4, #0xc
    mov r6, r7
loop:
    mov r0, r6
    mov r1, sb
    mov r2, r4
    bl strncmp
    cmp r0, #0
    moveq r0, #0x14
    mlaeq r0, r5, r0, r7
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, sb, pc}
    add r5, r5, #1
    cmp r5, r8
    add r6, r6, #0x14
    blt loop
end:
    mov r0, #0
    ldmia sp!, {r3, r4, r5, r6, r7, r8, sb, pc}
}
