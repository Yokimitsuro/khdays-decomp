/* Records the three fields of the pending request at +0xb46ec of the block held by
 * data_0204c234; each write re-reads the block pointer as the ROM does. */
extern char *data_0204c234;

void func_02033f50(int a, int b, int c) {
    *(int *)(data_0204c234 + 0xb46ec) = a;
    *(int *)(data_0204c234 + 0xb46f0) = b;
    *(short *)(data_0204c234 + 0xb46f4) = (short)c;
}
