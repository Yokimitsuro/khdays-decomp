/* func_ov008_0208ae84 -- Ov008_BuildRecipeList: collect the recipes listed under
 * category nCategory (Ov008_IsRecipeListed) into the table's sorted pointer
 * array (+0x38): count them, then (unless none) free the old array, allocate
 * one pointer per listed recipe and fill it with pointers into the recipe
 * records.  The count goes to *pCount; returns the array (0 when empty).
 */
typedef unsigned char u8;
typedef unsigned int  u32;

typedef struct Ov008RecipeRecord {
    u8 pad[0x34];
} Ov008RecipeRecord;

typedef struct Ov008ParamTable {
    u8  pad_00[8];
    u32 nRecipeCount;         /* 0x08 */
    u8  pad_0c[0x1c - 0xc];
    Ov008RecipeRecord *pRecipes; /* 0x1c */
    u8  pad_20[0x38 - 0x20];
    Ov008RecipeRecord **apListed; /* 0x38 */
} Ov008ParamTable;

extern Ov008ParamTable *data_ov008_02090fb0;
extern int func_ov008_0208adb8(int nCategory, int nIndex);             /* Ov008_IsRecipeListed */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);              /* AllocDefault */

Ov008RecipeRecord **func_ov008_0208ae84(int nCategory, int *pCount)
{
    int nListed = 0;
    u32 i;
    int nOut;

    for (i = 0; i < data_ov008_02090fb0->nRecipeCount; i++) {
        if (func_ov008_0208adb8(nCategory, i) != 0) {
            nListed++;
        }
    }
    if (nListed == 0) {
        *pCount = 0;
        return 0;
    }
    if (data_ov008_02090fb0->apListed != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov008_02090fb0->apListed);
        data_ov008_02090fb0->apListed = 0;
    }
    data_ov008_02090fb0->apListed = NNSi_FndAllocFromDefaultExpHeap(nListed * sizeof(Ov008RecipeRecord *));
    nOut = 0;
    for (i = 0; i < data_ov008_02090fb0->nRecipeCount; i++) {
        if (func_ov008_0208adb8(nCategory, i) != 0) {
            data_ov008_02090fb0->apListed[nOut] = &data_ov008_02090fb0->pRecipes[i];
            nOut++;
        }
    }
    *pCount = nOut;
    return data_ov008_02090fb0->apListed;
}
