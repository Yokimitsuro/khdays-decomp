extern void func_020158b0(int *arg0);
extern void func_0202aa9c(unsigned short *arg0);
void func_ov022_02093400(unsigned char *arg0) {
    int i;
    unsigned char *p;
    unsigned short *q;
    if ((*arg0 & 1) == 0) return;
    if ((*arg0 & 4) == 0) return;
    i = 0;
    p = arg0 + 0xb4;
    q = (unsigned short *)(arg0 + 4);
    do {
        func_020158b0((int *)p);
        func_0202aa9c(q);
        i++;
        p += 0x108;
        q += 0x84;
    } while (i < 9);
}
