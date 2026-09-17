/* ov025 class descriptor data_ov025_020b49c4, 0x020b49c4-0x020b49d8 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  This one is the records scene task (class 8 / group 0xd, constructor Ov025_AllocContextAndGetHandler 02082960, method 02082998, 4-byte state); registered by the scene hook 02082b1c (02023930) with its handle kept in data_ov025_020b49c0.
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

extern void func_ov025_02082960(void);
extern void func_ov025_02082998(void);

GameClassDescriptor data_ov025_020b49c4 = {
    8,  /* nClassId */
    13,  /* nGroupId */
    func_ov025_02082960,  /* pfnCtor */
    func_ov025_02082998,  /* pfnMethod */
    4,  /* nAuxSize */
    0,  /* pArena */
};
