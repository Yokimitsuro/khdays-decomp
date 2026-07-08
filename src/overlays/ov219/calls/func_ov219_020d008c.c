extern void func_0203c5c0(void *ctx, int a, int b, void *callback, int zero, void *out);
extern void func_ov219_020d0698(void);

void func_ov219_020d008c(void *obj)
{
    void **node;

    func_0203c5c0(*(void **)((char *)obj + 0x3c), 0x64, 0x54, func_ov219_020d0698, 0, &node);
    node[0] = obj;
    node[1] = *(void **)((char *)node[0] + 0x384);
    *(void **)((char *)obj + 0x214) = node;
}
