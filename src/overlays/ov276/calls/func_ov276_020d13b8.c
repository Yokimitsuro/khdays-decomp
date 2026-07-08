extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_ov276_020d0cdc(int obj, int a);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov276_020d1420(void);

// Accumulate the per-frame step (this[0]+0x2c) into the node timer (node[0x4c]).
// Once it reaches 0x666, reset the object to mode 0, run the release handler,
// clear the timer and advance the sub-state with the follow-up callback.
void func_ov276_020d13b8(int *this)
{
    int obj = this[0];
    int node = this[1];
    int acc = *(int *)(node + 0x4c) + *(int *)(obj + 0x2c);
    *(int *)(node + 0x4c) = acc;
    if (acc < 0x666) {
        return;
    }
    func_ov107_020c9264(*(int *)node, 0, 0);
    func_ov276_020d0cdc(*(int *)node, 0);
    *(int *)(node + 0x4c) = 0;
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov276_020d1420);
}
