/*  Revil Format Library
    Copyright(C) 2017-2020 Lukas Cone

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#include "datas/supercore.hpp"

template <class C, typename B> union _REPointer {
  typedef C value_type;

private:
  char *rawPtr;
  C *pointer;
  B varPtr;

public:
  operator C *() { return pointer; }
  C &operator*() { return *pointer; }
  C *operator->() { return pointer; }
  _REPointer &operator=(C *input) {
    pointer = input;
    return *this;
  }

  operator const C *() const { return pointer; }
  const C &operator*() const { return *pointer; }
  const C *operator->() const { return pointer; }

  void Fixup(char *masterBuffer) {
    if (!varPtr || rawPtr > masterBuffer)
      return;

    rawPtr = masterBuffer + varPtr;
  }
};

template <class C> using REPointerX64 = _REPointer<C, uint64>;

template <class C> struct _REPointerX86 {
  typedef C value_type;

private:
  uint32 varPtr;

public:
  operator C *() {
    return reinterpret_cast<C *>(reinterpret_cast<char *>(&varPtr) + varPtr);
  }

  C &operator*() { return *static_cast<C *>(*this); }
  C *operator->() { return *this; }

  operator const C *() const {
    return reinterpret_cast<const C *>(reinterpret_cast<const char *>(&varPtr) +
                                       varPtr);
  }
  const C &operator*() const { return *static_cast<C *>(*this); }
  const C *operator->() const { return *this; }

  void Fixup(char *masterBuffer) {
    if (!varPtr ||
        reinterpret_cast<char *>(static_cast<uintptr_t>(varPtr)) > masterBuffer)
      return;

    uintptr_t rawAddr = reinterpret_cast<uintptr_t>(masterBuffer) + varPtr;
    varPtr =
        static_cast<uint32>(rawAddr - reinterpret_cast<uintptr_t>(&varPtr));
  }
};

template <class C, bool x64> struct ___REPointerX86 {
  typedef _REPointerX86<C> value_type;
};
template <class C> struct ___REPointerX86<C, false> {
  typedef _REPointer<C, uint32> value_type;
};

template <class C>
using REPointerX86 = typename ___REPointerX86<C, ES_X64>::value_type;