/*******************************************************************************
 * testsuite/BulkLoadTest.cc
 *
 * STX B+ Tree Test Suite v0.9
 * Copyright (C) 2008-2013 Timo Bingmann
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

//#include <stx/btree_multiset.h>
#include <stx/btree_multimap.h>
#include <stx/btree_map.h>

#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>

#include "tpunit.h"

struct BulkLoadTest : public tpunit::TestFixture
{
    BulkLoadTest() : tpunit::TestFixture(
//                         TEST(BulkLoadTest::test_set),
                         TEST(BulkLoadTest::test_read),
                         TEST(BulkLoadTest::test_insert),
                         TEST(BulkLoadTest::test_read_benchmark),
                         TEST(BulkLoadTest::test_insert_benchmark)
    )
    { }

    typedef stx::btree_multimap<int, std::string,
            std::less<unsigned int>, stx::btree_default_map_traits<int, std::string> > btree_type;

//    template <typename KeyType, typename DataType>
//    struct traits_nodebug : stx::btree_default_map_traits<KeyType, DataType>
//    {
////        static const bool selfverify = true;
//        static const bool debug = false;
//
//        static const unsigned int  leafslots = 20;
//        static const unsigned int  innerslots = 20;
//    };

    void test_sequential_read(size_t numkeys, unsigned int mod)
    {
        typedef stx::btree_multimap<int, std::string,
                                    std::less<unsigned int>, stx::btree_default_map_traits<int, std::string> > btree_type;

        std::pair<int, std::string> pairs[numkeys];

        srand(34234235);
        for (unsigned int i = 0; i < numkeys; i++)
        {
            pairs[i].first = 2 * i;
            pairs[i].second = "key";
        }

        std::sort(pairs, pairs + numkeys);

        btree_type bt;
        bt.bulk_load(pairs, pairs + numkeys);

        unsigned int i = 0;

        for (unsigned int i = 0; i < numkeys; i++) {
            btree_type::iterator iterator = bt.find(pairs[i].first);
            ASSERT(iterator.key() == pairs[i].first);
        }
    }

    void test_random_read(size_t numkeys, unsigned int mod)
    {
        std::pair<int, std::string> pairs[numkeys];

        srand(34234235);
        for (unsigned int i = 0; i < numkeys; i++)
        {
            pairs[i].first = rand() % mod;
            pairs[i].second = "key";
        }

        std::sort(pairs, pairs + numkeys);

        btree_type bt;
        bt.bulk_load(pairs, pairs + numkeys);

        unsigned int i = 0;

        for (unsigned int i = 0; i < numkeys; i++) {
            btree_type::iterator iterator = bt.find(pairs[i].first);
            ASSERT(iterator.key() == pairs[i].first);
        }
    }

    void test_sequential_insert(size_t numkeys, unsigned int mod)
    {
        std::pair<int, std::string> pairs[numkeys];

        srand(34234235);
        srand(34234235);
        for (unsigned int i = 0; i < numkeys; i++)
        {
            pairs[i].first = 3 * i;
            pairs[i].second = "key";
        }

        std::sort(pairs, pairs + numkeys);

        btree_type bt;
        bt.bulk_load(pairs, pairs + numkeys / 2);

        unsigned int i = 0;

        for (unsigned int i = 0; i < numkeys / 2; i++) {
            btree_type::iterator iterator = bt.find(pairs[i].first);
            ASSERT(iterator.key() == pairs[i].first);
        }
        for (unsigned int i = numkeys / 2; i < numkeys; i++) {
            btree_type::iterator iterator = bt.insert(std::make_pair(pairs[i].first, pairs[i].second));
            ASSERT(iterator.key() == pairs[i].first);
        }
        for (unsigned int i = 0; i < numkeys; i++) {
            btree_type::iterator iterator = bt.find(pairs[i].first);
            ASSERT(iterator.key() == pairs[i].first);
        }
    }

    void test_ordered_insert(size_t numkeys, unsigned int mod)
    {
        std::pair<int, std::string> pairs[numkeys];

        srand(34234235);
        for (unsigned int i = 0; i < numkeys; i++)
        {
            pairs[i].first = i * 2;
            pairs[i].second = "key";
        }

        std::sort(pairs, pairs + numkeys);

        btree_type bt;
        bt.bulk_load(pairs, pairs + numkeys);

        unsigned int i = 0;

        for (unsigned int i = 0; i < numkeys; i++) {
            btree_type::iterator iterator = bt.find(pairs[i].first);
            ASSERT(iterator.key() == pairs[i].first);
        }
        for (unsigned int i = 0; i < numkeys; i++) {
            btree_type::iterator iterator = bt.insert(std::make_pair(2*i+1, "key"));
            ASSERT(iterator.key() == 2*i+1);
        }
        for (unsigned int i = 0; i < numkeys * 2; i++) {
            btree_type::iterator iterator = bt.find(i);
            ASSERT(iterator.key() == i);
        }
    }

    void test_random_insert(size_t numkeys, unsigned int mod)
    {
        std::pair<int, std::string> pairs[numkeys];

        srand(34234235);
        srand(34234235);
        for (unsigned int i = 0; i < numkeys; i++)
        {
            pairs[i].first = rand() % mod;
            pairs[i].second = "key";
        }

        std::sort(pairs, pairs + numkeys / 2);

        btree_type bt;
        bt.bulk_load(pairs, pairs + numkeys / 2);

        unsigned int i = 0;

        for (unsigned int i = 0; i < numkeys / 2; i++) {
            btree_type::iterator iterator = bt.find(pairs[i].first);
            ASSERT(iterator.key() == pairs[i].first);
        }
        for (unsigned int i = numkeys / 2; i < numkeys; i++) {
            btree_type::iterator iterator = bt.insert(pairs[i].first, pairs[i].second);
            ASSERT(iterator.key() == pairs[i].first);
        }
        for (unsigned int i = 0; i < numkeys; i++) {
            btree_type::iterator iterator = bt.find(pairs[i].first);
            ASSERT(iterator.key() == pairs[i].first);
        }
    }

    void test_read()
    {
        size_t test_scale = 100000;
        for (size_t n = 100; n <= test_scale; n*=10) {
            test_sequential_read(n, test_scale);
            test_random_read(n, test_scale);
        }
//        std::ostringstream os;
//        bt.print(os);
//        std::cout << os.str() << "\n";
    }

    void test_insert()
    {
        size_t test_scale = 100000;
        for (size_t n = 100; n <= test_scale; n*=10) {
            test_sequential_insert(n, test_scale);
            test_ordered_insert(n, test_scale);
            test_random_insert(n, test_scale);
        }
//        std::ostringstream os;
//        bt.print(os);
//        std::cout << os.str() << "\n";
    }

    void test_read_benchmark()
    {
        size_t test_scale = 100000;

        std::pair<int, std::string> pairs[test_scale];

        srand(34234235);
        for (unsigned int i = 0; i < test_scale; i++)
        {
            pairs[i].first = rand() % test_scale;
            pairs[i].second = "key";
        }

        std::sort(pairs, pairs + test_scale);

        btree_type bt;
        bt.bulk_load(pairs, pairs + test_scale);

        unsigned int i = 0;

        for (unsigned int i = 0; i < test_scale * 100; i++) {
            int key = rand() % test_scale;
            btree_type::iterator iterator = bt.find(pairs[key].first);
            ASSERT(iterator.key() == pairs[key].first);
        }
    }

    void test_insert_benchmark()
    {
        size_t test_scale = 100000;

        std::pair<int, std::string> pairs[test_scale];

        srand(34234235);
        for (unsigned int i = 0; i < test_scale; i++)
        {
            pairs[i].first = rand() % test_scale;
            pairs[i].second = "key";
        }

        std::sort(pairs, pairs + test_scale / 3);

        btree_type bt;
        bt.bulk_load(pairs, pairs + test_scale / 3);

        unsigned int i = 0;

        for (unsigned int i = test_scale / 3; i < test_scale; i++) {
            btree_type::iterator iterator = bt.insert(pairs[i].first, pairs[i].second);
            ASSERT(iterator.key() == pairs[i].first);
        }
    }
} _BulkLoadTest;

/******************************************************************************/
