
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

#include <iostream>

#include <yas/text_oarchive.hpp>
#include <yas/text_iarchive.hpp>

/***************************************************************************/

struct my_ostream: yas::detail::noncopyable {
	enum { bufsize = 1024 };

	my_ostream()
		:cur(buf)
	{
		std::memset(buf, 0, bufsize);
	}

	std::size_t write(const void *ptr, const std::size_t size) {
		std::memcpy(cur, ((const char*)ptr), size);
		cur += size;
		*cur = 0;
		return size;
	}

	char buf[bufsize];
	char *cur;
};

struct my_istream: yas::detail::noncopyable {
	my_istream(const char *ptr, const std::size_t size)
		:cur(ptr)
		,end(ptr+size)
	{}

	std::size_t read(void *ptr, const std::size_t size) {
		if ( cur+size > end ) return 0;
		std::memcpy(ptr, cur, size);
		cur += size;
		return size;
	}

	const char *cur;
	const char *end;
};

/***************************************************************************/

int main() {
	std::uint32_t v0 = 444, v1 = 0;
	my_ostream os;
	yas::text_oarchive<my_ostream> oa(os);
	oa & v0;

	std::cout << "buf:" << os.buf << std::endl;

	my_istream is(os.buf, os.cur-os.buf);
	yas::text_iarchive<my_istream> ia(is);
	ia & v1;

	if ( v0 != v1 )
		YAS_THROW_EXCEPTION(std::runtime_error, "bad value");
}

/***************************************************************************/
