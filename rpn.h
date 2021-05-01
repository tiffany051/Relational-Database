#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <math.h>
#include <vector>
#include<algorithm>

#include "shunting_yard.h"
#include "sy_token.h"
#include "../CS008_Final_Project/!include/queue.h"
#include "../CS008_Final_Project/!include/stack_class.h"
#include "../CS008_Final_Project/!include/my_mmap.h"
#include "../CS008_Final_Project/!include/my_map.h"
#include "number.h"
#include "operator.h"
#include "alpha.h"
#include "vector_long.h"


using namespace std;

class RPN
{
public:
    RPN(Queue <sy_Token*> postfix, vector<MMap<string, long>> indices, Map<string, long> field_name);
    vector<long> operator()();
    vector<long> Union(const vector<long>& v1, const vector<long>& v2);
    vector<long> intersection(const vector<long>& v1, const vector<long>& v2);
    void make_string(string& st1, const string& st2);

private:
    Queue <sy_Token*> _post_fix;
    vector<MMap<string, long> > _indices;
    Map<string, long> _field_name;
};

#endif // RPN_H
