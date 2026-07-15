#pragma thumb on
/* func_ov043_020b3ad0 -- tear down and free the node's sub-object (@+0x2644), ov043.
 * func_ov022_02091228 releases it, then it is freed from the default heap. */
extern void func_ov022_02091228(void *sub);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
void func_ov043_020b3ad0(char *obj) {
    func_ov022_02091228(*(void **)(obj + 0x2644));
    NNSi_FndFreeFromDefaultHeap(*(void **)(obj + 0x2644));
}
