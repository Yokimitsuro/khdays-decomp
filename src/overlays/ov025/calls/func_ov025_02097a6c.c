extern int func_ov025_0209010c();
extern void func_020235a8();

void func_ov025_02097a6c(int arg0) {
    int i = 1;
    do {
        if (func_ov025_0209010c(arg0, i)) func_020235a8(i + 0x37c9);
        i++;
    } while (i < 0x277);
}
