typedef unsigned char u8;
typedef unsigned int  u32;

typedef struct Ov009MenuContext {
    u8 pad_0000[0x959c];
    void *pageA;
    u8 pad_95a0[0x95c4 - 0x95a0];
    int pageInitArg;
    u8 pad_95c8[0x9618 - 0x95c8];
    int updateTaskPending;
    int blitPending;
    void *pageResource;
    int pageResourceReady;
} Ov009MenuContext;

extern Ov009MenuContext *data_ov009_020563e4[];
extern const char data_ov009_02056294[];

#define OV009_CONTEXT (data_ov009_020563e4[1])
#define OV009_CONTEXT_VOLATILE \
    (*(Ov009MenuContext *volatile *)&data_ov009_020563e4[1])

extern void  func_ov009_0204e6a8(int initArg);
extern u32   func_ov009_0204ee10(void);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 size);
extern void  MI_CpuFill8(void *destination, int value, u32 size);
extern void *func_ov009_0204e6dc(void *page);
extern void  func_ov009_0204e750(void *page);
extern void  func_ov009_0204cd34(int sourceOffset, int size);
extern void  func_ov009_0204cb6c(int state);
extern void  func_02000f48(int priority, const void *descriptor,
                          void (*callback)(void));
extern void  func_ov009_0204cd7c(void);

void func_ov009_0204d224(void)
{
    u32 pageSize;

    if (OV009_CONTEXT->pageA == 0) {
        func_ov009_0204e6a8(OV009_CONTEXT->pageInitArg);
        pageSize = func_ov009_0204ee10();
        OV009_CONTEXT_VOLATILE->pageA =
            NNSi_FndAllocFromDefaultExpHeap(pageSize);
        MI_CpuFill8(OV009_CONTEXT_VOLATILE->pageA, 0, pageSize);
    }

    if (OV009_CONTEXT->pageResource == 0) {
        OV009_CONTEXT->pageResource =
            func_ov009_0204e6dc(OV009_CONTEXT->pageA);
    } else {
        func_ov009_0204e750(OV009_CONTEXT->pageA);
    }

    OV009_CONTEXT_VOLATILE->pageResourceReady = 1;

    {
        Ov009MenuContext *context = OV009_CONTEXT_VOLATILE;
        if (context->pageResource != 0 &&
            context->pageResourceReady != 0) {
            if (context->blitPending != 0) {
                context->blitPending = 0;
                func_ov009_0204cd34(0, 100);
            } else {
                func_ov009_0204cd34(0, 100);
            }
            func_ov009_0204cb6c(2);
        }
    }

    if (OV009_CONTEXT->updateTaskPending != 0) {
        func_02000f48(
            1, data_ov009_02056294, func_ov009_0204cd7c);
        OV009_CONTEXT->updateTaskPending = 0;
    }
}
