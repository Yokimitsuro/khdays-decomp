/* Tail-call 02033e48 with the +0x10 field of *(param+4). */
extern int func_02033e48(int);
int func_ov107_020cb164(int param_1) {
    return func_02033e48(*(int *)(*(int *)(param_1 + 4) + 0x10));
}
