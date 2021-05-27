
#include "Session.h"
#include "Watchable.h"
//#include "../include/Session.h"
#include <sstream>

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

    string st, tmp;
    st = "split this into five words.";
    stringstream ss(st);
    vector<string> words;

    while(getline(ss, tmp, ' ')){
        words.push_back(tmp);
    }
    cout << words.size() << "\n";
    cout << words[0] << "\n";
    cout << words[words.size()-1];

    //TODO: currently giving code the path to json file manually!
    Session s("/home/aviv/CLionProjects/SPLFlix/config1.json");
    return 0;
}




/*
  ___ ___ _    ___ _ _     _
 / __| _ \ |  | __| (_)_ _| |
 \__ \  _/ |__| _|| | \ \ /_|
 |___/_| |____|_| |_|_/_\_(_)

 */