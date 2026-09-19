/* Jump entry: counts the +0x28 timer up by the scene step and, once past 0x2aaa (latched at
 * +0x51), fires effect 0x127 of kind 8 at the +0x38 anchor. Once the +4 child's +0xad byte clears
 * pose 0xb plays (looping), flag 0x40 is raised in the actor's +0x60 high byte, the +0x3c jump
 * velocity is the direction from the actor's +0x74 position to its +0x190 target scaled by a
 * fiftieth of the distance, its +0x40 rise is 0.75 minus that fiftieth (at least 1/16), and the
 * node moves to 020cff4c. */
struct Vec3 { int x, y, z; };
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int  func_01ff8d18(void *a, void *d);
extern int  VEC_Mag(void *v);
extern void func_01ffa724(int scale, void *v, void *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov236_020cff4c(void);

void func_ov236_020cfe10(int *node) {
    int *state = (int *)node[1];
    struct Vec3 dir;

    if (*((unsigned char *)state + 0x51) == 0) {
        state[0xa] += *(int *)(*node + 0x2c);
        if (state[0xa] >= 0x2aaa) {
            *((unsigned char *)state + 0x51) = 1;
            func_ov107_020c5af8(*state, 0x127, 8, (void *)state[0xe]);
        }
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xb, 1);
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x40;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    VEC_Subtract((void *)(*state + 0x190), (void *)(*state + 0x74), &dir);
    dir.y = 0;
    func_01ff8d18(&dir, state + 0xf);
    func_01ffa724(VEC_Mag(&dir) / 50, state + 0xf, state + 0xf);
    state[0x10] = 0xc00 - VEC_Mag(&dir) / 50;
    if (state[0x10] < 0x100) state[0x10] = 0x100;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov236_020cff4c);
}
