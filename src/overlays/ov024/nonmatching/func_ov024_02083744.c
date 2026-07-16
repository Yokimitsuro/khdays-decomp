/* func_ov024_02083744 -- MobiClip: pull the next character out of a subtitle stream (UTF-8).
 *
 * Decodes UTF-8 to a single UTF-16 code unit, advancing the stream's own cursor by the number of
 * bytes it consumed. Which text buffer and cursor to use depends on the stream's state (+0x6c):
 * state 0 reads the buffer at +0x74 through the cursor at +0x64, states 1..4 read the buffer at
 * +0x78[state-1] through the cursor at +0x68.
 *
 * The byte classes, in the order the ROM tests them:
 *   0x00        end of text -- reports 0 in state 0, otherwise resets to state 0 and reports 1
 *   0x01..0x1f  control code -- fed to the stream event dispatcher (func_ov024_0208365c), and
 *               whatever that returns is passed back to the caller
 *   0x20..0x7f  plain ASCII, returned as-is
 *   110xxxxx    2-byte sequence -> (lead & 0x1f) << 6 | (cont & 0x3f)
 *   1110xxxx    3-byte sequence -> (lead & 0x0f) << 12 | (c1 & 0x3f) << 6 | (c2 & 0x3f)
 * No 4-byte form: this decoder tops out at the BMP, consistent with a u16 result.
 *
 * The bytes are read SIGNED (ldrsb), which is why the lead-byte masks still work: a 0xc2 lead
 * sign-extends to 0xffffffc2 and `& 0xe0` still yields 0xc0.
 *
 * Note there is NO final return: a byte that is neither ASCII nor a valid 2- or 3-byte lead
 * (a stray continuation byte, or a 4-byte lead) falls out of the function with r0 holding
 * whatever was left in it. Kept as-is -- do not "fix" it into a defined return.
 *
 * NONMATCHING: 340/340 bytes, byte-exact through 0x10c (268 of 340). The state switch and its
 * jump table, the terminator/control/ASCII paths and the whole 2-byte UTF-8 path all match.
 * Only the 3-byte path differs, and only in scheduling + register assignment: the ROM interleaves
 * the cursor load and its +3 earlier (ldr r3,[r2] at 0x128, add r1,r3,#3 at 0x134) among the
 * shifts, where mwcc sinks them to 0x130/0x140. Identical instruction multiset, same size.
 *
 * Two orderings DID matter and are already applied -- keep them if you retry this:
 * 1. In each multi-byte block, name the CONTINUATION byte's mask in a local BEFORE the lead's.
 *    That is what fixed the 2-byte path (the diff moved from 0xd1 to 0x10d): the ROM emits
 *    `and r3,r0,#0x3f` (cont) before `lsl r0,ip,#0x10` (lead), and the decl order drives it.
 * 2. The u16 locals are load-bearing: `(v << 6)` on an `unsigned short` v is what produces the
 *    ROM's `lsl #0x10 ; lsr #0xa` pair (i.e. `((u16)v) << 6`) rather than a plain `lsl #6`.
 * Tried and rejected: reordering the 3-byte block's decls to a/v/b (no change), and hoisting the
 * cursor update above the return to pull the ldr forward -- that one wrecks the whole function
 * (diff at 0x0), so the store must stay after the value is computed.
 */
extern int func_ov024_0208365c(int stream, int event);

unsigned short func_ov024_02083744(int stream) {
    int state;
    int *cursor;
    signed char *buf;
    int ch;

    state = *(int *)(stream + 0x6c);
    switch (state) {
    case 0:
        cursor = (int *)(stream + 0x64);
        buf = *(signed char **)(stream + 0x74);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        buf = *(signed char **)(stream + (state - 1) * 4 + 0x78);
        cursor = (int *)(stream + 0x68);
        break;
    }

    ch = buf[*cursor];
    if (ch == 0) {
        if (state == 0) {
            return 0;
        }
        *(int *)(stream + 0x6c) = 0;
        return 1;
    }
    if (ch >= 1 && ch < 0x20) {
        *cursor = *cursor + 1;
        return (unsigned short)func_ov024_0208365c(stream, ch);
    }
    if (ch >= 0x20 && ch < 0x80) {
        *cursor = *cursor + 1;
        return (unsigned short)ch;
    }
    if ((ch & 0xe0) == 0xc0) {
        unsigned short cont = (unsigned short)(buf[*cursor + 1] & 0x3f);
        unsigned short v = (unsigned short)(ch & 0x1f);
        unsigned short r = (unsigned short)((v << 6) | cont);
        *cursor = *cursor + 2;
        return r;
    }
    if ((ch & 0xf0) == 0xe0) {
        unsigned short a = (unsigned short)(buf[*cursor + 1] & 0x3f);
        unsigned short v = (unsigned short)(ch & 0xf);
        unsigned short b = (unsigned short)(buf[*cursor + 2] & 0x3f);
        unsigned short r = (unsigned short)((v << 12) | (a << 6) | b);
        *cursor = *cursor + 3;
        return r;
    }
}
