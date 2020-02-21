//
// Created by ra_watt on 2/12/20.
//
#include "setacl_dependency.h"
int main(int argc, char* argv[]){

    int opt;
    bool file = false;
    std::string fileName;
    while ((opt = getopt(argc, argv, ":f:")) != -1) {
        switch (opt) {
            case 'f':
                file = true;
                fileName = std::string(optarg);
                break;
            case '?':
                std::cout << "-" << (char) optopt << " invalid option" << std::endl;
                break;
            case ':':
                std::cout << "argument required for option: -" << (char) optopt << std::endl;
                break;
        }
    }
//    if file is passed as a argument then check whether that file exist and
//    if that file exist then the uid of caller and uid of the file owner should be same
    if (file) {
        struct stat statbuff;
        if (stat(fileName.c_str(), &statbuff) == -1) {
            std::cout << strerror(errno) << std::endl;
            exit(-1);
        }
    }
    else {
        std::cout << "file name is required" << std::endl;
        exit(-1);
    }




    isInitialised(fileName);
  ssize_t temp=getxattr(fileName.c_str(),xattrName,NULL,0);
  char buff[temp];
  getxattr(fileName.c_str(),xattrName,buff,temp);
  ACL acl;
  acl.deserialise(std::string(buff));

  acl.printACL();
}