/* Down entry of the ov259 actor: it turns to the +8 target (+0x78 / +0x7c heading), the +0x68 timer,
 * cue flags, +0x4c and +0xae clear and the +0xa0 knock-down count grows; the recovery time +0x64
 * lengthens with it (0xff0, 0x2fd0, 0x4fb0, then 0x5fa0). With no health left (+0x21a) bits 0-1 of
 * +0x1ae are set. Sound 0x172/0x1b fires at the +0x10 point, the actor is knocked back there (mode
 * 4), pose 5 plays on the actor and its partner, the +0x384 rig closes (020d1764), bit 6 of the +0x60
 * high byte drops, pose 0x16 is queued (020cd628) and the node moves on to 020cfc40. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int y);
extern void func_ov259_020cd3c4(int actor, int id, int variant, void *at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_ov259_020d1764(int rig, int open);
extern void func_ov259_020cd628(int *node, int pose, int delay);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cfc40(void);

void func_ov259_020cfaa8(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(*state + 0x74), &d);
    func_01ff8d18(&d, &d);
    state[0x1e] = state[0x1f] = func_020050b4(d.x, d.z);
    state[0x1a] = 0;
    *((unsigned char *)state + 0xac) = 0;
    state[0x13] = 0;
    state[0x28]++;
    *((unsigned char *)state + 0xae) = 0;
    if (state[0x28] == 1) {
        state[0x19] = 0xff0;
    } else if (state[0x28] == 2) {
        state[0x19] = 0x2fd0;
    } else if (state[0x28] == 3) {
        state[0x19] = 0x4fb0;
    } else {
        state[0x19] = 0x5fa0;
    }
    if (*(short *)(*state + 0x21a) <= 0) {
        *(u16 *)(*state + 0x1ae) |= 3;
    }
    func_ov259_020cd3c4(*state, 0x172, 0x1b, (void *)state[4]);
    func_ov107_020c0b90(*state, 4, *(Vec3 *)state[4], 0);
    func_ov107_020c9264(*state, 5, 0);
    func_ov259_020cd524(node, 5, 0);
    func_ov259_020d1764(*(int *)(*state + 0x384), 0);
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    func_ov259_020cd628(node, 0x16, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020cfc40);
}
