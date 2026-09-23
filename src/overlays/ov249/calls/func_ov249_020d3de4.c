/* Setup of the ov249 actor: installs the +8 tick (020d3f88), +0xc (020d3fac), +0x1c message (020d3fe4)
 * and +0x30 (020d408c) handlers, sets bits 1-3 of the +0x60 high byte and bits 2 and 4 of +0x1ae, the
 * +0x70 scale to 0.625 and clears +0x54/+0x58 and the +0x64 pose; the +0x9c body gets flag 2. The main
 * model (+0x384, pool item 0x24) is subscribed with actions 0/2/4/1 enabled, the +0x390 slot model
 * (kind from data_ov249_020d4988) attached and hidden, and the +0x388 contact built from the pose. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int w[1]; } KindTable;
struct bf { unsigned b : 8; };

extern void func_ov249_020d3f88(void);
extern void func_ov249_020d3fac(void);
extern void func_ov249_020d3fe4(void);
extern void func_ov249_020d408c(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern void func_0203c7ac(int item, int a);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern const KindTable data_ov249_020d4988;

void func_ov249_020d3de4(char *self)
{
    int pool = *(int *)(self + 0x38c);
    KindTable kinds;
    u16 hw;

    kinds = data_ov249_020d4988;
    *(Callback *)(self + 0x8) = func_ov249_020d3f88;
    *(Callback *)(self + 0xc) = func_ov249_020d3fac;
    *(Callback *)(self + 0x1c) = func_ov249_020d3fe4;
    *(Callback *)(self + 0x30) = func_ov249_020d408c;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0xe) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 0x14;
    *(int *)(self + 0x70) = 0xa00;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x24));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 4, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 1, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x390) = func_0203b898(func_ov107_020c9440(pool, kinds.w[0]));
    func_ov107_020c9074(self, *(int *)(self + 0x390));
    *(int *)(*(int *)(self + 0x390) + 0x5c) |= 2;
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    ((struct bf *)(*(int *)(self + 0x388) + 8))->b |= 2;
}
