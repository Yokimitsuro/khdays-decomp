/* Constructor of the ov125 enemy. Installs the handlers (+8 release, +0xc draw veneer, +0x1c
 * message, +0x28/+0x2c/+0x30 callbacks, +0x34 leave, +0x1d0 hit, +0x1dc/+0x1e0 finish), sets
 * bit 6 of the +0x60 high byte, the +0x70 latch (0xe00), zeroes the +0x64 camera vector,
 * builds the model item from table entry 0 (subscribed, translated 0xe00 down) and resolves the
 * two anchor handles into +0x394/+0x398; then allocates the 9-entry effect set at +0x39c from
 * the table's ids (each attached and flagged), registers the four action slots (0/1/2/4) with
 * 0x2000, sets the blend of entries 2/3/4/8, creates the two pools at +0x388/+0x38c seeded with
 * the camera key, allocates the +0x390 projectile entry and the two +0x3a0 sub-entries, and
 * requests resource 0x11b. */
typedef struct { int id[9]; } IdTable;
typedef struct { int subitem; int pad; } Slot;
typedef struct { char pad[0x3a0]; int nodes[2]; } SubEntries;
typedef unsigned short u16;
typedef void (*Callback)(void);

extern void func_ov126_020cfef8(void);
extern void func_ov126_020cff38(void);
extern void func_ov126_020cffc4(void);
extern void func_ov126_020d029c(void);
extern void func_ov126_020d0388(void);
extern void func_ov126_020d03c4(void);
extern void func_ov126_020d0400(void);
extern void func_ov126_020d0660(void);
extern void func_ov126_020d044c(void);
extern void func_ov126_020cff94(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203ca14(void *srt, int x, int y, int z);
extern int func_0203bee8(int item, int kind, void *name);
extern int *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern void func_ov107_020c92b0(char *self, int slot, int a, int b, int c);
extern void func_02016cd0(int anim, int blend);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *camera);
extern int *func_ov126_020d20f0(char *self);
extern int func_ov126_020d3470(char *self);
extern void func_0203355c(int resourceId);
extern IdTable data_ov126_020d3fe8;
extern char data_ov126_020d408c[];
extern char data_ov126_020d4094[];

void func_ov126_020cfc04(char *self)
{
    IdTable ids = data_ov126_020d3fe8;
    u16 hw;
    int i;
    int *slot;

    *(Callback *)(self + 0x8) = func_ov126_020cfef8;
    *(Callback *)(self + 0xc) = func_ov126_020cff38;
    *(Callback *)(self + 0x1c) = func_ov126_020cffc4;
    *(Callback *)(self + 0x34) = func_ov126_020d029c;
    *(Callback *)(self + 0x28) = func_ov126_020d0388;
    *(Callback *)(self + 0x2c) = func_ov126_020d03c4;
    *(Callback *)(self + 0x30) = func_ov126_020d0400;
    *(Callback *)(self + 0x1e0) = func_ov126_020d0660;
    *(Callback *)(self + 0x1d0) = func_ov126_020d044c;
    *(Callback *)(self + 0x1dc) = func_ov126_020cff94;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    *(int *)(self + 0x70) = 0xe00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203ca14((void *)(*(int *)(self + 0x384) + 4), 0, -0xe00, 0);
    *(int *)(self + 0x394) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov126_020d408c);
    *(int *)(self + 0x398) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov126_020d4094);
    *(int **)(self + 0x39c) = func_0203d15c(0x48);
    for (i = 0; i < 9; i++) {
        (*(Slot **)(self + 0x39c))[i].subitem = func_0203b898(func_ov107_020c9440(self, ids.id[i]));
        func_ov107_020c9074(self, (*(Slot **)(self + 0x39c))[i].subitem);
        *(int *)((*(Slot **)(self + 0x39c))[i].subitem + 0x5c) |= 2;
    }
    func_ov107_020c92b0(self, 0, 1, 0, 0x2000);
    func_ov107_020c92b0(self, 1, 1, 0, 0x2000);
    func_ov107_020c92b0(self, 2, 1, 0, 0x2000);
    func_ov107_020c92b0(self, 4, 1, 0, 0x2000);
    func_02016cd0(*(int *)(*(int *)((*(Slot **)(self + 0x39c))[2].subitem + 0x88) + 0x78), 0xa);
    func_02016cd0(*(int *)(*(int *)((*(Slot **)(self + 0x39c))[3].subitem + 0x88) + 0x78), 0xb);
    func_02016cd0(*(int *)(*(int *)((*(Slot **)(self + 0x39c))[4].subitem + 0x88) + 0x78), 0xa);
    func_02016cd0(*(int *)(*(int *)((*(Slot **)(self + 0x39c))[8].subitem + 0x88) + 0x78), 0xa);
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x38c) = *slot = func_ov107_020c319c(self + 0x64);
    *(int **)(self + 0x390) = func_ov126_020d20f0(self);
    for (i = 0; i < 2; i++) {
        ((SubEntries *)self)->nodes[i] = func_ov126_020d3470(self);
    }
    func_0203355c(0x11b);
}
