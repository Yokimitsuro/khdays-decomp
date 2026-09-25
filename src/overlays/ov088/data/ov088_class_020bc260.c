/* ov088 class descriptor data_ov088_020bc260, 0x020bc260-0x020bc274 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020ba7d4, method 020ba7fc, 0x2f40-byte state.
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

extern void func_ov088_020ba7d4(void);
extern void func_ov088_020ba7fc(void);

GameClassDescriptor data_ov088_020bc260 = {
    10,  /* nClassId */
    6,  /* nGroupId */
    func_ov088_020ba7d4,  /* pfnCtor */
    func_ov088_020ba7fc,  /* pfnMethod */
    12096,  /* nAuxSize */
    0,  /* pArena */
};
