/* Play the anim (ov107 mode 0xb), fire ov107_020c5af8(*child, 0x112, 4, *(child+4)), clear
 * +0x44 and the +0x49 byte and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov244_020d30dc(int);
void func_ov244_020d3088(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0xb, 0);
    func_ov107_020c5af8(*(int *)child, 0x112, 4, *(int *)(child + 4));
    *(int *)(child + 0x44) = 0;
    *(signed char *)(child + 0x49) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov244_020d30dc);
}
