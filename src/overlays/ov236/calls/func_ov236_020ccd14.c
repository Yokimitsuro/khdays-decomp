/* func_ov236_020ccd14 -- forward a hit event to both sub-objects' +0x1f4 handlers (skipping either
 * if it has none) and then to the base handler. The two arguments ride through in r1/r2 the whole
 * way, which is why the ROM sets them up only once. */
extern void func_ov107_020c88dc(int obj, int a, int b);

void func_ov236_020ccd14(int obj, int a, int b) {
    void (*cb)(int, int, int);
    int sub;
    sub = *(int *)(obj + 0x3b4);
    cb = *(void (**)(int, int, int))(sub + 0x1f4);
    if (cb != 0) {
        cb(sub, a, b);
    }
    sub = *(int *)(obj + 0x3b8);
    cb = *(void (**)(int, int, int))(sub + 0x1f4);
    if (cb != 0) {
        cb(sub, a, b);
    }
    func_ov107_020c88dc(obj, a, b);
}
