/* Drop the entry (kind, value) from the list and reopen whatever the cursor now points at.
 *
 * The removal is done by func_ov002_0205cebc, which takes both halves of the entry key straight from
 * this function's own parameters -- they are never touched here, which is why the pointer load
 * ahead of the call cannot use r0 or r1. After the list shrinks, a cursor sitting past the new
 * end is pulled back to the last row, and if the entry under the cursor classifies as kind 3 it
 * is announced with its column (six to a row) and opened.
 *
 * The remainder has to come from func_02020400 by hand: writing `%%` emits _s32_div_f, which is
 * not linkable here. Ghidra carries the field names on Ov002PanelSession. */

typedef struct {
    unsigned char bKind;        /* +0 */
    unsigned char bMode;        /* +1 */
    char pad0002[2];
    unsigned char bKey;         /* +4 */
} Ov002PanelSession;

extern long long func_02020400(int numerator, int denominator);
extern Ov002PanelSession *data_ov002_0207f620;
extern int func_ov002_0205cebc(unsigned int kind, unsigned int value);
extern void func_ov002_0205cc44(void);
extern int func_ov002_0205a4ec(void);
extern int func_ov002_0205a3f0(int *out, int mode);
extern void func_ov002_0205bff4(int kind, int column);
extern void func_ov002_0205c87c(int entry);

void func_ov002_0205e3e4(unsigned int kind, unsigned int value) {
    Ov002PanelSession *session = data_ov002_0207f620;
    int out;
    int count;

    func_ov002_0205cebc(kind, value);
    func_ov002_0205cc44();
    count = func_ov002_0205a4ec();
    if (count >= 1 && session->bKey >= count) {
        session->bKey = (unsigned char)(count - 1);
    }
    if (func_ov002_0205a3f0(&out, session->bMode) == 3) {
        func_ov002_0205bff4(session->bKind, (int)(func_02020400(session->bKey, 6) >> 32));
        func_ov002_0205c87c(out);
    }
}
