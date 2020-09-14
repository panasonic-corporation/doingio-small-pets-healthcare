#include "DateDataController.h"

#include "split.h"


void DateDataController::setup(DayDataModel *_nowDayDataRef, DisplayDataModel *_dateDataRef)
{
    nowDayDataRef = _nowDayDataRef;
    dateDataRef = _dateDataRef;
    today();
}


void DateDataController::nextDate()
{
    if(dateDataRef->isToday == true) return;

    struct tm  tinfo = nowDayDataRef->nowtimeInfo;
    tinfo.tm_hour = 0;
    tinfo.tm_min = 0;
    tinfo.tm_sec = 0;
    time_t ntime = mktime(&tinfo); 

    struct tm  dinfo = dateDataRef -> displayDate;
    dinfo.tm_hour = 0;
    dinfo.tm_min = 0;
    dinfo.tm_sec = 0;
    time_t dtime = mktime(&dinfo);


    dtime += 24 * 60 * 60;
    dateDataRef -> displayDate = *localtime(&dtime);

    if(dtime == ntime)
    {
        today();
        return;
    }else{
        dateDataRef->isToday = false;
    }
    
    if(dateDataRef -> displayDate.tm_wday == 0)
    {
        time_t mintime = ntime - tinfo.tm_wday * 24 * 60 * 60;
        time_t maxtime = ntime + (6 - tinfo.tm_wday) * 24 * 60 * 60;
        if(dtime >= mintime && dtime <= maxtime)
        {
            dateDataRef -> isLatestWeek = true;
        }else{
            dateDataRef -> isLatestWeek = false;
        }

        weekSeek(true); 
    }
}

void DateDataController::prevDate()
{

    struct tm  tinfo = nowDayDataRef->nowtimeInfo;
    tinfo.tm_hour = 0;
    tinfo.tm_min = 0;
    tinfo.tm_sec = 0;
    time_t ntime = mktime(&tinfo); 


    struct tm  dinfo = dateDataRef -> displayDate;
    dinfo.tm_hour = 0;
    dinfo.tm_min = 0;
    dinfo.tm_sec = 0;

    time_t dtime = mktime(&dinfo);

    dtime -= 24 * 60 * 60;
    dateDataRef -> displayDate = *localtime(&dtime);

    time_t dt = mktime(&dateDataRef -> displayDate); 
    time_t nt = mktime(&tinfo); 

    if(dtime == ntime)
    {
        today();
        return;
    }else{
        dateDataRef->isToday = false;
    }

    if(dateDataRef -> displayDate.tm_wday == 6)
    {
        time_t mintime = ntime - tinfo.tm_wday * 24 * 60 * 60;
        time_t maxtime = ntime + (6 - tinfo.tm_wday) * 24 * 60 * 60;
        if(dtime >= mintime && dtime <= maxtime)
        {
            dateDataRef -> isLatestWeek = true;
        }else{
            dateDataRef -> isLatestWeek = false;
        }

        weekSeek(); 
    }

    
}

void DateDataController::today()
{
    loadLogData();

    dateDataRef -> displayDate.tm_year = nowDayDataRef -> nowtimeInfo.tm_year;
    dateDataRef -> displayDate.tm_mon = nowDayDataRef -> nowtimeInfo.tm_mon;
    dateDataRef -> displayDate.tm_mday = nowDayDataRef -> nowtimeInfo.tm_mday;
    dateDataRef -> displayDate.tm_wday = nowDayDataRef -> nowtimeInfo.tm_wday;
    dateDataRef -> displayDate.tm_hour = 0;
    dateDataRef -> displayDate.tm_min = 0;
    dateDataRef -> displayDate.tm_sec = 0;
    dateDataRef -> isToday = true;
    dateDataRef -> isLatestWeek = true;

    logData.seek = 0;
    weekSeek();
}


void DateDataController::weekSeek(bool isUpSeek)
{
    for(int i = 0; i < 7; i++ )
    {
        memset(&dateDataRef->displayWeekly[i].nowtimeInfo, 0, sizeof(struct tm));
        dateDataRef->displayWeekly[i].sensorsValue[0] = SENSOR_VALUE_NULL;
        dateDataRef->displayWeekly[i].sensorsValue[1] = SENSOR_VALUE_NULL;
        dateDataRef->displayWeekly[i].sensorsValue[2] = SENSOR_VALUE_NULL;
        dateDataRef->displayWeekly[i].sensorsValue[3] = SENSOR_VALUE_NULL;
        dateDataRef->displayWeekly[i].sensorsValue[4] = SENSOR_VALUE_NULL;
        dateDataRef->displayWeekly[i].sensorsValue[5] = SENSOR_VALUE_NULL;
        dateDataRef->displayWeekly[i].isCheck = false;
    }


    int pday = 7;
    if(dateDataRef -> isLatestWeek)
    {
        pday = nowDayDataRef->nowtimeInfo.tm_wday+1;
        
    }

    struct tm ddinfo;
    memset(&ddinfo, 0, sizeof(struct tm));
    ddinfo.tm_year = dateDataRef->displayDate.tm_year;
    ddinfo.tm_mon = dateDataRef->displayDate.tm_mon;
    ddinfo.tm_mday = dateDataRef->displayDate.tm_mday;
    time_t dd = mktime(&ddinfo);

    if(logData.len <= 0) return;

    if(isUpSeek)
    {
        for(int i = 0; i < pday; i++ )
        {
            dateDataRef->displayWeekly[i].nowtimeInfo = *localtime(&dd);
            dd += 24 * 60 * 60;
        }

        for(; logData.seek>=0; logData.seek--)
        {
            Serial.print("seek");
            Serial.println(logData.seek);

            struct tm  tinfo;
            memset(&tinfo, 0, sizeof(struct tm));
            tinfo.tm_year = logData.log[logData.seek].nowtimeInfo.tm_year;
            tinfo.tm_mon = logData.log[logData.seek].nowtimeInfo.tm_mon;
            tinfo.tm_mday = logData.log[logData.seek].nowtimeInfo.tm_mday;
            time_t ttime = mktime(&tinfo);

            time_t wt;

              for(int i= 0; i < pday; i++ )
            { 
                wt = mktime(&dateDataRef->displayWeekly[i].nowtimeInfo);

                if(ttime == wt)
                { 
                    dateDataRef->displayWeekly[i].isCheck = true;
                    dateDataRef->displayWeekly[i].sensorsValue[0] = logData.log[logData.seek].sensorsValue[0];
                    dateDataRef->displayWeekly[i].sensorsValue[1] = logData.log[logData.seek].sensorsValue[1];
                    dateDataRef->displayWeekly[i].sensorsValue[2] = logData.log[logData.seek].sensorsValue[2];
                    dateDataRef->displayWeekly[i].sensorsValue[3] = logData.log[logData.seek].sensorsValue[3];
                    dateDataRef->displayWeekly[i].sensorsValue[4] = logData.log[logData.seek].sensorsValue[4];
                    dateDataRef->displayWeekly[i].sensorsValue[5] = logData.log[logData.seek].sensorsValue[5];
                    break;
                }
            }

            if(ttime > wt) 
            {
                Serial.println("over");
                break;
            }
            int c = 0;
            for(int i=0; i < pday; i++ )
            {
                if(dateDataRef->displayWeekly[i].isCheck ) c++;
            }
            if(c >= pday)
            {
                Serial.println("allset");
                break; 
            }

        }


    }else
    {
        
        for(int i= pday-1; i >= 0; i-- )
        {
            dateDataRef->displayWeekly[i].nowtimeInfo = *localtime(&dd);
            dd -= 24 * 60 * 60;
        }

        for(; logData.seek <= logData.len; logData.seek++)
        {

            struct tm  tinfo;
            memset(&tinfo, 0, sizeof(struct tm));
            tinfo.tm_year = (logData.log[logData.seek].nowtimeInfo.tm_year);
            tinfo.tm_mon = (logData.log[logData.seek].nowtimeInfo.tm_mon);
            tinfo.tm_mday = (logData.log[logData.seek].nowtimeInfo.tm_mday);

            time_t ttime = mktime(&tinfo);

            time_t wt;

            for(int i= pday-1; i >= 0; i-- )
            { 
                wt = mktime(&dateDataRef->displayWeekly[i].nowtimeInfo);
    
                if(ttime == wt)
                { 
                    dateDataRef->displayWeekly[i].isCheck = true;
                    dateDataRef->displayWeekly[i].sensorsValue[0] = logData.log[logData.seek].sensorsValue[0];
                    dateDataRef->displayWeekly[i].sensorsValue[1] = logData.log[logData.seek].sensorsValue[1];
                    dateDataRef->displayWeekly[i].sensorsValue[2] = logData.log[logData.seek].sensorsValue[2];
                    dateDataRef->displayWeekly[i].sensorsValue[3] = logData.log[logData.seek].sensorsValue[3];
                    dateDataRef->displayWeekly[i].sensorsValue[4] = logData.log[logData.seek].sensorsValue[4];
                    dateDataRef->displayWeekly[i].sensorsValue[5] = logData.log[logData.seek].sensorsValue[5];
                    break;
                }
            }



            if(ttime < wt) break;

            int c = 0;
            for(int i= pday-1; i >= 0; i-- )
            {
                if(dateDataRef->displayWeekly[i].isCheck ) c++;
            }
            if(c >= pday)
            {
                break; 
            }
          

        }



        
    }

    if(logData.seek > logData.len) logData.seek = logData.len;
    if(logData.seek < 0) logData.seek = 0;
    

}


void DateDataController::saveLogData()
{
    struct tm  tinfo;
    memset(&tinfo, 0, sizeof(struct tm));
    tinfo.tm_year = nowDayDataRef->nowtimeInfo.tm_year;
    tinfo.tm_mon = nowDayDataRef->nowtimeInfo.tm_mon;
    tinfo.tm_mday = nowDayDataRef->nowtimeInfo.tm_mday;
    time_t ntime = mktime(&tinfo); 
    ntime -= 24*60*60;
    tinfo = *localtime(&ntime);

    char buf[128];
    sprintf(buf, "%04d/%02d/%02d,", tinfo.tm_year+1900, tinfo.tm_mon+1, tinfo.tm_mday);
    
    String str = buf;
    
    for(int i = 0; i < 6; i++) {
        str += nowDayDataRef->sensorsValue[i];
        if(i<(6-1))
        {
            str += ",";
        }
    }
    Serial.print("save: ");
    Serial.println(str);

    if(!SD.exists(LOG_PATH))
    {
        str = "DATE,CH1,CH2,CH3,CH4,CH5,CH6\n" + str;
    }

    File file = SD.open(LOG_PATH, FILE_APPEND);
    file.println(str);
    file.close();

}

void DateDataController::loadLogData()
{
    Serial.println("loadLogData");
    logData.len = 0;

    CSV_Parser cp("sffffff");
    File file = SD.open(LOG_PATH);
    if (file) {
        while(file.available()) {
            cp << file.read();
        }
        file.close();

        logData.len = cp.getRowsCount();
        int len = logData.len;

        Serial.print("log len: ");    
        Serial.println(len);

        int c = 0;
        for(int i = len-1; i >= 0; i--)
        {
            char str[16];
            strcpy(str, ((char**)cp[0])[i]);
            
            char *dst[8];
            int count = split(dst, str, '/');
            if(count < 3)
            {
                Serial.print("date error: ");
                Serial.println(str);
                continue;
            } 

            struct tm  tinfo;
            memset(&tinfo, 0, sizeof(struct tm));
            tinfo.tm_year = (atoi(dst[0]) - 1900);
            tinfo.tm_mon = (atoi(dst[1]) - 1);
            tinfo.tm_mday = (atoi(dst[2]));

            logData.log[c].nowtimeInfo = tinfo;
            logData.log[c].sensorsValue[0] = ((float*)cp[1])[i];
            logData.log[c].sensorsValue[1] = ((float*)cp[2])[i];
            logData.log[c].sensorsValue[2] = ((float*)cp[3])[i];
            logData.log[c].sensorsValue[3] = ((float*)cp[4])[i];
            logData.log[c].sensorsValue[4] = ((float*)cp[5])[i];
            logData.log[c].sensorsValue[5] = ((float*)cp[6])[i];

            c++;
            if(c >200) break;
        }
    }
    else {
        M5.Lcd.println("File open error");
    }
}
