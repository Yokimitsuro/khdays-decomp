/* Recoil wind-up tick of the ov248 enemy. The +0x4c timer accumulates the owner's
 * rate; past 0x770 reaction 0x146 mode 0xb fires at the +0xc position (once, flag +0x61). When
 * the +4 animator's +0xad flag drops, effect 7 spawns at the +0xc position, animation 0x17 plays,
 * bit 6 of the +0x60 high byte is raised, the timer restarts, the +0x1c impulse becomes
 * (0, 1.5, 0) and the tick hands over to func_ov248_020cf7ac. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov248_020cf7ac(int *node);

void func_ov248_020cf6b0(int *node)
{
    int *state = (int *)node[1];
    unsigned short v;

    state[0x13] += *(int *)(node[0] + 0x2c);
    if (*((unsigned char *)state + 0x61) == 0 && state[0x13] >= 0x770) {
        func_ov107_020c5af8(*state, 0x146, 0xb, (void *)state[3]);
        *((unsigned char *)state + 0x61) = 1;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c0b90(*state, 7, *(Vec3 *)state[3], 0);
    func_ov107_020c9264(*state, 0x17, 0);
    v = *(unsigned short *)(*state + 0x60);
    *(unsigned short *)(*state + 0x60) = (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    state[0x13] = 0;
    state[7] = 0;
    state[8] = 0x1800;
    state[9] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov248_020cf7ac);
}
