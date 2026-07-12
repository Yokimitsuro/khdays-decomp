/* Unless the busy byte at *(child+4)+0xad is set, mark sub-state 2. */
void func_ov283_020ce95c(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) == 0)
        *(signed char *)(*(int *)child + 0x1c7) = 2;
}
