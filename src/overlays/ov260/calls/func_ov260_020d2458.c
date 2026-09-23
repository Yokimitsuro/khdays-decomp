/* Constructor tail of an ov260 helper: installs its handlers (+8 020d2510, +0xc veneer 020d252c,
 * +0x30 020d25e0, +0x1dc 020d2538), sets bits 1-3 and 6 of the +0x60 high byte and bits 2 and 4 of
 * +0x1ae, +0x70 = 0x800, +0x64 rests at the origin, +0x54 / +0x58 clear, and its model (+0x384)
 * loads from the +0x38c owner's kit entry 0x31 and registers with the +0x9c scene. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020c9440(char *self, int kind);
extern int func_0203b898(int item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_ov260_020d2510(void);
extern void WM_EndKeySharing_0x020d252c(void);
extern void func_ov260_020d25e0(void);
extern void func_ov260_020d2538(void);
extern const Vec3 data_02041dc8;

void func_ov260_020d2458(char *self)
{
    char *owner = *(char **)(self + 0x38c);

    *(void **)(self + 8) = func_ov260_020d2510;
    *(void **)(self + 0xc) = WM_EndKeySharing_0x020d252c;
    *(void **)(self + 0x30) = func_ov260_020d25e0;
    *(void **)(self + 0x1dc) = func_ov260_020d2538;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 0x14;
    *(int *)(self + 0x70) = 0x800;
    *(Vec3 *)(self + 0x64) = data_02041dc8;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, 0x31));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
}
