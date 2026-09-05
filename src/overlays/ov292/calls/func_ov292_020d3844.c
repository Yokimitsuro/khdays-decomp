/* ov292 actor constructor: install the nine handler entries, set the bounding
 * box, seed the placement and open the sub-item.
 *
 * Same family as the matched ov189 and ov187 constructors and written in their
 * idioms: the six words at +0x1fc are a bounding box -- a pair of Vec3 holding
 * the minimum and the maximum, here a two-unit box standing on the ground --
 * the sub-item is created as func_0203b898(func_ov107_020c9440(...)) in one
 * expression, and the flag byte at +0x61 is raised with the family's explicit
 * insert rather than a bitfield, because a 16-bit bitfield would add a second
 * truncation the ROM does not have.
 *
 * Two things in here are load-bearing for the codegen. The zero vector must be
 * const: only then may the compiler hoist its three-word load above the store
 * to the flag halfword, which is what makes the function need a third
 * callee-saved register and gives the ROM's push list. And the box has to be
 * filled before the handler entries go in, exactly as the ov189 sibling does
 * it; filled afterwards the whole prologue schedules one slot late.
 */
struct Vec3 { int x, y, z; };
struct Placement { struct Vec3 vec; int scale; };
struct Box { struct Vec3 min, max; };

extern const struct Vec3 data_02041dc8;
extern unsigned short data_ov292_020d48cc[];

extern void func_ov292_020d3a90(void);
extern void WM_EndKeySharing_ov292_0x020d3ab4(void);
extern void WM_EndKeySharing_ov292_0x020d3ac0(void);
extern void func_ov292_020d3bdc(void);
extern void func_ov292_020d3afc(void);
extern void func_ov292_020d3b64(void);
extern void func_ov292_020d3c38(void);
extern void func_ov292_020d3acc(void);
extern void func_ov292_020d3dd0(void);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern void func_0203ca14();
extern void *func_0203bee8();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern int func_ov107_020c319c();
extern void func_0203355c();
extern void func_01fffc24();

void func_ov292_020d3844(char *self)
{
    struct Vec3 zero;
    struct Box box;
    struct Placement place;

    box.min.x = -0x2000;
    box.min.y = 0;
    box.min.z = -0x2000;
    box.max.x = 0x2000;
    box.max.y = 0x2000;
    box.max.z = 0x2000;
    *(void **)(self + 0x08) = func_ov292_020d3a90;
    *(void **)(self + 0x0c) = WM_EndKeySharing_ov292_0x020d3ab4;
    *(void **)(self + 0x1c) = WM_EndKeySharing_ov292_0x020d3ac0;
    *(void **)(self + 0x30) = func_ov292_020d3bdc;
    *(void **)(self + 0x34) = func_ov292_020d3afc;
    *(void **)(self + 0x38) = func_ov292_020d3b64;
    *(void **)(self + 0x1d0) = func_ov292_020d3c38;
    *(void **)(self + 0x1dc) = func_ov292_020d3acc;
    *(void **)(self + 0x1e0) = func_ov292_020d3dd0;

    *(struct Box *)(self + 0x1fc) = box;
    *(unsigned short *)(self + 0x1ae) |= 8;
    {
        unsigned short *p = (unsigned short *)(self + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    *(int *)(self + 0x70) = 0x1800;
    zero = data_02041dc8;
    *(struct Vec3 *)(self + 0x64) = zero;

    *(void **)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(void **)(self + 0x384));
    func_0203ca14(*(int *)(self + 0x384) + 4, 0, -0x1800, 0);
    *(void **)(self + 0x38c) =
        func_0203bee8(*(int *)(self + 0x384), 1, data_ov292_020d48cc);

    func_ov107_020c92b0(self, 0, 1, 0, 0x6000);
    func_ov107_020c92b0(self, 2, 1, 0, 0x6000);
    func_ov107_020c92b0(self, 1, 1, 0, 0x6000);
    func_ov107_020c92b0(self, 4, 1, 0, 0x6000);

    place = *(struct Placement *)(self + 0x64);
    place.vec = zero;

    *(void **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c(&place);
    {
        int *slot = func_01fffca8(self + 0x144, 4, 100);
        int handle = func_ov107_020c319c(&place);
        *slot = handle;
        *(int *)(self + 0x390) = handle;
    }
    func_0203355c(0x175);
    func_01fffc24(self + 0x394);
}
