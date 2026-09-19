/* Re-bind the clip and push the object's bone table into it: unhook the old clip
 * at +0x39c, re-attach with the caller's slot, then copy the 44 bytes at +0xa0
 * over the new clip's pose at +0x10.
 *
 * The clip is reached through TWO dereferences -- the pointer at +0x388 holds a
 * pointer to the clip -- and the +0x10 is added after the first ldm, not before. */
extern void func_ov107_020c9ec8(void *clip);
extern void func_ov107_020c6980(void *self, int slot);

typedef struct {
    int words[11];      /* 44 bytes */
} Ov158Pose;

typedef struct {
    char pad0000[0x10];
    Ov158Pose pose;     /* +0x10 */
} Ov158Clip;

typedef struct {
    char pad0000[0xa0];
    Ov158Pose bones;    /* +0xa0 */
    char pad00cc[0x2bc];
    Ov158Clip **ppClip; /* +0x388 */
    char pad038c[0x10];
    void *pOldClip;     /* +0x39c */
} Ov158Object;

void func_ov159_020d1cec(Ov158Object *self, int slot) {
    func_ov107_020c9ec8(self->pOldClip);
    func_ov107_020c6980(self, slot);

    (*self->ppClip)->pose = self->bones;
}
