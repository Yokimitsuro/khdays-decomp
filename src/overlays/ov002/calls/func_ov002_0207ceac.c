/* Script-VM command handler (family skeleton: tools/gen_vm_emit.py).
 * Builder: func_ov002_020772c4.
 *
 * One field is NOT fed by a fetcher: params.bField11 is a literal 0, stored
 * right after the last operand and before the target/id fetches. The generator
 * cannot see fields like that -- it only knows about slots written from a
 * fetcher's return value -- so it produced C that was 4 bytes short with every
 * instruction otherwise correct. Worth knowing for the rest of the family:
 * a small, otherwise-inexplicable size gap in a generated member is more likely
 * a constant-initialised field than a codegen problem.
 */
typedef struct {
    int nField00;            /* +0x00 */
    short nField04;          /* +0x04 */
    short nField06;          /* +0x06 */
    int nField08;            /* +0x08 */
    int nField0c;            /* +0x0c */
    unsigned char bField10;   /* +0x10 */
    unsigned char bField11;   /* +0x11 -- literal 0, not from a fetcher */
    short nField12;          /* +0x12 */
    short nField14;          /* +0x14 */
    short nField16;          /* +0x16 */
} Ov002EmitParams;          /* 0x18 */

extern int func_02021948(void *self, void *desc);
extern int func_02021980(void *self, void *desc);
extern int func_02021994(void *self, void *desc);
extern int func_ov002_020772c4(unsigned short id, Ov002EmitParams *params);
extern void func_ov002_0207643c(int target, int value);

int func_ov002_0207ceac(void *self, char *descs) {
    Ov002EmitParams params;
    int target;
    int id;

    params.nField00 = func_02021948(self, descs + 0x10);
    params.nField04 = func_02021980(self, descs + 0x18);
    params.nField06 = func_02021980(self, descs + 0x20);
    params.nField08 = func_02021994(self, descs + 0x28);
    params.nField0c = func_02021994(self, descs + 0x30);
    params.bField10 = func_02021980(self, descs + 0x38);
    params.nField12 = func_02021994(self, descs + 0x40);
    params.nField14 = func_02021994(self, descs + 0x48);
    params.nField16 = func_02021994(self, descs + 0x50);
    params.bField11 = 0;
    target = func_02021980(self, descs);
    id = func_02021980(self, descs + 0x8);
    func_ov002_0207643c(target, func_ov002_020772c4((unsigned short)id, &params));
    return 1;
}
