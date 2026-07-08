/* NON-MATCHING (register-allocation tie): semantically-equivalent, byte-structurally
   identical C (same THUMB instruction sequence + control flow, 96/96 bytes) but mwcc's
   register allocation differs from the original for this backward 4-entry search loop
   (orig holds -1 in a callee-saved reg and keeps `entry` in r7; mwcc re-derives -1 and
   re-materializes the base). The asm stub keeps the build byte-exact; this documents the
   logic for the PC-port / readability goal. Kept alongside the matched func_ov029_020b2f40. */

extern void func_0201e470();
extern char data_ov029_020b30b0[];
extern int data_ov029_020b320c[];
extern int data_ov029_020b3200[];
extern char data_ov029_020b2f70[];
int func_ov029_020b2ee0(int arg0, int idx)
{
    int off = idx << 4;
    int *entry = (int *)(data_ov029_020b30b0 + off);
    int *t = data_ov029_020b320c;
    int *e = entry + 3;
    int k = 3;
    int r = -1;
    while (k >= 0) {
        if (*t == -1 && *e != -1) {
            r = entry[k];
            data_ov029_020b3200[k] = r;
            break;
        }
        t--;
        e--;
        k--;
    }
    func_0201e470(0, r);
    (*(void (**)())(data_ov029_020b2f70 + off + k * 4))();
    return r;
}
