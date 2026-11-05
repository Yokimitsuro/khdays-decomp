/* Init state: clears the current and pending actions, clears bit 0 of the model's flag byte,
 * records pointers to the actor's velocity, position and model busy flag, sets the height scale
 * (+0x394) to its minimum and the initial flag bits, and installs the first action, the dispatcher and the heading
 * step. */

extern void SetIndexedSlot(int *self, int idx, void *cb);
extern void Ov181_stateSetFlagsClearBitInit(void);
extern void Ov181_stDispatchByStateByte(void);
extern void Ov181_AiApplyHeadingAndNormal(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned int f : 8; };

void Ov181_InitNodeAndRegisterHandlers(int *self) {
    int *s = (int *)self[1];
    int zero = 0;
    *(signed char *)(*s + 0x1c6) = zero;
    *(signed char *)(*s + 0x1c7) = zero - 1;
    ((struct b8 *)(*(int *)(*s + 0x388) + 8))->f &= ~1;
    s[1] = *s + 0xb0;
    s[2] = *s + 0x74;
    s[3] = *(int *)(*s + 0x384) + 0xad;
    *(int *)(*s + 0x394) = 1;
    ((struct hw60 *)(*s + 0x60))->hi |= (unsigned char)6;
    SetIndexedSlot(self, 1, (void *)&Ov181_stateSetFlagsClearBitInit);
    SetIndexedSlot(self, 0, (void *)&Ov181_stDispatchByStateByte);
    SetIndexedSlot(self, 2, (void *)&Ov181_AiApplyHeadingAndNormal);
}
