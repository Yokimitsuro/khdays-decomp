extern unsigned long long func_02020400(int a, unsigned int b);
extern void func_0203c634(int obj, int a, int cb);

// Once the linked object is idle (*node[8]==0), advance the wrap counter
// (node[9] = (node[9]+1) mod the object's period) via the 64-bit divide helper,
// force sub-state 3 and advance.
void func_ov291_020cd4cc(int *this)
{
    int node = this[1];
    if (*(unsigned char *)(*(int *)(node + 0x20)) != 0) {
        return;
    }
    *(int *)(node + 0x24) =
        (int)(func_02020400(*(int *)(node + 0x24) + 1,
                            *(unsigned int *)(*(int *)(*(int *)node + 0x3a0) + 8)) >> 0x20);
    *(signed char *)(*(int *)node + 0x1c7) = 3;
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), 0);
}
