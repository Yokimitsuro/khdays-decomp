extern void func_0202accc(int a, int b, int c, int d);
extern void func_0203c634(int node, int slot, void *cb);
extern void func_ov264_020ceab4(void);
extern void func_ov264_020cebc0(void);

void func_ov264_020ceb10(int node) {
    int *state = *(int **)(node + 4);
    *(void **)(*state + 0x78) = (void *)func_ov264_020ceab4;
    *(int **)(*state + 0x84) = state;
    *(unsigned *)(*state + 0x5c) &= ~2;
    func_0202accc(*(int *)(*state + 0x88), 0, *(int *)(*state + 0x88) + 0xe0, 0);
    {
        int i = 0;
        if (*(int *)(*state + 0x8c) > 0) {
            int off = 0;
            do {
                int base = *(int *)(*state + 0x90);
                i++;
                *(int *)(base + off) = 0;
                *(int *)(base + off + 4) = 0;
                off += 0x38;
            } while (i < *(int *)(*state + 0x8c));
        }
    }
    state[1] = 0;
    func_0203c634(node, *(signed char *)(node + 0x20), (void *)func_ov264_020cebc0);
}
