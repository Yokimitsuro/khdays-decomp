extern int func_020301c8();

void func_ov000_02053d18(int a, int b, int c, int d, int e, int sel) {
    int pool;
    switch (sel) {
    case 1:
        pool = 0x821;
        break;
    case 2:
        pool = 0x411;
        break;
    default:
        pool = 0x209;
        break;
    }
    func_020301c8(a, b + 1, c + 1, 1, pool, e);
    func_020301c8(a, b, c, d, pool, e);
}
