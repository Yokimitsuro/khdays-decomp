/* Fill a 2-word buffer for func_ov005_0204e194: for each slot, if the matching
 * param_2 flag bit 2 (+0x64 / +0x80) is set, copy from the func_ov005_0204e15c
 * result; otherwise compute it via func_0203602c from param_2->+0x4c / +0x68. */
extern int func_ov005_0204e15c(int param_1);
extern void func_0203602c(int src, void *dst);
extern void func_ov005_0204e194(int param_1, int param_2, void *buf);
struct bf3 { unsigned int b0:1, b1:1, b2:1; };
void func_ov005_0204dae0(int param_1, int param_2) {
    int buf[2];
    int *r = (int *)func_ov005_0204e15c(param_1);
    if (((struct bf3 *)(param_2 + 0x64))->b2) {
        buf[0] = r[0];
    } else {
        func_0203602c(param_2 + 0x4c, &buf[0]);
    }
    if (((struct bf3 *)(param_2 + 0x80))->b2) {
        buf[1] = r[1];
    } else {
        func_0203602c(param_2 + 0x68, &buf[1]);
    }
    func_ov005_0204e194(param_1, param_2, buf);
}
