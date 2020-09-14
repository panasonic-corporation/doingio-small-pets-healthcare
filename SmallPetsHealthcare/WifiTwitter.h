/*
  Twitter.cpp - Arduino library to Post messages to Twitter.
  Copyright (c) NeoCat 2009. All right reserved.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/

#ifndef WIFITWITTER_H
#define WIFITWITTER_H

#include <WiFiClientSecure.h>

// クラスの定義
class WifiTwitter
{
private:
  WiFiClientSecure client;
  const char *m_cpToken;
  uint8_t m_uParseSts;
  int m_iStsCode;
public:
  WifiTwitter( const char *user_and_passwd);
  bool post( const char *msg );
  bool checkStatus( void );
  int  wait( void );
};

#endif /* WIFITWITTER_H */
