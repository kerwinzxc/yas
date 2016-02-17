
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

#ifndef _yas__text__autoarray_serializer_hpp
#define _yas__text__autoarray_serializer_hpp

#include <yas/detail/type_traits/type_traits.hpp>
#include <yas/detail/type_traits/selector.hpp>
#include <yas/detail/io/serialization_exception.hpp>

namespace yas {
namespace detail {

/***************************************************************************/

template<typename T, size_t N>
struct serializer<
	type_prop::is_array_of_pods,
	ser_method::use_internal_serializer,
	archive_type::text,
	T[N]
> {
	// for chars only
	template<typename Archive, typename U>
	static Archive& save(Archive& ar, const U(&v)[N], YAS_ENABLE_IF_IS_ANY_OF(U, char, signed char, unsigned char)) {
		ar.write((std::uint32_t)N-1);
		ar.write(space_sep);
		ar.write(v, N-1);
		return ar;
	}

	// for bools only
	template<typename Archive, typename U>
	static Archive& save(Archive& ar, const U(&v)[N], YAS_ENABLE_IF_IS_ANY_OF(U, bool)) {
		ar.write((std::uint32_t)N-1);
		ar.write(space_sep);
		for ( const auto &it: v ) {
			ar.write(it);
		}
		return ar;
	}

	// others
	template<typename Archive, typename U>
	static Archive& save(Archive& ar, const U(&v)[N], YAS_DISABLE_IF_IS_ANY_OF(U, char, signed char, unsigned char, bool)) {
		ar.write((std::uint32_t)N);
		ar.write(space_sep);
		for ( const auto &it: v ) {
			ar & it;
		}
		return ar;
	}

	// for chars only
	template<typename Archive, typename U>
	static Archive& load(Archive& ar, U(&v)[N], YAS_ENABLE_IF_IS_ANY_OF(U, char, signed char, unsigned char)) {
		std::uint32_t size = 0;
		ar.read(size);
		if ( size != N-1 ) YAS_THROW_BAD_ARRAY_SIZE();
		if ( ar.getch() != space_sep ) YAS_THROW_SPACE_IS_EXPECTED();
		ar.read(v, size);
		v[size] = 0;
		return ar;
	}

	// for bools
	template<typename Archive, typename U>
	static Archive& load(Archive& ar, U(&v)[N], YAS_ENABLE_IF_IS_ANY_OF(U, bool)) {
		std::uint32_t size = 0;
		ar.read(size);
		if ( size != N ) YAS_THROW_BAD_ARRAY_SIZE();
		if ( ar.getch() != space_sep ) YAS_THROW_SPACE_IS_EXPECTED();
		for ( auto &it: v ) {
			ar.read(it);
		}
		return ar;
	}

	// others
	template<typename Archive, typename U>
	static Archive& load(Archive& ar, U(&v)[N], YAS_DISABLE_IF_IS_ANY_OF(U, char, signed char, unsigned char, bool)) {
		std::uint32_t size = 0;
		ar.read(size);
		if ( size != N ) YAS_THROW_BAD_ARRAY_SIZE();
		if ( ar.getch() != space_sep ) YAS_THROW_SPACE_IS_EXPECTED();
		for ( auto &it: v ) {
			ar & it;
		}
		return ar;
	}
};

/***************************************************************************/

template<typename T, size_t N>
struct serializer<
	type_prop::is_array,
	ser_method::use_internal_serializer,
	archive_type::text,
	T[N]
> {
	template<typename Archive>
	static Archive& save(Archive& ar, const T(&v)[N]) {
		ar.write((std::uint32_t)N);
		ar.write(space_sep);
		for ( const auto &it: v ) {
			ar & it;
		}
		return ar;
	}

	template<typename Archive>
	static Archive& load(Archive& ar, T(&v)[N]) {
		std::uint32_t size = 0;
		ar.read(size);
		if ( size != N ) YAS_THROW_BAD_ARRAY_SIZE();
		if ( ar.getch() != space_sep ) YAS_THROW_SPACE_IS_EXPECTED();
		for ( auto &it: v ) {
			ar & it;
		}
		return ar;
	}
};

/***************************************************************************/

} // namespace detail
} // namespace yas

#endif // _yas__text__autoarray_serializer_hpp
