/* ov284_ResetEntryList: zero the first word of every 0x38-byte entry in the
   list (count at list+0x8c, entries base at list+0x90), then set flag bit 1 at
   list+0x5c. list is reloaded from mgr each iteration. */
void func_ov284_020cd508(char *obj) {
    char *mgr = *(char **)(obj + 4);
    int i = 0;
    int off;
    char *list = *(char **)(mgr + 4);
    if (*(int *)(list + 0x8c) > 0) {
        off = 0;
        do {
            i++;
            *(int *)(*(char **)(list + 0x90) + off) = 0;
            list = *(char **)(mgr + 4);
            off += 0x38;
        } while (i < *(int *)(list + 0x8c));
    }
    *(int *)(list + 0x5c) |= 2;
}
