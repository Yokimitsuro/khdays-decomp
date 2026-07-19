typedef struct {
    short w[20];
    unsigned char enabled : 1;
} Msg;
typedef struct { int enabled : 1; } ObjFlags;
typedef void (*MsgHook)(int *obj, Msg *m, int size);

/* Builds a 0x2a-byte status message -- the enabled bit from +0x3d4 and the two coordinates at
 * +0x3bc/+0x3be -- and hands it to the object's hook, if it has one. */
void func_ov278_020ce430(int *obj) {
    Msg m = { 0 };
    *((unsigned char *)&m + 2) = 0;
    m.enabled = ((ObjFlags *)((char *)obj + 0x3d4))->enabled;
    m.w[18] = *(short *)((char *)obj + 0x300 + 0xd0);
    m.w[19] = *(short *)((char *)obj + 0x300 + 0xd2);
    if (obj[9] != 0) {
        (*(MsgHook)obj[9])(obj, &m, 0x2a);
    }
}
