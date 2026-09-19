/* func_ov253_020d2474 -- send message 0x2c to the actor's +0x24 hook (when set): a zeroed
 * 22-halfword message with byte 2 = 0 and the low halfwords of +0x398 / +0x38c / +0x390 / +0x394
 * at 0x24..0x2a. */
struct Ov253Msg2c { unsigned short w[22]; };

void func_ov253_020d2474(int self) {
    struct Ov253Msg2c msg = {0};
    void (*hook)(int, struct Ov253Msg2c *, int);

    msg.w[0x12] = (unsigned short)*(int *)(self + 0x398);
    msg.w[0x13] = (unsigned short)*(int *)(self + 0x38c);
    msg.w[0x14] = (unsigned short)*(int *)(self + 0x390);
    msg.w[0x15] = (unsigned short)*(int *)(self + 0x394);
    ((unsigned char *)&msg)[2] = 0;
    hook = *(void (**)(int, struct Ov253Msg2c *, int))(self + 0x24);
    if (hook == 0) {
        return;
    }
    hook(self, &msg, 0x2c);
}
