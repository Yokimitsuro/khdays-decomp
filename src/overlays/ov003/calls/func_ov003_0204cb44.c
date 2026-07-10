extern char data_ov003_0204f9a0[];
struct Row0204cb44 { unsigned short a, b; char pad[0x40 - 4]; };
void func_ov003_0204cb44(int obj) {
    struct Row0204cb44 *e = (struct Row0204cb44 *)(obj + 0x580);
    int v = (3 - *(int *)(*(int *)data_ov003_0204f9a0 + 0x1e14)) * 4;
    int b = v + 0x40;
    e[0].a = b | 0xc000;
    e[0].b = (b + 1) | 0xc000;
    e[1].a = (b + 2) | 0xc000;
    e[1].b = (b + 3) | 0xc000;
}
