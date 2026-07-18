/*
 * NON-MATCHING: size-exact (360B). The message-0 facing-bit RMW, the kind-5 jump-table switch, the
 * case-2/3 rig copy + transform + VEC_Add + 0203ca30 + spawn all match; the residual is the case-0/1
 * spawn-argument setup -- the ROM interleaves the `self+msg[3]*8` slot index between the ternary base
 * loads and colours base->r0, mwcc colours base->r2 and schedules the sp-arg stores differently. The
 * recurring message-handler spawn-setup scheduling tie (see deferred-ties.md). Result identical.
 */
/*
 * func_ov208_020d39d8 -- x3 (ov208/...). Message 0 sets a facing bit; message 5 spawns a reaction node.
 * On message 0 (and unless *(self+0x50)==1) copy bit 0 of the payload byte msg[0x24] into bit 1 of
 * *(*(self+0x384)+0x5c). On message 5, dispatch on msg[3]: sub-kinds 0/1 spawn straight from the anchor
 * (*(self+0x38c) or +0x390) via 020c09a0; sub-kinds 2/3 build a launch offset -- copy the source rig
 * *(self+0x394)+0xa0, drop {0,0,0x2000} through the temp matrix (0202f384), offset it (VEC_Add), apply
 * (0203ca30), and spawn from it via 020c0794. The spawned handle is stored at *(self+msg[3]*8+0x39c).
 * Always forward the message (020c7500).
 */
struct blk11 { int w[11]; };

extern int func_ov107_020c09a0(int scene, int slot, int kind, int owner, int a, int b);
extern void func_0202f384(int *out, int *in, int *m);
extern void VEC_Add(int *a, int *b, int *out);
extern void func_0203ca30(int *dst, int *v);
extern int func_ov107_020c0794(int scene, int slot, int kind, int flag, int *m);
extern void func_ov107_020c7500(int self, unsigned char *msg, int arg);

void func_ov208_020d39d8(int self, unsigned char *msg, int arg) {
    if (msg[2] == 0) {
        if (*(int *)(self + 0x50) != 1) {
            int m = *(int *)(self + 0x384);
            *(int *)(m + 0x5c) = (*(int *)(m + 0x5c) & ~2) |
                                 (((unsigned)msg[0x24] << 0x1f) >> 0x1e);
        }
    } else if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
        case 1: {
            int base = (msg[3] == 0) ? *(int *)(self + 0x38c) : *(int *)(self + 0x390);
            *(int *)(self + msg[3] * 8 + 0x39c) =
                func_ov107_020c09a0(*(int *)(self + 0x3c), *(int *)(self + msg[3] * 8 + 0x398),
                                    0x17, base + 4, 0, 1);
            break;
        }
        case 2:
        case 3: {
            struct blk11 m;
            int v[3];
            m = *(struct blk11 *)(*(int *)(self + 0x394) + 0xa0);
            v[0] = 0;
            v[1] = 0;
            v[2] = 0x2000;
            func_0202f384(v, (int *)&m, v);
            VEC_Add(v, &m.w[4], v);
            func_0203ca30((int *)&m, v);
            *(int *)(self + msg[3] * 8 + 0x39c) =
                func_ov107_020c0794(*(int *)(self + 0x3c), *(int *)(self + msg[3] * 8 + 0x398),
                                    0x17, 0, (int *)&m);
            break;
        }
        default:
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
