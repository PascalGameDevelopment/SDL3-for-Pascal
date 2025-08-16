{
  This file is part of:

    SDL3 for Pascal
    (https://github.com/PascalGameDevelopment/SDL3-for-Pascal)
    SPDX-License-Identifier: Zlib
}

{*
 * A signed 8-bit integer type.
 *
 * \since This macro is available since SDL 3.2.0.
  }
type
  ppcint8_t=^pcint8_t;
  pcint8_t=^cint8_t;
  cint8_t=cint8;
const
  SDL_MAX_SINT8=cint8($7F);                 { 127  }
  SDL_MIN_SINT8=cint8(not ($7F));           { -128  }

{*
 * An unsigned 8-bit integer type.
 *
 * \since This macro is available since SDL 3.2.0.
  }
type
  ppcuint8_t=^pcuint8_t;
  pcuint8_t=^cuint8_t;
  cuint8_t=cuint8;
const
  SDL_MAX_UINT8=cuint8($FF);                { 255  }
  SDL_MIN_UINT8=cuint8($00);                { 0  }

{*
 * A signed 16-bit integer type.
 *
 * \since This macro is available since SDL 3.2.0.
  }
type
  ppcint16_t=^pcint16_t;
  pcint16_t=^cint16_t;
  cint16_t=cint16;
const
  SDL_MAX_SINT16=cint16($7FFF);             { 32767  }
  SDL_MIN_SINT16=cint16(not ($7FFF));      { -32768  }

{*
 * An unsigned 16-bit integer type.
 *
 * \since This macro is available since SDL 3.2.0.
  }
type
  ppcuint16_t=^pcuint16_t;
  pcuint16_t=^cuint16_t;
  cuint16_t=cuint16;
const
  SDL_MAX_UINT16=cuint16($FFFF);           { 65535  }
  SDL_MIN_UINT16=cuint16($0000);           { 0  }

{*
 * A signed 32-bit integer type.
 *
 * \since This macro is available since SDL 3.2.0.
  }
type
  ppcint32_t=^pcint32_t;
  pcint32_t=^cint32_t;
  cint32_t=cint32;
const
  SDL_MAX_SINT32=cint32($7FFFFFFF);        { 2147483647  }
  SDL_MIN_SINT32=cint32(not ($7FFFFFFF));  { -2147483648  }

{*
 * An unsigned 32-bit integer type.
 *
 * \since This macro is available since SDL 3.2.0.
  }
type
  ppcuint32_t=^pcuint32_t;
  pcuint32_t=^cuint32_t;
  cuint32_t=cuint32;
const
  SDL_MAX_UINT32=cuint32($FFFFFFFF);   { 4294967295  }
  SDL_MIN_UINT32=cuint32($00000000);   { 0  }

{*
 * A signed 64-bit integer type.
 *
 * \since This macro is available since SDL 3.2.0.
 *
 * \sa SDL_SINT64_C
  }
type
  ppcint64_t=^pcint64_t;
  pcint64_t=^cint64_t;
  cint64_t=cint64;
const
  { #note : SDL3-for-Pascal:
            The macro SDL_SINT64_C converts the values to guarantee their size.
            We do this simply by converting to cint64 here. }
  SDL_MAX_SINT64=cint64($7FFFFFFFFFFFFFFF);         { 9223372036854775807  }
  SDL_MIN_SINT64= not (cint64($7FFFFFFFFFFFFFFF));  { -9223372036854775808  }

{*
 * An unsigned 64-bit integer type.
 *
 * \since This macro is available since SDL 3.2.0.
 *
 * \sa SDL_UINT64_C
  }
type
  ppcuint64_t=^pcuint64_t;
  pcuint64_t=^cuint64_t;
  cuint64_t=cuint64;
const
  { #note : SDL3-for-Pascal:
            The macro SDL_SUINT64_C converts the values to guarantee their size.
            We do this simply by converting to cuint64 here. }
  SDL_MAX_UINT64=cuint64($FFFFFFFFFFFFFFFF);  { 18446744073709551615  }
  SDL_MIN_UINT64=cuint64($0000000000000000);  { 0  }

{*
 * SDL times are signed, 64-bit integers representing nanoseconds since the
 * Unix epoch (Jan 1, 1970).
 *
 * They can be converted between POSIX time_t values with SDL_NS_TO_SECONDS()
 * and SDL_SECONDS_TO_NS(), and between Windows FILETIME values with
 * SDL_TimeToWindows() and SDL_TimeFromWindows().
 *
 * \since This macro is available since SDL 3.2.0.
 *
 * \sa SDL_MAX_SINT64
 * \sa SDL_MIN_SINT64
  }
type
  PPSDL_Time = ^PSDL_Time;
  PSDL_Time = ^TSDL_Time;
  TSDL_Time = cint64;

const
  SDL_MAX_TIME = SDL_MAX_SINT64;
  SDL_MIN_TIME = SDL_MIN_SINT64;

{*
 * Epsilon constant, used for comparing floating-point numbers.
 *
 * Equals by default to platform-defined `FLT_EPSILON`, or
 * `1.1920928955078125e-07F` if that's not available.
 *
 * \since This macro is available since SDL 3.1.3.
  }
const
  SDL_FLT_EPSILON = cfloat(1.1920928955078125e-07);

(* -- Memory management functions -- *)

{*
 * Allocate uninitialized memory.
 *
 * The allocated memory returned by this function must be freed with
 * SDL_free().
 *
 * If `size` is 0, it will be set to 1.
 *
 * If the allocation is successful, the returned pointer is guaranteed to be
 * aligned to either the *fundamental alignment* (`alignof(max_align_t)` in
 * C11 and later) or `2 * sizeof(Pointer)`, whichever is smaller. Use
 * SDL_aligned_alloc() if you need to allocate memory aligned to an alignment
 * greater than this guarantee.
 *
 * \param size the size to allocate.
 * \returns a pointer to the allocated memory, or NIL if allocation failed.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_free
 * \sa SDL_calloc
 * \sa SDL_realloc
 * \sa SDL_aligned_alloc
 *}
function SDL_malloc(size: csize_t): Pointer; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_malloc' {$ENDIF} {$ENDIF};

{*
 * Allocate a zero-initialized array.
 *
 * The memory returned by this function must be freed with SDL_free().
 *
 * If either of `nmemb` or `size` is 0, they will both be set to 1.
 *
 * If the allocation is successful, the returned pointer is guaranteed to be
 * aligned to either the *fundamental alignment* (`alignof(max_align_t)` in
 * C11 and later) or `2 * sizeof(Pointer)`, whichever is smaller.
 *
 * \param nmemb the number of elements in the array.
 * \param size the size of each element of the array.
 * \returns a pointer to the allocated array, or NIL if allocation failed.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_free
 * \sa SDL_malloc
 * \sa SDL_realloc
 *}
function SDL_calloc(nmemb, size: csize_t): Pointer; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_calloc' {$ENDIF} {$ENDIF};

{*
 * Change the size of allocated memory.
 *
 * The memory returned by this function must be freed with SDL_free().
 *
 * If `size` is 0, it will be set to 1. Note that this is unlike some other C
 * runtime `realloc` implementations, which may treat `realloc(mem, 0)` the
 * same way as `free(mem)`.
 *
 * If `mem` is NIL, the behavior of this function is equivalent to
 * SDL_malloc(). Otherwise, the function can have one of three possible
 * outcomes:
 *
 * - If it returns the same pointer as `mem`, it means that `mem` was resized
 *   in place without freeing.
 * - If it returns a different non-NIL pointer, it means that `mem` was freed
 *   and cannot be dereferenced anymore.
 * - If it returns NIL (indicating failure), then `mem` will remain valid and
 *   must still be freed with SDL_free().
 *
 * If the allocation is successfully resized, the returned pointer is
 * guaranteed to be aligned to either the *fundamental alignment*
 * (`alignof(max_align_t)` in C11 and later) or `2 * sizeof(Pointer)`,
 * whichever is smaller.
 *
 * \param mem a pointer to allocated memory to reallocate, or NIL.
 * \param size the new size of the memory.
 * \returns a pointer to the newly allocated memory, or NIL if allocation
 *          failed.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_free
 * \sa SDL_malloc
 * \sa SDL_calloc
 *}
function SDL_realloc(mem: Pointer; size: csize_t): Pointer; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_realloc' {$ENDIF} {$ENDIF};

{*
 * Free allocated memory.
 *
 * The pointer is no longer valid after this call and cannot be dereferenced
 * anymore.
 *
 * If `mem` is NIL, this function does nothing.
 *
 * \param mem a pointer to allocated memory, or NIL.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_malloc
 * \sa SDL_calloc
 * \sa SDL_realloc
 *}
procedure SDL_free(mem: Pointer); cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_free' {$ENDIF} {$ENDIF};

type
  PPSDL_malloc_func = ^PSDL_malloc_func;
  PSDL_malloc_func = ^TSDL_malloc_func;
  {*
   * A callback used to implement SDL_malloc().
   *
   * SDL will always ensure that the passed `size` is greater than 0.
   *
   * \param size the size to allocate.
   * \returns a pointer to the allocated memory, or NIL if allocation failed.
   *
   * \threadsafety It should be safe to call this callback from any thread.
   *
   * \since This datatype is available since SDL 3.2.0.
   *
   * \sa SDL_malloc
   * \sa SDL_GetOriginalMemoryFunctions
   * \sa SDL_GetMemoryFunctions
   * \sa SDL_SetMemoryFunctions
   *}
  TSDL_malloc_func = function(size: csize_t): Pointer; cdecl;

  PPSDL_calloc_func = ^PSDL_calloc_func;
  PSDL_calloc_func = ^TSDL_calloc_func;
  {*
   * A callback used to implement SDL_calloc().
   *
   * SDL will always ensure that the passed `nmemb` and `size` are both greater
   * than 0.
   *
   * \param nmemb the number of elements in the array.
   * \param size the size of each element of the array.
   * \returns a pointer to the allocated array, or NIL if allocation failed.
   *
   * \threadsafety It should be safe to call this callback from any thread.
   *
   * \since This datatype is available since SDL 3.2.0.
   *
   * \sa SDL_calloc
   * \sa SDL_GetOriginalMemoryFunctions
   * \sa SDL_GetMemoryFunctions
   * \sa SDL_SetMemoryFunctions
   *}
  TSDL_calloc_func = function(nmemb, size: csize_t): Pointer; cdecl;

  PPSDL_realloc_func = ^PSDL_realloc_func;
  PSDL_realloc_func = ^TSDL_realloc_func;
  {*
   * A callback used to implement SDL_realloc().
   *
   * SDL will always ensure that the passed `size` is greater than 0.
   *
   * \param mem a pointer to allocated memory to reallocate, or NIL.
   * \param size the new size of the memory.
   * \returns a pointer to the newly allocated memory, or NIL if allocation
   *          failed.
   *
   * \threadsafety It should be safe to call this callback from any thread.
   *
   * \since This datatype is available since SDL 3.2.0.
   *
   * \sa SDL_realloc
   * \sa SDL_GetOriginalMemoryFunctions
   * \sa SDL_GetMemoryFunctions
   * \sa SDL_SetMemoryFunctions
   *}
  TSDL_realloc_func = function(mem: Pointer; size: csize_t): Pointer; cdecl;

  PPSDL_free_func = ^PSDL_free_func;
  PSDL_free_func = ^TSDL_free_func;
  {*
   * A callback used to implement SDL_free().
   *
   * SDL will always ensure that the passed `mem` is a non-NIL pointer.
   *
   * \param mem a pointer to allocated memory.
   *
   * \threadsafety It should be safe to call this callback from any thread.
   *
   * \since This datatype is available since SDL 3.2.0.
   *
   * \sa SDL_free
   * \sa SDL_GetOriginalMemoryFunctions
   * \sa SDL_GetMemoryFunctions
   * \sa SDL_SetMemoryFunctions
   *}
  TSDL_free_func = procedure(mem: Pointer); cdecl;

{*
 * Get the original set of SDL memory functions.
 *
 * This is what SDL_malloc and friends will use by default, if there has been
 * no call to SDL_SetMemoryFunctions. This is not necessarily using the C
 * runtime's `malloc` functions behind the scenes! Different platforms and
 * build configurations might do any number of unexpected things.
 *
 * \param malloc_func filled with malloc function.
 * \param calloc_func filled with calloc function.
 * \param realloc_func filled with realloc function.
 * \param free_func filled with free function.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
procedure SDL_GetOriginalMemoryFunctions(
  malloc_func: PSDL_malloc_func;
  calloc_func: PSDL_calloc_func;
  realloc_func: PSDL_realloc_func;
  free_func: PSDL_free_func
); cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_GetOriginalMemoryFunctions' {$ENDIF} {$ENDIF};

{*
 * Get the current set of SDL memory functions.
 *
 * \param malloc_func filled with malloc function.
 * \param calloc_func filled with calloc function.
 * \param realloc_func filled with realloc function.
 * \param free_func filled with free function.
 *
 * \threadsafety This does not hold a lock, so do not call this in the
 *               unlikely event of a background thread calling
 *               SDL_SetMemoryFunctions simultaneously.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_SetMemoryFunctions
 * \sa SDL_GetOriginalMemoryFunctions
 *}
procedure SDL_GetMemoryFunctions(
  malloc_func: PSDL_malloc_func;
  calloc_func: PSDL_calloc_func;
  realloc_func: PSDL_realloc_func;
  free_func: PSDL_free_func
); cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_GetMemoryFunctions' {$ENDIF} {$ENDIF};

{*
 * Replace SDL's memory allocation functions with a custom set.
 *
 * It is not safe to call this function once any allocations have been made,
 * as future calls to SDL_free will use the new allocator, even if they came
 * from an SDL_malloc made with the old one!
 *
 * If used, usually this needs to be the first call made into the SDL library,
 * if not the very first thing done at program startup time.
 *
 * \param malloc_func custom malloc function.
 * \param calloc_func custom calloc function.
 * \param realloc_func custom realloc function.
 * \param free_func custom free function.
 * \returns true on success or false on failure; call SDL_GetError() for more
 *          information.
 *
 * \threadsafety It is safe to call this function from any thread, but one
 *               should not replace the memory functions once any allocations
 *               are made!
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_GetMemoryFunctions
 * \sa SDL_GetOriginalMemoryFunctions
 *}
function SDL_SetMemoryFunctions(
  malloc_func: TSDL_malloc_func;
  calloc_func: TSDL_calloc_func;
  realloc_func: TSDL_realloc_func;
  free_func: TSDL_free_func
): Boolean; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_SetMemoryFunctions' {$ENDIF} {$ENDIF};

{*
 * Allocate memory aligned to a specific alignment.
 *
 * The memory returned by this function must be freed with SDL_aligned_free(),
 * _not_ SDL_free().
 *
 * If `alignment` is less than the size of `void *`, it will be increased to
 * match that.
 *
 * The returned memory address will be a multiple of the alignment value, and
 * the size of the memory allocated will be a multiple of the alignment value.
 *
 * \param alignment the alignment of the memory.
 * \param size the size to allocate.
 * \returns a pointer to the aligned memory, or NIL if allocation failed.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_aligned_free
 *}
function SDL_aligned_alloc(alignment, size: csize_t): Pointer; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_aligned_alloc' {$ENDIF} {$ENDIF};

{*
 * Free memory allocated by SDL_aligned_alloc().
 *
 * The pointer is no longer valid after this call and cannot be dereferenced
 * anymore.
 *
 * If `mem` is NIL, this function does nothing.
 *
 * \param mem a pointer previously returned by SDL_aligned_alloc(), or NIL.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_aligned_alloc
 *}
procedure SDL_aligned_free(mem: Pointer); cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_aligned_free' {$ENDIF} {$ENDIF};

{*
 * Get the number of outstanding (unfreed) allocations.
 *
 * \returns the number of allocations or -1 if allocation counting is
 *          disabled.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_GetNumAllocations(): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_GetNumAllocations' {$ENDIF} {$ENDIF};

(* -- Environment variables manipulation functions -- *)

type
  PPSDL_Environment = ^PSDL_Environment;
  {*
   * A thread-safe set of environment variables
   *
   * \since This struct is available since SDL 3.2.0.
   *
   * \sa SDL_GetEnvironment
   * \sa SDL_CreateEnvironment
   * \sa SDL_GetEnvironmentVariable
   * \sa SDL_GetEnvironmentVariables
   * \sa SDL_SetEnvironmentVariable
   * \sa SDL_UnsetEnvironmentVariable
   * \sa SDL_DestroyEnvironment
   *}
  PSDL_Environment = type Pointer;

{*
 * Get the process environment.
 *
 * This is initialized at application start and is not affected by setenv()
 * and unsetenv() calls after that point. Use SDL_SetEnvironmentVariable() and
 * SDL_UnsetEnvironmentVariable() if you want to modify this environment, or
 * SDL_setenv_unsafe() or SDL_unsetenv_unsafe() if you want changes to persist
 * in the C runtime environment after SDL_Quit().
 *
 * \returns a pointer to the environment for the process or NIL on failure;
 *          call SDL_GetError() for more information.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_GetEnvironmentVariable
 * \sa SDL_GetEnvironmentVariables
 * \sa SDL_SetEnvironmentVariable
 * \sa SDL_UnsetEnvironmentVariable
 *}
function SDL_GetEnvironment(): PSDL_Environment; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_GetEnvironment' {$ENDIF} {$ENDIF};

{**
 * Create a set of environment variables
 *
 * \param populated true to initialize it from the C runtime environment,
 *                  false to create an empty environment.
 * \returns a pointer to the new environment or NIL on failure; call
 *          SDL_GetError() for more information.
 *
 * \threadsafety If `populated` is false, it is safe to call this function
 *               from any thread, otherwise it is safe if no other threads are
 *               calling setenv() or unsetenv()
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_GetEnvironmentVariable
 * \sa SDL_GetEnvironmentVariables
 * \sa SDL_SetEnvironmentVariable
 * \sa SDL_UnsetEnvironmentVariable
 * \sa SDL_DestroyEnvironment
 *}
function SDL_CreateEnvironment(populated: Boolean): PSDL_Environment; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_CreateEnvironment' {$ENDIF} {$ENDIF};

{*
 * Get the value of a variable in the environment.
 *
 * \param env the environment to query.
 * \param name the name of the variable to get.
 * \returns a pointer to the (read-only) value of the variable
 *          or NIL if it can't be found.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_GetEnvironment
 * \sa SDL_CreateEnvironment
 * \sa SDL_GetEnvironmentVariables
 * \sa SDL_SetEnvironmentVariable
 * \sa SDL_UnsetEnvironmentVariable
 *}
function SDL_GetEnvironmentVariable(env: PSDL_Environment; const name: PAnsiChar): PAnsiChar; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_GetEnvironmentVariable' {$ENDIF} {$ENDIF};

{*
 * Get all variables in the environment.
 *
 * \param env the environment to query.
 * \returns a NIL terminated array of pointers to environment variables in
 *          the form "variable=value" or NIL on failure; call SDL_GetError()
 *          for more information. This is a single allocation that should be
 *          freed with SDL_free() when it is no longer needed.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_GetEnvironment
 * \sa SDL_CreateEnvironment
 * \sa SDL_GetEnvironmentVariables
 * \sa SDL_SetEnvironmentVariable
 * \sa SDL_UnsetEnvironmentVariable
 *}
function SDL_GetEnvironmentVariables(env: PSDL_Environment): PPAnsiChar; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_GetEnvironmentVariables' {$ENDIF} {$ENDIF};

{**
 * Set the value of a variable in the environment.
 *
 * \param env the environment to modify.
 * \param name the name of the variable to set.
 * \param value the value of the variable to set.
 * \param overwrite true to overwrite the variable if it exists, false to
 *                  return success without setting the variable if it already
 *                  exists.
 * \returns true on success or false on failure; call SDL_GetError() for more
 *          information.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_GetEnvironment
 * \sa SDL_CreateEnvironment
 * \sa SDL_GetEnvironmentVariable
 * \sa SDL_GetEnvironmentVariables
 * \sa SDL_UnsetEnvironmentVariable
 *}
function SDL_SetEnvironmentVariable(env: PSDL_Environment; const name, value: PAnsiChar; overwrite: Boolean): Boolean; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_SetEnvironmentVariable' {$ENDIF} {$ENDIF};

{*
 * Clear a variable from the environment.
 *
 * \param env the environment to modify.
 * \param name the name of the variable to unset.
 * \returns true on success or false on failure; call SDL_GetError() for more
 *          information.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_GetEnvironment
 * \sa SDL_CreateEnvironment
 * \sa SDL_GetEnvironmentVariable
 * \sa SDL_GetEnvironmentVariables
 * \sa SDL_SetEnvironmentVariable
 * \sa SDL_UnsetEnvironmentVariable
 *}
function SDL_UnsetEnvironmentVariable(env: PSDL_Environment; const name: PAnsiChar): Boolean; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_UnsetEnvironmentVariable' {$ENDIF} {$ENDIF};

{*
 * Destroy a set of environment variables.
 *
 * \param env the environment to destroy.
 *
 * \threadsafety It is safe to call this function from any thread, as long as
 *               the environment is no longer in use.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_CreateEnvironment
 *}
procedure SDL_DestroyEnvironment(env: PSDL_Environment); cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_DestroyEnvironment' {$ENDIF} {$ENDIF};

{*
 * Get the value of a variable in the environment.
 *
 * This function uses SDL's cached copy of the environment and is thread-safe.
 *
 * \param name the name of the variable to get.
 * \returns a pointer to the (read-only) value of the variable
 *          or NIL if it can't be found.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_getenv(const name: PAnsiChar): PAnsiChar; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_getenv' {$ENDIF} {$ENDIF};

{*
 * Get the value of a variable in the environment.
 *
 * This function bypasses SDL's cached copy of the environment and is not
 * thread-safe.
 *
 * \param name the name of the variable to get.
 * \returns a pointer to the (read-only) value of the variable
 *          or NIL if it can't be found.
 *
 * \threadsafety This function is not thread safe, consider using SDL_getenv()
 *               instead.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_getenv
 *}
function SDL_getenv_unsafe(const name: PAnsiChar): PAnsiChar; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_getenv_unsafe' {$ENDIF} {$ENDIF};

{*
 * Set the value of a variable in the environment.
 *
 * \param name the name of the variable to set.
 * \param value the value of the variable to set.
 * \param overwrite 1 to overwrite the variable if it exists, 0 to return
 *                  success without setting the variable if it already exists.
 * \returns 0 on success, -1 on error.
 *
 * \threadsafety This function is not thread safe, consider using
 *               SDL_SetEnvironmentVariable() instead.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_SetEnvironmentVariable
 *}
function SDL_setenv_unsafe(const name, value: PAnsiChar; overwrite: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_setenv_unsafe' {$ENDIF} {$ENDIF};

{*
 * Clear a variable from the environment.
 *
 * \param name the name of the variable to unset.
 * \returns 0 on success, -1 on error.
 *
 * \threadsafety This function is not thread safe, consider using
 *               SDL_UnsetEnvironmentVariable() instead.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_UnsetEnvironmentVariable
 *}
function SDL_unsetenv_unsafe(const name: PAnsiChar): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_unsetenv_unsafe' {$ENDIF} {$ENDIF};

(* -- Character classification functions -- *)

{*
 * Query if a character is alphabetic (a letter).
 *
 * **WARNING**: Regardless of system locale, this will only treat ASCII values
 * for English 'a-z' and 'A-Z' as true.
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_isalpha(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_isalpha' {$ENDIF} {$ENDIF};

{*
 * Query if a character is alphabetic (a letter) or a number.
 *
 * **WARNING**: Regardless of system locale, this will only treat ASCII values
 * for English 'a-z', 'A-Z', and '0-9' as true.
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_isalnum(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_isalnum' {$ENDIF} {$ENDIF};

{*
 * Report if a character is blank (a space or tab).
 *
 * **WARNING**: Regardless of system locale, this will only treat ASCII values
 * 0x20 (space) or 0x9 (tab) as true.
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_isblank(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_isblank' {$ENDIF} {$ENDIF};

{*
 * Report if a character is a control character.
 *
 * **WARNING**: Regardless of system locale, this will only treat ASCII values
 * 0 through 0x1F, and 0x7F, as true.
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_iscntrl(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_iscntrl' {$ENDIF} {$ENDIF};

{*
 * Report if a character is a numeric digit.
 *
 * **WARNING**: Regardless of system locale, this will only treat ASCII values
 * '0' (0x30) through '9' (0x39), as true.
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_isdigit(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_isdigit' {$ENDIF} {$ENDIF};

{*
 * Report if a character is a hexadecimal digit.
 *
 * **WARNING**: Regardless of system locale, this will only treat ASCII values
 * 'A' through 'F', 'a' through 'f', and '0' through '9', as true.
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_isxdigit(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_isxdigit' {$ENDIF} {$ENDIF};

{*
 * Report if a character is a punctuation mark.
 *
 * **WARNING**: Regardless of system locale, this is equivalent to
 * `((SDL_isgraph(x)) && (!SDL_isalnum(x)))`.
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_isgraph
 * \sa SDL_isalnum
 *}
function SDL_ispunct(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_ispunct' {$ENDIF} {$ENDIF};

{*
 * Report if a character is whitespace.
 *
 * **WARNING**: Regardless of system locale, this will only treat the
 * following ASCII values as true:
 *
 * - space (0x20)
 * - tab (0x09)
 * - newline (0x0A)
 * - vertical tab (0x0B)
 * - form feed (0x0C)
 * - return (0x0D)
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_isspace(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_isspace' {$ENDIF} {$ENDIF};

{*
 * Report if a character is upper case.
 *
 * **WARNING**: Regardless of system locale, this will only treat ASCII values
 * 'A' through 'Z' as true.
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_isupper(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_isupper' {$ENDIF} {$ENDIF};

{*
 * Report if a character is lower case.
 *
 * **WARNING**: Regardless of system locale, this will only treat ASCII values
 * 'a' through 'z' as true.
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_islower(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_islower' {$ENDIF} {$ENDIF};

{*
 * Report if a character is "printable".
 *
 * Be advised that "printable" has a definition that goes back to text
 * terminals from the dawn of computing, making this a sort of special case
 * function that is not suitable for Unicode (or most any) text management.
 *
 * **WARNING**: Regardless of system locale, this will only treat ASCII values
 * ' ' (0x20) through '~' (0x7E) as true.
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *}
function SDL_isprint(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_isprint' {$ENDIF} {$ENDIF};

{*
 * Report if a character is any "printable" except space.
 *
 * Be advised that "printable" has a definition that goes back to text
 * terminals from the dawn of computing, making this a sort of special case
 * function that is not suitable for Unicode (or most any) text management.
 *
 * **WARNING**: Regardless of system locale, this is equivalent to
 * `(SDL_isprint(x)) && ((x) != ' ')`.
 *
 * \param x character value to check.
 * \returns non-zero if x falls within the character class, zero otherwise.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
 *
 * \sa SDL_isprint
 *}
function SDL_isgraph(x: cint): cint; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_isgraph' {$ENDIF} {$ENDIF};

(* -- Floating-point arithmetic functions -- *)

{*
 * Compute the absolute value of `x`
 *
 * Domain: `-INF <= x <= INF`
 *
 * Range: `0 <= y <= INF`
 *
 * This function operates on double-precision floating point values, use
 * SDL_copysignf for single-precision floats.
 *
 * \param x floating point value to use as the magnitude.
 * \returns the absolute value of `x`.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.1.3.
 *
 * \sa SDL_fabsf
  }
function SDL_fabs(x: cdouble): cdouble; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_fabs' {$ENDIF} {$ENDIF};

{*
 * Compute the absolute value of `x`
 *
 * Domain: `-INF <= x <= INF`
 *
 * Range: `0 <= y <= INF`
 *
 * This function operates on single-precision floating point values, use
 * SDL_copysignf for double-precision floats.
 *
 * \param x floating point value to use as the magnitude.
 * \returns the absolute value of `x`.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.1.3.
 *
 * \sa SDL_fabs
  }
function SDL_fabsf(x: cfloat): cfloat; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_fabsf' {$ENDIF} {$ENDIF};

{*
 * A generic function pointer.
 *
 * In theory, generic function pointers should use this, instead of `void *`,
 * since some platforms could treat code addresses differently than data
 * addresses. Although in current times no popular platforms make this
 * distinction, it is more correct and portable to use the correct type for a
 * generic pointer.
 *
 * If for some reason you need to force this typedef to be an actual `void *`,
 * perhaps to work around a compiler or existing code, you can define
 * `SDL_FUNCTION_POINTER_IS_VOID_POINTER` before including any SDL headers.
 *
 * \since This datatype is available since SDL 3.1.3.
  }
type
  TSDL_FunctionPointer = procedure(parameter:Pointer); cdecl;

