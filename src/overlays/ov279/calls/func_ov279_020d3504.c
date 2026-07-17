/*
 * func_ov279_020d3504 -- x3. Twin of func_ov119_020cf84c: advance a timer, blink a flag by counter
 * parity, dispatch -- but the once-past branch SETS bit1 of *(*(state[0]+0x384))+0x5c (|= 2) instead
 * of clearing it. state[1] += owner_delta; FX_Inv(state[1], 0x1000) (result unused); state[2]++ and
 * write its parity into bit1. While state[1] < 0x800 return. Once past: set bit1, hand off 0203c640.
 */
extern int  FX_Inv(int x, int k);
extern void func_0203c640(int self);

void func_ov279_020d3504(int *self) {
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
    *(int *)(q + 0x5c) |= 2;
    func_0203c640((int)self);
}
