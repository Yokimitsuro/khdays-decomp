struct v3 { int a, b, c; };
extern void func_0203b9fc(void *p, int a, int b, int c);
extern int data_02041dc8[];

void func_ov264_020cd138(char *this, int param2) {
    struct v3 buf = *(struct v3 *)data_02041dc8;
    *(struct v3 *)(this + 0x3b4) = buf;
    *(struct v3 *)(this + 0x424) = buf;
    func_0203b9fc(*(void **)(this + 0x420), 0, (short)param2, 0);
}
