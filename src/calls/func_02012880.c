/* 5-arg trampoline target (caller func_02012d24): scans 4-entry table of (u16,u16,...) at r0,
 * each 6 bytes; if (r1<=tbl[i].h0 && r2<=tbl[i].h1) returns &tbl[0]+i*6 (=&tbl[i]);
 * otherwise returns &tbl[0]+0x12 (end-of-table marker, last entry +6).
 */
asm void *func_02012880(void *table, int x, int y)
{
    stmdb sp!, {r3, lr}
    mov   lr, r0
    mov   ip, #0
loop:
    ldrh  r3, [lr]
    cmp   r1, r3
    ldrleh r3, [lr, #2]
    cmple r2, r3
    movle r1, #6
    mlale r0, ip, r1, r0
    ldmleia sp!, {r3, pc}
    add   ip, ip, #1
    cmp   ip, #4
    add   lr, lr, #6
    blt   loop
    add   r0, r0, #0x12
    ldmia sp!, {r3, pc}
}
