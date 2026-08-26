typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

typedef void *(*Ov022StateCallback)(void);

typedef struct Ov022Context {
    u16 flags;
    char pad_0002[6];
    void *slots[3];
    void *childObjects[2];
    int viewX;
    int viewY;
    char pad_0024[0x1a];
    s8 state;
} Ov022Context;

typedef struct Ov022Entity {
    char pad_0000[0x2668];
    void *pendingObject;
} Ov022Entity;

extern Ov022Context *data_ov022_020b2e60;
extern u8 data_0204be04;

extern int func_ov022_02083f0c(void);
extern void func_ov022_02083c08(int mode);
extern int func_020335c8(void);
extern int func_020335a4(void);
extern int func_ov002_02052ab8(void);
extern int func_ov002_0206b828(void);
extern int func_01fffe14(void);
extern int func_ov022_02088474(int index);
extern int func_ov002_0206ce00(int worldId);
extern int func_ov002_0206d9e4(void);
extern unsigned short func_ov022_02088254(int index);
extern void func_ov002_0204ce14(int actor, int angle);
extern int func_ov022_020881f8(int index);
extern void func_ov002_0204cce0(int actor, const void *origin);
extern void func_ov002_0206d9d0(int value);
extern void func_ov002_02073ffc(int index, int argument);
extern void func_ov022_02088528(int index);
extern Ov022Entity *func_01fffde0(int index);
extern void func_ov002_0206aae4(int kind, int value);
extern void func_ov022_02086638(void *object, int enabled);
extern void func_0201e3cc(int brightness);
extern void func_ov002_020518e0(void);
extern int func_0201e428(void);
extern int func_0201e438(void);

extern void *func_ov022_0208310c(void);
extern void *func_ov022_020833c8(void);

Ov022StateCallback func_ov022_02083204(void)
{
    Ov022Context *context = data_ov022_020b2e60;
    int actor = func_ov022_02083f0c();
    int angle;
    Ov022Entity *entity;
    void *pendingObject;

    if ((context->flags & 0x20) != 0) {
        func_ov022_02083c08(1);
        return func_ov022_0208310c;
    }
    if (data_0204be04 != 0) {
        return 0;
    }

    func_ov022_02083c08(1);
    if ((context->flags & 8) != 0) {
        return 0;
    }
    if (func_020335c8() != 0 || func_020335a4() != 0) {
        return 0;
    }
    if (func_ov002_02052ab8() == 0) {
        return 0;
    }
    if (func_ov002_0206b828() != 0 && (context->flags & 0x200) == 0) {
        return 0;
    }
    if (func_ov002_0206ce00(func_ov022_02088474(func_01fffe14())) == 0) {
        return 0;
    }

    angle = func_ov002_0206d9e4();
    if (angle < 0) {
        angle = func_ov022_02088254(func_01fffe14());
    }
    func_ov002_0204ce14(actor, angle);
    func_ov002_0204cce0(actor, (const void *)func_ov022_020881f8(func_01fffe14()));
    func_ov002_0206d9d0(-1);
    func_ov002_02073ffc(func_ov022_02088474(func_01fffe14()), 1);
    func_ov022_02088528(func_01fffe14());

    entity = func_01fffde0(func_01fffe14());
    pendingObject = entity->pendingObject;
    if (pendingObject != 0 && *(u8 *)pendingObject == 0) {
        func_01fffde0(func_01fffe14())->pendingObject = 0;
    }

    func_ov002_0206aae4(0, 2);
    func_ov022_02086638(context->slots[0], 0);

    if (context->state != 0) {
        if (context->state == 2) {
            context->viewY = -0x10000;
            func_0201e3cc(context->viewY >> 12);
            func_ov002_020518e0();
        }
    } else {
        context->viewX = func_0201e428() << 12;
        context->viewY = func_0201e438() << 12;
    }

    return func_ov022_020833c8;
}
