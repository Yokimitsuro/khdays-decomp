extern int func_ov107_020cab14(int a, int b);
extern int func_ov107_020c9f48(int src, int *out);
extern void func_0202f384(int dst, int mtx, int *v);
extern void func_01ffa724(int s, int dst, int src);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov140_020d0f24(void);

// Acquire the target (node[1]); if none, force sub-state 2 and bail. Otherwise
// run the transform+scale step and, once the linked object's ready byte clears
// (*node[0x50]==0), switch to mode 4 and advance with the follow-up callback.
void func_ov140_020d0e64(int *this)
{
    int node = this[1];
    int tmp[3];
    int target = func_ov107_020cab14(*(int *)node, 0);
    *(int *)(node + 4) = target;
    if (target == 0) {
        *(signed char *)(*(int *)node + 0x1c7) = 2;
        func_0203c634((int)this, *(signed char *)((int)this + 0x20), 0);
        return;
    }
    {
        int scale = func_ov107_020c9f48(*(int *)(*(int *)node + 0x390), tmp);
        func_0202f384(node + 0x14, *(int *)node + 0xa0, tmp);
        func_01ffa724(scale, node + 0x14, node + 0x14);
    }
    if (*(unsigned char *)(*(int *)(node + 0x50)) != 0) {
        return;
    }
    func_ov107_020c9264(*(int *)node, 4, 0);
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov140_020d0f24);
}
