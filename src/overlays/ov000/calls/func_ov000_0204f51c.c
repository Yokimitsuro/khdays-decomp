/* Fade-out tick: run the darken, then on the last frame reprogram engine-B BG registers, kick the
 * manager, load the next resource, and hand off to func_ov000_0204f610.
 *
 * While nStateFrame <= 16 it just drives SetMasterBrightnessSub(-frame). On the frame it passes 16
 * it rewrites the engine-B display registers (0x0400100a/0e = BG1/BG3CNT, 0x04001000 = DISPCNT:
 * BG mode field -> 0x1a), sets brightness to full-dark, runs the four manager ticks, creates the
 * next scene resource, and returns the next scene callback. Same 0xd18c Ov000SceneContext; +0 read
 * as the 32-bit frame counter.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*OverlayCallback)(void);

typedef struct {
    int nStateFrame;        /* +0x00 */
    u8 pad_0004[8];
    u8 renderNode[0x1a4];   /* +0x0c */
    u8 manager[0x4ebc];     /* +0x1b0 */
    int nResourceState;     /* +0x506c */
    void *pResource;        /* +0x5070 */
} Ov000SceneContext;

extern u8 data_ov000_0205ab0c[];
extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202aa9c(void *object);
extern void func_0201e3cc(int value);
extern void func_02032494(void *manager);
extern void func_0203255c(void *manager);
extern void func_0203253c(void *manager);
extern void func_02032428(void *manager);
extern void *func_02023930(const void *descriptor, int argument);
extern void func_ov000_0204f610(void);

OverlayCallback func_ov000_0204f51c(void) {
    Ov000SceneContext *context = NNSi_FndGetCurrentRootHeap();

    func_0202aa9c(context->renderNode);
    if (context->nStateFrame <= 16) {
        func_0201e3cc(-context->nStateFrame);
    } else {
        *(volatile u16 *)0x0400100a =
            (*(volatile u16 *)0x0400100a & 0x43) | 0x4008;
        *(volatile u16 *)0x0400100e =
            (*(volatile u16 *)0x0400100e & 0x43) | 0x210;
        *(volatile u32 *)0x04001000 =
            (*(volatile u32 *)0x04001000 & ~0x1f00) | 0x1a00;
        *(volatile u16 *)0x0400100a =
            (*(volatile u16 *)0x0400100a & ~3) | 3;
        *(volatile u16 *)0x0400100e &= ~3;

        func_02032494(context->manager);
        func_0203255c(context->manager);
        func_0203253c(context->manager);
        func_02032428(context->manager);
        func_0201e3cc(-16);

        context->pResource = func_02023930(data_ov000_0205ab0c, 0);
        context->nResourceState = 0;
        context->nStateFrame = 0;
        return func_ov000_0204f610;
    }

    context->nStateFrame++;
    return 0;
}
