extern void NNS_FndRemoveListObject(char *, void *);
extern void NNSi_FndFreeFromDefaultHeap(void *);
void func_ov008_020609e4(char *obj, void *block)
{
    NNS_FndRemoveListObject(obj + 0x1e7c, block);
    if (block != 0) {
        NNSi_FndFreeFromDefaultHeap(block);
    }
}
