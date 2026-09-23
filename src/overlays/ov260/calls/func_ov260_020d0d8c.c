/* Hit filter of the first ov260 sub-part (+0x1d0): while the actor is in move 1, a hit carrying
 * flags 0x01 and 0x10 knocks it back (020c0b90 mode 1 at the +0x18 point), requests move 0 and is
 * accepted; anything else is ignored. */typedef struct { int x, y, z; } Vec3;
struct HitWord { unsigned int lo : 16, hi : 16; };

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);

int func_ov260_020d0d8c(char *self, int src, unsigned int *hit)
{
    int *state = *(int **)(self + 0x214);

    if (*(signed char *)(*state + 0x100 + 0xc6) == 1 && (((struct HitWord *)hit)->lo & 1) != 0 &&
        (((struct HitWord *)hit)->lo & 0x10) != 0) {
        func_ov107_020c0b90(*state, 1, *(Vec3 *)state[6], 0);
        *(signed char *)(*state + 0x1c7) = 0;
        return 1;
    }
    return 0;
}
