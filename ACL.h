//
// Created by ra_watt on 2/12/20.
//

#ifndef ACL_H
#define ACL_H
#include<vector>
#include<utility>
#include<string>
#include<map>
#include<iostream>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include<sys/types.h>
#include<sys/xattr.h>

class ACL {
public:
    std::map<int,std::string> intToPermissions={
        {0,"---"},
        {1,"--x"},
        {2,"-w-"},
        {3,"-wx"},
        {4,"r--"},
        {5,"r-x"},
        {6,"rw-"},
        {7,"rwx"}};
    std::map<std::string,int> permissionsToint={
        {"---",0},
        {"--x",1},
        {"-w-",2},
        {"-wx",3},
        {"r--",4},
        {"r-x",5},
        {"rw-",6},
        {"rwx",7}};
    std::string FileName;
    std::string Owner;
    std::string group;
    std::vector<std::pair<std::string,int>> user;
    std::vector<std::pair<std::string,int>> groups;
    int others;
    int mask;
public:
    ACL();
    ACL(std::string fileName);
    void printACL();
    std::string serialise();
    void deserialise(std::string attrList);

};


#endif //ACL_H
