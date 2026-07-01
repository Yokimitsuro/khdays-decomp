extern void *func_01fffd70(void *list);
extern void  func_0203c424(void *self);
extern void  NNSi_FndDestroyDoubleList(void *list);
extern void  func_0203d194(void *p);

asm void func_0203c468(void *self)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    bl    func_01fffd70
    movs  r1, r0
    beq   done
loop:
    mov   r0, r4
    bl    func_0203c424
    mov   r0, r4
    bl    func_01fffd70
    movs  r1, r0
    bne   loop
done:
    mov   r0, r4
    bl    NNSi_FndDestroyDoubleList
    mov   r0, r4
    bl    func_0203d194
    ldmia sp!, {r4, pc}
}
