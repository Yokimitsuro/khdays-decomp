/* NONMATCHING: rematerialization-vs-CSE tie. The original recomputes
 * `add r0, obj, idx, lsl #2` after the 020b14a4 call before reloading the entry;
 * mwcc instead parks that address in a callee-saved register across the call,
 * coming out one instruction (4 bytes) short, and permutes the copy-loop registers
 * (src/dst/counter land in lr/ip/r5 instead of r6/lr/ip). `volatile` on the second
 * read forces the load but not the address recompute. The stack layout IS correct
 * once both locals are wrapped in one frame struct (buf at sp+0, tmp at sp+0x48).
 * Semantics below are exact. */
extern int data_ov022_020b2394;
extern int data_ov022_020b2b1c;
extern void func_02001878(char *dst, int *src, int v);
extern int func_ov022_020b14a4(char *a, int b, int c, int d);

struct Buf0208a830 { int w[18]; };
struct Frame0208a830 {
    struct Buf0208a830 buf;
    char tmp[128];
};

void func_ov022_0208a830(int arg0, int arg1) {
    struct Frame0208a830 f;
    f.buf = *(struct Buf0208a830 *)&data_ov022_020b2394;
    func_02001878(f.tmp, &data_ov022_020b2b1c, f.buf.w[arg1]);
    *(int *)(arg0 + 0x54) = func_ov022_020b14a4(
        f.tmp, *(unsigned char *)(*(int *)(arg0 + 0x58) + 9), 1,
        *(int *)(arg0 + arg1 * 4 + 0x18) + 8);
    *(int *)(arg0 + 0x10) = *(unsigned char *)(*(int *)(arg0 + arg1 * 4 + 0x18) + 0x112);
}
