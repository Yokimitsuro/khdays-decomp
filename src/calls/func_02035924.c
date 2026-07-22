/* True when every one of the func_0203595c(a) entries of record `a` has a non-zero
 * halfword at +0xba (stride 4). */
extern int func_0203595c(int a);
extern unsigned char data_0204c678[];

int func_02035924(int a) {
    int ok = 1;
    int n = func_0203595c(a);
    int i = 0;
    unsigned char *e;
    if (n > 0) {
        e = data_0204c678 + a * 260;
        do {
            if (*(unsigned short *)(e + 0xba) == 0) {
                ok = 0;
                break;
            }
            i = i + 1;
            e = e + 4;
        } while (i < n);
    }
    return ok;
}
