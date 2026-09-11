typedef struct { short w[3]; } Msg;
typedef void (*MsgHook)(int *obj, Msg *m, int size);

/* Builds a zeroed 6-byte message and hands it to the object's hook, if it has one. */
void func_ov107_020caf24(int *obj) {
    Msg m = { 0 };
    *((unsigned char *)&m + 2) = 0;
    if (obj[9] != 0) {
        (*(MsgHook)obj[9])(obj, &m, 6);
    }
}
