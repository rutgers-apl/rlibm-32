#include "IntervalRange.hpp"

void IntervalRange::AddInterval(double _xtrans, double _lb, double _ub) {
    // Why do I have to create one to search for one...
    unique_ptr<Interval> info = make_unique<Interval>();
    info->xtrans = _xtrans;
    info->lb = _lb;
    info->ub = _ub;
    info->origLb = _lb;
    info->origUb = _ub;
    
    // Search for an Interval with _xtrans
    auto comparer = [&](const unique_ptr<Interval>& left,
                        const unique_ptr<Interval>& right) {
        return left->xtrans < right->xtrans;
    };
    auto insertPos = lower_bound(intervals.begin(), intervals.end(), info, comparer);
        
    // Check if it already exists:
    if (insertPos != intervals.end() && (*insertPos)->xtrans == _xtrans) {
        // Then update ub/lb
        if (_lb > (*insertPos)->lb) (*insertPos)->lb = _lb;
        if (_lb > (*insertPos)->origLb) (*insertPos)->origLb = _lb;
        if (_ub < (*insertPos)->ub) (*insertPos)->ub = _ub;
        if (_ub < (*insertPos)->origUb) (*insertPos)->origUb = _ub;
    } else {
        // Otherwise, insert into position
        intervals.insert(insertPos, std::move(info));
    }
}

void IntervalRange::AssertSanity() {
    for (auto& ii : intervals) {
        if (ii->ub < ii->lb) {
            printf("Assertion failed: \n");
            printf("%.100e\n", ii->xtrans);
            printf("%.100e\n", ii->lb);
            printf("%.100e\n", ii->ub);
            exit(0);
        }
    }
    
    return;
}

void IntervalRange::PrintIntervals() {
    for (auto& ii : intervals) {
        printf("xtrans  = %.100e\n", ii->xtrans);
        printf("lb      = %.100e\n", ii->lb);
        printf("origLb = %.100e\n", ii->origLb);
        printf("ub      = %.100e\n", ii->ub);
        printf("origUb = %.100e\n", ii->origUb);
        printf("\n");
    }
}
