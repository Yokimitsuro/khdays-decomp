/* ov005 .rodata 0x0205b3bc-0x0205b3c8: message-list initialiser. */

/* Message-list set initialiser: the language-templated message archive path
 * ("UI/cm/msl_&.msi.z", '&' = language code), a start index and the list capacity. */
typedef struct MsgListInit {
    const char *pszArchive;  /* 0x00 */
    int nFirst;              /* 0x04 */
    int nCapacity;           /* 0x08 */
} MsgListInit;

extern char data_ov005_0205b788;  /* "UI/cm/msl_&.msi.z" */

/* Read by func_ov005_020584a8. */
const MsgListInit data_ov005_0205b3bc = { &data_ov005_0205b788, 0, 5 };
