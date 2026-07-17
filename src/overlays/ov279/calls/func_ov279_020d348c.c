/*
 * func_ov279_020d348c -- x3. AI-state tick: advance a timer, blink a flag by counter parity, dispatch.
 * state[1] += owner_delta (then FX_Inv(state[1], 0x1000) for its side path, result unused).
 * Increment the frame counter state[2] and write its parity into bit1 of *(*(state[0]+0x384))+0x5c.
 * While state[1] < 0x800 return. Once past: clear that bit1 and hand off via 0203c640(self).
 */
extern int  FX_Inv(int x, int k);
extern void func_0203c640(int self);

void func_ov279_020d348c(int *self) {
    int *state = (int *)self[1];
    int q;

    state[1] += *(int *)(*self + 0x2c);
    FX_Inv(state[1], 0x1000);
    state[2] += 1;
    q = *(int *)(*state + 0x384);
    *(int *)(q + 0x5c) = (*(int *)(q + 0x5c) & ~2) | ((unsigned int)(state[2] << 0x1f) >> 0x1e);
    if (state[1] < 0x800) {
        return;
    }
    q = *(int *)(*state + 0x384);
    *(int *)(q + 0x5c) &= ~2;
    func_0203c640((int)self);
}
