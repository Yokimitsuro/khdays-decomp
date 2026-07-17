/* Map the held item's kind to an animation id and play it (x5: ov259/260/283/297 + one
 * more). With nothing held (+0x140) there is nothing to do. The kind byte (+0x83) picks
 * an id in 0xe..0x1a; kind 3 asks ov002_0207298c which variant is active and picks 0x19
 * for variant 4, else 0x17. Kind 13 deliberately maps to nothing (the id stays -1 and the
 * play is skipped); everything unrecognised falls back to 0xe.
 *
 * The case order is the ROM's SOURCE order, recovered with tools/switchorder.py: the jump
 * table is indexed by value but the BODIES are laid out in source order, so sorting the
 * table's targets by address gives it directly. Note `default` sits in the middle (sharing
 * its body with cases 11 and 12) and the empty `case 13:` comes last -- that is not a
 * transcription artifact, it is what the layout says.
 *
 * `code = -1` must be a STATEMENT after the guard, not a declaration-initialiser: as an
 * initialiser mwcc hoists the `mvn r1, #0` above the early return, where the ROM emits it
 * after. Everything else was byte-exact on the first compile. */
extern int func_ov002_0207298c(void);
extern void func_ov107_020c5af8(int a, int b, int c, void *d);

void func_ov259_020cd2c8(int self, int param_2, int param_3, int param_4) {
    int code;
    int h = *(int *)(self + 0x140);

    if (h == 0) {
        return;
    }
    code = -1;
    switch (*(unsigned char *)(h + 0x83)) {
    case 0:  code = 0xe; break;
    case 1:  code = 0xf; break;
    case 4:  code = 0x10; break;
    case 9:  code = 0x11; break;
    case 7:  code = 0x12; break;
    case 8:  code = 0x13; break;
    case 2:  code = 0x14; break;
    case 5:  code = 0x15; break;
    case 6:  code = 0x16; break;
    case 3:  code = (short)(func_ov002_0207298c() == 4 ? 0x19 : 0x17); break;
    case 10: code = 0x18; break;
    case 14: code = 0x1a; break;
    case 11:
    case 12:
    default: code = 0xe; break;
    case 13: break;
    }
    if (code < 0) {
        return;
    }
    func_ov107_020c5af8(self, code, param_2, (void *)(self + 0xb0));
}
