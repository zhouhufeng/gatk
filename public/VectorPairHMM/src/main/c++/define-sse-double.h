/*Copyright (c) 2012 The Broad Institute

*Permission is hereby granted, free of charge, to any person
*obtaining a copy of this software and associated documentation
*files (the "Software"), to deal in the Software without
*restriction, including without limitation the rights to use,
*copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the
*Software is furnished to do so, subject to the following
*conditions:

*The above copyright notice and this permission notice shall be
*included in all copies or substantial portions of the Software.

*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
*OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
*NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
*HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
*THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifdef PRECISION
#undef PRECISION
#undef MAIN_TYPE
#undef MAIN_TYPE_SIZE
#undef UNION_TYPE
#undef IF_128
#undef IF_MAIN_TYPE
#undef SHIFT_CONST1
#undef SHIFT_CONST2
#undef SHIFT_CONST3
#undef _128_TYPE
#undef SIMD_TYPE
#undef AVX_LENGTH
#undef HAP_TYPE
#undef MASK_TYPE
#undef MASK_ALL_ONES

#undef VEC_EXTRACT_UNIT
#undef VEC_INSERT_UNIT
#undef SET_VEC_ZERO
#undef VEC_OR
#undef VEC_ADD
#undef VEC_SUB
#undef VEC_MUL
#undef VEC_DIV
#undef VEC_BLEND
#undef VEC_BLENDV
#undef VEC_CAST_256_128
#undef VEC_EXTRACT_128
#undef VEC_EXTRACT_UNIT
#undef VEC_SET1_VAL128
#undef VEC_MOVE
#undef VEC_CAST_128_256
#undef VEC_INSERT_VAL
#undef VEC_CVT_128_256
#undef VEC_SET1_VAL
#undef VEC_POPCVT_CHAR
#undef VEC_LDPOPCVT_CHAR
#undef VEC_CMP_EQ
#undef VEC_SET_LSE
#undef SHIFT_HAP
#undef MASK_VEC
#undef VEC_SSE_TO_AVX
#undef VEC_SHIFT_LEFT_1BIT
#undef MASK_ALL_ONES
#undef COMPARE_VECS
#undef _256_INT_TYPE
#undef BITMASK_VEC
#endif

#define SSE
#define PRECISION d

#define MAIN_TYPE double
#define MAIN_TYPE_SIZE 64
#define UNION_TYPE mix_D128
#define IF_128 IF_128d
#define IF_MAIN_TYPE IF_64
#define SHIFT_CONST1 1
#define SHIFT_CONST2 8
#define SHIFT_CONST3 0
#define _128_TYPE __m128d
#define SIMD_TYPE __m128d
#define _256_INT_TYPE __m128i
#define AVX_LENGTH 2
#define HAP_TYPE __m128i
#define MASK_TYPE uint64_t
#define MASK_ALL_ONES 0xFFFFFFFFFFFFFFFFL
#define MASK_VEC MaskVec_D

#define VEC_EXTRACT_UNIT(__v1, __im)            \
    _mm_extract_epi64(__v1, __im)

#define VEC_INSERT_UNIT(__v1,__ins,__im)        \
    _mm_insert_epi64(__v1,__ins,__im)

#define VEC_OR(__v1, __v2)                      \
    _mm_or_pd(__v1, __v2)

#define VEC_ADD(__v1, __v2)                     \
    _mm_add_pd(__v1, __v2)

#define VEC_SUB(__v1, __v2)                     \
    _mm_sub_pd(__v1, __v2)

#define VEC_MUL(__v1, __v2)                     \
    _mm_mul_pd(__v1, __v2)

#define VEC_DIV(__v1, __v2)                     \
    _mm_div_pd(__v1, __v2)

#define VEC_CMP_EQ(__v1, __v2)                  \
    _mm_cmpeq_pd(__v1, __v2)

#define VEC_BLEND(__v1, __v2, __mask)           \
    _mm_blend_pd(__v1, __v2, __mask)

#define VEC_BLENDV(__v1, __v2, __maskV)         \
    _mm_blendv_pd(__v1, __v2, __maskV)

#define SHIFT_HAP(__v1, __val)                  \
    __v1 = _mm_insert_epi32(_mm_slli_si128(__v1, 4), __val.i, 0)

#define VEC_CVT_128_256(__v1)                   \
    _mm_cvtepi32_pd(__v1)

#define VEC_SET1_VAL(__val)                     \
    _mm_set1_pd(__val)

#define VEC_POPCVT_CHAR(__ch)                   \
    _mm_cvtepi32_pd(_mm_set1_epi32(__ch))

#define VEC_SET_LSE(__val)                      \
    _mm_set_pd(zero, __val);

#define VEC_LDPOPCVT_CHAR(__addr)               \
    _mm_cvtepi32_pd(_mm_loadu_si128((__m128i const *)__addr))

#define VEC_SSE_TO_AVX(__vsLow, __vsHigh, __vdst)       \
    __vdst = _mm_castsi128_pd(_mm_set_epi64(__vsHigh, __vsLow))

#define VEC_SHIFT_LEFT_1BIT(__vs)               \
    __vs = _mm_slli_epi64(__vs, 1)


class BitMaskVec_sse_double {

    MASK_VEC combined_ ;
    public:
    inline MASK_TYPE& getLowEntry(int index) {
        return combined_.masks[index] ;
    }
    inline MASK_TYPE& getHighEntry(int index) {
        return combined_.masks[AVX_LENGTH/2+index] ;
    }

    inline const SIMD_TYPE& getCombinedMask() {
        return combined_.vecf ;
    }

    inline void shift_left_1bit() {
        VEC_SHIFT_LEFT_1BIT(combined_.vec) ;
    }

} ;

#define BITMASK_VEC BitMaskVec_sse_double

