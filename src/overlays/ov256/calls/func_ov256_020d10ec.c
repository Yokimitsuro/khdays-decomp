/* Constructor of an ov256 claw: installs its handlers (+8 020d12c0, +0xc update 020d12e4, +0x30
 * 020d1564, +0x1d0 020d1560), sets bits 1 and 6 of the +0x60 high byte, +0x70 = 0x800, +0x64 rests at
 * the origin, +0x54 / +0x58 clear. Its body (+0x384) loads from the +0x3ac owner's kit (0x4e left /
 * 0x4f right claw, +0x394) with +0x39c / +0x3a0 cleared, registers with the +0x9c scene and its +0x390
 * part is the owner's "move_buki_L/R" motion (0x47 / 0x48). A hit capsule (length 0x2a00, radius 0xa00)
 * goes into a +0x22c pool slot at +0x388 (bit 1 set), bit 3 of +0x1ae is set and a second capsule in a
 * +0x144 slot is also kept at +0x38c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;

extern int func_ov107_020c9440(char *self, int kind);
extern int func_0203b898(int item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_ov107_020c9e50(int item, char *name);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern void *func_ov107_020c3210(const Capsule *capsule);
extern void func_ov256_020d12c0(void);
extern void func_ov256_020d12e4(void);
extern void func_ov256_020d1564(void);
extern void func_ov256_020d1560(void);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;
extern char data_ov256_020d26d4[];
extern char data_ov256_020d26e0[];

void func_ov256_020d10ec(char *self)
{
    char *owner = *(char **)(self + 0x3ac);
    Vec3 origin;
    Capsule cap;

    *(void **)(self + 8) = func_ov256_020d12c0;
    *(void **)(self + 0xc) = func_ov256_020d12e4;
    *(void **)(self + 0x30) = func_ov256_020d1564;
    *(void **)(self + 0x1d0) = func_ov256_020d1560;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x42) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x70) = 0x800;
    origin = data_02041dc8;
    *(Vec3 *)(self + 0x64) = data_02041dc8;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    if (*(u8 *)(self + 0x394) == 0) {
        *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, 0x4e));
    } else {
        *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, 0x4f));
    }
    *(int *)(self + 0x39c) = 0;
    *(int *)(self + 0x3a0) = 0;
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    if (*(u8 *)(self + 0x394) == 0) {
        *(int *)(self + 0x390) = func_ov107_020c9e50(func_ov107_020c9440(owner, 0x47), data_ov256_020d26d4);
    } else {
        *(int *)(self + 0x390) = func_ov107_020c9e50(func_ov107_020c9440(owner, 0x48), data_ov256_020d26e0);
    }
    cap.pos = origin;
    cap.axis = data_02042258;
    cap.length = 0x2a00;
    cap.radius = 0xa00;
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(void ***)(self + 0x388) = func_ov107_020c3210(&cap);
    ((B8 *)(*(char **)(self + 0x388) + 8))->f |= 2;
    *(u16 *)(self + 0x1ae) |= 8;
    {
        void **slot = (void **)func_01fffca8(self + 0x144, 4, 100);

        *(void **)(self + 0x38c) = *slot = func_ov107_020c3210(&cap);
    }
}
