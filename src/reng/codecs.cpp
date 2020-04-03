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

#include "datas/masterprinter.hpp"
#include "motion_78.hpp"
#include <unordered_map>

struct _REMinMaxBounds {
  Vector4A16 min;
  Vector4A16 max;
};

struct RETrackController_internal : RETrackController {
  enum FrameType { FrameType_short = 4, FrameType_char = 2 };
  _REMinMaxBounds minMaxBounds;
  FrameType frameType;
  int componentID;
  uchar *frames;
  uint numFrames;

  template <class C> void _Assign(C *data) {
    frameType = static_cast<FrameType>((data->flags >> 20) & 0xf);

    if (data->minMaxBounds) {
      minMaxBounds.max = Vector4A16(data->minMaxBounds->max);
      minMaxBounds.min = Vector4A16(data->minMaxBounds->min);
    }

    componentID = ((data->flags >> 12) & 0xf) - 1;
    frames = data->frames.operator->();
    numFrames = data->numFrames;
    Assign(data->controlPoints.operator->());
  }

  virtual void Assign(char *data) = 0;
  void Assign(RETrackCurve *iCurve) { _Assign(iCurve); }
  void Assign(RETrackCurve78 *iCurve) { _Assign(iCurve); }

  ushort GetFrame(int id) const {
    if (frameType == FrameType_short)
      return *(reinterpret_cast<ushort *>(frames) + id);
    else
      return *(frames + id);
  }
};

struct LinearVector3Controller : RETrackController_internal {
  static const int ID = 0xF2;
  typedef std::allocator_hybrid<Vector> Alloc_Type;
  typedef std::vector<Vector, Alloc_Type> Storage_Type;
  Storage_Type dataStorage;

  void Assign(char *data) override {
    Vector *start = reinterpret_cast<Vector *>(data);
    dataStorage = Storage_Type(start, start + numFrames, Alloc_Type(start));
  }

  void Evaluate(int id, Vector4A16 &out) const { out = dataStorage[id]; }
};

struct BiLinearVector3_5bitController : RETrackController_internal {
  static const int ID = 0x200F2;
  typedef std::allocator_hybrid<ushort> Alloc_Type;
  typedef std::vector<ushort, Alloc_Type> Storage_Type;
  Storage_Type dataStorage;

  static const int componentMask = 0x1f;
  static const float componentMultiplier;

  void Assign(char *data) override {
    ushort *start = reinterpret_cast<ushort *>(data);
    dataStorage = Storage_Type(start, start + numFrames, Alloc_Type(start));
  }

  void Evaluate(int id, Vector4A16 &out) const {
    const ushort &retreived = dataStorage[id];
    out = Vector(static_cast<float>(retreived & componentMask),
                 static_cast<float>((retreived >> 5) & componentMask),
                 static_cast<float>((retreived >> 10) & componentMask));
    out = ((out * componentMultiplier) * minMaxBounds.min) + minMaxBounds.max;
  }
};

const float BiLinearVector3_5bitController::componentMultiplier =
    1.0f / static_cast<float>(componentMask);

struct BiLinearVector3_10bitController : RETrackController_internal {
  static const int ID = 0x400F2;
  typedef std::allocator_hybrid<uint> Alloc_Type;
  typedef std::vector<uint, Alloc_Type> Storage_Type;
  Storage_Type dataStorage;

  static const int componentMask = 0x3ff;
  static const float componentMultiplier;

  void Assign(char *data) override {
    uint *start = reinterpret_cast<uint *>(data);
    dataStorage = Storage_Type(start, start + numFrames, Alloc_Type(start));
  }

  void Evaluate(int id, Vector4A16 &out) const {
    const uint &retreived = dataStorage[id];
    out =
        Vector4A16(static_cast<float>(retreived & componentMask),
                   static_cast<float>((retreived >> 10) & componentMask),
                   static_cast<float>((retreived >> 20) & componentMask), 0.0f);
    out = ((out * componentMultiplier) * minMaxBounds.min) + minMaxBounds.max;
  }
};

const float BiLinearVector3_10bitController::componentMultiplier =
    1.0f / static_cast<float>(componentMask);

struct BiLinearVector3_21bitController : RETrackController_internal {
  static const int ID = 0x800F2;
  typedef std::allocator_hybrid<uint64> Alloc_Type;
  typedef std::vector<uint64, Alloc_Type> Storage_Type;
  Storage_Type dataStorage;

  static const uint64 componentMask = (1 << 21) - 1;
  static const float componentMultiplier;

  void Assign(char *data) override {
    uint64 *start = reinterpret_cast<uint64 *>(data);
    dataStorage = Storage_Type(start, start + numFrames, Alloc_Type(start));
  }

  void Evaluate(int id, Vector4A16 &out) const {
    const uint64 &retreived = dataStorage[id];
    out =
        Vector4A16(static_cast<float>(retreived & componentMask),
                   static_cast<float>((retreived >> 21) & componentMask),
                   static_cast<float>((retreived >> 42) & componentMask), 0.0f);
    out = ((out * componentMultiplier) * minMaxBounds.min) + minMaxBounds.max;
  }
};

const float BiLinearVector3_21bitController::componentMultiplier =
    1.0f / static_cast<float>(componentMask);

struct BiLinearQuat3_13bitController : RETrackController_internal {
  static const int ID = 0x50112;
  struct SType {
    uchar data[5];
  };
  typedef std::allocator_hybrid<SType> Alloc_Type;
  typedef std::vector<SType, Alloc_Type> Storage_Type;
  Storage_Type dataStorage;

  static const uint64 componentMask = (1 << 13) - 1;
  static const float componentMultiplier;

  void Assign(char *data) override {
    SType *start = reinterpret_cast<SType *>(data);
    dataStorage = Storage_Type(start, start + numFrames, Alloc_Type(start));
  }

  void Evaluate(int id, Vector4A16 &out) const {
    const uint64 retreived =
        (static_cast<uint64>(dataStorage[id].data[0]) << 32) |
        (static_cast<uint64>(dataStorage[id].data[1]) << 24) |
        (static_cast<uint64>(dataStorage[id].data[2]) << 16) |
        (static_cast<uint64>(dataStorage[id].data[3]) << 8) |
        (static_cast<uint64>(dataStorage[id].data[4]) << 0);

    out =
        Vector4A16(static_cast<float>(retreived & componentMask),
                   static_cast<float>((retreived >> 13) & componentMask),
                   static_cast<float>((retreived >> 26) & componentMask), 0.0f);
    out = ((out * componentMultiplier) * minMaxBounds.min) + minMaxBounds.max;
    out *= Vector4A16(1.f, 1.f, 1.f, 0.0f);
    out.QComputeElement();
  }
};

const float BiLinearQuat3_13bitController::componentMultiplier =
    1.0f / static_cast<float>(componentMask);

struct BiLinearQuat3_8bitController : RETrackController_internal {
  static const int ID = 0x30112;
  typedef std::allocator_hybrid<UCVector> Alloc_Type;
  typedef std::vector<UCVector, Alloc_Type> Storage_Type;
  Storage_Type dataStorage;

  static const int componentMask = 0xff;
  static const float componentMultiplier;

  void Assign(char *data) override {
    UCVector *start = reinterpret_cast<UCVector *>(data);
    dataStorage = Storage_Type(start, start + numFrames, Alloc_Type(start));
  }

  void Evaluate(int id, Vector4A16 &out) const {
    out = Vector4A16(dataStorage[id].Convert<float>());
    out = ((out * componentMultiplier) * minMaxBounds.min) + minMaxBounds.max;
    out *= Vector4A16(1.f, 1.f, 1.f, 0.0f);
    out.QComputeElement();
  }
};

const float BiLinearQuat3_8bitController::componentMultiplier =
    1.0f / static_cast<float>(componentMask);

struct LinearQuat3Controller : LinearVector3Controller {
  static const int ID1 = 0xB0112;
  static const int ID2 = 0xC0112;

  void Evaluate(int id, Vector4A16 &out) const {
    LinearVector3Controller::Evaluate(id, out);
    out *= Vector4A16(1.f, 1.f, 1.f, 0.0f);
    out.QComputeElement();
  }
};

struct BiLinearQuat3_5bitController : BiLinearVector3_5bitController {
  static const int ID = 0x20112;

  void Evaluate(int id, Vector4A16 &out) const {
    BiLinearVector3_5bitController::Evaluate(id, out);
    out *= Vector4A16(1.f, 1.f, 1.f, 0.0f);
    out.QComputeElement();
  }
};

struct BiLinearQuat3_10bitController : BiLinearVector3_10bitController {
  static const int ID1 = 0x30112;
  static const int ID2 = 0x40112;

  void Evaluate(int id, Vector4A16 &out) const {
    BiLinearVector3_10bitController::Evaluate(id, out);
    out *= Vector4A16(1.f, 1.f, 1.f, 0.0f);
    out.QComputeElement();
  }
};

struct BiLinearQuat3_21bitController : BiLinearVector3_21bitController {
  static const int ID = 0x70112;

  void Evaluate(int id, Vector4A16 &out) const {
    BiLinearVector3_21bitController::Evaluate(id, out);
    out *= Vector4A16(1.f, 1.f, 1.f, 0.0f);
    out.QComputeElement();
  }
};

struct LinearSCVector3Controller : RETrackController_internal {
  static const int ID1 = 0x310F2;
  static const int ID2 = 0x320F2;
  static const int ID3 = 0x330F2;
  static const int ID4 = 0x340F2;
  static const int ID5 = 0x410F2;
  static const int ID6 = 0x420F2;
  static const int ID7 = 0x430F2;
  static const int ID8 = 0x440F2;

  typedef std::allocator_hybrid<float> Alloc_Type;
  typedef std::vector<Alloc_Type::value_type, Alloc_Type> Storage_Type;
  Storage_Type dataStorage;

  void Assign(char *data) override {
    float *start = reinterpret_cast<float *>(data);
    dataStorage = Storage_Type(start, start + numFrames, Alloc_Type(start));
  }

  void Evaluate(int id, Vector4A16 &out) const {
    const float &retreived = dataStorage[id];
    if (componentID == 3) {
      out = Vector4A16(retreived);
    } else {
      out = minMaxBounds.min;
      out[componentID] = retreived;
    }
  }
};

struct BiLinearSCVector3_16bitController : RETrackController_internal {
  static const int ID1 = 0x210F2;
  static const int ID2 = 0x220F2;
  static const int ID3 = 0x230F2;
  static const int ID4 = 0x240F2;

  typedef std::allocator_hybrid<ushort> Alloc_Type;
  typedef std::vector<Alloc_Type::value_type, Alloc_Type> Storage_Type;
  Storage_Type dataStorage;

  static const int componentMask = (1 << 16) - 1;
  static const float componentMultiplier;

  void Assign(char *data) override {
    ushort *start = reinterpret_cast<ushort *>(data);
    dataStorage = Storage_Type(start, start + numFrames, Alloc_Type(start));
  }

  void Evaluate(int id, Vector4A16 &out) const {
    const ushort &retreived = dataStorage[id];
    float decompVal = minMaxBounds.min[0] +
                      (minMaxBounds.min[(componentID % 3) + 1] *
                       (static_cast<float>(retreived) * componentMultiplier));
    if (componentID == 3) {
      out = Vector4A16(decompVal);
    } else {
      out.X = minMaxBounds.min.Y;
      out.Y = minMaxBounds.min.Z;
      out.Z = minMaxBounds.min.W;
      out[componentID] = decompVal;
    }
  }
};

const float BiLinearSCVector3_16bitController::componentMultiplier =
    1.0f / static_cast<float>(componentMask);

struct BiLinearSCQuat3Controller : LinearSCVector3Controller {
  static const int ID1 = 0x31112;
  static const int ID2 = 0x32112;
  static const int ID3 = 0x33112;
  static const int ID4 = 0x41112;
  static const int ID5 = 0x42112;
  static const int ID6 = 0x43112;

  void Evaluate(int id, Vector4A16 &out) const {
    out[componentID] = dataStorage[id];
    out.QComputeElement();
  }
};

struct BiLinearSCQuat3_16bitController : BiLinearSCVector3_16bitController {
  static const int ID1 = 0x21112;
  static const int ID2 = 0x22112;
  static const int ID3 = 0x23112;

  void Evaluate(int id, Vector4A16 &out) const {
    const ushort &retreived = dataStorage[id];
    out[componentID] = minMaxBounds.min[1] +
                       (minMaxBounds.min[0] *
                        (static_cast<float>(retreived) * componentMultiplier));
    out.QComputeElement();
  }
};

template <class C> RETrackController_internal *controlDummy() { return new C; }

static const std::unordered_map<int, RETrackController_internal *(*)()>
    curveControllers = {
        {LinearVector3Controller::ID, controlDummy<LinearVector3Controller>},
        {LinearQuat3Controller::ID1, controlDummy<LinearQuat3Controller>},

        {BiLinearSCQuat3Controller::ID1,
         controlDummy<BiLinearSCQuat3Controller>},
        {BiLinearSCQuat3Controller::ID2,
         controlDummy<BiLinearSCQuat3Controller>},
        {BiLinearSCQuat3Controller::ID3,
         controlDummy<BiLinearSCQuat3Controller>},

        {BiLinearSCQuat3_16bitController::ID1,
         controlDummy<BiLinearSCQuat3_16bitController>},
        {BiLinearSCQuat3_16bitController::ID2,
         controlDummy<BiLinearSCQuat3_16bitController>},
        {BiLinearSCQuat3_16bitController::ID3,
         controlDummy<BiLinearSCQuat3_16bitController>},

        {LinearSCVector3Controller::ID1,
         controlDummy<LinearSCVector3Controller>},
        {LinearSCVector3Controller::ID2,
         controlDummy<LinearSCVector3Controller>},
        {LinearSCVector3Controller::ID3,
         controlDummy<LinearSCVector3Controller>},
        {LinearSCVector3Controller::ID4,
         controlDummy<LinearSCVector3Controller>},

        {BiLinearSCVector3_16bitController::ID1,
         controlDummy<BiLinearSCVector3_16bitController>},
        {BiLinearSCVector3_16bitController::ID2,
         controlDummy<BiLinearSCVector3_16bitController>},
        {BiLinearSCVector3_16bitController::ID3,
         controlDummy<BiLinearSCVector3_16bitController>},
        {BiLinearSCVector3_16bitController::ID4,
         controlDummy<BiLinearSCVector3_16bitController>},

        {BiLinearQuat3_10bitController::ID1,
         controlDummy<BiLinearQuat3_10bitController>},
        {BiLinearQuat3_21bitController::ID,
         controlDummy<BiLinearQuat3_21bitController>},
};

RETrackController *RETrackCurve::GetController() {
  const int type = flags & 0xff0fffff;
  RETrackController_internal *iCon = nullptr;

  if (curveControllers.count(type)) {
    iCon = curveControllers.at(type)();
    iCon->Assign(this);
  } else {
    printerror("[RETrackController]: Unhandled curve compression: ",
               << std::hex << type);
  }

  return iCon;
}

static const std::unordered_map<int, RETrackController_internal *(*)()>
    curveControllers78 = {
        {LinearVector3Controller::ID, controlDummy<LinearVector3Controller>},
        {LinearQuat3Controller::ID2, controlDummy<LinearQuat3Controller>},

        {BiLinearSCQuat3Controller::ID4,
         controlDummy<BiLinearSCQuat3Controller>},
        {BiLinearSCQuat3Controller::ID5,
         controlDummy<BiLinearSCQuat3Controller>},
        {BiLinearSCQuat3Controller::ID6,
         controlDummy<BiLinearSCQuat3Controller>},

        {BiLinearSCQuat3_16bitController::ID1,
         controlDummy<BiLinearSCQuat3_16bitController>},
        {BiLinearSCQuat3_16bitController::ID2,
         controlDummy<BiLinearSCQuat3_16bitController>},
        {BiLinearSCQuat3_16bitController::ID3,
         controlDummy<BiLinearSCQuat3_16bitController>},

        {LinearSCVector3Controller::ID5,
         controlDummy<LinearSCVector3Controller>},
        {LinearSCVector3Controller::ID6,
         controlDummy<LinearSCVector3Controller>},
        {LinearSCVector3Controller::ID7,
         controlDummy<LinearSCVector3Controller>},
        {LinearSCVector3Controller::ID8,
         controlDummy<LinearSCVector3Controller>},

        {BiLinearSCVector3_16bitController::ID1,
         controlDummy<BiLinearSCVector3_16bitController>},
        {BiLinearSCVector3_16bitController::ID2,
         controlDummy<BiLinearSCVector3_16bitController>},
        {BiLinearSCVector3_16bitController::ID3,
         controlDummy<BiLinearSCVector3_16bitController>},
        {BiLinearSCVector3_16bitController::ID4,
         controlDummy<BiLinearSCVector3_16bitController>},

        {BiLinearVector3_5bitController::ID,
         controlDummy<BiLinearVector3_5bitController>},
        {BiLinearVector3_10bitController::ID,
         controlDummy<BiLinearVector3_10bitController>},
        {BiLinearVector3_21bitController::ID,
         controlDummy<BiLinearVector3_21bitController>},

        {BiLinearQuat3_5bitController::ID,
         controlDummy<BiLinearQuat3_5bitController>},
        {BiLinearQuat3_8bitController::ID,
         controlDummy<BiLinearQuat3_8bitController>},
        {BiLinearQuat3_10bitController::ID2,
         controlDummy<BiLinearQuat3_10bitController>},
        {BiLinearQuat3_13bitController::ID,
         controlDummy<BiLinearQuat3_13bitController>},
};

RETrackController *RETrackCurve78::GetController() {
  const int type = flags & 0xff0fffff;
  RETrackController_internal *iCon = nullptr;

  if (curveControllers78.count(type)) {
    iCon = curveControllers78.at(type)();
    iCon->Assign(this);
  } else {
    printerror("[RETrackController]: Unhandled curve compression: ",
               << std::hex << type);
  }

  return iCon;
}