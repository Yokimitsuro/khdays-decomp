/* Setup of the ov230 actor's companion: installs the +8 tick (020d5dd0), +0x1c message (020d5df4),
 * +0x30 (020d5f04) and +0x1dc (020d5e6c) handlers, sets bits 1-3 of the +0x60 high byte and bits 2 and
 * 4 of +0x1ae and the +0x64 pose (scale 0.5); the main model (+0x384, item 0x23 of the +0x388 pool) is
 * subscribed to +0x9c and the +0x38c slot model (kind from data_ov230_020d6464) attached and hidden. */
typedef unsigned short u16;
typedef void (*Callback)(void);
typedef struct { int w[1]; } KindTable;

extern void func_ov230_020d5dd0(void);
extern void func_ov230_020d5df4(void);
extern void func_ov230_020d5f04(void);
extern void func_ov230_020d5e6c(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203c7ac(int item, int a);
extern void func_ov107_020c9074(char *self, int item);
extern const KindTable data_ov230_020d6464;

void func_ov230_020d5cdc(char *self)
{
    int pool = *(int *)(self + 0x388);
    KindTable kinds;
    u16 hw;

    kinds = data_ov230_020d6464;
    *(Callback *)(self + 0x8) = func_ov230_020d5dd0;
    *(Callback *)(self + 0x1c) = func_ov230_020d5df4;
    *(Callback *)(self + 0x30) = func_ov230_020d5f04;
    *(Callback *)(self + 0x1dc) = func_ov230_020d5e6c;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0xe) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 0x14;
    *(int *)(self + 0x70) = 0x800;
    {
        int scale = *(int *)(self + 0x70);

        *(int *)(self + 0x64) = 0;
        *(int *)(self + 0x68) = scale;
        *(int *)(self + 0x6c) = 0;
    }
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x23));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(pool, kinds.w[0]));
    func_ov107_020c9074(self, *(int *)(self + 0x38c));
    *(int *)(*(int *)(self + 0x38c) + 0x5c) |= 2;
}
