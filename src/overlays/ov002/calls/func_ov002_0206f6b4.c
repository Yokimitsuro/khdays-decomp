extern int func_02030694();
extern int func_ov002_0206f3e4();

int func_ov002_0206f6b4(int arg0) {
    if (func_02030694(arg0) == 0) {
        return 1;
    }
    return func_ov002_0206f3e4((arg0 != 0 ? 3 : 4) & 0xff);
}
