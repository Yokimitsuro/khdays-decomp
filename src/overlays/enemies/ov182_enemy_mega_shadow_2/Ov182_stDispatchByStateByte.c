/* State dispatcher: when an action is pending (+0x1c7 not -1) resets the per-action flags and the full
 * height scale (+0x394), makes it current (+0x1c6) and installs the step that starts that action; then marks
 * nothing pending. */

struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void Ov182_stateSetFlagsClearBitInit(void);
extern void Ov182_stateAcquireAimInit(void);
extern void Ov182_SpawnHook(void);
extern void Ov182_SetPose2ThenAdvanceSlot(void);
extern void Ov182_SetPose5ThenAdvanceSlot(void);
extern void Ov182_stateAnimAimAtTarget(void);
extern void Ov182_ConfigHw60FlagsBeginAction6(void);
extern void Ov182_ConfigSubStateThenAdvanceSlot(void);
extern void Ov182_BeginApproach(void);
extern void Ov182_stateAnimSetFlagClear(void);
extern void Ov182_stateAnimNegateClamp(void);
extern void Ov182_BeginState5AndClear(void);
extern void Ov182_AiSetStanceAndEnd(void);

void Ov182_stDispatchByStateByte(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c7) != -1) {
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 1;
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(int *)(*state + 0x394) = 0x1000;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            SetIndexedSlot(node, 1, Ov182_stateSetFlagsClearBitInit);
            break;
        case 1:
            SetIndexedSlot(node, 1, Ov182_stateAcquireAimInit);
            break;
        case 2:
            SetIndexedSlot(node, 1, Ov182_SpawnHook);
            break;
        case 4:
            SetIndexedSlot(node, 1, Ov182_SetPose2ThenAdvanceSlot);
            break;
        case 5:
            SetIndexedSlot(node, 1, Ov182_SetPose5ThenAdvanceSlot);
            break;
        case 6:
            SetIndexedSlot(node, 1, Ov182_stateAnimAimAtTarget);
            break;
        case 3:
            SetIndexedSlot(node, 1, Ov182_ConfigHw60FlagsBeginAction6);
            break;
        case 7:
            SetIndexedSlot(node, 1, Ov182_ConfigSubStateThenAdvanceSlot);
            break;
        case 8:
            SetIndexedSlot(node, 1, Ov182_BeginApproach);
            break;
        case 9:
            SetIndexedSlot(node, 1, Ov182_stateAnimSetFlagClear);
            break;
        case 0xa:
            SetIndexedSlot(node, 1, Ov182_stateAnimNegateClamp);
            break;
        case 0xb:
            SetIndexedSlot(node, 1, Ov182_BeginState5AndClear);
            break;
        case 0xc:
            SetIndexedSlot(node, 1, Ov182_AiSetStanceAndEnd);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}
