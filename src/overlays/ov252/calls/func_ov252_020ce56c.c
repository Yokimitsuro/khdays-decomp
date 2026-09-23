/* Reward handler of the ov252 actor: sound 0x148/0x10 plays at its +8 point, marker `n` lights and
 * marker n - 1 dims (020cdd30), and the next move is 8 unless it is already current. */
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_ov252_020cdd30(int *state, int index, int on);

void func_ov252_020ce56c(char *self, int n)
{
    int *state = *(int **)(self + 0x214);

    func_ov107_020c5af8((int)self, 0x148, 0x10, (void *)state[2]);
    func_ov252_020cdd30(state, n, 0);
    func_ov252_020cdd30(state, n - 1, 1);
    if (*(signed char *)(*state + 0x1c6) != 8) {
        *(signed char *)(*state + 0x1c7) = 8;
    }
}
