//
// Created by ra_watt on 2/12/20.
//
#include "setacl_dependency.h"
int main(int argc, char* argv[]){
  ssize_t temp=getxattr("testfile",xattrName,NULL,0);
  char buff[temp];
  getxattr("testfile",xattrName,buff,temp);
  ACL acl;
  acl.deserialise(std::string(buff));
  acl.printACL();
}