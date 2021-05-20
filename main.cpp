
#include "Session.h"
#include "Watchable.h"
//#include "../include/Session.h"

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
    //TO DO: currently giving code the path to json file manually!

    //test section
    vector<string> vec{"tag1", "tag2", "tag333"};
    Movie m = Movie(123, "nameee", 24, vec);
    cout << m.toString() << endl;


    Session s("home/aviv/CLionProjects/SPLFlix/config1.json");
    s.start();
    return 0;
}