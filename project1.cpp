#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <conio.h>
namespace fs = std::filesystem;
using namespace std;

//GLOBAL VARIABLES
fs::path curr_dir = "C:/" ;
string comm_line = "";

//Non member Functions
void start(){
    cout <<"{Kaustav}"<<curr_dir << ">>>";
}

string input(){
    while(true){

        char ch = _getch();
        switch(ch){
            case '\r':
                return "enter";
                break;
            case '\t':
                return "tab";
            case '\b':
                if (!comm_line.empty())
                {
                    comm_line.pop_back();   
                    cout << "\b \b";        
                }
                continue;
            default:
                comm_line += ch;
                cout << ch;
        }
    }
    return 0;
}

void comm_reader(string &str){

    int sep_index = str.find(";");
    string comm = str.substr(0, sep_index + 1);
    string phrase = str.substr(sep_index + 1);
    if (comm == "cd;")
    {
        if(phrase.empty()){
            ::curr_dir = "C:/";
        }
        else{
            fs::path new_dir = phrase;
            try{
                if (fs::exists(new_dir) && fs::is_directory(new_dir)){
                ::curr_dir = new_dir;
                }
                else{
                    cout << "!!!!ENTER A VALID EXISTING DIRECTORY!!!!" << endl;
                }
            }
            catch(const fs::filesystem_error& e){
                cout << e.what() << endl;
            }            
        }
    }
    else if (comm == "ls;")
    {
        for(const auto& entry : fs::directory_iterator(curr_dir))
        {
            cout << entry.path().filename()<<"\t";
        }
        cout << endl;
    }
}


int main(){

while(true){
    start();
    ::comm_line.clear();
    string key = input();
    if(key=="enter"){
        cout << endl;
        comm_reader(::comm_line);
        continue;
    }
    else if(key=="tab"){
        break;
    }
}


    return 0;
}