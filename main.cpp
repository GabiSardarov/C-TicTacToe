#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
void InputNames(string *name1, string *name2){
    cin>>*name1>>*name2;
    bool isIncorrect;
    for(int i=0;i<(*name1).size();i++){
        if(!(((*name1)[i]>='A'&&(*name1)[i]<='Z')||((*name1)[i]>='a'&&(*name1)[i]<='z'))){
            isIncorrect= true;
            break;
        }
    }
    for(int i=0;i<(*name2).size();i++){
        if(!(((*name2)[i]>='A'&&(*name2)[i]<='Z')||((*name2)[i]>='a'&&(*name2)[i]<='z'))){
            isIncorrect= true;
            break;
        }
    }
    if(isIncorrect){
        while(isIncorrect){
            isIncorrect= false;
            cout<<"Incorrect Username, Please Enter Using Latin Letters."<<endl;
            cin>>*name1>>*name2;
            for(int i=0;i<(*name1).size();i++){
                if(!(((*name1)[i]>='A'&&(*name1)[i]<='Z')||((*name1)[i]>='a'&&(*name1)[i]<='z'))){
                    isIncorrect= true;
                    break;
                }
            }
            for(int i=0;i<(*name2).size();i++){
                if(!(((*name2)[i]>='A'&&(*name2)[i]<='Z')||((*name2)[i]>='a'&&(*name2)[i]<='z'))){
                    isIncorrect= true;
                    break;
                }
            }
        }
    }
}
void DrawBoard(vector<char> &nums){
    for(int i=1;i<=7;i+=3) {
        cout << "---" << "|" << "---" << "|" << "---" << endl;
        cout << " " << nums[i] << " " << "|" << " " << nums[i+1] << " " << "|" << " " << nums[i+2] << endl;
    }
    cout << "---" << "|" << "---" << "|" << "---" << endl;
}
bool isFree(char a,vector<char> &nums){
    return (nums[a]!='x'&&nums[a]!='y');
}
void InputMove(vector<char> &nums,char symbol){
    int n;
    cin>>n;
    if(n>=1&&n<=9&&isFree(n,nums)){
        nums[n]=symbol;
    }else{
        cout<<"Invalid Index, Choose 1-9."<<endl;
    }
}
bool CheckIsWon(vector<char> &nums,bool *HasWon,int *marks){
    for(int i=1;i<=3;i++){
        if(nums[i]==nums[i+3]&&nums[i]==nums[i+6]){
            *HasWon = true;
            *marks++;
            return true;
        }
        if (nums[i] == nums[i + 1] && nums[i] == nums[i + 2]) {
            *HasWon = true;
            *marks++;
            return true;
        }
    }
    if(nums[1]==nums[5]&&nums[1]==nums[9]||nums[3]==nums[5]&&nums[3]==nums[7]){
        *HasWon = true;
        *marks++;
        return true;
    }
    return false;
}
void klebadoba(vector<int> &scores, vector<string> &names){
    int n=scores.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(scores[j]<scores[j+1]){
                swap(scores[j],scores[j+1]);
                swap(names[j],names[j+1]);
            }
        }
    }
}
int main() {
    string name1,name2;
    InputNames(&name1,&name2);
    vector<char> nums(9);
    vector<char> *pnt = &nums;
    for(int i=1;i<=nums.size();i++){
        nums[i]= i + '0';
    }
    bool HasWon= false;
    int cnt=0;
    int Xwins=0,Ywins=0;
    char symbols[2] = {'x', 'o'};
    while(!HasWon){
        int marks=0;
        DrawBoard(*pnt);
        InputMove(*pnt,symbols[0]);
        if(CheckIsWon(*pnt, &HasWon,&marks)){
            if(marks>1){
                DrawBoard(*pnt);
                cout<<name1<<" wins!"<<endl;
                Xwins+=4;
                Ywins--;
                break;
            }else{
                DrawBoard(*pnt);
                cout<<name1<<" wins!"<<endl;
                Xwins+=3;
                Ywins--;
                break;
            }
        }
        cnt++;
        if(cnt==9&&!HasWon){
            DrawBoard(*pnt);
            cout<<"It's a draw!"<<endl;
            Xwins++;
            Ywins++;
            break;
        }
        DrawBoard(*pnt);
        InputMove(*pnt,symbols[1]);
        if(CheckIsWon(*pnt, &HasWon,&marks)) {
            if(marks>1){
                DrawBoard(*pnt);
                cout<<name2<<" wins!"<<endl;
                Ywins+=4;
                Xwins--;
                break;
            }else{
                DrawBoard(*pnt);
                cout<<name2<<" wins!"<<endl;
                Ywins+=3;
                Xwins--;
                break;
            }
        }
        cnt++;
    }
    vector<string> names;
    vector<int> scores;
    ifstream leaderboardInput("leaderboard.txt");
    string name;
    int score;
    bool nameFound = false;
    while(leaderboardInput>>name>>score){
        if(name==name1){
            score+=Xwins;
            nameFound=true;
        }else if(name==name2){
            score+=Ywins;
            nameFound=true;
        }
        names.push_back(name);
        scores.push_back(score);
    }
    leaderboardInput.close();
    klebadoba(scores, names);
    if(!nameFound){
        if(Xwins>0){
            names.push_back(name1);
            scores.push_back(Xwins);
        }
        if(Ywins>0){
            names.push_back(name2);
            scores.push_back(Ywins);
        }
    }

    ofstream leaderboardOutput("leaderboard.txt");
    if(leaderboardOutput.is_open()){
        leaderboardOutput<<name1<<" "<<Xwins<<endl;
        leaderboardOutput<<name2<<" "<<Ywins<<endl;
        leaderboardOutput.close();
    }


    ofstream leaderboardChange("leaderboard.txt");
    if(leaderboardChange.is_open()){
        for (int i=0;i<names.size();i++){
            leaderboardChange<<names[i]<<" "<<scores[i]<<endl;
        }
        leaderboardChange.close();
    }

    ifstream leaderboardDisplay("leaderboard.txt");
    string line;
    if(leaderboardDisplay.is_open()){
        while(getline(leaderboardDisplay,line)){
            cout<<line<<endl;
        }
        leaderboardDisplay.close();
    }
    return 0;
}
