/* func_ov008_020594d0 -- ov008 per-frame branch: if bit 5 of the mode halfword at +0x5c6 is set,
 * run the fast path; otherwise run the slow one only when the shared phase byte is exactly 8 with
 * bit 1 masked off (`& 0xb`).
 * Both callees take this function's own argument, and since it is already in r0 nothing is emitted
 * for it -- which is why the call sites look argument-free and why the flags chain has to live in
 * r1. */
extern void WM_EndKeySharing_0x020594c4(int a);
extern void func_ov008_02058ae0(int a);
extern int data_ov008_02090f1c;
extern unsigned short data_0204c18c;

struct Ov008Flags { unsigned short lo : 5, bit5 : 1, rest : 10; };

void func_ov008_020594d0(int arg) {
    if (((struct Ov008Flags *)(*(int *)&data_ov008_02090f1c + 0x5c6))->bit5 != 0) {
        WM_EndKeySharing_0x020594c4(arg);
        return;
    }
    if ((data_0204c18c & 0xb) == 8) {
        func_ov008_02058ae0(arg);
    }
}
