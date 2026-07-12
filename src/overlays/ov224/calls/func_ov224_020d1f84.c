/* Set +0x74=6, anim 0x11, +0x6c=0x600, clear +0x75/+0x5c, then dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov224_020d203c(void);
void func_ov224_020d1f84(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(unsigned char *)(child + 0x74) = 6;
    func_ov107_020c9264(*(int *)child, 0x11, 0);
    *(int *)(child + 0x6c) = 0x600;
    *(unsigned char *)(child + 0x75) = 0;
    *(int *)(child + 0x5c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov224_020d203c);
}
