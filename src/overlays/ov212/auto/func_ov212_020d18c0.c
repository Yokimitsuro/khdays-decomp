void func_ov212_020d18c0(char *obj) {
    int i = 0;
    if (*(int *)(obj + 0x8c) > 0) {
        int off = 0;
        do {
            char *base = *(char **)(obj + 0x90);
            int v = *(int *)(base + off);
            char *elem = base + off;
            if (v > 0) {
                *(int *)(elem + 4) = *(int *)(elem + 4) - 0x3c;
                *(int *)elem = *(int *)elem - 0x78;
                if (*(int *)(elem + 4) <= 0) {
                    *(int *)elem = 0;
                }
            }
            i++;
            off += 0x38;
        } while (i < *(int *)(obj + 0x8c));
    }
}
