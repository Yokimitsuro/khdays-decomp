/* +0xf8 and +0x114 are 0x1c apart, i.e. two adjacent descriptors of the size
 * func_02035fb0 initialises -- an array of two, not two unrelated fields. */
typedef struct {
    char pad00[0x1c];
} Ov002Fader;

typedef struct {
    char pad00[0xf8];
    Ov002Fader fade[2];   /* +0xf8, +0x114 */
} Ov002Ctx;

extern void func_ov002_02053938(int a);
extern int func_ov002_02053558(int a);
extern void func_ov002_020535a4(void);
extern void func_02035fb0(void *p, int a1, int a2, int a3, int a4);
extern void func_02035ffc(void *p);
extern void func_ov002_020539f4(int a);

extern Ov002Ctx *data_ov002_0207f614;

void func_ov002_02055490(void) {
    Ov002Ctx *c = data_ov002_0207f614;

    func_ov002_02053938(0);
    func_ov002_02053558(0x50);
    func_ov002_020535a4();
    func_02035fb0(&c->fade[0], 2, 0x18000, 0, 300);
    func_02035fb0(&c->fade[1], 0, 0, 0, 0);
    func_02035ffc(&c->fade[0]);
    func_02035ffc(&c->fade[1]);
    func_ov002_020539f4(0);
}
