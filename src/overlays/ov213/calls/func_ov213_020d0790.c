/* Push the object's own bone table back into the current clip: run the animator,
 * then copy the 44 bytes at +0xa0 over the clip's slot at +0x10. Mirror of the
 * RefreshPose family, which copies the other way. */
extern void func_ov107_020c6980(void *self);

typedef struct {
    int words[11];      /* 44 bytes */
} Ov213Pose;

typedef struct {
    char pad0000[0x10];
    Ov213Pose pose;     /* +0x10 */
} Ov213Clip;

typedef struct {
    char pad0000[0xa0];
    Ov213Pose bones;    /* +0xa0 */
    char pad00cc[0x2c4];
    Ov213Clip *pClip;   /* +0x390 */
} Ov213Object;

void func_ov213_020d0790(Ov213Object *self) {
    func_ov107_020c6980(self);

    self->pClip->pose = self->bones;
}
