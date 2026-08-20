/* Visit every occupied slot of the park queue and release the ones the visitor
 * accepts. Ghidra models the object as Ov002ParkOwner; the struct below is the
 * codegen view of the same fields. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    char pad0000[0x1434];
    VecFx32 aParked[4];             /* +0x1434 */
    int aInUse[4];                  /* +0x1464 */
} Ov002ParkOwner;

extern Ov002ParkOwner *data_ov002_0207f628;

extern int func_ov002_02061370(int pContext, VecFx32 *pValue);

void func_ov002_02061308(int pContext)
{
    Ov002ParkOwner *pOwner;
    int i;

    pOwner = data_ov002_0207f628;

    for (i = 0; i < 4; i++) {
        if (pOwner->aInUse[i] != 0) {
            if (func_ov002_02061370(pContext, &pOwner->aParked[i]) != 0) {
                pOwner->aInUse[i] = 0;
            }
        }
    }
}
