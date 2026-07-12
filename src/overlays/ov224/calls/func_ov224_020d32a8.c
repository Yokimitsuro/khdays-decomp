/* Reset the child sprite (anim 0x10), scroll its +0x14 vector by -0x600,
 * clear +0x75/+0x5c, then dispatch via func_0203c634 (handler func_ov224_020d32fc). */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_01ffa724(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov224_020d32fc(void);
void func_ov224_020d32a8(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0x10, 0);
    func_01ffa724(-0x600, child + 0x14, child + 0x14);
    *(unsigned char *)(child + 0x75) = 0;
    *(int *)(child + 0x5c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov224_020d32fc);
}
