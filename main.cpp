
#include "Session.h"
#include "Watchable.h"

//#include "../include/Session.h"
#include <sstream>
#include <unistd.h>


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

    string path = get_current_dir_name();
    path = path.substr(0, path.size() - 17); //17: cmake/-build-debug
    string input;
    cout << "Enter the name of the config file: ";
    cin >> input;
    path.append(input);
    //cout << path << endl;
    //clearInput:
    cin.clear();
    int c;
    while ( (c=getchar()) != '\n' && c != EOF ){;}

    Session s(path);
    //Session s("/home/aviv/CLionProjects/SPLFlix/config1.json");
    return 0;
}




/*
  ___ ___ _    ___ _ _     _
 / __| _ \ |  | __| (_)_ _| |
 \__ \  _/ |__| _|| | \ \ /_|
 |___/_| |____|_| |_|_/_\_(_)

 */