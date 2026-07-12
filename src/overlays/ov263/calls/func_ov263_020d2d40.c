/* Attach the sub-actor (020c5c54), store the spawn position (param_3 -> +0x390) and slot
 * (param_4 -> +0x38c), and raise flag 0 in the high byte at (param_1)+0x60. */
extern void func_ov107_020c5c54(int a, int b);
struct Vec3_020cf0dc { int x, y, z; };
void func_ov263_020d2d40(int param_1, int param_2, int param_3, int param_4) {
    func_ov107_020c5c54(param_1, param_2);
    *(struct Vec3_020cf0dc *)(param_1 + 0x390) = *(struct Vec3_020cf0dc *)param_3;
    *(signed char *)(param_1 + 0x38c) = param_4;
    {
        unsigned short *p = (unsigned short *)(param_1 + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 1;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
}
