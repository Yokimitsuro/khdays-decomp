/* Sets the ov030 scene up and hands back its per-frame entry point.
 *
 * Clears the two slots the scene fills in later, parks the slew threshold at
 * its minimum and runs the shared init. Outside mission mode it also loads the
 * archive entry for this scene, wires it up, resets the focus field and calls
 * the scene's own hook; and unless story flag 0x2089 is set it instantiates the
 * extra class from a template whose last word is biased by the scene id.
 */
struct Ov030ClassArgs { int w00, w04, w08, w0c, w10; };

extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov030_020b3374(int *self);
extern void *func_0201ef9c(void *archive, int entry);
extern void func_0202a3cc(int a, int b, int c, int d);
extern int func_02023588(int flag);
extern int func_02023930(void *descriptor, struct Ov030ClassArgs *args);
extern void func_ov030_020b4b9c(int base, int slots);
extern void func_ov022_020a4798(int base, int a, int b);
extern void func_ov022_0209fb24(void);
extern unsigned char data_0204c240;
extern int data_ov030_020b5908;
extern struct Ov030ClassArgs data_ov030_020b58b0;
extern int data_ov022_020b2930;

void *func_ov030_020b3234(int *self) {
    int base = NNSi_FndGetCurrentRootHeap();

    *(int *)(base + 0x2c50) = 0;
    *(int *)(base + 0x2cac) = 0;
    *(int *)(base + 0x2ca8) = (int)0x80000000;

    func_ov030_020b3374(self);

    if ((data_0204c240 & 4) == 0) {
        *(int *)(base + 0x2c50) =
            (int)func_0201ef9c(&data_ov030_020b5908, *self + 7);
        func_0202a3cc(base + 0x2c2c, *(int *)(base + 0x20) + 4,
                      *(int *)(base + 0x2c50), *self + 7);
        *(int *)(base + 0x6bc) = -1;
        (*(void (**)(int, int))(base + 0x664))(base, 0);
        *(int *)(base + 0x2cac) = 0;
        if (func_02023588(0x2089) == 0) {
            struct Ov030ClassArgs args = data_ov030_020b58b0;

            args.w10 += *self;
            *(int *)(base + 0x2cac) =
                func_02023930(&data_ov022_020b2930, &args);
        }
    }

    func_ov030_020b4b9c(base, base + 0x2cb0);
    func_ov022_020a4798(base, 0x41, 0xd0);
    return (void *)&func_ov022_0209fb24;
}
