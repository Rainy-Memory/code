#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
class BaseJudger {
public:
    BaseJudger (size_t time_limit , size_t memory_limit ,
                const char *answer)
            : time_limit_(time_limit) ,
              memory_limit_(memory_limit) ,
              score_(0) {
        answer_ = new char[strlen(answer) + 1];
        strcpy(answer_ , answer);
    }
    
    virtual void Submit (size_t time , size_t memory , const char *output) = 0;
    
    size_t GetScore () const { return score_; }
    
    virtual ~BaseJudger (){
        delete []answer_;
    };

protected:
     char *answer_;
    const size_t time_limit_;
    const size_t memory_limit_;
    size_t score_;
    
    virtual bool CheckAnswer (const char *output) const {
        // the output must equal to the answer
        return strcmp(answer_ , output) == 0;
    }
};

class OIJudger : public BaseJudger {
public:
    OIJudger (size_t time_limit , size_t memory_limit ,
              const char *answer)
            : BaseJudger(time_limit , memory_limit , answer) , submitted(false) {}
    
    void Submit (size_t time , size_t memory , const char *output) {
        if (submitted) {
            score_ = 0;
        } else if (time <= time_limit_ && memory <= memory_limit_ &&
                   CheckAnswer(output)) {
            score_ = 100;
            submitted = true;
        }
    }

private:
    bool submitted;
    
    bool CheckAnswer (const char *output) const {
        // ignore the space at the end of line
    
        const char *output_start = output , *ans_start = answer_;
        while (*output_start || *ans_start) {
            if (*output_start != *ans_start) {
                if (*output_start == '\n' || *output_start == '\0') {
                    while (*ans_start != *output_start) {
                        if (*ans_start != ' ') {
                            return false;
                        }
                        ans_start++;
                    }
                } else if (*ans_start == '\n' || *output_start == '\0') {
                    while (*output_start != *ans_start) {
                        if (*output_start != ' ') {
                            return false;
                        }
                        output_start++;
                    }
                } else {
                    return false;
                }
            }
            output_start++;
            ans_start++;
        }
        return true;
    }
};

class ICPCJudger : public BaseJudger {
public:
    ICPCJudger (size_t time_limit , size_t memory_limit ,
                const char *answer)
            : BaseJudger(time_limit , memory_limit , answer) {}
    
    virtual void Submit (size_t time , size_t memory ,
                         const char *output) {
        if (time <= time_limit_ && memory <= memory_limit_ && CheckAnswer(output)) {
            score_ = 100;
        }
    }
};

class SpacialJudger : public ICPCJudger {
public:
    SpacialJudger (size_t time_limit , size_t memory_limit ,
                   size_t full_score_time , size_t full_score_memory ,
                   const char *answer)
            : ICPCJudger(time_limit , memory_limit , answer) ,
              full_score_memory_(full_score_memory) ,
              full_score_time_(full_score_time) {}
    
    void Submit (size_t time , size_t memory , const char *output) {
        if (CheckAnswer(output)) {
            size_t score = 100;
            if (time > full_score_time_) {
                score = score * (time_limit_ - time) / (time_limit_ - full_score_time_);
            }
            if (memory > full_score_memory_) {
                score = score * (memory_limit_ - memory) /
                        (memory_limit_ - full_score_memory_);
            }
            if (score > score_) {
                score_ = score;
            }
        }
    }

private:
    const size_t full_score_time_;
    const size_t full_score_memory_;
};
