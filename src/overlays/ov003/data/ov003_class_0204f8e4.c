/* ov003 class descriptor data_ov003_0204f8e4, 0x0204f8e4-0x0204f8f8 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 0204d98c, method 0204e384, 0x1e18-byte state.
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

extern void func_ov003_0204d98c(void);
extern void func_ov003_0204e384(void);

GameClassDescriptor data_ov003_0204f8e4 = {
    8,  /* nClassId */
    15,  /* nGroupId */
    func_ov003_0204d98c,  /* pfnCtor */
    func_ov003_0204e384,  /* pfnMethod */
    7704,  /* nAuxSize */
    0,  /* pArena */
};
