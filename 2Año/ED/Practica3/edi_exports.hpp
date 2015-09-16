#ifndef edi_exports_hpp
#define edi_exports_hpp

// Generic helper definitions for shared library support
// See:http://gcc.gnu.org/wiki/Visibility for details.
//
#if defined _WIN32 || defined __CYGWIN__
  #define EDI_HELPER_DLL_IMPORT __declspec(dllimport)
  #define EDI_HELPER_DLL_EXPORT __declspec(dllexport)
  #define EDI_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define EDI_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define EDI_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define EDI_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define EDI_HELPER_DLL_IMPORT
    #define EDI_HELPER_DLL_EXPORT
    #define EDI_HELPER_DLL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define EDI_API and EDI_LOCAL.
// EDI_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// EDI_LOCAL is used for non-api symbols.


#ifdef EDI_STATIC // defined if EDI is compiled as a STATIC LIB

  #define EDI_API
  #define EDI_LOCAL
  
#else // EDI_STATIC is not defined: this means EDI is a dynamic loaded lib.

  #ifdef EDI_EXPORTS // defined if we are building the EDI DLL (instead of using it)
    #define EDI_API EDI_HELPER_DLL_EXPORT
  #else
    #define EDI_API EDI_HELPER_DLL_IMPORT
  #endif // EDI_DLL_EXPORTS  
  #define EDI_LOCAL EDI_HELPER_DLL_LOCAL

#endif // EDI_STATIC

/** @defgroup edi Estructuras de Datos */
/** @brief Espacio de nombres para Estructras de Datos de la Información 
 * @ingroup edi
 */
namespace edi {}

#endif //edi_exports_hpp