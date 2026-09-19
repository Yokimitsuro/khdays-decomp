/* Clears bit 0 and raises flags 0x82 in the actor's +0x60 high byte, clears bit 0 of the
 * +0x38c item's +8 low byte and the +0x390 word, then re-arms 020cda68. */
typedef unsigned short u16;
struct b8 { unsigned f : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov277_020cda68(void);

void func_ov277_020cd9c8(int *node) {
    int *state = (int *)node[1];
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x82;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    ((struct b8 *)(*(int *)(*state + 0x38c) + 8))->f &= ~1;
    *(int *)(*state + 0x390) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov277_020cda68);
}
