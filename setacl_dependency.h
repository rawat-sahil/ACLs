//
// Created by ra_watt on 2/12/20.
//

#ifndef SETACL_DEPENDENCY_H
#define SETACL_DEPENDENCY_H
#include "ACL.h"
#include<unistd.h>
#include <stdio.h>
#include<iostream>
#include<error.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/xattr.h>
#include<string.h>

#define xattrName "user.acl"
void initialise(std::string fileName);
void isInitialised(std::string fileName);


#endif //SETACL_DEPENDENCY_H
