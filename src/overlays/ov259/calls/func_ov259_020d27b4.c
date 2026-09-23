/* Constructor tail of an ov259 helper: installs its handlers (+8 update veneer 020d28c0, +0xc 020d28cc,
 * +0x30 020d29b0, +0x1d0 020d29a8), +0x70 = 0xa00, sets bits 2 and 4 of +0x1ae, drops bit 6 of the
 * +0x60 high byte and builds its hit capsule (rest axis, length -0x500, radius 0x700) into a
 * +0x22c pool slot at +0x384, marked with bit 1; +0x388 (busy) clears. */
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;

extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern void *func_ov107_020c3210(const Capsule *capsule);
extern void WM_EndKeySharing_0x020d28c0(void);
extern void func_ov259_020d28cc(void);
extern void func_ov259_020d29b0(void);
extern void func_ov259_020d29a8(void);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042240;

void func_ov259_020d27b4(char *self)
{
    Capsule cap;

    *(void **)(self + 8) = WM_EndKeySharing_0x020d28c0;
    *(void **)(self + 0xc) = func_ov259_020d28cc;
    *(void **)(self + 0x30) = func_ov259_020d29b0;
    *(void **)(self + 0x1d0) = func_ov259_020d29a8;
    *(int *)(self + 0x70) = 0xa00;
    *(unsigned short *)(self + 0x1ae) |= 0x14;
    {
        unsigned short hw = *(unsigned short *)(self + 0x60);
        *(unsigned short *)(self + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    cap.pos = data_02041dc8;
    cap.axis = data_02042240;
    cap.length = -0x500;
    cap.radius = 0x700;
    *(int **)(self + 0x384) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(void ***)(self + 0x384) = func_ov107_020c3210(&cap);
    ((B8 *)(*(char **)(self + 0x384) + 8))->f |= 2;
    *(int *)(self + 0x388) = 0;
}
