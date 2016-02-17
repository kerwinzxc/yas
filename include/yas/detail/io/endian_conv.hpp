
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

#ifndef _yas__detail__io__endian_conv_hpp
#define _yas__detail__io__endian_conv_hpp

#include <yas/detail/config/config.hpp>
#include <yas/detail/type_traits/type_traits.hpp>

#include <cstring>

namespace yas {

enum endian_t {
	 big_endian
	,little_endian
	,as_host
};

namespace detail {

/***************************************************************************/

template<bool LE>
struct endian_convertor;

template<>
struct endian_convertor<true> {
	template<typename T>
	static void to_network(std::uint8_t *dst, const T &v) {
		*((T*)dst) = v;
	}

	template<typename T>
	static void from_network(T &v, const std::uint8_t *src) {
		v = *((T*)src);
	}
};

template<>
struct endian_convertor<false> {
	template<typename T>
	struct storage_type {
		enum {
			 is_float  = std::is_same<T, float>::value
			,is_double = std::is_same<T, double>::value
		};
		static_assert(is_float||is_double,"only double or float types is allowed");

		using type = typename std::conditional<
			 is_float
			,std::uint32_t
			,std::uint64_t
		>::type;

		template<typename U>
		static void bswab(U &u, YAS_ENABLE_IF_IS_ANY_OF(U, std::uint32_t)) {
			u = YAS_NETWORK_TO_LOCAL32(u);
		}
		template<typename U>
		static void bswab(U &u, YAS_ENABLE_IF_IS_ANY_OF(U, std::uint64_t)) {
			u = YAS_NETWORK_TO_LOCAL64(u);
		}
	};

	template<typename T>
	static void to_network(std::uint8_t *dst, const T &v) {
		union {
			typename storage_type<T>::type u;
			T v;
		} u;
		u.v = v;

		storage_type<T>::bswab(u.u);
		std::memcpy(dst, &u.u, sizeof(T));
	}

	template<typename T>
	static void from_network(T &v, const std::uint8_t *src) {
		union {
			typename storage_type<T>::type u;
			T v;
		} u;

		std::memcpy(&u.u, src, sizeof(v));
		storage_type<T>::bswab(u.u);
		v = u.v;
	}
};

/***************************************************************************/

} // ns detail
} // ns yas

#endif // _yas__detail__io__endian_conv_hpp
