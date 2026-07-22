/* Re-bind the clip and push the object's bone table into it: unhook the old clip
 * at +0x39c, re-attach with the caller's slot, then copy the 44 bytes at +0xa0
 * over the new clip's pose at +0x10.
 *
 * The clip is reached through TWO dereferences -- the pointer at +0x384 holds a
 * pointer to the clip -- and the +0x10 is added after the first ldm, not before. */
extern void func_ov107_020c9ec8(void *clip);
extern void func_ov107_020c6980(void *self, int slot);

typedef struct {
    int words[11];      /* 44 bytes */
} Ov137Pose;

typedef struct {
    char pad0000[0x10];
    Ov137Pose pose;     /* +0x10 */
} Ov137Clip;

typedef struct {
    char pad0000[0xa0];
    Ov137Pose bones;    /* +0xa0 */
    char pad00cc[0x2b8];
    Ov137Clip **ppClip; /* +0x384 */
    char pad0388[0x14];
    void *pOldClip;     /* +0x39c */
} Ov137Object;

void func_ov247_020d1cec(Ov137Object *self, int slot) {
    func_ov107_020c9ec8(self->pOldClip);
    func_ov107_020c6980(self, slot);

    (*self->ppClip)->pose = self->bones;
}
