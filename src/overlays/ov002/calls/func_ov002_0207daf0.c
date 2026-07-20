/* Script-VM command: resolve an entry by (id, param) and push a signed fx value to it.
 *
 * Reads three operands -- a u8 id, a u16 param, and an fx32 -- then resolves the target entry with
 * func_ov002_0207679c(id, param) and applies (short)fx via func_ov002_0207a784(entry, 1, v). The
 * middle operand is NOT discarded (Ghidra dropped it): it is the second argument to the resolver.
 */

extern int func_02021980(int self, unsigned short *operand);
extern int func_02021994(int self, unsigned short *operand);
extern void *func_ov002_0207679c(unsigned char id, unsigned short param);
extern void func_ov002_0207a784(void *entry, int a, short value);

int func_ov002_0207daf0(int self, unsigned short *op) {
    int id = func_02021980(self, op);
    int param = func_02021980(self, op + 4);
    int value = func_02021994(self, op + 8);

    func_ov002_0207a784(
        func_ov002_0207679c((unsigned char)id, (unsigned short)param), 1,
        (short)value);
    return 1;
}
