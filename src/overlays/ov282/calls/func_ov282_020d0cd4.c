/*
 * func_ov282_020d0cd4 -- x3. AI-state tick: fire, seed a random timer, dispatch.
 * state[0x14] = 0. Fire attack 1 (020c9264, flag 1). state[0xc] = RandNextScaled(0xa01) (random
 * duration); state[0xb] = 0 (elapsed); state[0x1a] = 0. Hand off to the 020d0d24 state.
 */
extern void func_ov107_020c9264(int a, int b, int c);
extern int  func_02023eb4();  /* K&R decl: needed for the rand `+ (v - v)` copy artifact */
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov282_020d0d30(void);

void func_ov282_020d0cd4(int *self) {
    int *state = (int *)self[1];
    int v;

    state[0x14] = 0;
    func_ov107_020c9264(*state, 1, 1);
    /* +(v-v) forces the rand result to be copied through `add r0,r0,#0` before the store */
    state[0xc] = func_02023eb4(0xa01) + (v - v);
    state[0xb] = 0;
    state[0x1a] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov282_020d0d30);
}
