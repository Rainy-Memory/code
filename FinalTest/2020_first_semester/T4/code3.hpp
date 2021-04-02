#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

class BaseJudger {
public:
    BaseJudger(size_t time_limit, size_t memory_limit,
               const char *answer) : time_limit_(time_limit), memory_limit_(memory_limit) {
        int len = strlen(answer);
        answer_ = new char[len + 1];
        for (int i = 0; i < len; i++) {
            answer_[i] = answer[i];
        }
        answer_[len] = '\0';
        score_ = 0;
    }
    
    virtual void Submit(size_t time, size_t memory, const char *output) = 0;
    
    size_t GetScore() const {
        return score_;
    }
    
    virtual ~BaseJudger() {
        delete[]answer_;
    }

protected:
    char *answer_;
    const size_t time_limit_;
    const size_t memory_limit_;
    size_t score_;
    
    virtual bool CheckAnswer(const char *output) const {
        // the output must equal to the answer
        return strcmp(answer_, output) == 0;
    }
};


class OIJudger : public BaseJudger {
public:
    OIJudger(size_t time_limit, size_t memory_limit,
             const char *answer) : BaseJudger(time_limit, memory_limit, answer) {}
    
    bool CheckAnswer(const char *output) const {
        std::string answer_str, output_str;
        int pos = 0, pos_temp = 0;
        bool change_line = false;
        while (pos < strlen(answer_)) {
            if (answer_[pos] == '\n') {
                int delete_pos = 0;
                for (int i = pos - 1; i >= pos_temp; i--) {
                    // '\n'' ''\n'
                    if (answer_[i] != ' ') {
                        delete_pos = i;
                        break;
                    }
                }
                for (int i = pos_temp; i <= delete_pos; i++) {
                    answer_str += answer_[i];
                }
                answer_str += '\n';
                pos_temp = pos;
                change_line = true;
            }
            pos++;
        }
        if (!change_line) {
            pos = 0;
            while (pos < strlen(answer_)) {
                answer_str += answer_[pos];
                pos++;
            }
        }
        
        pos = 0, pos_temp = 0;
        change_line = false;
        while (pos < strlen(output)) {
            if (output[pos] == '\n') {
                int delete_pos = 0;
                for (int i = pos - 1; i >= pos_temp; i--) {
                    // '\n'' ''\n'
                    if (output[i] != ' ') {
                        delete_pos = i;
                        break;
                    }
                }
                for (int i = pos_temp; i <= delete_pos; i++) {
                    output_str += output[i];
                }
                output_str += '\n';
                pos_temp = pos;
                change_line = true;
            }
            pos++;
        }
        if (!change_line) {
            pos = 0;
            while (pos < strlen(output)) {
                output_str += output[pos];
                pos++;
            }
        }
        
        return strcmp(answer_str.c_str(), output_str.c_str()) == 0;
    }
    
    void Submit(size_t time, size_t memory, const char *output) {
        if (submit) {
            score_ = 0;
            return;
        }
        submit = true;
        if (time <= time_limit_ && memory <= memory_limit_) {
            if (CheckAnswer(output))score_ = 100;
        }
    }

private:
    bool submit = false;
};


class ICPCJudger : public BaseJudger {
public:
    ICPCJudger(size_t time_limit, size_t memory_limit,
               const char *answer) : BaseJudger(time_limit, memory_limit, answer) {}
    
    void Submit(size_t time, size_t memory, const char *output) {
        if (time <= time_limit_ && memory <= memory_limit_) {
            if (CheckAnswer(output))score_ = 100;
        }
    }
};


class SpacialJudger : public BaseJudger {
public:
    SpacialJudger(size_t time_limit, size_t memory_limit, size_t full_score_time, size_t full_score_memory,
                  const char *answer) : BaseJudger(time_limit, memory_limit, answer), full_score_time_(full_score_time), full_score_memory_(full_score_memory) {}
    
    int time_score(int time) {
        if (time >= time_limit_)return 0;
        else if (time <= full_score_time_)return 100;
        else return 100 * (time_limit_ - time) / (time_limit_ - full_score_time_);
    }
    
    int memory_score(int memory) {
        if (memory >= memory_limit_)return 0;
        else if (memory <= full_score_memory_)return 100;
        else return 100 * (memory_limit_ - memory) / (memory_limit_ - full_score_memory_);
    }
    
    void Submit(size_t time, size_t memory, const char *output) {
        if (CheckAnswer(output)) {
            score_ = floor(time_score(time) * memory_score(memory) / 100);
        }
    }

private:
    size_t full_score_time_;
    size_t full_score_memory_;
};
