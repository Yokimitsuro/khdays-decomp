extern void func_0201ef58(int a, int b, int c, int d);
extern void func_0201f5ac(void *a);

void func_02022654(int param_1, int param_2, int param_3, int param_4) {
    if (param_2 >= 0) {
        func_0201ef58(param_1, param_2, param_3, param_4);
        func_0201f5ac(*(void **)(*(int *)(param_1 + 0x128) + 0x28));
    }
}
