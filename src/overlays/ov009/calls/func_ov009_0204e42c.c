/* Return the address (*(&data+4)) + 0x9500. */
extern int data_ov009_020563e4;
int func_ov009_0204e42c(void) {
    return *(int *)((char *)&data_ov009_020563e4 + 4) + 0x9500;
}
