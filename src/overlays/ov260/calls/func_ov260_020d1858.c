/* Constructor of an ov260 sub-part (the pool at +0x38c is filled in by the creator). Installs the
 * handlers (+8, +0xc, +0x1c message, +0x30 update, +0x1d0 hit filter), sets bits 1-3 and 6 of the
 * +0x60 high byte and bit 2 of +0x1ae, scale 0.625 at +0x70, clears +0x54 / +0x58 and marks the
 * +0x9c parent (bit 2 of +0x5c); builds the +0x384 rig from pose 0x26 (subscribed to +0x9c) with
 * channels 0, 2, 4 and 1 bound to (0, 1) and re-inits it, builds the two hidden sub-items of its
 * id table into the +0x390 pairs, and reserves the +0x388 placement of the +0x64 pose on the
 * +0x22c pool (flag bit 1). */typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int id[2]; } IdTable2;
struct Pairs { char pad[0x390]; struct { int res; int handle; } pair[2]; };
typedef struct { unsigned f : 8; } B8;

extern void func_ov260_020d1a28(void);
extern void func_ov260_020d1a60(void);
extern void func_ov260_020d1a98(void);
extern void func_ov260_020d1c1c(void);
extern void func_ov260_020d1b94(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern void func_0203c7ac(int item, int a);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *placement);
extern IdTable2 data_ov260_020d2a88;

void func_ov260_020d1858(char *self)
{
    IdTable2 ids = data_ov260_020d2a88;
    int pool = *(int *)(self + 0x38c);
    u16 hw;
    int i;

    *(Callback *)(self + 0x8) = func_ov260_020d1a28;
    *(Callback *)(self + 0xc) = func_ov260_020d1a60;
    *(Callback *)(self + 0x1c) = func_ov260_020d1a98;
    *(Callback *)(self + 0x30) = func_ov260_020d1c1c;
    *(Callback *)(self + 0x1d0) = func_ov260_020d1b94;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    *(int *)(self + 0x70) = 0xa00;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x26));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 4, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 1, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    for (i = 0; i < 2; i++) {
        ((struct Pairs *)self)->pair[i].res = func_0203b898(func_ov107_020c9440(pool, ids.id[i]));
        func_ov107_020c9074(self, ((struct Pairs *)self)->pair[i].res);
        *(int *)(((struct Pairs *)self)->pair[i].res + 0x5c) |= 2;
    }
    *(int *)(self + 0x388) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    ((B8 *)(*(int *)(self + 0x388) + 8))->f |= 2;
}
