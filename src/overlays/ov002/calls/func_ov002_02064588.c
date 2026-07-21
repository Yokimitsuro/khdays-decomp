extern int func_ov002_020536bc(int slot);
extern void func_ov002_020536dc(int handle, int flag);
extern int func_ov002_02053558(int id);
extern void func_ov002_020535a4(int handle);
/* Bring up panel 9 and register string 0x5e1 with the HUD. */
void func_ov002_02064588(void) {
    func_ov002_020536dc(func_ov002_020536bc(9), 0);
    func_ov002_020535a4(func_ov002_02053558(0x5e1));
}
