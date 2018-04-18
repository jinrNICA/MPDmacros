#include "PicoDstPidReader.cxx"

int main()
{
  PicoDstPidReader* t = new PicoDstPidReader();
  t->Loop();
  
  return 0;
}
