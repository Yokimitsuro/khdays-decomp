/* Forward (param_1, param_2) plus the pointer at (*global)+0x4b0 to the handler. */
extern int func_ov002_0205a6b0(int a, int b, int c);
extern int data_ov002_0207f620;

int func_ov002_0205a714(int param_1, int param_2) {
    return func_ov002_0205a6b0(param_1, param_2, *(int *)(*(int *)&data_ov002_0207f620 + 0x4b0));
}
