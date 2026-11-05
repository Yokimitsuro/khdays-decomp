/* Swap the two shared global words. */
extern int gMainHeap;
extern int gSubHeap;
void Ov023_SwapGlobalPair(void) {
    int tmp = gMainHeap;
    gMainHeap = gSubHeap;
    gSubHeap = tmp;
}
