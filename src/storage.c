//
//  storage.c
//  alarms++
//
//  Created by Christian Reinbacher on 02.11.14.
//
//

#include "storage.h"
#include "debug.h"

void load_persistent_storage_alarms(Alarm *alarms)
{
#ifdef PBL_PLATFORM_APLITE
  for(int i=0;i<NUM_ALARMS/8;i++) { // we can only store 8 alarms in one memory slot
    if (persist_exists(ALARMS_KEY+i)) {
      persist_read_data(ALARMS_KEY+i,&alarms[8*i],8*sizeof(Alarm));
    }
    else {
      for (int j=0; j<8; j++) {
        alarm_reset(&alarms[8*i+j]);
      }
    }
  }
#else
  // Perform migration
  if(persist_exists(ALARMS_OLD_KEY)) {
    Alarm_old temp_alarms[8];
    for(int i=0;i<NUM_ALARMS/8;i++) { // we can only store 8 alarms in one memory slot on aplite
      persist_read_data(ALARMS_OLD_KEY+i,temp_alarms,8*sizeof(Alarm_old));
      persist_delete(ALARMS_OLD_KEY+i);
      for (int j=0; j<8; j++) {
        alarms[8*i+j].alarm_id = temp_alarms[j].alarm_id;
        alarms[8*i+j].enabled = temp_alarms[j].enabled;
        alarms[8*i+j].hour = temp_alarms[j].hour;
        alarms[8*i+j].minute = temp_alarms[j].minute;
        alarms[8*i+j].smart_alarm_minutes = 0;
        for (int w=0; w<7; w++) {
          alarms[8*i+j].weekdays_active[w] = temp_alarms[j].weekdays_active[w];
        }
        strncpy(temp_alarms[j].description,alarms[8*i].description,8);
      }
    }
  } else {
    for(int i=0;i<NUM_ALARMS/4;i++) { // we can only store 4 alarms in one memory slot on other platforms
      if (persist_exists(ALARMS_KEY+i)) {
        persist_read_data(ALARMS_KEY+i,&alarms[4*i],4*sizeof(Alarm));
      }
      else {
        for (int j=0; j<4; j++) {
          alarm_reset(&alarms[4*i+j]);
        }
      }
    }
  }
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Size of one alarm struct: %d",sizeof(Alarm));
#endif
  // One-time migration: unused slots saved with the old default (all weekdays)
  // become one-time alarms, matching the new default in alarm_reset.
  if (!persist_exists(ONE_TIME_DEFAULT_MIGRATED_KEY)) {
    for (int i=0; i<NUM_ALARMS; i++) {
      Alarm *alarm = &alarms[i];
      bool all_days = true;
      for (int w=0; w<7; w++)
        all_days = all_days && alarm->weekdays_active[w];
      if (all_days && !alarm->enabled && alarm->hour==0 && alarm->minute==0 &&
          alarm->description[0]==0) {
        for (int w=0; w<7; w++)
          alarm->weekdays_active[w] = false;
      }
    }
    write_persistent_storage_alarms(alarms);
    persist_write_bool(ONE_TIME_DEFAULT_MIGRATED_KEY, true);
  }
}

void write_persistent_storage_alarms(Alarm *alarms)
{
#ifdef PBL_PLATFORM_APLITE
  for(int i=0;i<NUM_ALARMS/8;i++) // we can only store 8 alarms in one memory slot on aplite
    persist_write_data(ALARMS_KEY+i,&alarms[8*i],8*sizeof(Alarm));
#else
  for(int i=0;i<NUM_ALARMS/4;i++) // we can only store 4 alarms in one memory slot on other platforms
  persist_write_data(ALARMS_KEY+i,&alarms[4*i],4*sizeof(Alarm));
#endif
}

bool load_persistent_storage_bool(int key, bool default_val)
{
  bool temp = default_val;
  if(persist_exists(key))
    temp = persist_read_bool(key);
  return temp;
}
int load_persistent_storage_int(int key, int default_val)
{
  int temp = default_val;
  if(persist_exists(key))
    temp = persist_read_bool(key);
  return temp;
}
