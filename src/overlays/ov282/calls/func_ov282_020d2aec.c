/*
 * func_ov282_020d2aec -- x3 (ov210/211/282). AI-state tick: acquire target, else enter a timed
 * recovery.
 * Acquire (020cab14) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail (0203c634 cb=0). Else fire
 * attack 0x12, set the timer state[0x14]=0x3000, pick a random heading state[0xc]=RandNextScaled(
 * 0x1001)+0x1000, clear state[0xb], and hand off to the 020d2b60 state.
 */
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov107_020c9264(int a, int b, int c);
extern int  func_02023eb4(int mul);
extern void func_ov282_020d2b74(void);

void func_ov282_020d2aec(int *self) {
    int *state = (int *)self[1];
    int target = func_ov107_020cab14(*state, 0);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    func_ov107_020c9264(*state, 0x12, 0);
    state[0x14] = 0x3000;
    state[0xc] = func_02023eb4(0x1001) + 0x1000;
    state[0xb] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov282_020d2b74);
}
