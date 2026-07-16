/* func_ov275_020d3d88 -- reset the tuning, quiesce the owner and queue the effect, then hand on.
 * The constants at data_02041dc8 are copied into +0x14 unconditionally. Nothing further happens
 * while the gate byte at *(+0xc) is set.
 * Otherwise the owner is quiesced (mode 3), the progress fields (+0x24/+0x52) cleared, and a
 * 4-byte descriptor is queued through func_02031384 -- built from data_ov275_020d600c's +4/+6,
 * except the low half is then overwritten with the owner's own id (+2), so only the high half of
 * the global actually survives. Finally the caller's action (+0x20) is dispatched through
 * func_0203c634 with func_ov275_020d3e20 as the continuation. */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    unsigned short lo;
    unsigned short hi;
} Ov206_EffectDesc;

extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_02031384(int a, Ov206_EffectDesc *desc, int n, int v);
extern void func_0203c634(int self, int action, void (*cb)(void));
extern void func_ov275_020d3e20(void);
extern Vec3 data_02041dc8;
extern unsigned short data_ov275_020d600c[];

void func_ov275_020d3d88(int self) {
    int *ctx;
    Ov206_EffectDesc desc;
    unsigned short id;

    ctx = *(int **)(self + 4);
    *(Vec3 *)((char *)ctx + 0x14) = data_02041dc8;
    if (**(unsigned char **)(ctx + 3) != 0) {
        return;
    }

    func_ov107_020c9264(ctx[0], 3, 0);
    ctx[9] = 0;
    *(unsigned char *)((char *)ctx + 0x52) = 0;

    desc.hi = data_ov275_020d600c[3];
    desc.lo = data_ov275_020d600c[2];
    id = *(unsigned short *)(ctx[0] + 2);
    desc.lo = id;
    func_02031384(1, &desc, 4, id);

    func_0203c634(self, *(signed char *)(self + 0x20), func_ov275_020d3e20);
}
