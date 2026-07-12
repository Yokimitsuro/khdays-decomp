/* Notify func_ov223_020d0ee0 with the child fields, then dispatch. */
extern void func_ov223_020d0ee0(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov223_020d3c64(void);
void func_ov223_020d3c34(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov223_020d0ee0(*(int *)child, *(int *)(child + 0x78));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov223_020d3c64);
}
