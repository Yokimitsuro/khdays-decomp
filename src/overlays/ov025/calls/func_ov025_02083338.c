extern int data_ov025_020b5744[];

#define CTXV (*(int *)((char *)data_ov025_020b5744 + 4))

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

extern int func_ov025_020850f8(int mode);
extern int func_ov025_02085890(void);
extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void MI_CpuFill8(void *destination, int value, int size);
extern int func_ov025_0208512c(int object);
extern void func_ov025_020851a0(int object);
extern int func_02023588(int flagId);
extern int func_ov025_02084dd8(void);
extern int func_ov025_02084f78(int duration, int b, int c);
extern int func_ov025_020851d4(int value);
extern void func_020235a8(int flagId);
extern void func_ov025_02084e50(int x, int y);
extern int func_ov025_02085870(void);
extern int func_ov025_020858b0(void);
extern int func_ov025_02085208(int object);
extern void func_ov025_0208527c(int object);
extern void func_ov025_02082e18(int value, unsigned int duration);
extern void func_ov025_02082c50(int value);
extern void func_02000f48(int priority, const char *name, void (*callback)(void));
extern char data_ov025_020b4a38[];
extern void func_ov025_02082e60(void);

void func_ov025_02083338(void)
{
    Ov008UiContextTail *context;
    int size;

    context = (Ov008UiContextTail *)CTXV;
    if (context->pageA == 0) {
        func_ov025_020850f8(context->mode);
        size = func_ov025_02085890();
        *(void **)(CTXV + 0x959c) = NNSi_FndAllocFromDefaultExpHeap(size);
        MI_CpuFill8(*(void **)(CTXV + 0x959c), 0, size);
    }

    if (*(int *)(CTXV + 0x9620) == 0) {
        *(int *)(CTXV + 0x9620) =
            func_ov025_0208512c(*(int *)(CTXV + 0x959c));
    } else {
        func_ov025_020851a0(*(int *)(CTXV + 0x959c));
    }

    if (*(int *)(CTXV + 0x95f8) != 0) {
        if (*(int *)(CTXV + 0x95a0) == 0) {
            if (*(int *)(CTXV + 0x95c4) == 2 &&
                func_02023588(0x35bc) == 0 &&
                func_ov025_02084dd8() != 2) {
                func_ov025_02084f78(0xe, 0, 0);
                func_ov025_020851d4(4);
                func_020235a8(0x35bc);
            } else if (*(int *)(CTXV + 0x95c4) == 1 &&
                       *(int *)(CTXV + 0x9630) != 0 &&
                       *(int *)(CTXV + 0x9634) == 0 &&
                       func_ov025_02084dd8() != 2) {
                func_ov025_02084e50(0, 0);
                func_ov025_020851d4(5);
            } else if (*(int *)(CTXV + 0x95c4) == 1 &&
                       func_ov025_02084dd8() == 2 &&
                       func_02023588(0x200a) != 0) {
                func_ov025_020851d4(2);
            } else {
                func_ov025_020851d4(func_ov025_02085870());
            }

            size = func_ov025_020858b0();
            *(void **)(CTXV + 0x95a0) = NNSi_FndAllocFromDefaultExpHeap(size);
            MI_CpuFill8(*(void **)(CTXV + 0x95a0), 0, size);
        }

        if (*(int *)(CTXV + 0x9624) == 0) {
            *(int *)(CTXV + 0x9624) =
                func_ov025_02085208(*(int *)(CTXV + 0x95a0));
        } else {
            func_ov025_0208527c(*(int *)(CTXV + 0x95a0));
        }
    }

    context = (Ov008UiContextTail *)CTXV;
    if (context->pageAHandle != 0 && context->pageBHandle != 0) {
        if (context->refreshPending != 0) {
            context->refreshPending = 0;
            func_ov025_02082e18(0, 100);
        } else {
            func_ov025_02082e18(0, 100);
        }
        func_ov025_02082c50(2);
    }

    if (*(int *)(CTXV + 0x9618) != 0) {
        func_02000f48(1, data_ov025_020b4a38, func_ov025_02082e60);
        *(int *)(CTXV + 0x9618) = 0;
    }
}

