/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2015. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef NT_BASE64_H_
#define NT_BASE64_H_

#include <cstddef>
#include <string>

#include "llvm/StringRef.h"

namespace nt {

std::size_t Base64Decode(llvm::StringRef encoded, std::string* plain);
void Base64Encode(llvm::StringRef plain, std::string* encoded);

}  // namespace nt

#endif  // NT_BASE64_H_
