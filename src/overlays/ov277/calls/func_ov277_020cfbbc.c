/* Leap release: raises bit 7 of the actor's +0x60 high byte and bit 0 of +0x1ae, clears bit 0
 * of the +0x39c / +0x3a0 / +0x3a4 items' +8 low byte, then re-arms 020cfcf0. */
struct b8 { unsigned f : 8; };
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov277_020cfc88(void);

void func_ov277_020cfbbc(int *node) {
    int *state = (int *)node[1];
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x80;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    *(unsigned short *)(*state + 0x100 + 0xae) |= 1;
    ((struct b8 *)(*(int *)(*state + 0x39c) + 8))->f &= ~1;
    ((struct b8 *)(*(int *)(*state + 0x3a0) + 8))->f &= ~1;
    ((struct b8 *)(*(int *)(*state + 0x3a4) + 8))->f &= ~1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov277_020cfc88);
}
