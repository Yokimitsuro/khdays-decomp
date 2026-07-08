struct lobyte { unsigned int b : 8; };

extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov284_020ccbfc(void);

// Switch to mode 0, set the ready bit (node[0][0x3a8][8] bit0), and advance the
// sub-state with the follow-up callback.
void func_ov284_020ccba0(int *this)
{
    int node = this[1];
    func_ov107_020c9264(*(int *)node, 0, 1);
    ((struct lobyte *)(*(int *)(*(int *)node + 0x3a8) + 8))->b |= 1;
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov284_020ccbfc);
}
