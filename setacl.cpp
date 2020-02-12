#include"ACL.h"
#include<unistd.h>
#include<iostream>
int main(int argc,char * argv[]){
    int opt;
    bool extend=false,remove=false,removeAll=false,file=false;
    std::vector<std:: string> extendEntry,removeEntry;
    std::string fileName;
    while((opt=getopt(argc,argv,":m:x:bf:"))!=-1){
        switch(opt){
            case 'm':
                extend=true;
                extendEntry.push_back(optarg);
                break;
            case 'f':
                file=true;
                fileName=optarg;
                break;
            case 'x':
                remove=true;
                removeEntry.push_back(optarg);
                break;
            case 'b':
                removeAll=true;
                break;
            case '?':
                std::cout<<"-"<<(char)optopt<<" invalid option"<<std::endl;
                break;
            case ':':
                std::cout<<"argument required for option: -"<<(char)optopt<<std::endl;
                break;
        }
    }

    if(extend){
        for(auto i:extendEntry){
            std::cout<<i<<std::endl;
        }
    }
    if(remove){
        for(auto i: removeEntry){
        std::cout<<i<<std::endl;
        }
    }
    if(removeAll){
        std::cout<<"removeall\n";
    }
    if(file){
        std::cout<<fileName<<std::endl;
    }
    
}