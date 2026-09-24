/* Ov263_ProbeGround -- cast from the owner's position along `dir` and return the Y of the scaled
 * hit direction (0 when nothing is hit or the world has no collision). With bRay a single ray
 * is cast; otherwise up to four spheres are tried from the owner's position nudged by +-0x189e
 * along its local Y, then X (rotated by the owner's yaw), stopping at the first hit.
 *
 * pos/off/out are block locals (that is what gives the ROM's stack slots and puts &off/&pos in
 * r5/r6), and `hit` / `i` are declared around `state` so world and the counter get sb/r8. */
typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

extern void *func_01fff920(void *pColl, VecFx32 *pFrom, VecFx32 *pDir);
extern void *func_01fff948(void *pColl, VecFx32 *pFrom, VecFx32 *pDir, int nFlags);
extern void  func_01ffd144(int nScale, VecFx32 *pIn, VecFx32 *pOut);
extern void  func_ov263_020d06bc(VecFx32 *pIn, int *node, VecFx32 *pOut);
extern void  VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *out);

int func_ov263_020d0750(int *node, VecFx32 *dir, int bRay)
{
    void *hit;
    int *state = (int *)node[1];
    signed char i;
    char *owner = *(char **)state;
    char *world = *(char **)(owner + 4);

    if (*(void **)(world + 0x7c) != 0) {
        if (bRay) {
            hit = func_01fff920(*(void **)(world + 0x7c), (VecFx32 *)(owner + 0x74), dir);
        } else {
            for (i = 0; i < 4; i++) {
                VecFx32 pos = *(VecFx32 *)(*(char **)state + 0x74);
                VecFx32 off = {0, 0, 0};

                off.y += i == 0 ? 0x189e : (i == 1 ? -0x189e : 0);
                off.x += i == 2 ? 0x189e : (i == 3 ? -0x189e : 0);
                func_ov263_020d06bc(&off, node, &off);
                VEC_Add(&pos, &off, &pos);
                hit = func_01fff948(*(void **)(world + 0x7c), &pos, dir, 0);
                if (hit != 0) {
                    break;
                }
            }
        }
        if (hit != 0) {
            VecFx32 out;

            func_01ffd144(*(int *)((char *)hit + 0xc), dir, &out);
            return out.y;
        }
    }
    return 0;
}
