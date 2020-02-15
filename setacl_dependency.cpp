//
// Created by ra_watt on 2/12/20.
//
#include"setacl_dependency.h"
void isInitialised(std::string fileName){
  if(getxattr(fileName.c_str(),xattrName,NULL,0)==-1)initialise(fileName);
}

void initialise(std::string fileName){
  ACL acl(fileName);
  setxattr(fileName.c_str(),xattrName,&acl, sizeof(acl),XATTR_CREATE);
}
