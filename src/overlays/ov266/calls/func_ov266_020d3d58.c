/* Copy 3 words from *(child)+0x74 into (child)+8 and register the handler. */
struct w3 { int a, b, c; };
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov266_020d3d90(int);
void func_ov266_020d3d58(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(struct w3 *)(child + 8) = *(struct w3 *)(*(int *)child + 0x74);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov266_020d3d90);
}
