/* Rise tick of the ov277 enemy's pillar: the pillar follows the +0xc owner's +0x3c8 bone, lifted to
 * 0.125 above the owner's +0xb4 floor; the +4 clock runs up at the owner's rate and the +0x10 stage
 * advances at 2.5, then at 3.13 and 3.33 with rumble effects 0xb and 0xc (sound 0x165) at the pillar.
 * Once the pillar's +0xad rig is idle its actions 0/2/4/1 are enabled, its animation stops and
 * 020ce734 follows. */
struct Vec3 { int x, y, z; };
extern void func_0203ca30(int srt, struct Vec3 *pos);
extern void func_02033d0c(int id, int kind, struct Vec3 *pos, int flag);
extern void func_0203b9fc(int obj, int slot, int a, int b);
extern void func_0203c7ac(int obj, int a);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov277_020ce734(void);
void func_ov277_020ce5b0(int param_1) {
    int *node = *(int **)(param_1 + 4);
    struct Vec3 pos;

    pos = *(struct Vec3 *)(*(int *)(node[3] + 0x3c8) + 0x14);
    pos.y = *(int *)(node[3] + 0xb4) + 0x200;
    func_0203ca30(node[0] + 4, &pos);
    node[1] += *(int *)(*(int *)param_1 + 0x2c);
    if (*((unsigned char *)node + 0x10) == 0 && node[1] >= 0x2800) {
        *((unsigned char *)node + 0x10) += 1;
    } else if (*((unsigned char *)node + 0x10) == 1 && node[1] >= 0x3214) {
        *((unsigned char *)node + 0x10) += 1;
        func_02033d0c(0x165, 0xb, &pos, 0);
    } else if (*((unsigned char *)node + 0x10) == 2 && node[1] >= 0x3547) {
        *((unsigned char *)node + 0x10) += 1;
        func_02033d0c(0x165, 0xc, &pos, 0);
    }
    if (*(unsigned char *)(node[0] + 0xad) == 0) {
        func_0203b9fc(node[0], 0, 1, 0);
        func_0203b9fc(node[0], 2, 1, 0);
        func_0203b9fc(node[0], 4, 1, 0);
        func_0203b9fc(node[0], 1, 1, 0);
        func_0203c7ac(node[0], 0);
        func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov277_020ce734);
        return;
    }
}
