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
                         TEST(BulkLoadTest::test_map)
                         )
    { }

    template <typename KeyType, typename DataType>
    struct traits_nodebug : stx::btree_default_map_traits<KeyType, DataType>
    {
//        static const bool selfverify = true;
        static const bool debug = true;

        static const unsigned int  leafslots = 20;
        static const unsigned int  innerslots = 20;
    };

//    void test_set_instance(size_t numkeys, unsigned int mod)
//    {
//        typedef stx::btree_multiset<unsigned int,
//                                    std::less<unsigned int>, traits_nodebug<unsigned int> > btree_type;
//
//        std::vector<unsigned int> keys(numkeys);
//
//        srand(34234235);
//        for (unsigned int i = 0; i < numkeys; i++)
//        {
//            keys[i] = rand() % mod;
//        }
//
//        std::sort(keys.begin(), keys.end());
//
//        btree_type bt;
//        bt.bulk_load(keys.begin(), keys.end());
//
//        unsigned int i = 0;
//        for (btree_type::iterator it = bt.begin();
//             it != bt.end(); ++it, ++i)
//        {
//            ASSERT(*it == keys[i]);
//        }
//    }

//    void test_set()
//    {
//        for (size_t n = 6; n < 3200; ++n)
//            test_set_instance(n, 1000);
//
//        test_set_instance(31996, 10000);
//        test_set_instance(32000, 10000);
//        test_set_instance(117649, 100000);
//    }

    void test_bulk_load(size_t numkeys, unsigned int mod)
    {
        typedef stx::btree_multimap<int, std::string,
                                    std::less<unsigned int>, traits_nodebug<int, std::string> > btree_type;

//        std::vector<std::pair<int, std::string> > pairs(numkeys);
        std::pair<int, std::string> pairs[numkeys];

        srand(34234235);
        for (unsigned int i = 0; i < numkeys; i++)
        {
            pairs[i].first = rand() % mod;
//            pairs[i].first = i;
            pairs[i].second = "key";
        }

        std::sort(pairs, pairs + numkeys);

        btree_type bt;
        bt.bulk_load(pairs, pairs + numkeys);
        std::ostringstream os;
        bt.print(os);
        std::cout << os.str() << "\n";

        unsigned int i = 0;

        for (unsigned int i = 0; i < numkeys; i++) {
            std::cout << i << " " << pairs[i].first << "\n";
            btree_type::iterator iterator = bt.find(pairs[i].first);
            ASSERT(iterator.key() == pairs[i].first);
        }
    }

    void test_ordered_insert(size_t numkeys, unsigned int mod)
    {
        typedef stx::btree_multimap<int, int,
                std::less<unsigned int>, traits_nodebug<int, int> > btree_type;

//        std::vector<std::pair<int, std::string> > pairs(numkeys);
        std::pair<int, int> pairs[numkeys];

        srand(34234235);
        for (unsigned int i = 0; i < numkeys; i++)
        {
//            pairs[i].first = rand() % mod;
            pairs[i].first = i * 2;
            pairs[i].second = 999;
        }

        std::sort(pairs, pairs + numkeys);

        btree_type bt;
        bt.bulk_load(pairs, pairs + numkeys);

//        std::ostringstream os;
//        bt.print(os);
//        std::cout << os.str() << "\n";

        unsigned int i = 0;

        for (unsigned int i = 0; i < numkeys; i++) {
//            std::cout << i << " " << pairs[i].first << "\n";
            btree_type::iterator iterator = bt.find(pairs[i].first);
            ASSERT(iterator.key() == pairs[i].first);
        }

        for (unsigned int i = 0; i < numkeys; i++) {
            std::cout << i << " " << 2*i+1 << "\n";
            btree_type::iterator iterator = bt.insert(std::make_pair(2*i+1, 999));
            ASSERT(iterator.key() == 2*i+1);
            std::ostringstream os;
            bt.print(os);
            std::cout << os.str() << "\n";
        }
//
        int count = 0;
        for (unsigned int i = 4; i < numkeys * 2; i++) {
//            std::cout << i << " " << pairs[i].first << "\n";
            btree_type::iterator iterator = bt.find(i);
            std::cout << i << " " << iterator.key() << "\n";
            if (iterator.key() != i) {
//                std::ostringstream os;
//                bt.print(os);
//                std::cout << os.str() << "\n";
                count++;
            }
//            ASSERT(iterator.key() == i);
        }
        std::cout << count << "\n";
    }

    void test_map()
    {
//        for (size_t n = 6; n < 3200; ++n)
//            test_map_instance(n, 1000);
//        test_bulk_load(100, 1000000);
        test_ordered_insert(100, 1000000);
//        test_map_instance(31996, 10000);
//        test_map_instance(32000, 10000);
//        test_map_instance(117649, 100000);
    }
} _BulkLoadTest;

/******************************************************************************/
