/* Build step for the ov050 actor: clears the ready flags, requests animation set 3,
 * binds three render handles -- one against the scene link the actor was spawned from
 * and two against models reached through the object it is attached to -- clears the
 * 0xcb-byte work block at +0xda0, then latches the four ready bits and returns them.
 *
 * Same shape as the ov047/ov044/ov066/ov085/ov102 build steps, written off the ov047
 * one: the descriptors are 0x10-byte structs passed by their byte array, the slot is
 * an int parameter, the binding parameter is a void * built as the ADDRESS OF A MEMBER
 * rather than a pointer sum, and the function RETURNS the latched flags. */
typedef unsigned char u8;

struct Ov050BuildBlock {
    char pad000[0x334];
    u8 flags334;
    char pad335[0x0b];
    u8 *handle340;
    u8 *handle344;
    u8 *handle348;
};

struct Ov050SceneLink {
    int field00;
    int field04;
};

struct Ov050Model {
    char pad000[0x28];
    int field28;
};

struct Ov050Attach {
    char pad000[0x0c];
    struct Ov050Model *model0c;
    char pad010[0x5c];
    struct Ov050Model *model6c;
};

struct Ov050Runtime {
    char pad000[9];
    u8 slot09;
    char pad00a[0x16];
    struct Ov050SceneLink *scene20;
    char pad024[0x22d4];
    struct Ov050BuildBlock buildBlock22f8;
    struct Ov050Attach *attach2644;
};

struct Ov050Descriptor {
    char bytes[0x10];
};

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot,
                               int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern struct Ov050Descriptor data_ov050_020b7524;
extern struct Ov050Descriptor data_ov050_020b7534;
extern struct Ov050Descriptor data_ov050_020b7548;

u8 func_ov050_020b6030(struct Ov050Runtime *self)
{
    struct Ov050BuildBlock *block = &self->buildBlock22f8;

    block->flags334 = 0;
    func_ov022_020b15b0(self->slot09, 3);
    block->handle340 = func_ov022_020b14a4(
        data_ov050_020b7524.bytes, self->slot09, 0,
        &self->scene20->field04);
    block->handle344 = func_ov022_020b14a4(
        data_ov050_020b7534.bytes, self->slot09, 1,
        &self->attach2644->model6c->field28);
    block->handle348 = func_ov022_020b14a4(
        data_ov050_020b7548.bytes, self->slot09, 2,
        &self->attach2644->model0c->field28);
    func_ov022_020b1cec((char *)self + 0xda0, 0xcb);
    return block->flags334 |= 0xf;
}
