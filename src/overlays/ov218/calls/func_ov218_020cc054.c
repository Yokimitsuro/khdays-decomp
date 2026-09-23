/* Constructor of the ov218 enemy (variant of the ov220 d1a24 one): installs the handlers (+8, +0xc,
 * +0x1c message, +0x30, +0x28, +0x2c, +0x34, +0x1d0 hit, +0x1dc, +0x1d4, +0x1e0, +0x1e4), the +0x64
 * pose (scale 0.49) and the +0x1fc bounds box; builds the +0x384 body (pose 0, set up by 020cc018,
 * subscribed to +0x9c) with its +0x3a8 bone, the +0x3ac bone of pose 1, the two +0x3dc slot models
 * (kinds of data_ov218_020cf30c) attached and hidden, the +0x388 / +0x38c placements from the pose,
 * the two +0x394 helpers (020ce040), and loads sound 0x135. */
typedef unsigned char u8;
typedef void (*Callback)(void);
typedef struct { int w[6]; } Bounds;
typedef struct { u8 id[2]; } Kinds;
typedef struct { int pItem; int pad; } SubitemSlot;

extern void func_ov218_020cc294(void);
extern void func_ov218_020cc2d4(void);
extern void func_ov218_020cc3f4(void);
extern void func_ov218_020cc560(void);
extern void func_ov218_020cc37c(void);
extern void func_ov218_020cc3b8(void);
extern void func_ov218_020cc4ec(void);
extern void func_ov218_020cc5bc(void);
extern void func_ov218_020cc528(void);
extern void func_ov218_020cc77c(void);
extern void func_ov218_020cc79c(void);
extern void func_ov218_020cc7c8(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *pose);
extern void func_0203355c(int resourceId);
extern const Kinds data_ov218_020cf30c;
extern const char data_ov218_020cf32c[];
extern const char data_ov218_020cf338[];
extern int func_0203bdfc(int item, const char *name);
extern void func_ov218_020cc018(char *self);
extern int func_ov218_020ce040(char *self);

void func_ov218_020cc054(char *self)
{
    Kinds kinds = data_ov218_020cf30c;
    Bounds bounds;
    const u8 *kind;
    int *slot;
    int item;
    int i;

    bounds.w[0] = -0x54f;
    bounds.w[1] = 0;
    bounds.w[2] = bounds.w[0] - 0xd6;
    bounds.w[3] = bounds.w[0] + 0xa9d;
    bounds.w[4] = bounds.w[1] + 0xd34;
    bounds.w[5] = bounds.w[2] + 0x8b9;
    *(Callback *)(self + 0x8) = func_ov218_020cc294;
    *(Callback *)(self + 0xc) = func_ov218_020cc2d4;
    *(Callback *)(self + 0x1c) = func_ov218_020cc3f4;
    *(Callback *)(self + 0x30) = func_ov218_020cc560;
    *(Callback *)(self + 0x28) = func_ov218_020cc37c;
    *(Callback *)(self + 0x2c) = func_ov218_020cc3b8;
    *(Callback *)(self + 0x34) = func_ov218_020cc4ec;
    *(Callback *)(self + 0x1d0) = func_ov218_020cc5bc;
    *(Callback *)(self + 0x1dc) = func_ov218_020cc528;
    *(Callback *)(self + 0x1d4) = func_ov218_020cc77c;
    *(Callback *)(self + 0x1e0) = func_ov218_020cc79c;
    *(Callback *)(self + 0x1e4) = func_ov218_020cc7c8;
    *(int *)(self + 0x70) = 0x7cc;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x7cc;
    *(int *)(self + 0x6c) = 0;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_ov218_020cc018(self);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x3a8) = func_0203bdfc(*(int *)(self + 0x384), data_ov218_020cf32c);
    *(int *)(self + 0x3ac) = func_ov107_020c9e50(func_ov107_020c9440(self, 1), data_ov218_020cf338);
    kind = kinds.id;
    for (i = 0; i < 2; i++) {
        item = ((SubitemSlot *)(self + 0x3dc))[i].pItem = func_0203b898(func_ov107_020c9440(self, *kind++));
        func_ov107_020c9074(self, item);
        *(int *)(item + 0x5c) |= 2;
    }
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x38c) = *slot = func_ov107_020c319c(self + 0x64);
    for (i = 0; i < 2; i++) {
        ((int *)(self + 0x394))[i] = func_ov218_020ce040(self);
    }
    func_0203355c(0x135);
}
