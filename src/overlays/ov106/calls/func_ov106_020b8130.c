/* Tail-call func_02021048 with the global at data_ov106_020b8b60. */
extern int func_02021048(int arg);
extern int data_ov106_020b8b60;
int func_ov106_020b8130(void) {
    return func_02021048(*(int *)&data_ov106_020b8b60);
}
