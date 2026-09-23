/* Lay out the ov106 scene's +0x8bc4 widget: it is placed on the loaded +0x8b48 resource's second half
 * (texture word) at data_ov106_020b8a6c (depth 5.0x, style 5), enabled, given full alpha, bound to its
 * +0xe0 child on layer 4 and refreshed. */
typedef struct { int x, y, z; } Vec3;

extern char *data_ov106_020b8b60;
extern const Vec3 data_ov106_020b8a6c;
extern void func_ov106_020b7758(void *self, unsigned int owner, const Vec3 *pos, int depth, int style);
extern void func_0202afc4(void *pWidget, int nValue);
extern void func_0202afdc(void *pWidget, int nValue);
extern void func_0202accc(void *a, int b, void *c, int d);
extern void func_0202af1c(void *node);

void func_ov106_020b782c(void)
{
    Vec3 pos = data_ov106_020b8a6c;

    func_ov106_020b7758(data_ov106_020b8b60 + 0x8bc4,
                        (((*(int *)(data_ov106_020b8b60 + 0x8b48) + 0x8000) & 0xfffffc) << 7) | 0x80000002,
                        &pos, 0xa000, 5);
    func_0202afc4(data_ov106_020b8b60 + 0x8bc4, 1);
    func_0202afdc(data_ov106_020b8b60 + 0x8bc4, 0x7fff);
    func_0202accc(data_ov106_020b8b60 + 0x8bc4, 4, (void *)((int)(data_ov106_020b8b60 + 0x8bc4) + 0xe0), 0);
    func_0202af1c(data_ov106_020b8b60 + 0x8bc4);
}
