/* NONMATCHING: 216B vs 220B -- one instruction. The flags switch and the predicated engine
 * select now match the ROM instruction-for-instruction; only the +0x9400 placement differs.
 * The ROM computes the engine once (`add r0,r0,#0x3b8` then a separate `add r9,r0,#0x9400`)
 * and passes `mov r0,r9` at both call sites; mwcc folds 0x3b8 straight into r9 and SINKS the
 * +0x9400 into each call site instead (`add r0,r9,#0x9400` twice) -- one instruction fewer.
 * Note this is mwcc rematerialising where it usually shares, the inverse of the common
 * ctx-CSE tie. Not steerable: pointer-typed and int-typed forms both sink it.
 *
 * Two cracks DID land here and are worth reusing:
 *   - the flags select needed a `switch`, not `if/else if`: the ROM puts styles 1 and 2
 *     out-of-line with `b` and only predicates style 3 (the inverse of the ov000 0204ef34
 *     entry in codegen-cracks.md, which wanted if/else-if to inline the first arm)
 *   - the engine select needed the test flipped to `if (alt != 0)` so mwcc predicates the
 *     eq case and falls through to ne, matching the ROM
 *
 * func_ov006_020521a0 -- char select: draw one text run, optionally with a drop shadow.
 * `style` picks the draw flags: 1 -> 0x821, 2 -> 0x411, 3 -> 0x412, anything else -> 0x200.
 * `alt` selects the text engine: OBJ+0x36c when set, the default OBJ+0x3b8 otherwise (both
 * offset by 0x9400). The colour comes from func_ov006_02052090(colour, alt); the shadow is
 * the same run drawn one pixel down-right in colour 2 underneath. */
extern int  func_ov006_02052090(int colour, int alt);
extern void func_0202fa38(int engine, int x, int y, int colour, unsigned int flags, int text);
extern int *data_ov006_02056664;

void func_ov006_020521a0(int text, int x, int y, int colour, int shadow, int style, int alt) {
    unsigned int flags = 0x200;
    int engine;
    int fg;
    int sh;

    switch (style) {
    case 1:
        flags = 0x821;
        break;
    case 2:
        flags = 0x411;
        break;
    case 3:
        flags = 0x412;
        break;
    }

    if (alt != 0) {
        engine = (int)data_ov006_02056664 + 0x36c;
    } else {
        engine = (int)data_ov006_02056664 + 0x3b8;
    }
    engine = engine + 0x9400;

    fg = func_ov006_02052090(colour, alt);
    sh = func_ov006_02052090(2, alt);
    if (shadow != 0) {
        func_0202fa38(engine, x + 1, y + 1, sh, flags, text);
    }
    func_0202fa38(engine, x, y, fg, flags, text);
}
