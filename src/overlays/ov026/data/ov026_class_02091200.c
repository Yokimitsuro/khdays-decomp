/* ov026 class descriptor data_ov026_02091200, 0x02091200-0x02091214 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 02082960, method 020829a0, 0xc-byte state.
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

extern void func_ov026_02082960(void);
extern void func_ov026_020829a0(void);

GameClassDescriptor data_ov026_02091200 = {
    8,  /* nClassId */
    13,  /* nGroupId */
    func_ov026_02082960,  /* pfnCtor */
    func_ov026_020829a0,  /* pfnMethod */
    12,  /* nAuxSize */
    0,  /* pArena */
};
