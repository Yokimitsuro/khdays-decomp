/* func_ov245_020d2714 -- wait for the +0x3c8 owner's three +0x420 parts: once none of them has
 * bit 0 of its +0x60 low byte set, plays pose 2 and moves the node to 020d27b4; while one is
 * still active, counts the state's +0x1c timer up by the scene step and after 1.0 moves to
 * 020d24bc. */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct Ov245Owner { char pad[0x420]; int parts[3]; };

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d27b4(void);
extern void func_ov245_020d24bc(void);

void func_ov245_020d2714(int *node) {
    int *state = (int *)node[1];
    int i;
    struct Ov245Owner *owner;

    owner = *(struct Ov245Owner **)(*state + 0x3c8);
    for (i = 0; i < 3; i++) {
        if ((((struct hw60 *)(owner->parts[i] + 0x60))->lo & 1) != 0) {
            break;
        }
    }
    if (i >= 3) {
        func_ov107_020c9264(*state, 2, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d27b4);
        return;
    }
    state[7] += *(int *)(*node + 0x2c);
    if (state[7] < 0x1000) {
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d24bc);
}
