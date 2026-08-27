extern void func_0203c5c0(int a, int b, int c, void *cb, int d, void *out);
extern void func_ov172_020d2274(void);

void func_ov172_020d1fb0(int *node) {
    int *obj;
    func_0203c5c0(node[0xf], 100, 0x50, func_ov172_020d2274, 0, &obj);
    obj[0] = (int)node;
    obj[1] = *(int *)(*obj + 0x9c);
    node[0x85] = (int)obj;
}
