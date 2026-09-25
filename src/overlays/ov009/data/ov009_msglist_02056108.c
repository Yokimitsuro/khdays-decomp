/* ov009 .rodata 0x02056108-0x02056114: message-list initialiser. */

/* Message-list set initialiser: the language-templated message archive path
 * ("UI/cm/msl_&.msi.z", '&' = language code), a start index and the list capacity. */
typedef struct MsgListInit {
    const char *pszArchive;  /* 0x00 */
    int nFirst;              /* 0x04 */
    int nCapacity;           /* 0x08 */
} MsgListInit;

extern char data_ov009_020563b4;  /* "UI/cm/msl_&.msi.z" */

/* Read by func_ov009_020557dc. */
const MsgListInit data_ov009_02056108 = { &data_ov009_020563b4, 0, 5 };
