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

ACL getACLEntries(std::string filename){
  ssize_t temp=getxattr(filename.c_str(),xattrName,NULL,0);
  char buff[temp];
  getxattr(filename.c_str(),xattrName,buff,temp);
  ACL acl;
  acl.deserialise(std::string(buff));
  return acl;
}

void extendACL(std::string filename,std::string entry){
  ACL acl=getACLEntries(filename);
  acl.check(filename);
  acl.update(entry);
  std::string temp=acl.serialise();
  setxattr(filename.c_str(),xattrName,temp.c_str(), strlen(temp.c_str()),XATTR_REPLACE);
}

void removeAclEntry(std::string filename,std::string entry){
  ACL acl=getACLEntries(filename);
  acl.check(filename);
  acl.deleteEntry(entry);
  std::string temp=acl.serialise();
  setxattr(filename.c_str(),xattrName,temp.c_str(), strlen(temp.c_str()),XATTR_REPLACE);
}

void removeAllEntries(std::string filename){
  ACL acl=getACLEntries(filename);
  acl.check(filename);
  acl.removeAll();
  std::string temp=acl.serialise();
  setxattr(filename.c_str(),xattrName,temp.c_str(), strlen(temp.c_str()),XATTR_REPLACE);
}