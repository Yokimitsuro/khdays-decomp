typedef unsigned char u8;
typedef unsigned short u16;

typedef void *(*Ov022StateCallback)(void);

typedef struct Ov022Context {
    u16 flags;
    char pad_0002[0x1a];
    int viewX;
    int viewY;
} Ov022Context;

extern u8 data_0204be04;
extern Ov022Context *data_ov022_020b2e60;

extern void func_ov022_02083c08(int mode);
extern int func_02023c40(void);
extern void func_02023c14(int value);
extern void func_020235e8(int field, int width, int value);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern void *func_ov022_02083bd8(void);

Ov022StateCallback func_ov022_02083b20(void)
{
    Ov022Context *context = data_ov022_020b2e60;
    Ov022StateCallback next = 0;

    if (data_0204be04 != 0) {
        return next;
    }

    func_ov022_02083c08(1);

    int completed = 0;

    context->viewX += func_02023c40() == 1 ? 0x2000 : 0x1800;
    if (context->viewX >= 0x10000) {
        context->viewX = 0x10000;
        completed = 1;
    }
    context->viewY = context->viewX;

    if (completed != 0) {
        func_02023c14(1);
        next = func_ov022_02083bd8;
        func_020235e8(0x20e6, 1, 0);
    }

    func_0201e374(context->viewX >> 12);
    func_0201e3cc(context->viewY >> 12);
    return next;
}
