extern void *data_0204c024;
extern void *func_020236cc(int size, void *heap);
extern void func_02023960(void *ptr, int arg1, int arg2);

void func_02023930(int arg1, int arg2) {
    void *ptr = func_020236cc(0x2c, data_0204c024);

    func_02023960(ptr, arg1, arg2);
}
