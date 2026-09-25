/* ov089 class descriptor data_ov089_020bc0a0, 0x020bc0a0-0x020bc0b4 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020ba7d4, method 020ba7fc, 0x33a4-byte state.
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

extern void func_ov089_020ba7d4(void);
extern void func_ov089_020ba7fc(void);

GameClassDescriptor data_ov089_020bc0a0 = {
    10,  /* nClassId */
    6,  /* nGroupId */
    func_ov089_020ba7d4,  /* pfnCtor */
    func_ov089_020ba7fc,  /* pfnMethod */
    13220,  /* nAuxSize */
    0,  /* pArena */
};
