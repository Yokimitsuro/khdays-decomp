extern void func_ov147_020ccb30();
extern void func_0203c634();

struct w3 { int a, b, c; };

void func_ov147_020cd668(int this_) {
    int node = *(int *)(this_ + 4);
    func_ov147_020ccb30(node, *(struct w3 *)(node + 0x28), 1);
    if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)node + 0x1c7) = 5;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
