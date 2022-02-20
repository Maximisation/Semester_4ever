//
// Created by Maksim on 17.02.2022.
//
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

void find_person(std::string a, std::map<std::string,int> s1){
    for(auto i=s1.begin(); i!=s1.end();i++){
        if (i->first ==a){
            std::cout << a<<" : "<<i->second<<std::endl;
            return;
        }
    }
    std::cout << "There is no such person here!"<<std::endl;

}

void Sort_by_name(std::map<std::string,int> s1){
    std::vector<std::string> names;
    for(auto i=s1.begin();i!=s1.end();i++){
        names.push_back(i->first);
    }
    std::sort(names.begin(),names.end());
    for(auto i=0;i<names.size();i++){ find_person(names[i],s1);}
}

void Random(std::map<std::string,int> s1){
    unsigned ran=43;
    srand(ran);
    int k=rand()%(s1.size());
    for(auto i=s1.begin();i!=s1.end();i++){
        if (k!=0){
            k-=1;
        }
        else{
            std::cout << i->first<<" : "<<i->second<<std::endl;
            return;
        }
    }
}

int main(){
    std::map<std::string,int> s{{"Maxim",3785},{"Katya",8744},{"Damir",8573},{"Joe",2139},{"Pete",9482},{"Nikita",1038}};
    find_person("Nikita",s);
    Sort_by_name(s);
    Random(s);
}