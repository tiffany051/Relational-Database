#include "alpha.h"

Alpha::Alpha(string st):_alpha(st)
{

}
int Alpha::type_of()
{
    return ALPHA;
}
void Alpha::print()
{
    cout << _alpha << " ";
}
string Alpha::get_alpha()
{
    return _alpha;
}
