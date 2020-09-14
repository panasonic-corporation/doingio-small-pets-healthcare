/*
  Twitter.cpp - Arduino library to Post messages to Twitter.
  Copyright (c) NeoCat 2009. All right reserved.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 */

#include "WifiTwitter.h"

#define LIB_DOMAIN "arduino-tweet.appspot.com"

WifiTwitter::WifiTwitter( const char *cpToken )
{
  m_cpToken = cpToken;
}

bool WifiTwitter::post(const char *cpMsg)
{
  bool abRet;
  
  if (client.connect(LIB_DOMAIN, 443))
  {
    client.println("POST http://" LIB_DOMAIN "/update HTTP/1.1");
    client.print("Content-Length: ");
    client.println(strlen(cpMsg)+strlen(m_cpToken)+14);
    client.println("Host: " LIB_DOMAIN);
    client.println("Connection: close");
    client.println();
    client.print("token=");
    client.print(m_cpToken);
    client.print("&status=");
    client.println(cpMsg);
    abRet = true;
  }
  else
  {
    abRet =  false;
  }

  return abRet;
}

bool WifiTwitter::checkStatus(void)
{
  if (!client.connected()) {
    client.flush();
    client.stop();
    return false;
  }
  if (!client.available())
    return true;
  char c = client.read();
  switch(m_uParseSts) {
  case 0:
    if (c == ' ') m_uParseSts++; break;  // skip "HTTP/1.1 "
  case 1:
    if (c >= '0' && c <= '9') {
      m_iStsCode *= 10;
      m_iStsCode += c - '0';
    } else {
      m_uParseSts++;
    }
  }
  return true;
}

int WifiTwitter::wait( void )
{
  while (checkStatus());
  return m_iStsCode;
}
