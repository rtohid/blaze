//=================================================================================================
/*!
//  \file blaze/math/typetraits/IsMatrix.h
//  \brief Header file for the IsMatrix type trait
//
//  Copyright (C) 2012-2018 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_TYPETRAITS_ISMATRIX_H_
#define _BLAZE_MATH_TYPETRAITS_ISMATRIX_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <utility>
#include <blaze/math/expressions/Matrix.h>
#include <blaze/util/FalseType.h>
#include <blaze/util/TrueType.h>


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Auxiliary helper struct for the IsMatrix type trait.
// \ingroup math_type_traits
*/
template< typename T >
struct IsMatrixHelper
{
 private:
   //**********************************************************************************************
   template< typename MT, bool SO >
   static TrueType test( const Matrix<MT,SO>& );

   template< typename MT, bool SO >
   static TrueType test( const volatile Matrix<MT,SO>& );

   static FalseType test( ... );
   //**********************************************************************************************

 public:
   //**********************************************************************************************
   using Type = decltype( test( std::declval<T&>() ) );
   //**********************************************************************************************
};
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Compile time check for matrix types.
// \ingroup math_type_traits
//
// This type trait tests whether or not the given template parameter is a N-dimensional dense
// or sparse matrix type. In case the type is a matrix type, the \a value member constant is
// set to \a true, the nested type definition \a Type is \a TrueType, and the class derives
// from \a TrueType. Otherwise \a yes is set to \a false, \a Type is \a FalseType, and the
// class derives from \a FalseType.

   \code
   blaze::IsMatrix< StaticMatrix<float,3U,3U,false> >::value  // Evaluates to 1
   blaze::IsMatrix< const DynamicMatrix<double,true> >::Type  // Results in TrueType
   blaze::IsMatrix< volatile CompressedMatrix<int,true> >     // Is derived from TrueType
   blaze::IsMatrix< StaticVector<float,3U,false> >::value     // Evaluates to 0
   blaze::IsMatrix< const DynamicVector<double,true> >::Type  // Results in FalseType
   blaze::IsMatrix< volatile CompressedVector<int,true> >     // Is derived from FalseType
   \endcode
*/
template< typename T >
struct IsMatrix
   : public IsMatrixHelper<T>::Type
{};
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Auxiliary variable template for the IsMatrix type trait.
// \ingroup type_traits
//
// The IsMatrix_v variable template provides a convenient shortcut to access the nested \a value
// of the IsMatrix class template. For instance, given the type \a T the following two statements
// are identical:

   \code
   constexpr bool value1 = blaze::IsMatrix<T>::value;
   constexpr bool value2 = blaze::IsMatrix_v<T>;
   \endcode
*/
template< typename T >
constexpr bool IsMatrix_v = IsMatrix<T>::value;
//*************************************************************************************************

} // namespace blaze

#endif
