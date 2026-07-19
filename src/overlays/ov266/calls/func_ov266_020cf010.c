typedef struct { short w[97]; } Msg;
typedef struct { int b0 : 1; int b1 : 1; } SubFlags;
typedef void (*MsgHook)(int *obj, Msg *m, int size);

/* Builds a blank message and sends it to the hook -- the short 0x26-byte form when the sub-node
 * asks for it, the full 0xc2-byte one otherwise. */
void func_ov266_020cf010(int *obj) {
    Msg m = { 0 };
    MsgHook hook;
    *((unsigned char *)&m + 2) = 0;
    hook = (MsgHook)obj[9];
    if (((SubFlags *)(*(int *)((char *)obj + 0x38c) + 0x5c))->b1) {
        if (hook != 0) {
            hook(obj, &m, 0x26);
        }
    } else {
        if (hook != 0) {
            hook(obj, &m, 0xc2);
        }
    }
}
