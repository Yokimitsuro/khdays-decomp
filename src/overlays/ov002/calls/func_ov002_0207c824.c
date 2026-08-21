typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern int FX_Sqrt(int n);

/* Is a point within range of a box built around a centre?
 *
 * The box is the centre widened by the extent vector, the distance measured is
 * the per axis overshoot of the point outside it, and a point inside the box is
 * in range whatever the radius.
 *
 * The extent components are NOT used one per axis: the low side takes x, x, y
 * and the high side takes y, z, z. That is what the original does and it is
 * reproduced here rather than corrected.
 */
int func_ov002_0207c824(const Vec3 *pCentre, const Vec3 *pExtent,
                        const Vec3 *pPoint, int nRange)
{
    int aMin[3];
    int aMax[3];
    int aPoint[3];
    int aOver[3];
    int nCount;
    int i;
    int nSum;

    aMin[0] = pCentre->x - pExtent->x;
    aMin[1] = pCentre->y - pExtent->x;
    aMin[2] = pCentre->z - pExtent->y;
    aMax[0] = pCentre->x + pExtent->y;
    aMax[1] = pCentre->y + pExtent->z;
    aMax[2] = pCentre->z + pExtent->z;
    aPoint[0] = pPoint->x;
    aPoint[1] = pPoint->y;
    aPoint[2] = pPoint->z;

    nCount = 0;
    nSum = 0;
    for (i = 0; i < 3; i++) {
        if (aMin[i] > aPoint[i]) {
            aOver[nCount] = aMin[i] - aPoint[i];
            nCount++;
        } else if (aMax[i] < aPoint[i]) {
            aOver[nCount] = aPoint[i] - aMax[i];
            nCount++;
        }
    }

    if (nCount == 0) {
        return 1;
    }

    while (nCount > 0) {
        nCount--;
        nSum += (int)(((long long)aOver[nCount] * aOver[nCount] + 0x800) >> 12);
    }

    return nRange >= FX_Sqrt(nSum);
}
