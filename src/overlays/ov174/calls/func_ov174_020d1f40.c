extern int func_ov107_020cab14(int a, int b, int c, int d);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov174_020d1fac(void);

// Query the node's target; cache it at node[3]. If none was found, force
// sub-state 2 and advance with no callback; otherwise switch mode 2, clear the
// tracking fields and advance with the follow-up callback.
void func_ov174_020d1f40(int *this, int p2, int p3, int p4)
{
    int *node = (int *)this[1];
    int found = func_ov107_020cab14(node[0], 0, p3, p4);
    node[3] = found;
    if (found == 0) {
        *(signed char *)(node[0] + 0x1c7) = 2;
        func_0203c634((int)this, *(signed char *)((int)this + 0x20), 0);
        return;
    }
    func_ov107_020c9264(node[0], 2, 0);
    node[0x12] = 0;
    *(signed char *)((int)node + 0x84) = 0;
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov174_020d1fac);
}
