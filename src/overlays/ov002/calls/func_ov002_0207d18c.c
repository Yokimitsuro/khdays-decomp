/* Script-VM command handler (family skeleton: tools/gen_vm_emit.py).
 * Builder: func_ov002_02079c94.
 *
 * Seven operands into a 0x18 block whose middle is three consecutive SHORTS
 * (+0x04/+0x06/+0x08) followed by two words and a trailing byte -- the mixed
 * widths are what the generator reads off the str/strh/strb it sees, and they
 * are why the block is 0x18 rather than 0x1c despite having the same operand
 * count as the wider members. */
typedef struct {
    int nField00;            /* +0x00 */
    short nField04;          /* +0x04 */
    short nField06;          /* +0x06 */
    short nField08;          /* +0x08 */
    char pad0a[2];
    int nField0c;            /* +0x0c */
    int nField10;            /* +0x10 */
    unsigned char bField14;  /* +0x14 */
    char pad15[3];
} Ov002EmitParams18;         /* 0x18 */

extern int func_02021948(void *self, void *desc);
extern int func_02021980(void *self, void *desc);
extern int func_02021994(void *self, void *desc);
extern int func_ov002_02079c94(unsigned short id, Ov002EmitParams18 *params);
extern void func_ov002_0207643c(int target, int value);

int func_ov002_0207d18c(void *self, char *descs) {
    Ov002EmitParams18 params;
    int target;
    int id;

    params.nField00 = func_02021948(self, descs + 0x10);
    params.nField04 = func_02021980(self, descs + 0x18);
    params.nField06 = func_02021980(self, descs + 0x20);
    params.nField08 = func_02021980(self, descs + 0x28);
    params.nField0c = func_02021994(self, descs + 0x30);
    params.nField10 = func_02021994(self, descs + 0x38);
    params.bField14 = func_02021980(self, descs + 0x40);
    target = func_02021980(self, descs);
    id = func_02021980(self, descs + 0x8);
    func_ov002_0207643c(target, func_ov002_02079c94((unsigned short)id, &params));
    return 1;
}
