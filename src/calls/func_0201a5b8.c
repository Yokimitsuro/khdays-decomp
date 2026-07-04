extern void func_0201e144(void *a, int b, unsigned c);
extern void func_0201a8e0(int a, int b);
extern void func_0201a76c(void *a);

void func_0201a5b8(int *param_1, unsigned param_2) {
    if (param_1 != 0) {
        if (*(unsigned char *)(param_1 + 0xb) != 0) {
            if (param_2 == 0) {
                func_0201a76c(param_1);
            } else {
                func_0201e144(param_1 + 7, 0, param_2);
                func_0201a8e0((int)param_1, 0);
                *(unsigned char *)(param_1 + 0xb) = 2;
            }
        }
    }
}
