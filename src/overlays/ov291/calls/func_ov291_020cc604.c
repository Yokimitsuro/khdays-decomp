extern unsigned char data_0204c240[];
extern void func_0203c5c0(void *ctx, int a, int b, void *callback, int zero, void *out);
extern void func_ov291_020cc7e8(void);

void func_ov291_020cc604(void *obj)
{
    int *node;

    func_0203c5c0(*(void **)((char *)obj + 0x3c), 0x64, 0x38, func_ov291_020cc7e8, 0, &node);
    node[0xc] = (data_0204c240[0] & 4) != 0;
    *(void **)node = obj;
    *(int **)((char *)obj + 0x214) = node;
}
