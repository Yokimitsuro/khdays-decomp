/* c634 handler: query func_ov107_020cab14; if 0, latch owner->+0x1c7 = 2 and
 * dispatch null cb. Otherwise build a transform (func_0203cd7c into a stack buffer,
 * then func_0202ea48 into obj+0x38), set obj->f10 = -0x200, and if either owner bit
 * (+0x17a / +0x17c bit0) is set, OR 0xc into owner->+0x1b0 and dispatch cb. */
extern int func_ov107_020cab14(int owner, int a);
extern void func_0203c634(int self, int index, void *cb);
extern void func_0203cd7c(void *buf, int a, int b, void *data);
extern void func_0202ea48(int dst, void *buf);
extern void func_ov213_020ce784(void);
extern int data_02042264;
struct bit0 { unsigned char b:1; };
void func_ov213_020ce6b0(int self) {
    int obj = *(int *)(self + 4);
    int buf[9];
    *(int *)(obj + 0x24) = func_ov107_020cab14(*(int *)obj, 0);
    if (*(int *)(obj + 0x24) == 0) {
        *(unsigned char *)(*(int *)obj + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    func_0203cd7c(buf, *(int *)(obj + 0x24) + 0x74, *(int *)obj + 0x74, &data_02042264);
    func_0202ea48(obj + 0x38, buf);
    *(int *)(obj + 0x10) = -0x200;
    if (((struct bit0 *)(*(int *)obj + 0x17a))->b == 0 &&
        ((struct bit0 *)(*(int *)obj + 0x17c))->b == 0) {
        return;
    }
    *(unsigned short *)(*(int *)obj + 0x1b0) |= 0xc;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov213_020ce784);
}
