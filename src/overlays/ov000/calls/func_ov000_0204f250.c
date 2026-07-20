/* Boot fade-in tick: darken-to-lit over 16 frames, then hand off to the menu loop.
 *
 * func_0201e3cc/0201e374 are SetMasterBrightnessSub/Main; the argument runs step-16 (i.e. -16..0),
 * so this is a master-brightness fade from black up to full. Sub is always driven; Main only when
 * the sharing handle (pResource5074) is non-null. On the frame the counter passes 16 it pins the
 * counter to 120, stamps GetTick64 into llTimestamp, and returns Ov000_TickMenuLoop as the next
 * scene tick. Same 0xd18c Ov000SceneContext as the other menu ticks; +0 is read as a 32-bit frame
 * counter here (the reading the type's +0 comment records).
 */

typedef unsigned char u8;
typedef unsigned long long u64;
typedef void (*OverlayCallback)(void);

typedef struct {
    int nStateFrame;         /* +0x00 */
    u8 pad_0004[8];
    u8 renderNode[0x108];    /* +0x0c */
    u8 scrollBounds[0x4b50]; /* +0x114 */
    u64 llTimestamp;         /* +0x4c64 */
    u8 pad_4c6c[0x408];
    void *pResource5074;     /* +0x5074 -- shared-resource handle, gates the Main fade */
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_02023d70(void *bounds, int right, int left, int top,
                           int bottom);
extern void func_0202aa9c(void *object);
extern void func_0201e3cc(int value);
extern void func_0201e374(int value);
extern u64 func_020031d4(void);
extern void func_ov000_0204e5b0(void);

OverlayCallback func_ov000_0204f250(void) {
    Ov000SceneContext *context = NNSi_FndGetCurrentRootHeap();

    func_02023d70(context->scrollBounds, 0x3b33, -0x3b33, -0x4d9a,
                  0x4d9a);
    func_0202aa9c(context->renderNode);

    if (context->nStateFrame <= 16) {
        func_0201e3cc(context->nStateFrame - 16);
        if (context->pResource5074 != 0) {
            func_0201e374(context->nStateFrame - 16);
        }
    } else {
        func_0201e3cc(0);
        if (context->pResource5074 != 0) {
            func_0201e374(context->nStateFrame - 16);
        }
        context->nStateFrame = 120;
        context->llTimestamp = func_020031d4();
        return func_ov000_0204e5b0;
    }

    context->nStateFrame++;
    return 0;
}
