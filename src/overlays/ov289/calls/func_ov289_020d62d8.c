extern unsigned int func_02023eb4(int);
extern void func_ov107_020c9264(int node, int a, int b);
extern void func_0203c634();
extern void func_ov289_020d6378(void);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov289_020d62d8(int this_) {
    int f0 = *(int *)this_;
    int holder = *(int *)(this_ + 4);
    int t = *(int *)(holder + 0x34) + *(int *)(f0 + 0x2c);
    *(int *)(holder + 0x34) = t;
    if (t < 0x2a8) return;
    ((struct hw60 *)(*(int *)holder + 0x60))->hi &= ~0x80;
    *(int *)(*(int *)holder + 0x394) = 1;
    *(int *)(*(int *)holder + 0x38c) = func_02023eb4(0x64) < 0xa;
    func_ov107_020c9264(*(int *)holder, 0, 0);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov289_020d6378);
}
