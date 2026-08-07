/* Rebuilds the actor's id list at +0x398 from a caller-supplied word array:
   frees the existing nodes, re-initialises the list, then appends one node per
   word. The count arrives in bytes and is turned into words in place. */

extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_01fffc24(void *list);
extern int *func_01fffca8(void *list, int size, int rank);

void func_ov129_020cc330(char *self, int nCount, const int *pSrc)
{
    int i;

    NNSi_FndDestroyDoubleList(self + 0x398);
    func_01fffc24(self + 0x398);
    nCount = (unsigned int)nCount >> 2;
    i = 0;
    if (nCount <= 0) {
        return;
    }
    do {
        int *pNode = func_01fffca8(self + 0x398, 4, 100);
        *pNode = *pSrc++;
        i++;
    } while (i < nCount);
}
