#ifndef PARSER_CLASS_H
#define PARSER_CLASS_H
#include <iostream>
#include <string>

#include "../CS008_Final_Project/!include/my_map.h"
#include "../CS008_Final_Project/!include/my_mmap.h"
#include "../CS008_Final_Project/!include/stokenizer.h"
#include "../CS008_Final_Project/!include/my_vector.h"
#include "../CS008_Final_Project/!include/vector.h"


using namespace std;
static const int MAX_COLUMN = 30;
static const int MAX_ROW = 20;
static const int MAX_BUFF = 600;


class Parser_Class
{
public:
    Parser_Class(char* s);
    void set_string(char str[]);
    string get_column();
    bool get_parser_tree();
    int build_key_word_list(const string st);
    vector<string>& convert_condition(const vector<string>& condition);
    MMap<string, string> parse_tree();


private:
    MMap<string, string> ptree;
    Map<string, string> map;
    int adjacenct_table[MAX_ROW][MAX_COLUMN];
    char _buffer[MAX_BUFF];
    vector<string> result;
    void make_table(int _table[][MAX_COLUMN])
    {
        //initial table
        init_table(_table);

        //set up adjcency table
        mark_fail(_table, 0);
        mark_fail(_table, 1);
        mark_fail(_table, 2);
        mark_fail(_table, 3);
        mark_success(_table, 4);
        mark_success(_table, 5);
//        mark_fail(_table, 5);
        mark_fail(_table, 6);
        mark_success(_table, 7);
        mark_success(_table, 8);
        mark_fail(_table, 9);
        mark_fail(_table, 10);
        mark_success(_table, 11);
        mark_fail(_table, 12);
        mark_success(_table, 13);
        mark_fail(_table, 14);
        mark_fail(_table, 15);
        mark_fail(_table, 16);
        mark_success(_table, 17);
        mark_success(_table, 18);

        mark_cell(0, _table, 1, 1);//SELECT
        mark_cell(0, _table, 12, 9);//create
        mark_cell(0, _table, 13, 9);//Make
        mark_cell(0, _table, 16, 14);//insert
        mark_cell(0, _table, 19, 15);//drop
        mark_cell(0, _table, 24, 16);//Batch

        mark_cell(1, _table, 22, 2);//Symbol
        mark_cell(1, _table, 23, 2);//Symbol

        mark_cell(2, _table, 2, 3);//from
        mark_cell(2, _table, 3, 1);//,

        mark_cell(3, _table, 22, 4);//symbol

        mark_cell(4, _table, 4, 5);//where

        mark_cell(5, _table, 22, 6);//symbol
        mark_cell(5, _table, 10, 5);//(
        mark_cell(5, _table, 11, 5);//)
        mark_cell(5, _table, 20, 5);//and
        mark_cell(5, _table, 21, 5);//or

        mark_cell(6, _table, 5, 7);//=
        mark_cell(6, _table, 6, 7);//<
        mark_cell(6, _table, 7, 7);//>
        mark_cell(6, _table, 8, 7);//>=
        mark_cell(6, _table, 9, 7);//<=
        mark_cell(6, _table, 22, 7);//symbol

        mark_cell(7, _table, 22, 8);//symbol
        mark_cell(7, _table, 24, 8);//"
        mark_cell(7, _table, 20, 5);//"
        mark_cell(7, _table, 21, 5);//"

        mark_cell(8, _table, 10, 5);//(
        mark_cell(8, _table, 11, 5);//)
        mark_cell(8, _table, 22, 7);//symbol
        mark_cell(8, _table, 24, 7);//"
        mark_cell(8, _table, 20, 5);//and
        mark_cell(8, _table, 21, 5);//or


        mark_cell(9, _table, 14, 10);//table
//        mark_cell(9, _table, 22, 11);//table

        mark_cell(10, _table, 22, 11);//symbol

        mark_cell(11, _table, 15, 12);//fields
        mark_cell(11, _table, 18, 12);//drop

        mark_cell(12, _table, 22, 13);//symbol
        mark_cell(12, _table, 22, 13);//"
        mark_cell(12, _table, 24, 13);//"

        mark_cell(13, _table, 3, 12);//,
        mark_cell(13, _table, 22, 13);//"
        mark_cell(13, _table, 24, 13);//"

        mark_cell(14, _table, 17, 10);//into
        mark_cell(15, _table, 14, 10);//table

        mark_cell(16, _table, 22, 17);//Batch

        mark_cell(17, _table, 22, 18);//.
        mark_cell(17, _table, 22, 18);//.
        mark_cell(18, _table, 22, 18);//.
    }

    //=========Helper functions
    //Fill all cells of the array with -1
    void init_table(int _table[][MAX_COLUMN])
    {
        for (int i = 0; i < MAX_ROW; i++)
        {
            for (int j = 0; j < MAX_COLUMN; j++)
            {
                _table[i][j] = -1;
            }
        }
    }

    //Mark this state (row) with a 1 (success)
    void mark_success(int _table[][MAX_COLUMN], int state)
    {
        _table[state][0] = 1;
    }

    //Mark this state (row) with a 0 (fail)
    void mark_fail(int _table[][MAX_COLUMN], int state)
    {
        _table[state][0] = 0;
    }

    //Mark this row and column
    void mark_cell(int row, int table[][MAX_COLUMN], int column, int state)
    {
        table[row][column] = state;
    }

    enum keys{ZERO, SELECT, FROM, COMMA, WHERE, EQUAL, LESS, GREATER, LESSTHAN, GREATERTHAN,
              LPARENTHESIS, RPARENTATHESIS, CREATE, MAKE, TABLE, FIELDS, INSERT, INTO, VALUE, DROP,
              AND, OR, SYM, STAR, BATCH};
    Vector<string> inputq;
};

#endif // PARSER_CLASS_H
