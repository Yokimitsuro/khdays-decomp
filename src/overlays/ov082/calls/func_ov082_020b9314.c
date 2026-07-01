extern int func_0202aa9c();

struct Vec3 { int a, b, c; };

void func_ov082_020b9314(char *this) {
    char *p = *(char **)(this + 0xdb4);
    unsigned short h;

    if (*(int *)(this + 0x124) != 1) {
        return;
    }
    h = *(unsigned short *)(*(char **)(p + 0x20) + 0x80);
    *(short *)(this + 0x1a4) = (unsigned short)(h - 0x8000) + 0x8000;
    *(unsigned short *)(this + 0x128) |= 0x20;
    *(struct Vec3 *)(this + 0x1cc) = *(struct Vec3 *)(p + 0x904);
    func_0202aa9c(this + 0x128);
}
