/* func_ov245_020d6a14 -- double-strike tick: the +0x3a0 item's forward vector (020c9f48,
 * speed returned) rotated by the actor's +0xa0 placement and scaled becomes the +0x1c
 * direction; the +0x394 / +0x398 items' +0x14 anchors offset by it give two strike centres.
 * The +0x40 timer runs up by the frame step: past 0.166 (latched at +0x48) effect 3 plays at
 * the +0x390 item's anchor and reaction 0x11a/4 fires at the +0xc anchor; past 0.996 each
 * centre is swept with a 0.1875 sphere (020c8eb8) and every hit whose +2 slot bit is not in the
 * +0x49 mask is pushed along the direction through the +0x3cc item (020ca918, mode 6): a
 * landing hit gets effect 1 at the centre, its bit set, the direction zeroed and reaction
 * 0x11a/5 at the centre. Once the +4 item's animation is free (+0xad) the direction is copied
 * to +0x28 and the node moves to 020d6c78. */
typedef struct { int x, y, z; } Vec3;
struct Sphere { Vec3 centre; int radius; };

extern int func_ov107_020c9f48(int item, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern int func_ov107_020c8eb8(int actor, struct Sphere *sphere, int *out);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov245_020d6c78(void);

void func_ov245_020d6a14(int *node) {
    int *state = (int *)node[1];
    int hits[4];
    Vec3 centres[2];
    Vec3 fwd;
    struct Sphere sphere;
    Vec3 zero;
    int j;
    int speed;
    int nHits;
    int i;
    Vec3 *centre;
    Vec3 *anchor;

    speed = func_ov107_020c9f48(*(int *)(*state + 0x3a0), &fwd);
    func_0202f384((Vec3 *)(state + 7), (void *)(*state + 0xa0), &fwd);
    func_01ffa724(speed, (Vec3 *)(state + 7), (Vec3 *)(state + 7));
    VEC_Add((Vec3 *)(*(int *)(*state + 0x394) + 0x14), (Vec3 *)(state + 7), &centres[0]);
    VEC_Add((Vec3 *)(*(int *)(*state + 0x398) + 0x14), (Vec3 *)(state + 7), &centres[1]);
    state[0x10] += *(int *)(node[0] + 0x2c);
    if (*((unsigned char *)state + 0x48) == 0 && state[0x10] >= 0x2a8) {
        *((unsigned char *)state + 0x48) = 1;
        func_ov107_020c0b90(*state, 3, *(Vec3 *)(*(int *)(*state + 0x390) + 0x14), 0);
        func_ov107_020c5af8(*state, 0x11a, 4, (void *)state[3]);
    }
    if (state[0x10] >= 0xff0) {
        zero = data_02041dc8;
        centre = centres;
        anchor = centres;
        for (j = 0; j < 2; j++) {
            sphere.centre = *centre;
            sphere.radius = 0x300;
            nHits = func_ov107_020c8eb8(*state, &sphere, hits);
            for (i = 0; i < nHits; i++) {
                if ((*((unsigned char *)state + 0x49) & (1 << *(unsigned short *)(hits[i] + 2))) == 0) {
                    if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x3cc), 6, (Vec3 *)(state + 7), 0) != 0) {
                        func_ov107_020c0b90(*state, 1, *centre, 0);
                        *((unsigned char *)state + 0x49) |= 1 << *(unsigned short *)(hits[i] + 2);
                        *(Vec3 *)(state + 7) = zero;
                        func_ov107_020c5af8(*state, 0x11a, 5, anchor);
                    }
                }
            }
            centre++;
            anchor++;
        }
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(Vec3 *)(state + 10) = *(Vec3 *)(state + 7);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d6c78);
}
