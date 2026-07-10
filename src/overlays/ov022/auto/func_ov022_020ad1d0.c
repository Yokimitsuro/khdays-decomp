/* 64-bit flag word at +0x464; the struct-field form keeps `ldr [obj,#0x468]` direct. */
struct Flags020ad1d0 { char pad0[0x464]; unsigned long long flags; };

int func_ov022_020ad1d0(int arg0) {
    int r = -1;
    if (*(unsigned char *)(arg0 + 0x4f0) == 2 &&
        (((struct Flags020ad1d0 *)arg0)->flags & 0x10LL) == 0) {
        r = *(unsigned char *)(*(int *)(arg0 + 0x4f8) + 0x17);
    }
    return r;
}
