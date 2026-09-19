/* func_ov253_020d0a04 -- taunt tick: the +0x18 speed follows six times the frame step (30 / 5);
 * once the +8 item's animation is free sprite request 4 (data_ov253_020d4964 + 4 with the
 * actor's +2 id) is dispatched, pose 5 (flag 1) plays, the +0x1c timer is armed with 4.0 plus a
 * random 4.0 and the node moves to 020d0ab8. */
struct hpair { unsigned short a, b; };

extern void func_02031384(int a, void *req, int b);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern int func_02023eb4(int scale);
extern void func_0203c634(int *node, int slot, void *cb);
extern const struct hpair data_ov253_020d4964[];
extern void func_ov253_020d0ab8(void);

void func_ov253_020d0a04(int *node) {
    int *state = (int *)node[1];

    state[6] = *(int *)(node[0] + 0x2c) * 0x1e / 5;
    if (*(unsigned char *)state[2] != 0) {
        return;
    }
    {
        struct hpair buf = data_ov253_020d4964[1];
        buf.a = *(unsigned short *)(*state + 2);
        func_02031384(4, &buf, 4);
    }
    func_ov107_020c9264(*state, 5, 1);
    state[7] = func_02023eb4(0x4001) + 0x4000;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d0ab8);
}
