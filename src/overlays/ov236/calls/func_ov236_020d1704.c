/* Spawn step: hold off while the spawner is still busy (+0xad of its owner),
 * then pick the entry animation -- the short one when the "seen before" bit is
 * set, the full one otherwise -- and hand control to the idle handler. */
extern void func_0203c634(void *self, int script, void *handler);

typedef struct {
    char pad0000[0x1c7];
    unsigned char bEntryAnim;   /* +0x1c7 */
} Ov236Model;

typedef struct {
    char pad0000[0xad];
    unsigned char bBusy;        /* +0xad */
} Ov236Spawner;

typedef struct {
    Ov236Model *pModel;         /* +0 */
    Ov236Spawner *pSpawner;     /* +4 */
    char pad0008[0x4a];
    unsigned char bSeenBefore : 1;  /* +0x52 bit 0 */
} Ov236Actor;

typedef struct {
    char pad0000[4];
    Ov236Actor *pActor;         /* +4 */
    char pad0008[0x18];
    signed char bScript;        /* +0x20 */
} Ov236Enemy;

void func_ov236_020d1704(Ov236Enemy *self) {
    Ov236Actor *actor = self->pActor;

    if (actor->pSpawner->bBusy != 0) {
        return;
    }

    if (actor->bSeenBefore) {
        actor->pModel->bEntryAnim = 4;
    } else {
        actor->pModel->bEntryAnim = 7;
    }

    func_0203c634(self, self->bScript, 0);
}
