//
// Created by Maksim on 17.02.2022.
//
#include <iostream>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std::chrono;

void find_person(std::string a, std::map<std::string,int> s1){
    std::cout << a << " : " << s1.find(a)->second << std::endl;

}

void Sort_by_name(std::map<std::string,int> s1){
    for(auto i=s1.begin();i!=s1.end();i++){
        std::cout << i->first<<" : "<<i->second<<std::endl;
    }
}

void Random(std::map<std::string,int> s1){
    auto k=(steady_clock::now().time_since_epoch().count())%s1.size();
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
    Random(s);

}