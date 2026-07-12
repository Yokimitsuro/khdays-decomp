/* Set anim 2, raise flag 0x40 in the high byte of the u16 at (*child)+0x60, clear
 * +0x6c/+0x75/+0x5c, then dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov224_020d203c(void);
void func_ov224_020d1fd4(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 2, 0);
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x40;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    *(int *)(child + 0x6c) = 0;
    *(unsigned char *)(child + 0x75) = 0;
    *(int *)(child + 0x5c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov224_020d203c);
}
