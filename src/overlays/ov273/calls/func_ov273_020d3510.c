/* Unless the busy byte at *(child+8) is set, play the anim (ov107 mode 5,1), clear +0x1c,
 * set +0x5c = 0x1000, clear the +0x69 byte and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov273_020d3568(int);
void func_ov273_020d3510(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 8) != 0) return;
    func_ov107_020c9264(*(int *)child, 5, 1);
    *(int *)(child + 0x1c) = 0;
    *(int *)(child + 0x5c) = 0x1000;
    *(signed char *)(child + 0x69) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov273_020d3568);
}
