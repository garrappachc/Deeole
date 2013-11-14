/**
 * Type traits for Deeole.
 */
namespace Dee {

namespace Types {
  template <typename T, typename...>
    struct all_of_type;
    
  template <typename T>
    struct all_of_type<T> :
      std::true_type
    {};
    
  template <typename T, typename First, typename ...Rest>
    struct all_of_type<T, First, Rest...> :
      std::integral_constant<bool,
        std::is_convertible<T, First>::value && all_of_type<T, Rest...>::value>
    {};
}

}
