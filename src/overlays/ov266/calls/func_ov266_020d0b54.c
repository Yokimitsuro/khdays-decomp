/* Run the local setup (mode 1) on *(child+4), then dispatch to the handler. */
extern void func_ov266_020cf3dc(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov266_020d0b80(int);
void func_ov266_020d0b54(int param_1) {
    func_ov266_020cf3dc(*(int *)(param_1 + 4), 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov266_020d0b80);
}
