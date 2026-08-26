typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov022Context {
    u16 flags;
    char pad_0002[0x32];
    int scale;
} Ov022Context;

extern Ov022Context *data_ov022_020b2e60;
extern u8 data_0204be04;

extern int func_ov022_02083f0c(void);
extern u32 func_ov022_02088338(void);
extern int func_01fffe14(void);
extern void func_ov000_0204cac0(int actor, int mode);
extern int func_ov022_02088474(int index);
extern void func_ov002_020722a0(void);
extern void func_0202bc90(int index);
extern u32 func_ov022_0208848c(void);
extern void func_ov002_02072364(int worldId, int scale, int enabled);
extern void func_ov002_020744b0(void);
extern int func_02020a9c(void);
extern void func_0202bda4(u32 mask, int scale);

void func_ov022_02083c08(int mode)
{
    int actor = func_ov022_02083f0c();
    u32 enabled = func_ov022_02088338();
    int index = func_01fffe14();
    u32 mask;

    if ((data_ov022_020b2e60->flags & 8) == 0) {
        func_ov000_0204cac0(actor, mode);
    }

    index = func_ov022_02088474(index);
    if (index >= 0) {
        func_ov002_020722a0();
        func_0202bc90((u16)index);
    }

    mask = func_ov022_0208848c();
    if (enabled == 0) {
        return;
    }

    if (index >= 0) {
        Ov022Context *context = data_ov022_020b2e60;
        func_ov002_02072364(
            index,
            context->scale,
            (context->flags & 0xbc) == 0);
        func_ov002_020744b0();
    }

    if (func_02020a9c() == 0x2a) {
        mask = 1 << data_0204be04;
    }

    func_0202bda4(mask, data_ov022_020b2e60->scale);
}
