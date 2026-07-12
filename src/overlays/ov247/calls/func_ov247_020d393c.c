/* Allocate a 0x3a0-byte object, wire its owner (+0x38c) and vtable/handler
 * (+0x18c = func_ov247_020d3970), start it via func_ov107_020c6624, and return it. */
extern int func_0203d15c(int size);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov247_020d3970(void);
int func_ov247_020d393c(int param_1) {
    int obj = func_0203d15c(0x3a0);
    *(int *)(obj + 0x38c) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov247_020d3970;
    func_ov107_020c6624(obj, 0);
    return obj;
}
