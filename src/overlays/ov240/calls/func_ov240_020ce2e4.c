extern void func_0203c5c0(void *ctx, int a, int b, void *callback, int zero, void *out);
extern void func_ov240_020ce97c(void);

void func_ov240_020ce2e4(void *obj)
{
    void **node;

    func_0203c5c0(*(void **)((char *)obj + 0x3c), 0x64, 0x44, func_ov240_020ce97c, 0, &node);
    node[0] = obj;
    node[1] = *(void **)((char *)node[0] + 0x388);
    *(void **)((char *)obj + 0x214) = node;
}
