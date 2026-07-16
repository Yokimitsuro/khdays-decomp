/* func_ov005_0204dba0 -- per-frame update for a scene's widget layer.
 * Runs func_ov005_0204db58 first, then unless bit 2 of +0x4a6c suppresses it, re-projects the
 * anchor at +0x4a54 and feeds the Q12 result (>> 12) to func_020327e0.
 * Bit 0 of +0x4a7c enables the hit/selection pass (func_ov005_0204d770); if that found nothing
 * and bit 1 is set, func_ov005_0204d850 handles the fallback, otherwise the field at +0x4a78 is
 * parked at 0xf0 (off-screen).
 * Finally the layer is committed through func_0203256c or func_0203255c depending on `flag`. */

typedef struct {
    char pad[0x4a54];
    int f4a54;
    char pad2[0x4a6c - 0x4a58];
    unsigned int b4a6c_0 : 2;
    unsigned int b4a6c_2 : 1;
    unsigned int b4a6c_rest : 29;
    char pad3[0x4a78 - 0x4a70];
    unsigned short f4a78;
    unsigned short pad4;
    unsigned int b4a7c_0 : 1;
    unsigned int b4a7c_1 : 1;
    unsigned int b4a7c_rest : 30;
} Obj;

extern void func_ov005_0204db58(Obj *o);
extern void func_0203602c(int *anchor, int *out);
extern void func_020327e0(Obj *o, int v);
extern int func_ov005_0204d770(Obj *o);
extern void func_ov005_0204d850(Obj *o, int p);
extern void func_0203256c(Obj *o);
extern void func_0203255c(Obj *o);

void func_ov005_0204dba0(Obj *o, int p, int flag) {
    int v;
    int sel;

    sel = 0;
    v = 0;
    func_ov005_0204db58(o);
    if (!o->b4a6c_2) {
        func_0203602c(&o->f4a54, &v);
        func_020327e0(o, v >> 12);
    }
    if (o->b4a7c_0) {
        sel = func_ov005_0204d770(o);
    }
    if (sel == 0 && o->b4a7c_1) {
        func_ov005_0204d850(o, p);
    } else {
        o->f4a78 = 0xf0;
    }
    if (flag != 0) {
        func_0203256c(o);
    } else {
        func_0203255c(o);
    }
}
