/* NONMATCHING: block-layout tie. mwcc places the c==2 (func_0201ef58) block
 * inline; the original places it out-of-line (beq to it) and the c==3/4 test
 * inline (+4B for the extra branch). func_020339b0 is genuinely 2-arg (p[6],p[2]).
 * Logic: c=*arg0; if c==2 call func_0201ef58(2,args); if c in {2,3,4} call
 * func_020339b0(p[6],p[2]); always func_ov022_020b1be8(arg0,p[6]). */
extern void func_0201ef58(int a, int b, int c, int d);
extern void func_020339b0(int a, int b);
extern void func_ov022_020b1be8(char *p, char v);
void func_ov022_020b1c08(char *arg0, int arg1, int arg2, int arg3) {
    unsigned char c = *arg0;
    if (c == 2) func_0201ef58(2, arg1, arg2, arg3);
    else if (c != 3 && c != 4) goto skip;
    func_020339b0(arg0[6], *(short *)(arg0 + 2));
skip:
    func_ov022_020b1be8(arg0, arg0[6]);
}
