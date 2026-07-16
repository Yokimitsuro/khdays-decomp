/* func_ov024_02082eb8 -- MobiClip player: has the user asked to abort playback?
 * True when either of the two request slots at heap+0x8bd8 / heap+0x8bdc reads 2. */
extern int NNSi_FndGetCurrentRootHeap(void);

int func_ov024_02082eb8(void) {
    int heap = NNSi_FndGetCurrentRootHeap();
    return *(int *)(heap + 0x8bd8) == 2 || *(int *)(heap + 0x8bdc) == 2;
}
