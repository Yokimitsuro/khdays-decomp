struct vec3 { int x, y, z; };

extern void func_ov147_020ccb30(int node, struct vec3 v, int flag);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_ov147_020cc9c0(int obj, int arg1);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov147_020cd50c(void);

// Apply the node's pending transform (vector at node+0x28); if the target slot
// is still free (node[1][0xad]==0), switch to mode 3, seed the default pose and
// advance the sub-state with the follow-up callback.
void func_ov147_020cd4a4(int *this)
{
    int node = this[1];
    func_ov147_020ccb30(node, *(struct vec3 *)(node + 0x28), 1);
    if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*(int *)node, 3, 0);
    func_ov147_020cc9c0(*(int *)node, 1);
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov147_020cd50c);
}
