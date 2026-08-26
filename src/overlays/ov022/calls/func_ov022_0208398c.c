typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

typedef void *(*Ov022StateCallback)(void);

typedef struct Ov022Context {
    u16 flags;
    char pad_0002[0x1a];
    int viewX;
    int viewY;
    char pad_0024[0x1a];
    s8 state;
} Ov022Context;

extern u8 data_0204be04;
extern Ov022Context *data_ov022_020b2e60;

extern void func_ov022_02083c08(int mode);
extern int func_ov002_0205196c(void);
extern void func_02023c14(int value);
extern int func_02023c40(void);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern void *func_ov022_02083bd8(void);

Ov022StateCallback func_ov022_0208398c(void)
{
    Ov022Context *context = data_ov022_020b2e60;
    Ov022StateCallback next = 0;

    if (data_0204be04 != 0) {
        return next;
    }

    func_ov022_02083c08(1);
    if (context->state != 0) {
        if (context->state == 2 && func_ov002_0205196c() != 0) {
            func_02023c14(1);
            next = func_ov022_02083bd8;
        }
    } else {
        context->viewX -= func_02023c40() == 1 ? 0x3000 : 0x2000;
        context->viewY -= func_02023c40() == 1 ? 0x3000 : 0x2000;

        u8 completed = 0;

        if (context->viewX <= -0x10000) {
            context->viewX = -0x10000;
            completed++;
        }
        if (context->viewY <= -0x10000) {
            context->viewY = -0x10000;
            completed++;
        }

        if (completed >= 2 && func_ov002_0205196c() != 0) {
            func_02023c14(1);
            next = func_ov022_02083bd8;
        }

        func_0201e374(context->viewX >> 12);
        func_0201e3cc(context->viewY >> 12);
    }

    return next;
}
