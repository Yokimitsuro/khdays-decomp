/* func_ov245_020d52b8 -- sweep tick: advances the +0xc timer by the frame step and, past 0.863
 * once, plays effect 2 at the origin (+0x10 latch). Then the actor's +0x388 shape capsule
 * (+0x78, radius widened by 1.0) is swept for hits (020c8f44); each hit whose +2 slot bit is not
 * yet in the actor's +0x3b0 mask is offered to the +0x398 item (020ca918, mode 7, push
 * (0, 1.0, -5.0), 0x80) and, when it lands, gets effect 0 at its +0x74 position and its bit set.
 * Any landing hit fires reaction 0/0x51 at the +8 anchor; unless the scene's +0xad flag is set
 * the node moves to 020d5088. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p0; Vec3 dir; int scale; } Segment;
struct Capsule { Segment seg; int radius; };

extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern int func_ov107_020c8f44(int actor, struct Capsule *cap, int *out);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d5088(void);
extern const Vec3 data_02041dc8;

void func_ov245_020d52b8(int *node) {
    int *state = (int *)node[1];
    int hits[4];
    struct Capsule cap;
    Vec3 push;
    int any = 0;
    int nHits;
    int i;
    unsigned char bit;

    state[3] += *(int *)(node[0] + 0x2c);
    if (state[3] >= 0xdd0 && *((unsigned char *)state + 0x10) == 0) {
        func_ov107_020c0b90(*state, 2, data_02041dc8, 0);
        *((unsigned char *)state + 0x10) = 1;
    }
    push.x = 0;
    push.y = 0x1000;
    push.z = -0x5000;
    cap = *(struct Capsule *)(**(int **)(*state + 0x388) + 0x78);
    cap.radius += 0x1000;
    nHits = func_ov107_020c8f44(*state, &cap, hits);
    for (i = 0; i < nHits; i++) {
        bit = 1 << *(unsigned short *)(hits[i] + 2);
        if ((*(unsigned char *)(*state + 0x3b0) & bit) == 0) {
            if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x398), 7, &push, 0x80) != 0) {
                func_ov107_020c0b90(*(int *)(*state + 0x398), 0, *(Vec3 *)(hits[i] + 0x74), 0);
                *(unsigned char *)(*state + 0x3b0) |= bit;
                any = 1;
            }
        }
    }
    if (any != 0) {
        func_ov107_020c5af8(*state, 0, 0x51, (void *)state[2]);
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d5088);
}
