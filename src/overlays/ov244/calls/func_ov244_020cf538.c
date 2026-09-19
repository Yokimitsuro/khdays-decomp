/* Pounce hold entry: places the owner's transform (+4) at a point built from the +0x3d8 item's
 * +0x14 x / +0x1c z and the +0x3b8 item's +0x18 y, points the entry's +0x14 at the owner's +0xad
 * byte, clears bit 1 of the owner's +0x5c, binds its channels 0 / 4 / 1 / 2 with (1, 0),
 * re-inits it, clears the +8 timer and +0x10 latch and moves the node to 020cf638. */
struct Vec3 { int x, y, z; };
extern void func_0203ca30(int srt, struct Vec3 *pos);
extern void func_0203b9fc(int obj, int slot, int a, int b);
extern void func_0203c7ac(int obj, int a);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov244_020cf638(void);

void func_ov244_020cf538(int param_1) {
    int *node = *(int **)(param_1 + 4);
    node[6] = *(int *)(*(int *)(node[1] + 0x3d8) + 0x14);
    node[7] = *(int *)(*(int *)(node[1] + 0x3b8) + 0x18);
    node[8] = *(int *)(*(int *)(node[1] + 0x3d8) + 0x1c);
    func_0203ca30(node[0] + 4, (struct Vec3 *)(node + 6));
    node[5] = node[0] + 0xad;
    *(int *)(node[0] + 0x5c) &= ~2;
    func_0203b9fc(node[0], 0, 1, 0);
    func_0203b9fc(node[0], 4, 1, 0);
    func_0203b9fc(node[0], 1, 1, 0);
    func_0203b9fc(node[0], 2, 1, 0);
    func_0203c7ac(node[0], 0);
    node[2] = 0;
    *((unsigned char *)node + 0x10) = 0;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov244_020cf638);
}
