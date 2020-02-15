#include "setacl_dependency.h"


int main(int argc,char * argv[]) {
    int opt;
    bool extend = false, remove = false, removeAll = false, file = false;
    std::vector <std::string> extendEntry, removeEntry;
    std::string fileName;
    while ((opt = getopt(argc, argv, ":m:x:bf:")) != -1) {
        switch (opt) {
            case 'm':
                extend = true;
                extendEntry.push_back(optarg);
                break;
            case 'f':
                file = true;
                fileName = std::string(optarg);
                break;
            case 'x':
                remove = true;
                removeEntry.push_back(optarg);
                break;
            case 'b':
                removeAll = true;
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
        if (getuid() != statbuff.st_uid & getuid() != 0) {
            std::cout << "only owner of the file or root can change acl" << std::endl;
            exit(-1);
        }
    }
    else {
        std::cout << "file name is required" << std::endl;
        exit(-1);
    }

//    check if the file is initialised for acls
    isInitialised(fileName);


//if entries are to extended in the acl
    if (extend) {
        for (auto i:extendEntry) {
            std::cout << i << std::endl;
        }
    }

// if a particular entry is to be removed from the acl
    if (remove) {
        for (auto i: removeEntry) {
            std::cout << i << std::endl;
        }
    }

// if all the extended entries to be removed from the acl
    if (removeAll) {
        std::cout << "removeall\n";
    }

}