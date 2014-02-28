//  Created by Mathias Lindblom on 2014-01-27.
//  Copyright (c) 2014 Mathias Lindblom. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <set>

void switchGroup(std::vector<int> & from, std::vector<int> & to, int* friendGroupInfo, int newPos) {
    for(int i: from) {
        to.push_back(i);
        friendGroupInfo[i] = newPos;
    }
}

int main(int argc, const char * argv[])
{
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::vector<std::string> startVector = {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
    int friends = std::stoi(startVector[0]);
    int friendShips = std::stoi(startVector[1]);
    
    int* owesInfo =  new int[friends];
    
    for(int i = 0; i < friends; i++){
        std::getline(std::cin, line);
        int owes = std::stoi(line);
        owesInfo[i] = owes;
    }
    
    int* friendGroupInfo = new int[friends]{};
    std::fill_n(friendGroupInfo, friends, -1);
    std::vector<std::vector<int>> friendGroup;
    std::set<int> activeFriendGroups;
    
    int m;
    int n;
    for(int i = 0; i < friendShips; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::vector<std::string> friendShip = {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
        m = std::stoi(friendShip[0]);
        n = std::stoi(friendShip[1]);
        if(friendGroupInfo[m] == -1) {
            if(friendGroupInfo[n] == -1) {
                friendGroupInfo[m] = friendGroup.size();
                friendGroupInfo[n] = friendGroup.size();
                activeFriendGroups.insert(friendGroup.size());
                friendGroup.push_back({m,n});
            } else {
                friendGroupInfo[m] = friendGroupInfo[n];
                friendGroup[friendGroupInfo[n]].push_back(m);
            }
        } else {
            if(friendGroupInfo[n] == -1) {
                friendGroupInfo[n] = friendGroupInfo[m];
                friendGroup[friendGroupInfo[m]].push_back(n);
            } else if(friendGroupInfo[n] != friendGroupInfo[m]){
                std::vector<int> & nGroup = friendGroup[friendGroupInfo[n]];
                std::vector<int> & mGroup = friendGroup[friendGroupInfo[m]];
                if(nGroup.size() < mGroup.size()) {
                    activeFriendGroups.erase(friendGroupInfo[n]);
                    switchGroup(nGroup, mGroup, friendGroupInfo, friendGroupInfo[m]);
                } else {
                    activeFriendGroups.erase(friendGroupInfo[m]);
                    switchGroup(mGroup, nGroup, friendGroupInfo, friendGroupInfo[n]);
                }
            }
        }
    }
    
    for(int i: activeFriendGroups) {
        std::vector<int> group = friendGroup[i];
        long value = 0;
        for(int j: group) {
            value += owesInfo[j];
        }
        if(value != 0) {
            std::cout << "IMPOSSIBLE" << std::endl;
            return 0;
        }
    }
    std::cout << "POSSIBLE" << std::endl;
    return 0;
}





