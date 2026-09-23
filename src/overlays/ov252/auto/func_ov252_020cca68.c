/* Report the ov252 actor's armour to its +0x24 hook as a 0x44-byte snapshot: per piece the +0x38c
 * model's shown bit, the +0x518 record's high nibble and the +0x39c slot byte, then the +0x57a, +0x57c
 * and +0x57e masks. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int b0 : 1; int b1 : 1; } Bits;
typedef struct { u8 lo : 4; u8 hi : 4; } NibblePair;
struct Ov252Body {
    char pad[0x38c];
    int models[4];
    signed char slots[4];
    char pad3a0[0x518 - 0x3a0];
    NibblePair *records[4];
};
struct Ov252Msg {
    u8 kind;
    u8 sub;
    u8 b2;
    u8 pad[0x21];
    int shown[4];
    u8 armour[4];
    u16 masks[3];
    signed char slots[4];
    u8 pad42[2];
};

void func_ov252_020cca68(int self)
{
    struct Ov252Msg msg = {0};
    void (*hook)(int, struct Ov252Msg *, int);
    signed char i;

    msg.b2 = 0;
    for (i = 0; i < 4; i++) {
        msg.shown[i] = ((Bits *)(((struct Ov252Body *)self)->models[i] + 0x5c))->b1;
        msg.armour[i] = ((struct Ov252Body *)self)->records[i]->hi;
        msg.slots[i] = *(signed char *)(self + i + 0x39c);
    }
    msg.masks[0] = *(u16 *)(self + 0x57a);
    msg.masks[1] = *(u16 *)(self + 0x57c);
    msg.masks[2] = *(u16 *)(self + 0x57e);
    hook = *(void (**)(int, struct Ov252Msg *, int))(self + 0x24);
    if (hook == 0) {
        return;
    }
    hook(self, &msg, 0x44);
}
