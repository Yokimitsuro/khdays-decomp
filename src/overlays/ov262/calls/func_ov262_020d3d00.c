/* Tick hook of the ov261 enemy (and its byte-identical twin): with a +0x3a4 grab target and a
 * +0x3a8 holder of the same +4 scene, a not yet ready actor raises bit 0 of the +0x60 high
 * byte and drops bit 7 (shown); with a target but no holder, an actor flagged in +0x40 bit 1
 * that is not yet ready does the same and requests sub-state 2; without a target the high
 * byte drops bit 0 and raises bit 7 (hidden). The base tick always runs. */
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov107_020c7ca4(int actor);

void func_ov262_020d3d00(int actor)
{
    unsigned short *hw;
    unsigned int h;

    if (*(int *)(actor + 0x3a4) != 0) {
        if (*(int *)(actor + 0x3a8) != 0) {
            if (*(int *)(actor + 4) == *(int *)(*(int *)(actor + 0x3a8) + 4)) {
                if ((((struct hw60 *)(actor + 0x60))->lo & 1) == 0) {
                    hw = (unsigned short *)(actor + 0x60);
                    h = *hw;
                    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
                    ((struct hw60 *)(actor + 0x60))->hi &= ~0x80;
                }
            }
        } else if (((*(int *)(actor + 0x40) << 30) >> 31) != 0) {
            if ((((struct hw60 *)(actor + 0x60))->lo & 1) == 0) {
                hw = (unsigned short *)(actor + 0x60);
                h = *hw;
                *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
                ((struct hw60 *)(actor + 0x60))->hi &= ~0x80;
                *(unsigned char *)(actor + 0x1c7) = 2;
            }
        }
    } else {
        ((struct hw60 *)(actor + 0x60))->hi &= ~1;
        hw = (unsigned short *)(actor + 0x60);
        h = *hw;
        *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10);
    }
    func_ov107_020c7ca4(actor);
}
