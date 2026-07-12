/* Copy 3 words from *(child)+0x74 into (child)+8 and register the handler. */
struct w3 { int a, b, c; };
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov212_020d1f9c(int);
void func_ov212_020d1f64(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(struct w3 *)(child + 8) = *(struct w3 *)(*(int *)child + 0x74);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov212_020d1f9c);
}
