
#include <iostream>
#include <thread>

//#include "wraps.hpp"
#include "application.hpp"

     
// Programa Principal 
int main(int argc, char** argv)
{
     int time=0;

     Application app(argc,argv);
 
     app.exec();
     

     return 0;
}
