struct v3 { int x, y, z; };
struct b1 { unsigned char b:1; };

extern void func_01ffa724(int a, void *b, void *c);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int node, int slot, void *cb);
extern void func_ov114_020cd97c(void);

void func_ov114_020cd8f8(int node) {
    int state = *(int *)(node + 4);
    struct v3 *src = (struct v3 *)(state + 0x5c);
    *(struct v3 *)(state + 0x50) = *src;
    func_01ffa724(0xb00, src, src);
    if (*(unsigned char *)(*(int *)(state + 0xc)) != 0) return;
    {
        int obj = *(int *)state;
        if (((struct b1 *)(obj + 0x17a))->b || ((struct b1 *)(obj + 0x17c))->b) {
            func_ov107_020c9264(obj, 9, 1);
            func_0203c634(node, *(signed char *)(node + 0x20), &func_ov114_020cd97c);
        }
    }
}
