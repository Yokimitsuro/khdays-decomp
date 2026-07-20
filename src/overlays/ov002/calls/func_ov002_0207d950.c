/* Script-VM command handler, twelve operands into a 0x1c block.
 * Builder: func_ov002_0207c2c8.
 *
 * Hand-written rather than generated, and it needed no iteration because it is
 * two already-known wrinkles stacked:
 *   - the first operand is OPTIONAL (16-bit type tag at descs+0x10, 0 = absent),
 *     which must be a ternary so both arms share one store;
 *   - `id` is truncated at the ASSIGNMENT here (lsls/lsrs straight into r6),
 *     because the tag test intervenes between the fetch and the use.
 * See tools/gen_vm_emit.py and the family notes for both.
 */
typedef struct {
    int nField00;            /* +0x00 */
    int nField04;            /* +0x04 */
    unsigned char bField08;  /* +0x08 */
    char pad09[1];
    short nField0a;          /* +0x0a */
    short nField0c;          /* +0x0c */
    short nField0e;          /* +0x0e */
    short nField10;          /* +0x10 */
    short nField12;          /* +0x12 */
    unsigned char bField14;  /* +0x14 */
    char pad15[1];
    short nField16;          /* +0x16 */
    short nField18;          /* +0x18 */
    unsigned char bField1a;  /* +0x1a */
    char pad1b[1];
} Ov002EmitParams1c;         /* 0x1c */

extern int func_02021948(void *self, void *desc);
extern int func_02021980(void *self, void *desc);
extern int func_02021994(void *self, void *desc);
extern int func_ov002_0207c2c8(unsigned short id, Ov002EmitParams1c *params);
extern void func_ov002_0207643c(int target, int value);

int func_ov002_0207d950(void *self, char *descs) {
    Ov002EmitParams1c params;
    int target;
    unsigned short id;

    target = func_02021980(self, descs);
    id = func_02021980(self, descs + 0x8);
    params.nField00 = (*(short *)(descs + 0x10) == 0)
                      ? 0 : func_02021948(self, descs + 0x10);
    params.nField04 = func_02021994(self, descs + 0x18);
    params.bField08 = func_02021980(self, descs + 0x20);
    params.nField0a = func_02021994(self, descs + 0x28);
    params.nField0c = func_02021994(self, descs + 0x30);
    params.nField0e = func_02021994(self, descs + 0x38);
    params.nField10 = func_02021980(self, descs + 0x40);
    params.nField12 = func_02021980(self, descs + 0x48);
    params.bField14 = func_02021980(self, descs + 0x50);
    params.nField16 = func_02021980(self, descs + 0x58);
    params.nField18 = func_02021980(self, descs + 0x60);
    params.bField1a = func_02021980(self, descs + 0x68);
    func_ov002_0207643c(target, func_ov002_0207c2c8(id, &params));
    return 1;
}
