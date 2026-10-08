/* Script command: when the actor's sequence is loaded, stores it in the current slot and continues;
 * otherwise requests it and asks to retry. */

extern int ScriptVm_ReadOperandInt(void *state, void *operands);
extern int IsSubStructValidAndReady(int x);
extern void Slot48_StoreAtCurrentIndex(void *a, int b);
extern void SetSelectionIfChanged(int x);
extern unsigned char data_020425e8;

int RegisterActorOrRetry(void *obj, void *operands) {
    int r4 = ScriptVm_ReadOperandInt(obj, operands);
    if (IsSubStructValidAndReady(r4) != 0) {
        Slot48_StoreAtCurrentIndex(obj, r4);
        return 0;
    }
    data_020425e8 = r4;
    SetSelectionIfChanged(r4 & 0xff);
    return 1;
}
