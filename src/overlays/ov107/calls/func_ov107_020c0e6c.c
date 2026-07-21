extern void func_0203d194(int block);
extern void func_ov107_020c1dd8(int obj);
extern void func_ov107_020c1cd4(int obj);
extern void func_ov107_020c0d74(int obj);
/* Destructor: release the optional sub-block at +0xf4, run the two subclass teardowns, then the
 * base destructor. */
void func_ov107_020c0e6c(int obj) {
    if (*(int *)(obj + 0xf4) != 0) {
        func_0203d194(*(int *)(obj + 0xf4));
    }
    func_ov107_020c1dd8(obj);
    func_ov107_020c1cd4(obj);
    func_ov107_020c0d74(obj);
}
