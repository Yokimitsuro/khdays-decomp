typedef int fx32;

typedef struct {
    fx32 x, y, z;
} VecFx32;

typedef struct {
    fx32 w, x, y, z;
} Quat_0203c304;

typedef struct {
    int marker;                 /* 0x00 */
    int field_04;                /* 0x04 */
    Quat_0203c304 orientation;   /* 0x08 */
    char pad18[0x2c - 0x18];
    VecFx32 position;             /* 0x2c */
} Entry_0203c304;

typedef struct {
    char pad00[0x78];
    void *model;                  /* 0x78 */
} ModelHolder_0203c304;

typedef struct {
    char pad00[0x4c];
    VecFx32 baseVector;           /* 0x4c */
    char pad58[0x88 - 0x58];
    ModelHolder_0203c304 *modelHolder; /* 0x88 */
    int count;                    /* 0x8c */
    Entry_0203c304 *entries;      /* 0x90 */
} Obj_0203c304;

extern void func_01ffa724(int factor, int *src, int *dst);
extern void func_0202ec2c(int *mtx, const Quat_0203c304 *q);
extern void func_02015880(const VecFx32 *target);
extern void func_0201574c(void);
extern void func_02016ae8(int obj, unsigned int idx, unsigned int val);
extern void func_02016bd8(int obj, unsigned int idx, unsigned int val);
extern void func_02016cd0(unsigned char *ptr, int arg);
extern void func_01ffcc1c(void *model, unsigned int materialId, unsigned int shapeId, int sendMaterial);
extern int data_02047458[3];
extern int data_02047428[9];

void func_0203c304(Obj_0203c304 *this) {
    int i;
    for (i = 0; i < this->count; i++) {
        Entry_0203c304 *entry = &this->entries[i];
        if (entry->marker != 0) {
            func_01ffa724(entry->marker, (int *)&this->baseVector, data_02047458);
            func_0202ec2c(data_02047428, &entry->orientation);
            func_02015880(&entry->position);
            func_0201574c();
            func_02016ae8((int)this->modelHolder->model, 0, 3);
            func_02016bd8((int)this->modelHolder->model, 0, (entry->field_04 * 31) >> 12);
            func_02016cd0((unsigned char *)this->modelHolder->model, i % 0x3f);
            func_01ffcc1c(this->modelHolder->model, 0, 0, 1);
        }
    }
}
