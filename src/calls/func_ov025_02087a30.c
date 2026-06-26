extern int func_02024da4();
extern int func_01ff88c4();

struct Entry {
    int field0;
    short field4;
    unsigned short field6;
};

int func_ov025_02087a30(int a, int b) {
    struct Entry buf[4];
    int i;
    int last;

    last = func_02024da4(buf) - 1;
    for (i = last; i >= 0; i--) {
        if (buf[i].field6 == 0) {
            return func_01ff88c4(&buf[i], b, 8);
        }
    }
    return func_01ff88c4(&buf[last], b, 8);
}
