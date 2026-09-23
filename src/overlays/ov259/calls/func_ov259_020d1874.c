/* Constructor of an ov259 helper: installs its handlers (+8 update 020d1aa4, +0xc 020d1ad4, +0x1c
 * 020d1be0, +0x30 020d1c68, +0x34 020d1bec, +0x1d0 020d1c60), sets bits 1, 5 and 6 of the +0x60 high
 * byte and bits 3-4 of +0x1ae, +0x70 = 0x800, +0x64 rests at the origin, +0x54 / +0x58 / +0x398 clear.
 * Its body (+0x384) and shell (+0x388) models load from the owner's +0x394 kit (0x3c / 0x3e, or
 * 0x3d / 0x3f in the alternate costume, global 0204c240 bit 2); the owner's +0x410 takes the shell's
 * "tag00_1" node, both register with the +0x9c scene, the shell hides and the body shows at full
 * scale. A hit capsule (length 0x1a00, radius 0x400) goes into a +0x22c pool slot at +0x38c (bit 1
 * set) and a second one into a +0x144 slot, also kept at +0x390. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;

extern int func_ov107_020c9440(char *self, int kind);
extern int func_0203b898(int item);
extern int func_0203bee8(int item, int a, const char *name);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203ca9c(int srt, int scale);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern void *func_ov107_020c3210(const Capsule *capsule);
extern void func_ov259_020d1aa4(void);
extern void func_ov259_020d1ad4(void);
extern void WM_EndKeySharing_0x020d1be0(void);
extern void func_ov259_020d1c68(void);
extern void WM_EndKeySharing_0x020d1bec(void);
extern void func_ov259_020d1c60(void);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;
extern u8 data_0204c240;
extern char data_ov259_020d2fdc[];

void func_ov259_020d1874(char *self)
{
    char *owner = *(char **)(self + 0x394);
    Vec3 origin;
    Capsule cap;

    *(void **)(self + 8) = func_ov259_020d1aa4;
    *(void **)(self + 0xc) = func_ov259_020d1ad4;
    *(void **)(self + 0x1c) = WM_EndKeySharing_0x020d1be0;
    *(void **)(self + 0x30) = func_ov259_020d1c68;
    *(void **)(self + 0x34) = WM_EndKeySharing_0x020d1bec;
    *(void **)(self + 0x1d0) = func_ov259_020d1c60;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x62) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 8;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x1ae) |= 0x10;
    *(int *)(self + 0x70) = 0x800;
    origin = data_02041dc8;
    *(Vec3 *)(self + 0x64) = data_02041dc8;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(self + 0x398) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, (data_0204c240 & 4) ? 0x3d : 0x3c));
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(owner, (data_0204c240 & 4) ? 0x3f : 0x3e));
    *(int *)(*(char **)(self + 0x394) + 0x410) = func_0203bee8(*(int *)(self + 0x388), 3, data_ov259_020d2fdc);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    func_0203ca9c(*(int *)(self + 0x388) + 4, 0);
    func_0203ca9c(*(int *)(self + 0x384) + 4, 0x1000);
    cap.pos = origin;
    cap.axis = data_02042258;
    cap.length = 0x1a00;
    cap.radius = 0x400;
    *(int **)(self + 0x38c) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(void ***)(self + 0x38c) = func_ov107_020c3210(&cap);
    ((B8 *)(*(char **)(self + 0x38c) + 8))->f |= 2;
    {
        void **slot = (void **)func_01fffca8(self + 0x144, 4, 100);

        *(void **)(self + 0x390) = *slot = func_ov107_020c3210(&cap);
    }
}
