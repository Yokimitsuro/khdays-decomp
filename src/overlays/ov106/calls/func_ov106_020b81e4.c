extern char *data_ov106_020b8b60;
/* Push a new entry onto the transition record at ctx+0x8e2c: carry the previous target into
 * slot 0, store the new one, clear the timer, and latch it as previous only for a null mode. */
void func_ov106_020b81e4(int target, int mode) {
    int *e = (int *)((int)data_ov106_020b8b60 + 0x8e2c);
    e[0] = e[4];
    e[1] = target;
    e[3] = mode;
    e[2] = 0;
    if (mode == 0) {
        e[4] = target;
    }
}
