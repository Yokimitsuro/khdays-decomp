/* Reset the child sprite (anim 0xf, clear +0x5c word and +0x75 flag), then
 * dispatch via func_0203c634 (handler func_ov226_020d3a58). */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov226_020d3a58(void);
void func_ov226_020d3a18(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0xf, 0);
    *(int *)(child + 0x5c) = 0;
    *(unsigned char *)(child + 0x75) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov226_020d3a58);
}
