/* Advance the camera's held distance toward the selector's target and return it
 * with a fixed offset added.
 *
 * With the flag clear nothing moves. Otherwise the aim direction is compared
 * with the direction to the tracked point: a wide angle or a far point means
 * the view is clear and the held distance is pulled down by 0x80, never below
 * the selector's target. A narrow angle on a near point means the point may be
 * occluded, so up to twenty probes are taken and every failed round pushes the
 * wanted distance out by 0x200; the held distance then rises toward it by at
 * most 0x100, again clamped at the target.
 *
 * The two rate limits are nested clamp expressions rather than guarded ifs: as
 * an if with a body, mwcc predicates the load and compare instead of branching,
 * because the outer and inner tests share a condition code and merge. The loop
 * counter is declared immediately before the target so the two land in the
 * registers the ROM uses.
 */
extern char data_ov002_0207e764[];

extern int func_02023bf0(void);
extern void VEC_Subtract(const int *pA, const int *pB, int *pOut);
extern int func_01ff8d18(const int *pIn, int *pOut);
extern int VEC_DotProduct(const int *pA, const int *pB);
extern int func_ov002_0204e2e0(int *pOut, const int *pVec, int nA, int nB);

int func_ov002_02050b90(int nIndex) {
    int nProbe;
    int aAim[3];
    int aTo[3];
    int nOffset = nIndex * 0xc;
    int nCam = *(int *)(func_02023bf0() + 0x20);
    int i;
    int nTarget = *(int *)(data_ov002_0207e764 + nOffset);

    if ((*(unsigned int *)(nCam + 0x38) & 0x8000000) != 0) {
        int nLength;
        int nDot;

        VEC_Subtract((int *)(nCam + 0x14), (int *)(nCam + 0x20), aAim);
        func_01ff8d18(aAim, aAim);
        VEC_Subtract((int *)(nCam + 0x8c), (int *)(nCam + 0x20), aTo);
        nLength = func_01ff8d18(aTo, aTo);
        nDot = VEC_DotProduct(aAim, aTo);

        if (nDot > 0xa00 && nLength < 0x50000) {
            i = 0;

            do {
                if (func_ov002_0204e2e0(&nProbe, (int *)(nCam + 0x8c), 0, 0)
                        != 0 &&
                    func_ov002_0204e2e0(&nProbe, (int *)(nCam + 0x8c), 0x14,
                                        0x14) != 0) {
                    break;
                }
                i++;
                nTarget += 0x200;
            } while (i < 0x14);
        } else {
            int nCur = *(int *)(nCam + 0x98);
            int nStep = nCur - 0x80;

            nCur = (nCur < nStep)
                       ? nCur
                       : ((nStep < *(int *)(data_ov002_0207e764 + nOffset))
                              ? *(int *)(data_ov002_0207e764 + nOffset)
                              : nStep);
            *(int *)(nCam + 0x98) = nCur;
        }

        {
            int nCur = *(int *)(nCam + 0x98);

            if (nTarget - nCur > 0) {
                int nStep = nCur + 0x100;

                if (nStep <= nTarget) {
                    nTarget = *(int *)(data_ov002_0207e764 + nOffset);
                    if (nStep >= nTarget) {
                        nTarget = nStep;
                    }
                }
                *(int *)(nCam + 0x98) = nTarget;
            }
        }
        nTarget = *(int *)(nCam + 0x98);
    }
    return nTarget + 0xc00;
}
