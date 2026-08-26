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

extern Ov022Context *data_ov022_020b2e60;
extern u8 data_0204be04;

extern void func_ov022_02083c08(int mode);
extern int func_ov002_0205196c(void);
extern int func_02023c40(void);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern int func_ov002_0206f49c(void);

extern void *func_ov022_0208310c(void);
extern void *func_ov022_02082d8c(void);

Ov022StateCallback func_ov022_020833c8(void)
{
    Ov022StateCallback next = 0;
    Ov022Context *context = data_ov022_020b2e60;
    int completed = 0;

    if ((context->flags & 0x20) != 0) {
        func_ov022_02083c08(1);
        return func_ov022_0208310c;
    }
    if (data_0204be04 != 0) {
        return next;
    }

    func_ov022_02083c08(1);
    if ((context->flags & 8) != 0) {
        return next;
    }

    if (context->state != 0) {
        if (context->state == 2 && func_ov002_0205196c() != 0) {
            completed = 1;
        }
    } else {
        context->viewX += func_02023c40() == 1 ? 0x3000 : 0x2000;
        if (context->viewX >= 0) {
            context->viewX = 0;
            completed = 1;
        }
        context->viewY = context->viewX;
        func_0201e374(context->viewX >> 12);
        func_0201e3cc(context->viewY >> 12);
    }

    if (completed != 0) {
        if (func_ov002_0206f49c() == 0) {
            return 0;
        }
        context->state = -1;
        context->flags &= ~0x10;
        next = func_ov022_02082d8c;
    }

    return next;
}
