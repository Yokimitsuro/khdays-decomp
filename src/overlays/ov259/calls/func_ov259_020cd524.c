/* Mirror a pose on the ov259 actor's +0x414 partner: the 27-entry pose -> partner motion map
 * (data_ov259_020d2f90, -1 = none) picks the motion, played with the caller's mode. */
typedef struct { signed char motion[27]; } PartnerMotionMap;

extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern const PartnerMotionMap data_ov259_020d2f90;

void func_ov259_020cd524(int *node, int pose, int mode)
{
    int *state = (int *)node[1];
    PartnerMotionMap map = data_ov259_020d2f90;

    if (map.motion[pose] < 0) {
        return;
    }
    func_ov107_020c9ee8(*(int *)(*state + 0x414), map.motion[pose], mode);
}
