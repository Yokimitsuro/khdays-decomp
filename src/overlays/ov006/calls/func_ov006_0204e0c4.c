/* func_ov006_0204e0c4 -- Mission Mode: push the current display config (mode 2) plus the live key
 * state to func_02031600. The scene object carries its key block at +0x42c: the raw key word
 * at +4 and its packed form at +8, which func_ov006_0204feb0 turns into the handler's key code. */
extern int  func_ov006_0204feb0(short *keys);
extern void func_02031600(void *cfg);
extern int  data_ov006_020565e4;

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

void func_ov006_0204e0c4(void) {
    struct Ov006DispCfg cfg;
    int *obj = *(int **)&data_ov006_020565e4;
    struct Ov006KeyBlock *kb = (struct Ov006KeyBlock *)((char *)obj + 0x42c);
    cfg.mode = 2;
    cfg.rawkeys = kb->raw;
    cfg.packed = kb->packed;
    cfg.keycode = func_ov006_0204feb0((short *)&kb->packed);
    func_02031600(&cfg);
}
