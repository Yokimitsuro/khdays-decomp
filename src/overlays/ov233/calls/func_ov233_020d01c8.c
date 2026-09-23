/* Setup of the ov229 enemy's companion: installs the +8 tick, +0xc, +0x1c message, +0x30 and +0x1dc
 * handlers, sets bits 1-3 of the +0x60 high byte and bits 2 and 4 of +0x1ae, the +0x64 pose (scale
 * 0.875) and flag 2 of the +0x9c body; the main model (+0x384, item 0x24 of the +0x38c pool) is
 * subscribed with its animation stopped, the +0x390 slot model (kind from data_ov233_020d0e20)
 * attached and hidden, and the +0x388 contact built from the pose. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int w[1]; } KindTable;
struct bf { unsigned b : 8; };

extern void func_ov233_020d0324(void);
extern void func_ov233_020d0348(void);
extern void func_ov233_020d0380(void);
extern void func_ov233_020d0490(void);
extern void func_ov233_020d03f8(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern void func_0203c7ac(int item, int a);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern const KindTable data_ov233_020d0e20;

void func_ov233_020d01c8(char *self)
{
    int pool = *(int *)(self + 0x38c);
    KindTable kinds;
    u16 hw;

    kinds = data_ov233_020d0e20;
    *(Callback *)(self + 0x8) = func_ov233_020d0324;
    *(Callback *)(self + 0xc) = func_ov233_020d0348;
    *(Callback *)(self + 0x1c) = func_ov233_020d0380;
    *(Callback *)(self + 0x30) = func_ov233_020d0490;
    *(Callback *)(self + 0x1dc) = func_ov233_020d03f8;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0xe) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 0x14;
    *(int *)(self + 0x70) = 0xe00;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    {
        int scale = *(int *)(self + 0x70);

        *(int *)(self + 0x64) = 0;
        *(int *)(self + 0x68) = scale;
        *(int *)(self + 0x6c) = 0;
    }
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x24));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x390) = func_0203b898(func_ov107_020c9440(pool, kinds.w[0]));
    func_ov107_020c9074(self, *(int *)(self + 0x390));
    *(int *)(*(int *)(self + 0x390) + 0x5c) |= 2;
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    ((struct bf *)(*(int *)(self + 0x388) + 8))->b |= 2;
}
