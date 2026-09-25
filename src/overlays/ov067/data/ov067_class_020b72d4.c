/* ov067 class descriptor data_ov067_020b72d4, 0x020b72d4-0x020b72e8 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020b5a34, method 020b5a5c, 0x2fa0-byte state.
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

extern void func_ov067_020b5a34(void);
extern void func_ov067_020b5a5c(void);

GameClassDescriptor data_ov067_020b72d4 = {
    10,  /* nClassId */
    6,  /* nGroupId */
    func_ov067_020b5a34,  /* pfnCtor */
    func_ov067_020b5a5c,  /* pfnMethod */
    12192,  /* nAuxSize */
    0,  /* pArena */
};
