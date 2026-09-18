/* Approach entry of the ov139 enemy (and its byte-identical twin): without a target the state
 * ends with sub-state 2; else the +0xc target yaw is the flat direction from the +0x4c position
 * to the target's +0x74, the +0x14 velocity is 0x100 along the +8 yaw's (sin, 0, cos) and, once
 * the +0x50 busy byte clears, the +0x390 part restarts action 0, animation 3 (looped) plays and
 * the tick hands off to the approach tick. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };

extern int func_ov107_020cab14(int actor, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int scale, void *v, void *d);
extern void func_ov107_020c9ee8(void *part, int a, int b);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern const short data_0203d210[];
extern void func_ov139_020cd114(int *node);

void func_ov139_020ccfc8(int *node)
{
    int *state = (int *)node[1];
    struct Vecx32 dir;
    struct Vecx32 fwd;
    int idx;

    state[1] = func_ov107_020cab14(*state, 0);
    if (state[1] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state[1] + 0x74), (void *)state[0x13], &dir);
    dir.y = 0;
    func_01ff8d18(&dir, &dir);
    state[3] = func_020050b4(dir.x, dir.z);
    idx = (unsigned short)((0x28BE60DB9391LL * state[2] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    fwd.y = 0;
    fwd.x = data_0203d210[(idx >> 4) << 1];                                             /* FX_SinIdx */
    fwd.z = data_0203d210[((idx >> 4) << 1) + 1];                                       /* FX_CosIdx */
    func_01ffa724(0x100, &fwd, state + 5);
    if (*(u8 *)state[0x14] != 0) {
        return;
    }
    func_ov107_020c9ee8(*(void **)(*state + 0x390), 0, 1);
    func_ov107_020c9264(*state, 3, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov139_020cd114);
}
