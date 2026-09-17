/* NitroSystem g2di_BGManipulator.c: NNSiG2dBGCNTTable, the BGnCNT register of each of the eight
 * BGs (main 0-3, sub 0-3) by NNSG2dBGSelect. */
typedef volatile unsigned short REGType16v;

#define REG_BG0CNT_ADDR    0x04000008
#define REG_BG1CNT_ADDR    0x0400000a
#define REG_BG2CNT_ADDR    0x0400000c
#define REG_BG3CNT_ADDR    0x0400000e
#define REG_DB_BG0CNT_ADDR 0x04001008
#define REG_DB_BG1CNT_ADDR 0x0400100a
#define REG_DB_BG2CNT_ADDR 0x0400100c
#define REG_DB_BG3CNT_ADDR 0x0400100e

REGType16v *const data_02041ac0[8] = {
    (REGType16v *)REG_BG0CNT_ADDR, (REGType16v *)REG_BG1CNT_ADDR, (REGType16v *)REG_BG2CNT_ADDR, (REGType16v *)REG_BG3CNT_ADDR,
    (REGType16v *)REG_DB_BG0CNT_ADDR, (REGType16v *)REG_DB_BG1CNT_ADDR, (REGType16v *)REG_DB_BG2CNT_ADDR, (REGType16v *)REG_DB_BG3CNT_ADDR
};
