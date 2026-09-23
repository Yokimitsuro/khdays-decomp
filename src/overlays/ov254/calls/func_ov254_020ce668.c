/* Seek entry: while aggressive (+0x78) bit 2 of the actor's +0x60 high byte is set. Without a
 * route point (020cd750) the next move is 2. Otherwise the pose / partner motion pair is 1 / 0
 * (aggressive) or 0xc / 7 (+0x75 / +0x76) and plays (partner looping); aggressive also starts the
 * +0x460 / +0x464 helpers and knocks the actor back in place (mode 0xb). The +0x10 / +0x60
 * counters and +0x71 flag clear and the node moves to 020ce7a0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_ov254_020cd750(int *state);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov254_020d4d18(int helper);
extern void func_ov254_020d5310(int helper);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov254_020ce7a0(void);

void func_ov254_020ce668(int *node)
{
    int *state = (int *)node[1];

    if (state[0x1e] != 0) {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 4) << 0x18) >> 0x10);
    }
    if (func_ov254_020cd750(state) == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *((u8 *)state + 0x75) = state[0x1e] != 0 ? 1 : 0xc;
    *((u8 *)state + 0x76) = state[0x1e] != 0 ? 0 : 7;
    func_ov107_020c9264(*state, *((u8 *)state + 0x75), 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x430), *((u8 *)state + 0x76), 1);
    if (state[0x1e] != 0) {
        func_ov254_020d4d18(*(int *)(*state + 0x460));
        func_ov254_020d5310(*(int *)(*state + 0x464));
        func_ov107_020c0b90(*state, 0xb, data_02041dc8, 0);
    }
    state[4] = 0;
    state[0x18] = 0;
    *((u8 *)state + 0x71) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020ce7a0);
}
