/* func_ov245_020cd73c -- landing decision: with the state's +0x44 flag set it is cleared and the
 * actor's three +0x420 parts are checked; when none has bit 0 of its +0x60 low byte set, the
 * +0x34 timer is armed with 60.0, sub-state 8 is requested and the node's slot is released.
 * Otherwise (flag clear or a part active) pose 0 plays and the node moves to 020cd7e0. */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct Ov245Actor { char pad[0x420]; int parts[3]; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov245_020cd7e0(void);

void func_ov245_020cd73c(int *node) {
    int *state = (int *)node[1];
    int i;

    if (state[0x11] != 0) {
        state[0x11] = 0;
        for (i = 0; i < 3; i++) {
            if ((((struct hw60 *)(((struct Ov245Actor *)*state)->parts[i] + 0x60))->lo & 1) != 0) {
                break;
            }
        }
        if (i >= 3) {
            state[0xd] = 0x3c000;
            *(unsigned char *)(*state + 0x1c7) = 8;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    func_ov107_020c9264(*state, 0, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020cd7e0);
}
