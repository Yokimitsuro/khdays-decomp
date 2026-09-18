/* Facing update of the ov261 enemy (and its byte-identical twin): builds the +0x1c anchor
 * quaternion from the direction from the position to the target point (the shared forward
 * vector when degenerate), with its vertical component clamped to [-0x800, 0x800] and
 * renormalised, through the zero-origin look-at matrix. */
struct Vecx32 { int x, y, z; };

extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_0203cd7c(int *out, struct Vecx32 *dir, const struct Vecx32 *origin, const struct Vecx32 *up);
extern void func_0202ea48(int *quat, int *mtx);
extern const struct Vecx32 data_02042258;
extern const struct Vecx32 data_02041dc8;
extern const struct Vecx32 data_02042264;

void func_ov261_020d0348(int *anchor, struct Vecx32 *target, struct Vecx32 *pos)
{
    int mtx[9];
    struct Vecx32 dir;
    int y;

    VEC_Subtract(target, pos, &dir);
    if (func_01ff8d18(&dir, &dir) == 0) {
        dir = data_02042258;
    }
    y = dir.y;
    if (y > 0x800) {
        y = 0x800;
    } else if (y < -0x800) {
        y = -0x800;
    }
    dir.y = y;
    func_01ff8d18(&dir, &dir);
    func_0203cd7c(mtx, &dir, &data_02041dc8, &data_02042264);
    func_0202ea48(anchor, mtx);
}
