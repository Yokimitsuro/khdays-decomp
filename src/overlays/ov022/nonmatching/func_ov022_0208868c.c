/* NONMATCHING: bit0-extract codegen tie. The original reads bit0 of the byte at
 * slot+0x3c via `ldrb; lsl#0x1f; lsr#0x1f` (a 1-bit unsigned bitfield read);
 * mwcc compiles both `& 1` and an explicit `(x<<31)>>31` down to a single
 * `and #1` (4B short), and modeling it as a bitfield struct overshoots (+4B).
 * Same logic. Returns: 0 if no entry; 1 if entry field@+0x2668 != 0; else bit0
 * of the global slot byte@+0x3c. */
extern int data_ov022_020b2e78;
extern unsigned short func_01fffe14(void);
extern int func_01fffde0(int arg0);
unsigned char func_ov022_0208868c(void) {
    int s = ((int *)&data_ov022_020b2e78)[1];
    unsigned short a = func_01fffe14();
    int e = func_01fffde0(a);
    if (e == 0) return 0;
    if (*(int *)(e + 0x2668) == 0) return *(unsigned char *)(s + 0x3c) & 1;
    return 1;
}
