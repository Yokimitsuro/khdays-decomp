/* Marks all four sub-nodes as needing a refresh. */
void func_ov257_020d2bf0(int *self) {
    int *s = (int *)self[1];
    int i;
    for (i = 0; i < 4; i++) {
        char *node = *(char **)(*s + (i << 2) + 0x3a4);
        *(int *)(node + 0x5c) |= 2;
    }
}
