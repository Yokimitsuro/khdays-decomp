extern char *NNSi_FndGetCurrentRootHeap(void);
extern int func_02023930(void *desc, int arg);
extern char *data_ov026_02091360;
extern char data_ov026_02091230;
extern void func_ov026_020829b4(void);

/* Allocates the sub-scene block off the root heap, builds its resource set and enters state 9. */
void *func_ov026_02082960(void) {
    char *st = NNSi_FndGetCurrentRootHeap();
    *(char **)&data_ov026_02091360 = st;
    *(int *)(st + 4) = func_02023930(&data_ov026_02091230, 0);
    *(int *)st = 9;
    return (void *)&func_ov026_020829b4;
}
