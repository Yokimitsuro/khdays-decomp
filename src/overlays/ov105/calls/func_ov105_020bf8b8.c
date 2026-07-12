/* Store param_1 into the field at (&data_ov105_020c04c0 + 0x38). */
extern int data_ov105_020c04c0;
void func_ov105_020bf8b8(int param_1) {
    *(int *)((char *)&data_ov105_020c04c0 + 0x38) = param_1;
}
