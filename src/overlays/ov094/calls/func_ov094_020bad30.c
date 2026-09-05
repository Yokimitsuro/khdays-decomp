typedef unsigned char u8;

struct Ov094BuildBlock {
    char pad000[0x334];
    u8 flags334;
    char pad335[0x0b];
    u8 *handle340;
    u8 *handle344;
};

struct Ov094SceneLink { int field00; int field04; };

struct Ov094Runtime {
    char pad000[9];
    u8 slot09;
    char pad00a[0x16];
    struct Ov094SceneLink *scene20;
    char pad024[0x22d4];
    struct Ov094BuildBlock buildBlock22f8;
};

struct Ov094SceneBlock { char pad000[0x11c]; int field11c; };
struct Ov094SceneBody { char pad0000[0x2c00]; struct Ov094SceneBlock block2c00; };
struct Ov094Scene { char pad000[0x2c]; struct Ov094SceneBody body2c; };
struct Ov094Descriptor { char bytes[0x10]; };

extern struct Ov094Scene *data_ov094_020bc240;
extern struct Ov094Descriptor data_ov094_020bc1b0;
extern struct Ov094Descriptor data_ov094_020bc1c0;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);

u8 func_ov094_020bad30(struct Ov094Runtime *self)
{
    struct Ov094SceneBlock *scene;
    struct Ov094BuildBlock *block = &self->buildBlock22f8;

    block->flags334 = 0;
    func_ov022_020b15b0(self->slot09, 2);
    scene = &data_ov094_020bc240->body2c.block2c00;
    block->handle340 = func_ov022_020b14a4(
        data_ov094_020bc1b0.bytes, self->slot09, 0,
        &self->scene20->field04);
    block->handle344 = func_ov022_020b14a4(
        data_ov094_020bc1c0.bytes, self->slot09, 1,
        &scene->field11c);
    func_ov022_020b1cec((char *)self + 0xda0, 0xc8);
    return block->flags334 |= 0xb;
}
