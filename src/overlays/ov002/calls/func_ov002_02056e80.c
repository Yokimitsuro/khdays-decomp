extern void func_ov002_0205e1f0(unsigned char a);
extern void func_ov002_0205d214(unsigned char a, int b);
extern void func_ov002_0205d430(unsigned char a);
extern void func_ov002_0205d98c(int a);
extern unsigned char data_0204c4f0;
extern unsigned char data_0204c4f2;
extern unsigned char data_0204c4f3;
extern int data_0204c4fc;

/* Republishes the HUD from the saved state: the party layout, the current member, the camera
 * mode, and -- unless the member is 9 -- the active mission block. */
void func_ov002_02056e80(void) {
    func_ov002_0205e1f0(data_0204c4f2);
    func_ov002_0205d214(data_0204c4f0, -1);
    func_ov002_0205d430(data_0204c4f3);
    if (data_0204c4f0 == 9) {
        return;
    }
    func_ov002_0205d98c(data_0204c4fc);
}
