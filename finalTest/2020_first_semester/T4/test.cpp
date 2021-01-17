#include <iostream>
#include "code3.hpp"
using namespace std;


string get_data () {
    // ignore empty lines
    string ret = "" , line;
    while (getline(cin , line)) {
        if (line.length() == 0) {
            continue;
        }
        if (line == "#####") {
            break;
        }
        ret += line + "\n";
    }
    return std::move(ret);
}

int main () {
    char judger_name[100];
    cin >> judger_name;
    size_t time_limit , mem_limit;
    cin >> time_limit >> mem_limit;
    BaseJudger *judger = nullptr;
    string tmp;
    if (strcmp(judger_name , "OIJudger") == 0) {
        tmp = get_data();
        judger = new OIJudger(time_limit , mem_limit , tmp.c_str());
    } else if (strcmp(judger_name , "ICPCJudger") == 0) {
        tmp = get_data();
        judger = new ICPCJudger(time_limit , mem_limit , tmp.c_str());
    } else if (strcmp(judger_name ,"SpacialJudger") == 0) {
        size_t full_score_time , full_score_memory;
        cin >> full_score_time >> full_score_memory;
        tmp = get_data();
        judger = new SpacialJudger(time_limit , mem_limit , full_score_time ,
                                   full_score_memory , tmp.c_str());
    } else {
        cout << "Unknown Judger type" << endl;
        return 0;
    }
    
    size_t submit_time , submit_mem;
    while (cin >> submit_time >> submit_mem) {
        if(submit_time==233)break;
        tmp = get_data();
        const char *output = tmp.c_str();
        judger->Submit(submit_time , submit_mem , output);
    }
    cout << judger->GetScore() << endl;
    delete judger;
    return 0;
}
