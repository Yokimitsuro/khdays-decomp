/* Run the local setup (mode 1) on *(child+4), then dispatch to the handler. */
extern void func_ov267_020d11fc(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov267_020d29a0(int);
void func_ov267_020d2974(int param_1) {
    func_ov267_020d11fc(*(int *)(param_1 + 4), 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov267_020d29a0);
}
