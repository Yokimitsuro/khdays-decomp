/* func_ov008_020846c0 -- Ov008_RebuildShopList: rebuild the shop's record
 * list for the current tab (+0xc250) and category (+0xc3c0): tab 0 builds
 * the shop list for the story level (1 with flag 0x200b set, else field
 * 0x44e) and the category's slot from table 0208feb8, tab 1 the item list
 * (slot from the same table), tab 2 the recipe list (category from
 * 0208fe60 + 0x2c) and tab 3 the reward list (list from 0208fe60).  When a
 * list came back (or bForce) it becomes the view (+0xc3d0 / +0xc3cc); unless
 * bKeep is set and the cursor still fits, cursor, scroll and the scroll
 * argument (+0xc4bc) are reset, otherwise a scroll that ends exactly at the
 * new count steps back one row; +0xc4c4 is raised, the record under the
 * cursor gets its pending unlock bit set (tabs other than 1), the cursor is
 * refreshed and the count published.  Returns whether a list was built.
 * Codegen: the three category tables are struct copies from rodata (the
 * 16-byte one as a halfword loop, the others unrolled); the reset branch is
 * written first; pView declared before pShop.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   s16;

#define TAB_SHOP    0
#define TAB_ITEMS   1
#define TAB_RECIPES 2
#define TAB_REWARDS 3
#define FLAG_STORY_DONE 0x200b
#define FIELD_STORY 0x44e
#define ROWS_VISIBLE 7

typedef struct Ov008ParamRecord Ov008ParamRecord;

typedef struct Ov008CategorySlots {
    s16 aSlot[8];             /* per category: shop / item list slot */
} Ov008CategorySlots;

typedef struct Ov008RecipeCategories {
    s16 aCategory[6];         /* per category: recipe list */
} Ov008RecipeCategories;

typedef struct Ov008RewardLists {
    s16 aList[2];             /* per category: reward list */
} Ov008RewardLists;

typedef struct Ov008ShopView {
    int nRow;                 /* 0x00 */
    int nScroll;              /* 0x04 */
    u32 nCount;               /* 0x08 */
    Ov008ParamRecord **apRows; /* 0x0c */
    u8  pad_10[0xf8 - 0x10];
    int nScrollArg;           /* 0xf8 (ctx 0xc4bc) */
    u8  pad_fc[4];
    int bListReady;           /* 0x100 (ctx 0xc4c4) */
} Ov008ShopView;

typedef struct Ov008ShopState {
    u8  pad_00[8];
    int nCategory;            /* 0x08 (ctx 0xc3c0) */
    Ov008ShopView view;       /* 0x0c (ctx 0xc3c4) */
} Ov008ShopState;

typedef struct Ov008PanelContext {
    u8  pad_0000[0xc250];
    int nTab;                 /* 0xc250 */
    u8  pad_c254[0xc3b8 - 0xc254];
    Ov008ShopState shop;      /* 0xc3b8 */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern s16 data_ov008_0208feb8[];                                 /* category slots (8) */
extern s16 data_ov008_0208fe60[];                                 /* reward lists (2) ... recipe categories at +0x2c (6) */
extern int  func_02023588(int nFlag);                             /* GameState_IsFlagSet */
extern u32  func_020235d0(int nField, int nBits);                 /* GameState_GetField */
extern Ov008ParamRecord **func_ov008_0208a91c(int nLevel, int nSlot, u32 *pCount); /* Ov008_BuildShopList */
extern Ov008ParamRecord **func_ov008_0208aac0(int nSlot, u32 *pCount);           /* item list */
extern Ov008ParamRecord **func_ov008_0208ae84(int nCategory, u32 *pCount);       /* Ov008_BuildRecipeList */
extern Ov008ParamRecord **func_ov008_0208af90(int nList, u32 *pCount);           /* reward list */
extern u32  func_ov008_0208b368(Ov008ParamRecord **apRecords, int nIndex, u32 bSet); /* Ov008_QueryRecordUnlock */
extern void func_ov008_02084604(void);                            /* refresh the cursor */
extern void func_ov008_020844cc(u32 nCount);                      /* publish the count */

int func_ov008_020846c0(int bKeep, int bForce)
{
    Ov008CategorySlots slots;
    Ov008RecipeCategories recipes;
    u32 nCount;
    Ov008RewardLists rewards;
    Ov008PanelContext *ctx;
    Ov008ShopView *pView;
    Ov008ShopState *pShop;
    Ov008ParamRecord **apRows;
    int nLevel;

    ctx = data_ov008_02090fac;
    apRows = 0;
    pView = &ctx->shop.view;
    pShop = &ctx->shop;
    nCount = 0;
    slots = *(Ov008CategorySlots *)data_ov008_0208feb8;
    recipes = *(Ov008RecipeCategories *)&data_ov008_0208fe60[0x16];
    rewards = *(Ov008RewardLists *)&data_ov008_0208fe60[0];
    switch (ctx->nTab) {
    case TAB_SHOP:
        if (func_02023588(FLAG_STORY_DONE) != 0) {
            nLevel = 1;
        } else {
            nLevel = func_020235d0(FIELD_STORY, 3);
        }
        apRows = func_ov008_0208a91c(nLevel, slots.aSlot[pShop->nCategory], &nCount);
        break;
    case TAB_ITEMS:
        apRows = func_ov008_0208aac0(slots.aSlot[pShop->nCategory], &nCount);
        break;
    case TAB_RECIPES:
        apRows = func_ov008_0208ae84(recipes.aCategory[pShop->nCategory], &nCount);
        break;
    case TAB_REWARDS:
        apRows = func_ov008_0208af90(rewards.aList[pShop->nCategory], &nCount);
        break;
    }
    if (apRows != 0 || bForce != 0) {
        pView->apRows = apRows;
        pView->nCount = nCount;
        if (bKeep != 0 || nCount <= (u32)pView->nRow) {
            pView->nScroll = 0;
            pView->nRow = 0;
            pView->nScrollArg = 0;
        } else if (pView->nScroll > 0 && pView->nScroll + ROWS_VISIBLE == nCount) {
            pView->nScroll--;
            pView->nScrollArg = 0;
        }
        pView->bListReady = 1;
        if (apRows != 0 && ctx->nTab != TAB_ITEMS) {
            func_ov008_0208b368(apRows, pView->nRow, 1);
        }
        func_ov008_02084604();
        func_ov008_020844cc(nCount);
    }
    return apRows != 0;
}
