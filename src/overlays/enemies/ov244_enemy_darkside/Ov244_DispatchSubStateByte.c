/* State dispatcher: when an action is pending (+0x1c7 not -1) resets the per-action flags and the full
 * height scale (+0x390), makes it current (+0x1c6) and installs the step that starts that action; then marks
 * nothing pending. */

struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void Ov244_SetVisFlagsEnterState(void);
extern void Ov244_AiTargetAndFace(void);
extern void Ov244_StartSidestep(void);
extern void Ov244_SetPose3ThenAdvanceSlot(void);
extern void Ov244_AiEnterSink(void);
extern void Ov244_BounceEntry(void);
extern void Ov244_AiEnterPursuit(void);
extern void Ov244_PoseSetAngleFieldsThenAdvance(void);
extern void Ov244_ConfigSubStateThenAdvanceSlot(void);
extern void Ov244_FaceTargetAndWindUp(void);
extern void Ov244_Action6Callback(void);
extern void Ov244_AiEnterSinkAndStay(void);
extern void Ov244_AiSetStanceAndEnd(void);

void Ov244_DispatchSubStateByte(int *node) {
    int *state = (int *)node[1];
    int c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~0x1;
        ((struct bf *)(*(int *)(*state + 0x388) + 8))->b |= 0x1;
        *(int *)(*state + 0x390) = 0x1000;
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            SetIndexedSlot(node, 1, Ov244_SetVisFlagsEnterState);
            break;
        case 1:
            SetIndexedSlot(node, 1, Ov244_AiTargetAndFace);
            break;
        case 2:
            SetIndexedSlot(node, 1, Ov244_StartSidestep);
            break;
        case 4:
            SetIndexedSlot(node, 1, Ov244_SetPose3ThenAdvanceSlot);
            break;
        case 6:
            SetIndexedSlot(node, 1, Ov244_AiEnterSink);
            break;
        case 7:
            SetIndexedSlot(node, 1, Ov244_BounceEntry);
            break;
        case 8:
            SetIndexedSlot(node, 1, Ov244_AiEnterPursuit);
            break;
        case 5:
            SetIndexedSlot(node, 1, Ov244_PoseSetAngleFieldsThenAdvance);
            break;
        case 9:
            SetIndexedSlot(node, 1, Ov244_ConfigSubStateThenAdvanceSlot);
            break;
        case 0xa:
            SetIndexedSlot(node, 1, Ov244_FaceTargetAndWindUp);
            break;
        case 3:
            SetIndexedSlot(node, 1, Ov244_Action6Callback);
            break;
        case 0xb:
            SetIndexedSlot(node, 1, Ov244_AiEnterSinkAndStay);
            break;
        case 0xc:
            SetIndexedSlot(node, 1, Ov244_AiSetStanceAndEnd);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}
