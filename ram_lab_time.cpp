#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

long getCurrentTime()
{
   struct timeval tv;
   gettimeofday(&tv,NULL);
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

string ltos(long l)
{
    ostringstream os;
    os<<l;
    string result;
    istringstream is(os.str());
    is>>result;
    return result;

}

int main()
{
    cout<<ltos(getCurrentTime())<<endl;
    usleep(1000);
    cout<<ltos(getCurrentTime())<<endl;
    return 0;
}
