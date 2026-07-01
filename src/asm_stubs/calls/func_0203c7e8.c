/* func_0203c7e8 (ARM): refcount-decrement + free node helper.
 *   p = obj[0]; if (p) { c=p->[+0x60]; if (c) p->[+0x60] = c-1; }
 *   cb = obj[+0x64]; if (cb) cb(obj);
 *   (*data_0204caa8)--; func_0203d194(obj);
 */
extern void func_0203d194(void *p);
extern int  *data_0204caa8;

asm void func_0203c7e8(void *obj)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    ldr   r1, [r4]
    cmp   r1, #0
    ldrneb r0, [r1, #0x60]
    cmpne r0, #0
    subne r0, r0, #1
    strneb r0, [r1, #0x60]
    ldr   r1, [r4, #0x64]
    cmp   r1, #0
    beq   nocb
    mov   r0, r4
    blx   r1
nocb:
    ldr   r1, =data_0204caa8
    mov   r0, r4
    ldr   r2, [r1]
    sub   r2, r2, #1
    str   r2, [r1]
    bl    func_0203d194
    ldmia sp!, {r4, pc}
}
