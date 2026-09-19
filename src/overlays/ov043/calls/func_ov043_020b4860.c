/* Bind the mission owner's +0x2d38 slot to this actor's +0x263c record (+4), then run the
 * 020b5274 pass on the actor and the 020b4bd8 pass on the owner's +0x2d38 block. */
extern int data_ov043_020b58e0;
extern void func_ov043_020b5274(int self);
extern void func_ov043_020b4bd8(int block);

void func_ov043_020b4860(int self) {
    int block = data_ov043_020b58e0 + 0x138 + 0x2c00;
    *(int *)(block + 0x118) = *(int *)(self + 0x2000 + 0x63c) + 4;
    func_ov043_020b5274(self);
    func_ov043_020b4bd8(block);
}
