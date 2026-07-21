extern int func_020235d0(int key, int sub);
extern int OS_SPrintf(char *buf, const char *fmt, ...);
extern char data_0204c270[];
extern char data_ov002_0207efc4[];
/* Format the day counter (game field 0x2080/5) into the shared string buffer. */
void func_ov002_0206a44c(void) {
    int day = func_020235d0(0x2080, 5);
    OS_SPrintf(data_0204c270, data_ov002_0207efc4, day);
}
