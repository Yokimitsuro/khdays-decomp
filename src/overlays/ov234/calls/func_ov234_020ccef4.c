extern void func_0203c634();

struct hw60 { unsigned short lo : 8, hi : 8; };
struct w3 { int a, b, c; };

void func_ov234_020ccef4(int this_) {
    int node = *(int *)(this_ + 4);
    int obj = *(int *)node;
    if ((((struct hw60 *)(obj + 0x60))->lo & 1) == 0) return;
    *(struct w3 *)(node + 0x1c) = *(struct w3 *)(obj + 0xb0);
    *(signed char *)(*(int *)node + 0x1c7) = *(signed char *)(*(int *)node + 0x1c9);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
