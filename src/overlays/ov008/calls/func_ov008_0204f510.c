extern int data_ov008_02090f04[];

#define CTXV (*(int *)((char *)data_ov008_02090f04 + 4))

typedef struct Ov008UiContextTail {
    char pad_0000[0x959c];
    void *pageA;
    void *pageB;
    char pad_95a4[0x20];
    int mode;
    char pad_95c8[0x30];
    int secondaryEnabled;
    char pad_95fc[0x1c];
    int taskPending;
    int refreshPending;
    int pageAHandle;
    int pageBHandle;
} Ov008UiContextTail;

extern int func_ov008_02051348(int mode);
extern int func_ov008_02051ae0(void);
extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void MI_CpuFill8(void *destination, int value, int size);
extern int func_ov008_0205137c(int object);
extern void func_ov008_020513f0(int object);
extern int func_02023588(int flagId);
extern int func_ov008_02050fc8(void);
extern int func_ov008_02051168(int duration, int b, int c);
extern int func_ov008_02051424(int value);
extern void func_020235a8(int flagId);
extern void func_ov008_02051040(int x, int y);
extern int func_ov008_02051ac0(void);
extern int func_ov008_02051b00(void);
extern int func_ov008_02051458(int object);
extern void func_ov008_020514cc(int object);
extern void func_ov008_0204eff0(int value, unsigned int duration);
extern void func_ov008_0204ee28(int value);
extern void func_02000f48(int priority, const char *name, void (*callback)(void));
extern char data_ov008_02090024[];
extern void func_ov008_0204f038(void);

void func_ov008_0204f510(void)
{
    Ov008UiContextTail *context;
    int size;

    context = (Ov008UiContextTail *)CTXV;
    if (context->pageA == 0) {
        func_ov008_02051348(context->mode);
        size = func_ov008_02051ae0();
        *(void **)(CTXV + 0x959c) = NNSi_FndAllocFromDefaultExpHeap(size);
        MI_CpuFill8(*(void **)(CTXV + 0x959c), 0, size);
    }

    if (*(int *)(CTXV + 0x9620) == 0) {
        *(int *)(CTXV + 0x9620) =
            func_ov008_0205137c(*(int *)(CTXV + 0x959c));
    } else {
        func_ov008_020513f0(*(int *)(CTXV + 0x959c));
    }

    if (*(int *)(CTXV + 0x95f8) != 0) {
        if (*(int *)(CTXV + 0x95a0) == 0) {
            if (*(int *)(CTXV + 0x95c4) == 2 &&
                func_02023588(0x35bc) == 0 &&
                func_ov008_02050fc8() != 2) {
                func_ov008_02051168(0xe, 0, 0);
                func_ov008_02051424(4);
                func_020235a8(0x35bc);
            } else if (*(int *)(CTXV + 0x95c4) == 1 &&
                       *(int *)(CTXV + 0x9630) != 0 &&
                       *(int *)(CTXV + 0x9634) == 0 &&
                       func_ov008_02050fc8() != 2) {
                func_ov008_02051040(0, 0);
                func_ov008_02051424(5);
            } else if (*(int *)(CTXV + 0x95c4) == 1 &&
                       func_ov008_02050fc8() == 2 &&
                       func_02023588(0x200a) != 0) {
                func_ov008_02051424(2);
            } else {
                func_ov008_02051424(func_ov008_02051ac0());
            }

            size = func_ov008_02051b00();
            *(void **)(CTXV + 0x95a0) = NNSi_FndAllocFromDefaultExpHeap(size);
            MI_CpuFill8(*(void **)(CTXV + 0x95a0), 0, size);
        }

        if (*(int *)(CTXV + 0x9624) == 0) {
            *(int *)(CTXV + 0x9624) =
                func_ov008_02051458(*(int *)(CTXV + 0x95a0));
        } else {
            func_ov008_020514cc(*(int *)(CTXV + 0x95a0));
        }
    }

    context = (Ov008UiContextTail *)CTXV;
    if (context->pageAHandle != 0 && context->pageBHandle != 0) {
        if (context->refreshPending != 0) {
            context->refreshPending = 0;
            func_ov008_0204eff0(0, 100);
        } else {
            func_ov008_0204eff0(0, 100);
        }
        func_ov008_0204ee28(2);
    }

    if (*(int *)(CTXV + 0x9618) != 0) {
        func_02000f48(1, data_ov008_02090024, func_ov008_0204f038);
        *(int *)(CTXV + 0x9618) = 0;
    }
}

