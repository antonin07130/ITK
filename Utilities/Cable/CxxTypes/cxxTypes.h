/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    cxxTypes.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#ifndef _cxxTypes_h
#define _cxxTypes_h

#include "cxxUtils.h"

namespace _cxx_
{

/**
 * Enumeration of identifiers for representation types.
 */
enum RepresentationType
{
  Undefined_id=0,
  
  ArrayType_id, ClassType_id, PointerType_id, PointerToMemberType_id,
  ReferenceType_id, FundamentalType_id, FunctionType_id
};

class TypeSystem;

} // namespace _cxx_

// Include all the representation types.
#include "cxxCvQualifiedType.h"
#include "cxxArrayType.h"
#include "cxxClassType.h"
#include "cxxFunctionType.h"
#include "cxxFundamentalType.h"
#include "cxxPointerType.h"
#include "cxxPointerToMemberType.h"
#include "cxxReferenceType.h"
#include "cxxTypedefType.h"


#endif
