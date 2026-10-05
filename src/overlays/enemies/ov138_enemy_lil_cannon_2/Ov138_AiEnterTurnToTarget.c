/* Set anim 5; if the target object (+0x48) exists, aim toward it via VEC_Subtract
 * + FX_Atan2 and store the angle at +0x10/+0xc; then dispatch. */
extern void Ov107_PostTagUpdate(int a, int b, int c);
extern void VEC_Subtract(const void *a, const void *b, void *out);
extern short FX_Atan2(int a, int b);
extern int SetIndexedSlot(int a, int b, void *handler);
extern void Ov138_AiDecelUntilAnimEnd(void);
void Ov138_AiEnterTurnToTarget(int param_1) {
    int child = *(int *)(param_1 + 4);
    Ov107_PostTagUpdate(*(int *)child, 5, 0);
    {
        int target = *(int *)(child + 0x48);
        if (target != 0) {
            int diff[3];
            VEC_Subtract((const void *)(target + 0x190), (const void *)(*(int *)child + 0xb0), diff);
            int r = FX_Atan2(diff[0], diff[2]);
            *(int *)(child + 0x10) = r;
            *(int *)(child + 0xc) = r;
        }
    }
    SetIndexedSlot(param_1, *(signed char *)(param_1 + 0x20), (void *)&Ov138_AiDecelUntilAnimEnd);
}
