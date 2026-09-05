/* func_ov012_0205bcf0 -- MobiClip: pull the next character out of a subtitle stream (UTF-8).
 *
 * Decodes UTF-8 to a single UTF-16 code unit, advancing the stream's own cursor by the number of
 * bytes it consumed. Which text buffer and cursor to use depends on the stream's state (+0x6c):
 * state 0 reads the buffer at +0x74 through the cursor at +0x64, states 1..4 read the buffer at
 * +0x78[state-1] through the cursor at +0x68.
 *
 * The byte classes, in the order the ROM tests them:
 *   0x00        end of text -- reports 0 in state 0, otherwise resets to state 0 and reports 1
 *   0x01..0x1f  control code -- fed to the stream event dispatcher (func_ov012_0205bc08), and
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
 * MATCH: 340/340 bytes and 1/1 relocation in ARM mode. The early return for non-three-byte
 * lead values is source-shape significant: it makes MWCC preserve the ROM's cursor-load schedule.
 */
extern int func_ov012_0205bc08(int stream, int event);

unsigned short func_ov012_0205bcf0(int stream) {
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
        return (unsigned short)func_ov012_0205bc08(stream, ch);
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
    if ((ch & 0xf0) != 0xe0) return;
        unsigned short r = (unsigned short)(((unsigned short)(buf[*cursor + 1] & 0x3f) << 6) | ((unsigned short)(ch & 0xf) << 12) | (unsigned short)(buf[*cursor + 2] & 0x3f));
        *cursor = *cursor + 3;
        return r;

}
