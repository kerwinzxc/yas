
// Copyright (c) 2010-2016 niXman (i dot nixman dog gmail dot com). All
// rights reserved.
//
// This file is part of YAS(https://github.com/niXman/yas) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef _yas_test__yas_pair_hpp__included_
#define _yas_test__yas_pair_hpp__included_

/***************************************************************************/

namespace _yas_pair_test_ {

struct type0: private ::yas::detail::noncopyable {
	int v;

	type0(int v)
		:v(v)
	{}

	template<typename Archive>
	void serialize(Archive &ar) {
		ar & YAS_PAIR(v);
	}
};

}

template<typename archive_traits>
bool yas_pair_test(const char* archive_type, const char* io_type) {
	{
		int i0 = 3, i1 = 0;
		const char *s0 = "i0";
		auto p0 = yas::make_pair(s0, i0);
		auto p1 = yas::make_pair("i1", i1);

		typename archive_traits::oarchive oa;
		archive_traits::ocreate(oa, archive_type, io_type);
		oa & p0;

		typename archive_traits::iarchive ia;
		archive_traits::icreate(ia, oa, archive_type, io_type);
		ia & p1;

		if ( i0 != i1 ) {
			std::cout << "YAS_PAIR deserialization error! [1]" << std::endl;
			return false;
		}
	}
	{
		const int i0 = 4;
		int i1 = 0;
		auto p0 = yas::make_pair("i0", i0);
		auto p1 = yas::make_pair("i1", i1);

		typename archive_traits::oarchive oa;
		archive_traits::ocreate(oa, archive_type, io_type);
		oa & p0;

		typename archive_traits::iarchive ia;
		archive_traits::icreate(ia, oa, archive_type, io_type);
		ia & p1;

		if ( i0 != i1 ) {
			std::cout << "YAS_PAIR deserialization error! [2]" << std::endl;
			return false;
		}
	}
	{
		int i0 = 3, i1 = 0;

		typename archive_traits::oarchive oa;
		archive_traits::ocreate(oa, archive_type, io_type);
		oa & yas::make_pair("i0", i0);

		typename archive_traits::iarchive ia;
		archive_traits::icreate(ia, oa, archive_type, io_type);
		ia & yas::make_pair("i1", i1);

		if ( i0 != i1 ) {
			std::cout << "YAS_PAIR deserialization error! [3]" << std::endl;
			return false;
		}
	}
	{
		_yas_pair_test_::type0 t0(3), t1(0);

		typename archive_traits::oarchive oa;
		archive_traits::ocreate(oa, archive_type, io_type);
		oa & t0;

		typename archive_traits::iarchive ia;
		archive_traits::icreate(ia, oa, archive_type, io_type);
		ia & t1;

		if ( t0.v != t1.v ) {
			std::cout << "YAS_PAIR deserialization error! [4]" << std::endl;
			return false;
		}
	}

	return true;
}

/***************************************************************************/

#endif // _yas_test__yas_pair_hpp__included_
