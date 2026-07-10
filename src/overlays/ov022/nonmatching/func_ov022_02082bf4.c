/*
 * [nonmatching: branch-layout tie: inverting the top-level (u16&4) guard aligned it, but the inner (&&-guarded 0206b5a0) blocks lay out in a different order than the original]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted
 * register allocation / block layout. Left uncarved (byte-exact in the blob).
 */
extern int func_02021054(int arg0);
extern int func_ov002_0206b5a0(int arg0);
extern void func_ov002_02071b10(void);
extern void func_ov022_02083c08(int arg0);
extern int func_01fffe14(void);
extern int data_ov022_020b2e60;
extern void func_ov022_02082c54(void);
extern int data_0204c240;

int func_ov022_02082bf4(void) {
    int ret = 0;
    if ((*(unsigned short *)*(int *)&data_ov022_020b2e60 & 4) != 0) {
        if (func_02021054(*(int *)(*(int *)&data_ov022_020b2e60 + 0x2c)) != 0 &&
            func_ov002_0206b5a0(-1) != 0) {
            func_ov002_02071b10();
            ret = (int)func_ov022_02082c54;
        }
    } else {
        int arg;
        func_ov022_02083c08(0);
        if ((*(int *)&data_0204c240 & 4) == 0) {
            arg = -1;
        } else {
            arg = func_01fffe14();
        }
        if (func_ov002_0206b5a0(arg) != 0) {
            ret = (int)func_ov022_02082c54;
        }
    }
    return ret;
}
