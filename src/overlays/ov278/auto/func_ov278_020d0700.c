/* Rider release (shared): raises flags 0xc2 and clears bit 0 in the actor's +0x60 high byte and
 * sets bits 0-1 of +0x1ae; then, for rider 0 the +0x3b0 / +0x3b4 items' +8 low byte bit 0 and
 * bit 0 of +0x3c0 clear, for any other rider the +0x3c0 / +0x3c4 items' and bit 0 of +0x3d4. */
typedef unsigned short u16;
struct b8 { unsigned f : 8; };

void func_ov278_020d0700(int actor, int rider)
{
    unsigned short *hw;
    unsigned int h;

    hw = (unsigned short *)(actor + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0xc2) << 0x18) >> 0x10);
    {
        u16 w = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (w & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)w << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    *(unsigned short *)(actor + 0x100 + 0xae) |= 3;
    if (rider == 0) {
        ((struct b8 *)(*(int *)(actor + 0x3b0) + 8))->f &= ~1;
        ((struct b8 *)(*(int *)(actor + 0x3b4) + 8))->f &= ~1;
        *(int *)(actor + 0x3c0) &= ~1;
    } else {
        ((struct b8 *)(*(int *)(actor + 0x3c0) + 8))->f &= ~1;
        ((struct b8 *)(*(int *)(actor + 0x3c4) + 8))->f &= ~1;
        *(int *)(actor + 0x3d4) &= ~1;
    }
}
