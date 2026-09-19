/* Attach the sub-actor (020c5c54), store the spawn pose (param_3 -> +0x394, 16 bytes) and raise
 * flag 0 in the high byte at (param_1)+0x60. */
extern void func_ov107_020c5c54(int a, int b);
struct m4 { int w[4]; };
void func_ov244_020cd3f0(int param_1, int param_2, int param_3) {
    *(struct m4 *)(param_1 + 0x394) = *(struct m4 *)param_3;
    func_ov107_020c5c54(param_1, param_2);
    {
        unsigned short *p = (unsigned short *)(param_1 + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 1;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
}
