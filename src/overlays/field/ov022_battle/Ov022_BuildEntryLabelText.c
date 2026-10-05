/* Build the label for entry `arg1` and hand it to the text layer: copy the 18-word
 * template, format it with the entry's value, create the text object with the palette
 * byte from *(arg0+0x58)+9, and cache the object at +0x54 plus a flag byte at +0x10.
 *
 * The entry pointer at arg0 + arg1*4 + 0x18 is read TWICE and the ROM recomputes
 * `add r0, arg0, arg1 lsl #2` after the call rather than parking it in a callee-saved
 * register. Writing the two reads identically lets mwcc common them up, which is four
 * bytes short; spelling the second one through a `char *` base -- same address, same
 * two instructions -- is enough to stop the CSE without changing the addressing.
 *
 * Both locals live in ONE frame struct so the stack layout comes out as the ROM has it
 * (the word buffer at sp+0, the text buffer at sp+0x48). */
extern int data_ov022_020b2394;
extern int gOv022BaMaMoPackPathFmt;
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int Ov022_AcquireGridSlot(char *text, int palette, int layer, int owner);

struct Buf0208a830 { int w[18]; };
struct Frame0208a830 {
    struct Buf0208a830 buf;
    char tmp[128];
};

void Ov022_BuildEntryLabelText(int arg0, int arg1) {
    struct Frame0208a830 f;

    f.buf = *(struct Buf0208a830 *)&data_ov022_020b2394;
    OS_SPrintf(f.tmp, (const char *)&gOv022BaMaMoPackPathFmt, f.buf.w[arg1]);
    *(int *)(arg0 + 0x54) = Ov022_AcquireGridSlot(
        f.tmp, *(unsigned char *)(*(int *)(arg0 + 0x58) + 9), 1,
        *(int *)(arg0 + arg1 * 4 + 0x18) + 8);
    *(int *)(arg0 + 0x10) =
        *(unsigned char *)(((int *)((char *)arg0 + arg1 * 4))[6] + 0x112);
}
