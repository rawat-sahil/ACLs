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

std::string ACL::serialise(){
  std::string serialisedString="";
  char buff[256];
  sprintf(buff,"%s\n",FileName.c_str());
  serialisedString.append(buff);

  sprintf(buff,"%s\n",Owner.c_str());
  serialisedString.append(buff);

  sprintf(buff,"%s\n",group.c_str());
  serialisedString.append(buff);

  for(auto i:user){
    sprintf(buff,"u%s%d\n",i.first.c_str(),i.second);
    serialisedString.append(buff);
  }
  for(auto i:groups){
    sprintf(buff,"g%s%d\n",i.first.c_str(),i.second);
    serialisedString.append(buff);
  }
  sprintf(buff,"o%d\n",others);
  serialisedString.append(buff);

  sprintf(buff,"m%d\n",mask);
  serialisedString.append(buff);

  return serialisedString;
}

void ACL::deserialise(std::string attrList) {
    const char * tempAttrList=attrList.c_str();
    std::vector<std::string> stringList;

    char * token=strtok((char *)tempAttrList,"\n");

    while(token!=NULL){
        stringList.push_back(std::string(token));
        token=strtok(NULL,"\n");
    }

    FileName=stringList[0];
    Owner=stringList[1];
    group=stringList[2];

    for(int i=3;i<stringList.size();++i){
        if(stringList[i][0]=='u'){
            int permission=stringList[i][stringList[i].size()-1]-'0';
            std::string user=stringList[i].substr(1,stringList[i].size()-2);
            this->user.push_back(std::make_pair(user,permission));
        }
        else if(stringList[i][0]=='g'){
            int permission=stringList[i][stringList[i].size()-1]-'0';
            std::string group=stringList[i].substr(1,stringList[i].size()-2);
            groups.push_back(std::make_pair(group,permission));
        }
        else if(stringList[i][0]=='o'){
            others=stringList[i][1]-'0';
        }
        else if(stringList[i][0]=='m'){
            mask=stringList[i][1]-'0';
        }

    }


}