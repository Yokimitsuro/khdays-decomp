typedef unsigned char u8;

struct Ov063BuildBlock {
    char pad000[0x334];
    u8 flags334;
    char pad335[0x0b];
    u8 *handle340;
    u8 *handle344;
};

struct Ov063SceneLink {
    int field00;
    int field04;
};

struct Ov063Runtime {
    char pad000[9];
    u8 slot09;
    char pad00a[0x16];
    struct Ov063SceneLink *scene20;
    char pad024[0x2b8];
    char parameterBase2dc;
    char pad2dd[0x201b];
    struct Ov063BuildBlock buildBlock22f8;
};

struct Ov063Descriptor {
    char bytes[0x10];
};

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot,
                               int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern struct Ov063Descriptor data_ov063_020b7d7c[];

u8 func_ov063_020b61ac(struct Ov063Runtime *self)
{
    struct Ov063BuildBlock *block = &self->buildBlock22f8;

    block->flags334 = 0;
    func_ov022_020b15b0(self->slot09, 2);
    block->handle340 = func_ov022_020b14a4(
        data_ov063_020b7d7c[1].bytes, self->slot09, 0,
        &self->scene20->field04);
    block->handle344 = func_ov022_020b14a4(
        data_ov063_020b7d7c[2].bytes, self->slot09, 1,
        &self->parameterBase2dc + 0x2c00);
    func_ov022_020b1cec((char *)self + 0xda0, 0xd1);
    return block->flags334 |= 0xb;
}

