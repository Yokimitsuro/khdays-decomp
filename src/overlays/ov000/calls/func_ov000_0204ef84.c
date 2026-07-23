extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_02023d70(int p, int a, int b, int c, int d);
extern void func_0202aa9c(unsigned short *p);
extern void func_0201e3cc(int n);
extern void func_02032494(int *p);
extern void func_0203255c(int *p);
extern void func_0203253c(int p);
extern void func_02032428(int *p);
extern void *func_02023930(void *class_desc, int arg);
extern int data_ov000_0205aa34;
extern void func_ov000_0204f124(void);

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov000SceneNextField {
    int value;
} Ov000SceneNextField;

typedef struct Ov000BootContext {
    int frame;
    u8 pad_0004[8];
    u8 renderNode[0x108];
    u8 scrollBounds[0x9c];
    u8 textEngine[1];
    u8 pad_01b1[0x4a7c];
    s8 savedSlotIndex;
    s8 savedSceneIds[3];
    s8 resumeBoot;
    u8 pad_4c32[0x43a];
    void *sceneInstance;
    Ov000SceneNextField sceneNext;
} Ov000BootContext;

int func_ov000_0204ef84(void) {
    register int zero;
    Ov000BootContext *context =
        (Ov000BootContext *)NNSi_FndGetCurrentRootHeap();
    volatile unsigned short *bg = (volatile unsigned short *)0x04001008;

    func_02023d70((int)context->scrollBounds, 0x3b33, -0x3b33, -0x4d9a,
                  0x4d9a);
    func_0202aa9c((u16 *)context->renderNode);

    if (context->frame <= 0x10) {
        func_0201e3cc(-context->frame);
    } else {
        short base = 0x4004;
        bg[0] = bg[0] & 0x43 | base;
        bg[1] = bg[1] & 0x43 | (base + 0x200);
        bg[2] = bg[2] & 0x43 | (base + 0x400);
        bg[3] = bg[3] & 0x43 | (base - 0x3a00);
        *(volatile unsigned int *)0x04001000 =
            *(volatile unsigned int *)0x04001000 & ~0x1f00 | 0x1f00;
        bg[1] = bg[1] & ~3 | 3;
        bg[0] = bg[0] & ~3 | 2;
        bg[2] = bg[2] & ~3 | 1;
        bg[3] = bg[3] & ~3;

        func_02032494((int *)context->textEngine);
        func_0203255c((int *)context->textEngine);
        func_0203253c((int)context->textEngine);
        func_02032428((int *)context->textEngine);
        func_0201e3cc(-0x10);

        if (context->resumeBoot == 1) {
            context->sceneInstance =
                func_02023930((void *)&data_ov000_0205aa34,
                              context->savedSceneIds[context->savedSlotIndex] +
                                  1);
        } else {
            context->sceneInstance =
                func_02023930((void *)&data_ov000_0205aa34, 0);
        }
        zero = 0;
        context->sceneNext.value = zero;
        context->frame = zero;
        return (int)func_ov000_0204f124;
    }
    context->frame = context->frame + 1;
    return 0;
}
