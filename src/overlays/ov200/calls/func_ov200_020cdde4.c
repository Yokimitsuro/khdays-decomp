/* Constructor of the ov200 enemy (x2 with ov201). Installs the handlers (+8, +0xc draw, +0x1c
 * message, +0x28, +0x2c, +0x30, +0x34 update, +0x1d0 hit filter, +0x1dc, +0x1e0), copies the
 * data_ov200_020d1814 bounds box to +0x1fc, raises bit 6 of the +0x60 high byte, sets the +0x64
 * pose (scale 2.65), builds the +0x384 rig from pose 0 (subscribed to +0x9c, lowered by the same
 * 2.65) and resolves its two set-1 bones (+0x39c, +0x3a0); builds the four sub-items of
 * data_ov200_020d1804 into the +0x3a4 pair table (registered, bit 1 of +0x5c), registers actions
 * 0, 1, 2 and 4 with mode 1 (rate 3.0), builds the ten-joint +0x3a8 chain from pose 8, reserves
 * the +0x22c placement (+0x388) and one +0x144 placement (+0x38c) at the pose, creates the three
 * +0x390 parts (func_ov200_020d032c kinds 0/1/2) and loads sound 0x157. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int id[4]; } IdTable;
typedef struct { int w[6]; } Box;
typedef struct { int subitem; int pad; } Slot;

extern void func_ov200_020ce0d0(void);
extern void func_ov200_020ce134(void);
extern void func_ov200_020ce1c8(void);
extern void func_ov200_020ce4b8(void);
extern void WM_EndKeySharing_0x020ce638(void);
extern void WM_EndKeySharing_0x020ce644(void);
extern void func_ov200_020ce650(void);
extern void func_ov200_020ce8c4(void);
extern void func_ov200_020ce6ac(void);
extern void func_ov200_020ce190(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203ca14(void *srt, int x, int y, int z);
extern int func_0203bee8(int item, int kind, void *name);
extern int *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov107_020c92b0(char *self, int slot, int a, int b, int c);
extern int func_0203c1b0(void *res, int joints);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *camera);
extern int func_ov200_020d032c(char *self, int kind);
extern void func_0203355c(int resourceId);
extern IdTable data_ov200_020d1804;
extern Box data_ov200_020d1814;
extern char data_ov200_020d186c[];
extern char data_ov200_020d1874[];

void func_ov200_020cdde4(char *self)
{
    IdTable ids = data_ov200_020d1804;
    u16 hw;
    int i;
    int *slot;

    *(Callback *)(self + 0x8) = func_ov200_020ce0d0;
    *(Callback *)(self + 0xc) = func_ov200_020ce134;
    *(Callback *)(self + 0x1c) = func_ov200_020ce1c8;
    *(Callback *)(self + 0x34) = func_ov200_020ce4b8;
    *(Callback *)(self + 0x28) = WM_EndKeySharing_0x020ce638;
    *(Callback *)(self + 0x2c) = WM_EndKeySharing_0x020ce644;
    *(Callback *)(self + 0x30) = func_ov200_020ce650;
    *(Callback *)(self + 0x1e0) = func_ov200_020ce8c4;
    *(Callback *)(self + 0x1d0) = func_ov200_020ce6ac;
    *(Callback *)(self + 0x1dc) = func_ov200_020ce190;
    *(Box *)(self + 0x1fc) = data_ov200_020d1814;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    *(int *)(self + 0x70) = 0x2a66;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203ca14((void *)(*(int *)(self + 0x384) + 4), 0, -0x2a66, 0);
    *(int *)(self + 0x39c) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov200_020d186c);
    *(int *)(self + 0x3a0) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov200_020d1874);
    *(int **)(self + 0x3a4) = func_0203d15c(0x20);
    for (i = 0; i < 4; i++) {
        (*(Slot **)(self + 0x3a4))[i].subitem = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, (*(Slot **)(self + 0x3a4))[i].subitem);
        *(int *)((*(Slot **)(self + 0x3a4))[i].subitem + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 0, 1, 0, 0x3000);
    func_ov107_020c92b0(self, 1, 1, 0, 0x3000);
    func_ov107_020c92b0(self, 2, 1, 0, 0x3000);
    func_ov107_020c92b0(self, 4, 1, 0, 0x3000);
    *(int *)(self + 0x3a8) = func_0203c1b0(func_ov107_020c9440(self, 8), 0xa);
    func_ov107_020c9074(self, *(int *)(self + 0x3a8));
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x38c) = *slot = func_ov107_020c319c(self + 0x64);
    for (i = 0; i < 3; i++) {
        int kind = 0;
        switch (i) {
        case 0:
            kind = 0;
            break;
        case 2:
            kind = 2;
            break;
        case 1:
            kind = 1;
            break;
        }
        ((int *)(self + 0x390))[i] = func_ov200_020d032c(self, kind);
    }
    func_0203355c(0x157);
}
