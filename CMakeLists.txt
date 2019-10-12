cmake_minimum_required(VERSION 3.14)
project(stx_btree)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/stx)
#include_directories(memprofile)
include_directories(testsuite)
#include_directories(wxbtreedemo)

add_executable(stx_btree
        include/stx/btree.h
        include/stx/btree_map.h
        include/stx/btree_multimap.h
        include/stx/btree_multiset.h
        include/stx/btree_set.h
#        memprofile/main.cc
#        memprofile/malloc_count.c
#        memprofile/malloc_count.h
#        memprofile/memprofile.h
#        speedtest/speedtest-tune.cc
#        speedtest/speedtest.cc
        testsuite/BoundTest.cc
        testsuite/BulkLoadTest.cc
        testsuite/DumpRestoreTest.cc
        testsuite/InstantiationTest.cc
        testsuite/IteratorTest.cc
        testsuite/LargeTest.cc
        testsuite/RelationTest.cc
        testsuite/SimpleTest.cc
        testsuite/StructureTest.cc
        testsuite/tpunit.cc
        testsuite/tpunit.h)
#        wxbtreedemo/WMain.cpp
#        wxbtreedemo/WMain.h
#        wxbtreedemo/WMain_wxg.cpp
#        wxbtreedemo/WMain_wxg.h
#        wxbtreedemo/WTreeDrawing.cpp
#        wxbtreedemo/WTreeDrawing.h)
