//
// Created by Rainy Memory on 2020/12/13.
//

#include <iostream>
#include <fstream>
#include "code3.hpp"

using namespace std;
ifstream ifs;

string get_data() {
    // ignore empty lines
    string ret = "", line;
    while (getline(ifs, line)) {
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

int main() {
    string path;
    int s = 0;
    for (int i = 0; i < 10; i++) {
        path = "";
        path += (i + '0');
        string path_in = path + ".in", path_out = path + ".out";
        //freopen(path_in.c_str(), "r", stdin);
        ifs.open(path_in);
        char judger_name[100];
        ifs >> judger_name;
        size_t time_limit, mem_limit;
        ifs >> time_limit >> mem_limit;
        BaseJudger *judger = nullptr;
        string tmp;
        if (strcmp(judger_name, "OIJudger") == 0) {
            tmp = get_data();
            judger = new OIJudger(time_limit, mem_limit, tmp.c_str());
        }
        else if (strcmp(judger_name, "ICPCJudger") == 0) {
            tmp = get_data();
            judger = new ICPCJudger(time_limit, mem_limit, tmp.c_str());
        }
        else if (strcmp(judger_name, "SpacialJudger") == 0) {
            size_t full_score_time, full_score_memory;
            ifs >> full_score_time >> full_score_memory;
            tmp = get_data();
            judger = new SpacialJudger(time_limit, mem_limit, full_score_time,
                                       full_score_memory, tmp.c_str());
        }
        else {
            cout << "Data " << i << " Failed. Unknown judger type." << endl;
            continue;
        }
        
        size_t submit_time, submit_mem;
        while (ifs >> submit_time >> submit_mem) {
            if (submit_time == -1)break;
            tmp = get_data();
            const char *output = tmp.c_str();
            judger->Submit(submit_time, submit_mem, output);
        }
        ifs.close();
        //freopen(path_out.c_str(), "r", stdin);
        ifs.open(path_out.c_str());
        int std_score;
        ifs >> std_score;
        int my_score = judger->GetScore();
        if (std_score != my_score) {
            cout << "Data " << i << " Failed." << endl;
            cout << "Standard output: " << std_score << endl;
            cout << "Your output: " << my_score << endl;
        }
        else {
            cout << "Data " << i << " Pass." << endl;
            s++;
        }
        cout << endl;
        ifs.close();
        delete judger;
    }
    cout<<s<<" / 10 passed."<<(s==10?" Congratulation!":"")<<endl;
    return 0;
}
