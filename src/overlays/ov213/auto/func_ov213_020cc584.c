typedef struct {
    int w[9];
    unsigned int enabled : 1;
} Msg;
typedef struct { int enabled : 1; } ObjFlags;
typedef void (*MsgHook)(int *obj, Msg *m, int size);

/* Builds a 0x28-byte status message carrying only the enabled bit from +0x434 and hands it to
 * the object's hook, if it has one. */
void func_ov213_020cc584(int *obj) {
    Msg m = { 0 };
    m.enabled = ((ObjFlags *)((char *)obj + 0x434))->enabled;
    *((unsigned char *)&m + 2) = 0;
    if (obj[9] != 0) {
        (*(MsgHook)obj[9])(obj, &m, 0x28);
    }
}
