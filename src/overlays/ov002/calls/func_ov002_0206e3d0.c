/* Publish a state change. In a live session it goes out as a link message --
 * kind 0x15 from the host, 0x14 from a client -- and an unassigned reply
 * (0xffff) reports failure. Outside a session it is posted locally as event
 * data instead. Reports 1 unless the link request came back unassigned. */
extern int func_02030670(void);
extern int func_02030788(void);
extern int func_ov002_0206fb84(int kind, void *message);
extern void func_020235e8(int a, int b, unsigned short c);

int func_ov002_0206e3d0(int a, int b, int c) {
    unsigned char message[8];

    if (func_02030670() != 0) {
        *(short *)(message + 2) = (short)a;
        message[4] = (unsigned char)b;
        *(short *)(message + 6) = (short)c;

        if (func_ov002_0206fb84(func_02030788() == 0 ? 0x14 : 0x15, message) == 0xffff) {
            return 0;
        }
    } else {
        func_020235e8(a, b, (unsigned short)c);
    }

    return 1;
}
