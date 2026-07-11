extern void func_020235a8(void *obj);
extern void func_020235bc(void *obj);
extern int data_ov069_020baa2c;

void func_ov069_020b8100(void *obj, int index, int arg3) {
    int (*fn)(int) = ((int (**)(int)) &data_ov069_020baa2c)[index];
    if (fn) {
        if (fn(arg3)) {
            func_020235a8(obj);
        } else {
            func_020235bc(obj);
        }
    }
}
