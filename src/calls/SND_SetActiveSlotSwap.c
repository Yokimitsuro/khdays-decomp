/* SND_SetActiveSlotSwap: stores the active-slot mask and returns the previous one. */

extern int data_0204ad4c;

int SND_SetActiveSlotSwap(int mask) {
    int old = data_0204ad4c;
    data_0204ad4c = mask;
    return old;
}
