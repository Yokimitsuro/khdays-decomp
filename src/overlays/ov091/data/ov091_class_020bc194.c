/* ov091 class descriptor data_ov091_020bc194, 0x020bc194-0x020bc1a8 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020ba7d4, method 020ba804, 0x2e1c-byte state.
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

extern void func_ov091_020ba7d4(void);
extern void func_ov091_020ba804(void);

GameClassDescriptor data_ov091_020bc194 = {
    10,  /* nClassId */
    6,  /* nGroupId */
    func_ov091_020ba7d4,  /* pfnCtor */
    func_ov091_020ba804,  /* pfnMethod */
    11804,  /* nAuxSize */
    0,  /* pArena */
};
