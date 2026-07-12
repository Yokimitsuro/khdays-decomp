/* Read the word at +0x6a50 of the ov000 global object, or 0 if absent. */
extern int data_ov000_0205ac24;
int func_ov000_020532d0(void) {
    if (data_ov000_0205ac24 != 0) return *(int *)(data_ov000_0205ac24 + 0x6a50);
    return 0;
}
