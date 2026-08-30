typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long long u64;
typedef signed long long s64;
typedef s64 (*Ov002EntrySampleFn)(void);

typedef struct Ov002PauseSlot {
    int nObject;
    char pad004[0x68];
    int nClockStart;
    int nClockLimit;
    char pad074[4];
} Ov002PauseSlot;
typedef struct Ov002RootContext {
    char pad0000[0x8c94];
    Ov002PauseSlot pause;
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern void func_ov002_02069d40(void);
extern void func_ov002_0206a048(void);
extern u8 func_ov002_02056ba4(u64, int, Ov002EntrySampleFn);
extern u8 func_ov002_02056c44(int);
extern void func_020235e8(int, int, u16);
extern s64 func_ov002_0206f5c0(void);
extern s64 func_ov002_0206f630(void);
extern s64 func_ov002_0206f604(void);
extern s64 func_ov002_0206dda8(void);
extern s64 func_ov002_0206dde4(void);
extern u64 func_02020368(u64, u64);

/* Dispatches HUD creation, sampled time counters and value-only entries.
 * Commands 1/2 convert signed milliseconds to ticks before sampling; 6/7
 * capture a clock baseline and optionally replace the remaining-time limit.
 * The unsigned division helper is named explicitly to preserve its ROM alias. */
void func_ov002_0206ac74(int nCommand, int nValue, int nSampler)
{
    Ov002PauseSlot *pPause;
    u64 nTicks;

    pPause = &data_ov002_0207fa00->pause;
    switch (nCommand) {
    case 0:
        switch (nValue) {
        case 0:
            func_ov002_02069d40();
            break;
        case 1:
            func_ov002_0206a048();
            break;
        }
        break;
    case 1:
        if (pPause->nObject != -1) {
            nTicks = (u64)((s64)nValue * 33514) >> 6;
            switch (nSampler) {
            case 0:
                func_ov002_02056ba4(nTicks, 1, func_ov002_0206f5c0);
                break;
            case 1:
                func_ov002_02056ba4(nTicks, 1, func_ov002_0206f630);
                break;
            case 2:
                func_ov002_02056ba4(nTicks, 1, func_ov002_0206f604);
                break;
            }
        }
        break;
    case 2:
        if (pPause->nObject != -1) {
            nTicks = (u64)((s64)nValue * 33514) >> 6;
            switch (nSampler) {
            case 0:
                func_ov002_02056ba4(nTicks, 2, func_ov002_0206f5c0);
                break;
            case 1:
                func_ov002_02056ba4(nTicks, 2, func_ov002_0206f630);
                break;
            case 2:
                func_ov002_02056ba4(nTicks, 2, func_ov002_0206f604);
                break;
            }
        }
        break;
    case 6:
        if (nValue == 0) {
            pPause->nClockStart = func_02020368((u64)func_ov002_0206f604() << 6, 33514);
        }
        func_ov002_02056ba4(0, 0, func_ov002_0206dda8);
        break;
    case 7:
        if (nValue == 0) {
            pPause->nClockStart = func_02020368((u64)func_ov002_0206f604() << 6, 33514);
        }
        if (nSampler >= 0) {
            pPause->nClockLimit = nSampler;
        }
        func_ov002_02056ba4(0, 0, func_ov002_0206dde4);
        break;
    case 5:
        func_020235e8(0x20a9, 4, func_ov002_02056c44((s16)nValue) + 1);
        break;
    }
}
