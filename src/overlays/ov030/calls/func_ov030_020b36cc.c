typedef unsigned char u8;

struct Ov030BuildBlock {
    char pad000[0x334];
    u8 flags334;
    char pad335[0x0b];
    u8 *handle340;
    u8 *handle344;
};

struct Ov030SceneLink { int field00; int field04; };

struct Ov030Runtime {
    char pad000[9];
    u8 slot09;
    char pad00a[0x16];
    struct Ov030SceneLink *scene20;
    char pad024[0x22d4];
    struct Ov030BuildBlock buildBlock22f8;
};

struct Ov030SceneBlock { char pad000[0x234]; int field234; };
struct Ov030Scene { char pad0000[0x2cb0]; struct Ov030SceneBlock block2cb0; };
struct Ov030Descriptor { char bytes[0x10]; };

extern struct Ov030Scene *data_ov030_020b5a00;
extern struct Ov030Descriptor data_ov030_020b5960;
extern struct Ov030Descriptor data_ov030_020b5970;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);

u8 func_ov030_020b36cc(struct Ov030Runtime *self)
{
    struct Ov030SceneBlock *scene = &data_ov030_020b5a00->block2cb0;
    struct Ov030BuildBlock *block = &self->buildBlock22f8;

    block->flags334 = 0;
    func_ov022_020b15b0(self->slot09, 2);
    block->handle340 = func_ov022_020b14a4(
        data_ov030_020b5960.bytes, self->slot09, 0,
        &self->scene20->field04);
    block->handle344 = func_ov022_020b14a4(
        data_ov030_020b5970.bytes, self->slot09, 1,
        &scene->field234);
    func_ov022_020b1cec((char *)self + 0xda0, 0xd0);
    return block->flags334 |= 0xb;
}
