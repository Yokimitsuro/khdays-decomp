/* Script-VM command handler with a VARIABLE-LENGTH operand list: three fixed
 * operands, then a signed count, then that many 8-byte descriptors gathered into
 * an array. (Family skeleton: tools/gen_vm_emit.py.)
 *
 * Three things here that the fixed-shape members do not show:
 *
 *   The count at params+6 is re-read from memory on EVERY iteration (ldrsb), so
 *   it must stay a struct field read in the loop condition -- caching it in a
 *   local costs the reload.
 *
 *   `descs` is reused as the cursor. Introducing a separate pointer variable
 *   makes mwcc keep both live and spill `self` to the stack, which is +2 bytes
 *   and a different register assignment throughout the loop.
 *
 *   pCountDesc exists only to control SCHEDULING. The ROM computes the count
 *   descriptor's address, THEN advances descs, THEN calls -- and mwcc will only
 *   emit that order if the argument is already in a temp when the increment is
 *   written. With `f(self, descs + 0x20); descs += 0x28;` the increment sinks
 *   past the call and the ldrsb. Same instructions either way; only the position
 *   of `adds r5, #0x28` differs.
 */
typedef struct {
    int nField00;              /* +0x00 */
    short nField04;            /* +0x04 */
    signed char nCount;        /* +0x06 */
    char pad07[1];
    int aItems[7];             /* +0x08 -- extent bounded by the 0x24 frame slot */
} Ov002ListParams;             /* 0x24 */

extern int func_02021948(void *self, void *desc);
extern int func_02021980(void *self, void *desc);
extern int func_02021994(void *self, void *desc);
extern int func_ov002_0207bc64(unsigned short id, Ov002ListParams *params);
extern void func_ov002_0207643c(int target, int value);

int func_ov002_0207d610(void *self, char *descs) {
    Ov002ListParams params;
    int target;
    int id;
    int i;
    char *pCountDesc;

    target = func_02021980(self, descs);
    id = func_02021980(self, descs + 0x8);
    params.nField00 = func_02021948(self, descs + 0x10);
    params.nField04 = func_02021994(self, descs + 0x18);
    pCountDesc = descs + 0x20;
    descs += 0x28;
    params.nCount = func_02021980(self, pCountDesc);
    for (i = 0; i < params.nCount; i++) {
        params.aItems[i] = func_02021948(self, descs);
        descs += 8;
    }
    func_ov002_0207643c(target, func_ov002_0207bc64((unsigned short)id, &params));
    return 1;
}
