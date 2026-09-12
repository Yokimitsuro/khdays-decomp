extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov043_020b3810(int param_1);
extern void func_ov043_020b47fc(int param_1);
extern void func_ov043_020b3ad0(char *obj);
extern void func_ov022_0209fab4(char *root);
extern int data_ov043_020b58e0;

void func_ov043_020b3264(void) {
    int root = (int)NNSi_FndGetCurrentRootHeap();
    func_ov043_020b3810(root);
    func_ov043_020b47fc(root);
    func_ov043_020b3ad0((char *)root);
    func_ov022_0209fab4((char *)root);
    data_ov043_020b58e0 = 0;
}
