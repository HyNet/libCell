/*!
 * @file atom_val.hpp
 * @brief 简要说明
 *
 *  详细说明
 *
 * @author
 * @date 2017/01/25
 * @version
 * @note
 */

#ifndef CELL_ATOM_VAL_HPP
#define CELL_ATOM_VAL_HPP

#include <cstdint>

namespace cell {
namespace detail {

namespace {

	// encodes ASCII characters to 6bit encoding
	/*
	 *  "A" == 41 in ASCII
	 *  "B" == 42 in ASCII
	 *  "1" == 31 in ASCII
	 */
	constexpr unsigned char encoding_table[] =
	{
		/*       ..0 ..1 ..2 ..3 ..4 ..5 ..6 ..7 ..8 ..9 ..A ..B ..C ..D ..E ..F  */
		/* 0.. */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		/* 1.. */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		/* 2.. */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		/* 3.. */  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 0,  0,  0,  0,  0,  0,
		/* 4.. */  0, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
		/* 5.. */ 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,  0,  0,  0,  0, 37,
		/* 6.. */  0, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
		/* 7.. */ 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,  0,  0,  0,  0,  0
	};

	// decodes 6bit characters to ASCII
	constexpr char decoding_table[] = " 0123456789"
										"ABCDEFGHIJKLMNOPQRSTUVWXYZ_"
										"abcdefghijklmnopqrstuvwxyz";
}  // namespace <anonymous>

constexpr uint64_t next_interim(uint64_t current, size_t char_code)
{
	// 0x7F is the size of encoding_table
	return (current << 6) | encoding_table[(char_code <= 0x7F) ? char_code : 0];
}


/*!
 *   @param   cstr  被转换的字符
 *   @param   interim  default:0xF
 *   @return  输入的字符串中每个字符按照ASCII码映射到encoding_table之后得到的uint64_t数值
 *   @note    输入的字符串一定要以'\0'结尾，字符串的长度控制在10个以内
 */
constexpr uint64_t atom_val(const char* cstr, uint64_t interim = 0xF)
{
	return (*cstr == '\0') ?
		interim :
		atom_val(cstr + 1,
			next_interim(interim, static_cast<size_t>(*cstr)));
}

} // namespace detail
} // namespace cell

#endif /*CELL_ATOM_VAL_HPP*/