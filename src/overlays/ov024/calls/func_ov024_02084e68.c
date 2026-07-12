/* Return +0x48 of the primary or fallback ov024 object, or -1 if neither exists. */
extern int data_ov024_02093a2c;
int func_ov024_02084e68(void) {
    int a = (&data_ov024_02093a2c)[2];
    if (a != 0) return *(int *)(a + 0x48);
    a = (&data_ov024_02093a2c)[3];
    if (a != 0) return *(int *)(a + 0x48);
    return -1;
}
