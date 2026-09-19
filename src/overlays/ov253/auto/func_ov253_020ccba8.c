/* func_ov253_020ccba8 -- send message 0x2c to the actor's +0x24 hook (when set): a zeroed
 * 44-byte message with byte 2 = 0, the +0x448 handle at 0x24 and the +0x451 kind at 0x28. */
struct Ov253Msg {
    unsigned char kind;
    unsigned char sub;
    unsigned char b2;
    unsigned char pad[0x21];
    int handle;
    unsigned char kind28;
    unsigned char pad29[3];
};

void func_ov253_020ccba8(int self) {
    struct Ov253Msg msg = {0};
    void (*hook)(int, struct Ov253Msg *, int);

    msg.b2 = 0;
    msg.handle = *(int *)(self + 0x448);
    msg.kind28 = *(signed char *)(self + 0x400 + 0x51);
    hook = *(void (**)(int, struct Ov253Msg *, int))(self + 0x24);
    if (hook == 0) {
        return;
    }
    hook(self, &msg, 0x2c);
}
