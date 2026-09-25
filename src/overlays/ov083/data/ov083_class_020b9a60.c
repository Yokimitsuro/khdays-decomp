/* ov083 class descriptor data_ov083_020b9a60, 0x020b9a60-0x020b9a74 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020b8114, method 020b813c, 0x3074-byte state.
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

extern void func_ov083_020b8114(void);
extern void func_ov083_020b813c(void);

GameClassDescriptor data_ov083_020b9a60 = {
    10,  /* nClassId */
    6,  /* nGroupId */
    func_ov083_020b8114,  /* pfnCtor */
    func_ov083_020b813c,  /* pfnMethod */
    12404,  /* nAuxSize */
    0,  /* pArena */
};
