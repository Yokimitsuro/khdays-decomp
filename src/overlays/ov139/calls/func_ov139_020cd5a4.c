struct hw60 { unsigned short lo : 8, hi : 8; };

extern int func_ov107_020c9f48(int src, int *out);
extern void func_0202f384(int dst, int mtx, int *v);
extern void func_01ffa724(int s, int dst, int src);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov139_020cd640(void);

// Sample the linked object's transform (obj[0x390]) into a temp, rotate the node
// vector (node+0x14) by it and scale by the returned factor. If the factor is 0
// the move is complete: clear hw60 flag 0x40 and advance the sub-state.
void func_ov139_020cd5a4(int *this)
{
    int node = this[1];
    int tmp[3];
    int scale = func_ov107_020c9f48(*(int *)(*(int *)node + 0x390), tmp);
    func_0202f384(node + 0x14, *(int *)node + 0xa0, tmp);
    func_01ffa724(scale, node + 0x14, node + 0x14);
    if (scale != 0) {
        return;
    }
    ((struct hw60 *)(*(int *)node + 0x60))->hi &= ~0x40;
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov139_020cd640);
}
