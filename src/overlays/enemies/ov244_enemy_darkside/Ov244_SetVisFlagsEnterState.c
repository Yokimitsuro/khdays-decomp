/* State step: sets the visibility bits in the high byte of the actor's flags (+0x60), clears bit 0
 * of its model's flag byte, sets the height scale (+0x390) to its minimum and installs the resume-stored-action
 * step. */

extern void SetIndexedSlot(void *node, int idx, void *cb);
extern void Ov244_AiStep_ResumeStoredAction(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct LowByteFlags { unsigned bits : 8; };

void Ov244_SetVisFlagsEnterState(int *node) {
    int *state = (int *)node[1];
    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0xce) << 0x18) >> 0x10);
    }
    ((struct LowByteFlags *)(*(int *)(*state + 0x388) + 8))->bits &= ~1;
    *(int *)(*state + 0x390) = 1;
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov244_AiStep_ResumeStoredAction);
}
