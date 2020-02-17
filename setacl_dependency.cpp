//
// Created by ra_watt on 2/12/20.
//
#include"setacl_dependency.h"
void isInitialised(std::string fileName){
  if(getxattr(fileName.c_str(),xattrName,NULL,0)==-1){
    initialise(fileName);
  }
}

void initialise(std::string fileName){
  ACL acl(fileName);
  std::string temp=acl.serialise();
  std::cout<<temp<<std::endl;
  setxattr(fileName.c_str(),xattrName,temp.c_str(), strlen(temp.c_str()),XATTR_CREATE);
}
