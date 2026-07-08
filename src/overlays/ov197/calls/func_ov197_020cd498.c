struct vec3 { int x, y, z; };

extern void func_ov197_020ccb24(int node, struct vec3 v, int flag);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_ov197_020cc9b4(int obj, int arg1);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov197_020cd500(void);

// Apply the node's pending transform (vector at node+0x28); if the target slot
// is still free (node[1][0xad]==0), switch to mode 3, seed the default pose and
// advance the sub-state with the follow-up callback.
void func_ov197_020cd498(int *this)
{
    int node = this[1];
    func_ov197_020ccb24(node, *(struct vec3 *)(node + 0x28), 1);
    if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*(int *)node, 3, 0);
    func_ov197_020cc9b4(*(int *)node, 1);
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov197_020cd500);
}
