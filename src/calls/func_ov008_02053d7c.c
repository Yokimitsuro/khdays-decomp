extern int func_02024da4();
extern int MI_CpuCopy8();

struct Entry {
    int field0;
    short field4;
    unsigned short field6;
};

int func_ov008_02053d7c(int a, int b) {
    struct Entry buf[4];
    int i;
    int last;

    last = func_02024da4(buf) - 1;
    for (i = last; i >= 0; i--) {
        if (buf[i].field6 == 0) {
            return MI_CpuCopy8(&buf[i], b, 8);
        }
    }
    return MI_CpuCopy8(&buf[last], b, 8);
}
