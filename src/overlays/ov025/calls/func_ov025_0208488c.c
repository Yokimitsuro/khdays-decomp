extern void func_ov025_02089818();
extern void func_ov025_02088af4();
extern void func_ov025_02088acc();
extern int data_ov025_020b5744;

void func_ov025_0208488c(unsigned int arg0) {
    func_ov025_02089818(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x9500, arg0);
    func_ov025_02088af4(*(int *)((char *)&data_ov025_020b5744 + 4), arg0);
    func_ov025_02088acc(*(int *)((char *)&data_ov025_020b5744 + 4), arg0);
    *(unsigned int *)(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x9600) = arg0;
}
