typedef unsigned char u8;

struct Ov038BuildBlock {
    char pad000[0x334];
    u8 flags334;
    char pad335[0x0b];
    u8 *handle340;
    u8 *handle344;
};

struct Ov038SceneLink { int field00; int field04; };

struct Ov038Runtime {
    char pad000[9];
    u8 slot09;
    char pad00a[0x16];
    struct Ov038SceneLink *scene20;
    char pad024[0x22d4];
    struct Ov038BuildBlock buildBlock22f8;
};

struct Ov038SceneBlock { char pad000[0x11c]; int field11c; };
struct Ov038SceneBody { char pad0000[0x2c00]; struct Ov038SceneBlock block2c00; };
struct Ov038Scene { char pad000[0x2c]; struct Ov038SceneBody body2c; };
struct Ov038Descriptor { char bytes[0x10]; };

extern struct Ov038Scene *data_ov038_020b4ca0;
extern struct Ov038Descriptor data_ov038_020b4c10;
extern struct Ov038Descriptor data_ov038_020b4c20;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);

u8 func_ov038_020b3790(struct Ov038Runtime *self)
{
    struct Ov038SceneBlock *scene;
    struct Ov038BuildBlock *block = &self->buildBlock22f8;

    block->flags334 = 0;
    func_ov022_020b15b0(self->slot09, 2);
    scene = &data_ov038_020b4ca0->body2c.block2c00;
    block->handle340 = func_ov022_020b14a4(
        data_ov038_020b4c10.bytes, self->slot09, 0,
        &self->scene20->field04);
    block->handle344 = func_ov022_020b14a4(
        data_ov038_020b4c20.bytes, self->slot09, 1,
        &scene->field11c);
    func_ov022_020b1cec((char *)self + 0xda0, 0xc8);
    return block->flags334 |= 0xb;
}
