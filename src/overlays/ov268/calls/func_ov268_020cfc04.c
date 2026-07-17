/*
 * func_ov268_020cfc04 -- x3 (ov208/209/268). Snapshot the owner's matrix and nudge it by a small
 * downward offset, then re-commit it.
 * Copy the 11-word matrix at obj+0xa0 into the working slot obj+0x3e0. Build a scaled offset
 * (-0x25b3 * the shared vector at *OS_IsThreadAvailable()+0x7c) and add the owner point obj+0x74
 * into it; feed it to the matrix at obj+0x3e0 (0203ca30) and finalise with 0203ca9c(.., 0x14cd).
 */
typedef struct {
    int data[11];
} Mat;

typedef struct {
    char p0[0xa0];
    Mat src;
    char p1[0x314];
    Mat dst;
} Obj;

extern int *OS_IsThreadAvailable_0x020c9848();
extern void func_01ffa724();
extern void VEC_Add();
extern void func_0203ca30();
extern void func_0203ca9c();

void func_ov268_020cfc04(int param_1, int obj) {
    int tmp[3];

    ((Obj *)obj)->dst = ((Obj *)obj)->src;
    func_01ffa724(-0x25b3, *OS_IsThreadAvailable_0x020c9848() + 0x7c, tmp);
    VEC_Add(obj + 0x74, tmp, tmp);
    func_0203ca30(obj + 0x3e0, tmp);
    func_0203ca9c(obj + 0x3e0, 0x14cd);
}
