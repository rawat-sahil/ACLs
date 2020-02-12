//
// Created by ra_watt on 2/12/20.
//

#ifndef ACL_H
#define ACL_H
#include<vector>
#include<utility>
#include<string>
#include<map>
std::map<int,std::string> intToPermissions={{0,"---"},{1,"--x"},{2,"-w-"},{3,"-wx"},{4,"r--"},{5,"r-x"},{6,"rw-"},{7,"rwx"}};
std::map<std::string,int> permissionsToString={{"---",0},{"--x",1},{"-w-",2},{"-wx",3},{"r--",4},{"r-x",5},{"rw-",6},{"rwx",7}};
class ACL {
    std::string fileName;
    std::string Owner;
    std::string group;
    std::vector<std::pair<std::string,int>> user;
    std::vector<std::pair<std::string,int>> groups;
    int others;
    int mask;
};


#endif //SE_ASSIGNMENT_ACL_H
