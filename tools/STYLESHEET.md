# SDL3 Code Style Sheet (C to Pascal)

This guide helps to quickly translate often found C constructs in the
SDL3 package into Pascal according to our Code style guidelines. Its
goal is to have consistent code over all files in the conversion
project.

## General Rules

1. Names of C defines (constants) and function parameters shall not be modified or "pascalified"
Ex: `SDL_INIT_VIDEO` does not change into `SDLInitVideo`.

2. Names corresponding to reserved key words are kept and an underscore is added.
Ex.: `type` in C function `SDL_HasEvent(Uint32 type)` changes into `type_`
in Pascal function `SDL_HasEvent(type_: TSDL_EventType)`.

3. Use C data types like `cuint8`, `cuint16`, `cuint32`, `cint8`, `cint16`,
`cint32`, `cfloat` and so on if native C data types are used  in the
original code. Note: For FPC you need to add the unit `ctypes` to use these C
data types. For Delphi we have a temporary solution provided.

**Example:** Use `cuint32` (if `Uint32` is used in
the original code) instead of `UInt32`, `Cardinal`, `LongWord` or `DWord`.
Exception 1: Replace `*char` by `PAnsiChar`.

4. In SDL3 the type `SDL_Bool` has been replaced by plain `bool`. C's bool is usually 1 byte in size
and therefore fully memory comaptible with Free Pascal's and Delphi's Boolean.
Hence we translate `bool` by `Boolean`.

5. If an identifier or a function declaration is gone, mark it as `deprecated`.

6. For convenience we encourage to add single and double pointers for any SDL type.

## Defines

### Basic Defines

C:

```c
#define SDL_HAT_CENTERED    0x00
#define SDL_HAT_UP          0x01
#define SDL_HAT_RIGHT       0x02
#define SDL_HAT_DOWN        0x04
#define SDL_HAT_LEFT        0x08
#define SDL_HAT_RIGHTUP     (SDL_HAT_RIGHT|SDL_HAT_UP)
#define SDL_HAT_RIGHTDOWN   (SDL_HAT_RIGHT|SDL_HAT_DOWN)
#define SDL_HAT_LEFTUP      (SDL_HAT_LEFT|SDL_HAT_UP)
#define SDL_HAT_LEFTDOWN    (SDL_HAT_LEFT|SDL_HAT_DOWN)
```

Pascal:

```pascal
const
  SDL_HAT_CENTERED  = $00;
  SDL_HAT_UP        = $01;
  SDL_HAT_RIGHT     = $02;
  SDL_HAT_DOWN      = $04;
  SDL_HAT_LEFT      = $08;
  SDL_HAT_RIGHTUP   = SDL_HAT_RIGHT or SDL_HAT_UP;
  SDL_HAT_RIGHTDOWN = SDL_HAT_RIGHT or SDL_HAT_DOWN;
  SDL_HAT_LEFTUP    = SDL_HAT_LEFT or SDL_HAT_UP;
  SDL_HAT_LEFTDOWN  = SDL_HAT_LEFT or SDL_HAT_DOWN;
```
### Basic Types

C:

```c
typedef Uint32 SDL_WindowID;
```

Pascal:

```pascal
type
  PPSDL_WindowID = ^PSDL_WindowID;
  PSDL_WindowID = ^TSDL_WindowID;
  TSDL_WindowID = cuint32;
```
Always add the single pointer and the double pointer of a type.

### Typed Aliases

Often in there are defines which are clearly associated with a SDL type.

C:
```
typedef Uint32 SDL_InitFlags;

#define SDL_INIT_AUDIO      0x00000010u /**< `SDL_INIT_AUDIO` implies `SDL_INIT_EVENTS` */
#define SDL_INIT_VIDEO      0x00000020u /**< `SDL_INIT_VIDEO` implies `SDL_INIT_EVENTS` */
#define SDL_INIT_JOYSTICK   0x00000200u /**< `SDL_INIT_JOYSTICK` implies `SDL_INIT_EVENTS`, should be initialized on the same thread as SDL_INIT_VIDEO on Windows if you don't set SDL_HINT_JOYSTICK_THREAD */
#define SDL_INIT_HAPTIC     0x00001000u
#define SDL_INIT_GAMEPAD    0x00002000u /**< `SDL_INIT_GAMEPAD` implies `SDL_INIT_JOYSTICK` */
#define SDL_INIT_EVENTS     0x00004000u
#define SDL_INIT_SENSOR     0x00008000u /**< `SDL_INIT_SENSOR` implies `SDL_INIT_EVENTS` */
#define SDL_INIT_CAMERA     0x00010000u /**< `SDL_INIT_CAMERA` implies `SDL_INIT_EVENTS` */
```

Pascal:

```pascal
type
  PPSDL_InitFlags = ^PSDL_InitFlags;
  PSDL_InitFlags = ^TSDL_InitFlags;
  TSDL_InitFlags = type cuint32;

const
  SDL_INIT_AUDIO = TSDL_InitFlags($00000010);    { `SDL_INIT_AUDIO` implies `SDL_INIT_EVENTS`  }
  SDL_INIT_VIDEO = TSDL_InitFlags($00000020);    { `SDL_INIT_VIDEO` implies `SDL_INIT_EVENTS`  }
  SDL_INIT_JOYSTICK = TSDL_InitFlags($00000200); { `SDL_INIT_JOYSTICK` implies `SDL_INIT_EVENTS`, should be initialized on the same thread as SDL_INIT_VIDEO on Windows if you don't set SDL_HINT_JOYSTICK_THREAD  }
  SDL_INIT_HAPTIC = TSDL_InitFlags($00001000);
  SDL_INIT_GAMEPAD = TSDL_InitFlags($00002000);  { `SDL_INIT_GAMEPAD` implies `SDL_INIT_JOYSTICK`  }
  SDL_INIT_EVENTS = TSDL_InitFlags($00004000);
  SDL_INIT_SENSOR = TSDL_InitFlags($00008000);   { `SDL_INIT_SENSOR` implies `SDL_INIT_EVENTS`  }
  SDL_INIT_CAMERA = TSDL_InitFlags($00010000);   { `SDL_INIT_CAMERA` implies `SDL_INIT_EVENTS`  }
```
1. The translated type gets a typed alias (here: ...= **type** cuint32 instead of just ...= cuint32).

2. The (const) values are typed accordingly.

### Enums

C:

```c
typedef enum
{
   SDL_JOYSTICK_POWER_UNKNOWN = -1,
   SDL_JOYSTICK_POWER_EMPTY,   /* <= 5% */
   SDL_JOYSTICK_POWER_LOW,     /* <= 20% */
   SDL_JOYSTICK_POWER_MEDIUM,  /* <= 70% */
   SDL_JOYSTICK_POWER_FULL,    /* <= 100% */
   SDL_JOYSTICK_POWER_WIRED,
   SDL_JOYSTICK_POWER_MAX
} SDL_JoystickPowerLevel;
```

Pascal:

```pascal
type
  PPSDL_JoystickPowerLevel = ^PSDL_JoystickPowerLevel;
  PSDL_JoystickPowerLevel = ^TSDL_JoystickPowerLevel;
  TSDL_JoystickPowerLevel = type Integer;

const
  SDL_JOYSTICK_POWER_UNKNOWN = TSDL_JoystickPowerLevel(-1);
  SDL_JOYSTICK_POWER_EMPTY   = TSDL_JoystickPowerLevel(0);  {* <= 5% *}
  SDL_JOYSTICK_POWER_LOW     = TSDL_JoystickPowerLevel(1);  {* <= 20% *}
  SDL_JOYSTICK_POWER_MEDIUM  = TSDL_JoystickPowerLevel(2);  {* <= 70% *}
  SDL_JOYSTICK_POWER_FULL    = TSDL_JoystickPowerLevel(3);  {* <= 100% *}
  SDL_JOYSTICK_POWER_WIRED   = TSDL_JoystickPowerLevel(4);
  SDL_JOYSTICK_POWER_MAX     = TSDL_JoystickPowerLevel(5);
```

Hint 1: C enums start at 0 if no explicit value is set.

Hint 2: The type should always be cint. Most C compilers have the enum elements
> In C, each enumeration constant has type int and each enumeration type
> is compatible with some integer type. (The integer types include all three
> character types–plain, signed, and unsigned.) The choice of compatible
> type is implementation-defined. The C standard grants the freedom to
> use different integer types to represent different enumeration types,
> but most compilers just use int to represent all enumeration types.
Ref.: [https://www.embedded.com/enumerations-are-integers-except-when-theyre-not/](https://www.embedded.com/enumerations-are-integers-except-when-theyre-not/)

Hint 3: Do not translate C enums to Pascal enums. C enums are handled like plain
integers which will make bitwise operations (e. g. in macros) possible
without typecasting.

## Structs

### Defined Structs

C:

```c
typedef struct SDL_version
{
    Uint8 major;        /**< major version */
    Uint8 minor;        /**< minor version */
    Uint8 patch;        /**< update version */
} SDL_version;
```

Pascal:

```pascal
type
  PPSDL_Version = ^PSDL_Version;
  PSDL_Version = ^TSDL_Version;
  TSDL_Version = record
    major: cuint8    { major version }
    minor: cuint8    { minor version }
    patch: cuint8;   { update version }
  end;
```

### Opaque Structs

If you have something like ```typedef struct name name```. the concrete
structure is opaque, and the programmer is expected to only ever
interact with pointers to the struct.

C:

```c
typedef struct SDL_Window SDL_Window;
```

Pascal:

```pascal
type
  PPSDL_Window = ^PSDL_Window;
  PSDL_Window = type Pointer;
```

As shown above, for opaque structs, we avoid defining the base `TType`
and define only the pointer `PType`.
For the rationale behind this decision, read the discussion in
[issue #63](https://github.com/PascalGameDevelopment/SDL2-for-Pascal/issues/63).


## Unions

C:

```c
typedef union {
    /** \brief A cutoff alpha value for binarization of the window shape's alpha channel. */
    Uint8 binarizationCutoff;
    SDL_Color colorKey;
} SDL_WindowShapeParams;
```

Pascal:

```pascal
type
  PPSDL_WindowShapeParams = ^PSDL_WindowShapeParams;
  PSDL_WindowShapeParams = ^TSDL_WindowShapeParams;
  TSDL_WindowShapeParams = record
  case cint of
    { A cutoff alpha value for binarization of the window shape's alpha channel. }
    0: (binarizationCutoff: cuint8);
    1: (colorKey: TSDL_ColorKey);
  end;
```

## Functions

C:

```c
extern DECLSPEC void SDLCALL SDL_LockJoysticks(void);

extern DECLSPEC const char *SDLCALL SDL_JoystickNameForIndex(int device_index);
```

Pascal:

```pascal
procedure SDL_LockJoysticks(); cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_LockJoysticks' {$ENDIF} {$ENDIF};

function SDL_JoystickNameForIndex(device_index: cint): PAnsiChar; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_JoystickNameForIndex' {$ENDIF} {$ENDIF};
```

### Variadic Functions
C:
```c
extern SDL_DECLSPEC void SDLCALL SDL_Log(const char *fmt, ...);
```

Pascal:

```pascal
procedure SDL_Log(fmt: PAnsiChar; Args: array of const); cdecl; overload;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_Log' {$ENDIF} {$ENDIF};
procedure SDL_Log(fmt: PAnsiChar); cdecl; overload;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_Log' {$ENDIF} {$ENDIF};
```
A variadic C function expands to two overloaded Pascal functions. One which
has no variadic part and one which translates the variadic part (...) to an
array of const.

## C Macros

Macros are pre-processed constructs in C which have no analogue in Pascal.
Usually a C macro is translated as a Pascal function and implemented in SDL2.pas.

C:

```c
#define SDL_VERSION_ATLEAST(X, Y, Z) \
    (SDL_COMPILEDVERSION >= SDL_VERSIONNUM(X, Y, Z))
```

Pascal:

_sdlversion.inc (declaration)_:
```pascal
function SDL_VERSION_ATLEAST(X,Y,Z: cuint8): Boolean;
```

_sdl2.pas (implementation)_:
```pascal
function SDL_VERSION_ATLEAST(X,Y,Z: cuint8): Boolean;
begin
  Result := SDL_COMPILEDVERSION >= SDL_VERSIONNUM(X,Y,Z);
end;
```
Hint: As can be seen from this example, the macro has no clearly defined
argument types and return value type. The types to be used for arguments and
return values depend on the context in which this macro is used. Here from the
context is known that X, Y and Z stand for the major version, minor version and
the patch level which are declared to be 8 bit unsigned integers. From the
context it is also clear, that the macro returns true or false, hence the
function should return a Boolean value.
