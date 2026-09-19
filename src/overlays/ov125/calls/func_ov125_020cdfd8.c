/* Start the ov125 enemy's hop: cancel the current action (mode 6, flag 1), clear the hop
 * timers (+0x40, +0x48, +0x2c), roll a random hop direction (-0x1000 or +0x1000) into +0x44,
 * seed the +0x3c counter with 15 times the owner's +0x2c rate, the +0x4c count with 5 + rand(6)
 * and the +0x50 count with 7 + rand(4), then register the hop think callback. */
extern void func_ov107_020c9264(int owner, int mode, int b);
extern int func_02023eb4();
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov125_020ce078(void);

void func_ov125_020cdfd8(int self) {
    int v;
    int *node = *(int **)(self + 4);
    func_ov107_020c9264(*node, 6, 1);
    node[0x10] = 0;
    node[0x11] = func_02023eb4(2) + (v - v) != 0 ? -0x1000 : 0x1000;
    node[0x12] = 0;
    node[0xf] = *(int *)(*(int *)self + 0x2c) * 0x1e / 2;
    node[0x13] = func_02023eb4(6) + 5;
    node[0xb] = 0;
    node[0x14] = func_02023eb4(4) + 7;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov125_020ce078);
}
