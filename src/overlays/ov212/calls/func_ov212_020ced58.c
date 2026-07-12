/* Run the local setup (mode 1) on *(child+4), then dispatch to the handler. */
extern void func_ov212_020cd5ec(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov212_020ced84(int);
void func_ov212_020ced58(int param_1) {
    func_ov212_020cd5ec(*(int *)(param_1 + 4), 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov212_020ced84);
}
