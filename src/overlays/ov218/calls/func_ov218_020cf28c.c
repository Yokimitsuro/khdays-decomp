/* Tick of an ov218 flash helper: it ends when its owner's +0x394 effect is gone or after eight steps;
 * each 1.0 (+8) it advances its step (+0xc) and plays it on layer 4 of the +4 rig. */
extern void func_0203c640(int *node);
extern void func_0203b9fc(int rig, int channel, int a, int b);

void func_ov218_020cf28c(int *node)
{
    int *state = (int *)node[1];

    if (*(int *)(*state + 0x394) == 0) {
        func_0203c640(node);
        return;
    }
    state[2] += *(int *)(node[0] + 0x2c);
    if (state[2] < 0x1000) {
        return;
    }
    if (state[3] >= 8) {
        func_0203c640(node);
        return;
    }
    state[2] = 0;
    state[3]++;
    func_0203b9fc(state[1], 4, (short)state[3], 1);
}
