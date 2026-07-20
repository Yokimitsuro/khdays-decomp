typedef unsigned char u8;
typedef unsigned short u16;
typedef void (*OverlayCallback)(void);

typedef struct {
    u8 pad_0000[0x84];
    void *resource;
    u8 pad_0088[0x95e2];
    u16 transition_state;
    u8 pad_966c[0x3aac];
    u8 transition_object[1];
} OverlayContext;

typedef struct {
    u8 pad_0000[0x9660];
    void *resource_9660;
} OverlaySharedContext;

extern OverlaySharedContext *data_ov000_0205ac3c;
extern u8 data_ov000_0205abe8[];
extern OverlayContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_0201eea8(void *resource);
extern void func_0201e374(int value);
extern void func_0201e3cc(int value);
extern void func_ov000_02058a40(void);
extern void *func_02024ee8(const void *data, int id);
extern void func_ov000_02058c28(void);
extern void func_ov000_02058e88(void);
extern void func_ov000_0205906c(void);
extern void func_ov000_02059200(void);
extern void func_ov000_02059130(void);
extern void func_02024d68(void);
extern void func_02024fd4(void *resource);
extern void func_ov000_02059324(int value);
extern void func_ov000_02059d78(void);
extern int func_02034014(int value);
extern void func_02033fb4(int first, int second);
extern void func_02035fb0(void *object, int x, int y, int scale, int duration);
extern void func_02035ffc(void *object);
extern void func_ov000_0205a010(void);

OverlayCallback func_ov000_02059e60(void) {
    OverlayContext *context = NNSi_FndGetCurrentRootHeap();

    if (func_0201eea8(data_ov000_0205ac3c->resource_9660) == 0) {
        return 0;
    }

    func_0201e374(-16);
    func_0201e3cc(-16);
    func_ov000_02058a40();
    context->resource = func_02024ee8(data_ov000_0205abe8, 14);
    func_ov000_02058c28();
    func_ov000_02058e88();
    func_ov000_0205906c();
    func_ov000_02059200();
    func_ov000_02059130();
    func_02024d68();
    func_02024fd4(context->resource);
    func_ov000_02059324(28);
    func_ov000_02059d78();

    if (func_02034014(0) == 0) {
        func_02033fb4(0, 0);
    }

    func_02035fb0(context->transition_object, 0, 0, 0x1000, 500);
    func_02035ffc(context->transition_object);
    context->transition_state = 3;
    return func_ov000_0205a010;
}
