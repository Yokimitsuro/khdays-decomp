/* NONMATCHING: semantically complete, register-allocation/scheduling tie. The event broadcast
 * (active-gate callback, sign-extended +0x14 dispatch, sequence-stamp walk, three subscriber
 * registrations, tail to 020c4e9c) is all present; residue is ~8 instructions of callee-saved
 * coloring (cb in r7 where the ROM uses r2 and re-reads) and temp scheduling across a 172B body
 * with three loops. Behaviour: see the plate comment. */
extern int func_01fffd8c(int list);
extern void func_0203bfb4(int ctx, int *subscriber, unsigned int marker);
extern void func_ov107_020c4e9c(int obj, int scene);

void func_ov107_020c7b70(int obj, int scene) {
    void (*cb)(int, int);
    int i;

    if (*(int *)(obj + 0x50) == 1 && *(void (**)(void))(obj + 0x30) != 0) {
        (*(void (**)(void))(obj + 0x30))();
    }
    {
        int sign = (*(int *)(scene + 0x40) << 0x1e) >> 0x1f;
        cb = *(void (**)(int, int))(obj + 0x14);
        if (cb != 0) {
            cb(obj, sign);
        }
    }
    {
        char seq = 0;
        int node = func_01fffd70(obj + 0x22c);
        while (node != 0) {
            *(char *)(node + 4) = seq;
            seq++;
            node = func_01fffd8c(obj + 0x22c);
        }
    }
    func_0203bfb4(*(int *)(scene + 0x104), *(int **)(obj + 0x1a8), (unsigned int)cb);
    {
        int *node = (int *)func_01fffd70(obj + 0x260);
        while (node != 0) {
            func_0203bfb4(*(int *)(scene + 0x104), (int *)*node, (unsigned int)cb);
            node = (int *)func_01fffd8c(obj + 0x260);
        }
    }
    {
        int cur = obj;
        for (i = 0; i < 8; i++) {
            if (*(int *)(cur + 0x350) != 0) {
                int *sub = *(int **)(*(int *)(cur + 0x350) + 0x14);
                if (sub != 0) {
                    func_0203bfb4(*(int *)(scene + 0x104), sub, (unsigned int)cb);
                }
            }
            cur += 4;
        }
    }
    func_ov107_020c4e9c(obj, scene);
}
