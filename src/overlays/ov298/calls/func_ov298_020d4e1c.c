struct vec3 { int x, y, z; };
struct b1 { unsigned char b:1; };

extern void func_01ffa724(int s, int dst, int src);
extern void func_ov298_020d3f50();
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov298_020d4ea0(void);

void func_ov298_020d4e1c(int *this)
{
    int node = this[1];
    struct vec3 *v = (struct vec3 *)(node + 0x1c);
    *(struct vec3 *)(node + 0x10) = *v;
    *(int *)(node + 0x14) = *(int *)(node + 0x4c);
    *(int *)(node + 0x4c) = *(int *)(node + 0x4c) - 0x80;
    func_01ffa724(0xe00, (int)v, (int)v);
    if (!((struct b1 *)(*(int *)node + 0x17a))->b) {
        return;
    }
    func_ov298_020d3f50(*(int *)node, 3);
    func_ov107_020c9264(*(int *)node, 4, 0);
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov298_020d4ea0);
}
