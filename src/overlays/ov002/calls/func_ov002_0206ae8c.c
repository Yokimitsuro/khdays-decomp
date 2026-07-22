/* Snapshot the paused object into a 0x100-byte stack buffer and hand it to the
 * report builder. Does nothing when nothing is paused.
 *
 * The object being snapshotted is the CALLER'S, passed straight through -- r0 is
 * never written before the call. The paused-object slot is only the gate. */
extern void func_0202fcb8(int object, void *out);
extern void func_ov002_02063294(void *snapshot);

typedef struct {
    char pad0000[0x8c94];
    int nPauseObject;       /* +0x8c94, -1 = none */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

void func_ov002_0206ae8c(int object) {
    char snapshot[0x100];

    if (data_ov002_0207fa00->nPauseObject == -1) {
        return;
    }

    func_0202fcb8(object, snapshot);
    func_ov002_02063294(snapshot);
}
