/* func_ov008_0205c458 -- ov008 teardown: release the two fixed surfaces (+0x380, +0x488), then each
 * of the twelve 0x108-byte row surfaces at +0x590 whose entry in data_ov008_0208f050 is
 * non-negative, and finally the two command lists at +0x1248 and +0x1270. */
extern void func_0202a7dc(int p);
extern void func_02011134(int p);
extern void func_02011320(int p);
extern int data_ov008_0208f050;

void func_ov008_0205c458(int obj) {
    int i;
    char *p;
    func_0202a7dc(obj + 0x380);
    func_0202a7dc(obj + 0x88 + 0x400);
    p = (char *)(obj + 0x590);
    i = 0;
    do {
        if (((int *)&data_ov008_0208f050)[i] >= 0) {
            func_0202a7dc((int)p);
        }
        i = i + 1;
        p = p + 0x108;
    } while (i < 0xc);
    func_02011134(obj + 0x248 + 0x1000);
    func_02011320(obj + 0x270 + 0x1000);
}
