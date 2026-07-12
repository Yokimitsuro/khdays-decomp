/* Read the field at (&data_ov105_020c04c0 + 0x30). */
extern int data_ov105_020c04c0;
int func_ov105_020bf25c(void) {
    return *(int *)((char *)&data_ov105_020c04c0 + 0x30);
}
