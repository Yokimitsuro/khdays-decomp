struct lobyte { unsigned int b : 8; };

extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int *a, int i, int v);
extern void func_ov284_020cd1e8(void);

void func_ov284_020cd178(int *this)
{
    int node = this[1];
    func_ov107_020c9264(*(int *)node, 1, 0);
    ((struct lobyte *)(*(int *)(*(int *)node + 0x3a8) + 8))->b |= 1;
    *(unsigned short *)(*(int *)node + 0x1ae) |= 1;
    func_0203c634(this, *(signed char *)((int)this + 0x20), (int)&func_ov284_020cd1e8);
}
