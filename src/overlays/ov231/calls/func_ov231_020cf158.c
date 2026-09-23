/* Construction of the ov231 enemy's item: installs the handlers (+8
 * 020d2ef0, +0x30 020d2f44, +0x1d0 020d2f0c), raises flags 0x42 in the +0x60 high byte and bit 2
 * of +0x1ae, scales the +0x70 size to 0.58 of the +0x388 owner's and clears +0x54/+0x58. The
 * +0x384 sub-item is built from pose 0x14 of the owner, the +0xa0 pose is scaled by 1.3, the
 * sub-item is subscribed to +0x9c, uniformly scaled by 1.0 (0x1119/0x1119), its channels 0 and 2 are
 * enabled and it is reset. */
typedef unsigned short u16;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern int FX_Inv(int num, int den);
extern int func_ov107_020c9440(int pool, int kind);
extern int func_0203b898(int res);
extern void func_0203ca9c(void *srt, int weight);
extern void func_0203bfb4(int list, int obj);
extern void func_0203ca50(void *scale, int x, int y, int z);
extern void func_0203b9fc(int obj, int channel, int a, int b);
extern void func_0203c7ac(int obj, int v);
extern void func_ov231_020cf288(void);
extern void func_ov231_020cf2dc(void);
extern void func_ov231_020cf2a4(void);

void func_ov231_020cf158(char *self)
{
    int owner = *(int *)(self + 0x388);
    int w = FX_Inv(0x1119, 0x1119);
    u16 v;

    *(void **)(self + 8) = (void *)func_ov231_020cf288;
    *(void **)(self + 0x30) = (void *)func_ov231_020cf2dc;
    *(void **)(self + 0x1d0) = (void *)func_ov231_020cf2a4;
    v = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (u16)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x42) << 0x18) >> 0x10));
    *(u16 *)(self + 0x1ae) |= 4;
    *(int *)(self + 0x70) = FX_MUL(*(int *)(*(int *)(self + 0x388) + 0x70), 0x943);
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, 0x14));
    func_0203ca9c(self + 0xa0, 0x14cd);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203ca50((void *)(*(int *)(self + 0x384) + 4), w, w, w);
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
}
