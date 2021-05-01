TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        !include/adjacency_matrix.cpp \
        !include/file_utility_functions.cpp \
        !include/get_token.cpp \
        !include/stokenizer.cpp \
        !include/token.cpp \
        alpha.cpp \
        left_parenthesis.cpp \
        logical_operator.cpp \
        main.cpp \
        number.cpp \
        operator.cpp \
        parser_class.cpp \
        record.cpp \
        right_parenthesis.cpp \
        rpn.cpp \
        shunting_yard.cpp \
        sql.cpp \
        sy_token.cpp \
        table.cpp \
        vector_long.cpp

HEADERS += \
    !include/add_entry.h \
    !include/adjacency_matrix.h \
    !include/array_functions.h \
    !include/bplustree.h \
    !include/file_utility_functions.h \
    !include/get_token.h \
    !include/mpair.h \
    !include/my_map.h \
    !include/my_mmap.h \
    !include/my_vector.h \
    !include/pair.h \
    !include/queue.h \
    !include/stack_class.h \
    !include/stokenizer.h \
    !include/token.h \
    !include/vector.h \
    alpha.h \
    left_parenthesis.h \
    logical_operator.h \
    number.h \
    operator.h \
    output.h \
    parser_class.h \
    record.h \
    right_parenthesis.h \
    rpn.h \
    shunting_yard.h \
    sql.h \
    sy_token.h \
    table.h \
    vector_long.h \
    work_report.h
