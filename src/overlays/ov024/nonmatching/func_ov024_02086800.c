/* NONMATCHING: 336B vs 344B -- 82 of 84 instructions correct, and every one of the four
 * codepaths (step lookup, bit-weighted diff, sign, saturation, nibble packing) matches. The
 * two missing instructions are both register allocation, the same "retail's compiler shares
 * less than mwcc 3.0/139" family as ov000 0204ef84 (see references/deferred-ties.md):
 *   1. the ROM emits `movmi X,#0 ; strmi X,[r0,#4]` at BOTH step-index clamps, materialising
 *      the zero each time; mwcc hoists a zero into a callee-saved reg (`mov r4,r7`) and emits
 *      a single `strmi r4` per site -- one instruction fewer, twice.
 *   2. the ROM copies the old step index (`mov fp,r9`) before destroying r9 with idx*2; mwcc
 *      allocates around it without the copy.
 * Cracks that DID land here and are worth reusing:
 *   - `if (count <= 0)` not `< 1`  -> `cmp r2,#0` instead of `cmp r2,#1`
 *   - predicate BOTH arms of the sign (`if (c & 8) s -= d; else s += d;`) to get the ROM's
 *     `addeq`/`subne` pair instead of mwcc's `rsbne` negate-then-add
 *   - hold the source byte in a SIGNED int so `code >> 4` emits `asr`, not `lsr`
 *
 * func_ov024_02086800 -- MobiClip: decode one IMA ADPCM block.
 * Standard IMA: `state[0]` is the running predictor (clamped to signed 16-bit), `state[1]` the
 * step index (clamped to 0..88 = the step table's 89 entries). Each source byte holds two
 * nibbles, low first; each nibble's bits 2/1/0 add step, step/2 and step/4 on top of the
 * step/8 bias and bit 3 negates. The two resulting samples are packed into one output word,
 * low half first. `count` is the byte count, so it yields 2*count samples. */
extern short       data_ov024_0209383c[];   /* IMA step table, 89 entries          */
extern signed char data_ov024_0209382c[];   /* IMA step-index adjust, 16 entries   */

void func_ov024_02086800(int *state, int src, int count, unsigned int *dst) {
    signed char *adjust = data_ov024_0209382c;
    short *steps = data_ov024_0209383c;
    int i = 0;
    int nibble;
    unsigned int idx;
    int newidx;
    unsigned int lo;
    signed char adj;
    int step;
    int diff;

    if (count <= 0) {
        return;
    }
    do {
        int code = *(unsigned char *)(src + i);
        idx = state[1];
        i = i + 1;

        newidx = (int)idx + adjust[code & 7];
        state[1] = newidx;
        if (newidx < 0) {
            newidx = 0;
            state[1] = newidx;
        }
        step = steps[idx];
        if (0x58 < state[1]) {
            state[1] = 0x58;
        }
        diff = step >> 3;
        if (code & 4) {
            diff = diff + step;
        }
        if (code & 2) {
            diff = diff + (step >> 1);
        }
        if (code & 1) {
            diff = diff + (step >> 2);
        }
        nibble = code >> 4;
        if (code & 8) {
            state[0] = state[0] - diff;
        } else {
            state[0] = state[0] + diff;
        }
        if (state[0] < -0x8000) {
            state[0] = -0x8000;
        }
        adj = adjust[nibble & 7];
        if (0x7fff < state[0]) {
            state[0] = 0x7fff;
        }
        lo = state[0];

        idx = state[1];
        newidx = (int)idx + adj;
        state[1] = newidx;
        if (newidx < 0) {
            newidx = 0;
            state[1] = newidx;
        }
        step = steps[idx];
        if (0x58 < state[1]) {
            state[1] = 0x58;
        }
        diff = step >> 3;
        if (nibble & 4) {
            diff = diff + step;
        }
        if (nibble & 2) {
            diff = diff + (step >> 1);
        }
        if (nibble & 1) {
            diff = diff + (step >> 2);
        }
        if (nibble & 8) {
            state[0] = state[0] - diff;
        } else {
            state[0] = state[0] + diff;
        }
        if (state[0] < -0x8000) {
            state[0] = -0x8000;
        }
        if (0x7fff < state[0]) {
            state[0] = 0x7fff;
        }

        *dst = state[0] << 0x10 | (lo << 0x10) >> 0x10;
        dst = dst + 1;
    } while (i < count);
}
