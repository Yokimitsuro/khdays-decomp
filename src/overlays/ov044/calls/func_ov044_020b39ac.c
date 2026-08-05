typedef unsigned char u8;

struct Ov044BuildBlock {
    char pad000[0x334];
    u8 flags334;
    char pad335[0x0b];
    u8 *handle340;
    u8 *handle344;
};

struct Ov044SceneLink {
    int field00;
    int field04;
};

struct Ov044Runtime {
    char pad000[9];
    u8 slot09;
    char pad00a[0x16];
    struct Ov044SceneLink *scene20;
    char pad024[0x2b8];
    char parameterBase2dc;
    char pad2dd[0x201b];
    struct Ov044BuildBlock buildBlock22f8;
};

struct Ov044Descriptor {
    char bytes[0x10];
};

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot,
                               int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern struct Ov044Descriptor data_ov044_020b557c[];

u8 func_ov044_020b39ac(struct Ov044Runtime *self)
{
    struct Ov044BuildBlock *block = &self->buildBlock22f8;

    block->flags334 = 0;
    func_ov022_020b15b0(self->slot09, 2);
    block->handle340 = func_ov022_020b14a4(
        data_ov044_020b557c[1].bytes, self->slot09, 0,
        &self->scene20->field04);
    block->handle344 = func_ov022_020b14a4(
        data_ov044_020b557c[2].bytes, self->slot09, 1,
        &self->parameterBase2dc + 0x2c00);
    func_ov022_020b1cec((char *)self + 0xda0, 0xd1);
    return block->flags334 |= 0xb;
}
