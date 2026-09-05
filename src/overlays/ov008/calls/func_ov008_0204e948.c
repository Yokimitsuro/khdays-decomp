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

extern Ov008MenuContext *data_ov008_02090f00;

extern void func_ov008_0204d564(void);
extern int func_ov008_02050548(int mode);
extern int func_ov008_02050e44(void);
extern int func_ov008_0204e130(void);
extern int func_02023588(int flagId);
extern void func_020307b8(int enabled);

extern void func_ov008_0204ea4c(void);
extern void func_ov008_0204eaac(void);
extern void func_ov008_0204e184(void);
extern void func_ov008_0204e1bc(void);
extern void func_ov008_0204e04c(void);
extern void func_ov008_0204e8a8(void);

void *func_ov008_0204e948(void)
{
    void *result = 0;

    func_ov008_0204d564();
    if (func_ov008_02050548(0) != 0) {
        switch (func_ov008_02050e44()) {
        case 3:
            result = (void *)func_ov008_0204ea4c;
            func_ov008_0204e130();
            break;
        case 4:
            func_ov008_0204e130();
            result = (void *)func_ov008_0204eaac;
            break;
        case 7:
            result = (void *)func_ov008_0204e184;
            break;
        case 8:
            result = (void *)func_ov008_0204e1bc;
            break;
        default:
        {
            u8 synchronized =
                data_ov008_02090f00->sharedFlags.bits.synchronized;
            int flagSet = func_02023588(0x2010) != 0;

            if (synchronized == flagSet) {
                result = (void *)func_ov008_0204e04c;
            } else {
                data_ov008_02090f00->sharedFlags.bits.synchronized =
                    (u8)flagSet;
                func_020307b8(1);
                result = (void *)func_ov008_0204e8a8;
            }
            func_ov008_0204e130();
            break;
        }
        }
    }
    return result;
}
