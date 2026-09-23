/* Constructor of the ov255 partner object: installs its handlers (+8 update, +0xc draw, +0x1c
 * message, +0x30, +0x34, +0x1d0 hit filter), raises bits 1-4, 6 and 7 of the +0x60 high byte and
 * bits 2 and 4 of +0x1ae, sets the +0x70 scale to 0.125, builds the +0x388 binding of the rig's
 * pose 0x4a, creates the +0x3c4 effect (func_ov255_020d26b8), allocates the two-pair +0x3c0 table
 * (the first item from the data_ov255_020d2c30 resource, the second from pose 0x4b; both hidden)
 * and reserves the +0x38c shape (a placement at the +0x64 pose, flag bit 1). */
typedef void (*Callback)(void);
struct Word8 { unsigned int lo : 8; };

extern int func_ov107_020c9c24(const char *name);
extern void *func_ov107_020c9440(int obj, int index);
extern int func_0203c1b0(void *res, int size);
extern void func_ov107_020c9074(int self, int item);
extern int func_ov255_020d26b8(char *self);
extern int *func_0203d15c(int size);
extern int func_0203b898(void *res);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(const void *placement);
extern const char data_ov255_020d2c30[];
extern void func_ov255_020d1a20(void);
extern void func_ov255_020d1a60(void);
extern void func_ov255_020d1a98(void);
extern void WM_EndKeySharing_0x020d1b6c(void);
extern void func_ov255_020d1ba8(void);
extern void func_ov255_020d1b78(void);

void func_ov255_020d187c(char *self)
{
    int res = func_ov107_020c9c24(data_ov255_020d2c30);
    unsigned short hw;

    *(Callback *)(self + 0x8) = func_ov255_020d1a20;
    *(Callback *)(self + 0xc) = func_ov255_020d1a60;
    *(Callback *)(self + 0x1c) = func_ov255_020d1a98;
    *(Callback *)(self + 0x34) = WM_EndKeySharing_0x020d1b6c;
    *(Callback *)(self + 0x30) = func_ov255_020d1ba8;
    *(Callback *)(self + 0x1d0) = func_ov255_020d1b78;
    hw = *(unsigned short *)(self + 0x60);
    *(unsigned short *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0xde) << 0x18) >> 0x10);
    *(unsigned short *)(self + 0x100 + 0xae) |= 0x14;
    *(int *)(self + 0x70) = 0x200;
    *(int *)(self + 0x388) = func_0203c1b0(func_ov107_020c9440(*(int *)(self + 0x384), 0x4a), 0x20);
    func_ov107_020c9074(*(int *)(self + 0x384), *(int *)(self + 0x388));
    *(int *)(self + 0x3c4) = func_ov255_020d26b8(self);
    *(int **)(self + 0x3c0) = func_0203d15c(0x10);
    (*(int **)(self + 0x3c0))[0] = func_0203b898((void *)((((res + 0x8000) & 0xfffffc) << 7) | 0x80000001));
    func_ov107_020c9074((int)self, (*(int **)(self + 0x3c0))[0]);
    *(int *)((*(int **)(self + 0x3c0))[0] + 0x5c) |= 2;
    (*(int **)(self + 0x3c0))[2] = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), 0x4b));
    func_ov107_020c9074((int)self, (*(int **)(self + 0x3c0))[2]);
    *(int *)((*(int **)(self + 0x3c0))[2] + 0x5c) |= 2;
    *(int **)(self + 0x38c) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x38c) = func_ov107_020c319c(self + 0x64);
    ((struct Word8 *)(*(int *)(self + 0x38c) + 8))->lo |= 2;
}
