typedef unsigned char u8;

typedef union Ov008FlagsByte {
    u8 raw;
    struct {
        u8 bit0 : 1;
        u8 synchronized : 1;
        u8 rest : 6;
    } bits;
} Ov008FlagsByte;

typedef struct Ov008MenuContext {
    u8 pad_0000[0x48];
    Ov008FlagsByte sharedFlags;
} Ov008MenuContext;

extern char *NNSi_FndGetCurrentRootHeap(void);
extern void WM_EndKeySharing_0x02023ad0(int handle);
extern char *data_0204be18;
extern void func_ov008_02053a90(void *source);
extern Ov008MenuContext *data_ov008_02090f00;
extern int func_02023588(int flagId);
extern void func_020307b8(int enabled);
extern void func_ov008_0204e04c(void);
extern void func_ov008_0204e8a8(void);

void *func_ov008_0204eadc(void)
{
    char *root = NNSi_FndGetCurrentRootHeap();

    if (*(int *)(root + 0x14) >= 0) {
        WM_EndKeySharing_0x02023ad0(*(int *)(root + 0x14));
        *(int *)(root + 0x14) = -1;
    }

    func_ov008_02053a90(data_0204be18 + 0xee0);

    {
        u8 synchronized =
            data_ov008_02090f00->sharedFlags.bits.synchronized;
        int flagSet = func_02023588(0x2010) != 0;

        if (synchronized == flagSet) {
            return (void *)func_ov008_0204e04c;
        }

        data_ov008_02090f00->sharedFlags.bits.synchronized = (u8)flagSet;
        func_020307b8(1);
        return (void *)func_ov008_0204e8a8;
    }
}
