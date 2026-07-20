/* Script-VM command handler, eleven operands into a 0x20 block.
 * Builder: func_ov015_020800d4.
 *
 * TWO optional operands here (type tags at descs+0x18 and descs+0x20), each a
 * ternary so both arms share one store. Note also that params.bField1c -- the
 * HIGHEST offset in the block -- is written THIRD, right after the target/id
 * fetches; the field order in the struct and the assignment order in the source
 * are independent, and following the ROM's assignment order is what matters.
 *
 * `id` truncates at the assignment (lsls/lsrs straight into r6) because the tag
 * tests intervene between its fetch and its use.
 */
typedef struct {
    int nField00;            /* +0x00 */
    int nField04;            /* +0x04 */
    int nField08;            /* +0x08 */
    unsigned char bField0c;  /* +0x0c */
    char pad0d[1];
    short nField0e;          /* +0x0e */
    short nField10;          /* +0x10 */
    short nField12;          /* +0x12 */
    unsigned char bField14;  /* +0x14 */
    char pad15[3];
    int nField18;            /* +0x18 */
    unsigned char bField1c;  /* +0x1c */
    char pad1d[3];
} Ov015EmitParams;           /* 0x20 */

extern int func_02021948(void *self, void *desc);
extern int func_02021980(void *self, void *desc);
extern int func_02021994(void *self, void *desc);
extern int func_ov015_020800d4(unsigned short id, Ov015EmitParams *params);
extern void func_ov002_0207643c(int target, int value);

int func_ov015_020822b0(void *self, char *descs) {
    Ov015EmitParams params;
    int target;
    unsigned short id;

    target = func_02021980(self, descs);
    id = func_02021980(self, descs + 0x8);
    params.bField1c = func_02021980(self, descs + 0x10);
    params.nField00 = (*(short *)(descs + 0x18) == 0)
                      ? 0 : func_02021948(self, descs + 0x18);
    params.nField04 = (*(short *)(descs + 0x20) == 0)
                      ? 0 : func_02021948(self, descs + 0x20);
    params.nField08 = func_02021994(self, descs + 0x28);
    params.bField0c = func_02021980(self, descs + 0x30);
    params.nField0e = func_02021994(self, descs + 0x38);
    params.nField10 = func_02021994(self, descs + 0x40);
    params.nField12 = func_02021994(self, descs + 0x48);
    params.bField14 = func_02021980(self, descs + 0x50);
    params.nField18 = func_02021980(self, descs + 0x58);
    func_ov002_0207643c(target, func_ov015_020800d4(id, &params));
    return 1;
}
