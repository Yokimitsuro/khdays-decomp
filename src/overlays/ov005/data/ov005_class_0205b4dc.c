/* ov005 class descriptor data_ov005_0205b4dc, 0x0205b4dc-0x0205b4f0 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020515dc, method 020516b4, 0x14-byte state.
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

extern void func_ov005_020515dc(void);
extern void func_ov005_020516b4(void);

GameClassDescriptor data_ov005_0205b4dc = {
    8,  /* nClassId */
    15,  /* nGroupId */
    func_ov005_020515dc,  /* pfnCtor */
    func_ov005_020516b4,  /* pfnMethod */
    20,  /* nAuxSize */
    0,  /* pArena */
};
