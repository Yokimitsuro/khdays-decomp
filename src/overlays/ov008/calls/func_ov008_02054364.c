extern void func_02032428(void *context);
extern void func_ov008_020546ec(void *context);

typedef struct {
    char pad[0x4a7c];
    unsigned int flags;
} Unk02054364;

void func_ov008_02054364(Unk02054364 *context)
{
    func_ov008_020546ec(context);

    if (((context->flags << 29) >> 31) == 1) {
        func_02032428(context);
        context->flags &= ~4;
    }
}
