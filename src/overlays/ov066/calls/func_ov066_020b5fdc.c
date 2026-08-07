/* Build step for the ov066 actor: clears the ready flags, requests animation set 2,
 * binds two render handles -- one against the scene link the actor was spawned from
 * and one against the model of the object it is attached to -- clears the 0xd4-byte
 * work block at +0xda0, then latches the three ready bits and returns them. */
typedef unsigned char u8;

struct Ov047BuildBlock {
    char pad000[0x334];
    u8 flags334;
    char pad335[0x0b];
    u8 *handle340;
    u8 *handle344;
};

struct Ov047SceneLink {
    int field00;
    int field04;
};

struct Ov047Model {
    char pad000[0x28];
    int field28;
};

struct Ov047Attach {
    char pad000[0x0c];
    struct Ov047Model *model0c;
};

struct Ov047Runtime {
    char pad000[9];
    u8 slot09;
    char pad00a[0x16];
    struct Ov047SceneLink *scene20;
    char pad024[0x22d4];
    struct Ov047BuildBlock buildBlock22f8;
    char pad2640[4];
    struct Ov047Attach *attach2644;
};

struct Ov047Descriptor {
    char bytes[0x10];
};

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot,
                               int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern struct Ov047Descriptor data_ov066_020b6b1c;
extern struct Ov047Descriptor data_ov066_020b6b2c;

u8 func_ov066_020b37dc(struct Ov047Runtime *self)
{
    struct Ov047BuildBlock *block = &self->buildBlock22f8;

    block->flags334 = 0;
    func_ov022_020b15b0(self->slot09, 2);
    block->handle340 = func_ov022_020b14a4(
        data_ov066_020b6b1c.bytes, self->slot09, 0,
        &self->scene20->field04);
    block->handle344 = func_ov022_020b14a4(
        data_ov066_020b6b2c.bytes, self->slot09, 1,
        &self->attach2644->model0c->field28);
    func_ov022_020b1cec((char *)self + 0xda0, 0xd4);
    return block->flags334 |= 0xb;
}
