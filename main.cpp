#include <iostream>
#include "sql.h"

using namespace std;

void sample_run();

int main()
{
//    sample_run();
    SQL s;
    s.run();
    cout << "==============END==============" << endl;
    return 0;
}
void sample_run()
{
    Table T("employee", {"last", "first", "major"});
    T.insert_into({"Cho", "Shirley", "CS"});
    T.insert_into({"Shin", "Julie", "CS"});
    T.insert_into({"Liu", "Angela", "Chem"});

    Table T1("employee");

    cout << "------SELECT ALL----------" << endl;
    cout << T._select_all() << endl;

    cout << "------SELECT last name----------" << endl;
    vector<string> st;
    st.push_back("first");
//    st.push_back("=");
//    st.push_back("Liu");

    cout << T1.select(st) << endl;
//    T1._select_all();
//    cout << T1._select_all() << endl;
}
