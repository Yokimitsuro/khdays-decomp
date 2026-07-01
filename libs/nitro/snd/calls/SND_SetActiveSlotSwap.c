extern int data_0204ad4c;

int SND_SetActiveSlotSwap(int arg0)
{
    int old = data_0204ad4c;
    data_0204ad4c = arg0;
    return old;
}
