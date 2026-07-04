extern void func_ov017_020807c4();
extern void func_ov002_0207cea4();

void *func_ov017_0208079c(int this_) {
    unsigned char x = *(unsigned char *)(this_ + 0x1b4);
    if (x == 5) {
        return func_ov017_020807c4;
    }
    if (x == 7) {
        return func_ov002_0207cea4;
    }
    return 0;
}
