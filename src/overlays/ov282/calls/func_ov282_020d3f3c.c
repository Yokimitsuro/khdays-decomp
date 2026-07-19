typedef struct { short w[15]; } Msg;
typedef void (*MsgHook)(int *obj, Msg *m, int size);

/* Builds a blank 0x1e-byte message and hands it to the object's hook, if it has one. */
void func_ov282_020d3f3c(int *obj) {
    Msg m = { 0 };
    *((unsigned char *)&m + 2) = 0;
    if (obj[9] != 0) {
        (*(MsgHook)obj[9])(obj, &m, 0x1e);
    }
}
