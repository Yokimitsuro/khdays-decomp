/*
 * func_ov201_020d53a8 -- x3 (ov200/...). Reset the ring buffer to its idle state.
 * state = *(param1+4). Install the tick callback *(*state+0x78) = &020d1708, back-link
 * *(*state+0x84) = state, clear bit 1 of *(*state+0x5c). Kick the sub-object via
 * 0202accc(*(*state+0x88), 0, *(*state+0x88)+0xe0, 0). Then for each of the *(*state+0x8c) slots in
 * the ring at *(*state+0x90): zero slot[0] and set slot+4 = 0x1000. Finally reset the write index
 * state[1] = 0.
 */
extern void func_0202accc(int a, int b, int c, int d);
extern void func_ov201_020d5348(void);

void func_ov201_020d53a8(int param1) {
    int *state = *(int **)(param1 + 4);
    int i;

    *(int *)(*state + 0x78) = (int)&func_ov201_020d5348;
    *(int **)(*state + 0x84) = state;
    *(unsigned int *)(*state + 0x5c) &= ~2;
    func_0202accc(*(int *)(*state + 0x88), 0, *(int *)(*state + 0x88) + 0xe0, 0);
    for (i = 0; i < *(int *)(*state + 0x8c); i++) {
        int ring = *(int *)(*state + 0x90);
        *(int *)(ring + i * 0x38) = 0;
        *(int *)(ring + i * 0x38 + 4) = 0x1000;
    }
    state[1] = 0;
}
