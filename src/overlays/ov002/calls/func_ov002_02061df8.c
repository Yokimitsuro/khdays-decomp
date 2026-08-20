typedef struct { int x; int y; int z; } VecFx32;

typedef struct {
    char pad0000[0x1434];
    VecFx32 aParked[4];
    int aInUse[4];
} Ov002ParkOwner;

extern int data_ov002_0207f628;

void func_ov002_02061df8(const VecFx32 *pValue)
{
    int i;
    Ov002ParkOwner *pOwner;

    pOwner = *(Ov002ParkOwner **)&data_ov002_0207f628;
    if (pOwner == 0) return;
    for (i = 0; i < 4; i++) {
        if (pOwner->aInUse[i] == 0) {
            pOwner->aParked[i] = *pValue;
            pOwner->aInUse[i] = 1;
            return;
        }
    }
}
