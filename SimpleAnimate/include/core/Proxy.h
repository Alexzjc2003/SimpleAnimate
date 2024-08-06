#include <functional>
#include <def.h>

namespace SA
{
  template <typename Tval>
  class SA_API Proxy
  {
  public:
    Proxy();
    Proxy(Tval _val);

    Proxy<Tval> &set(const Tval val);
    Tval get();

    Proxy<Tval> &copy(const Tval val);
    Tval clone() const;

    std::function<Tval()> onGet;
    std::function<void(const Tval val)> onSet;

    void operator=(const Tval val);
    operator Tval();
    Tval &operator->();

  protected:
    Tval _val;
  };

  template <typename Tval>
  Proxy<Tval>::Proxy() : _val() {}
  template <typename Tval>
  Proxy<Tval>::Proxy(Tval _val) : _val(_val) {}

  template <typename Tval>
  Proxy<Tval> &Proxy<Tval>::set(const Tval val)
  {
    if (onSet)
      onSet(val);
    else
      _val = val;
    return *this;
  }
  template <typename Tval>
  Tval Proxy<Tval>::get()
  {
    if (onGet)
      return onGet();
    return _val;
  }

  template <typename Tval>
  Proxy<Tval> &Proxy<Tval>::copy(const Tval val)
  {
    _val = val;
    return *this;
  }

  template <typename Tval>
  Tval Proxy<Tval>::clone() const
  {
    return _val;
  }

  template <typename Tval>
  void
  Proxy<Tval>::operator=(const Tval val)
  {
    set(val);
  }

  template <typename Tval>
  Proxy<Tval>::operator Tval()
  {
    return get();
  }

  template <typename Tval>
  Tval &
  Proxy<Tval>::operator->()
  {
    return _val;
  }

} // namespace SA
