extern void func_ov107_020c4924(void *self);
extern void func_0203c9d0(void *pose, void *bones);

typedef struct {
    int words[11];
} Ov191Pose;

typedef struct {
    char pad0000[0xa0];
    char bones[0x2ec];
    Ov191Pose *pClip;   /* +0x38c */
    char pad0390[0xc];
    Ov191Pose pose;     /* +0x39c */
} Ov191Object;

void func_ov155_020d3c58(Ov191Object *self) {
    func_ov107_020c4924(self);

    self->pose = *(Ov191Pose *)((char *)self->pClip + 4);

    func_0203c9d0(&self->pose, self->bones);
}
