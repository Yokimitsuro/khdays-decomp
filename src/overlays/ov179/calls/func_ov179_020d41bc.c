extern void *func_0203d15c(int size);
extern void func_ov107_020c6624(void *obj, int flag);
extern void func_ov179_020d41f0(void);

void *func_ov179_020d41bc(void *a) {
    void *obj = func_0203d15c(0x390);
    *(void **)((char *)obj + 0x38c) = a;
    *(void **)((char *)obj + 0x18c) = func_ov179_020d41f0;
    func_ov107_020c6624(obj, 0);
    return obj;
}
