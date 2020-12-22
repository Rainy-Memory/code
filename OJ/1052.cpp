#include <iostream>
#include <vector>

using namespace std;


struct point {
    int No=0;
    int line[7]={0};
    int row=0;
};

struct point_adjacent {
    int row;
    int No;
};

int n, m;
int table[7][7];
int point_row[7];
bool chosen[7] = {false};
bool blank[7] = {false};
vector<point> point_set[7];
point zero;
vector<int> adjacent[8][10000];


void input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> table[i][j];
        }
    }
}

void dfs(int row, int remain) {
    if (remain != 0) {
        int flag = 0;
        for (int i = 0; i < m; i++) {
            if (blank[i]) {
                flag = i;
                break;
            }
        }
        for (int i = 0; i < m; i++) {
            if (!chosen[i]) {
                point_row[flag] = i;
                blank[i] = false;
                dfs(row, remain - 1);
                point_row[flag] = 0;
                blank[i] = true;
            }
        }
    } else {
        point temp;
        temp.row = row;
        for (int i = 0; i < m; i++) {
            temp.line[i] = point_row[i];
        }
        temp.No = point_set[row].size();
        point_set[row].push_back(temp);
        //point_set[row][No]
    }
}

void init_point_row(int row) {
    int chosen_num = 0;
    for (int i = 0; i < m; i++) {
        chosen[i] = false;
        blank[i] = false;
        point_row[i] = table[row][i];
    }
    for (int i = 0; i < m; i++) {
        if (table[row][i] != 0) {
            chosen[table[row][i]] = true;
            chosen_num++;
        } else blank[i] = true;
    }
    dfs(row, m - chosen_num);
}

void initialize_point() {
    for (int i = 0; i < n; i++) {
        init_point_row(i);
    }
}

bool judge_legal(int row_up,int status1,int status2){
    for(int i=0;i<m;i++){
        int num1=point_set[row_up][status1].line[i],num2=point_set[row_up+1][status2].line[i];
        int dif=num1>num2?num1-num2:num2-num1;
        if(dif>1)return false;
    }
    return true;
}

void add_edge() {
    for(int i=0;i<point_set[0].size();i++){
        adjacent[0][0].push_back(i);//?????????? i cant make it clear..
    }
    for (int i = 0; i < n - 1; i++) {
        //add edge between i & i+1
        int size1 = point_set[i].size(), size2 = point_set[i + 1].size();
        for (int j = 0; j < size1; j++) {
            for (int k = 0; k < size2; k++) {
                //if legal -> add edge
                if(judge_legal(i,j,k)){

                    adjacent[i+1][j].push_back(k);
                }



            }
        }
    }
}


void initialize() {
    input();
    initialize_point();
    add_edge();
}


int main() {
    initialize();


    return 0;
}