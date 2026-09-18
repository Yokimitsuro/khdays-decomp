/* Target finder of the ov191 enemy (x3: ov191/192/193). Walks the owner's +0xa8 actor list
 * for live (+0x40 bit 1), enabled (+0x60 bit 0) actors and returns one with, through `out`,
 * the surface distance (squared distance between the +0x74 positions minus both +0x80 radii
 * squared, floored at zero). Without bit 2 of the 0204c240 flags the first candidate not marked
 * at +0x1b4 wins; with it the nearest of all candidates does. */
typedef struct { int x, y, z; } Vec3;
struct flags40 { int bit0 : 1, bit1 : 1; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern unsigned char data_0204c240;
extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);

int func_ov193_020d581c(int self, int *out)
{
    int best = 0;
    int bestDist = 0x7fffffff;
    int owner = *(int *)(self + 4);
    int *pNode;
    int actor;
    Vec3 dNear;
    Vec3 dAll;
    long long distSq;
    long long radSq;
    int dist;

    if ((data_0204c240 & 4) == 0) {
        pNode = func_01fffd70((void *)(owner + 0xa8));
        actor = pNode == 0 ? 0 : *pNode;
        while (actor != 0) {
            if (((struct flags40 *)(actor + 0x40))->bit1 && (((struct hw60 *)(actor + 0x60))->lo & 1) != 0
                && *(unsigned char *)(actor + 0x1b4) == 0) {
                VEC_Subtract((Vec3 *)(actor + 0x74), (Vec3 *)(self + 0x74), &dNear);
                distSq = (long long)dNear.x * dNear.x + (long long)dNear.y * dNear.y
                       + (long long)dNear.z * dNear.z;
                radSq = (long long)*(int *)(self + 0x80) * *(int *)(self + 0x80)
                      + (long long)*(int *)(actor + 0x80) * *(int *)(actor + 0x80);
                bestDist = (int)((distSq + 0x800) >> 12) - (int)((radSq + 0x800) >> 12);
                if (bestDist < 0) {
                    bestDist = 0;
                }
                best = actor;
                break;
            }
            pNode = func_01fffd8c((void *)(owner + 0xa8));
            actor = pNode == 0 ? 0 : *pNode;
        }
    } else {
        pNode = func_01fffd70((void *)(owner + 0xa8));
        actor = pNode == 0 ? 0 : *pNode;
        while (actor != 0) {
            if (((struct flags40 *)(actor + 0x40))->bit1 && (((struct hw60 *)(actor + 0x60))->lo & 1) != 0) {
                VEC_Subtract((Vec3 *)(actor + 0x74), (Vec3 *)(self + 0x74), &dAll);
                distSq = (long long)dAll.x * dAll.x + (long long)dAll.y * dAll.y
                       + (long long)dAll.z * dAll.z;
                radSq = (long long)*(int *)(self + 0x80) * *(int *)(self + 0x80)
                      + (long long)*(int *)(actor + 0x80) * *(int *)(actor + 0x80);
                dist = (int)((distSq + 0x800) >> 12) - (int)((radSq + 0x800) >> 12);
                if (dist < 0) {
                    dist = 0;
                }
                if (dist < bestDist) {
                    bestDist = dist;
                    best = actor;
                }
            }
            pNode = func_01fffd8c((void *)(owner + 0xa8));
            actor = pNode == 0 ? 0 : *pNode;
        }
    }
    if (best != 0 && out != 0) {
        *out = bestDist;
    }
    return best;
}
