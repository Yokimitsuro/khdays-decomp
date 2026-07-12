/* Unless the busy byte at *(child+4)+0xad is set, play the anim (ov107 mode 5,0), run the
 * local setup (mode 0) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov267_020d1cec(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov267_020d2c50(int);
void func_ov267_020d2c00(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)child, 5, 0);
    func_ov267_020d1cec(*(int *)child, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov267_020d2c50);
}
