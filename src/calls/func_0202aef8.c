extern unsigned short **func_01fff75c(void);

int func_0202aef8(void) {
    unsigned short **p;
    p = func_01fff75c();
    if (!p) {
        return 0;
    }
    return p[2][2] << 12;
}
