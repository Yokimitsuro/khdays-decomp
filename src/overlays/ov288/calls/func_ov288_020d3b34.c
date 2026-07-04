extern void *func_ov107_020c7a90();

void *func_ov288_020d3b34(int this_, unsigned char *msg, int arg3) {
    if (msg[2] == 0) {
        msg[0x24] = *(int *)(this_ + 0x394);
    }
    return func_ov107_020c7a90(this_, msg, arg3);
}
