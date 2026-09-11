struct vec3_020cdae4 { int x, y, z; };

extern void func_01ffa724(int factor, int *src, int *dst);
extern unsigned int func_02023e80(unsigned int range);
extern void func_0203c634(int *a, int i, int v);

void func_ov283_020cdae4(int *this)
{
    int node = this[1];
    struct vec3_020cdae4 *v = (struct vec3_020cdae4 *)(node + 0x1c);
    int y;

    *(struct vec3_020cdae4 *)(node + 0x10) = *v;
    *(int *)(node + 0x14) = *(int *)(node + 0x58);
    *(int *)(node + 0x58) = *(int *)(node + 0x58) - 0x80;
    func_01ffa724(0xe00, (int *)v, (int *)v);

    if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) {
        return;
    }

    y = func_02023e80(0x1922) + 0x1922;
    *(int *)(node + 0x34) = y;
    *(int *)(node + 0x7c) = (y > 0x25b3) ? 1 : 0;
    *(int *)(node + 0x3c) = 0;
    *(signed char *)(*(int *)node + 0x1c7) = 4;

    func_0203c634(this, *(signed char *)((char *)this + 0x20), 0);
}
