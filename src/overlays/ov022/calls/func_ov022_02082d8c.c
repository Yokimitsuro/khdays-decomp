typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

typedef void *(*Ov022StateCallback)(void);

typedef struct Ov022Context {
    u16 flags;
    char pad_0002[2];
    int delay;
    char pad_0008[0x36];
    s8 state;
} Ov022Context;

extern Ov022Context *data_ov022_020b2e60;
extern u8 data_0204c240;

extern int func_ov022_02083f0c(void);
extern int func_01fffe14(void);
extern int func_01fffde0(int index);
extern void func_ov022_02083c08(int mode);
extern int func_ov022_02086ef4(void);
extern int func_ov022_02086f24(void);
extern int func_02023588(unsigned int flagId);
extern int func_020235a8(unsigned int flagId);
extern void func_ov022_02086f14(void);
extern int func_ov022_020886d0(int index);
extern int func_ov002_0206b828(void);
extern void func_ov002_0206f514(int busy);
extern int func_ov022_02088648(void);
extern int func_ov002_0206b7f4(void);
extern unsigned int func_ov022_02088668(void);
extern int func_ov022_020882e0(int index);
extern void func_02020878(char value);
extern void func_020208d0(int value);
extern void func_ov002_02056fa0(void);

extern void *func_ov022_0208310c(void);
extern void *func_ov022_02083038(void);
extern void *func_ov022_02083204(void);
extern void *func_ov022_020834d8(void);

Ov022StateCallback func_ov022_02082d8c(void)
{
    Ov022Context *context = data_ov022_020b2e60;
    Ov022StateCallback next = 0;

    func_ov022_02083f0c();
    func_01fffde0(func_01fffe14());

    if ((context->flags & 2) != 0) {
        return next;
    }
    if (context->delay > 0) {
        context->delay--;
        return next;
    }

    func_ov022_02083c08(1);

    if (func_ov022_02086ef4() != 0 && func_ov022_02086f24() != 0) {
        if (func_02023588(0x2085) == 0) {
            func_020235a8(0x2085);
        }
    } else if (func_ov022_02086ef4() == 0 &&
               func_02023588(0x2086) != 0 &&
               func_02023588(0x2085) == 0) {
        func_020235a8(0x2085);
    }

    if ((context->flags & 0x20) > 0) {
        if (func_ov022_02086ef4() != 0) {
            if (func_02023588(0x2085) == 0) {
                func_020235a8(0x2085);
            }
            if ((data_ov022_020b2e60->flags & 0x40) == 0 &&
                func_ov022_02086f24() == 0) {
                return 0;
            }
        }
        return func_ov022_0208310c;
    }

    if ((context->flags & 0x80) > 0) {
        return 0;
    }

    if ((context->flags & 0x40) > 0 && func_ov022_02086ef4() != 0) {
        func_ov022_02086f14();
        context->flags &= ~0x40;
    }

    if ((context->flags & 8) == 0 &&
        func_ov022_020886d0(func_01fffe14()) != 0 &&
        ((data_0204c240 & 4) != 0 || func_ov002_0206b828() == 0)) {
        if ((data_0204c240 & 4) == 0) {
            func_ov002_0206f514(1);
        }
        return func_ov022_02083038;
    }

    if (context->state >= 0) {
        return func_ov022_02083204;
    }

    if (func_ov022_02088648() != 0 &&
        (context->flags & 8) <= 0 &&
        func_ov002_0206b7f4() != 0 &&
        func_ov022_02088668() != 0 &&
        func_ov022_020882e0(func_01fffe14()) > 0) {
        if (func_ov022_02086ef4() != 0 &&
            (data_ov022_020b2e60->flags & 0x40) == 0 &&
            func_ov022_02086f24() == 0) {
            return 0;
        }

        context->flags |= 0x100;
        func_02020878(0);
        if ((data_0204c240 & 4) != 0) {
            func_020208d0(0);
        }
        context->flags |= 0x10;
        if ((data_0204c240 & 4) == 0) {
            func_ov002_0206f514(1);
        }
        func_ov002_02056fa0();
        next = func_ov022_020834d8;
    }

    return next;
}
