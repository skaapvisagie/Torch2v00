#ifndef BAT_STATUS
#define BAT_STATUS

#define BATSTAT_BAT_STAT_UNKNOWN  0x00
#define BATSTAT_BAT_OK            0x01
#define BATSTAT_BAT_LOW           0x02
#define BATSTAT_BAT_DEAD          0x03        

void BATSTAT_updateBatStatus(void);

uint8_t BATSTAT_batStatus(void);

#endif
