#include "pch.h"
#include "Attribute.h"

using namespace SA;

Attribute::Attribute()
{
  this->arr = std::vector<float>();
  this->sz = 0;
  this->cnt = 0;
  this->isNorm = false;
  this->name = "";
  this->type = NR_ATTR_TYPE;
  
}

Attribute::Attribute(const ATTR_TYPE _t, const std::vector<float> &_arr, size_t _sz, bool _isNorm = false)
{
  this->arr = _arr;
  this->sz = _sz;
  this->cnt = _arr.size() / _sz;
  this->isNorm = _isNorm;
  this->name = "";
  this->type = _t;
}

const float *Attribute::getData() const
{
  return arr.data();
}

const std::vector<float> &Attribute::getArray() const
{
  return arr;
}