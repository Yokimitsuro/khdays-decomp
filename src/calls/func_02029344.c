/* 6-arg initializer (3 args via stack). Inits a player/handle slot:
 *   func_0202926c(slot, arg1, arg2);                  // base ctor (caller already pushed r3 etc)
 *   slot->kind_21   = 3;
 *   slot->vtbl_1c   = data_02042928;
 *   slot->field_38  = arg3;
 *   slot->field_3c  = stk0;
 *   slot->field_40  = stk1;
 *   slot->field_44  = stk2;
 *   return 1;
 */
extern void  func_0202926c(void *slot, int a, int b);
extern void *data_02042928;

asm int func_02029344(void *slot, int a, int b, int arg3 /* + 3 on stack */)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov   r5, r0
    mov   r4, r3
    bl    func_0202926c
    mov   r1, #3
    ldr   r0, =data_02042928
    strb  r1, [r5, #0x21]
    str   r0, [r5, #0x1c]
    ldr   r0, [sp, #0x10]
    str   r4, [r5, #0x38]
    ldr   r1, [sp, #0x14]
    str   r0, [r5, #0x3c]
    ldr   r0, [sp, #0x18]
    str   r1, [r5, #0x40]
    str   r0, [r5, #0x44]
    mov   r0, #1
    ldmia sp!, {r3, r4, r5, pc}
}
