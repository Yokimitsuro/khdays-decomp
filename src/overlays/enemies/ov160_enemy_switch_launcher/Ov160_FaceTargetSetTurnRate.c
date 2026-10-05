/*
 * Ov160_FaceTargetSetTurnRate -- x3. AI-state tick: face the acquired target, set the aim rate, dispatch.
 * target = acquire(*state, 0) -> state[2]. If none, mark *state[0]+0x1c7 = 2 and bail. Else set flags
 * (*(u16)(state[0]+0x1b0) |= 0xc, later *(u16)(state[0]+0x1ae) |= 8), face the target:
 * dir = normalise(flatten_y(target(+0x190) - state[0x13])); state[4] = atan2(dir.x, dir.z). Set the
 * turn rate state[5] = owner_delta * 30 / 5, then hand off to the 020cd7e8 state.
 */
extern int  Ov107_FindNearestObject(int obj, int flag);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void VEC_Normalize(void *a, void *b);
extern short  FX_Atan2(int x, int z);
extern void Ov160_ArmMovePhase2(void);

void Ov160_FaceTargetSetTurnRate(int *self) {
    int *state = (int *)self[1];
    int target;
    int v[3];

    target = Ov107_FindNearestObject(*state, 0);
    state[2] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    *(unsigned short *)(*state + 0x1b0) |= 0xc;
    VEC_Subtract((void *)(state[2] + 0x190), (void *)state[0x13], v);
    v[1] = 0;
    VEC_Normalize(v, v);
    state[4] = FX_Atan2(v[0], v[2]);
    *(unsigned short *)(*state + 0x1ae) |= 8;
    state[5] = *(int *)(*self + 0x2c) * 0x1e / 5;
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov160_ArmMovePhase2);
}
