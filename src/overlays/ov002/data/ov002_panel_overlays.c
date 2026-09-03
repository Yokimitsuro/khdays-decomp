/* ov002 panel overlay table, 0x0207f590-0x0207f600.
 *
 * Fourteen {data, overlay id} entries read by ov002_SwitchPanelOverlay, one per panel
 * slot. The pointer reaches the panel overlay's own data block and the id is the
 * overlay to load; -1 marks a slot with no overlay, and a null pointer marks one whose
 * data is not resident.
 */

typedef struct {
    void *pData;
    int nOverlayId;
} Ov002PanelOverlay;

extern int data_ov013_0207fec8;
extern int data_ov014_020808e0;
extern int data_ov019_0207fd60;
extern int data_ov016_020826e0;
extern int data_ov020_020800c0;
extern int data_ov015_02082904;
extern int data_ov017_02080e40;
extern int data_ov018_0207fa60;
extern int data_ov021_02080f20;

Ov002PanelOverlay data_ov002_0207f590[14] = {
    { &data_ov013_0207fec8, 14 },
    { &data_ov014_020808e0, 19 },
    { &data_ov019_0207fd60, 16 },
    { &data_ov016_020826e0, 20 },
    { &data_ov020_020800c0, 15 },
    { &data_ov015_02082904, -1 },
    { 0, -1 },
    { 0, 17 },
    { &data_ov017_02080e40, -1 },
    { 0, -1 },
    { 0, 18 },
    { &data_ov018_0207fa60, 21 },
    { &data_ov021_02080f20, 0 },
    { 0, 0 },
};
