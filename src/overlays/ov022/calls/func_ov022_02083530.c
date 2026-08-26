typedef unsigned char u8;
typedef unsigned short u16;

typedef void *(*Ov022StateCallback)(void);

typedef struct Ov022Context {
    u16 flags;
    char pad_0002[0x2e];
    int sessionHandle;
} Ov022Context;

typedef struct Ov022Entity {
    char pad_0000[0x2668];
    void *pendingObject;
} Ov022Entity;

extern u8 data_0204be04;
extern u8 data_0204c240;
extern Ov022Context *data_ov022_020b2e60;

extern void func_ov022_02083c08(int mode);
extern int func_ov002_0205196c(void);
extern int func_01fffe14(void);
extern int func_ov022_020886d0(int index);
extern int func_ov002_02072844(int handle);
extern void func_020235e8(int field, int width, int value);
extern int func_ov002_02072854(int handle);
extern void func_ov002_02072820(int handle, void *payload);
extern int func_ov002_02072808(int handle);
extern int func_ov002_0207283c(int handle);
extern int func_ov002_0207284c(int handle);
extern void func_ov002_0206b0b8(int slot, void *payload, int argument, int flag);
extern Ov022Entity *func_01fffde0(int index);
extern int func_ov022_02088474(int index);
extern void func_ov002_02073ffc(int index, int argument);
extern void func_ov002_02074054(int enabled);
extern void func_ov002_02063774(void);
extern void func_ov002_020726a0(int index, int *outKind, int *outSlot);
extern void func_ov002_0207650c(int index);
extern void func_ov002_0207209c(void);

extern void *func_ov022_02083878(void);
extern void *func_ov022_02082d8c(void);
extern void *func_ov022_020836f8(void);

Ov022StateCallback func_ov022_02083530(void)
{
    char payload[12];
    int rosterSlot;
    Ov022StateCallback next = 0;

    if (data_0204be04 != 0) {
        return next;
    }

    func_ov022_02083c08(1);
    if (func_ov002_0205196c() != 0) {
        if (func_ov022_020886d0(func_01fffe14()) != 0) {
            return func_ov022_02083878;
        }

        if ((data_0204c240 & 4) == 0 &&
            func_ov002_02072844(data_ov022_020b2e60->sessionHandle) < 0x100) {
            func_020235e8(
                0x2099,
                8,
                (u16)func_ov002_02072844(data_ov022_020b2e60->sessionHandle));
        }

        if (func_ov002_02072854(data_ov022_020b2e60->sessionHandle) != 0) {
            int slot;
            int argument;
            int flag;

            func_ov002_02072820(data_ov022_020b2e60->sessionHandle, payload);
            slot = func_ov002_02072808(data_ov022_020b2e60->sessionHandle);
            argument = func_ov002_0207283c(data_ov022_020b2e60->sessionHandle);
            flag = func_ov002_0207284c(data_ov022_020b2e60->sessionHandle);
            func_ov002_0206b0b8(slot, payload, argument, flag);

            data_ov022_020b2e60->sessionHandle = 0;
            func_01fffde0(func_01fffe14())->pendingObject = 0;
            data_ov022_020b2e60->flags |= 0x80;
            return func_ov022_02082d8c;
        }

        func_ov002_02073ffc(func_ov022_02088474(func_01fffe14()), 0);
        func_ov002_02074054(0);
        func_ov002_02063774();
        func_ov002_020726a0(func_ov022_02088474(func_01fffe14()), 0, &rosterSlot);
        func_ov002_0207650c((u16)rosterSlot);
        func_ov002_0207209c();
        next = func_ov022_020836f8;
    }

    return next;
}
