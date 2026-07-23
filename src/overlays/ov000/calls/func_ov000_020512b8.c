typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov000SceneContext {
    u8 pad_0000[0x4b08];
    int displayState;
    int previousDisplayState;
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern Ov000SceneContext *volatile data_ov000_0205ac24;
extern void G2x_SetBlendAlpha_(
    void *registerBase,
    int plane1,
    int plane2,
    int plane3,
    int coefficient
);

void func_ov000_020512b8(u32 x, u32 y) {
    Ov000SceneContext *context = NNSi_FndGetCurrentRootHeap();
    int state = context->displayState;
    int changed = state != context->previousDisplayState;

    if (state < 3) {
        volatile u32 *display = (volatile u32 *)0x04001000;
        volatile u32 *affine = (volatile u32 *)0x04001018;
        u32 coordinateMask = 0x1ff;
        u32 highCoordinateMask = coordinateMask << 16;

        if (changed) {
            display[0] = (display[0] & ~0x1f00) | 0x1e00;
            *(volatile u16 *)((u8 *)display + 8) =
                (*(volatile u16 *)((u8 *)display + 8) & ~3) | 1;
            *(volatile u16 *)((u8 *)display + 0xc) =
                (*(volatile u16 *)((u8 *)display + 0xc) & ~3) | 2;
            G2x_SetBlendAlpha_(
                (u8 *)display + 0x50, 4, 0x10, 0, 0x10);
        }

        affine[0] =
            (x & coordinateMask) |
            ((y << 16) & highCoordinateMask);
        *(volatile u16 *)((u8 *)affine + 0x28) =
            ((-x << 8) & 0xff00) | ((0xc6 - x) & 0xff);
        *(volatile u16 *)((u8 *)affine + 0x2c) =
            ((-y << 8) & 0xff00) | ((0x23 - y) & 0xff);
    } else {
        volatile u32 *display = (volatile u32 *)0x04001000;
        volatile u32 *affine = (volatile u32 *)0x04001010;
        u32 coordinateMask = 0x1ff;
        u32 highCoordinateMask = coordinateMask << 16;

        if (changed) {
            display[0] = (display[0] & ~0x1f00) | 0x1b00;
            *(volatile u16 *)((u8 *)display + 8) =
                (*(volatile u16 *)((u8 *)display + 8) & ~3) | 2;
            *(volatile u16 *)((u8 *)display + 0xc) =
                (*(volatile u16 *)((u8 *)display + 0xc) & ~3) | 1;
            G2x_SetBlendAlpha_(
                (u8 *)display + 0x50, 1, 0x10, 0, 0x10);
        }

        affine[0] =
            (x & coordinateMask) |
            ((y << 16) & highCoordinateMask);
        *(volatile u16 *)((u8 *)affine + 0x30) =
            ((-x << 8) & 0xff00) | ((0xc6 - x) & 0xff);
        *(volatile u16 *)((u8 *)affine + 0x34) =
            ((-y << 8) & 0xff00) | ((0x0e - y) & 0xff);
    }

    context = data_ov000_0205ac24;
    context->previousDisplayState = context->displayState;
}
