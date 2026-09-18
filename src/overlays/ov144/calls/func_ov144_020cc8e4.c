/* Line-of-sight test of the ov144 enemy (and its byte-identical twin): casts a 0x40 sphere from
 * the actor's +0x74 position towards the target point, stopping the margin short (at least one
 * unit), and reports 1 when nothing is in the way. */
struct Vecx32 { int x, y, z; };

extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_01ffa724(int scale, void *v, void *d);
extern void *func_01fff948(void *world, void *from, void *step, int radius);

int func_ov144_020cc8e4(int *state, struct Vecx32 target, int margin)
{
    struct Vecx32 step;
    struct Vecx32 pos;
    int scene;
    int len;

    scene = *(int *)(*state + 4);
    pos = *(struct Vecx32 *)(*state + 0x74);
    VEC_Subtract(&target, &pos, &step);
    len = func_01ff8d18(&step, &step) - margin;
    if (len <= 0) {
        len = 1;
    }
    func_01ffa724(len, &step, &step);
    if (func_01fff948(*(void **)(scene + 0x7c), &pos, &step, 0x40) != 0) {
        return 0;
    }
    return 1;
}
