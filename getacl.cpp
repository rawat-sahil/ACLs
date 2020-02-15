//
// Created by ra_watt on 2/12/20.
//
#include "setacl_dependency.h"
int main(){
  ssize_t temp=getxattr("testfile",xattrName,NULL,0);
  ACL * acl=(ACL *)malloc((long)temp);
  getxattr("testfile",xattrName,(acl),temp);
  acl->printACL();
}