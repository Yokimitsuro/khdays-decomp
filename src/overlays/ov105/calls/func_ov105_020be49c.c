/* Store param_1 into the field at (&data_ov105_020c04c0 + 0x24). */
extern int data_ov105_020c04c0;
void func_ov105_020be49c(int param_1) {
    *(int *)((char *)&data_ov105_020c04c0 + 0x24) = param_1;
}
