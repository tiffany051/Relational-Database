#ifndef OUTPUT_H
#define OUTPUT_H
/*
> batch samples.bin
//****************************************************************************
//              CREATE AND INSERT
//****************************************************************************

//---- employee table ----------
[0]make table employee fields  last,            first,                  dep
Table: employee1 Record:0
    Record           last          first            dep


SQL::DONE
[1]insert into employee values Blow,            Joe,                    CS

SQL::DONE
[2]insert into employee values Johnson,         "Jimmy" ,               Chemistry

SQL::DONE
[3]insert into employee values Yang,            Bo,                     CS

SQL::DONE
[4]insert into employee values "Jackson" ,      Billy,                  Math

SQL::DONE
[5]insert into employee values Johnson ,        Billy,                  "Phys Ed"

SQL::DONE
[6]insert into employee values "Van Gogh" ,     "Jim Bob" ,             "Phys Ed"

SQL::DONE

[7]select * from employee
Table: employee2 Record:6
    Record           last          first            dep
         0           Blow            Joe             CS
         1        Johnson          Jimmy      Chemistry
         2           Yang             Bo             CS
         3        Jackson          Billy           Math
         4        Johnson          Billy        Phys Ed
         5       Van Gogh        Jim Bob        Phys Ed


SQL::DONE

//----- student table ----------
[8]make table student fields    fname,                  lname,          major,                          age
Table: student1 Record:0
    Record          fname          lname          major            age


SQL::DONE
[9]insert into student values   Flo,                    Yao,            CS,                             20

SQL::DONE
[10]insert into student values  "Flo" ,                         "Jackson" ,     Math,                           21

SQL::DONE
[11]insert into student values  Calvin,                 Woo,            Physics,                        22

SQL::DONE
[12]insert into student values  "Anna Grace" ,  "Del Rio" ,     CS,                                     22

SQL::DONE
[13]select * from student
Table: student2 Record:4
    Record          fname          lname          major            age
         0            Flo            Yao             CS             20
         1            Flo        Jackson           Math             21
         2         Calvin            Woo        Physics             22
         3     Anna Grace        Del Rio             CS             22


SQL::DONE



//****************************************************************************
//              SIMPLE SELECT
//****************************************************************************

[14]select * from student
Table: student3 Record:4
    Record          fname          lname          major            age
         0            Flo            Yao             CS             20
         1            Flo        Jackson           Math             21
         2         Calvin            Woo        Physics             22
         3     Anna Grace        Del Rio             CS             22


SQL::DONE

//------- simple strings -------------------
[15]select * from student where lname = Jackson
Table: student4 Record:1
    Record          fname          lname          major            age
         0            Flo        Jackson           Math             21


SQL::DONE

//----- quoted strings ---------------------
[16]select * from student where lname = "Del Rio"
Table: student5 Record:1
    Record          fname          lname          major            age
         0     Anna Grace        Del Rio             CS             22


SQL::DONE

//-------- non-existing string ------------------
[17]select * from student where lname = "Does Not Exist"
Table: student6 Record:0
    Record          fname          lname          major            age


SQL::DONE

//****************************************************************************
//              RELATIONAL OPERATORS:
//****************************************************************************

//.................
//:Greater Than   :
//.................
[18]select * from student where lname > Yang
Table: student7 Record:1
    Record          fname          lname          major            age
         0            Flo            Yao             CS             20


SQL::DONE


//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[19]select * from student where age > 50
Table: student8 Record:0
    Record          fname          lname          major            age


SQL::DONE

//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .
[20]select * from student where age  > 53
Table: student9 Record:0
    Record          fname          lname          major            age


SQL::DONE

//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .
[21]select * from student where age > 54
Table: student10 Record:0
    Record          fname          lname          major            age


SQL::DONE

//.................
//:Greater Equal  :
//.................
[22]select * from student where lname >= Yang
st1:DelRio:st:Yang
st1:Jackson:st:Yang
st1:Woo:st:Yang
st1:Yao:st:Yang
Table: student11 Record:1
    Record          fname          lname          major            age
         0            Flo            Yao             CS             20


SQL::DONE
//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .
[23]select * from employee where last >= Jack
st1:Jackson:st:Jack
st1:VanGogh:st:Jack
st1:Blow:st:Jack
st1:Johnson:st:Jack
st1:Yang:st:Jack
Table: employee3 Record:5
    Record           last          first            dep
         0        Jackson          Billy           Math
         1       Van Gogh        Jim Bob        Phys Ed
         2        Johnson          Jimmy      Chemistry
         3        Johnson          Billy        Phys Ed
         4           Yang             Bo             CS


SQL::DONE


//.................
//:Less Than      :
//.................


//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[24]select * from student where lname < Jackson
Table: student12 Record:1
    Record          fname          lname          major            age
         0     Anna Grace        Del Rio             CS             22


SQL::DONE

//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .
[25]select * from student where age  < 20
Table: student13 Record:0
    Record          fname          lname          major            age


SQL::DONE


//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .

[26]select * from student where age  < 19
Table: student14 Record:0
    Record          fname          lname          major            age


SQL::DONE


//.................
//:Less Equal     :
//.................

[27]select * from student where lname <= Smith
st1:DelRio:st:Smith
st1:Jackson:st:Smith
st1:Woo:st:Smith
st1:Yao:st:Smith
Table: student15 Record:2
    Record          fname          lname          major            age
         0     Anna Grace        Del Rio             CS             22
         1            Flo        Jackson           Math             21


SQL::DONE

//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .
[28]select * from employee where last <= Peach
st1:Jackson:st:Peach
st1:VanGogh:st:Peach
st1:Blow:st:Peach
st1:Johnson:st:Peach
st1:Yang:st:Peach
Table: employee4 Record:4
    Record           last          first            dep
         0        Jackson          Billy           Math
         1           Blow            Joe             CS
         2        Johnson          Jimmy      Chemistry
         3        Johnson          Billy        Phys Ed


SQL::DONE

//****************************************************************************
//              LOGICAL OPERATORS
//****************************************************************************


//.................
//:AND            :
//.................

[29]select * from student where fname = "Flo" and lname = "Yao"
Table: student16 Record:1
    Record          fname          lname          major            age
         0            Flo            Yao             CS             20


SQL::DONE


//.................
//:OR            :
//.................
[30]select * from student where fname = Flo or lname = Jackson
Table: student17 Record:2
    Record          fname          lname          major            age
         0            Flo            Yao             CS             20
         1            Flo        Jackson           Math             21


SQL::DONE


//.................
//:OR AND         :
//.................
[31]select * from student where fname = Flo or major = CS and age <= 23
st1:20:st:23
st1:21:st:23
st1:22:st:23
Table: student18 Record:3
    Record          fname          lname          major            age
         0            Flo            Yao             CS             20
         1            Flo        Jackson           Math             21
         2     Anna Grace        Del Rio             CS             22


SQL::DONE


//.................
//:AND OR AND     :
//.................

[32]select * from student where age <30 and major=CS or major = Physics and lname = Jackson
Table: student19 Record:2
    Record          fname          lname          major            age
         0            Flo            Yao             CS             20
         1     Anna Grace        Del Rio             CS             22


SQL::DONE


//.................
//:OR AND OR      :
//.................

[33]select * from student where lname = Yang or major = CS and age < 23 or lname = Jackson
Table: student20 Record:3
    Record          fname          lname          major            age
         0            Flo            Yao             CS             20
         1            Flo        Jackson           Math             21
         2     Anna Grace        Del Rio             CS             22


SQL::DONE






SQL::DONE
>

  */
#endif // OUTPUT_H
