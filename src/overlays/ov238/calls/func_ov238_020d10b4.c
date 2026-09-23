/* Idle decision of the ov238 actor: a pending rider signal (+0x384 model's +0x394) is consumed and the
 * next move is 5. Otherwise, once the partner holds no queued move: with charges left (+0x2d) one is
 * spent and pose 0 plays; with no rest pending (+0x28) a picked move (020d0b2c) ends the node; a
 * target farther than 20.0 or a rider below -15.0 gives move 4; at 6.0-20.0 the actor starts walking
 * (pose 0x11, part motion 7, node 020d120c); else the node goes to 020d107c. */
extern int func_ov238_020d0878(int *node);
extern int func_ov238_020d0b2c(int *node);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov238_020d120c(void);
extern void func_ov238_020d107c(void);

void func_ov238_020d10b4(int *node)
{
    int *state = (int *)node[1];
    int dist = func_ov238_020d0878(node);

    if (*(int *)(*(int *)(*state + 0x384) + 0x394) != 0) {
        *(int *)(*(int *)(*state + 0x384) + 0x394) = 0;
        *(unsigned char *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (*((unsigned char *)state + 0x2d) != 0) {
        *((unsigned char *)state + 0x2d) -= 1;
        func_ov107_020c9264(*state, 0, 0);
        return;
    }
    if (state[0xa] == 0 && func_ov238_020d0b2c(node) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (dist > 0x5000 || *(int *)(*(int *)(*state + 0x3e4) + 0x198) < -0xf000) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (dist <= 0x5000 && dist >= 0x1800) {
        func_ov107_020c9264(*state, 0x11, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x3e0), 7, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov238_020d120c);
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov238_020d107c);
}
