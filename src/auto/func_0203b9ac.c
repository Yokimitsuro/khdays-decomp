/* Reset the 5 slot rows: id/aux halfwords to -1 and the word field to zero.
 * `v = i = 0` is deliberate -- the ROM materialises the zero once and copies it
 * (mov ip,#0 / mov r2,ip); two separate `= 0` initialisers do not reproduce that. */
void func_0203b9ac(int param_1, int param_2) {
    int i, v;

    if (param_2 == 0) {
        param_2 = *(int *)(param_1 + 0x88) + 0xe0;
    }
    *(int *)(param_1 + 0x8c) = param_2;

    v = i = 0;
    do {
        ((short *)(*(int *)(param_1 + 0x88)))[i + 1] = -1;
        ((short *)(*(int *)(param_1 + 0x88)))[i + 0x65] = -1;
        ((int *)(*(int *)(param_1 + 0x88)))[i + 3] = v;
        i = i + 1;
    } while (i < 5);
}
