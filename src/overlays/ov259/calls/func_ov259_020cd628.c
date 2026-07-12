/* Store param_2 at (child)+0xa4; set +0x90 to param_3 or the owner rate. */
void func_ov259_020cd628(int param_1, int param_2, int param_3) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0xa4) = param_2;
    if (param_3 != 0) *(int *)(child + 0x90) = param_3;
    else *(int *)(child + 0x90) = *(int *)(*(int *)param_1 + 0x2c);
}
