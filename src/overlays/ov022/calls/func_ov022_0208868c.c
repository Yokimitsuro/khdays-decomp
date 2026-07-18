/* Three things have to line up here, and each one alone looks like a tie:
 *  - the 1-bit `unsigned char` BITFIELD gives the ROM's lsl#31/lsr#31; `& 1` gives `and #1`;
 *  - the TERNARY keeps the tail predicated (ldrbeq/lsleq/lsreq); an `if` + early return
 *    makes mwcc branch with a popne;
 *  - the return type is INT, not unsigned char -- a narrow return adds `and r0,r0,#0xff`. */
extern int data_ov022_020b2e78;
extern unsigned short func_01fffe14(void);
extern int func_01fffde0(int arg0);

struct Flag3c { unsigned char b0 : 1; };

int func_ov022_0208868c(void) {
    int s = ((int *)&data_ov022_020b2e78)[1];
    unsigned short a = func_01fffe14();
    int e = func_01fffde0(a);
    if (e == 0) return 0;
    return *(int *)(e + 0x2668) != 0 ? 1 : ((struct Flag3c *)(s + 0x3c))->b0;
}
