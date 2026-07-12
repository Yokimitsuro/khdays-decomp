/* Store the aligned pair into ov024 slots +0x18/+0x14 and clear +8. */
extern int data_ov024_0209bb30;
void func_ov024_020865d8(int param_1, int param_2) {
    (&data_ov024_0209bb30)[6] = param_1;
    (&data_ov024_0209bb30)[5] = param_2 & ~3;
    (&data_ov024_0209bb30)[2] = 0;
}
