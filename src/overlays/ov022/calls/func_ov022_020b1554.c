extern int data_ov022_020b2eb8;
int func_ov022_020b1554(int arg0) {
    int r = 1;
    int i = 0;
    int e = data_ov022_020b2eb8 + 0x10 + arg0 * 0xa8;
    do {
        if ((unsigned char)(*(unsigned char *)(e + 3) + 0xff) <= 1) {
            r = 0;
            break;
        }
        i++;
        e += 0x38;
    } while (i < 3);
    return r;
}
