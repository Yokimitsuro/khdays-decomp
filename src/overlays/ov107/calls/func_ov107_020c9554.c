/* Allocate 0xb4 bytes via func_0203d15c, initialise via func_ov107_020c96c8,
 * return the allocation. */
extern int func_0203d15c(int size);
extern void func_ov107_020c96c8(int arg);
int func_ov107_020c9554(void) {
    int r = func_0203d15c(0xb4);
    func_ov107_020c96c8(r);
    return r;
}
