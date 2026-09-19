/* func_ov253_020d3aac -- item construction: installs the handlers (+8 020d3c38, +0xc 020d3c78,
 * +0x1c 020d3cac, +0x30 020d3e3c, +0x1d0 020d3de0), raises bits 1-4, 6-7 of the +0x60 high byte,
 * bit 2 of +0x1ae and of the +0x9c parent's +0x5c, sets +0x70 / +0x54, builds the +0x384 item
 * from pose 0x23 of the +0x388 pool (subscribed to the parent, channels 0 and 2 enabled,
 * finalised), allocates the +0x398 pair block whose two effects come from the
 * data_ov253_020d4a00 poses (registered, bit 1 of +0x5c raised), and links a +0x144 list slot
 * to the +0x64 pose as +0x39c. */
typedef unsigned short u16;
struct Ov253Poses { int w[2]; };
struct Ov253Pair { int pEffect; int pChild; };

extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern void func_0203c7ac(int item, int a);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(int self, int item);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern const struct Ov253Poses data_ov253_020d4a00;
extern void func_ov253_020d3c38(void);
extern void func_ov253_020d3c78(void);
extern void func_ov253_020d3cac(void);
extern void func_ov253_020d3e3c(void);
extern void func_ov253_020d3de0(void);

void func_ov253_020d3aac(char *self) {
    struct Ov253Poses poses = data_ov253_020d4a00;
    int i;
    int *p;

    *(void **)(self + 0x8) = func_ov253_020d3c38;
    *(void **)(self + 0xc) = func_ov253_020d3c78;
    *(void **)(self + 0x1c) = func_ov253_020d3cac;
    *(void **)(self + 0x30) = func_ov253_020d3e3c;
    *(void **)(self + 0x1d0) = func_ov253_020d3de0;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0xde) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x70) = 0x200;
    *(int *)(self + 0x54) = 0x100;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x388), 0x23));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(struct Ov253Pair **)(self + 0x398) = func_0203d15c(0x10);
    for (i = 0; i < 2; i++) {
        (*(struct Ov253Pair **)(self + 0x398))[i].pEffect =
            func_0203b898(func_ov107_020c9440(*(int *)(self + 0x388), poses.w[i]));
        func_ov107_020c9074(*(int *)(self + 0x388), (*(struct Ov253Pair **)(self + 0x398))[i].pEffect);
        *(int *)((*(struct Ov253Pair **)(self + 0x398))[i].pEffect + 0x5c) |= 2;
    }
    p = func_01fffca8(self + 0x144, 4, 0x64);
    *p = func_ov107_020c319c(self + 0x64);
    *(int *)(self + 0x39c) = *p;
}
