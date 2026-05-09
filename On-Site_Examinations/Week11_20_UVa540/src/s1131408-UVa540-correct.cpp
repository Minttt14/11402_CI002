#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    int cnt = 1;
    while(cin >> t && t != 0){
        cout << "Scenario #" << cnt << "\n";
        cnt ++;
        
        map<int, int> mp;
        for(int i=1; i<=t; ++i){
            int num;
            cin >> num;
            for(int j=0; j<num; ++j){
                int person;
                cin >> person;
                mp[person] = i;
            }
        }
        queue<int> main;
        queue<int> team[1100];
        
        string cmd;
        while(cin >> cmd && cmd != "STOP"){
            if(cmd == "ENQUEUE"){
                int newPerson;
                cin >> newPerson;
                int teamId = mp[newPerson];
                
                if(team[teamId].empty()) main.push(teamId);
                team[teamId].push(newPerson);
            }
            else if(cmd == "DEQUEUE"){
                int frontTeam = main.front();
                cout << team[frontTeam].front() << "\n";
                
                team[frontTeam].pop();
                
                if(team[frontTeam].empty()) main.pop();
            }
        }
        cout << "\n";
    }
}