/* Read the word at +0x95cc of the second ov009 global object. */
extern int data_ov009_020563e4;
int func_ov009_0204cb84(void) {
    return *(int *)((&data_ov009_020563e4)[1] + 0x95cc);
}
