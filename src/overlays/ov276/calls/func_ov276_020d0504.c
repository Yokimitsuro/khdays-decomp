extern void func_0203c5c0(void *ctx, int a, int b, void *callback, int zero, void *out);
extern void func_ov276_020d0d98(void);

void func_ov276_020d0504(void *obj)
{
    void **node;

    func_0203c5c0(*(void **)((char *)obj + 0x3c), 0x64, 0x6c, func_ov276_020d0d98, 0, &node);
    node[0] = obj;
    node[1] = *(void **)((char *)node[0] + 0x3a8);
    *(void **)((char *)obj + 0x214) = node;
}
