/* ov023 class descriptor data_ov023_0208a748, 0x0208a748-0x0208a75c (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020896b8, method 020896f0, 0x84-byte state.
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

extern void func_ov023_020896b8(void);
extern void func_ov023_020896f0(void);

GameClassDescriptor data_ov023_0208a748 = {
    62,  /* nClassId */
    13,  /* nGroupId */
    func_ov023_020896b8,  /* pfnCtor */
    func_ov023_020896f0,  /* pfnMethod */
    132,  /* nAuxSize */
    0,  /* pArena */
};
