/* Piece lure of the ov144 enemy (and its byte-identical twin): in mission mode 1, with a
 * positive charge range, a +0x3ec piece and the +0x1f4 gate open, the piece's position raised
 * by 0x800 becomes the +0x18 goal and the +0xc target (reporting 1) when its flat distance from
 * the actor's +0x74 position is within the range. */
struct Vecx32 { int x, y, z; };

extern int func_ov002_0207690c(void);
extern int func_ov145_020ce618(int *state, int flag);
extern int func_ov014_0208064c(void);
extern struct Vecx32 *func_ov002_02076cc8(void *piece);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);

int func_ov145_020ce78c(int *state, int flag)
{
    struct Vecx32 dir;
    struct Vecx32 goal;
    int range;

    if (func_ov002_0207690c() == 1) {
        range = func_ov145_020ce618(state, flag);
        if (range <= 0) {
            return 0;
        }
        if (*(void **)(*state + 0x3ec) != 0 && func_ov014_0208064c() != 0) {
            goal = *func_ov002_02076cc8(*(void **)(*state + 0x3ec));
            goal.y += 0x800;
            VEC_Subtract(&goal, (void *)(*state + 0x74), &dir);
            dir.y = 0;
            if (func_01ff8d18(&dir, &dir) <= range) {
                *(struct Vecx32 *)(state + 6) = goal;
                *(struct Vecx32 *)(state + 3) = *(struct Vecx32 *)(state + 6);
                return 1;
            }
        }
    }
    return 0;
}
