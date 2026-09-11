struct vec3i { int x, y, z; };
struct Flags17a { char pad[0x17a]; unsigned char ready : 1; };

extern void func_01ffa724(int factor, void *src, void *dst);
extern void func_ov297_020d406c();
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int a, int i, int v);
extern void func_ov297_020d4ff0(int this_);

void func_ov297_020d4f6c(int this_) {
    int node = *(int *)(this_ + 4);
    void *v = (void *)(node + 0x1c);

    *(struct vec3i *)(node + 0x10) = *(struct vec3i *)v;
    *(int *)(node + 0x14) = *(int *)(node + 0x4c);
    *(int *)(node + 0x4c) = *(int *)(node + 0x4c) - 0x80;
    func_01ffa724(0xe00, v, v);
    if (!((struct Flags17a *)(*(int *)node))->ready) return;
    func_ov297_020d406c(*(int *)node, 3);
    func_ov107_020c9264(*(int *)node, 4, 0);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov297_020d4ff0);
}
