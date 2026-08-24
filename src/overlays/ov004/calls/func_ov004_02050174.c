typedef long long s64;
typedef unsigned int u32;

extern char *data_ov004_02051384;
extern char data_ov004_0205135c[];

extern char *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void MI_CpuCopy8(void *src, void *dst, u32 size);
extern void func_ov004_0204cac0(void *object, void *resource);
extern void func_ov004_0204fd60(void);
extern s64 func_020031d4(void);
extern void *func_ov004_02050300(void);

void *func_ov004_02050174(void *args) {
    char *context;
    int currentFx;

    context = NNSi_FndGetCurrentRootHeap();
    data_ov004_02051384 = context;
    MI_CpuFill8(context, 0, 0x5618);
    MI_CpuCopy8(args, context + 0x5558, 8);

    *(int *)(context + 0x5598) = *(int *)(context + 0x555c);
    if (*(int *)(context + 0x5558) == 0x190) {
        *(int *)(context + 0x555c) = 0xff;
        *(int *)(context + 0x5558) = 0xff;
    }

    currentFx = *(int *)(context + 0x5558) << 12;
    *(int *)(context + 0x5568) = currentFx;
    *(int *)(context + 0x5560) = currentFx;
    *(int *)(context + 0x556c) = *(int *)(context + 0x555c) << 12;
    *(int *)(context + 0x5564) =
        *(int *)(context + 0x556c) - *(int *)(context + 0x5560);

    func_ov004_0204cac0(context + 0x558c, data_ov004_0205135c);
    func_ov004_0204fd60();

    *(int *)(context + 0xb08) = 0;
    *(int *)(context + 0xaf8) = 0;
    *(s64 *)(context + 0xb00) = func_020031d4();

    return (void *)func_ov004_02050300;
}

