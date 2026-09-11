struct vec3 { int x, y, z; };
struct b1 { unsigned char b:1; };

extern void func_01ffa724(int factor, int *src, int *dst);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov283_020cdae4(void);

void func_ov283_020cda58(int *this) {
    int node = this[1];
    struct vec3 *v = (struct vec3 *)(node + 0x1c);
    *(struct vec3 *)(node + 0x10) = *v;
    *(int *)(node + 0x14) = *(int *)(node + 0x58);
    *(int *)(node + 0x58) = *(int *)(node + 0x58) - 0x80;
    func_01ffa724(0xe00, (int *)v, (int *)v);

    if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) {
        int obj = *(int *)node;
        if (!((struct b1 *)(obj + 0x17a))->b) {
            return;
        }
    }

    func_ov107_020c9264(*(int *)node, 4, 0);
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov283_020cdae4);
}
