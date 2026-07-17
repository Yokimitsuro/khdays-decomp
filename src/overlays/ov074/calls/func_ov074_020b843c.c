/*
 * Apply a mode change to the actor (x4: ov035/054/074/091).
 *
 * `mode - 0x2e` picks a per-mode arm; each arm no-ops when the mode did not change (+0x6bc
 * caches it). 0x2e re-inits; 0x2f clears the block's flag word and rearms the sub-object at
 * +0x10 with 0, firing event 0xd3 phase 0; 0x32 sets the flag word, rearms with 0xf000, fires
 * phase 2 -- and then rewrites mode to 0x2f while caching 0x32 as the mode actually reached;
 * 0x30/0x31 share an arm that fires phase 1 (or 3 for 0x31) and snaps the block's angle at +0xe
 * to the actor's heading minus half a turn. Then 020a384c hands the mode down and it is
 * forwarded to the UI: at/above 0x2e translated first (020519b0 -> 02052024), below straight
 * through (020521a4).
 *
 * MATCHED on the first compile off the ov034/ov046 template. The spellings that carried it:
 * 020521a4 takes FOUR args (see func_ov046_020b3508.c for how that was settled); the source
 * writes the cases in the order 0, 1, 4, 2+3 -- which is what switchorder.py recovers from the
 * body layout -- and every small conditional value here is a zero/one-init plus one conditional
 * set (`v = 1; if (mode == 0x31) v = 3;`, `flag = 0; if (x == 2) flag = 1;`), never a
 * comparison or a ternary.
 */
extern int data_ov074_020b9b80;
extern void WM_EndKeySharing_0x020b89e8(int self);
extern void func_ov074_020b8a24(int *p, int v);
extern void func_ov022_020a4490(int self, int a, int b);
extern void func_ov022_020a384c(int self, int mode);
extern int func_ov002_020519b0(int a, int b, int c);
extern void func_ov002_02052024(void *a, int b, int c, int d, int e);
extern void func_ov002_020521a4(void *a, int b, int c, int d);

void func_ov074_020b843c(int self, int mode) {
    int base = data_ov074_020b9b80;
    int *p = (int *)(base + 0x2ca4);
    int reached = -1;
    int flag;
    int ret;

    switch (mode - 0x2e) {
    case 0:
        if (*(int *)(self + 0x6bc) != mode) { WM_EndKeySharing_0x020b89e8(self); }
        break;
    case 1:
        *p = 0;
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov074_020b8a24((int *)((char *)p + 0x10), 0);
            func_ov022_020a4490(self, 0xd3, 0);
        }
        break;
    case 4:
        *p = 1;
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov074_020b8a24((int *)((char *)p + 0x10), 0xf000);
            func_ov022_020a4490(self, 0xd3, 2);
        }
        mode = 0x2f;
        reached = 0x32;
        break;
    case 2:
    case 3:
        if (*(int *)(self + 0x6bc) != mode) {
            int v = 1;
            if (mode == 0x31) { v = 3; }
            func_ov022_020a4490(self, 0xd3, v);
            *(short *)((char *)p + 0xe) =
                (short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000);
        }
        break;
    }
    func_ov022_020a384c(self, mode);
    flag = 0;
    if (*(signed char *)(self + 0x2bb2) == 2) { flag = 1; }
    if (mode >= 0x2e) {
        ret = func_ov002_020519b0(mode, *(int *)(self + 0x6bc), *(int *)(self + 0xc));
        func_ov002_02052024((void *)(self + 0xf0c), base + 0x2c50, mode, 2, ret);
    } else {
        func_ov002_020521a4((void *)(self + 0xf0c), base + 0x2c50, mode, flag);
    }
    if (reached >= 0) { *(int *)(self + 0x6bc) = reached; }
}
