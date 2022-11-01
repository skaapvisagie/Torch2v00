#ifndef BAT_STATUS
#define BAT_STATUS

#define BATSTAT_BAT_STAT_UNKNOWN  0x00u
#define BATSTAT_BAT_OK            0x01u
#define BATSTAT_BAT_LOW           0x02u
#define BATSTAT_BAT_DEAD          0x03u       

void BATSTAT_updateBatStatus(void);

uint8_t BATSTAT_batStatus(void);

#endif
