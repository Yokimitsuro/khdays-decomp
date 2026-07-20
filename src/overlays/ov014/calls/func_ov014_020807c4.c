/* Script-VM command handler (see tools/gen_vm_emit.py for the family skeleton),
 * with one wrinkle the pure members do not have: the first operand is OPTIONAL.
 *
 * Each descriptor starts with a 16-bit type tag, and tag 0 means "absent" -- so
 * this command reads the tag at descs+0x10 directly and substitutes 0 rather
 * than calling the fetcher. It must be a ternary, not an if/else: the ROM shares
 * ONE store between both arms, and an if/else emits two.
 *
 * Note also that `id` is declared `unsigned short` here where the pure members
 * need `int` plus a cast at the call. Both spellings are right in their place --
 * mwcc truncates where you write the conversion, so when code intervenes between
 * the fetch and the use (the conditional, here) the ROM truncates at the
 * assignment, and when the fetch is adjacent to the use it truncates there.
 */
typedef struct {
    int nField00;            /* +0x00 */
    int nField04;            /* +0x04 */
    int nField08;            /* +0x08 */
} Ov014EmitParams;           /* 0xc */

extern int func_02021948(void *self, void *desc);
extern int func_02021980(void *self, void *desc);
extern int func_02021994(void *self, void *desc);
extern int func_ov014_02080540(unsigned short id, Ov014EmitParams *params);
extern void func_ov002_0207643c(int target, int value);

int func_ov014_020807c4(void *self, char *descs) {
    Ov014EmitParams params;
    int target;
    unsigned short id;

    target = func_02021980(self, descs);
    id = func_02021980(self, descs + 0x8);
    params.nField00 = (*(short *)(descs + 0x10) == 0)
                      ? 0 : func_02021948(self, descs + 0x10);
    params.nField04 = func_02021994(self, descs + 0x18);
    params.nField08 = func_02021994(self, descs + 0x20);
    func_ov002_0207643c(target, func_ov014_02080540(id, &params));
    return 1;
}
