struct vec3 { int x, y, z; };

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(int *out, int *tbl, int r);
extern void func_0203c9d0(int dst, int *src);
extern int data_02042264;
extern int data_02041dc8;

// Recompute the node's scalar from its stored triple, build the derived vector
// (into node[0]+0xa0), shift the previous target triple into node[0]+0xf0.. and
// reload the default triple (data_02041dc8) into node[7..9].
void func_ov120_020cca40(int *this)
{
    int *node = (int *)this[1];
    int scratch[4];
    node[4] = func_0203d040(node[4], node[5], node[6], 0);
    func_0202f188(scratch, &data_02042264, node[4]);
    func_0203c9d0(node[0] + 0xa0, scratch);
    {
        struct vec3 *triple = (struct vec3 *)(node + 7);
        *(struct vec3 *)(node[0] + 0xf0) = *triple;
        *triple = *(struct vec3 *)&data_02041dc8;
    }
}
