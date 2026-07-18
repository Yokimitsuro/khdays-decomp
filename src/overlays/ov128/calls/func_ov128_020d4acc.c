extern void func_ov128_020d3ce8(int self);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov128_020d4b40(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct flag17a { unsigned char b0 : 1; };

void func_ov128_020d4acc(int self) {
    int *s = *(int **)(self + 4);
    func_ov128_020d3ce8(self);
    if (!((struct flag17a *)(*s + 0x17a))->b0) return;
    ((struct hw60 *)(*s + 0x60))->hi &= ~0x40;
    func_ov107_020c9264(*s, 6, 0);
    func_0203c634(self, *(signed char *)(self + 0x20), (void *)&func_ov128_020d4b40);
}
