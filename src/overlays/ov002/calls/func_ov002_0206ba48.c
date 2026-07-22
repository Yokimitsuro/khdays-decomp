/* Abort the session, if one is open: cancel at the link layer and let the ov022
 * side tear its half down.
 *
 * The cancel takes the CONSTANT -1, not the session handle -- the handle at
 * +0x8bcc is only the gate, and the -1 built for the comparison is still in r0
 * at the call. */
extern void func_01fffe14(int what);
extern void func_ov022_02088474(void);

typedef struct {
    char pad0000[0x8bcc];
    int nSessionHandle;     /* +0x8bcc, -1 = none */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

void func_ov002_0206ba48(void) {
    if (data_ov002_0207fa00->nSessionHandle == -1) {
        return;
    }

    func_01fffe14(-1);
    func_ov022_02088474();
}
