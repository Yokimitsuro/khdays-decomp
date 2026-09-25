/* ov107 class descriptor data_ov107_020cbaa4, 0x020cbaa4-0x020cbab8 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020c9960, method 020c9a10, 0x90-byte state.
 */

typedef void (*GameClassFn)(void);

typedef struct GameClassDescriptor {
    unsigned short nClassId;  /* 0x00 */
    unsigned short nGroupId;  /* 0x02 */
    GameClassFn pfnCtor;      /* 0x04: returns the object's first state fn */
    GameClassFn pfnMethod;    /* 0x08 */
    int nAuxSize;             /* 0x0c: zero-filled state block */
    int *pArena;              /* 0x10 */
} GameClassDescriptor;

extern void func_ov107_020c9960(void);
extern void func_ov107_020c9a10(void);

GameClassDescriptor data_ov107_020cbaa4 = {
    16,  /* nClassId */
    11,  /* nGroupId */
    func_ov107_020c9960,  /* pfnCtor */
    func_ov107_020c9a10,  /* pfnMethod */
    144,  /* nAuxSize */
    0,  /* pArena */
};
