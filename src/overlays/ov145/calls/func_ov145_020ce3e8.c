extern void *func_ov107_020c7a90();

struct actor_1c6 {
    signed char _pad[0x1c6];
    signed char field_1c6;
};

void *func_ov145_020ce3e8(int this_, unsigned char *msg, int arg3) {
    if (msg[2] == 0) {
        msg[0x24] = ((struct actor_1c6 *)this_)->field_1c6;
        msg[0x26] = *(int *)(this_ + 0x3f4);
        msg[0x25] = *(int *)(this_ + 0x3bc);
    }
    return func_ov107_020c7a90(this_, msg, arg3);
}
