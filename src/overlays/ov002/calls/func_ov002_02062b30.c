typedef struct {
    unsigned pad : 2;
    unsigned visible : 1;
} PageFlags;

extern void func_ov002_02063114(int a, int b);
extern int func_ov002_020536bc(int id);
extern void func_ov002_020536dc(int handle, int a);
extern void func_ov002_02053558(int id);
extern void func_ov002_020535f0(void);
extern void func_ov002_02053864(int a);
extern char *data_ov002_0207f62c;

/* Redraws the options page while it is visible: mode 2 only refreshes the footer, every other
 * mode also rebuilds the two toggles and their labels. */
void func_ov002_02062b30(void) {
    char *page = (&data_ov002_0207f62c)[1];
    if (((PageFlags *)(page + 0x70))->visible == 0) {
        return;
    }
    *(int *)(page + 8) = 0;
    if (*(int *)(page + 0xc) != 2) {
        func_ov002_02063114(1, 1);
        func_ov002_02063114(0, 0);
        func_ov002_020536dc(func_ov002_020536bc(8), 0);
        func_ov002_020536dc(func_ov002_020536bc(0xb), 0);
        func_ov002_02053558(0x5e1);
        func_ov002_020535f0();
        func_ov002_02053558(0x5ed);
        func_ov002_020535f0();
    }
    func_ov002_02053558(0x5e3);
    func_ov002_020535f0();
    func_ov002_02053864(1);
}
