void func_ov264_020ceab4(char *obj) {
    int i = 0;
    if (*(int *)(obj + 0x8c) > 0) {
        int off = 0;
        do {
            char *base = *(char **)(obj + 0x90);
            int v = *(int *)(base + off);
            char *elem = base + off;
            if (v > 0) {
                int t = *(int *)(elem + 4) - 0x3c;
                *(int *)(elem + 4) = t;
                if (t < 0x80) {
                    *(int *)elem = 0;
                }
            }
            i++;
            off += 0x38;
        } while (i < *(int *)(obj + 0x8c));
    }
}
