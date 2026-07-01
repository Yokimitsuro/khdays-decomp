extern int *NNS_FndGetNextListObject();

int *func_ov000_02055b48(char *r4, int r5) {
    int *r1;

    r1 = 0;
    if (r5 >= 0) {
        r1 = NNS_FndGetNextListObject(r4 + 0x4a38, 0);
        if (r1 != 0) {
            r4 += 0x238;
            do {
                if (r1[3] == r5)
                    break;
                r1 = NNS_FndGetNextListObject(r4 + 0x4800, r1);
            } while (r1 != 0);
        }
    }
    return r1;
}
