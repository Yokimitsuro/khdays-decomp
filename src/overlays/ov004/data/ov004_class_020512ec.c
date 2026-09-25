/* ov004 class descriptor data_ov004_020512ec, 0x020512ec-0x02051300 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 02050174, method 0205023c, 0x5618-byte state.
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

extern void func_ov004_02050174(void);
extern void func_ov004_0205023c(void);

GameClassDescriptor data_ov004_020512ec = {
    8,  /* nClassId */
    14,  /* nGroupId */
    func_ov004_02050174,  /* pfnCtor */
    func_ov004_0205023c,  /* pfnMethod */
    22040,  /* nAuxSize */
    0,  /* pArena */
};
