//
// Created by ra_watt on 2/12/20.
//

#include "ACL.h"

ACL::ACL() {
}

ACL::ACL(std::string fileName){
//  setting file name
  FileName=std::string(basename(strdup(fileName.c_str())));

  struct stat statbuf;
  if(stat(fileName.c_str(),&statbuf)==-1){
    std::cout<<"file not found"<<std::endl;
    exit(-1);
  }

//  setting owner of the file
  Owner=std::string(getpwuid(statbuf.st_uid)->pw_name);

//  setting group of the file
  group=std::string(getgrgid(statbuf.st_gid)->gr_name);

  char userPermissions[4],groupPermissions[4],otherPermissions[4];
  sprintf(userPermissions,"%o",statbuf.st_mode & S_IRWXU);
  sprintf(groupPermissions,"%o",statbuf.st_mode & S_IRWXG);
  sprintf(otherPermissions,"%o",statbuf.st_mode & S_IRWXO);

//  pushing owner with the group permissions
  user.push_back(std::make_pair("",userPermissions[0]-'0'));
//  pushing group with the group permissions
  groups.push_back(std::make_pair("",groupPermissions[0]-'0'));
//  setting permissions for the others
  others=otherPermissions[0]-'0';
  mask=0;

}

void ACL::printACL() {
  using namespace std;
//  print filename owner and group
  cout<<"# file: "<<FileName<<endl;
  cout<<"# owner: "<<Owner<<endl;
  cout<<"# group: "<<group<<endl;

//  print permission associated with all the users
  for(auto i:user){
    cout<<"user:"<<i.first<<":"<<intToPermissions[i.second]<<endl;
  }
//  print permissions associated with all the groups
  for(auto i:groups){
    cout<<"group:"<<i.first<<":"<<intToPermissions[i.second]<<endl;
  }
  cout<<"other::"<<intToPermissions[others]<<endl;
  cout<<"mask::"<<intToPermissions[mask]<<endl;
}