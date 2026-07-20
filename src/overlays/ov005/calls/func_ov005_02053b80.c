/* Scene entry for ov005's big context: 0x62198 bytes (401,816), measured off the
 * MI_CpuFill8 rather than inferred from the fields.
 *
 * Carries the saved mode byte over from the config block at
 * data_ov005_0205b85c+0x5c -- the same block func_ov005_020515dc reads its
 * nOption64 from, which is why both files declare the one Ov005Config type.
 *
 * The closing `llStartTick = func_020031d4()` is a single 64-bit store: the ROM
 * splits it into two str because GetTick64 returns the pair in r0:r1, and the
 * pool load for the return value is scheduled between them.
 *
 * The global is re-read at every use instead of being cached in a local -- that
 * is what the ROM does and caching it costs the match. */
typedef struct {
    char pad00[0x4bf4];
    long long llStartTick;      /* +0x4bf4 */
    char pad4bfc[0x94];
    int nUnk4c90;               /* +0x4c90 */
    char pad4c94[0x5d4e4];
    unsigned char bMode;        /* +0x62178 */
    char pad62179[0xf];
    int aSub62188[1];           /* +0x62188 */
} Ov005Context;

typedef struct {
    char pad00[0x5c];
    unsigned char bMode;    /* +0x5c */
    char pad5d[7];
    int nOption64;          /* +0x64 */
} Ov005Config;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, unsigned char value, unsigned int size);
extern void func_ov005_0205b0a0(int *sub, int *out);
extern void func_ov005_02052ba8(void);
extern void func_ov005_020528c0(void);
extern void func_ov005_02051f78(void);
extern void func_ov005_02052738(void);
extern void func_ov005_020531cc(void);
extern void func_ov005_02052ca4(void);
extern void func_ov005_02052fe0(void);
extern void func_ov005_020532d0(int *p);
extern void func_ov005_0205234c(int a);
extern void func_ov005_020523f8(int a);
extern long long func_020031d4(void);
extern void func_ov005_02053d74(void);

extern Ov005Context *data_ov005_0205b80c;
extern Ov005Config data_ov005_0205b85c;

void *func_ov005_02053b80(void) {
    int out[2] = { 0, 0 };

    data_ov005_0205b80c = NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(data_ov005_0205b80c, 0, 0x62198);
    data_ov005_0205b80c->bMode = data_ov005_0205b85c.bMode;
    func_ov005_0205b0a0(data_ov005_0205b80c->aSub62188, out);
    func_ov005_02052ba8();
    func_ov005_020528c0();
    func_ov005_02051f78();
    func_ov005_02052738();
    func_ov005_020531cc();
    func_ov005_02052ca4();
    func_ov005_02052fe0();
    func_ov005_020532d0(&data_ov005_0205b80c->nUnk4c90);
    func_ov005_0205234c(0);
    func_ov005_0205234c(1);
    func_ov005_020523f8(2);
    data_ov005_0205b80c->llStartTick = func_020031d4();
    return (void *)&func_ov005_02053d74;
}
