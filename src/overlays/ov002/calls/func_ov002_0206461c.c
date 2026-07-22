/* Re-arm three tag-tracker nodes in one go: tag 9 off, tags 0xb and 8 on. */
extern int func_ov002_020536bc(int tag);
extern void func_ov002_020536dc(int node, int armed);

void func_ov002_0206461c(void) {
    func_ov002_020536dc(func_ov002_020536bc(9), 0);
    func_ov002_020536dc(func_ov002_020536bc(0xb), 1);
    func_ov002_020536dc(func_ov002_020536bc(8), 1);
}
