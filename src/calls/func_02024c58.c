extern void *func_0201ef9c(void *a, void *b);
extern int   func_02011a20(void *a, void *b);
extern void  NNSi_FndFreeFromDefaultHeap(void *p);

asm void *func_02024c58(void *self, void *a, void *b)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov   r5, r0
    mov   r0, r1
    mov   r1, r2
    bl    func_0201ef9c
    movs  r4, r0
    beq   end
    mov   r1, r5
    bl    func_02011a20
    cmp   r0, #0
    mov   r0, r4
    ldmneia sp!, {r3, r4, r5, pc}
    bl    NNSi_FndFreeFromDefaultHeap
end:
    mov   r0, #0
    ldmia sp!, {r3, r4, r5, pc}
}
