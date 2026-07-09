extern int func_0203595c();
extern int data_0204c678;

void func_020359b4(int arg0, unsigned short *arg1) {
    unsigned int n = func_0203595c(arg0);
    int i = 0;
    if ((int)n > 0) {
        unsigned short *p = (unsigned short *)((int)&data_0204c678 + arg0 * 0x104 + 0xba);
        do {
            if (*p == 0) {
                *p = *arg1;
                p[1] = arg1[1];
                return;
            }
            i++;
            p += 2;
        } while (i < (int)n);
    }
}
