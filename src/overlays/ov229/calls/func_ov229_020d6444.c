/* Unless the busy byte at *(*child+0x384)+0xad is set, play the anim (ov107 mode 1,1) and dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov229_020d6488(int);
void func_ov229_020d6444(int param_1) {
    int obj = *(int *)*(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(obj + 0x384) + 0xad) != 0) return;
    func_ov107_020c9264(obj, 1, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov229_020d6488);
}
