# 0 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/samplerOGL.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/samplerOGL.cpp"
# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/samplerOGL.h" 1
       
# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/sampler.h" 1
       

namespace Neon::RHI
{
class Sampler
{
public:
    virtual ~Sampler() = default;
};
}
# 3 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/samplerOGL.h" 2
# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/descriptions/samplerDescription.h" 1
       

# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/enums/mipmapFilter.h" 1
       

namespace Neon::RHI
{
    enum class MipmapFilter
    {
        None,
        Nearest,
        Linear
    };
}
# 4 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/descriptions/samplerDescription.h" 2
# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/enums/textureFilter.h" 1
       

namespace Neon::RHI
{
    enum class TextureFilter
    {
        Nearest,
        Linear
    };
}
# 5 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/descriptions/samplerDescription.h" 2
# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/enums/textureWrap.h" 1
       

namespace Neon::RHI
{
    enum class TextureWrap
    {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder
    };
}
# 6 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/descriptions/samplerDescription.h" 2

namespace Neon::RHI
{
struct SamplerDescription
{
    TextureFilter minFilter = TextureFilter::Linear;
    TextureFilter magFilter = TextureFilter::Linear;
    MipmapFilter mipmapFilter = MipmapFilter::Linear;

    struct WrapMode
    {
        TextureWrap x = TextureWrap::Repeat;
        TextureWrap y = TextureWrap::Repeat;
        TextureWrap z = TextureWrap::Repeat;
    };

    WrapMode wrapMode = WrapMode{};

    float lodBias = 0.0f;
};
}
# 4 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/samplerOGL.h" 2

# 1 "C:/msys64/mingw64/include/c++/15.2.0/cstdint" 1 3
# 40 "C:/msys64/mingw64/include/c++/15.2.0/cstdint" 3
# 1 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 1 3
# 37 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"

#pragma GCC diagnostic ignored "-Wc++11-extensions"
#pragma GCC diagnostic ignored "-Wc++23-extensions"
# 336 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 3
namespace std
{
  typedef long long unsigned int size_t;
  typedef long long int ptrdiff_t;


  typedef decltype(nullptr) nullptr_t;


#pragma GCC visibility push(default)


  extern "C++" __attribute__ ((__noreturn__, __always_inline__))
  inline void __terminate() noexcept
  {
    void terminate() noexcept __attribute__ ((__noreturn__,__cold__));
    terminate();
  }
#pragma GCC visibility pop
}
# 369 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 3
namespace std
{
  inline namespace __cxx11 __attribute__((__abi_tag__ ("cxx11"))) { }
}
namespace __gnu_cxx
{
  inline namespace __cxx11 __attribute__((__abi_tag__ ("cxx11"))) { }
}
# 573 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 3
namespace std
{
#pragma GCC visibility push(default)




  __attribute__((__always_inline__))
  constexpr inline bool
  __is_constant_evaluated() noexcept
  {


    if consteval { return true; } else { return false; }






  }
#pragma GCC visibility pop
}
# 617 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 3
namespace std
{
#pragma GCC visibility push(default)

  extern "C++" __attribute__ ((__noreturn__)) __attribute__((__cold__))
  void
  __glibcxx_assert_fail
    (const char* __file, int __line, const char* __function,
     const char* __condition)
  noexcept;
#pragma GCC visibility pop
}
# 648 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 3
namespace std
{
  __attribute__((__always_inline__,__visibility__("default")))
  inline void
  __glibcxx_assert_fail()
  { }
}
# 727 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 3
# 1 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/os_defines.h" 1 3
# 728 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 2 3


# 1 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/cpu_defines.h" 1 3
# 731 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 2 3
# 887 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 3
namespace __gnu_cxx
{
  typedef __decltype(0.0bf16) __bfloat16_t;
}
# 949 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 3
# 1 "C:/msys64/mingw64/include/c++/15.2.0/pstl/pstl_config.h" 1 3
# 950 "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32/bits/c++config.h" 2 3



#pragma GCC diagnostic pop
# 41 "C:/msys64/mingw64/include/c++/15.2.0/cstdint" 2 3






# 1 "C:/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/stdint.h" 1 3 4
# 9 "C:/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/stdint.h" 3 4
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
# 1 "C:/msys64/mingw64/include/stdint.h" 1 3 4
# 28 "C:/msys64/mingw64/include/stdint.h" 3 4
# 1 "C:/msys64/mingw64/include/crtdefs.h" 1 3 4
# 10 "C:/msys64/mingw64/include/crtdefs.h" 3 4
# 1 "C:/msys64/mingw64/include/corecrt.h" 1 3 4
# 10 "C:/msys64/mingw64/include/corecrt.h" 3 4
# 1 "C:/msys64/mingw64/include/_mingw.h" 1 3 4
# 10 "C:/msys64/mingw64/include/_mingw.h" 3 4
# 1 "C:/msys64/mingw64/include/_mingw_mac.h" 1 3 4
# 108 "C:/msys64/mingw64/include/_mingw_mac.h" 3 4
             
# 117 "C:/msys64/mingw64/include/_mingw_mac.h" 3 4
             
# 326 "C:/msys64/mingw64/include/_mingw_mac.h" 3 4
       
# 405 "C:/msys64/mingw64/include/_mingw_mac.h" 3 4
       
# 11 "C:/msys64/mingw64/include/_mingw.h" 2 3 4
# 1 "C:/msys64/mingw64/include/_mingw_secapi.h" 1 3 4
# 44 "C:/msys64/mingw64/include/_mingw_secapi.h" 3 4
extern "C++" {
template <bool __test, typename __dsttype>
  struct __if_array;
template <typename __dsttype>
  struct __if_array <true, __dsttype> {
    typedef __dsttype __type;
};
}
# 12 "C:/msys64/mingw64/include/_mingw.h" 2 3 4
# 306 "C:/msys64/mingw64/include/_mingw.h" 3 4
# 1 "C:/msys64/mingw64/include/vadefs.h" 1 3 4
# 9 "C:/msys64/mingw64/include/vadefs.h" 3 4
# 1 "C:/msys64/mingw64/include/_mingw.h" 1 3 4
# 685 "C:/msys64/mingw64/include/_mingw.h" 3 4
# 1 "C:/msys64/mingw64/include/sdks/_mingw_ddk.h" 1 3 4
# 686 "C:/msys64/mingw64/include/_mingw.h" 2 3 4
# 10 "C:/msys64/mingw64/include/vadefs.h" 2 3 4




#pragma pack(push,_CRT_PACKING)



extern "C" {





  typedef __builtin_va_list __gnuc_va_list;






  typedef __gnuc_va_list va_list;
# 99 "C:/msys64/mingw64/include/vadefs.h" 3 4
}



#pragma pack(pop)
# 307 "C:/msys64/mingw64/include/_mingw.h" 2 3 4
# 592 "C:/msys64/mingw64/include/_mingw.h" 3 4
extern "C" {
# 604 "C:/msys64/mingw64/include/_mingw.h" 3 4
void __attribute__((__cdecl__)) __debugbreak(void);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __debugbreak(void)
{



  __asm__ __volatile__("int {$}3":);





}
# 625 "C:/msys64/mingw64/include/_mingw.h" 3 4
void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) __fastfail(unsigned int code);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) __fastfail(unsigned int code)
{




  __asm__ __volatile__("int {$}0x29"::"c"(code));






  __builtin_unreachable();
}
# 665 "C:/msys64/mingw64/include/_mingw.h" 3 4
const char *__mingw_get_crt_info (void);


}
# 11 "C:/msys64/mingw64/include/corecrt.h" 2 3 4




#pragma pack(push,_CRT_PACKING)
# 35 "C:/msys64/mingw64/include/corecrt.h" 3 4
__extension__ typedef unsigned long long size_t;
# 45 "C:/msys64/mingw64/include/corecrt.h" 3 4
__extension__ typedef long long ssize_t;






typedef size_t rsize_t;
# 62 "C:/msys64/mingw64/include/corecrt.h" 3 4
__extension__ typedef long long intptr_t;
# 75 "C:/msys64/mingw64/include/corecrt.h" 3 4
__extension__ typedef unsigned long long uintptr_t;
# 88 "C:/msys64/mingw64/include/corecrt.h" 3 4
__extension__ typedef long long ptrdiff_t;
# 106 "C:/msys64/mingw64/include/corecrt.h" 3 4
typedef unsigned short wint_t;
typedef unsigned short wctype_t;





typedef int errno_t;




typedef long __time32_t;




__extension__ typedef long long __time64_t;
# 138 "C:/msys64/mingw64/include/corecrt.h" 3 4
typedef __time64_t time_t;
# 157 "C:/msys64/mingw64/include/corecrt.h" 3 4
__attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _invalid_parameter_noinfo(void);
__attribute__ ((__dllimport__)) __attribute__ ((__noreturn__)) void __attribute__((__cdecl__)) _invalid_parameter_noinfo_noreturn(void);
__attribute__ ((__dllimport__)) __attribute__ ((__noreturn__)) void __attribute__((__cdecl__)) _invoke_watson(const wchar_t *expression, const wchar_t *function_name, const wchar_t *file_name, unsigned int line_number, uintptr_t reserved);
# 437 "C:/msys64/mingw64/include/corecrt.h" 3 4
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct {
  pthreadlocinfo locinfo;
  pthreadmbcinfo mbcinfo;
} _locale_tstruct,*_locale_t;



typedef struct tagLC_ID {
  unsigned short wLanguage;
  unsigned short wCountry;
  unsigned short wCodePage;
} LC_ID,*LPLC_ID;




typedef struct threadlocaleinfostruct {





  int refcount;
  unsigned int lc_codepage;
  unsigned int lc_collate_cp;
  unsigned long lc_handle[6];
  LC_ID lc_id[6];
  struct {
    char *locale;
    wchar_t *wlocale;
    int *refcount;
    int *wrefcount;
  } lc_category[6];
  int lc_clike;
  int mb_cur_max;
  int *lconv_intl_refcount;
  int *lconv_num_refcount;
  int *lconv_mon_refcount;
  struct lconv *lconv;
  int *ctype1_refcount;
  unsigned short *ctype1;
  const unsigned short *pctype;
  const unsigned char *pclmap;
  const unsigned char *pcumap;
  struct __lc_time_data *lc_time_curr;

} threadlocinfo;
# 508 "C:/msys64/mingw64/include/corecrt.h" 3 4
#pragma pack(pop)
# 11 "C:/msys64/mingw64/include/crtdefs.h" 2 3 4
# 29 "C:/msys64/mingw64/include/stdint.h" 2 3 4



# 1 "C:/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/stddef.h" 1 3 4
# 1 "C:/msys64/mingw64/include/stddef.h" 1 3 4
# 13 "C:/msys64/mingw64/include/stddef.h" 3 4
extern "C" {




  __attribute__ ((__dllimport__)) extern int *__attribute__((__cdecl__)) _errno(void);

  errno_t __attribute__((__cdecl__)) _set_errno(int _Value);
  errno_t __attribute__((__cdecl__)) _get_errno(int *_Value);


  __attribute__ ((__dllimport__)) extern unsigned long __attribute__((__cdecl__)) __threadid(void);

  __attribute__ ((__dllimport__)) extern uintptr_t __attribute__((__cdecl__)) __threadhandle(void);


}
# 2 "C:/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/stddef.h" 2 3 4
# 441 "C:/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
# 452 "C:/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/stddef.h" 3 4
} max_align_t;






  typedef decltype(nullptr) nullptr_t;
# 33 "C:/msys64/mingw64/include/stdint.h" 2 3 4


typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned uint32_t;
__extension__ typedef long long int64_t;
__extension__ typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef short int_least16_t;
typedef unsigned short uint_least16_t;
typedef int int_least32_t;
typedef unsigned uint_least32_t;
__extension__ typedef long long int_least64_t;
__extension__ typedef unsigned long long uint_least64_t;





typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef short int_fast16_t;
typedef unsigned short uint_fast16_t;
typedef int int_fast32_t;
typedef unsigned int uint_fast32_t;
__extension__ typedef long long int_fast64_t;
__extension__ typedef unsigned long long uint_fast64_t;


__extension__ typedef long long intmax_t;
__extension__ typedef unsigned long long uintmax_t;
# 12 "C:/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/15.2.0/include/stdint.h" 2 3 4
#pragma GCC diagnostic pop
# 48 "C:/msys64/mingw64/include/c++/15.2.0/cstdint" 2 3


namespace std
{

  using ::int8_t;
  using ::int16_t;
  using ::int32_t;
  using ::int64_t;

  using ::int_fast8_t;
  using ::int_fast16_t;
  using ::int_fast32_t;
  using ::int_fast64_t;

  using ::int_least8_t;
  using ::int_least16_t;
  using ::int_least32_t;
  using ::int_least64_t;

  using ::intmax_t;
  using ::intptr_t;

  using ::uint8_t;
  using ::uint16_t;
  using ::uint32_t;
  using ::uint64_t;

  using ::uint_fast8_t;
  using ::uint_fast16_t;
  using ::uint_fast32_t;
  using ::uint_fast64_t;

  using ::uint_least8_t;
  using ::uint_least16_t;
  using ::uint_least32_t;
  using ::uint_least64_t;

  using ::uintmax_t;
  using ::uintptr_t;
# 144 "C:/msys64/mingw64/include/c++/15.2.0/cstdint" 3
}
# 6 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/samplerOGL.h" 2
# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/glad/glad.h" 1
# 59 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/glad/glad.h"

# 59 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/glad/glad.h"
extern "C" {
# 168 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/glad/glad.h"
typedef void (*GLADapiproc)(void);

typedef GLADapiproc (*GLADloadfunc)(const char *name);
typedef GLADapiproc (*GLADuserptrloadfunc)(void *userptr, const char *name);

typedef void (*GLADprecallback)(const char *name, GLADapiproc apiproc, int len_args, ...);
typedef void (*GLADpostcallback)(void *ret, const char *name, GLADapiproc apiproc, int len_args, ...);
# 1989 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/glad/glad.h"
# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/KHR/khrplatform.h" 1
# 150 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/KHR/khrplatform.h"
typedef int32_t khronos_int32_t;
typedef uint32_t khronos_uint32_t;
typedef int64_t khronos_int64_t;
typedef uint64_t khronos_uint64_t;
# 242 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/KHR/khrplatform.h"
typedef signed char khronos_int8_t;
typedef unsigned char khronos_uint8_t;
typedef signed short int khronos_int16_t;
typedef unsigned short int khronos_uint16_t;







typedef intptr_t khronos_intptr_t;
typedef uintptr_t khronos_uintptr_t;
# 264 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/KHR/khrplatform.h"
typedef signed long long int khronos_ssize_t;
typedef unsigned long long int khronos_usize_t;
# 275 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/KHR/khrplatform.h"
typedef float khronos_float_t;
# 288 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/KHR/khrplatform.h"
typedef khronos_uint64_t khronos_utime_nanoseconds_t;
typedef khronos_int64_t khronos_stime_nanoseconds_t;
# 305 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/KHR/khrplatform.h"
typedef enum {
    KHRONOS_FALSE = 0,
    KHRONOS_TRUE = 1,
    KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = 0x7FFFFFFF
} khronos_boolean_enum_t;
# 1990 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/dependencies/glad/include/glad/glad.h" 2
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef khronos_int8_t GLbyte;
typedef khronos_uint8_t GLubyte;
typedef khronos_int16_t GLshort;
typedef khronos_uint16_t GLushort;
typedef int GLint;
typedef unsigned int GLuint;
typedef khronos_int32_t GLclampx;
typedef int GLsizei;
typedef khronos_float_t GLfloat;
typedef khronos_float_t GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void *GLeglClientBufferEXT;
typedef void *GLeglImageOES;
typedef char GLchar;
typedef char GLcharARB;



typedef unsigned int GLhandleARB;

typedef khronos_uint16_t GLhalf;
typedef khronos_uint16_t GLhalfARB;
typedef khronos_int32_t GLfixed;



typedef khronos_intptr_t GLintptr;




typedef khronos_intptr_t GLintptrARB;




typedef khronos_ssize_t GLsizeiptr;




typedef khronos_ssize_t GLsizeiptrARB;

typedef khronos_int64_t GLint64;
typedef khronos_int64_t GLint64EXT;
typedef khronos_uint64_t GLuint64;
typedef khronos_uint64_t GLuint64EXT;
typedef struct __GLsync *GLsync;
struct _cl_context;
struct _cl_event;
typedef void (__attribute__((__stdcall__)) *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (__attribute__((__stdcall__)) *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (__attribute__((__stdcall__)) *GLDEBUGPROCKHR)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (__attribute__((__stdcall__)) *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
typedef unsigned short GLhalfNV;
typedef GLintptr GLvdpauSurfaceNV;
typedef void (__attribute__((__stdcall__)) *GLVULKANPROCNV)(void);



extern int GLAD_GL_VERSION_1_0;

extern int GLAD_GL_VERSION_1_1;

extern int GLAD_GL_VERSION_1_2;

extern int GLAD_GL_VERSION_1_3;

extern int GLAD_GL_VERSION_1_4;

extern int GLAD_GL_VERSION_1_5;

extern int GLAD_GL_VERSION_2_0;

extern int GLAD_GL_VERSION_2_1;

extern int GLAD_GL_VERSION_3_0;

extern int GLAD_GL_VERSION_3_1;

extern int GLAD_GL_VERSION_3_2;

extern int GLAD_GL_VERSION_3_3;

extern int GLAD_GL_VERSION_4_0;

extern int GLAD_GL_VERSION_4_1;

extern int GLAD_GL_VERSION_4_2;

extern int GLAD_GL_VERSION_4_3;

extern int GLAD_GL_VERSION_4_4;

extern int GLAD_GL_VERSION_4_5;

extern int GLAD_GL_VERSION_4_6;

extern int GLAD_GL_ARB_bindless_texture;

extern int GLAD_GL_ARB_buffer_storage;

extern int GLAD_GL_ARB_compute_shader;

extern int GLAD_GL_ARB_direct_state_access;

extern int GLAD_GL_ARB_multi_draw_indirect;

extern int GLAD_GL_ARB_shader_storage_buffer_object;

extern int GLAD_GL_KHR_debug;


typedef void (__attribute__((__stdcall__)) *PFNGLACCUMPROC)(GLenum op, GLfloat value);
typedef void (__attribute__((__stdcall__)) *PFNGLACTIVESHADERPROGRAMPROC)(GLuint pipeline, GLuint program);
typedef void (__attribute__((__stdcall__)) *PFNGLACTIVETEXTUREPROC)(GLenum texture);
typedef void (__attribute__((__stdcall__)) *PFNGLALPHAFUNCPROC)(GLenum func, GLfloat ref);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLARETEXTURESRESIDENTPROC)(GLsizei n, const GLuint * textures, GLboolean * residences);
typedef void (__attribute__((__stdcall__)) *PFNGLARRAYELEMENTPROC)(GLint i);
typedef void (__attribute__((__stdcall__)) *PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void (__attribute__((__stdcall__)) *PFNGLBEGINPROC)(GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLBEGINCONDITIONALRENDERPROC)(GLuint id, GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLBEGINQUERYPROC)(GLenum target, GLuint id);
typedef void (__attribute__((__stdcall__)) *PFNGLBEGINQUERYINDEXEDPROC)(GLenum target, GLuint index, GLuint id);
typedef void (__attribute__((__stdcall__)) *PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum primitiveMode);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDBUFFERRANGEPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDBUFFERSBASEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint * buffers);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDBUFFERSRANGEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDFRAGDATALOCATIONPROC)(GLuint program, GLuint color, const GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDIMAGETEXTUREPROC)(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDIMAGETEXTURESPROC)(GLuint first, GLsizei count, const GLuint * textures);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDRENDERBUFFERPROC)(GLenum target, GLuint renderbuffer);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDSAMPLERPROC)(GLuint unit, GLuint sampler);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDSAMPLERSPROC)(GLuint first, GLsizei count, const GLuint * samplers);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDTEXTUREUNITPROC)(GLuint unit, GLuint texture);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDTEXTURESPROC)(GLuint first, GLsizei count, const GLuint * textures);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDTRANSFORMFEEDBACKPROC)(GLenum target, GLuint id);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDVERTEXBUFFERPROC)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (__attribute__((__stdcall__)) *PFNGLBINDVERTEXBUFFERSPROC)(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides);
typedef void (__attribute__((__stdcall__)) *PFNGLBITMAPPROC)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap);
typedef void (__attribute__((__stdcall__)) *PFNGLBLENDCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLBLENDEQUATIONPROC)(GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
typedef void (__attribute__((__stdcall__)) *PFNGLBLENDEQUATIONSEPARATEIPROC)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (__attribute__((__stdcall__)) *PFNGLBLENDEQUATIONIPROC)(GLuint buf, GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
typedef void (__attribute__((__stdcall__)) *PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (__attribute__((__stdcall__)) *PFNGLBLENDFUNCSEPARATEIPROC)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (__attribute__((__stdcall__)) *PFNGLBLENDFUNCIPROC)(GLuint buf, GLenum src, GLenum dst);
typedef void (__attribute__((__stdcall__)) *PFNGLBLITFRAMEBUFFERPROC)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (__attribute__((__stdcall__)) *PFNGLBLITNAMEDFRAMEBUFFERPROC)(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (__attribute__((__stdcall__)) *PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
typedef void (__attribute__((__stdcall__)) *PFNGLBUFFERSTORAGEPROC)(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags);
typedef void (__attribute__((__stdcall__)) *PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCALLLISTPROC)(GLuint list);
typedef void (__attribute__((__stdcall__)) *PFNGLCALLLISTSPROC)(GLsizei n, GLenum type, const void * lists);
typedef GLenum (__attribute__((__stdcall__)) *PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum target);
typedef GLenum (__attribute__((__stdcall__)) *PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)(GLuint framebuffer, GLenum target);
typedef void (__attribute__((__stdcall__)) *PFNGLCLAMPCOLORPROC)(GLenum target, GLenum clamp);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARPROC)(GLbitfield mask);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARACCUMPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARBUFFERDATAPROC)(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARBUFFERSUBDATAPROC)(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARBUFFERFIPROC)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARBUFFERFVPROC)(GLenum buffer, GLint drawbuffer, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARBUFFERIVPROC)(GLenum buffer, GLint drawbuffer, const GLint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARBUFFERUIVPROC)(GLenum buffer, GLint drawbuffer, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARDEPTHPROC)(GLdouble depth);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARDEPTHFPROC)(GLfloat d);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARINDEXPROC)(GLfloat c);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARNAMEDBUFFERDATAPROC)(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARSTENCILPROC)(GLint s);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARTEXIMAGEPROC)(GLuint texture, GLint level, GLenum format, GLenum type, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCLEARTEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCLIENTACTIVETEXTUREPROC)(GLenum texture);
typedef GLenum (__attribute__((__stdcall__)) *PFNGLCLIENTWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (__attribute__((__stdcall__)) *PFNGLCLIPCONTROLPROC)(GLenum origin, GLenum depth);
typedef void (__attribute__((__stdcall__)) *PFNGLCLIPPLANEPROC)(GLenum plane, const GLdouble * equation);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3BVPROC)(const GLbyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3IPROC)(GLint red, GLint green, GLint blue);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3UBVPROC)(const GLubyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3UIVPROC)(const GLuint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR3USVPROC)(const GLushort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4BPROC)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4BVPROC)(const GLbyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4DPROC)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4FPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4IPROC)(GLint red, GLint green, GLint blue, GLint alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4SPROC)(GLshort red, GLshort green, GLshort blue, GLshort alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4UBPROC)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4UBVPROC)(const GLubyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4UIPROC)(GLuint red, GLuint green, GLuint blue, GLuint alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4UIVPROC)(const GLuint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4USPROC)(GLushort red, GLushort green, GLushort blue, GLushort alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLOR4USVPROC)(const GLushort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLORMASKIPROC)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLORMATERIALPROC)(GLenum face, GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLORP3UIPROC)(GLenum type, GLuint color);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLORP3UIVPROC)(GLenum type, const GLuint * color);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLORP4UIPROC)(GLenum type, GLuint color);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLORP4UIVPROC)(GLenum type, const GLuint * color);
typedef void (__attribute__((__stdcall__)) *PFNGLCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef void (__attribute__((__stdcall__)) *PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYBUFFERSUBDATAPROC)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYIMAGESUBDATAPROC)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYNAMEDBUFFERSUBDATAPROC)(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLCOPYTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLCREATEBUFFERSPROC)(GLsizei n, GLuint * buffers);
typedef void (__attribute__((__stdcall__)) *PFNGLCREATEFRAMEBUFFERSPROC)(GLsizei n, GLuint * framebuffers);
typedef GLuint (__attribute__((__stdcall__)) *PFNGLCREATEPROGRAMPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLCREATEPROGRAMPIPELINESPROC)(GLsizei n, GLuint * pipelines);
typedef void (__attribute__((__stdcall__)) *PFNGLCREATEQUERIESPROC)(GLenum target, GLsizei n, GLuint * ids);
typedef void (__attribute__((__stdcall__)) *PFNGLCREATERENDERBUFFERSPROC)(GLsizei n, GLuint * renderbuffers);
typedef void (__attribute__((__stdcall__)) *PFNGLCREATESAMPLERSPROC)(GLsizei n, GLuint * samplers);
typedef GLuint (__attribute__((__stdcall__)) *PFNGLCREATESHADERPROC)(GLenum type);
typedef GLuint (__attribute__((__stdcall__)) *PFNGLCREATESHADERPROGRAMVPROC)(GLenum type, GLsizei count, const GLchar *const* strings);
typedef void (__attribute__((__stdcall__)) *PFNGLCREATETEXTURESPROC)(GLenum target, GLsizei n, GLuint * textures);
typedef void (__attribute__((__stdcall__)) *PFNGLCREATETRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint * ids);
typedef void (__attribute__((__stdcall__)) *PFNGLCREATEVERTEXARRAYSPROC)(GLsizei n, GLuint * arrays);
typedef void (__attribute__((__stdcall__)) *PFNGLCULLFACEPROC)(GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC callback, const void * userParam);
typedef void (__attribute__((__stdcall__)) *PFNGLDEBUGMESSAGECONTROLPROC)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled);
typedef void (__attribute__((__stdcall__)) *PFNGLDEBUGMESSAGEINSERTPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint * buffers);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei n, const GLuint * framebuffers);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETELISTSPROC)(GLuint list, GLsizei range);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETEPROGRAMPROC)(GLuint program);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETEPROGRAMPIPELINESPROC)(GLsizei n, const GLuint * pipelines);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETEQUERIESPROC)(GLsizei n, const GLuint * ids);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETERENDERBUFFERSPROC)(GLsizei n, const GLuint * renderbuffers);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETESAMPLERSPROC)(GLsizei count, const GLuint * samplers);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETESHADERPROC)(GLuint shader);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETESYNCPROC)(GLsync sync);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint * textures);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETETRANSFORMFEEDBACKSPROC)(GLsizei n, const GLuint * ids);
typedef void (__attribute__((__stdcall__)) *PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint * arrays);
typedef void (__attribute__((__stdcall__)) *PFNGLDEPTHFUNCPROC)(GLenum func);
typedef void (__attribute__((__stdcall__)) *PFNGLDEPTHMASKPROC)(GLboolean flag);
typedef void (__attribute__((__stdcall__)) *PFNGLDEPTHRANGEPROC)(GLdouble n, GLdouble f);
typedef void (__attribute__((__stdcall__)) *PFNGLDEPTHRANGEARRAYVPROC)(GLuint first, GLsizei count, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLDEPTHRANGEINDEXEDPROC)(GLuint index, GLdouble n, GLdouble f);
typedef void (__attribute__((__stdcall__)) *PFNGLDEPTHRANGEFPROC)(GLfloat n, GLfloat f);
typedef void (__attribute__((__stdcall__)) *PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
typedef void (__attribute__((__stdcall__)) *PFNGLDISABLEPROC)(GLenum cap);
typedef void (__attribute__((__stdcall__)) *PFNGLDISABLECLIENTSTATEPROC)(GLenum array);
typedef void (__attribute__((__stdcall__)) *PFNGLDISABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
typedef void (__attribute__((__stdcall__)) *PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (__attribute__((__stdcall__)) *PFNGLDISABLEIPROC)(GLenum target, GLuint index);
typedef void (__attribute__((__stdcall__)) *PFNGLDISPATCHCOMPUTEPROC)(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
typedef void (__attribute__((__stdcall__)) *PFNGLDISPATCHCOMPUTEINDIRECTPROC)(GLintptr indirect);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWARRAYSINDIRECTPROC)(GLenum mode, const void * indirect);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWBUFFERPROC)(GLenum buf);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWBUFFERSPROC)(GLsizei n, const GLenum * bufs);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void * indirect);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWPIXELSPROC)(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWRANGEELEMENTSPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWTRANSFORMFEEDBACKPROC)(GLenum mode, GLuint id);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)(GLenum mode, GLuint id, GLsizei instancecount);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum mode, GLuint id, GLuint stream);
typedef void (__attribute__((__stdcall__)) *PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
typedef void (__attribute__((__stdcall__)) *PFNGLEDGEFLAGPROC)(GLboolean flag);
typedef void (__attribute__((__stdcall__)) *PFNGLEDGEFLAGPOINTERPROC)(GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLEDGEFLAGVPROC)(const GLboolean * flag);
typedef void (__attribute__((__stdcall__)) *PFNGLENABLEPROC)(GLenum cap);
typedef void (__attribute__((__stdcall__)) *PFNGLENABLECLIENTSTATEPROC)(GLenum array);
typedef void (__attribute__((__stdcall__)) *PFNGLENABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
typedef void (__attribute__((__stdcall__)) *PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (__attribute__((__stdcall__)) *PFNGLENABLEIPROC)(GLenum target, GLuint index);
typedef void (__attribute__((__stdcall__)) *PFNGLENDPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLENDCONDITIONALRENDERPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLENDLISTPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLENDQUERYPROC)(GLenum target);
typedef void (__attribute__((__stdcall__)) *PFNGLENDQUERYINDEXEDPROC)(GLenum target, GLuint index);
typedef void (__attribute__((__stdcall__)) *PFNGLENDTRANSFORMFEEDBACKPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALCOORD1DPROC)(GLdouble u);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALCOORD1DVPROC)(const GLdouble * u);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALCOORD1FPROC)(GLfloat u);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALCOORD1FVPROC)(const GLfloat * u);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALCOORD2DPROC)(GLdouble u, GLdouble v);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALCOORD2DVPROC)(const GLdouble * u);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALCOORD2FPROC)(GLfloat u, GLfloat v);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALCOORD2FVPROC)(const GLfloat * u);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALMESH1PROC)(GLenum mode, GLint i1, GLint i2);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALMESH2PROC)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALPOINT1PROC)(GLint i);
typedef void (__attribute__((__stdcall__)) *PFNGLEVALPOINT2PROC)(GLint i, GLint j);
typedef void (__attribute__((__stdcall__)) *PFNGLFEEDBACKBUFFERPROC)(GLsizei size, GLenum type, GLfloat * buffer);
typedef GLsync (__attribute__((__stdcall__)) *PFNGLFENCESYNCPROC)(GLenum condition, GLbitfield flags);
typedef void (__attribute__((__stdcall__)) *PFNGLFINISHPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLFLUSHPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (__attribute__((__stdcall__)) *PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (__attribute__((__stdcall__)) *PFNGLFOGCOORDPOINTERPROC)(GLenum type, GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLFOGCOORDDPROC)(GLdouble coord);
typedef void (__attribute__((__stdcall__)) *PFNGLFOGCOORDDVPROC)(const GLdouble * coord);
typedef void (__attribute__((__stdcall__)) *PFNGLFOGCOORDFPROC)(GLfloat coord);
typedef void (__attribute__((__stdcall__)) *PFNGLFOGCOORDFVPROC)(const GLfloat * coord);
typedef void (__attribute__((__stdcall__)) *PFNGLFOGFPROC)(GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLFOGFVPROC)(GLenum pname, const GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLFOGIPROC)(GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLFOGIVPROC)(GLenum pname, const GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLFRAMEBUFFERPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (__attribute__((__stdcall__)) *PFNGLFRAMEBUFFERTEXTUREPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (__attribute__((__stdcall__)) *PFNGLFRAMEBUFFERTEXTURE1DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (__attribute__((__stdcall__)) *PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (__attribute__((__stdcall__)) *PFNGLFRAMEBUFFERTEXTURE3DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (__attribute__((__stdcall__)) *PFNGLFRAMEBUFFERTEXTURELAYERPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (__attribute__((__stdcall__)) *PFNGLFRONTFACEPROC)(GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLFRUSTUMPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (__attribute__((__stdcall__)) *PFNGLGENBUFFERSPROC)(GLsizei n, GLuint * buffers);
typedef void (__attribute__((__stdcall__)) *PFNGLGENFRAMEBUFFERSPROC)(GLsizei n, GLuint * framebuffers);
typedef GLuint (__attribute__((__stdcall__)) *PFNGLGENLISTSPROC)(GLsizei range);
typedef void (__attribute__((__stdcall__)) *PFNGLGENPROGRAMPIPELINESPROC)(GLsizei n, GLuint * pipelines);
typedef void (__attribute__((__stdcall__)) *PFNGLGENQUERIESPROC)(GLsizei n, GLuint * ids);
typedef void (__attribute__((__stdcall__)) *PFNGLGENRENDERBUFFERSPROC)(GLsizei n, GLuint * renderbuffers);
typedef void (__attribute__((__stdcall__)) *PFNGLGENSAMPLERSPROC)(GLsizei count, GLuint * samplers);
typedef void (__attribute__((__stdcall__)) *PFNGLGENTEXTURESPROC)(GLsizei n, GLuint * textures);
typedef void (__attribute__((__stdcall__)) *PFNGLGENTRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint * ids);
typedef void (__attribute__((__stdcall__)) *PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint * arrays);
typedef void (__attribute__((__stdcall__)) *PFNGLGENERATEMIPMAPPROC)(GLenum target);
typedef void (__attribute__((__stdcall__)) *PFNGLGENERATETEXTUREMIPMAPPROC)(GLuint texture);
typedef void (__attribute__((__stdcall__)) *PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETACTIVEATTRIBPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLGETACTIVESUBROUTINENAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values);
typedef void (__attribute__((__stdcall__)) *PFNGLGETACTIVEUNIFORMPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
typedef void (__attribute__((__stdcall__)) *PFNGLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETACTIVEUNIFORMNAMEPROC)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName);
typedef void (__attribute__((__stdcall__)) *PFNGLGETACTIVEUNIFORMSIVPROC)(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETATTACHEDSHADERSPROC)(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
typedef GLint (__attribute__((__stdcall__)) *PFNGLGETATTRIBLOCATIONPROC)(GLuint program, const GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLGETBOOLEANI_VPROC)(GLenum target, GLuint index, GLboolean * data);
typedef void (__attribute__((__stdcall__)) *PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean * data);
typedef void (__attribute__((__stdcall__)) *PFNGLGETBUFFERPARAMETERI64VPROC)(GLenum target, GLenum pname, GLint64 * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETBUFFERPOINTERVPROC)(GLenum target, GLenum pname, void ** params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLGETCLIPPLANEPROC)(GLenum plane, GLdouble * equation);
typedef void (__attribute__((__stdcall__)) *PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint level, void * img);
typedef void (__attribute__((__stdcall__)) *PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)(GLuint texture, GLint level, GLsizei bufSize, void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels);
typedef GLuint (__attribute__((__stdcall__)) *PFNGLGETDEBUGMESSAGELOGPROC)(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog);
typedef void (__attribute__((__stdcall__)) *PFNGLGETDOUBLEI_VPROC)(GLenum target, GLuint index, GLdouble * data);
typedef void (__attribute__((__stdcall__)) *PFNGLGETDOUBLEVPROC)(GLenum pname, GLdouble * data);
typedef GLenum (__attribute__((__stdcall__)) *PFNGLGETERRORPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLGETFLOATI_VPROC)(GLenum target, GLuint index, GLfloat * data);
typedef void (__attribute__((__stdcall__)) *PFNGLGETFLOATVPROC)(GLenum pname, GLfloat * data);
typedef GLint (__attribute__((__stdcall__)) *PFNGLGETFRAGDATAINDEXPROC)(GLuint program, const GLchar * name);
typedef GLint (__attribute__((__stdcall__)) *PFNGLGETFRAGDATALOCATIONPROC)(GLuint program, const GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum target, GLenum attachment, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETFRAMEBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef GLenum (__attribute__((__stdcall__)) *PFNGLGETGRAPHICSRESETSTATUSPROC)(void);
typedef GLuint64 (__attribute__((__stdcall__)) *PFNGLGETIMAGEHANDLEARBPROC)(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
typedef void (__attribute__((__stdcall__)) *PFNGLGETINTEGER64I_VPROC)(GLenum target, GLuint index, GLint64 * data);
typedef void (__attribute__((__stdcall__)) *PFNGLGETINTEGER64VPROC)(GLenum pname, GLint64 * data);
typedef void (__attribute__((__stdcall__)) *PFNGLGETINTEGERI_VPROC)(GLenum target, GLuint index, GLint * data);
typedef void (__attribute__((__stdcall__)) *PFNGLGETINTEGERVPROC)(GLenum pname, GLint * data);
typedef void (__attribute__((__stdcall__)) *PFNGLGETINTERNALFORMATI64VPROC)(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETINTERNALFORMATIVPROC)(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETLIGHTFVPROC)(GLenum light, GLenum pname, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETLIGHTIVPROC)(GLenum light, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETMAPDVPROC)(GLenum target, GLenum query, GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLGETMAPFVPROC)(GLenum target, GLenum query, GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLGETMAPIVPROC)(GLenum target, GLenum query, GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLGETMATERIALFVPROC)(GLenum face, GLenum pname, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETMATERIALIVPROC)(GLenum face, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETMULTISAMPLEFVPROC)(GLenum pname, GLuint index, GLfloat * val);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)(GLuint buffer, GLenum pname, GLint64 * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNAMEDBUFFERPARAMETERIVPROC)(GLuint buffer, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNAMEDBUFFERPOINTERVPROC)(GLuint buffer, GLenum pname, void ** params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)(GLuint framebuffer, GLenum pname, GLint * param);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)(GLuint renderbuffer, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label);
typedef void (__attribute__((__stdcall__)) *PFNGLGETOBJECTPTRLABELPROC)(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPIXELMAPFVPROC)(GLenum map, GLfloat * values);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPIXELMAPUIVPROC)(GLenum map, GLuint * values);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPIXELMAPUSVPROC)(GLenum map, GLushort * values);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPOINTERVPROC)(GLenum pname, void ** params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPOLYGONSTIPPLEPROC)(GLubyte * mask);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPROGRAMBINARYPROC)(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void * binary);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPROGRAMINTERFACEIVPROC)(GLuint program, GLenum programInterface, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPROGRAMPIPELINEINFOLOGPROC)(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPROGRAMPIPELINEIVPROC)(GLuint pipeline, GLenum pname, GLint * params);
typedef GLuint (__attribute__((__stdcall__)) *PFNGLGETPROGRAMRESOURCEINDEXPROC)(GLuint program, GLenum programInterface, const GLchar * name);
typedef GLint (__attribute__((__stdcall__)) *PFNGLGETPROGRAMRESOURCELOCATIONPROC)(GLuint program, GLenum programInterface, const GLchar * name);
typedef GLint (__attribute__((__stdcall__)) *PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)(GLuint program, GLenum programInterface, const GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPROGRAMRESOURCENAMEPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPROGRAMRESOURCEIVPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei count, GLsizei * length, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPROGRAMSTAGEIVPROC)(GLuint program, GLenum shadertype, GLenum pname, GLint * values);
typedef void (__attribute__((__stdcall__)) *PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETQUERYBUFFEROBJECTI64VPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (__attribute__((__stdcall__)) *PFNGLGETQUERYBUFFEROBJECTIVPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (__attribute__((__stdcall__)) *PFNGLGETQUERYBUFFEROBJECTUI64VPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (__attribute__((__stdcall__)) *PFNGLGETQUERYBUFFEROBJECTUIVPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (__attribute__((__stdcall__)) *PFNGLGETQUERYINDEXEDIVPROC)(GLenum target, GLuint index, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETQUERYOBJECTI64VPROC)(GLuint id, GLenum pname, GLint64 * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETQUERYOBJECTIVPROC)(GLuint id, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETQUERYOBJECTUI64VPROC)(GLuint id, GLenum pname, GLuint64 * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETQUERYOBJECTUIVPROC)(GLuint id, GLenum pname, GLuint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETQUERYIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, GLuint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (__attribute__((__stdcall__)) *PFNGLGETSHADERPRECISIONFORMATPROC)(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
typedef void (__attribute__((__stdcall__)) *PFNGLGETSHADERSOURCEPROC)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
typedef void (__attribute__((__stdcall__)) *PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint * params);
typedef const GLubyte * (__attribute__((__stdcall__)) *PFNGLGETSTRINGPROC)(GLenum name);
typedef const GLubyte * (__attribute__((__stdcall__)) *PFNGLGETSTRINGIPROC)(GLenum name, GLuint index);
typedef GLuint (__attribute__((__stdcall__)) *PFNGLGETSUBROUTINEINDEXPROC)(GLuint program, GLenum shadertype, const GLchar * name);
typedef GLint (__attribute__((__stdcall__)) *PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)(GLuint program, GLenum shadertype, const GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLGETSYNCIVPROC)(GLsync sync, GLenum pname, GLsizei count, GLsizei * length, GLint * values);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXENVFVPROC)(GLenum target, GLenum pname, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXENVIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXGENDVPROC)(GLenum coord, GLenum pname, GLdouble * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXGENFVPROC)(GLenum coord, GLenum pname, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXGENIVPROC)(GLenum coord, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXLEVELPARAMETERFVPROC)(GLenum target, GLint level, GLenum pname, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXLEVELPARAMETERIVPROC)(GLenum target, GLint level, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, GLuint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef GLuint64 (__attribute__((__stdcall__)) *PFNGLGETTEXTUREHANDLEARBPROC)(GLuint texture);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXTUREIMAGEPROC)(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXTURELEVELPARAMETERFVPROC)(GLuint texture, GLint level, GLenum pname, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXTURELEVELPARAMETERIVPROC)(GLuint texture, GLint level, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXTUREPARAMETERIIVPROC)(GLuint texture, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXTUREPARAMETERIUIVPROC)(GLuint texture, GLenum pname, GLuint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXTUREPARAMETERFVPROC)(GLuint texture, GLenum pname, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXTUREPARAMETERIVPROC)(GLuint texture, GLenum pname, GLint * params);
typedef GLuint64 (__attribute__((__stdcall__)) *PFNGLGETTEXTURESAMPLERHANDLEARBPROC)(GLuint texture, GLuint sampler);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTEXTURESUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTRANSFORMFEEDBACKI64_VPROC)(GLuint xfb, GLenum pname, GLuint index, GLint64 * param);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTRANSFORMFEEDBACKI_VPROC)(GLuint xfb, GLenum pname, GLuint index, GLint * param);
typedef void (__attribute__((__stdcall__)) *PFNGLGETTRANSFORMFEEDBACKIVPROC)(GLuint xfb, GLenum pname, GLint * param);
typedef GLuint (__attribute__((__stdcall__)) *PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar * uniformBlockName);
typedef void (__attribute__((__stdcall__)) *PFNGLGETUNIFORMINDICESPROC)(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices);
typedef GLint (__attribute__((__stdcall__)) *PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar * name);
typedef void (__attribute__((__stdcall__)) *PFNGLGETUNIFORMSUBROUTINEUIVPROC)(GLenum shadertype, GLint location, GLuint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETUNIFORMDVPROC)(GLuint program, GLint location, GLdouble * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETUNIFORMFVPROC)(GLuint program, GLint location, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETUNIFORMIVPROC)(GLuint program, GLint location, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETUNIFORMUIVPROC)(GLuint program, GLint location, GLuint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETVERTEXARRAYINDEXED64IVPROC)(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param);
typedef void (__attribute__((__stdcall__)) *PFNGLGETVERTEXARRAYINDEXEDIVPROC)(GLuint vaobj, GLuint index, GLenum pname, GLint * param);
typedef void (__attribute__((__stdcall__)) *PFNGLGETVERTEXARRAYIVPROC)(GLuint vaobj, GLenum pname, GLint * param);
typedef void (__attribute__((__stdcall__)) *PFNGLGETVERTEXATTRIBIIVPROC)(GLuint index, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETVERTEXATTRIBIUIVPROC)(GLuint index, GLenum pname, GLuint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETVERTEXATTRIBLDVPROC)(GLuint index, GLenum pname, GLdouble * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETVERTEXATTRIBLUI64VARBPROC)(GLuint index, GLenum pname, GLuint64EXT * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint index, GLenum pname, void ** pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLGETVERTEXATTRIBDVPROC)(GLuint index, GLenum pname, GLdouble * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETVERTEXATTRIBFVPROC)(GLuint index, GLenum pname, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETVERTEXATTRIBIVPROC)(GLuint index, GLenum pname, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNCOLORTABLEPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * table);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint lod, GLsizei bufSize, void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNCONVOLUTIONFILTERPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * image);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNHISTOGRAMPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNMAPDVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNMAPFVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNMAPIVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNMINMAXPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNPIXELMAPFVPROC)(GLenum map, GLsizei bufSize, GLfloat * values);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNPIXELMAPUIVPROC)(GLenum map, GLsizei bufSize, GLuint * values);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNPIXELMAPUSVPROC)(GLenum map, GLsizei bufSize, GLushort * values);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNPOLYGONSTIPPLEPROC)(GLsizei bufSize, GLubyte * pattern);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNSEPARABLEFILTERPROC)(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void * row, GLsizei columnBufSize, void * column, void * span);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNUNIFORMDVPROC)(GLuint program, GLint location, GLsizei bufSize, GLdouble * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNUNIFORMFVPROC)(GLuint program, GLint location, GLsizei bufSize, GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNUNIFORMIVPROC)(GLuint program, GLint location, GLsizei bufSize, GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLGETNUNIFORMUIVPROC)(GLuint program, GLint location, GLsizei bufSize, GLuint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLHINTPROC)(GLenum target, GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXMASKPROC)(GLuint mask);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXPOINTERPROC)(GLenum type, GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXDPROC)(GLdouble c);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXDVPROC)(const GLdouble * c);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXFPROC)(GLfloat c);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXFVPROC)(const GLfloat * c);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXIPROC)(GLint c);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXIVPROC)(const GLint * c);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXSPROC)(GLshort c);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXSVPROC)(const GLshort * c);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXUBPROC)(GLubyte c);
typedef void (__attribute__((__stdcall__)) *PFNGLINDEXUBVPROC)(const GLubyte * c);
typedef void (__attribute__((__stdcall__)) *PFNGLINITNAMESPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLINTERLEAVEDARRAYSPROC)(GLenum format, GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLINVALIDATEBUFFERDATAPROC)(GLuint buffer);
typedef void (__attribute__((__stdcall__)) *PFNGLINVALIDATEBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (__attribute__((__stdcall__)) *PFNGLINVALIDATEFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum * attachments);
typedef void (__attribute__((__stdcall__)) *PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments);
typedef void (__attribute__((__stdcall__)) *PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLINVALIDATESUBFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLINVALIDATETEXIMAGEPROC)(GLuint texture, GLint level);
typedef void (__attribute__((__stdcall__)) *PFNGLINVALIDATETEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISBUFFERPROC)(GLuint buffer);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISENABLEDPROC)(GLenum cap);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISENABLEDIPROC)(GLenum target, GLuint index);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISFRAMEBUFFERPROC)(GLuint framebuffer);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISIMAGEHANDLERESIDENTARBPROC)(GLuint64 handle);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISLISTPROC)(GLuint list);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISPROGRAMPROC)(GLuint program);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISQUERYPROC)(GLuint id);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISRENDERBUFFERPROC)(GLuint renderbuffer);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISSAMPLERPROC)(GLuint sampler);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISSHADERPROC)(GLuint shader);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISSYNCPROC)(GLsync sync);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISTEXTUREPROC)(GLuint texture);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISTEXTUREHANDLERESIDENTARBPROC)(GLuint64 handle);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISTRANSFORMFEEDBACKPROC)(GLuint id);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLISVERTEXARRAYPROC)(GLuint array);
typedef void (__attribute__((__stdcall__)) *PFNGLLIGHTMODELFPROC)(GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLLIGHTMODELFVPROC)(GLenum pname, const GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLLIGHTMODELIPROC)(GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLLIGHTMODELIVPROC)(GLenum pname, const GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLLIGHTFPROC)(GLenum light, GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLLIGHTFVPROC)(GLenum light, GLenum pname, const GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLLIGHTIPROC)(GLenum light, GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLLIGHTIVPROC)(GLenum light, GLenum pname, const GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLLINESTIPPLEPROC)(GLint factor, GLushort pattern);
typedef void (__attribute__((__stdcall__)) *PFNGLLINEWIDTHPROC)(GLfloat width);
typedef void (__attribute__((__stdcall__)) *PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void (__attribute__((__stdcall__)) *PFNGLLISTBASEPROC)(GLuint base);
typedef void (__attribute__((__stdcall__)) *PFNGLLOADIDENTITYPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLLOADMATRIXDPROC)(const GLdouble * m);
typedef void (__attribute__((__stdcall__)) *PFNGLLOADMATRIXFPROC)(const GLfloat * m);
typedef void (__attribute__((__stdcall__)) *PFNGLLOADNAMEPROC)(GLuint name);
typedef void (__attribute__((__stdcall__)) *PFNGLLOADTRANSPOSEMATRIXDPROC)(const GLdouble * m);
typedef void (__attribute__((__stdcall__)) *PFNGLLOADTRANSPOSEMATRIXFPROC)(const GLfloat * m);
typedef void (__attribute__((__stdcall__)) *PFNGLLOGICOPPROC)(GLenum opcode);
typedef void (__attribute__((__stdcall__)) *PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC)(GLuint64 handle);
typedef void (__attribute__((__stdcall__)) *PFNGLMAKEIMAGEHANDLERESIDENTARBPROC)(GLuint64 handle, GLenum access);
typedef void (__attribute__((__stdcall__)) *PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC)(GLuint64 handle);
typedef void (__attribute__((__stdcall__)) *PFNGLMAKETEXTUREHANDLERESIDENTARBPROC)(GLuint64 handle);
typedef void (__attribute__((__stdcall__)) *PFNGLMAP1DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points);
typedef void (__attribute__((__stdcall__)) *PFNGLMAP1FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points);
typedef void (__attribute__((__stdcall__)) *PFNGLMAP2DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points);
typedef void (__attribute__((__stdcall__)) *PFNGLMAP2FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points);
typedef void * (__attribute__((__stdcall__)) *PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
typedef void * (__attribute__((__stdcall__)) *PFNGLMAPBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (__attribute__((__stdcall__)) *PFNGLMAPGRID1DPROC)(GLint un, GLdouble u1, GLdouble u2);
typedef void (__attribute__((__stdcall__)) *PFNGLMAPGRID1FPROC)(GLint un, GLfloat u1, GLfloat u2);
typedef void (__attribute__((__stdcall__)) *PFNGLMAPGRID2DPROC)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
typedef void (__attribute__((__stdcall__)) *PFNGLMAPGRID2FPROC)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
typedef void * (__attribute__((__stdcall__)) *PFNGLMAPNAMEDBUFFERPROC)(GLuint buffer, GLenum access);
typedef void * (__attribute__((__stdcall__)) *PFNGLMAPNAMEDBUFFERRANGEPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (__attribute__((__stdcall__)) *PFNGLMATERIALFPROC)(GLenum face, GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLMATERIALFVPROC)(GLenum face, GLenum pname, const GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLMATERIALIPROC)(GLenum face, GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLMATERIALIVPROC)(GLenum face, GLenum pname, const GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLMATRIXMODEPROC)(GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLMEMORYBARRIERPROC)(GLbitfield barriers);
typedef void (__attribute__((__stdcall__)) *PFNGLMEMORYBARRIERBYREGIONPROC)(GLbitfield barriers);
typedef void (__attribute__((__stdcall__)) *PFNGLMINSAMPLESHADINGPROC)(GLfloat value);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTMATRIXDPROC)(const GLdouble * m);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTMATRIXFPROC)(const GLfloat * m);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTTRANSPOSEMATRIXDPROC)(const GLdouble * m);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTTRANSPOSEMATRIXFPROC)(const GLfloat * m);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTIDRAWARRAYSPROC)(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTIDRAWARRAYSINDIRECTPROC)(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)(GLenum mode, const void * indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTIDRAWELEMENTSPROC)(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTIDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)(GLenum mode, GLenum type, const void * indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD1DPROC)(GLenum target, GLdouble s);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD1DVPROC)(GLenum target, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD1FPROC)(GLenum target, GLfloat s);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD1FVPROC)(GLenum target, const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD1IPROC)(GLenum target, GLint s);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD1IVPROC)(GLenum target, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD1SPROC)(GLenum target, GLshort s);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD1SVPROC)(GLenum target, const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD2DPROC)(GLenum target, GLdouble s, GLdouble t);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD2DVPROC)(GLenum target, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD2FPROC)(GLenum target, GLfloat s, GLfloat t);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD2FVPROC)(GLenum target, const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD2IPROC)(GLenum target, GLint s, GLint t);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD2IVPROC)(GLenum target, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD2SPROC)(GLenum target, GLshort s, GLshort t);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD2SVPROC)(GLenum target, const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD3DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD3DVPROC)(GLenum target, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD3FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD3FVPROC)(GLenum target, const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD3IPROC)(GLenum target, GLint s, GLint t, GLint r);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD3IVPROC)(GLenum target, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD3SPROC)(GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD3SVPROC)(GLenum target, const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD4DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD4DVPROC)(GLenum target, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD4FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD4FVPROC)(GLenum target, const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD4IPROC)(GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD4IVPROC)(GLenum target, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD4SPROC)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORD4SVPROC)(GLenum target, const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORDP1UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORDP1UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORDP2UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORDP2UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORDP3UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORDP3UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORDP4UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (__attribute__((__stdcall__)) *PFNGLMULTITEXCOORDP4UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDBUFFERDATAPROC)(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDBUFFERSTORAGEPROC)(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)(GLuint framebuffer, GLenum buf);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)(GLuint framebuffer, GLsizei n, const GLenum * bufs);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)(GLuint framebuffer, GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)(GLuint framebuffer, GLenum src);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDRENDERBUFFERSTORAGEPROC)(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLNEWLISTPROC)(GLuint list, GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMAL3BPROC)(GLbyte nx, GLbyte ny, GLbyte nz);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMAL3BVPROC)(const GLbyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMAL3DPROC)(GLdouble nx, GLdouble ny, GLdouble nz);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMAL3DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMAL3FPROC)(GLfloat nx, GLfloat ny, GLfloat nz);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMAL3FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMAL3IPROC)(GLint nx, GLint ny, GLint nz);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMAL3IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMAL3SPROC)(GLshort nx, GLshort ny, GLshort nz);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMAL3SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMALP3UIPROC)(GLenum type, GLuint coords);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMALP3UIVPROC)(GLenum type, const GLuint * coords);
typedef void (__attribute__((__stdcall__)) *PFNGLNORMALPOINTERPROC)(GLenum type, GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei length, const GLchar * label);
typedef void (__attribute__((__stdcall__)) *PFNGLOBJECTPTRLABELPROC)(const void * ptr, GLsizei length, const GLchar * label);
typedef void (__attribute__((__stdcall__)) *PFNGLORTHOPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (__attribute__((__stdcall__)) *PFNGLPASSTHROUGHPROC)(GLfloat token);
typedef void (__attribute__((__stdcall__)) *PFNGLPATCHPARAMETERFVPROC)(GLenum pname, const GLfloat * values);
typedef void (__attribute__((__stdcall__)) *PFNGLPATCHPARAMETERIPROC)(GLenum pname, GLint value);
typedef void (__attribute__((__stdcall__)) *PFNGLPAUSETRANSFORMFEEDBACKPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLPIXELMAPFVPROC)(GLenum map, GLsizei mapsize, const GLfloat * values);
typedef void (__attribute__((__stdcall__)) *PFNGLPIXELMAPUIVPROC)(GLenum map, GLsizei mapsize, const GLuint * values);
typedef void (__attribute__((__stdcall__)) *PFNGLPIXELMAPUSVPROC)(GLenum map, GLsizei mapsize, const GLushort * values);
typedef void (__attribute__((__stdcall__)) *PFNGLPIXELSTOREFPROC)(GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLPIXELSTOREIPROC)(GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLPIXELTRANSFERFPROC)(GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLPIXELTRANSFERIPROC)(GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLPIXELZOOMPROC)(GLfloat xfactor, GLfloat yfactor);
typedef void (__attribute__((__stdcall__)) *PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLPOINTPARAMETERFVPROC)(GLenum pname, const GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLPOINTPARAMETERIPROC)(GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLPOINTPARAMETERIVPROC)(GLenum pname, const GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLPOINTSIZEPROC)(GLfloat size);
typedef void (__attribute__((__stdcall__)) *PFNGLPOLYGONMODEPROC)(GLenum face, GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
typedef void (__attribute__((__stdcall__)) *PFNGLPOLYGONOFFSETCLAMPPROC)(GLfloat factor, GLfloat units, GLfloat clamp);
typedef void (__attribute__((__stdcall__)) *PFNGLPOLYGONSTIPPLEPROC)(const GLubyte * mask);
typedef void (__attribute__((__stdcall__)) *PFNGLPOPATTRIBPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLPOPCLIENTATTRIBPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLPOPDEBUGGROUPPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLPOPMATRIXPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLPOPNAMEPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLPRIMITIVERESTARTINDEXPROC)(GLuint index);
typedef void (__attribute__((__stdcall__)) *PFNGLPRIORITIZETEXTURESPROC)(GLsizei n, const GLuint * textures, const GLfloat * priorities);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMBINARYPROC)(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMPARAMETERIPROC)(GLuint program, GLenum pname, GLint value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM1DPROC)(GLuint program, GLint location, GLdouble v0);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM1DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM1FPROC)(GLuint program, GLint location, GLfloat v0);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM1FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM1IPROC)(GLuint program, GLint location, GLint v0);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM1IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM1UIPROC)(GLuint program, GLint location, GLuint v0);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM1UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM2DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM2DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM2FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM2FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM2IPROC)(GLuint program, GLint location, GLint v0, GLint v1);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM2IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM2UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM2UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM3DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM3DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM3FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM3FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM3IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM3IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM3UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM3UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM4DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM4DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM4FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM4FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM4IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM4IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM4UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORM4UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC)(GLuint program, GLint location, GLuint64 value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC)(GLuint program, GLint location, GLsizei count, const GLuint64 * values);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLPROVOKINGVERTEXPROC)(GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLPUSHATTRIBPROC)(GLbitfield mask);
typedef void (__attribute__((__stdcall__)) *PFNGLPUSHCLIENTATTRIBPROC)(GLbitfield mask);
typedef void (__attribute__((__stdcall__)) *PFNGLPUSHDEBUGGROUPPROC)(GLenum source, GLuint id, GLsizei length, const GLchar * message);
typedef void (__attribute__((__stdcall__)) *PFNGLPUSHMATRIXPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLPUSHNAMEPROC)(GLuint name);
typedef void (__attribute__((__stdcall__)) *PFNGLQUERYCOUNTERPROC)(GLuint id, GLenum target);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS2DPROC)(GLdouble x, GLdouble y);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS2DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS2FPROC)(GLfloat x, GLfloat y);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS2FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS2IPROC)(GLint x, GLint y);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS2IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS2SPROC)(GLshort x, GLshort y);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS2SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS3DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS3FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS3IPROC)(GLint x, GLint y, GLint z);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS3IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS3SPROC)(GLshort x, GLshort y, GLshort z);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS3SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS4DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS4FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS4IPROC)(GLint x, GLint y, GLint z, GLint w);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS4IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (__attribute__((__stdcall__)) *PFNGLRASTERPOS4SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLREADBUFFERPROC)(GLenum src);
typedef void (__attribute__((__stdcall__)) *PFNGLREADPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLREADNPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data);
typedef void (__attribute__((__stdcall__)) *PFNGLRECTDPROC)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
typedef void (__attribute__((__stdcall__)) *PFNGLRECTDVPROC)(const GLdouble * v1, const GLdouble * v2);
typedef void (__attribute__((__stdcall__)) *PFNGLRECTFPROC)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
typedef void (__attribute__((__stdcall__)) *PFNGLRECTFVPROC)(const GLfloat * v1, const GLfloat * v2);
typedef void (__attribute__((__stdcall__)) *PFNGLRECTIPROC)(GLint x1, GLint y1, GLint x2, GLint y2);
typedef void (__attribute__((__stdcall__)) *PFNGLRECTIVPROC)(const GLint * v1, const GLint * v2);
typedef void (__attribute__((__stdcall__)) *PFNGLRECTSPROC)(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
typedef void (__attribute__((__stdcall__)) *PFNGLRECTSVPROC)(const GLshort * v1, const GLshort * v2);
typedef void (__attribute__((__stdcall__)) *PFNGLRELEASESHADERCOMPILERPROC)(void);
typedef GLint (__attribute__((__stdcall__)) *PFNGLRENDERMODEPROC)(GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLRESUMETRANSFORMFEEDBACKPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLROTATEDPROC)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
typedef void (__attribute__((__stdcall__)) *PFNGLROTATEFPROC)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef void (__attribute__((__stdcall__)) *PFNGLSAMPLECOVERAGEPROC)(GLfloat value, GLboolean invert);
typedef void (__attribute__((__stdcall__)) *PFNGLSAMPLEMASKIPROC)(GLuint maskNumber, GLbitfield mask);
typedef void (__attribute__((__stdcall__)) *PFNGLSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, const GLint * param);
typedef void (__attribute__((__stdcall__)) *PFNGLSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, const GLuint * param);
typedef void (__attribute__((__stdcall__)) *PFNGLSAMPLERPARAMETERFPROC)(GLuint sampler, GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, const GLfloat * param);
typedef void (__attribute__((__stdcall__)) *PFNGLSAMPLERPARAMETERIPROC)(GLuint sampler, GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, const GLint * param);
typedef void (__attribute__((__stdcall__)) *PFNGLSCALEDPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (__attribute__((__stdcall__)) *PFNGLSCALEFPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (__attribute__((__stdcall__)) *PFNGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLSCISSORARRAYVPROC)(GLuint first, GLsizei count, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLSCISSORINDEXEDPROC)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLSCISSORINDEXEDVPROC)(GLuint index, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3BVPROC)(const GLbyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3IPROC)(GLint red, GLint green, GLint blue);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3UBVPROC)(const GLubyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3UIVPROC)(const GLuint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLOR3USVPROC)(const GLushort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLORP3UIPROC)(GLenum type, GLuint color);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLORP3UIVPROC)(GLenum type, const GLuint * color);
typedef void (__attribute__((__stdcall__)) *PFNGLSECONDARYCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLSELECTBUFFERPROC)(GLsizei size, GLuint * buffer);
typedef void (__attribute__((__stdcall__)) *PFNGLSHADEMODELPROC)(GLenum mode);
typedef void (__attribute__((__stdcall__)) *PFNGLSHADERBINARYPROC)(GLsizei count, const GLuint * shaders, GLenum binaryFormat, const void * binary, GLsizei length);
typedef void (__attribute__((__stdcall__)) *PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length);
typedef void (__attribute__((__stdcall__)) *PFNGLSHADERSTORAGEBLOCKBINDINGPROC)(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
typedef void (__attribute__((__stdcall__)) *PFNGLSPECIALIZESHADERPROC)(GLuint shader, const GLchar * pEntryPoint, GLuint numSpecializationConstants, const GLuint * pConstantIndex, const GLuint * pConstantValue);
typedef void (__attribute__((__stdcall__)) *PFNGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
typedef void (__attribute__((__stdcall__)) *PFNGLSTENCILFUNCSEPARATEPROC)(GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (__attribute__((__stdcall__)) *PFNGLSTENCILMASKPROC)(GLuint mask);
typedef void (__attribute__((__stdcall__)) *PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, GLuint mask);
typedef void (__attribute__((__stdcall__)) *PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
typedef void (__attribute__((__stdcall__)) *PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXBUFFERPROC)(GLenum target, GLenum internalformat, GLuint buffer);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXBUFFERRANGEPROC)(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD1DPROC)(GLdouble s);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD1DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD1FPROC)(GLfloat s);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD1FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD1IPROC)(GLint s);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD1IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD1SPROC)(GLshort s);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD1SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD2DPROC)(GLdouble s, GLdouble t);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD2DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD2FPROC)(GLfloat s, GLfloat t);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD2FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD2IPROC)(GLint s, GLint t);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD2IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD2SPROC)(GLshort s, GLshort t);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD2SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD3DPROC)(GLdouble s, GLdouble t, GLdouble r);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD3DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD3FPROC)(GLfloat s, GLfloat t, GLfloat r);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD3FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD3IPROC)(GLint s, GLint t, GLint r);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD3IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD3SPROC)(GLshort s, GLshort t, GLshort r);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD3SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD4DPROC)(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD4DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD4FPROC)(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD4FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD4IPROC)(GLint s, GLint t, GLint r, GLint q);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD4IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD4SPROC)(GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORD4SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORDP1UIPROC)(GLenum type, GLuint coords);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORDP1UIVPROC)(GLenum type, const GLuint * coords);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORDP2UIPROC)(GLenum type, GLuint coords);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORDP2UIVPROC)(GLenum type, const GLuint * coords);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORDP3UIPROC)(GLenum type, GLuint coords);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORDP3UIVPROC)(GLenum type, const GLuint * coords);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORDP4UIPROC)(GLenum type, GLuint coords);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORDP4UIVPROC)(GLenum type, const GLuint * coords);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXCOORDPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXENVFPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXENVFVPROC)(GLenum target, GLenum pname, const GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXENVIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXENVIVPROC)(GLenum target, GLenum pname, const GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXGENDPROC)(GLenum coord, GLenum pname, GLdouble param);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXGENDVPROC)(GLenum coord, GLenum pname, const GLdouble * params);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXGENFPROC)(GLenum coord, GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXGENFVPROC)(GLenum coord, GLenum pname, const GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXGENIPROC)(GLenum coord, GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXGENIVPROC)(GLenum coord, GLenum pname, const GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXIMAGE1DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXIMAGE3DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXIMAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, const GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, const GLuint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat * params);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXSTORAGE1DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXSTORAGE2DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXSTORAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXSTORAGE3DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXSTORAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTUREBARRIERPROC)(void);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTUREBUFFERPROC)(GLuint texture, GLenum internalformat, GLuint buffer);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTUREBUFFERRANGEPROC)(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTUREPARAMETERIIVPROC)(GLuint texture, GLenum pname, const GLint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTUREPARAMETERIUIVPROC)(GLuint texture, GLenum pname, const GLuint * params);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTUREPARAMETERFPROC)(GLuint texture, GLenum pname, GLfloat param);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTUREPARAMETERFVPROC)(GLuint texture, GLenum pname, const GLfloat * param);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTUREPARAMETERIPROC)(GLuint texture, GLenum pname, GLint param);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTUREPARAMETERIVPROC)(GLuint texture, GLenum pname, const GLint * param);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTURESTORAGE1DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTURESTORAGE2DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTURESTORAGE3DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
typedef void (__attribute__((__stdcall__)) *PFNGLTEXTUREVIEWPROC)(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
typedef void (__attribute__((__stdcall__)) *PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)(GLuint xfb, GLuint index, GLuint buffer);
typedef void (__attribute__((__stdcall__)) *PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (__attribute__((__stdcall__)) *PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode);
typedef void (__attribute__((__stdcall__)) *PFNGLTRANSLATEDPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (__attribute__((__stdcall__)) *PFNGLTRANSLATEFPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM1DPROC)(GLint location, GLdouble x);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM1DVPROC)(GLint location, GLsizei count, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM1FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM1IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM1UIPROC)(GLint location, GLuint v0);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM1UIVPROC)(GLint location, GLsizei count, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM2DPROC)(GLint location, GLdouble x, GLdouble y);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM2DVPROC)(GLint location, GLsizei count, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM2IPROC)(GLint location, GLint v0, GLint v1);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM2IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM2UIPROC)(GLint location, GLuint v0, GLuint v1);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM2UIVPROC)(GLint location, GLsizei count, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM3DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM3DVPROC)(GLint location, GLsizei count, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM3IPROC)(GLint location, GLint v0, GLint v1, GLint v2);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM3IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM3UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM3UIVPROC)(GLint location, GLsizei count, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM4DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM4DVPROC)(GLint location, GLsizei count, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM4IPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM4IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM4UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORM4UIVPROC)(GLint location, GLsizei count, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMHANDLEUI64ARBPROC)(GLint location, GLuint64 value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMHANDLEUI64VARBPROC)(GLint location, GLsizei count, const GLuint64 * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX2X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX2X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX2X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX2X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX3X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX3X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX3X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX3X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX4X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX4X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX4X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMMATRIX4X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (__attribute__((__stdcall__)) *PFNGLUNIFORMSUBROUTINESUIVPROC)(GLenum shadertype, GLsizei count, const GLuint * indices);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLUNMAPBUFFERPROC)(GLenum target);
typedef GLboolean (__attribute__((__stdcall__)) *PFNGLUNMAPNAMEDBUFFERPROC)(GLuint buffer);
typedef void (__attribute__((__stdcall__)) *PFNGLUSEPROGRAMPROC)(GLuint program);
typedef void (__attribute__((__stdcall__)) *PFNGLUSEPROGRAMSTAGESPROC)(GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (__attribute__((__stdcall__)) *PFNGLVALIDATEPROGRAMPROC)(GLuint program);
typedef void (__attribute__((__stdcall__)) *PFNGLVALIDATEPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX2DPROC)(GLdouble x, GLdouble y);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX2DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX2FPROC)(GLfloat x, GLfloat y);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX2FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX2IPROC)(GLint x, GLint y);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX2IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX2SPROC)(GLshort x, GLshort y);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX2SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX3DPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX3DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX3FPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX3FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX3IPROC)(GLint x, GLint y, GLint z);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX3IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX3SPROC)(GLshort x, GLshort y, GLshort z);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX3SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX4DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX4FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX4IPROC)(GLint x, GLint y, GLint z, GLint w);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX4IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEX4SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXARRAYATTRIBBINDINGPROC)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXARRAYATTRIBFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXARRAYATTRIBIFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXARRAYATTRIBLFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXARRAYBINDINGDIVISORPROC)(GLuint vaobj, GLuint bindingindex, GLuint divisor);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXARRAYELEMENTBUFFERPROC)(GLuint vaobj, GLuint buffer);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXARRAYVERTEXBUFFERPROC)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXARRAYVERTEXBUFFERSPROC)(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB1DPROC)(GLuint index, GLdouble x);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB1DVPROC)(GLuint index, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB1FVPROC)(GLuint index, const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB1SPROC)(GLuint index, GLshort x);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB1SVPROC)(GLuint index, const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB2DPROC)(GLuint index, GLdouble x, GLdouble y);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB2DVPROC)(GLuint index, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB2FVPROC)(GLuint index, const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB2SPROC)(GLuint index, GLshort x, GLshort y);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB2SVPROC)(GLuint index, const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB3DVPROC)(GLuint index, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB3FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB3FVPROC)(GLuint index, const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB3SPROC)(GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB3SVPROC)(GLuint index, const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4NBVPROC)(GLuint index, const GLbyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4NIVPROC)(GLuint index, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4NSVPROC)(GLuint index, const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4NUBPROC)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4NUBVPROC)(GLuint index, const GLubyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4NUIVPROC)(GLuint index, const GLuint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4NUSVPROC)(GLuint index, const GLushort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4BVPROC)(GLuint index, const GLbyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4DVPROC)(GLuint index, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4FVPROC)(GLuint index, const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4IVPROC)(GLuint index, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4SPROC)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4SVPROC)(GLuint index, const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4UBVPROC)(GLuint index, const GLubyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4UIVPROC)(GLuint index, const GLuint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIB4USVPROC)(GLuint index, const GLushort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBBINDINGPROC)(GLuint attribindex, GLuint bindingindex);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBDIVISORPROC)(GLuint index, GLuint divisor);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI1IPROC)(GLuint index, GLint x);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI1IVPROC)(GLuint index, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI1UIPROC)(GLuint index, GLuint x);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI1UIVPROC)(GLuint index, const GLuint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI2IPROC)(GLuint index, GLint x, GLint y);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI2IVPROC)(GLuint index, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI2UIPROC)(GLuint index, GLuint x, GLuint y);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI2UIVPROC)(GLuint index, const GLuint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI3IPROC)(GLuint index, GLint x, GLint y, GLint z);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI3IVPROC)(GLuint index, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI3UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI3UIVPROC)(GLuint index, const GLuint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI4BVPROC)(GLuint index, const GLbyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI4IPROC)(GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI4IVPROC)(GLuint index, const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI4SVPROC)(GLuint index, const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI4UBVPROC)(GLuint index, const GLubyte * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI4UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI4UIVPROC)(GLuint index, const GLuint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBI4USVPROC)(GLuint index, const GLushort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBIFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBL1DPROC)(GLuint index, GLdouble x);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBL1DVPROC)(GLuint index, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBL1UI64ARBPROC)(GLuint index, GLuint64EXT x);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBL1UI64VARBPROC)(GLuint index, const GLuint64EXT * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBL2DPROC)(GLuint index, GLdouble x, GLdouble y);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBL2DVPROC)(GLuint index, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBL3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBL3DVPROC)(GLuint index, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBL4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBL4DVPROC)(GLuint index, const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBLFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBLPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBP1UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBP1UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBP2UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBP2UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBP3UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBP3UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBP4UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBP4UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXBINDINGDIVISORPROC)(GLuint bindingindex, GLuint divisor);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXP2UIPROC)(GLenum type, GLuint value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXP2UIVPROC)(GLenum type, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXP3UIPROC)(GLenum type, GLuint value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXP3UIVPROC)(GLenum type, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXP4UIPROC)(GLenum type, GLuint value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXP4UIVPROC)(GLenum type, const GLuint * value);
typedef void (__attribute__((__stdcall__)) *PFNGLVERTEXPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (__attribute__((__stdcall__)) *PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (__attribute__((__stdcall__)) *PFNGLVIEWPORTARRAYVPROC)(GLuint first, GLsizei count, const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLVIEWPORTINDEXEDFPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
typedef void (__attribute__((__stdcall__)) *PFNGLVIEWPORTINDEXEDFVPROC)(GLuint index, const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS2DPROC)(GLdouble x, GLdouble y);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS2DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS2FPROC)(GLfloat x, GLfloat y);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS2FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS2IPROC)(GLint x, GLint y);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS2IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS2SPROC)(GLshort x, GLshort y);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS2SVPROC)(const GLshort * v);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS3DVPROC)(const GLdouble * v);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS3FVPROC)(const GLfloat * v);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS3IPROC)(GLint x, GLint y, GLint z);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS3IVPROC)(const GLint * v);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS3SPROC)(GLshort x, GLshort y, GLshort z);
typedef void (__attribute__((__stdcall__)) *PFNGLWINDOWPOS3SVPROC)(const GLshort * v);

extern PFNGLACCUMPROC glad_glAccum;

extern PFNGLACTIVESHADERPROGRAMPROC glad_glActiveShaderProgram;

extern PFNGLACTIVETEXTUREPROC glad_glActiveTexture;

extern PFNGLALPHAFUNCPROC glad_glAlphaFunc;

extern PFNGLARETEXTURESRESIDENTPROC glad_glAreTexturesResident;

extern PFNGLARRAYELEMENTPROC glad_glArrayElement;

extern PFNGLATTACHSHADERPROC glad_glAttachShader;

extern PFNGLBEGINPROC glad_glBegin;

extern PFNGLBEGINCONDITIONALRENDERPROC glad_glBeginConditionalRender;

extern PFNGLBEGINQUERYPROC glad_glBeginQuery;

extern PFNGLBEGINQUERYINDEXEDPROC glad_glBeginQueryIndexed;

extern PFNGLBEGINTRANSFORMFEEDBACKPROC glad_glBeginTransformFeedback;

extern PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation;

extern PFNGLBINDBUFFERPROC glad_glBindBuffer;

extern PFNGLBINDBUFFERBASEPROC glad_glBindBufferBase;

extern PFNGLBINDBUFFERRANGEPROC glad_glBindBufferRange;

extern PFNGLBINDBUFFERSBASEPROC glad_glBindBuffersBase;

extern PFNGLBINDBUFFERSRANGEPROC glad_glBindBuffersRange;

extern PFNGLBINDFRAGDATALOCATIONPROC glad_glBindFragDataLocation;

extern PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glad_glBindFragDataLocationIndexed;

extern PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer;

extern PFNGLBINDIMAGETEXTUREPROC glad_glBindImageTexture;

extern PFNGLBINDIMAGETEXTURESPROC glad_glBindImageTextures;

extern PFNGLBINDPROGRAMPIPELINEPROC glad_glBindProgramPipeline;

extern PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer;

extern PFNGLBINDSAMPLERPROC glad_glBindSampler;

extern PFNGLBINDSAMPLERSPROC glad_glBindSamplers;

extern PFNGLBINDTEXTUREPROC glad_glBindTexture;

extern PFNGLBINDTEXTUREUNITPROC glad_glBindTextureUnit;

extern PFNGLBINDTEXTURESPROC glad_glBindTextures;

extern PFNGLBINDTRANSFORMFEEDBACKPROC glad_glBindTransformFeedback;

extern PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;

extern PFNGLBINDVERTEXBUFFERPROC glad_glBindVertexBuffer;

extern PFNGLBINDVERTEXBUFFERSPROC glad_glBindVertexBuffers;

extern PFNGLBITMAPPROC glad_glBitmap;

extern PFNGLBLENDCOLORPROC glad_glBlendColor;

extern PFNGLBLENDEQUATIONPROC glad_glBlendEquation;

extern PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate;

extern PFNGLBLENDEQUATIONSEPARATEIPROC glad_glBlendEquationSeparatei;

extern PFNGLBLENDEQUATIONIPROC glad_glBlendEquationi;

extern PFNGLBLENDFUNCPROC glad_glBlendFunc;

extern PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate;

extern PFNGLBLENDFUNCSEPARATEIPROC glad_glBlendFuncSeparatei;

extern PFNGLBLENDFUNCIPROC glad_glBlendFunci;

extern PFNGLBLITFRAMEBUFFERPROC glad_glBlitFramebuffer;

extern PFNGLBLITNAMEDFRAMEBUFFERPROC glad_glBlitNamedFramebuffer;

extern PFNGLBUFFERDATAPROC glad_glBufferData;

extern PFNGLBUFFERSTORAGEPROC glad_glBufferStorage;

extern PFNGLBUFFERSUBDATAPROC glad_glBufferSubData;

extern PFNGLCALLLISTPROC glad_glCallList;

extern PFNGLCALLLISTSPROC glad_glCallLists;

extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus;

extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC glad_glCheckNamedFramebufferStatus;

extern PFNGLCLAMPCOLORPROC glad_glClampColor;

extern PFNGLCLEARPROC glad_glClear;

extern PFNGLCLEARACCUMPROC glad_glClearAccum;

extern PFNGLCLEARBUFFERDATAPROC glad_glClearBufferData;

extern PFNGLCLEARBUFFERSUBDATAPROC glad_glClearBufferSubData;

extern PFNGLCLEARBUFFERFIPROC glad_glClearBufferfi;

extern PFNGLCLEARBUFFERFVPROC glad_glClearBufferfv;

extern PFNGLCLEARBUFFERIVPROC glad_glClearBufferiv;

extern PFNGLCLEARBUFFERUIVPROC glad_glClearBufferuiv;

extern PFNGLCLEARCOLORPROC glad_glClearColor;

extern PFNGLCLEARDEPTHPROC glad_glClearDepth;

extern PFNGLCLEARDEPTHFPROC glad_glClearDepthf;

extern PFNGLCLEARINDEXPROC glad_glClearIndex;

extern PFNGLCLEARNAMEDBUFFERDATAPROC glad_glClearNamedBufferData;

extern PFNGLCLEARNAMEDBUFFERSUBDATAPROC glad_glClearNamedBufferSubData;

extern PFNGLCLEARNAMEDFRAMEBUFFERFIPROC glad_glClearNamedFramebufferfi;

extern PFNGLCLEARNAMEDFRAMEBUFFERFVPROC glad_glClearNamedFramebufferfv;

extern PFNGLCLEARNAMEDFRAMEBUFFERIVPROC glad_glClearNamedFramebufferiv;

extern PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC glad_glClearNamedFramebufferuiv;

extern PFNGLCLEARSTENCILPROC glad_glClearStencil;

extern PFNGLCLEARTEXIMAGEPROC glad_glClearTexImage;

extern PFNGLCLEARTEXSUBIMAGEPROC glad_glClearTexSubImage;

extern PFNGLCLIENTACTIVETEXTUREPROC glad_glClientActiveTexture;

extern PFNGLCLIENTWAITSYNCPROC glad_glClientWaitSync;

extern PFNGLCLIPCONTROLPROC glad_glClipControl;

extern PFNGLCLIPPLANEPROC glad_glClipPlane;

extern PFNGLCOLOR3BPROC glad_glColor3b;

extern PFNGLCOLOR3BVPROC glad_glColor3bv;

extern PFNGLCOLOR3DPROC glad_glColor3d;

extern PFNGLCOLOR3DVPROC glad_glColor3dv;

extern PFNGLCOLOR3FPROC glad_glColor3f;

extern PFNGLCOLOR3FVPROC glad_glColor3fv;

extern PFNGLCOLOR3IPROC glad_glColor3i;

extern PFNGLCOLOR3IVPROC glad_glColor3iv;

extern PFNGLCOLOR3SPROC glad_glColor3s;

extern PFNGLCOLOR3SVPROC glad_glColor3sv;

extern PFNGLCOLOR3UBPROC glad_glColor3ub;

extern PFNGLCOLOR3UBVPROC glad_glColor3ubv;

extern PFNGLCOLOR3UIPROC glad_glColor3ui;

extern PFNGLCOLOR3UIVPROC glad_glColor3uiv;

extern PFNGLCOLOR3USPROC glad_glColor3us;

extern PFNGLCOLOR3USVPROC glad_glColor3usv;

extern PFNGLCOLOR4BPROC glad_glColor4b;

extern PFNGLCOLOR4BVPROC glad_glColor4bv;

extern PFNGLCOLOR4DPROC glad_glColor4d;

extern PFNGLCOLOR4DVPROC glad_glColor4dv;

extern PFNGLCOLOR4FPROC glad_glColor4f;

extern PFNGLCOLOR4FVPROC glad_glColor4fv;

extern PFNGLCOLOR4IPROC glad_glColor4i;

extern PFNGLCOLOR4IVPROC glad_glColor4iv;

extern PFNGLCOLOR4SPROC glad_glColor4s;

extern PFNGLCOLOR4SVPROC glad_glColor4sv;

extern PFNGLCOLOR4UBPROC glad_glColor4ub;

extern PFNGLCOLOR4UBVPROC glad_glColor4ubv;

extern PFNGLCOLOR4UIPROC glad_glColor4ui;

extern PFNGLCOLOR4UIVPROC glad_glColor4uiv;

extern PFNGLCOLOR4USPROC glad_glColor4us;

extern PFNGLCOLOR4USVPROC glad_glColor4usv;

extern PFNGLCOLORMASKPROC glad_glColorMask;

extern PFNGLCOLORMASKIPROC glad_glColorMaski;

extern PFNGLCOLORMATERIALPROC glad_glColorMaterial;

extern PFNGLCOLORP3UIPROC glad_glColorP3ui;

extern PFNGLCOLORP3UIVPROC glad_glColorP3uiv;

extern PFNGLCOLORP4UIPROC glad_glColorP4ui;

extern PFNGLCOLORP4UIVPROC glad_glColorP4uiv;

extern PFNGLCOLORPOINTERPROC glad_glColorPointer;

extern PFNGLCOMPILESHADERPROC glad_glCompileShader;

extern PFNGLCOMPRESSEDTEXIMAGE1DPROC glad_glCompressedTexImage1D;

extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D;

extern PFNGLCOMPRESSEDTEXIMAGE3DPROC glad_glCompressedTexImage3D;

extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glad_glCompressedTexSubImage1D;

extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D;

extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glad_glCompressedTexSubImage3D;

extern PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC glad_glCompressedTextureSubImage1D;

extern PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC glad_glCompressedTextureSubImage2D;

extern PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC glad_glCompressedTextureSubImage3D;

extern PFNGLCOPYBUFFERSUBDATAPROC glad_glCopyBufferSubData;

extern PFNGLCOPYIMAGESUBDATAPROC glad_glCopyImageSubData;

extern PFNGLCOPYNAMEDBUFFERSUBDATAPROC glad_glCopyNamedBufferSubData;

extern PFNGLCOPYPIXELSPROC glad_glCopyPixels;

extern PFNGLCOPYTEXIMAGE1DPROC glad_glCopyTexImage1D;

extern PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D;

extern PFNGLCOPYTEXSUBIMAGE1DPROC glad_glCopyTexSubImage1D;

extern PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D;

extern PFNGLCOPYTEXSUBIMAGE3DPROC glad_glCopyTexSubImage3D;

extern PFNGLCOPYTEXTURESUBIMAGE1DPROC glad_glCopyTextureSubImage1D;

extern PFNGLCOPYTEXTURESUBIMAGE2DPROC glad_glCopyTextureSubImage2D;

extern PFNGLCOPYTEXTURESUBIMAGE3DPROC glad_glCopyTextureSubImage3D;

extern PFNGLCREATEBUFFERSPROC glad_glCreateBuffers;

extern PFNGLCREATEFRAMEBUFFERSPROC glad_glCreateFramebuffers;

extern PFNGLCREATEPROGRAMPROC glad_glCreateProgram;

extern PFNGLCREATEPROGRAMPIPELINESPROC glad_glCreateProgramPipelines;

extern PFNGLCREATEQUERIESPROC glad_glCreateQueries;

extern PFNGLCREATERENDERBUFFERSPROC glad_glCreateRenderbuffers;

extern PFNGLCREATESAMPLERSPROC glad_glCreateSamplers;

extern PFNGLCREATESHADERPROC glad_glCreateShader;

extern PFNGLCREATESHADERPROGRAMVPROC glad_glCreateShaderProgramv;

extern PFNGLCREATETEXTURESPROC glad_glCreateTextures;

extern PFNGLCREATETRANSFORMFEEDBACKSPROC glad_glCreateTransformFeedbacks;

extern PFNGLCREATEVERTEXARRAYSPROC glad_glCreateVertexArrays;

extern PFNGLCULLFACEPROC glad_glCullFace;

extern PFNGLDEBUGMESSAGECALLBACKPROC glad_glDebugMessageCallback;

extern PFNGLDEBUGMESSAGECONTROLPROC glad_glDebugMessageControl;

extern PFNGLDEBUGMESSAGEINSERTPROC glad_glDebugMessageInsert;

extern PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;

extern PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers;

extern PFNGLDELETELISTSPROC glad_glDeleteLists;

extern PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;

extern PFNGLDELETEPROGRAMPIPELINESPROC glad_glDeleteProgramPipelines;

extern PFNGLDELETEQUERIESPROC glad_glDeleteQueries;

extern PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers;

extern PFNGLDELETESAMPLERSPROC glad_glDeleteSamplers;

extern PFNGLDELETESHADERPROC glad_glDeleteShader;

extern PFNGLDELETESYNCPROC glad_glDeleteSync;

extern PFNGLDELETETEXTURESPROC glad_glDeleteTextures;

extern PFNGLDELETETRANSFORMFEEDBACKSPROC glad_glDeleteTransformFeedbacks;

extern PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;

extern PFNGLDEPTHFUNCPROC glad_glDepthFunc;

extern PFNGLDEPTHMASKPROC glad_glDepthMask;

extern PFNGLDEPTHRANGEPROC glad_glDepthRange;

extern PFNGLDEPTHRANGEARRAYVPROC glad_glDepthRangeArrayv;

extern PFNGLDEPTHRANGEINDEXEDPROC glad_glDepthRangeIndexed;

extern PFNGLDEPTHRANGEFPROC glad_glDepthRangef;

extern PFNGLDETACHSHADERPROC glad_glDetachShader;

extern PFNGLDISABLEPROC glad_glDisable;

extern PFNGLDISABLECLIENTSTATEPROC glad_glDisableClientState;

extern PFNGLDISABLEVERTEXARRAYATTRIBPROC glad_glDisableVertexArrayAttrib;

extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray;

extern PFNGLDISABLEIPROC glad_glDisablei;

extern PFNGLDISPATCHCOMPUTEPROC glad_glDispatchCompute;

extern PFNGLDISPATCHCOMPUTEINDIRECTPROC glad_glDispatchComputeIndirect;

extern PFNGLDRAWARRAYSPROC glad_glDrawArrays;

extern PFNGLDRAWARRAYSINDIRECTPROC glad_glDrawArraysIndirect;

extern PFNGLDRAWARRAYSINSTANCEDPROC glad_glDrawArraysInstanced;

extern PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glad_glDrawArraysInstancedBaseInstance;

extern PFNGLDRAWBUFFERPROC glad_glDrawBuffer;

extern PFNGLDRAWBUFFERSPROC glad_glDrawBuffers;

extern PFNGLDRAWELEMENTSPROC glad_glDrawElements;

extern PFNGLDRAWELEMENTSBASEVERTEXPROC glad_glDrawElementsBaseVertex;

extern PFNGLDRAWELEMENTSINDIRECTPROC glad_glDrawElementsIndirect;

extern PFNGLDRAWELEMENTSINSTANCEDPROC glad_glDrawElementsInstanced;

extern PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glad_glDrawElementsInstancedBaseInstance;

extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glad_glDrawElementsInstancedBaseVertex;

extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glad_glDrawElementsInstancedBaseVertexBaseInstance;

extern PFNGLDRAWPIXELSPROC glad_glDrawPixels;

extern PFNGLDRAWRANGEELEMENTSPROC glad_glDrawRangeElements;

extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glad_glDrawRangeElementsBaseVertex;

extern PFNGLDRAWTRANSFORMFEEDBACKPROC glad_glDrawTransformFeedback;

extern PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glad_glDrawTransformFeedbackInstanced;

extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glad_glDrawTransformFeedbackStream;

extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC glad_glDrawTransformFeedbackStreamInstanced;

extern PFNGLEDGEFLAGPROC glad_glEdgeFlag;

extern PFNGLEDGEFLAGPOINTERPROC glad_glEdgeFlagPointer;

extern PFNGLEDGEFLAGVPROC glad_glEdgeFlagv;

extern PFNGLENABLEPROC glad_glEnable;

extern PFNGLENABLECLIENTSTATEPROC glad_glEnableClientState;

extern PFNGLENABLEVERTEXARRAYATTRIBPROC glad_glEnableVertexArrayAttrib;

extern PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;

extern PFNGLENABLEIPROC glad_glEnablei;

extern PFNGLENDPROC glad_glEnd;

extern PFNGLENDCONDITIONALRENDERPROC glad_glEndConditionalRender;

extern PFNGLENDLISTPROC glad_glEndList;

extern PFNGLENDQUERYPROC glad_glEndQuery;

extern PFNGLENDQUERYINDEXEDPROC glad_glEndQueryIndexed;

extern PFNGLENDTRANSFORMFEEDBACKPROC glad_glEndTransformFeedback;

extern PFNGLEVALCOORD1DPROC glad_glEvalCoord1d;

extern PFNGLEVALCOORD1DVPROC glad_glEvalCoord1dv;

extern PFNGLEVALCOORD1FPROC glad_glEvalCoord1f;

extern PFNGLEVALCOORD1FVPROC glad_glEvalCoord1fv;

extern PFNGLEVALCOORD2DPROC glad_glEvalCoord2d;

extern PFNGLEVALCOORD2DVPROC glad_glEvalCoord2dv;

extern PFNGLEVALCOORD2FPROC glad_glEvalCoord2f;

extern PFNGLEVALCOORD2FVPROC glad_glEvalCoord2fv;

extern PFNGLEVALMESH1PROC glad_glEvalMesh1;

extern PFNGLEVALMESH2PROC glad_glEvalMesh2;

extern PFNGLEVALPOINT1PROC glad_glEvalPoint1;

extern PFNGLEVALPOINT2PROC glad_glEvalPoint2;

extern PFNGLFEEDBACKBUFFERPROC glad_glFeedbackBuffer;

extern PFNGLFENCESYNCPROC glad_glFenceSync;

extern PFNGLFINISHPROC glad_glFinish;

extern PFNGLFLUSHPROC glad_glFlush;

extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC glad_glFlushMappedBufferRange;

extern PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC glad_glFlushMappedNamedBufferRange;

extern PFNGLFOGCOORDPOINTERPROC glad_glFogCoordPointer;

extern PFNGLFOGCOORDDPROC glad_glFogCoordd;

extern PFNGLFOGCOORDDVPROC glad_glFogCoorddv;

extern PFNGLFOGCOORDFPROC glad_glFogCoordf;

extern PFNGLFOGCOORDFVPROC glad_glFogCoordfv;

extern PFNGLFOGFPROC glad_glFogf;

extern PFNGLFOGFVPROC glad_glFogfv;

extern PFNGLFOGIPROC glad_glFogi;

extern PFNGLFOGIVPROC glad_glFogiv;

extern PFNGLFRAMEBUFFERPARAMETERIPROC glad_glFramebufferParameteri;

extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer;

extern PFNGLFRAMEBUFFERTEXTUREPROC glad_glFramebufferTexture;

extern PFNGLFRAMEBUFFERTEXTURE1DPROC glad_glFramebufferTexture1D;

extern PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D;

extern PFNGLFRAMEBUFFERTEXTURE3DPROC glad_glFramebufferTexture3D;

extern PFNGLFRAMEBUFFERTEXTURELAYERPROC glad_glFramebufferTextureLayer;

extern PFNGLFRONTFACEPROC glad_glFrontFace;

extern PFNGLFRUSTUMPROC glad_glFrustum;

extern PFNGLGENBUFFERSPROC glad_glGenBuffers;

extern PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers;

extern PFNGLGENLISTSPROC glad_glGenLists;

extern PFNGLGENPROGRAMPIPELINESPROC glad_glGenProgramPipelines;

extern PFNGLGENQUERIESPROC glad_glGenQueries;

extern PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers;

extern PFNGLGENSAMPLERSPROC glad_glGenSamplers;

extern PFNGLGENTEXTURESPROC glad_glGenTextures;

extern PFNGLGENTRANSFORMFEEDBACKSPROC glad_glGenTransformFeedbacks;

extern PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;

extern PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap;

extern PFNGLGENERATETEXTUREMIPMAPPROC glad_glGenerateTextureMipmap;

extern PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glad_glGetActiveAtomicCounterBufferiv;

extern PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib;

extern PFNGLGETACTIVESUBROUTINENAMEPROC glad_glGetActiveSubroutineName;

extern PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glad_glGetActiveSubroutineUniformName;

extern PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glad_glGetActiveSubroutineUniformiv;

extern PFNGLGETACTIVEUNIFORMPROC glad_glGetActiveUniform;

extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glad_glGetActiveUniformBlockName;

extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC glad_glGetActiveUniformBlockiv;

extern PFNGLGETACTIVEUNIFORMNAMEPROC glad_glGetActiveUniformName;

extern PFNGLGETACTIVEUNIFORMSIVPROC glad_glGetActiveUniformsiv;

extern PFNGLGETATTACHEDSHADERSPROC glad_glGetAttachedShaders;

extern PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation;

extern PFNGLGETBOOLEANI_VPROC glad_glGetBooleani_v;

extern PFNGLGETBOOLEANVPROC glad_glGetBooleanv;

extern PFNGLGETBUFFERPARAMETERI64VPROC glad_glGetBufferParameteri64v;

extern PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv;

extern PFNGLGETBUFFERPOINTERVPROC glad_glGetBufferPointerv;

extern PFNGLGETBUFFERSUBDATAPROC glad_glGetBufferSubData;

extern PFNGLGETCLIPPLANEPROC glad_glGetClipPlane;

extern PFNGLGETCOMPRESSEDTEXIMAGEPROC glad_glGetCompressedTexImage;

extern PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC glad_glGetCompressedTextureImage;

extern PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC glad_glGetCompressedTextureSubImage;

extern PFNGLGETDEBUGMESSAGELOGPROC glad_glGetDebugMessageLog;

extern PFNGLGETDOUBLEI_VPROC glad_glGetDoublei_v;

extern PFNGLGETDOUBLEVPROC glad_glGetDoublev;

extern PFNGLGETERRORPROC glad_glGetError;

extern PFNGLGETFLOATI_VPROC glad_glGetFloati_v;

extern PFNGLGETFLOATVPROC glad_glGetFloatv;

extern PFNGLGETFRAGDATAINDEXPROC glad_glGetFragDataIndex;

extern PFNGLGETFRAGDATALOCATIONPROC glad_glGetFragDataLocation;

extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetFramebufferAttachmentParameteriv;

extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC glad_glGetFramebufferParameteriv;

extern PFNGLGETGRAPHICSRESETSTATUSPROC glad_glGetGraphicsResetStatus;

extern PFNGLGETIMAGEHANDLEARBPROC glad_glGetImageHandleARB;

extern PFNGLGETINTEGER64I_VPROC glad_glGetInteger64i_v;

extern PFNGLGETINTEGER64VPROC glad_glGetInteger64v;

extern PFNGLGETINTEGERI_VPROC glad_glGetIntegeri_v;

extern PFNGLGETINTEGERVPROC glad_glGetIntegerv;

extern PFNGLGETINTERNALFORMATI64VPROC glad_glGetInternalformati64v;

extern PFNGLGETINTERNALFORMATIVPROC glad_glGetInternalformativ;

extern PFNGLGETLIGHTFVPROC glad_glGetLightfv;

extern PFNGLGETLIGHTIVPROC glad_glGetLightiv;

extern PFNGLGETMAPDVPROC glad_glGetMapdv;

extern PFNGLGETMAPFVPROC glad_glGetMapfv;

extern PFNGLGETMAPIVPROC glad_glGetMapiv;

extern PFNGLGETMATERIALFVPROC glad_glGetMaterialfv;

extern PFNGLGETMATERIALIVPROC glad_glGetMaterialiv;

extern PFNGLGETMULTISAMPLEFVPROC glad_glGetMultisamplefv;

extern PFNGLGETNAMEDBUFFERPARAMETERI64VPROC glad_glGetNamedBufferParameteri64v;

extern PFNGLGETNAMEDBUFFERPARAMETERIVPROC glad_glGetNamedBufferParameteriv;

extern PFNGLGETNAMEDBUFFERPOINTERVPROC glad_glGetNamedBufferPointerv;

extern PFNGLGETNAMEDBUFFERSUBDATAPROC glad_glGetNamedBufferSubData;

extern PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetNamedFramebufferAttachmentParameteriv;

extern PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC glad_glGetNamedFramebufferParameteriv;

extern PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC glad_glGetNamedRenderbufferParameteriv;

extern PFNGLGETOBJECTLABELPROC glad_glGetObjectLabel;

extern PFNGLGETOBJECTPTRLABELPROC glad_glGetObjectPtrLabel;

extern PFNGLGETPIXELMAPFVPROC glad_glGetPixelMapfv;

extern PFNGLGETPIXELMAPUIVPROC glad_glGetPixelMapuiv;

extern PFNGLGETPIXELMAPUSVPROC glad_glGetPixelMapusv;

extern PFNGLGETPOINTERVPROC glad_glGetPointerv;

extern PFNGLGETPOLYGONSTIPPLEPROC glad_glGetPolygonStipple;

extern PFNGLGETPROGRAMBINARYPROC glad_glGetProgramBinary;

extern PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;

extern PFNGLGETPROGRAMINTERFACEIVPROC glad_glGetProgramInterfaceiv;

extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC glad_glGetProgramPipelineInfoLog;

extern PFNGLGETPROGRAMPIPELINEIVPROC glad_glGetProgramPipelineiv;

extern PFNGLGETPROGRAMRESOURCEINDEXPROC glad_glGetProgramResourceIndex;

extern PFNGLGETPROGRAMRESOURCELOCATIONPROC glad_glGetProgramResourceLocation;

extern PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glad_glGetProgramResourceLocationIndex;

extern PFNGLGETPROGRAMRESOURCENAMEPROC glad_glGetProgramResourceName;

extern PFNGLGETPROGRAMRESOURCEIVPROC glad_glGetProgramResourceiv;

extern PFNGLGETPROGRAMSTAGEIVPROC glad_glGetProgramStageiv;

extern PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;

extern PFNGLGETQUERYBUFFEROBJECTI64VPROC glad_glGetQueryBufferObjecti64v;

extern PFNGLGETQUERYBUFFEROBJECTIVPROC glad_glGetQueryBufferObjectiv;

extern PFNGLGETQUERYBUFFEROBJECTUI64VPROC glad_glGetQueryBufferObjectui64v;

extern PFNGLGETQUERYBUFFEROBJECTUIVPROC glad_glGetQueryBufferObjectuiv;

extern PFNGLGETQUERYINDEXEDIVPROC glad_glGetQueryIndexediv;

extern PFNGLGETQUERYOBJECTI64VPROC glad_glGetQueryObjecti64v;

extern PFNGLGETQUERYOBJECTIVPROC glad_glGetQueryObjectiv;

extern PFNGLGETQUERYOBJECTUI64VPROC glad_glGetQueryObjectui64v;

extern PFNGLGETQUERYOBJECTUIVPROC glad_glGetQueryObjectuiv;

extern PFNGLGETQUERYIVPROC glad_glGetQueryiv;

extern PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_glGetRenderbufferParameteriv;

extern PFNGLGETSAMPLERPARAMETERIIVPROC glad_glGetSamplerParameterIiv;

extern PFNGLGETSAMPLERPARAMETERIUIVPROC glad_glGetSamplerParameterIuiv;

extern PFNGLGETSAMPLERPARAMETERFVPROC glad_glGetSamplerParameterfv;

extern PFNGLGETSAMPLERPARAMETERIVPROC glad_glGetSamplerParameteriv;

extern PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;

extern PFNGLGETSHADERPRECISIONFORMATPROC glad_glGetShaderPrecisionFormat;

extern PFNGLGETSHADERSOURCEPROC glad_glGetShaderSource;

extern PFNGLGETSHADERIVPROC glad_glGetShaderiv;

extern PFNGLGETSTRINGPROC glad_glGetString;

extern PFNGLGETSTRINGIPROC glad_glGetStringi;

extern PFNGLGETSUBROUTINEINDEXPROC glad_glGetSubroutineIndex;

extern PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glad_glGetSubroutineUniformLocation;

extern PFNGLGETSYNCIVPROC glad_glGetSynciv;

extern PFNGLGETTEXENVFVPROC glad_glGetTexEnvfv;

extern PFNGLGETTEXENVIVPROC glad_glGetTexEnviv;

extern PFNGLGETTEXGENDVPROC glad_glGetTexGendv;

extern PFNGLGETTEXGENFVPROC glad_glGetTexGenfv;

extern PFNGLGETTEXGENIVPROC glad_glGetTexGeniv;

extern PFNGLGETTEXIMAGEPROC glad_glGetTexImage;

extern PFNGLGETTEXLEVELPARAMETERFVPROC glad_glGetTexLevelParameterfv;

extern PFNGLGETTEXLEVELPARAMETERIVPROC glad_glGetTexLevelParameteriv;

extern PFNGLGETTEXPARAMETERIIVPROC glad_glGetTexParameterIiv;

extern PFNGLGETTEXPARAMETERIUIVPROC glad_glGetTexParameterIuiv;

extern PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv;

extern PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv;

extern PFNGLGETTEXTUREHANDLEARBPROC glad_glGetTextureHandleARB;

extern PFNGLGETTEXTUREIMAGEPROC glad_glGetTextureImage;

extern PFNGLGETTEXTURELEVELPARAMETERFVPROC glad_glGetTextureLevelParameterfv;

extern PFNGLGETTEXTURELEVELPARAMETERIVPROC glad_glGetTextureLevelParameteriv;

extern PFNGLGETTEXTUREPARAMETERIIVPROC glad_glGetTextureParameterIiv;

extern PFNGLGETTEXTUREPARAMETERIUIVPROC glad_glGetTextureParameterIuiv;

extern PFNGLGETTEXTUREPARAMETERFVPROC glad_glGetTextureParameterfv;

extern PFNGLGETTEXTUREPARAMETERIVPROC glad_glGetTextureParameteriv;

extern PFNGLGETTEXTURESAMPLERHANDLEARBPROC glad_glGetTextureSamplerHandleARB;

extern PFNGLGETTEXTURESUBIMAGEPROC glad_glGetTextureSubImage;

extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glad_glGetTransformFeedbackVarying;

extern PFNGLGETTRANSFORMFEEDBACKI64_VPROC glad_glGetTransformFeedbacki64_v;

extern PFNGLGETTRANSFORMFEEDBACKI_VPROC glad_glGetTransformFeedbacki_v;

extern PFNGLGETTRANSFORMFEEDBACKIVPROC glad_glGetTransformFeedbackiv;

extern PFNGLGETUNIFORMBLOCKINDEXPROC glad_glGetUniformBlockIndex;

extern PFNGLGETUNIFORMINDICESPROC glad_glGetUniformIndices;

extern PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;

extern PFNGLGETUNIFORMSUBROUTINEUIVPROC glad_glGetUniformSubroutineuiv;

extern PFNGLGETUNIFORMDVPROC glad_glGetUniformdv;

extern PFNGLGETUNIFORMFVPROC glad_glGetUniformfv;

extern PFNGLGETUNIFORMIVPROC glad_glGetUniformiv;

extern PFNGLGETUNIFORMUIVPROC glad_glGetUniformuiv;

extern PFNGLGETVERTEXARRAYINDEXED64IVPROC glad_glGetVertexArrayIndexed64iv;

extern PFNGLGETVERTEXARRAYINDEXEDIVPROC glad_glGetVertexArrayIndexediv;

extern PFNGLGETVERTEXARRAYIVPROC glad_glGetVertexArrayiv;

extern PFNGLGETVERTEXATTRIBIIVPROC glad_glGetVertexAttribIiv;

extern PFNGLGETVERTEXATTRIBIUIVPROC glad_glGetVertexAttribIuiv;

extern PFNGLGETVERTEXATTRIBLDVPROC glad_glGetVertexAttribLdv;

extern PFNGLGETVERTEXATTRIBLUI64VARBPROC glad_glGetVertexAttribLui64vARB;

extern PFNGLGETVERTEXATTRIBPOINTERVPROC glad_glGetVertexAttribPointerv;

extern PFNGLGETVERTEXATTRIBDVPROC glad_glGetVertexAttribdv;

extern PFNGLGETVERTEXATTRIBFVPROC glad_glGetVertexAttribfv;

extern PFNGLGETVERTEXATTRIBIVPROC glad_glGetVertexAttribiv;

extern PFNGLGETNCOLORTABLEPROC glad_glGetnColorTable;

extern PFNGLGETNCOMPRESSEDTEXIMAGEPROC glad_glGetnCompressedTexImage;

extern PFNGLGETNCONVOLUTIONFILTERPROC glad_glGetnConvolutionFilter;

extern PFNGLGETNHISTOGRAMPROC glad_glGetnHistogram;

extern PFNGLGETNMAPDVPROC glad_glGetnMapdv;

extern PFNGLGETNMAPFVPROC glad_glGetnMapfv;

extern PFNGLGETNMAPIVPROC glad_glGetnMapiv;

extern PFNGLGETNMINMAXPROC glad_glGetnMinmax;

extern PFNGLGETNPIXELMAPFVPROC glad_glGetnPixelMapfv;

extern PFNGLGETNPIXELMAPUIVPROC glad_glGetnPixelMapuiv;

extern PFNGLGETNPIXELMAPUSVPROC glad_glGetnPixelMapusv;

extern PFNGLGETNPOLYGONSTIPPLEPROC glad_glGetnPolygonStipple;

extern PFNGLGETNSEPARABLEFILTERPROC glad_glGetnSeparableFilter;

extern PFNGLGETNTEXIMAGEPROC glad_glGetnTexImage;

extern PFNGLGETNUNIFORMDVPROC glad_glGetnUniformdv;

extern PFNGLGETNUNIFORMFVPROC glad_glGetnUniformfv;

extern PFNGLGETNUNIFORMIVPROC glad_glGetnUniformiv;

extern PFNGLGETNUNIFORMUIVPROC glad_glGetnUniformuiv;

extern PFNGLHINTPROC glad_glHint;

extern PFNGLINDEXMASKPROC glad_glIndexMask;

extern PFNGLINDEXPOINTERPROC glad_glIndexPointer;

extern PFNGLINDEXDPROC glad_glIndexd;

extern PFNGLINDEXDVPROC glad_glIndexdv;

extern PFNGLINDEXFPROC glad_glIndexf;

extern PFNGLINDEXFVPROC glad_glIndexfv;

extern PFNGLINDEXIPROC glad_glIndexi;

extern PFNGLINDEXIVPROC glad_glIndexiv;

extern PFNGLINDEXSPROC glad_glIndexs;

extern PFNGLINDEXSVPROC glad_glIndexsv;

extern PFNGLINDEXUBPROC glad_glIndexub;

extern PFNGLINDEXUBVPROC glad_glIndexubv;

extern PFNGLINITNAMESPROC glad_glInitNames;

extern PFNGLINTERLEAVEDARRAYSPROC glad_glInterleavedArrays;

extern PFNGLINVALIDATEBUFFERDATAPROC glad_glInvalidateBufferData;

extern PFNGLINVALIDATEBUFFERSUBDATAPROC glad_glInvalidateBufferSubData;

extern PFNGLINVALIDATEFRAMEBUFFERPROC glad_glInvalidateFramebuffer;

extern PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC glad_glInvalidateNamedFramebufferData;

extern PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC glad_glInvalidateNamedFramebufferSubData;

extern PFNGLINVALIDATESUBFRAMEBUFFERPROC glad_glInvalidateSubFramebuffer;

extern PFNGLINVALIDATETEXIMAGEPROC glad_glInvalidateTexImage;

extern PFNGLINVALIDATETEXSUBIMAGEPROC glad_glInvalidateTexSubImage;

extern PFNGLISBUFFERPROC glad_glIsBuffer;

extern PFNGLISENABLEDPROC glad_glIsEnabled;

extern PFNGLISENABLEDIPROC glad_glIsEnabledi;

extern PFNGLISFRAMEBUFFERPROC glad_glIsFramebuffer;

extern PFNGLISIMAGEHANDLERESIDENTARBPROC glad_glIsImageHandleResidentARB;

extern PFNGLISLISTPROC glad_glIsList;

extern PFNGLISPROGRAMPROC glad_glIsProgram;

extern PFNGLISPROGRAMPIPELINEPROC glad_glIsProgramPipeline;

extern PFNGLISQUERYPROC glad_glIsQuery;

extern PFNGLISRENDERBUFFERPROC glad_glIsRenderbuffer;

extern PFNGLISSAMPLERPROC glad_glIsSampler;

extern PFNGLISSHADERPROC glad_glIsShader;

extern PFNGLISSYNCPROC glad_glIsSync;

extern PFNGLISTEXTUREPROC glad_glIsTexture;

extern PFNGLISTEXTUREHANDLERESIDENTARBPROC glad_glIsTextureHandleResidentARB;

extern PFNGLISTRANSFORMFEEDBACKPROC glad_glIsTransformFeedback;

extern PFNGLISVERTEXARRAYPROC glad_glIsVertexArray;

extern PFNGLLIGHTMODELFPROC glad_glLightModelf;

extern PFNGLLIGHTMODELFVPROC glad_glLightModelfv;

extern PFNGLLIGHTMODELIPROC glad_glLightModeli;

extern PFNGLLIGHTMODELIVPROC glad_glLightModeliv;

extern PFNGLLIGHTFPROC glad_glLightf;

extern PFNGLLIGHTFVPROC glad_glLightfv;

extern PFNGLLIGHTIPROC glad_glLighti;

extern PFNGLLIGHTIVPROC glad_glLightiv;

extern PFNGLLINESTIPPLEPROC glad_glLineStipple;

extern PFNGLLINEWIDTHPROC glad_glLineWidth;

extern PFNGLLINKPROGRAMPROC glad_glLinkProgram;

extern PFNGLLISTBASEPROC glad_glListBase;

extern PFNGLLOADIDENTITYPROC glad_glLoadIdentity;

extern PFNGLLOADMATRIXDPROC glad_glLoadMatrixd;

extern PFNGLLOADMATRIXFPROC glad_glLoadMatrixf;

extern PFNGLLOADNAMEPROC glad_glLoadName;

extern PFNGLLOADTRANSPOSEMATRIXDPROC glad_glLoadTransposeMatrixd;

extern PFNGLLOADTRANSPOSEMATRIXFPROC glad_glLoadTransposeMatrixf;

extern PFNGLLOGICOPPROC glad_glLogicOp;

extern PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC glad_glMakeImageHandleNonResidentARB;

extern PFNGLMAKEIMAGEHANDLERESIDENTARBPROC glad_glMakeImageHandleResidentARB;

extern PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC glad_glMakeTextureHandleNonResidentARB;

extern PFNGLMAKETEXTUREHANDLERESIDENTARBPROC glad_glMakeTextureHandleResidentARB;

extern PFNGLMAP1DPROC glad_glMap1d;

extern PFNGLMAP1FPROC glad_glMap1f;

extern PFNGLMAP2DPROC glad_glMap2d;

extern PFNGLMAP2FPROC glad_glMap2f;

extern PFNGLMAPBUFFERPROC glad_glMapBuffer;

extern PFNGLMAPBUFFERRANGEPROC glad_glMapBufferRange;

extern PFNGLMAPGRID1DPROC glad_glMapGrid1d;

extern PFNGLMAPGRID1FPROC glad_glMapGrid1f;

extern PFNGLMAPGRID2DPROC glad_glMapGrid2d;

extern PFNGLMAPGRID2FPROC glad_glMapGrid2f;

extern PFNGLMAPNAMEDBUFFERPROC glad_glMapNamedBuffer;

extern PFNGLMAPNAMEDBUFFERRANGEPROC glad_glMapNamedBufferRange;

extern PFNGLMATERIALFPROC glad_glMaterialf;

extern PFNGLMATERIALFVPROC glad_glMaterialfv;

extern PFNGLMATERIALIPROC glad_glMateriali;

extern PFNGLMATERIALIVPROC glad_glMaterialiv;

extern PFNGLMATRIXMODEPROC glad_glMatrixMode;

extern PFNGLMEMORYBARRIERPROC glad_glMemoryBarrier;

extern PFNGLMEMORYBARRIERBYREGIONPROC glad_glMemoryBarrierByRegion;

extern PFNGLMINSAMPLESHADINGPROC glad_glMinSampleShading;

extern PFNGLMULTMATRIXDPROC glad_glMultMatrixd;

extern PFNGLMULTMATRIXFPROC glad_glMultMatrixf;

extern PFNGLMULTTRANSPOSEMATRIXDPROC glad_glMultTransposeMatrixd;

extern PFNGLMULTTRANSPOSEMATRIXFPROC glad_glMultTransposeMatrixf;

extern PFNGLMULTIDRAWARRAYSPROC glad_glMultiDrawArrays;

extern PFNGLMULTIDRAWARRAYSINDIRECTPROC glad_glMultiDrawArraysIndirect;

extern PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC glad_glMultiDrawArraysIndirectCount;

extern PFNGLMULTIDRAWELEMENTSPROC glad_glMultiDrawElements;

extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glad_glMultiDrawElementsBaseVertex;

extern PFNGLMULTIDRAWELEMENTSINDIRECTPROC glad_glMultiDrawElementsIndirect;

extern PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC glad_glMultiDrawElementsIndirectCount;

extern PFNGLMULTITEXCOORD1DPROC glad_glMultiTexCoord1d;

extern PFNGLMULTITEXCOORD1DVPROC glad_glMultiTexCoord1dv;

extern PFNGLMULTITEXCOORD1FPROC glad_glMultiTexCoord1f;

extern PFNGLMULTITEXCOORD1FVPROC glad_glMultiTexCoord1fv;

extern PFNGLMULTITEXCOORD1IPROC glad_glMultiTexCoord1i;

extern PFNGLMULTITEXCOORD1IVPROC glad_glMultiTexCoord1iv;

extern PFNGLMULTITEXCOORD1SPROC glad_glMultiTexCoord1s;

extern PFNGLMULTITEXCOORD1SVPROC glad_glMultiTexCoord1sv;

extern PFNGLMULTITEXCOORD2DPROC glad_glMultiTexCoord2d;

extern PFNGLMULTITEXCOORD2DVPROC glad_glMultiTexCoord2dv;

extern PFNGLMULTITEXCOORD2FPROC glad_glMultiTexCoord2f;

extern PFNGLMULTITEXCOORD2FVPROC glad_glMultiTexCoord2fv;

extern PFNGLMULTITEXCOORD2IPROC glad_glMultiTexCoord2i;

extern PFNGLMULTITEXCOORD2IVPROC glad_glMultiTexCoord2iv;

extern PFNGLMULTITEXCOORD2SPROC glad_glMultiTexCoord2s;

extern PFNGLMULTITEXCOORD2SVPROC glad_glMultiTexCoord2sv;

extern PFNGLMULTITEXCOORD3DPROC glad_glMultiTexCoord3d;

extern PFNGLMULTITEXCOORD3DVPROC glad_glMultiTexCoord3dv;

extern PFNGLMULTITEXCOORD3FPROC glad_glMultiTexCoord3f;

extern PFNGLMULTITEXCOORD3FVPROC glad_glMultiTexCoord3fv;

extern PFNGLMULTITEXCOORD3IPROC glad_glMultiTexCoord3i;

extern PFNGLMULTITEXCOORD3IVPROC glad_glMultiTexCoord3iv;

extern PFNGLMULTITEXCOORD3SPROC glad_glMultiTexCoord3s;

extern PFNGLMULTITEXCOORD3SVPROC glad_glMultiTexCoord3sv;

extern PFNGLMULTITEXCOORD4DPROC glad_glMultiTexCoord4d;

extern PFNGLMULTITEXCOORD4DVPROC glad_glMultiTexCoord4dv;

extern PFNGLMULTITEXCOORD4FPROC glad_glMultiTexCoord4f;

extern PFNGLMULTITEXCOORD4FVPROC glad_glMultiTexCoord4fv;

extern PFNGLMULTITEXCOORD4IPROC glad_glMultiTexCoord4i;

extern PFNGLMULTITEXCOORD4IVPROC glad_glMultiTexCoord4iv;

extern PFNGLMULTITEXCOORD4SPROC glad_glMultiTexCoord4s;

extern PFNGLMULTITEXCOORD4SVPROC glad_glMultiTexCoord4sv;

extern PFNGLMULTITEXCOORDP1UIPROC glad_glMultiTexCoordP1ui;

extern PFNGLMULTITEXCOORDP1UIVPROC glad_glMultiTexCoordP1uiv;

extern PFNGLMULTITEXCOORDP2UIPROC glad_glMultiTexCoordP2ui;

extern PFNGLMULTITEXCOORDP2UIVPROC glad_glMultiTexCoordP2uiv;

extern PFNGLMULTITEXCOORDP3UIPROC glad_glMultiTexCoordP3ui;

extern PFNGLMULTITEXCOORDP3UIVPROC glad_glMultiTexCoordP3uiv;

extern PFNGLMULTITEXCOORDP4UIPROC glad_glMultiTexCoordP4ui;

extern PFNGLMULTITEXCOORDP4UIVPROC glad_glMultiTexCoordP4uiv;

extern PFNGLNAMEDBUFFERDATAPROC glad_glNamedBufferData;

extern PFNGLNAMEDBUFFERSTORAGEPROC glad_glNamedBufferStorage;

extern PFNGLNAMEDBUFFERSUBDATAPROC glad_glNamedBufferSubData;

extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC glad_glNamedFramebufferDrawBuffer;

extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC glad_glNamedFramebufferDrawBuffers;

extern PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC glad_glNamedFramebufferParameteri;

extern PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC glad_glNamedFramebufferReadBuffer;

extern PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC glad_glNamedFramebufferRenderbuffer;

extern PFNGLNAMEDFRAMEBUFFERTEXTUREPROC glad_glNamedFramebufferTexture;

extern PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC glad_glNamedFramebufferTextureLayer;

extern PFNGLNAMEDRENDERBUFFERSTORAGEPROC glad_glNamedRenderbufferStorage;

extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glNamedRenderbufferStorageMultisample;

extern PFNGLNEWLISTPROC glad_glNewList;

extern PFNGLNORMAL3BPROC glad_glNormal3b;

extern PFNGLNORMAL3BVPROC glad_glNormal3bv;

extern PFNGLNORMAL3DPROC glad_glNormal3d;

extern PFNGLNORMAL3DVPROC glad_glNormal3dv;

extern PFNGLNORMAL3FPROC glad_glNormal3f;

extern PFNGLNORMAL3FVPROC glad_glNormal3fv;

extern PFNGLNORMAL3IPROC glad_glNormal3i;

extern PFNGLNORMAL3IVPROC glad_glNormal3iv;

extern PFNGLNORMAL3SPROC glad_glNormal3s;

extern PFNGLNORMAL3SVPROC glad_glNormal3sv;

extern PFNGLNORMALP3UIPROC glad_glNormalP3ui;

extern PFNGLNORMALP3UIVPROC glad_glNormalP3uiv;

extern PFNGLNORMALPOINTERPROC glad_glNormalPointer;

extern PFNGLOBJECTLABELPROC glad_glObjectLabel;

extern PFNGLOBJECTPTRLABELPROC glad_glObjectPtrLabel;

extern PFNGLORTHOPROC glad_glOrtho;

extern PFNGLPASSTHROUGHPROC glad_glPassThrough;

extern PFNGLPATCHPARAMETERFVPROC glad_glPatchParameterfv;

extern PFNGLPATCHPARAMETERIPROC glad_glPatchParameteri;

extern PFNGLPAUSETRANSFORMFEEDBACKPROC glad_glPauseTransformFeedback;

extern PFNGLPIXELMAPFVPROC glad_glPixelMapfv;

extern PFNGLPIXELMAPUIVPROC glad_glPixelMapuiv;

extern PFNGLPIXELMAPUSVPROC glad_glPixelMapusv;

extern PFNGLPIXELSTOREFPROC glad_glPixelStoref;

extern PFNGLPIXELSTOREIPROC glad_glPixelStorei;

extern PFNGLPIXELTRANSFERFPROC glad_glPixelTransferf;

extern PFNGLPIXELTRANSFERIPROC glad_glPixelTransferi;

extern PFNGLPIXELZOOMPROC glad_glPixelZoom;

extern PFNGLPOINTPARAMETERFPROC glad_glPointParameterf;

extern PFNGLPOINTPARAMETERFVPROC glad_glPointParameterfv;

extern PFNGLPOINTPARAMETERIPROC glad_glPointParameteri;

extern PFNGLPOINTPARAMETERIVPROC glad_glPointParameteriv;

extern PFNGLPOINTSIZEPROC glad_glPointSize;

extern PFNGLPOLYGONMODEPROC glad_glPolygonMode;

extern PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset;

extern PFNGLPOLYGONOFFSETCLAMPPROC glad_glPolygonOffsetClamp;

extern PFNGLPOLYGONSTIPPLEPROC glad_glPolygonStipple;

extern PFNGLPOPATTRIBPROC glad_glPopAttrib;

extern PFNGLPOPCLIENTATTRIBPROC glad_glPopClientAttrib;

extern PFNGLPOPDEBUGGROUPPROC glad_glPopDebugGroup;

extern PFNGLPOPMATRIXPROC glad_glPopMatrix;

extern PFNGLPOPNAMEPROC glad_glPopName;

extern PFNGLPRIMITIVERESTARTINDEXPROC glad_glPrimitiveRestartIndex;

extern PFNGLPRIORITIZETEXTURESPROC glad_glPrioritizeTextures;

extern PFNGLPROGRAMBINARYPROC glad_glProgramBinary;

extern PFNGLPROGRAMPARAMETERIPROC glad_glProgramParameteri;

extern PFNGLPROGRAMUNIFORM1DPROC glad_glProgramUniform1d;

extern PFNGLPROGRAMUNIFORM1DVPROC glad_glProgramUniform1dv;

extern PFNGLPROGRAMUNIFORM1FPROC glad_glProgramUniform1f;

extern PFNGLPROGRAMUNIFORM1FVPROC glad_glProgramUniform1fv;

extern PFNGLPROGRAMUNIFORM1IPROC glad_glProgramUniform1i;

extern PFNGLPROGRAMUNIFORM1IVPROC glad_glProgramUniform1iv;

extern PFNGLPROGRAMUNIFORM1UIPROC glad_glProgramUniform1ui;

extern PFNGLPROGRAMUNIFORM1UIVPROC glad_glProgramUniform1uiv;

extern PFNGLPROGRAMUNIFORM2DPROC glad_glProgramUniform2d;

extern PFNGLPROGRAMUNIFORM2DVPROC glad_glProgramUniform2dv;

extern PFNGLPROGRAMUNIFORM2FPROC glad_glProgramUniform2f;

extern PFNGLPROGRAMUNIFORM2FVPROC glad_glProgramUniform2fv;

extern PFNGLPROGRAMUNIFORM2IPROC glad_glProgramUniform2i;

extern PFNGLPROGRAMUNIFORM2IVPROC glad_glProgramUniform2iv;

extern PFNGLPROGRAMUNIFORM2UIPROC glad_glProgramUniform2ui;

extern PFNGLPROGRAMUNIFORM2UIVPROC glad_glProgramUniform2uiv;

extern PFNGLPROGRAMUNIFORM3DPROC glad_glProgramUniform3d;

extern PFNGLPROGRAMUNIFORM3DVPROC glad_glProgramUniform3dv;

extern PFNGLPROGRAMUNIFORM3FPROC glad_glProgramUniform3f;

extern PFNGLPROGRAMUNIFORM3FVPROC glad_glProgramUniform3fv;

extern PFNGLPROGRAMUNIFORM3IPROC glad_glProgramUniform3i;

extern PFNGLPROGRAMUNIFORM3IVPROC glad_glProgramUniform3iv;

extern PFNGLPROGRAMUNIFORM3UIPROC glad_glProgramUniform3ui;

extern PFNGLPROGRAMUNIFORM3UIVPROC glad_glProgramUniform3uiv;

extern PFNGLPROGRAMUNIFORM4DPROC glad_glProgramUniform4d;

extern PFNGLPROGRAMUNIFORM4DVPROC glad_glProgramUniform4dv;

extern PFNGLPROGRAMUNIFORM4FPROC glad_glProgramUniform4f;

extern PFNGLPROGRAMUNIFORM4FVPROC glad_glProgramUniform4fv;

extern PFNGLPROGRAMUNIFORM4IPROC glad_glProgramUniform4i;

extern PFNGLPROGRAMUNIFORM4IVPROC glad_glProgramUniform4iv;

extern PFNGLPROGRAMUNIFORM4UIPROC glad_glProgramUniform4ui;

extern PFNGLPROGRAMUNIFORM4UIVPROC glad_glProgramUniform4uiv;

extern PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC glad_glProgramUniformHandleui64ARB;

extern PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC glad_glProgramUniformHandleui64vARB;

extern PFNGLPROGRAMUNIFORMMATRIX2DVPROC glad_glProgramUniformMatrix2dv;

extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC glad_glProgramUniformMatrix2fv;

extern PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glad_glProgramUniformMatrix2x3dv;

extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glad_glProgramUniformMatrix2x3fv;

extern PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glad_glProgramUniformMatrix2x4dv;

extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glad_glProgramUniformMatrix2x4fv;

extern PFNGLPROGRAMUNIFORMMATRIX3DVPROC glad_glProgramUniformMatrix3dv;

extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC glad_glProgramUniformMatrix3fv;

extern PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glad_glProgramUniformMatrix3x2dv;

extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glad_glProgramUniformMatrix3x2fv;

extern PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glad_glProgramUniformMatrix3x4dv;

extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glad_glProgramUniformMatrix3x4fv;

extern PFNGLPROGRAMUNIFORMMATRIX4DVPROC glad_glProgramUniformMatrix4dv;

extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC glad_glProgramUniformMatrix4fv;

extern PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glad_glProgramUniformMatrix4x2dv;

extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glad_glProgramUniformMatrix4x2fv;

extern PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glad_glProgramUniformMatrix4x3dv;

extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glad_glProgramUniformMatrix4x3fv;

extern PFNGLPROVOKINGVERTEXPROC glad_glProvokingVertex;

extern PFNGLPUSHATTRIBPROC glad_glPushAttrib;

extern PFNGLPUSHCLIENTATTRIBPROC glad_glPushClientAttrib;

extern PFNGLPUSHDEBUGGROUPPROC glad_glPushDebugGroup;

extern PFNGLPUSHMATRIXPROC glad_glPushMatrix;

extern PFNGLPUSHNAMEPROC glad_glPushName;

extern PFNGLQUERYCOUNTERPROC glad_glQueryCounter;

extern PFNGLRASTERPOS2DPROC glad_glRasterPos2d;

extern PFNGLRASTERPOS2DVPROC glad_glRasterPos2dv;

extern PFNGLRASTERPOS2FPROC glad_glRasterPos2f;

extern PFNGLRASTERPOS2FVPROC glad_glRasterPos2fv;

extern PFNGLRASTERPOS2IPROC glad_glRasterPos2i;

extern PFNGLRASTERPOS2IVPROC glad_glRasterPos2iv;

extern PFNGLRASTERPOS2SPROC glad_glRasterPos2s;

extern PFNGLRASTERPOS2SVPROC glad_glRasterPos2sv;

extern PFNGLRASTERPOS3DPROC glad_glRasterPos3d;

extern PFNGLRASTERPOS3DVPROC glad_glRasterPos3dv;

extern PFNGLRASTERPOS3FPROC glad_glRasterPos3f;

extern PFNGLRASTERPOS3FVPROC glad_glRasterPos3fv;

extern PFNGLRASTERPOS3IPROC glad_glRasterPos3i;

extern PFNGLRASTERPOS3IVPROC glad_glRasterPos3iv;

extern PFNGLRASTERPOS3SPROC glad_glRasterPos3s;

extern PFNGLRASTERPOS3SVPROC glad_glRasterPos3sv;

extern PFNGLRASTERPOS4DPROC glad_glRasterPos4d;

extern PFNGLRASTERPOS4DVPROC glad_glRasterPos4dv;

extern PFNGLRASTERPOS4FPROC glad_glRasterPos4f;

extern PFNGLRASTERPOS4FVPROC glad_glRasterPos4fv;

extern PFNGLRASTERPOS4IPROC glad_glRasterPos4i;

extern PFNGLRASTERPOS4IVPROC glad_glRasterPos4iv;

extern PFNGLRASTERPOS4SPROC glad_glRasterPos4s;

extern PFNGLRASTERPOS4SVPROC glad_glRasterPos4sv;

extern PFNGLREADBUFFERPROC glad_glReadBuffer;

extern PFNGLREADPIXELSPROC glad_glReadPixels;

extern PFNGLREADNPIXELSPROC glad_glReadnPixels;

extern PFNGLRECTDPROC glad_glRectd;

extern PFNGLRECTDVPROC glad_glRectdv;

extern PFNGLRECTFPROC glad_glRectf;

extern PFNGLRECTFVPROC glad_glRectfv;

extern PFNGLRECTIPROC glad_glRecti;

extern PFNGLRECTIVPROC glad_glRectiv;

extern PFNGLRECTSPROC glad_glRects;

extern PFNGLRECTSVPROC glad_glRectsv;

extern PFNGLRELEASESHADERCOMPILERPROC glad_glReleaseShaderCompiler;

extern PFNGLRENDERMODEPROC glad_glRenderMode;

extern PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage;

extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glRenderbufferStorageMultisample;

extern PFNGLRESUMETRANSFORMFEEDBACKPROC glad_glResumeTransformFeedback;

extern PFNGLROTATEDPROC glad_glRotated;

extern PFNGLROTATEFPROC glad_glRotatef;

extern PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage;

extern PFNGLSAMPLEMASKIPROC glad_glSampleMaski;

extern PFNGLSAMPLERPARAMETERIIVPROC glad_glSamplerParameterIiv;

extern PFNGLSAMPLERPARAMETERIUIVPROC glad_glSamplerParameterIuiv;

extern PFNGLSAMPLERPARAMETERFPROC glad_glSamplerParameterf;

extern PFNGLSAMPLERPARAMETERFVPROC glad_glSamplerParameterfv;

extern PFNGLSAMPLERPARAMETERIPROC glad_glSamplerParameteri;

extern PFNGLSAMPLERPARAMETERIVPROC glad_glSamplerParameteriv;

extern PFNGLSCALEDPROC glad_glScaled;

extern PFNGLSCALEFPROC glad_glScalef;

extern PFNGLSCISSORPROC glad_glScissor;

extern PFNGLSCISSORARRAYVPROC glad_glScissorArrayv;

extern PFNGLSCISSORINDEXEDPROC glad_glScissorIndexed;

extern PFNGLSCISSORINDEXEDVPROC glad_glScissorIndexedv;

extern PFNGLSECONDARYCOLOR3BPROC glad_glSecondaryColor3b;

extern PFNGLSECONDARYCOLOR3BVPROC glad_glSecondaryColor3bv;

extern PFNGLSECONDARYCOLOR3DPROC glad_glSecondaryColor3d;

extern PFNGLSECONDARYCOLOR3DVPROC glad_glSecondaryColor3dv;

extern PFNGLSECONDARYCOLOR3FPROC glad_glSecondaryColor3f;

extern PFNGLSECONDARYCOLOR3FVPROC glad_glSecondaryColor3fv;

extern PFNGLSECONDARYCOLOR3IPROC glad_glSecondaryColor3i;

extern PFNGLSECONDARYCOLOR3IVPROC glad_glSecondaryColor3iv;

extern PFNGLSECONDARYCOLOR3SPROC glad_glSecondaryColor3s;

extern PFNGLSECONDARYCOLOR3SVPROC glad_glSecondaryColor3sv;

extern PFNGLSECONDARYCOLOR3UBPROC glad_glSecondaryColor3ub;

extern PFNGLSECONDARYCOLOR3UBVPROC glad_glSecondaryColor3ubv;

extern PFNGLSECONDARYCOLOR3UIPROC glad_glSecondaryColor3ui;

extern PFNGLSECONDARYCOLOR3UIVPROC glad_glSecondaryColor3uiv;

extern PFNGLSECONDARYCOLOR3USPROC glad_glSecondaryColor3us;

extern PFNGLSECONDARYCOLOR3USVPROC glad_glSecondaryColor3usv;

extern PFNGLSECONDARYCOLORP3UIPROC glad_glSecondaryColorP3ui;

extern PFNGLSECONDARYCOLORP3UIVPROC glad_glSecondaryColorP3uiv;

extern PFNGLSECONDARYCOLORPOINTERPROC glad_glSecondaryColorPointer;

extern PFNGLSELECTBUFFERPROC glad_glSelectBuffer;

extern PFNGLSHADEMODELPROC glad_glShadeModel;

extern PFNGLSHADERBINARYPROC glad_glShaderBinary;

extern PFNGLSHADERSOURCEPROC glad_glShaderSource;

extern PFNGLSHADERSTORAGEBLOCKBINDINGPROC glad_glShaderStorageBlockBinding;

extern PFNGLSPECIALIZESHADERPROC glad_glSpecializeShader;

extern PFNGLSTENCILFUNCPROC glad_glStencilFunc;

extern PFNGLSTENCILFUNCSEPARATEPROC glad_glStencilFuncSeparate;

extern PFNGLSTENCILMASKPROC glad_glStencilMask;

extern PFNGLSTENCILMASKSEPARATEPROC glad_glStencilMaskSeparate;

extern PFNGLSTENCILOPPROC glad_glStencilOp;

extern PFNGLSTENCILOPSEPARATEPROC glad_glStencilOpSeparate;

extern PFNGLTEXBUFFERPROC glad_glTexBuffer;

extern PFNGLTEXBUFFERRANGEPROC glad_glTexBufferRange;

extern PFNGLTEXCOORD1DPROC glad_glTexCoord1d;

extern PFNGLTEXCOORD1DVPROC glad_glTexCoord1dv;

extern PFNGLTEXCOORD1FPROC glad_glTexCoord1f;

extern PFNGLTEXCOORD1FVPROC glad_glTexCoord1fv;

extern PFNGLTEXCOORD1IPROC glad_glTexCoord1i;

extern PFNGLTEXCOORD1IVPROC glad_glTexCoord1iv;

extern PFNGLTEXCOORD1SPROC glad_glTexCoord1s;

extern PFNGLTEXCOORD1SVPROC glad_glTexCoord1sv;

extern PFNGLTEXCOORD2DPROC glad_glTexCoord2d;

extern PFNGLTEXCOORD2DVPROC glad_glTexCoord2dv;

extern PFNGLTEXCOORD2FPROC glad_glTexCoord2f;

extern PFNGLTEXCOORD2FVPROC glad_glTexCoord2fv;

extern PFNGLTEXCOORD2IPROC glad_glTexCoord2i;

extern PFNGLTEXCOORD2IVPROC glad_glTexCoord2iv;

extern PFNGLTEXCOORD2SPROC glad_glTexCoord2s;

extern PFNGLTEXCOORD2SVPROC glad_glTexCoord2sv;

extern PFNGLTEXCOORD3DPROC glad_glTexCoord3d;

extern PFNGLTEXCOORD3DVPROC glad_glTexCoord3dv;

extern PFNGLTEXCOORD3FPROC glad_glTexCoord3f;

extern PFNGLTEXCOORD3FVPROC glad_glTexCoord3fv;

extern PFNGLTEXCOORD3IPROC glad_glTexCoord3i;

extern PFNGLTEXCOORD3IVPROC glad_glTexCoord3iv;

extern PFNGLTEXCOORD3SPROC glad_glTexCoord3s;

extern PFNGLTEXCOORD3SVPROC glad_glTexCoord3sv;

extern PFNGLTEXCOORD4DPROC glad_glTexCoord4d;

extern PFNGLTEXCOORD4DVPROC glad_glTexCoord4dv;

extern PFNGLTEXCOORD4FPROC glad_glTexCoord4f;

extern PFNGLTEXCOORD4FVPROC glad_glTexCoord4fv;

extern PFNGLTEXCOORD4IPROC glad_glTexCoord4i;

extern PFNGLTEXCOORD4IVPROC glad_glTexCoord4iv;

extern PFNGLTEXCOORD4SPROC glad_glTexCoord4s;

extern PFNGLTEXCOORD4SVPROC glad_glTexCoord4sv;

extern PFNGLTEXCOORDP1UIPROC glad_glTexCoordP1ui;

extern PFNGLTEXCOORDP1UIVPROC glad_glTexCoordP1uiv;

extern PFNGLTEXCOORDP2UIPROC glad_glTexCoordP2ui;

extern PFNGLTEXCOORDP2UIVPROC glad_glTexCoordP2uiv;

extern PFNGLTEXCOORDP3UIPROC glad_glTexCoordP3ui;

extern PFNGLTEXCOORDP3UIVPROC glad_glTexCoordP3uiv;

extern PFNGLTEXCOORDP4UIPROC glad_glTexCoordP4ui;

extern PFNGLTEXCOORDP4UIVPROC glad_glTexCoordP4uiv;

extern PFNGLTEXCOORDPOINTERPROC glad_glTexCoordPointer;

extern PFNGLTEXENVFPROC glad_glTexEnvf;

extern PFNGLTEXENVFVPROC glad_glTexEnvfv;

extern PFNGLTEXENVIPROC glad_glTexEnvi;

extern PFNGLTEXENVIVPROC glad_glTexEnviv;

extern PFNGLTEXGENDPROC glad_glTexGend;

extern PFNGLTEXGENDVPROC glad_glTexGendv;

extern PFNGLTEXGENFPROC glad_glTexGenf;

extern PFNGLTEXGENFVPROC glad_glTexGenfv;

extern PFNGLTEXGENIPROC glad_glTexGeni;

extern PFNGLTEXGENIVPROC glad_glTexGeniv;

extern PFNGLTEXIMAGE1DPROC glad_glTexImage1D;

extern PFNGLTEXIMAGE2DPROC glad_glTexImage2D;

extern PFNGLTEXIMAGE2DMULTISAMPLEPROC glad_glTexImage2DMultisample;

extern PFNGLTEXIMAGE3DPROC glad_glTexImage3D;

extern PFNGLTEXIMAGE3DMULTISAMPLEPROC glad_glTexImage3DMultisample;

extern PFNGLTEXPARAMETERIIVPROC glad_glTexParameterIiv;

extern PFNGLTEXPARAMETERIUIVPROC glad_glTexParameterIuiv;

extern PFNGLTEXPARAMETERFPROC glad_glTexParameterf;

extern PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv;

extern PFNGLTEXPARAMETERIPROC glad_glTexParameteri;

extern PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv;

extern PFNGLTEXSTORAGE1DPROC glad_glTexStorage1D;

extern PFNGLTEXSTORAGE2DPROC glad_glTexStorage2D;

extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC glad_glTexStorage2DMultisample;

extern PFNGLTEXSTORAGE3DPROC glad_glTexStorage3D;

extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC glad_glTexStorage3DMultisample;

extern PFNGLTEXSUBIMAGE1DPROC glad_glTexSubImage1D;

extern PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D;

extern PFNGLTEXSUBIMAGE3DPROC glad_glTexSubImage3D;

extern PFNGLTEXTUREBARRIERPROC glad_glTextureBarrier;

extern PFNGLTEXTUREBUFFERPROC glad_glTextureBuffer;

extern PFNGLTEXTUREBUFFERRANGEPROC glad_glTextureBufferRange;

extern PFNGLTEXTUREPARAMETERIIVPROC glad_glTextureParameterIiv;

extern PFNGLTEXTUREPARAMETERIUIVPROC glad_glTextureParameterIuiv;

extern PFNGLTEXTUREPARAMETERFPROC glad_glTextureParameterf;

extern PFNGLTEXTUREPARAMETERFVPROC glad_glTextureParameterfv;

extern PFNGLTEXTUREPARAMETERIPROC glad_glTextureParameteri;

extern PFNGLTEXTUREPARAMETERIVPROC glad_glTextureParameteriv;

extern PFNGLTEXTURESTORAGE1DPROC glad_glTextureStorage1D;

extern PFNGLTEXTURESTORAGE2DPROC glad_glTextureStorage2D;

extern PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC glad_glTextureStorage2DMultisample;

extern PFNGLTEXTURESTORAGE3DPROC glad_glTextureStorage3D;

extern PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC glad_glTextureStorage3DMultisample;

extern PFNGLTEXTURESUBIMAGE1DPROC glad_glTextureSubImage1D;

extern PFNGLTEXTURESUBIMAGE2DPROC glad_glTextureSubImage2D;

extern PFNGLTEXTURESUBIMAGE3DPROC glad_glTextureSubImage3D;

extern PFNGLTEXTUREVIEWPROC glad_glTextureView;

extern PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC glad_glTransformFeedbackBufferBase;

extern PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC glad_glTransformFeedbackBufferRange;

extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC glad_glTransformFeedbackVaryings;

extern PFNGLTRANSLATEDPROC glad_glTranslated;

extern PFNGLTRANSLATEFPROC glad_glTranslatef;

extern PFNGLUNIFORM1DPROC glad_glUniform1d;

extern PFNGLUNIFORM1DVPROC glad_glUniform1dv;

extern PFNGLUNIFORM1FPROC glad_glUniform1f;

extern PFNGLUNIFORM1FVPROC glad_glUniform1fv;

extern PFNGLUNIFORM1IPROC glad_glUniform1i;

extern PFNGLUNIFORM1IVPROC glad_glUniform1iv;

extern PFNGLUNIFORM1UIPROC glad_glUniform1ui;

extern PFNGLUNIFORM1UIVPROC glad_glUniform1uiv;

extern PFNGLUNIFORM2DPROC glad_glUniform2d;

extern PFNGLUNIFORM2DVPROC glad_glUniform2dv;

extern PFNGLUNIFORM2FPROC glad_glUniform2f;

extern PFNGLUNIFORM2FVPROC glad_glUniform2fv;

extern PFNGLUNIFORM2IPROC glad_glUniform2i;

extern PFNGLUNIFORM2IVPROC glad_glUniform2iv;

extern PFNGLUNIFORM2UIPROC glad_glUniform2ui;

extern PFNGLUNIFORM2UIVPROC glad_glUniform2uiv;

extern PFNGLUNIFORM3DPROC glad_glUniform3d;

extern PFNGLUNIFORM3DVPROC glad_glUniform3dv;

extern PFNGLUNIFORM3FPROC glad_glUniform3f;

extern PFNGLUNIFORM3FVPROC glad_glUniform3fv;

extern PFNGLUNIFORM3IPROC glad_glUniform3i;

extern PFNGLUNIFORM3IVPROC glad_glUniform3iv;

extern PFNGLUNIFORM3UIPROC glad_glUniform3ui;

extern PFNGLUNIFORM3UIVPROC glad_glUniform3uiv;

extern PFNGLUNIFORM4DPROC glad_glUniform4d;

extern PFNGLUNIFORM4DVPROC glad_glUniform4dv;

extern PFNGLUNIFORM4FPROC glad_glUniform4f;

extern PFNGLUNIFORM4FVPROC glad_glUniform4fv;

extern PFNGLUNIFORM4IPROC glad_glUniform4i;

extern PFNGLUNIFORM4IVPROC glad_glUniform4iv;

extern PFNGLUNIFORM4UIPROC glad_glUniform4ui;

extern PFNGLUNIFORM4UIVPROC glad_glUniform4uiv;

extern PFNGLUNIFORMBLOCKBINDINGPROC glad_glUniformBlockBinding;

extern PFNGLUNIFORMHANDLEUI64ARBPROC glad_glUniformHandleui64ARB;

extern PFNGLUNIFORMHANDLEUI64VARBPROC glad_glUniformHandleui64vARB;

extern PFNGLUNIFORMMATRIX2DVPROC glad_glUniformMatrix2dv;

extern PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv;

extern PFNGLUNIFORMMATRIX2X3DVPROC glad_glUniformMatrix2x3dv;

extern PFNGLUNIFORMMATRIX2X3FVPROC glad_glUniformMatrix2x3fv;

extern PFNGLUNIFORMMATRIX2X4DVPROC glad_glUniformMatrix2x4dv;

extern PFNGLUNIFORMMATRIX2X4FVPROC glad_glUniformMatrix2x4fv;

extern PFNGLUNIFORMMATRIX3DVPROC glad_glUniformMatrix3dv;

extern PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv;

extern PFNGLUNIFORMMATRIX3X2DVPROC glad_glUniformMatrix3x2dv;

extern PFNGLUNIFORMMATRIX3X2FVPROC glad_glUniformMatrix3x2fv;

extern PFNGLUNIFORMMATRIX3X4DVPROC glad_glUniformMatrix3x4dv;

extern PFNGLUNIFORMMATRIX3X4FVPROC glad_glUniformMatrix3x4fv;

extern PFNGLUNIFORMMATRIX4DVPROC glad_glUniformMatrix4dv;

extern PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;

extern PFNGLUNIFORMMATRIX4X2DVPROC glad_glUniformMatrix4x2dv;

extern PFNGLUNIFORMMATRIX4X2FVPROC glad_glUniformMatrix4x2fv;

extern PFNGLUNIFORMMATRIX4X3DVPROC glad_glUniformMatrix4x3dv;

extern PFNGLUNIFORMMATRIX4X3FVPROC glad_glUniformMatrix4x3fv;

extern PFNGLUNIFORMSUBROUTINESUIVPROC glad_glUniformSubroutinesuiv;

extern PFNGLUNMAPBUFFERPROC glad_glUnmapBuffer;

extern PFNGLUNMAPNAMEDBUFFERPROC glad_glUnmapNamedBuffer;

extern PFNGLUSEPROGRAMPROC glad_glUseProgram;

extern PFNGLUSEPROGRAMSTAGESPROC glad_glUseProgramStages;

extern PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram;

extern PFNGLVALIDATEPROGRAMPIPELINEPROC glad_glValidateProgramPipeline;

extern PFNGLVERTEX2DPROC glad_glVertex2d;

extern PFNGLVERTEX2DVPROC glad_glVertex2dv;

extern PFNGLVERTEX2FPROC glad_glVertex2f;

extern PFNGLVERTEX2FVPROC glad_glVertex2fv;

extern PFNGLVERTEX2IPROC glad_glVertex2i;

extern PFNGLVERTEX2IVPROC glad_glVertex2iv;

extern PFNGLVERTEX2SPROC glad_glVertex2s;

extern PFNGLVERTEX2SVPROC glad_glVertex2sv;

extern PFNGLVERTEX3DPROC glad_glVertex3d;

extern PFNGLVERTEX3DVPROC glad_glVertex3dv;

extern PFNGLVERTEX3FPROC glad_glVertex3f;

extern PFNGLVERTEX3FVPROC glad_glVertex3fv;

extern PFNGLVERTEX3IPROC glad_glVertex3i;

extern PFNGLVERTEX3IVPROC glad_glVertex3iv;

extern PFNGLVERTEX3SPROC glad_glVertex3s;

extern PFNGLVERTEX3SVPROC glad_glVertex3sv;

extern PFNGLVERTEX4DPROC glad_glVertex4d;

extern PFNGLVERTEX4DVPROC glad_glVertex4dv;

extern PFNGLVERTEX4FPROC glad_glVertex4f;

extern PFNGLVERTEX4FVPROC glad_glVertex4fv;

extern PFNGLVERTEX4IPROC glad_glVertex4i;

extern PFNGLVERTEX4IVPROC glad_glVertex4iv;

extern PFNGLVERTEX4SPROC glad_glVertex4s;

extern PFNGLVERTEX4SVPROC glad_glVertex4sv;

extern PFNGLVERTEXARRAYATTRIBBINDINGPROC glad_glVertexArrayAttribBinding;

extern PFNGLVERTEXARRAYATTRIBFORMATPROC glad_glVertexArrayAttribFormat;

extern PFNGLVERTEXARRAYATTRIBIFORMATPROC glad_glVertexArrayAttribIFormat;

extern PFNGLVERTEXARRAYATTRIBLFORMATPROC glad_glVertexArrayAttribLFormat;

extern PFNGLVERTEXARRAYBINDINGDIVISORPROC glad_glVertexArrayBindingDivisor;

extern PFNGLVERTEXARRAYELEMENTBUFFERPROC glad_glVertexArrayElementBuffer;

extern PFNGLVERTEXARRAYVERTEXBUFFERPROC glad_glVertexArrayVertexBuffer;

extern PFNGLVERTEXARRAYVERTEXBUFFERSPROC glad_glVertexArrayVertexBuffers;

extern PFNGLVERTEXATTRIB1DPROC glad_glVertexAttrib1d;

extern PFNGLVERTEXATTRIB1DVPROC glad_glVertexAttrib1dv;

extern PFNGLVERTEXATTRIB1FPROC glad_glVertexAttrib1f;

extern PFNGLVERTEXATTRIB1FVPROC glad_glVertexAttrib1fv;

extern PFNGLVERTEXATTRIB1SPROC glad_glVertexAttrib1s;

extern PFNGLVERTEXATTRIB1SVPROC glad_glVertexAttrib1sv;

extern PFNGLVERTEXATTRIB2DPROC glad_glVertexAttrib2d;

extern PFNGLVERTEXATTRIB2DVPROC glad_glVertexAttrib2dv;

extern PFNGLVERTEXATTRIB2FPROC glad_glVertexAttrib2f;

extern PFNGLVERTEXATTRIB2FVPROC glad_glVertexAttrib2fv;

extern PFNGLVERTEXATTRIB2SPROC glad_glVertexAttrib2s;

extern PFNGLVERTEXATTRIB2SVPROC glad_glVertexAttrib2sv;

extern PFNGLVERTEXATTRIB3DPROC glad_glVertexAttrib3d;

extern PFNGLVERTEXATTRIB3DVPROC glad_glVertexAttrib3dv;

extern PFNGLVERTEXATTRIB3FPROC glad_glVertexAttrib3f;

extern PFNGLVERTEXATTRIB3FVPROC glad_glVertexAttrib3fv;

extern PFNGLVERTEXATTRIB3SPROC glad_glVertexAttrib3s;

extern PFNGLVERTEXATTRIB3SVPROC glad_glVertexAttrib3sv;

extern PFNGLVERTEXATTRIB4NBVPROC glad_glVertexAttrib4Nbv;

extern PFNGLVERTEXATTRIB4NIVPROC glad_glVertexAttrib4Niv;

extern PFNGLVERTEXATTRIB4NSVPROC glad_glVertexAttrib4Nsv;

extern PFNGLVERTEXATTRIB4NUBPROC glad_glVertexAttrib4Nub;

extern PFNGLVERTEXATTRIB4NUBVPROC glad_glVertexAttrib4Nubv;

extern PFNGLVERTEXATTRIB4NUIVPROC glad_glVertexAttrib4Nuiv;

extern PFNGLVERTEXATTRIB4NUSVPROC glad_glVertexAttrib4Nusv;

extern PFNGLVERTEXATTRIB4BVPROC glad_glVertexAttrib4bv;

extern PFNGLVERTEXATTRIB4DPROC glad_glVertexAttrib4d;

extern PFNGLVERTEXATTRIB4DVPROC glad_glVertexAttrib4dv;

extern PFNGLVERTEXATTRIB4FPROC glad_glVertexAttrib4f;

extern PFNGLVERTEXATTRIB4FVPROC glad_glVertexAttrib4fv;

extern PFNGLVERTEXATTRIB4IVPROC glad_glVertexAttrib4iv;

extern PFNGLVERTEXATTRIB4SPROC glad_glVertexAttrib4s;

extern PFNGLVERTEXATTRIB4SVPROC glad_glVertexAttrib4sv;

extern PFNGLVERTEXATTRIB4UBVPROC glad_glVertexAttrib4ubv;

extern PFNGLVERTEXATTRIB4UIVPROC glad_glVertexAttrib4uiv;

extern PFNGLVERTEXATTRIB4USVPROC glad_glVertexAttrib4usv;

extern PFNGLVERTEXATTRIBBINDINGPROC glad_glVertexAttribBinding;

extern PFNGLVERTEXATTRIBDIVISORPROC glad_glVertexAttribDivisor;

extern PFNGLVERTEXATTRIBFORMATPROC glad_glVertexAttribFormat;

extern PFNGLVERTEXATTRIBI1IPROC glad_glVertexAttribI1i;

extern PFNGLVERTEXATTRIBI1IVPROC glad_glVertexAttribI1iv;

extern PFNGLVERTEXATTRIBI1UIPROC glad_glVertexAttribI1ui;

extern PFNGLVERTEXATTRIBI1UIVPROC glad_glVertexAttribI1uiv;

extern PFNGLVERTEXATTRIBI2IPROC glad_glVertexAttribI2i;

extern PFNGLVERTEXATTRIBI2IVPROC glad_glVertexAttribI2iv;

extern PFNGLVERTEXATTRIBI2UIPROC glad_glVertexAttribI2ui;

extern PFNGLVERTEXATTRIBI2UIVPROC glad_glVertexAttribI2uiv;

extern PFNGLVERTEXATTRIBI3IPROC glad_glVertexAttribI3i;

extern PFNGLVERTEXATTRIBI3IVPROC glad_glVertexAttribI3iv;

extern PFNGLVERTEXATTRIBI3UIPROC glad_glVertexAttribI3ui;

extern PFNGLVERTEXATTRIBI3UIVPROC glad_glVertexAttribI3uiv;

extern PFNGLVERTEXATTRIBI4BVPROC glad_glVertexAttribI4bv;

extern PFNGLVERTEXATTRIBI4IPROC glad_glVertexAttribI4i;

extern PFNGLVERTEXATTRIBI4IVPROC glad_glVertexAttribI4iv;

extern PFNGLVERTEXATTRIBI4SVPROC glad_glVertexAttribI4sv;

extern PFNGLVERTEXATTRIBI4UBVPROC glad_glVertexAttribI4ubv;

extern PFNGLVERTEXATTRIBI4UIPROC glad_glVertexAttribI4ui;

extern PFNGLVERTEXATTRIBI4UIVPROC glad_glVertexAttribI4uiv;

extern PFNGLVERTEXATTRIBI4USVPROC glad_glVertexAttribI4usv;

extern PFNGLVERTEXATTRIBIFORMATPROC glad_glVertexAttribIFormat;

extern PFNGLVERTEXATTRIBIPOINTERPROC glad_glVertexAttribIPointer;

extern PFNGLVERTEXATTRIBL1DPROC glad_glVertexAttribL1d;

extern PFNGLVERTEXATTRIBL1DVPROC glad_glVertexAttribL1dv;

extern PFNGLVERTEXATTRIBL1UI64ARBPROC glad_glVertexAttribL1ui64ARB;

extern PFNGLVERTEXATTRIBL1UI64VARBPROC glad_glVertexAttribL1ui64vARB;

extern PFNGLVERTEXATTRIBL2DPROC glad_glVertexAttribL2d;

extern PFNGLVERTEXATTRIBL2DVPROC glad_glVertexAttribL2dv;

extern PFNGLVERTEXATTRIBL3DPROC glad_glVertexAttribL3d;

extern PFNGLVERTEXATTRIBL3DVPROC glad_glVertexAttribL3dv;

extern PFNGLVERTEXATTRIBL4DPROC glad_glVertexAttribL4d;

extern PFNGLVERTEXATTRIBL4DVPROC glad_glVertexAttribL4dv;

extern PFNGLVERTEXATTRIBLFORMATPROC glad_glVertexAttribLFormat;

extern PFNGLVERTEXATTRIBLPOINTERPROC glad_glVertexAttribLPointer;

extern PFNGLVERTEXATTRIBP1UIPROC glad_glVertexAttribP1ui;

extern PFNGLVERTEXATTRIBP1UIVPROC glad_glVertexAttribP1uiv;

extern PFNGLVERTEXATTRIBP2UIPROC glad_glVertexAttribP2ui;

extern PFNGLVERTEXATTRIBP2UIVPROC glad_glVertexAttribP2uiv;

extern PFNGLVERTEXATTRIBP3UIPROC glad_glVertexAttribP3ui;

extern PFNGLVERTEXATTRIBP3UIVPROC glad_glVertexAttribP3uiv;

extern PFNGLVERTEXATTRIBP4UIPROC glad_glVertexAttribP4ui;

extern PFNGLVERTEXATTRIBP4UIVPROC glad_glVertexAttribP4uiv;

extern PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;

extern PFNGLVERTEXBINDINGDIVISORPROC glad_glVertexBindingDivisor;

extern PFNGLVERTEXP2UIPROC glad_glVertexP2ui;

extern PFNGLVERTEXP2UIVPROC glad_glVertexP2uiv;

extern PFNGLVERTEXP3UIPROC glad_glVertexP3ui;

extern PFNGLVERTEXP3UIVPROC glad_glVertexP3uiv;

extern PFNGLVERTEXP4UIPROC glad_glVertexP4ui;

extern PFNGLVERTEXP4UIVPROC glad_glVertexP4uiv;

extern PFNGLVERTEXPOINTERPROC glad_glVertexPointer;

extern PFNGLVIEWPORTPROC glad_glViewport;

extern PFNGLVIEWPORTARRAYVPROC glad_glViewportArrayv;

extern PFNGLVIEWPORTINDEXEDFPROC glad_glViewportIndexedf;

extern PFNGLVIEWPORTINDEXEDFVPROC glad_glViewportIndexedfv;

extern PFNGLWAITSYNCPROC glad_glWaitSync;

extern PFNGLWINDOWPOS2DPROC glad_glWindowPos2d;

extern PFNGLWINDOWPOS2DVPROC glad_glWindowPos2dv;

extern PFNGLWINDOWPOS2FPROC glad_glWindowPos2f;

extern PFNGLWINDOWPOS2FVPROC glad_glWindowPos2fv;

extern PFNGLWINDOWPOS2IPROC glad_glWindowPos2i;

extern PFNGLWINDOWPOS2IVPROC glad_glWindowPos2iv;

extern PFNGLWINDOWPOS2SPROC glad_glWindowPos2s;

extern PFNGLWINDOWPOS2SVPROC glad_glWindowPos2sv;

extern PFNGLWINDOWPOS3DPROC glad_glWindowPos3d;

extern PFNGLWINDOWPOS3DVPROC glad_glWindowPos3dv;

extern PFNGLWINDOWPOS3FPROC glad_glWindowPos3f;

extern PFNGLWINDOWPOS3FVPROC glad_glWindowPos3fv;

extern PFNGLWINDOWPOS3IPROC glad_glWindowPos3i;

extern PFNGLWINDOWPOS3IVPROC glad_glWindowPos3iv;

extern PFNGLWINDOWPOS3SPROC glad_glWindowPos3s;

extern PFNGLWINDOWPOS3SVPROC glad_glWindowPos3sv;






extern int gladLoadGLUserPtr( GLADuserptrloadfunc load, void *userptr);
extern int gladLoadGL( GLADloadfunc load);




}
# 7 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/samplerOGL.h" 2

namespace Neon::RHI
{
class SamplerOGL : public Sampler
{
public:
    explicit SamplerOGL(const SamplerDescription &description);

    void bind(uint32_t binding) const;
private:
    GLuint handle{};
};
}
# 2 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/samplerOGL.cpp" 2



# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/convertOGL.h" 1
       
# 1 "C:/msys64/mingw64/include/c++/15.2.0/typeinfo" 1 3
# 36 "C:/msys64/mingw64/include/c++/15.2.0/typeinfo" 3
# 1 "C:/msys64/mingw64/include/c++/15.2.0/bits/exception.h" 1 3
# 40 "C:/msys64/mingw64/include/c++/15.2.0/bits/exception.h" 3

# 40 "C:/msys64/mingw64/include/c++/15.2.0/bits/exception.h" 3
extern "C++" {

namespace std
{
# 61 "C:/msys64/mingw64/include/c++/15.2.0/bits/exception.h" 3
  class exception
  {
  public:
    exception() noexcept { }
    virtual ~exception() noexcept;

    exception(const exception&) = default;
    exception& operator=(const exception&) = default;
    exception(exception&&) = default;
    exception& operator=(exception&&) = default;




    virtual const char*
    what() const noexcept;
  };



}

}
# 37 "C:/msys64/mingw64/include/c++/15.2.0/typeinfo" 2 3

# 1 "C:/msys64/mingw64/include/c++/15.2.0/bits/hash_bytes.h" 1 3
# 39 "C:/msys64/mingw64/include/c++/15.2.0/bits/hash_bytes.h" 3
namespace std
{







  size_t
  _Hash_bytes(const void* __ptr, size_t __len, size_t __seed);





  size_t
  _Fnv_hash_bytes(const void* __ptr, size_t __len, size_t __seed);


}
# 39 "C:/msys64/mingw64/include/c++/15.2.0/typeinfo" 2 3



# 1 "C:/msys64/mingw64/include/c++/15.2.0/bits/version.h" 1 3
# 43 "C:/msys64/mingw64/include/c++/15.2.0/typeinfo" 2 3

#pragma GCC visibility push(default)

extern "C++" {

namespace __cxxabiv1
{
  class __class_type_info;
}
# 85 "C:/msys64/mingw64/include/c++/15.2.0/typeinfo" 3
namespace std
{






  class type_info
  {
  public:




    virtual ~type_info();



    const char* name() const noexcept
    { return __name[0] == '*' ? __name + 1 : __name; }



    bool before(const type_info& __arg) const noexcept;

    constexpr
    bool operator==(const type_info& __arg) const noexcept;







    size_t hash_code() const noexcept
    {

      return _Hash_bytes(name(), __builtin_strlen(name()),
    static_cast<size_t>(0xc70f6907UL));



    }



    virtual bool __is_pointer_p() const;


    virtual bool __is_function_p() const;







    virtual bool __do_catch(const type_info *__thr_type, void **__thr_obj,
       unsigned __outer) const;


    virtual bool __do_upcast(const __cxxabiv1::__class_type_info *__target,
        void **__obj_ptr) const;

  protected:
    const char *__name;

    explicit type_info(const char *__n): __name(__n) { }

  private:


    type_info& operator=(const type_info&) = delete;
    type_info(const type_info&) = delete;






    bool __equal(const type_info&) const noexcept;

  };
# 194 "C:/msys64/mingw64/include/c++/15.2.0/typeinfo" 3
  [[__gnu__::__always_inline__]]

  constexpr inline bool
  type_info::operator==(const type_info& __arg) const noexcept
  {
    if (std::__is_constant_evaluated())
      return this == &__arg;

    if (__name == __arg.__name)
      return true;



    return __equal(__arg);






  }
# 224 "C:/msys64/mingw64/include/c++/15.2.0/typeinfo" 3
  class bad_cast : public exception
  {
  public:
    bad_cast() noexcept { }



    virtual ~bad_cast() noexcept;


    virtual const char* what() const noexcept;
  };





  class bad_typeid : public exception
  {
  public:
    bad_typeid () noexcept { }



    virtual ~bad_typeid() noexcept;


    virtual const char* what() const noexcept;
  };
}

}

#pragma GCC visibility pop
# 3 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/convertOGL.h" 2



# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/enums/pixelFormat.h" 1
       


# 3 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/enums/pixelFormat.h"
namespace Neon::RHI
{
    enum class PixelFormat
    {
        R8Unorm,
        R8Snorm,
        R8Uint,
        R8Int,

        R16Unorm,
        R16Snorm,
        R16Uint,
        R16Int,
        R16Float,

        R8G8Unorm,
        R8G8Snorm,
        R8G8Uint,
        R8G8Int,

        R16G16Unorm,
        R16G16Snorm,
        R16G16Uint,
        R16G16Int,
        R16G16Float,

        R32G32Float,
        R32G32Uint,
        R32G32Int,

        R32Float,
        R32Uint,
        R32Int,

        R8G8B8Unorm,
        R8G8B8Snorm,
        R8G8B8Uint,
        R8G8B8Int,
        R8G8B8UnormSrgb,
        B8G8R8Unorm,
        B8G8R8UnormSrgb,

        R16G16B16Unorm,
        R16G16B16Snorm,
        R16G16B16Uint,
        R16G16B16Int,
        R16G16B16Float,

        R32G32B32Float,
        R32G32B32Uint,
        R32G32B32Int,

        R8G8B8A8Unorm,
        R8G8B8A8Snorm,
        R8G8B8A8Uint,
        R8G8B8A8Int,
        R8G8B8A8UnormSrgb,
        B8G8R8A8Unorm,
        B8G8R8A8UnormSrgb,

        R16G16B16A16Unorm,
        R16G16B16A16Snorm,
        R16G16B16A16Uint,
        R16G16B16A16Int,
        R16G16B16A16Float,

        R32G32B32A32Float,
        R32G32B32A32Uint,
        R32G32B32A32Int,

        R10G10B10A2Unorm,
        R11G11B10Ufloat,

        BC1RgbaUnorm,
        BC1RgbaUnormSrgb,
        BC2RgbaUnorm,
        BC2RgbaUnormSrgb,
        BC3RgbaUnorm,
        BC3RgbaUnormSrgb,
        BC4RUnorm,
        BC5RgUnorm,
        BC7RgbaUnorm,
        BC7RgbaUnormSrgb,

        D24UnormS8Uint,
        D32FloatS8Uint,

        Invalid,
    };
}
# 7 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/convertOGL.h" 2
# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/enums/pixelLayout.h" 1
       

namespace Neon::RHI
{
enum class PixelLayout
{
    R,
    RG,
    RGB,
    BGR,
    RGBA,
    BGRA,
    Depth,
    Stencil,
    DepthStencil
};
}
# 8 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/convertOGL.h" 2
# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/enums/pixelType.h" 1
       

namespace Neon::RHI
{
    enum class PixelType
    {
        UnsignedByte,
        Byte,
        UnsignedShort,
        Short,
        UnsignedInt,
        Int,
        Float,
        UnsignedByte332,
        UnsignedShort565,
        UnsignedInt1010102
    };
}
# 9 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/convertOGL.h" 2
# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/enums/shaderType.h" 1
       

namespace Neon::RHI
{
enum class ShaderType
{
    Compute, Fragment, Vertex
};
}
# 10 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/convertOGL.h" 2

# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/enums/textureType.h" 1
       

namespace Neon::RHI
{
enum class TextureType
{
    Texture1D,
    Texture2D,
    Texture3D,
};
}
# 12 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/convertOGL.h" 2

# 1 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/input/keyCodes.h" 1
       


enum class KeyCode
{
    Unknown,
    Return,
    Escape,
    Backspace,
    Tab,
    Space,
    Exclaim,
    DblApostrophe,
    Hash,
    Dollar,
    Percent,
    Ampersand,
    Apostrophe,
    LeftParen,
    RightParen,
    Asterisk,
    Plus,
    Comma,
    Minus,
    Period,
    Slash,
    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Colon,
    Semicolon,
    Less,
    Equals,
    Greater,
    Question,
    At,
    LeftBracket,
    Backslash,
    RightBracket,
    Caret,
    Underscore,
    Grave,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    LeftBrace,
    Pipe,
    RightBrace,
    Tilde,
    Delete,
    PlusMinus,
    CapsLock,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    PrintScreen,
    ScrollLock,
    Pause,
    Insert,
    Home,
    PageUp,
    End,
    PageDown,
    Right,
    Left,
    Down,
    Up,
    NumLockClear,
    KpDivide,
    KpMultiply,
    KpMinus,
    KpPlus,
    KpEnter,
    Kp1,
    Kp2,
    Kp3,
    Kp4,
    Kp5,
    Kp6,
    Kp7,
    Kp8,
    Kp9,
    Kp0,
    KpPeriod,
    Application,
    Power,
    KpEquals,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25,
    Execute,
    Help,
    Menu,
    Select,
    Stop,
    Again,
    Undo,
    Cut,
    Copy,
    Paste,
    Find,
    Mute,
    VolumeUp,
    VolumeDown,
    KpComma,
    KpEqualsAs400,
    AltErase,
    SysReq,
    Cancel,
    Clear,
    Prior,
    Return2,
    Separator,
    Out,
    Oper,
    ClearAgain,
    CrSel,
    ExSel,
    Kp00,
    Kp000,
    ThousandsSeparator,
    DecimalSeparator,
    CurrencyUnit,
    CurrencySubUnit,
    KpLeftParen,
    KpRightParen,
    KpLeftBrace,
    KpRightBrace,
    KpTab,
    KpBackspace,
    KpA,
    KpB,
    KpC,
    KpD,
    KpE,
    KpF,
    KpXor,
    KpPower,
    KpPercent,
    KpLess,
    KpGreater,
    KpAmpersand,
    KpDblAmpersand,
    KpVerticalBar,
    KpDblVerticalBar,
    KpColon,
    KpHash,
    KpSpace,
    KpAt,
    KpExclam,
    KpMemStore,
    KpMemRecall,
    KpMemClear,
    KpMemAdd,
    KpMemSubtract,
    KpMemMultiply,
    KpMemDivide,
    KpPlusMinus,
    KpClear,
    KpClearEntry,
    KpBinary,
    KpOctal,
    KpDecimal,
    KpHexadecimal,
    LCtrl,
    LShift,
    LAlt,
    LGui,
    RCtrl,
    RShift,
    RAlt,
    RGui,
    Mode,
    Sleep,
    Wake,
    ChannelIncrement,
    ChannelDecrement,
    MediaPlay,
    MediaPause,
    MediaRecord,
    MediaFastForward,
    MediaRewind,
    MediaNextTrack,
    MediaPreviousTrack,
    MediaStop,
    MediaEject,
    MediaPlayPause,
    MediaSelect,
    AcNew,
    AcOpen,
    AcClose,
    AcExit,
    AcSave,
    AcPrint,
    AcProperties,
    AcSearch,
    AcHome,
    AcBack,
    AcForward,
    AcStop,
    AcRefresh,
    AcBookmarks,
    SoftLeft,
    SoftRight,
    Call,
    EndCall,
    LeftTab,
    Level5Shift,
    MultiKeyCompose,
    LMeta,
    RMeta,
    LHyper,
    RHyper,


    ExtendedMask,
    ScancodeMask
};

enum class KeyMod
{
    None,
    LShift,
    RShift,
    Level5,
    LCtrl,
    RCtrl,
    LAlt,
    RAlt,
    LGui,
    RGui,
    Num,
    Caps,
    Mode,
    Scroll,


    Ctrl,
    Shift,
    Alt,
    Gui
};

enum class MouseButton
{
    None,
    Left,
    Middle,
    Right,
    Side1,
    Side2,
};
# 14 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/convertOGL.h" 2

namespace Neon::RHI
{
class ConvertOGL
{
public:
    static GLenum typeinfoToGL(const std::type_info* type);
    static GLenum shaderTypeToGL(ShaderType type);
    static GLenum pixelFormatToGL(PixelFormat format);
    static GLenum pixelFormatToGLType(PixelFormat format);
    static uint32_t getComponentCount(const std::type_info* type);
    static KeyCode keyCodeFromGLFW(int keyCode);
    static KeyMod keyModFromGLFW(int mod);
    static MouseButton mouseButtonFromGLFW(int button);
    static GLenum textureWrapToGL(TextureWrap wrap);
    static GLenum textureFilterCombineToGL(TextureFilter filter, MipmapFilter mipmapFilter);
    static GLenum pixelTypeToGL(PixelType type);
    static GLenum pixelLayoutToGL(PixelLayout layout);
    static GLenum textureTypeToGLType(TextureType type);
};
}
# 6 "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/neonrhi/src/implementations/opengl/samplerOGL.cpp" 2

namespace Neon::RHI
{
    SamplerOGL::SamplerOGL(const SamplerDescription &description)
    {
        glad_glCreateSamplers(1, &handle);

        glad_glSamplerParameteri(handle, 0x2802, static_cast<int>(ConvertOGL::textureWrapToGL(description.wrapMode.x)));
        glad_glSamplerParameteri(handle, 0x2803, static_cast<int>(ConvertOGL::textureWrapToGL(description.wrapMode.y)));
        glad_glSamplerParameteri(handle, 0x2801, static_cast<int>(ConvertOGL::textureFilterCombineToGL(description.minFilter, description.mipmapFilter)));
        glad_glSamplerParameteri(handle, 0x2800, static_cast<int>(ConvertOGL::textureFilterCombineToGL(description.magFilter, description.mipmapFilter)));
        glad_glSamplerParameterf(handle, 0x8501, description.lodBias);
        glad_glSamplerParameteri(handle, 0x884C, 0);
    }

    void SamplerOGL::bind(const uint32_t binding) const
    {
        glad_glBindSampler(binding, handle);
    }
}
