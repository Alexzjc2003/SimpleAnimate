/*
 * State class
 * State is a bit-wise flag variable
 */
#pragma once
#include "def.h"

namespace SA
{
  using StateBit = unsigned int;
  constexpr StateBit SA_MODEL_NEEDS_UPDATE = 0x00000001;
  constexpr StateBit SA_LIGHT_NEEDS_UPDATE = 0x00000002;

  class SA_API State
  {

  public:
    State() {}
    template <typename... StateBit>
    State(StateBit... bits) { _flag = (bits | ...); }

    template <typename... StateBit>
    void dirty(StateBit... bits);
    template <typename... StateBit>
    void clean(StateBit... bits);

    template <typename... StateBit>
    unsigned int mask(StateBit... bits);

  private:
    unsigned int _flag = 0x00000000;
  };

  template <typename... StateBit>
  void State::dirty(StateBit... bits)
  {
    _flag |= (bits | ...);
  }
  template <typename... StateBit>
  void State::clean(StateBit... bits)
  {
    _flag &= ~(bits | ...);
  }

  template <typename... StateBit>
  unsigned int State::mask(StateBit... bits)
  {
    return _flag & (bits | ...);
  }
} // namespace SA
