#include <iostream>
#include "Session.h"
using namespace std;

int main(int argc, char** argv){
    /*
    if(argc!=2)
    {
        cout << "usage splflix input_file" << endl;
        return 0;
    }
     */
    //Session s(argv[1]);
    Session s("home/aviv/CLionProjects/SPLFlix/config1.json");
    s.start();
    return 0;
}