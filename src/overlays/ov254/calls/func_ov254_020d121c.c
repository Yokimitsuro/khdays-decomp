/* Landing tick: the +0x10 climb is 1/32 of the height difference to the next route point. Once
 * the +8 track dips below the actor's +0x4d4 floor + 15.4 (not aggressive, +0x70 bit 0 clear) the
 * actor is knocked back once at its feet (020cdbbc, side -1). Once the +4 item's +0xad byte clears
 * the actor plays pose 8 (aggressive) or 0x11 (looping) and is knocked back in place (mode 5,
 * flag 1), the +0x3e4 shape loses bit 1 and the +0x3e0 one gains it, the +0x44 timer clears and
 * the node moves to 020d1384. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern int func_ov254_020cd840(int *state, int a);
extern void func_ov254_020cdbbc(int actor, int side);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov254_020d1384(void);

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov254_020d121c(int *node)
{
    int *state = (int *)node[1];

    state[4] = FX_Mul(func_ov254_020cd840(state, -1) - *(int *)(state[2] + 4), 0x80);
    if ((*((u8 *)state + 0x70) & 1) == 0 && state[0x1e] == 0 &&
        *(int *)(state[2] + 4) < *(int *)(*state + 0x4d4) + 0xf662) {
        *((u8 *)state + 0x70) |= 1;
        func_ov254_020cdbbc(*state, -1);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, state[0x1e] != 0 ? 8 : 0x11, 1);
    func_ov107_020c0b90(*state, 5, data_02041dc8, 1);
    ((B8 *)(*(int *)(*state + 0x3e4) + 8))->f &= ~2;
    ((B8 *)(*(int *)(*state + 0x3e0) + 8))->f |= 2;
    state[0x11] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d1384);
}
