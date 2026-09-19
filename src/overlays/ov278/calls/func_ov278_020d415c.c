/* Rider fire tick (second rider): counts the +0x78 timer up by the scene step and, at each of
 * three thresholds (0xa83 / 0x12aa / 0x1d55, stepped through the +0x7c stage byte), fires an
 * effect while the matching rider counter (+0x3d2 / +0x3d2 / +0x3d0) is positive: kind 5 at
 * the +0x3c4 item's transform for the first two, kind 4 at the +0x3c0 item's for the third.
 * Once the +0x20 child's byte clears, pose 0xb plays (looping) and the node dispatches null. */
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov278_020d415c(int *node) {
    int *state = (int *)node[1];
    unsigned char stage;

    state[0x1e] += *(int *)(*node + 0x2c);
    stage = *((unsigned char *)state + 0x7c);
    if (stage == 0 && state[0x1e] >= 0xa83) {
        *((unsigned char *)state + 0x7c) = stage + 1;
        if (*(short *)(*state + 0x300 + 0xd2) > 0) {
            func_ov107_020c5af8(*state, 0x166, 5, (void *)(*(int *)(*(int *)(*state + 0x3c4)) + 4));
        }
    } else if (stage == 1 && state[0x1e] >= 0x12aa) {
        *((unsigned char *)state + 0x7c) += 1;
        if (*(short *)(*state + 0x300 + 0xd2) > 0) {
            func_ov107_020c5af8(*state, 0x166, 5, (void *)(*(int *)(*(int *)(*state + 0x3c4)) + 4));
        }
    } else if (stage == 2 && state[0x1e] >= 0x1d55) {
        *((unsigned char *)state + 0x7c) += 1;
        if (*(short *)(*state + 0x300 + 0xd0) > 0) {
            func_ov107_020c5af8(*state, 0x166, 4, (void *)(*(int *)(*(int *)(*state + 0x3c0)) + 4));
        }
    }
    if (*(unsigned char *)state[8] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xb, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
