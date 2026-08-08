/* Build step for the ov031 actor: clears the ready flags, requests animation set 3,
 * binds three render handles -- one against the scene link the actor was spawned from
 * and two against models reached through the object it is attached to -- clears the
 * 0xcb-byte work block at +0xda0, then latches the four ready bits and returns them.
 *
 * Same shape as the ov047/ov044/ov066/ov085/ov102 build steps, written off the ov047
 * one: the descriptors are 0x10-byte structs passed by their byte array, the slot is
 * an int parameter, the binding parameter is a void * built as the ADDRESS OF A MEMBER
 * rather than a pointer sum, and the function RETURNS the latched flags. */
typedef unsigned char u8;

struct Ov031BuildBlock {
    char pad000[0x334];
    u8 flags334;
    char pad335[0x0b];
    u8 *handle340;
    u8 *handle344;
    u8 *handle348;
};

struct Ov031SceneLink {
    int field00;
    int field04;
};

struct Ov031Model {
    char pad000[0x28];
    int field28;
};

struct Ov031Attach {
    char pad000[0x0c];
    struct Ov031Model *model0c;
    char pad010[0x5c];
    struct Ov031Model *model6c;
};

struct Ov031Runtime {
    char pad000[9];
    u8 slot09;
    char pad00a[0x16];
    struct Ov031SceneLink *scene20;
    char pad024[0x22d4];
    struct Ov031BuildBlock buildBlock22f8;
    struct Ov031Attach *attach2644;
};

struct Ov031Descriptor {
    char bytes[0x10];
};

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot,
                               int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern struct Ov031Descriptor data_ov031_020b4d24;
extern struct Ov031Descriptor data_ov031_020b4d34;
extern struct Ov031Descriptor data_ov031_020b4d48;

u8 func_ov031_020b3830(struct Ov031Runtime *self)
{
    struct Ov031BuildBlock *block = &self->buildBlock22f8;

    block->flags334 = 0;
    func_ov022_020b15b0(self->slot09, 3);
    block->handle340 = func_ov022_020b14a4(
        data_ov031_020b4d24.bytes, self->slot09, 0,
        &self->scene20->field04);
    block->handle344 = func_ov022_020b14a4(
        data_ov031_020b4d34.bytes, self->slot09, 1,
        &self->attach2644->model6c->field28);
    block->handle348 = func_ov022_020b14a4(
        data_ov031_020b4d48.bytes, self->slot09, 2,
        &self->attach2644->model0c->field28);
    func_ov022_020b1cec((char *)self + 0xda0, 0xcb);
    return block->flags334 |= 0xf;
}
