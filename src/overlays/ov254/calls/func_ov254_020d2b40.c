/* Constructor of an ov254 helper: installs its handlers (+8, +0xc, +0x30 update, +0x1d0 hit
 * filter, +0x1dc), sets bits 2-3 and 9 of +0x1ae and bit 15 of the +0 flags, scale 1.0, +0x54 =
 * 3.0, clears +0x58 and the +0x64 pose, builds the +0x384 item (pose 0x44 of the +0x394 pool,
 * subscribed and re-initialised) and places the +0x64 pose on the +0x22c (+0x388) and +0x144
 * (+0x38c) pools. */
typedef unsigned short u16;
typedef void (*Callback)(void);

extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203c7ac(int item, int a);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *placement);
extern void func_ov254_020d2c3c(void);
extern void func_ov254_020d2c58(void);
extern void func_ov254_020d2f98(void);
extern void func_ov254_020d2e4c(void);
extern void func_ov254_020d2cb8(void);

void func_ov254_020d2b40(char *self)
{
    int pool = *(int *)(self + 0x394);
    int *slot;

    *(Callback *)(self + 0x8) = func_ov254_020d2c3c;
    *(Callback *)(self + 0xc) = func_ov254_020d2c58;
    *(Callback *)(self + 0x30) = func_ov254_020d2f98;
    *(Callback *)(self + 0x1d0) = func_ov254_020d2e4c;
    *(Callback *)(self + 0x1dc) = func_ov254_020d2cb8;
    *(u16 *)(self + 0x100 + 0xae) |= 0x20c;
    *(u16 *)self |= 0x8000;
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x54) = 0x3000;
    *(int *)(self + 0x58) = 0;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x44));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x388) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x38c) = *slot = func_ov107_020c319c(self + 0x64);
}
