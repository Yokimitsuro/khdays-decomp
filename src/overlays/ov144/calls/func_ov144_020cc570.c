typedef struct { short w[20]; } Msg;
typedef void (*MsgHook)(int *obj, Msg *m, int size);

/* Builds a zeroed 0x28-byte message and hands it to the object's hook, if it has one. */
void func_ov144_020cc570(int *obj) {
    Msg m = { 0 };
    *((unsigned char *)&m + 2) = 0;
    if (obj[9] != 0) {
        (*(MsgHook)obj[9])(obj, &m, 0x28);
    }
}
