/* Clear the flag at *(*child+0x384)+0xa8, set *(*child)+0x54 = 0x3000 and register the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov278_020d27fc(int);
void func_ov278_020d27c4(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(unsigned char *)(*(int *)(*(int *)child + 0x384) + 0xa8) = 0;
    *(int *)(*(int *)child + 0x54) = 0x3000;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov278_020d27fc);
}
