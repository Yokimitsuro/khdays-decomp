extern void FS_LoadOverlay(void);
extern void FS_UnloadOverlay(void);
extern void OS_AllocFromArenaLo(void);
extern void OS_GetArenaLo(void);
extern void OS_GetArenaHi(void);
extern void NNS_FndCreateExpHeapEx(void);

asm void func_ov001_0204ce40(void *r0, void *r1)
{
    stmfd   sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    ldr     r4, [pc, #0x10c]
    mov     r7, #0
    mov     r6, r0
    mov     r5, r1
    mov     r0, r7
    mov     r1, r4
    mov     r8, r7
    bl      FS_LoadOverlay
    mov     r0, r7
    dcd     0xeb00f988
    cmp     r0, #0
    beq     _L_0x54
    mov     r0, r7
    mov     r1, #0xc8000
    mov     r2, #0x10
    bl      OS_AllocFromArenaLo
    mov     r1, #0xc8000
    mov     r2, r7
    bl      NNS_FndCreateExpHeapEx
    mov     r7, r0
_L_0x54:
    mov     r0, #0
    bl      OS_GetArenaLo
    add     r1, r0, #0xf
    mov     r0, #0
    bic     r9, r1, #0xf
    bl      OS_GetArenaHi
    bic     r10, r0, #0xf
    mov     r0, #0
    dcd     0xeb00f8d1
    cmp     r0, #0
    bne     _L_0x90
    mov     r0, #0
    dcd     0xeb00f85d
    cmp     r0, #0
    beq     _L_0xbc
_L_0x90:
    sub     r0, r10, r9
    mov     r8, r0, lsr #1
    mov     r1, r8
    mov     r0, #0
    mov     r2, #0x10
    bl      OS_AllocFromArenaLo
    mov     r1, r8
    mov     r2, #0
    bl      NNS_FndCreateExpHeapEx
    mov     r8, r0
    b       _L_0x100
_L_0xbc:
    mov     r0, #0
    dcd     0xeb00f886
    cmp     r0, #0
    beq     _L_0x100
    mov     r0, #0
    dcd     0xeb00f8f2
    cmp     r0, #0
    beq     _L_0x100
    sub     r8, r10, r9
    mov     r1, r8
    mov     r0, #0
    mov     r2, #0x10
    bl      OS_AllocFromArenaLo
    mov     r1, r8
    mov     r2, #0
    bl      NNS_FndCreateExpHeapEx
    mov     r8, r0
_L_0x100:
    mov     r1, r4
    mov     r0, #0
    bl      FS_UnloadOverlay
    str     r7, [r6]
    str     r8, [r5]
    ldmfd   sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
    dcd     0x0000001c
}
