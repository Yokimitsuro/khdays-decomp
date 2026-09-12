/* func_ov008_0208b2c8 -- Ov008_CommitSynthesisOrder: hand over the synthesised item
 * (stock + count, its "seen" flag, the recipe's unlock bit) and take the up to four
 * ingredient stacks out of the stock.
 */
typedef unsigned char u8;
typedef unsigned int  u32;

#define INGREDIENT_COUNT 4
#define FLAG_ITEM_SEEN_BASE 0x4db

typedef struct Ov008ItemDef {
    u8  pad_0000[0x14];
    int nItemId;                      /* 0x14 */
} Ov008ItemDef;

typedef struct Ov008ItemStack {
    Ov008ItemDef *pItemDef;
    int           nCount;
} Ov008ItemStack;

typedef struct Ov008RecipeRecord {                  /* synthesis recipe */
    int               pad_0000;
    u32               nUnlockBit;     /* 0x04 */
    int               nPrice;         /* 0x08 */
    Ov008ItemDef     *pItemDef;       /* 0x0c: product */
    int               nCount;         /* 0x10 */
    Ov008ItemStack    aIngredient[INGREDIENT_COUNT]; /* 0x14 */
} Ov008RecipeRecord;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];             /* 0x810 */
    u8 aUnlockBits[1];                /* 0x10e0 */
} GameState;

extern GameState *data_0204be18;
extern void func_020235a8(int nFlag);              /* GameState_SetFlag */
extern void func_02025640(u8 *pBits, u32 nBit);     /* BitArray_SetBit */

void func_ov008_0208b2c8(Ov008RecipeRecord *pRecipe)
{
    int i;

    data_0204be18->aItemCount[pRecipe->pItemDef->nItemId] += pRecipe->nCount;
    func_020235a8(pRecipe->pItemDef->nItemId + FLAG_ITEM_SEEN_BASE);
    func_02025640(data_0204be18->aUnlockBits, pRecipe->nUnlockBit);
    for (i = 0; i < INGREDIENT_COUNT; i++) {
        if (pRecipe->aIngredient[i].nCount != 0) {
            data_0204be18->aItemCount[pRecipe->aIngredient[i].pItemDef->nItemId] -= pRecipe->aIngredient[i].nCount;
        }
    }
}
