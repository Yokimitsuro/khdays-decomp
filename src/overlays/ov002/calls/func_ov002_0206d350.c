/* Silence the current ov022 entry and park the session sub-state on 2,
 * reporting 1. Reports 0 without touching anything when func_ov002_0206b5a0
 * refuses mode 1 -- and that early return is written LAST so it lands out of
 * line, which is where the ROM's forward beq goes.
 *
 * The field is reached as base + 0x8bcc + 0xc0: the session is a sub-object of
 * the root context, so the big offset is a pool literal held in a register and
 * the field offset is the immediate. Writing the sum as one 0x8c8c constant
 * costs the split and four bytes. */
typedef struct {
    char pad00[0xc0];
    int nSubState;          /* +0xc0 */
} Ov002Session;

extern int func_ov002_0206b5a0(int mode);
extern int func_ov022_02083f5c(void);
extern void func_ov022_02086638(int entry, int a);

extern int data_ov002_0207fa00;

int func_ov002_0206d350(void) {
    if (func_ov002_0206b5a0(1) != 0) {
        Ov002Session *session = (Ov002Session *)(data_ov002_0207fa00 + 0x8bcc);

        func_ov022_02086638(func_ov022_02083f5c(), 0);
        session->nSubState = 2;
        return 1;
    }
    return 0;
}
