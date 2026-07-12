/* Read the u16 field at (&data_ov105_020c04c0 + 0xc). */
extern int data_ov105_020c04c0;
int func_ov105_020bf26c(void) {
    return *(unsigned short *)((char *)&data_ov105_020c04c0 + 0xc);
}
