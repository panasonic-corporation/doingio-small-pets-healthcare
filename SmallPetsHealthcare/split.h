static int isDelimiter(char p, char delim){
    return p == delim;
}

static int split(char *dst[], char *src, char delim){
  int count = 0;
  for(;;) {
    while (isDelimiter(*src, delim)){
      src++;
    }
    if (*src == '\0') break;
    dst[count++] = src;
    while (*src && !isDelimiter(*src, delim)) {
      src++;
    }
    if (*src == '\0') break;
    *src++ = '\0';
  }
  return count;
}
