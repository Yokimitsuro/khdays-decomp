struct b1 { unsigned char b : 1; };
struct v3 { int a, b, c; };
extern void func_ov099_020bb594(void *p);
extern void func_ov099_020bb9d4(void *this);
extern void func_0202aa9c(void *p);

void func_ov099_020bb860(char *this) {
    char *g = *(char **)(this + 0xdb4);
    int i;
    char *p;
    if (((struct b1 *)(g + 0x694))->b == 0) return;
    p = this + 0x234;
    for (i = 0; i < 8; i++) {
        func_ov099_020bb594(p);
        p += 0x170;
    }
    func_ov099_020bb9d4(this);
    if (*(int *)(this + 0x14) != 1) return;
    *(struct v3 *)(this + 0xbc) = *(struct v3 *)(g + 0x48c);
    func_0202aa9c(this + 0x18);
}
