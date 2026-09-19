/* Jump tick: the +0x18 velocity follows the +0x3c one, whose rise decays by 0x80 per tick;
 * once falling, and only if the actor's +0x17a bit 0 (grounded) is set, the landing cue
 * (first halfword pair of data_ov236_020d63c0) is sent through the +0x24 hook, effect 0x127 of kind 9
 * fires at the +0x38 anchor, pose request 5 is queued and the node dispatches null. */
typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
struct Vec3 { int x, y, z; };
struct Bits17a { u8 b0 : 1; };

extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern unsigned short data_ov236_020d63c0[];

void func_ov236_020cff4c(int *node) {
    int *state = (int *)node[1];
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();

    *(struct Vec3 *)(state + 6) = *(struct Vec3 *)(state + 0xf);
    state[0x10] -= 0x80;
    if (state[0x10] >= 0) {
        return;
    }
    if (((struct Bits17a *)(*state + 0x17a))->b0 == 0) {
        return;
    }
    pp = pair;
    pp[1] = data_ov236_020d63c0[1];
    pp[0] = data_ov236_020d63c0[0];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    func_ov107_020c5af8(*state, 0x127, 9, (void *)state[0xe]);
    *(unsigned char *)(*state + 0x1c7) = 5;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
