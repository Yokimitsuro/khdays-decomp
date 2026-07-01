extern int WM_EndKeySharing_0x0202019c(void *a, void *b, unsigned int size);

asm void *func_02028d90(void *p, void *needle)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    mov r5, r0
    ldrh r0, [r5, #0x76]
    mov r4, r1
    mov r8, #0x0
    cmp r0, #0x0
    ble done
    mov r9, r8
    mov r6, #0x8
loop:
    ldr r7, [r5, #0x94]
    mov r1, r4
    mov r2, r6
    add r0, r7, r9
    bl WM_EndKeySharing_0x0202019c
    cmp r0, #0x0
    addeq r0, r7, r9
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    ldrh r0, [r5, #0x76]
    add r8, r8, #0x1
    add r9, r9, #0x18
    cmp r8, r0
    blt loop
done:
    mov r0, #0x0
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
