/* Release the mission owner's +0x2d38 block: free its +0x10 request, then the 2 x 2 grid of
 * 0x108-byte requests starting at +0x130 (row stride 0x240), and rewind this actor's +0x2644
 * part record (+0x30). */
extern void func_0202a7dc(int p);
extern void func_ov022_02091228(int p);
extern int data_ov043_020b58e0;

void func_ov043_020b47fc(int this_) {
    int block = data_ov043_020b58e0 + 0x2d38;
    int i;
    int j;
    func_0202a7dc(block + 0x10);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            func_0202a7dc(block + 0x130 + i * 0x240 + j * 0x108);
        }
    }
    func_ov022_02091228(*(int *)(this_ + 0x2644) + 0x30);
}
