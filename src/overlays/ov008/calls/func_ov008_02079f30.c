/* func_ov008_02079f30 -- push the current display config (mode 2) plus the live key
 * state to func_02031600. The scene object carries its key block at +0x42c: the raw key word
 * at +4 and its packed form at +8, which func_ov008_0207bc94 turns into the handler's key code.
 *
 * PROVENANCE: byte-identical twin of func_ov006_0204e0c4 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern int  func_ov008_0207bc94(short *keys);
extern void func_02031600(void *cfg);
extern int  data_ov008_02090f24;

struct Ov006KeyBlock {
    int f0;
    int raw;
    unsigned short packed;
};

struct Ov006DispCfg {
    int mode;
    int keycode;
    int rawkeys;
    unsigned short packed;
};

void func_ov008_02079f30(void) {
    struct Ov006DispCfg cfg;
    int *obj = *(int **)&data_ov008_02090f24;
    struct Ov006KeyBlock *kb = (struct Ov006KeyBlock *)((char *)obj + 0x42c);
    cfg.mode = 2;
    cfg.rawkeys = kb->raw;
    cfg.packed = kb->packed;
    cfg.keycode = func_ov008_0207bc94((short *)&kb->packed);
    func_02031600(&cfg);
}
