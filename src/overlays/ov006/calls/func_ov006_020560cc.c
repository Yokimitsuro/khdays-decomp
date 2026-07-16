/* func_ov006_020560cc -- allocate an 8-byte title sub-object, instantiate its class into it,
 * and return the object's update entry (func_ov006_02056154). */
extern int  NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int val, unsigned int size);
extern int  func_02023930(int class_desc, int arg);   /* InstantiateClass */
extern int  data_ov006_02056668;   /* holds the allocated object pointer */
extern int  data_ov006_020563e4;   /* class descriptor */
extern void func_ov006_02056154(void);

int func_ov006_020560cc(int param_1) {
    int *blk = (int *)NNSi_FndGetCurrentRootHeap();
    data_ov006_02056668 = (int)blk;
    MI_CpuFill8(blk, 0, 8);
    *(int *)data_ov006_02056668 = func_02023930((int)&data_ov006_020563e4, param_1);
    return (int)func_ov006_02056154;
}
