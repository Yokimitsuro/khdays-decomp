extern int func_ov002_02052650();

void func_ov002_020527e8(int arg0) {
    if (*(int *)arg0 != 3) {
        return;
    }
    int p = *(int *)(arg0 + 0x3c);
    if (p == 0) {
        return;
    }
    func_ov002_02052650(arg0, p);
}
