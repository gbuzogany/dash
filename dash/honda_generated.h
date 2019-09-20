// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_HONDA_DASH_H_
#define FLATBUFFERS_GENERATED_HONDA_DASH_H_

#include "flatbuffers/flatbuffers.h"

namespace dash {

struct statsMessage;

struct statsMessage FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_BATTVOLTAGE = 4,
    VT_COOLANTTEMP = 6,
    VT_AIRINTAKETEMP = 8,
    VT_MANIFOLDPRESSURE = 10,
    VT_SPEED = 12,
    VT_TPS = 14,
    VT_RPM = 16,
    VT_NEUTRAL = 18,
    VT_ENGINERUNNING = 20,
    VT_INJDUR = 22,
    VT_IGNADV = 24
  };
  float battVoltage() const {
    return GetField<float>(VT_BATTVOLTAGE, 0.0f);
  }
  float coolantTemp() const {
    return GetField<float>(VT_COOLANTTEMP, 0.0f);
  }
  float airIntakeTemp() const {
    return GetField<float>(VT_AIRINTAKETEMP, 0.0f);
  }
  float manifoldPressure() const {
    return GetField<float>(VT_MANIFOLDPRESSURE, 0.0f);
  }
  float speed() const {
    return GetField<float>(VT_SPEED, 0.0f);
  }
  float tps() const {
    return GetField<float>(VT_TPS, 0.0f);
  }
  int32_t rpm() const {
    return GetField<int32_t>(VT_RPM, 0);
  }
  int32_t neutral() const {
    return GetField<int32_t>(VT_NEUTRAL, 0);
  }
  int32_t engineRunning() const {
    return GetField<int32_t>(VT_ENGINERUNNING, 0);
  }
  float injDur() const {
    return GetField<float>(VT_INJDUR, 0.0f);
  }
  float ignAdv() const {
    return GetField<float>(VT_IGNADV, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_BATTVOLTAGE) &&
           VerifyField<float>(verifier, VT_COOLANTTEMP) &&
           VerifyField<float>(verifier, VT_AIRINTAKETEMP) &&
           VerifyField<float>(verifier, VT_MANIFOLDPRESSURE) &&
           VerifyField<float>(verifier, VT_SPEED) &&
           VerifyField<float>(verifier, VT_TPS) &&
           VerifyField<int32_t>(verifier, VT_RPM) &&
           VerifyField<int32_t>(verifier, VT_NEUTRAL) &&
           VerifyField<int32_t>(verifier, VT_ENGINERUNNING) &&
           VerifyField<float>(verifier, VT_INJDUR) &&
           VerifyField<float>(verifier, VT_IGNADV) &&
           verifier.EndTable();
  }
};

struct statsMessageBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_battVoltage(float battVoltage) {
    fbb_.AddElement<float>(statsMessage::VT_BATTVOLTAGE, battVoltage, 0.0f);
  }
  void add_coolantTemp(float coolantTemp) {
    fbb_.AddElement<float>(statsMessage::VT_COOLANTTEMP, coolantTemp, 0.0f);
  }
  void add_airIntakeTemp(float airIntakeTemp) {
    fbb_.AddElement<float>(statsMessage::VT_AIRINTAKETEMP, airIntakeTemp, 0.0f);
  }
  void add_manifoldPressure(float manifoldPressure) {
    fbb_.AddElement<float>(statsMessage::VT_MANIFOLDPRESSURE, manifoldPressure, 0.0f);
  }
  void add_speed(float speed) {
    fbb_.AddElement<float>(statsMessage::VT_SPEED, speed, 0.0f);
  }
  void add_tps(float tps) {
    fbb_.AddElement<float>(statsMessage::VT_TPS, tps, 0.0f);
  }
  void add_rpm(int32_t rpm) {
    fbb_.AddElement<int32_t>(statsMessage::VT_RPM, rpm, 0);
  }
  void add_neutral(int32_t neutral) {
    fbb_.AddElement<int32_t>(statsMessage::VT_NEUTRAL, neutral, 0);
  }
  void add_engineRunning(int32_t engineRunning) {
    fbb_.AddElement<int32_t>(statsMessage::VT_ENGINERUNNING, engineRunning, 0);
  }
  void add_injDur(float injDur) {
    fbb_.AddElement<float>(statsMessage::VT_INJDUR, injDur, 0.0f);
  }
  void add_ignAdv(float ignAdv) {
    fbb_.AddElement<float>(statsMessage::VT_IGNADV, ignAdv, 0.0f);
  }
  explicit statsMessageBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  statsMessageBuilder &operator=(const statsMessageBuilder &);
  flatbuffers::Offset<statsMessage> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<statsMessage>(end);
    return o;
  }
};

inline flatbuffers::Offset<statsMessage> CreatestatsMessage(
    flatbuffers::FlatBufferBuilder &_fbb,
    float battVoltage = 0.0f,
    float coolantTemp = 0.0f,
    float airIntakeTemp = 0.0f,
    float manifoldPressure = 0.0f,
    float speed = 0.0f,
    float tps = 0.0f,
    int32_t rpm = 0,
    int32_t neutral = 0,
    int32_t engineRunning = 0,
    float injDur = 0.0f,
    float ignAdv = 0.0f) {
  statsMessageBuilder builder_(_fbb);
  builder_.add_ignAdv(ignAdv);
  builder_.add_injDur(injDur);
  builder_.add_engineRunning(engineRunning);
  builder_.add_neutral(neutral);
  builder_.add_rpm(rpm);
  builder_.add_tps(tps);
  builder_.add_speed(speed);
  builder_.add_manifoldPressure(manifoldPressure);
  builder_.add_airIntakeTemp(airIntakeTemp);
  builder_.add_coolantTemp(coolantTemp);
  builder_.add_battVoltage(battVoltage);
  return builder_.Finish();
}

inline const dash::statsMessage *GetstatsMessage(const void *buf) {
  return flatbuffers::GetRoot<dash::statsMessage>(buf);
}

inline const dash::statsMessage *GetSizePrefixedstatsMessage(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<dash::statsMessage>(buf);
}

inline bool VerifystatsMessageBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<dash::statsMessage>(nullptr);
}

inline bool VerifySizePrefixedstatsMessageBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<dash::statsMessage>(nullptr);
}

inline void FinishstatsMessageBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<dash::statsMessage> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedstatsMessageBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<dash::statsMessage> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace dash

#endif  // FLATBUFFERS_GENERATED_HONDA_DASH_H_
