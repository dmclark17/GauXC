#pragma once

namespace GauXC {
namespace detail {

template <typename T, typename ParameterType>
class NamedType {

public:

  constexpr explicit NamedType() : value_() { }
  constexpr explicit NamedType(T const& value) : value_(value) {}
  constexpr explicit NamedType(T&& value) : value_(std::move(value)) {}

  constexpr NamedType( const NamedType& other ) : value_(other.get()) { }
  constexpr NamedType( NamedType&& other ) noexcept : 
    value_(std::move(other.get())) { };

  constexpr NamedType& operator=( const NamedType& other ) {
    value_ = other.get();
    return *this;
  }
  constexpr NamedType& operator=( NamedType&& other ) {
    value_ = std::move(other.get());
    return *this;
  }

  constexpr T& get() { return value_; }
  constexpr T const& get() const {return value_; }

private:

  T value_;

};

template <typename T, typename ParameterType>
inline bool operator==( 
  const NamedType<T,ParameterType>& n1,
  const NamedType<T,ParameterType>& n2
) { return n1.get() == n2.get(); }

template <typename T, typename ParameterType>
inline bool operator==( 
  const NamedType<T,ParameterType>& n1,
  const           T               & n2
) { return n1.get() == n2; }

template <typename T, typename ParameterType>
inline bool operator==( 
  const           T               & n1,
  const NamedType<T,ParameterType>& n2
) { return n2 == n1; }

template <typename T, typename ParameterType>
inline bool operator!=( 
  const NamedType<T,ParameterType>& n1,
  const NamedType<T,ParameterType>& n2
) { return not(n1 == n2); }

template <typename T, typename ParameterType>
inline bool operator!=( 
  const NamedType<T,ParameterType>& n1,
  const           T               & n2
) { return not( n1 == n2 ); }

template <typename T, typename ParameterType>
inline bool operator!=( 
  const           T               & n1,
  const NamedType<T,ParameterType>& n2
) { return not( n1 == n2 ); }

template <typename T, typename ParameterType>
inline std::ostream& operator<<( std::ostream&                     out, 
                                 const NamedType<T,ParameterType>& n ) {

  out << n.get();
  return out;
}

}
}

namespace std {

template <typename T, typename ParameterType>
struct std::hash< GauXC::detail::NamedType<T,ParameterType> > {

  std::size_t 
    operator()( const GauXC::detail::NamedType<T,ParameterType>& key ) const {
    return hash<T>()(key.get());
  }

};

}