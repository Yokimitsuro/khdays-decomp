/* Raise flag 0x80 in the high byte at (*child)+0x60, reset +0x388, clear flag 0 in the high
 * byte at (*child)+0x60, copy the const offset vector into (child)+8, and register the handler. */
struct Vec3_020d1168 { int x, y, z; };
extern const struct Vec3_020d1168 data_02041dc8;
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov267_020d4e14(int);
struct node60_020d1168 { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov267_020d4d80(int param_1) {
    int child = *(int *)(param_1 + 4);
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x80;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    *(int *)(*(int *)child + 0x388) = 0;
    ((struct node60_020d1168 *)(*(int *)child + 0x60))->hi &= ~1;
    *(struct Vec3_020d1168 *)(child + 8) = data_02041dc8;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov267_020d4e14);
}
