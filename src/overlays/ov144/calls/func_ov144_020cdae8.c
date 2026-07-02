extern void func_0203c634(void *obj, int idx, void *value);
void func_ov144_020cdae8(int *node) {
    int *state = (int *)node[1];
    if (*(unsigned char *)(*(int *)(*state + 0x384) + 0xad) != 0) return;
    {
        int count = 0;
        for (;;) {
            int idx = (state[0x12] + 1) % 5;
            int e;
            state[0x12] = idx;
            e = ((int *)(*state) + idx)[0xf0];
            state[0xf] = e;
            if (e >= 0) break;
            count++;
            if (count >= 5) break;
        }
    }
    *(signed char *)(*state + 0x1c7) = *(signed char *)((char *)state + 0x50);
    func_0203c634(node, *(signed char *)(node + 8), 0);
}
