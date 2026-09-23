/* Entry of the ov249 actor's leap: with no target (020cab14) the next move is 0 and the brain slot
 * +0x20 clears. Otherwise the +0x2c range is the distance to the target less 3.0 (at most 32.0), the
 * +0x28 clock resets, +0x18 keeps the +0x398 goal and +0xc the origin; bit 0 of the +0x60 high byte is
 * raised and bits 2, 3 and 7 cleared, the +0x388 rig's flag 0 is set, cue 0x145 (13) plays on the +8
 * target and effect 0 at the actor's +0x74 position; the +0x24 count resets and 020d4490 runs next. */
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern int func_ov107_020cab14(int actor, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c5af8(int owner, int cue, int kind, void *target);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov249_020d4490(void);
extern const Vec3 data_02041dc8;

void func_ov249_020d4308(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    int target = func_ov107_020cab14(*state, 0);

    if (target == 0) {
        *(signed char *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((Vec3 *)(target + 0x190), (Vec3 *)(*state + 0xb0), &d);
    state[0xb] = func_01ff8d18(&d, &d) - 0x3000;
    if (state[0xb] > 0x20000) {
        state[0xb] = 0x20000;
    }
    state[0xa] = 0;
    *(Vec3 *)(state + 6) = *(Vec3 *)(*state + 0x398);
    *(Vec3 *)(state + 3) = data_02041dc8;
    {
        unsigned short hw = *(unsigned short *)(*state + 0x60);

        *(unsigned short *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    {
        unsigned short hw = *(unsigned short *)(*state + 0x60);

        *(unsigned short *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x8c) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x388) + 8))->f |= 1;
    func_ov107_020c5af8(*state, 0x145, 0xd, (void *)state[2]);
    func_ov107_020c0b90(*state, 0, *(Vec3 *)(*state + 0x74), 0);
    state[9] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov249_020d4490);
}
