#-------------------------------------------------
#
# Project created by QtCreator 2015-05-25T23:51:24
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Introduction_to_algorithms
CONFIG   += console
CONFIG   -= app_bundle
CONFIG+=c++11
CONFIG+=no_keywords

TEMPLATE = app

SOURCES += \
    kmptest.cpp \
    heaptest.cpp \
    test.cpp \
    avltest.cpp \
    mergesorttest.cpp \
    maxsubarraytest.cpp \
    quicksorttest.cpp

HEADERS += \
    heap.h \
    heapsort.h \
    catch.hpp \
    kmp.h \
    avltree.h \
    mergesort.h \
    densematrix.h \
    sparsematrix.h \
    linkedlist.h \
    maxsubarray.h \
    qsort.h
