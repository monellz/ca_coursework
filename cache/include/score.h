#ifndef SCORE_H_
#define SCORE_H_

#include <vector>
#include "replace_policy.h"

namespace cache {

//INTERVAL: 100K(default)
//STEP = 0 -> static initial score
template<unsigned WAY, unsigned INIT_SCORE = 0, unsigned THRESHOLD = 48, unsigned SCORE = 6, unsigned IV = 40, unsigned DV = 1, unsigned INTERVAL = 100000, unsigned PREV = 32, unsigned STEP = 3>
class Score: public ReplacePolicy<WAY> {
public:
    //| scores[0] | ... | scores[WAY - 1] | init_score | threshold | prev_miss_num | direction
    Bitset<SCORE * WAY + SCORE + PREV + 1> scores;

    inline unsigned int width() { return SCORE; }
    inline unsigned int upper_score() { return 1u << SCORE; }

    inline void set_init_score(unsigned int init_score) {
        scores.range_set(WAY * width(), (WAY + 1) * width(), init_score);
    }

    inline unsigned int get_init_score() {
        return scores.range_get(WAY * width(), (WAY + 1) * width());
    }

    inline void set_threshold(unsigned int threshold) {
        scores.range_set((WAY + 1) * width(), (WAY + 2) * width(), threshold);
    }

    inline unsigned int get_threshold() {
        return scores.range_get((WAY + 1) * width(), (WAY + 2) * width());
    }
    
    inline void set_prev_miss_num(unsigned int n) {
        scores.range_set((WAY + 2) * width(), (WAY + 3) * width(), n);
    }

    inline unsigned int get_prev_miss_num() {
        return scores.range_get((WAY + 2) * width(), (WAY + 3) * width());
    }

    inline int direction() {
        return scores.test(scores.size() - 1)? 1: -1;
    }

    inline void change_direction() {
        scores.flip(scores.size() - 1);
    }

    Score() {
        set_init_score(INIT_SCORE);
        set_threshold(THRESHOLD);
        for (int i = 0; i < WAY; ++i) {
            scores.range_set(i * width(), (i + 1) * width(), INIT_SCORE);
        }
    }

    void dynamic_init_score() {
        int s = PerfStats::get_instance().time - (int)INTERVAL;
        if (s > 0) {
            //test
            if (PerfStats::get_instance().range_miss_num(s, s + INTERVAL) > get_prev_miss_num()) {
                change_direction();
            }
        }

        s = (int)get_init_score();
        s += direction() * STEP;
        s = s < 0? 0: (s > upper_score()? upper_score(): s);
        set_init_score(s);
    }

    void access(int access_way) {
        //increase score
        unsigned int s = scores.range_get(access_way * width(), (access_way + 1) * width());
        s = upper_score() - s <= IV? upper_score(): s + IV; 
        scores.range_set(access_way * width(), (access_way + 1) * width(), s);

        dynamic_init_score();
    }

    int victim() {
        std::vector<int> v;
        int min_victim = 0;
        int min_score = upper_score();
        unsigned int threshold = get_threshold();
        for (int i = 0; i < WAY; ++i) {
            unsigned int s = scores.range_get(i * width(), (i + 1) * width());
            if (s < threshold) {
                v.push_back(i);
            }

            if (s < min_score) {
                min_victim = i;
                min_score = s;
            }
        }

        int choice;
        if (v.size() > 0) {
            //random
            choice = v[rand() % v.size()];
        } else {
            choice = min_victim;
        }
        //set init score for victim
        scores.range_set(choice * width(), (choice + 1) * width(), get_init_score());
        
        //decrease other score 
        for (int i = 0; i < WAY; ++i) {
            if (i != choice) {
                unsigned int s = scores.range_get(i * width(), (i + 1) * width());
                s = s < DV? 0: s - DV;
                scores.range_set(i * width(), (i + 1) * width(), s);
            }
        }

        return choice;
    }
};

}; //namespace cache

#endif //SCORE_H_