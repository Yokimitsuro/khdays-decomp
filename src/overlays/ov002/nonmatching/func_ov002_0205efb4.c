/* NONMATCHING: semantically complete, coloring+scheduling tie. Body/logic byte-exact after
 * fixing the u16 flags read (ldrh), the inverted flags guard (predicated else), the reused
 * result/entry register, and the two draw calls; residue is ctx->r5/result->r4 where the ROM
 * uses ctx->r4/result->r5, plus one scheduling instruction. No decl order flips it.
 * (See git log for the full behaviour.) */

typedef void (*Callback)(void);

extern int *data_ov002_0207f624;
extern unsigned short data_0204c190;
extern void func_ov002_0205f084(void);
extern void func_ov002_020539f4(int object);
extern void func_ov002_0205ed24(void);
extern int func_02023c40(void);
extern int func_02023c50(void);
extern int func_ov002_0205e9e8(void);
extern void func_ov002_0205eaf0(void);
extern void func_ov002_0205eba4(int a);
extern int func_ov002_020536bc(int tag);
extern void func_ov002_0205376c(int entry, int a);
extern void func_ov002_020536dc(int entry, int armed);
extern void func_ov002_0205ec50(int a);
extern void func_020300f8(int object);

void *func_ov002_0205efb4(void) {
    int *ctx = data_ov002_0207f624;
    int result = 0;

    func_ov002_020539f4(ctx[0x1a7]);
    if ((data_0204c190 & 0x83) != 0) {
        func_ov002_0205ed24();
    } else {
        if (func_02023c40() != 2 || (func_02023c50() & 1) == 0) {
            if (func_ov002_0205e9e8() == 0) {
                if (ctx[0x1f8] < 1) {
                    func_ov002_0205ec50(1);
                } else {
                    func_ov002_0205eaf0();
                    func_ov002_0205eba4(ctx[0x1f7]);
                    result = func_ov002_020536bc(0xd);
                    func_ov002_0205376c(result, ctx[0x1a7]);
                    func_ov002_020536dc(result, 1);
                }
                result = (int)func_ov002_0205f084;
                *ctx = 4;
            }
            func_020300f8((int)(ctx + 0x1be));
        }
    }
    func_ov002_020539f4(ctx[0x1a8]);
    return (void *)result;
}
