struct vec3 { int x, y, z; };

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(int *out, int *tbl, int r);
extern void func_0202ed60(int *out, int *tbl, int v);
extern void func_0202ef54(int *out, int *a, int *b);
extern void func_0203c9d0(int dst, int *src);
extern int data_02042264;
extern int data_02041dc8;

// Recompute the node scalar, build the combined transform (blend of the table
// vector and the object matrix at node[0]+0x124) into node[0]+0xa0, tick down the
// countdown at node[0x10], and shift/reload the vector triple at node[5..7].
void func_ov139_020cc920(int *this)
{
    int *node = (int *)this[1];
    int delta[4];
    int base[4];
    node[2] = func_0203d040(node[2], node[3], node[4], 0);
    func_0202f188(delta, &data_02042264, node[2]);
    func_0202ed60(base, &data_02042264, node[0] + 0x124);
    func_0202ef54(base, base, delta);
    func_0203c9d0(node[0] + 0xa0, base);
    if (node[0x10] >= 0) {
        node[0x10] = node[0x10] - *(int *)(*this + 0x2c);
    }
    {
        struct vec3 *triple = (struct vec3 *)(node + 5);
        *(struct vec3 *)(node[0] + 0xf0) = *triple;
        *triple = *(struct vec3 *)&data_02041dc8;
    }
}
