struct vec3 { int x, y, z; };

extern void func_01ffa724(int s, int dst, int src);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov283_020cda58(void);

// Snapshot the working vector (node+0x1c) into node+0x10, override its Y with the
// descent value (node[0x13]) and decrement that by 0x80, then scale the vector by
// 0xe00. Once the linked object is ready (node[1][0xad]==0), switch to mode 3.
void func_ov283_020cd9e0(int *this)
{
    int node = this[1];
    struct vec3 *v = (struct vec3 *)(node + 0x1c);
    *(struct vec3 *)(node + 0x10) = *v;
    *(int *)(node + 0x14) = *(int *)(node + 0x58);
    *(int *)(node + 0x58) = *(int *)(node + 0x58) - 0x80;
    func_01ffa724(0xe00, (int)v, (int)v);
    if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*(int *)node, 3, 0);
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov283_020cda58);
}
