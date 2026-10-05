/* Face the target on entry: clear the pause flag (+0xac), and if a target is set (node[3]) compute
 * the heading to it (atan2 of the flattened owner->target vector) into node[0x1f]/[0x1e]; then
 * register the think callback. */
extern void VEC_Subtract(void *a, void *b, void *d);
extern short FX_Atan2(int x, int z);
extern void SetIndexedSlot(int self, int idx, void *cb);
extern void Ov259_EnterLunge(void);

void Ov259_FaceTargetOnEntry(int param_1) {
    int *node = *(int **)(param_1 + 4);
    int aim[3];
    *(char *)((char *)node + 0xac) = 0;
    if (node[3] != 0) {
        int heading;
        VEC_Subtract((void *)(node[3] + 0x190), (void *)(*node + 0xb0), aim);
        heading = FX_Atan2(aim[0], aim[2]);
        node[0x1f] = heading;
        node[0x1e] = heading;
    }
    SetIndexedSlot(param_1, *(signed char *)((char *)param_1 + 0x20), &Ov259_EnterLunge);
}
