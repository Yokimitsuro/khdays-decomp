/* ov024 .data, 0x02093900-0x02093958: the three static objects of the movie
 * player.
 *
 * data_ov024_02093900 is the handle of the one live stream source. There is a
 * single slot rather than per-instance state: MobiClip_SrcOpen parks the handle
 * it gets from InstantiateClass here, the teardown clears it, and -1 is the
 * "nothing open" value it starts at.
 *
 * data_ov024_02093904 is the class descriptor that same open call hands to
 * InstantiateClass -- class 8 of group 13, with the player's open and close
 * hooks and a 0x8bf0-byte auxiliary block. It is the shape the rest of the tree
 * calls GameClassDescriptor.
 *
 * data_ov024_02093918 is the player's BG palette, loaded to both engines at
 * palette offset 0x1a0 by GX_LoadBGPltt and GXS_LoadBGPltt. Sixteen BGR555
 * entries are used and sixteen are spare: index 0 is the transparent one, 1 a
 * warm white, 3 to 8 the primaries and their complements in order, and 15 a
 * dark grey. Only the low half is ever written, which is why the second half
 * of the block is zero.
 */

typedef unsigned short u16;
typedef void (*GameClassFn)(void);

typedef struct {
    u16 nClassId;
    u16 nGroupId;
    GameClassFn pfnOpen;
    GameClassFn pfnClose;
    int nAuxSize;
    int *pArena;
} GameClassDescriptor;

#define BGR555(r, g, b) ((u16)(((b) << 10) | ((g) << 5) | (r)))

extern void func_ov024_02082a78(void);
extern void func_ov024_02082c44(void);

int data_ov024_02093900 = -1;

GameClassDescriptor data_ov024_02093904 = {
    8,
    13,
    func_ov024_02082a78,
    func_ov024_02082c44,
    0x8bf0,
    0,
};

u16 data_ov024_02093918[32] = {
    BGR555(0, 0, 0),        /*  0 transparent */
    BGR555(28, 27, 24),     /*  1 warm white */
    BGR555(0, 0, 0),        /*  2 */
    BGR555(31, 0, 0),       /*  3 red */
    BGR555(0, 31, 0),       /*  4 green */
    BGR555(0, 0, 31),       /*  5 blue */
    BGR555(0, 31, 31),      /*  6 cyan */
    BGR555(31, 0, 31),      /*  7 magenta */
    BGR555(31, 31, 0),      /*  8 yellow */
    BGR555(0, 0, 0),        /*  9 */
    BGR555(0, 0, 0),        /* 10 */
    BGR555(0, 0, 0),        /* 11 */
    BGR555(0, 0, 0),        /* 12 */
    BGR555(0, 0, 0),        /* 13 */
    BGR555(0, 0, 0),        /* 14 */
    BGR555(8, 8, 8),        /* 15 dark grey */
    BGR555(0, 0, 0),        /* 16 spare from here down */
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
    BGR555(0, 0, 0),
};
