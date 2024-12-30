unit SDL3;

{
                                SDL3-for-Pascal
                               =================
          Pascal units for SDL3 - Simple Direct MediaLayer, Version 3

  (to be extended - todo)

}

{$I sdl.inc}

interface

  {$IFDEF WINDOWS}
    uses
      {$IFDEF FPC}
      ctypes,
      {$ENDIF}
      Windows;
  {$ENDIF}

  {$IF DEFINED(UNIX) AND NOT DEFINED(ANDROID)}
    uses
      {$IFDEF FPC}
      ctypes,
      UnixType,
      {$ENDIF}
      {$IFDEF DARWIN}
      CocoaAll;
      {$ELSE}
      X,
      XLib;
      {$ENDIF}
  {$ENDIF}

  {$IF DEFINED(UNIX) AND DEFINED(ANDROID) AND DEFINED(FPC)}
    uses
      ctypes,
      UnixType;
  {$ENDIF}

const

  {$IFDEF WINDOWS}
    SDL_LibName = 'SDL3.dll';
  {$ENDIF}

  {$IFDEF UNIX}
    {$IFDEF DARWIN}
      SDL_LibName = 'libSDL3.dylib';
      {$IFDEF FPC}
        {$LINKLIB libSDL2}
      {$ENDIF}
    {$ELSE}
      {$IFDEF FPC}
        SDL_LibName = 'libSDL3.so';
      {$ELSE}
        SDL_LibName = 'libSDL3.so.0';
      {$ENDIF}
    {$ENDIF}
  {$ENDIF}

  {$IFDEF MACOS}
    SDL_LibName = 'SDL3';
    {$IFDEF FPC}
      {$linklib libSDL3}
    {$ENDIF}
  {$ENDIF}

{$I ctypes.inc}                           // C data types

{ The include file translates
  corresponding C header file.
                                          Inc file was updated against
  SDL_init.inc --> SDL_init.h             this version of the header file: }
{$I SDL_init.inc}                         // 3.1.6-prev
{$I SDL_log.inc}                          // 3.1.6-prev
{$I SDL_version.inc}                      // 3.1.6-prev
{$I SDL_revision.inc}                     // 3.1.6-prev
{$I SDL_stdinc.inc}                       // 3.1.6-prev (unfinished)
{$I SDL_rect.inc}                         // 3.1.6-prev
{$I SDL_properties.inc}                   // 3.1.6-prev
{$I SDL_pixels.inc}                       // 3.1.6-prev
{$I SDL_blendmode.inc}                    // 3.1.6-prev
{$I SDL_iostream.inc}                     // 3.1.6-prev (unfinished)
{$I SDL_surface.inc}                      // 3.1.6-prev
{$I SDL_video.inc}                        // 3.1.6-prev
{$I SDL_render.inc}                       // 3.1.6-prev
{$I SDL_timer.inc}                        // 3.1.6-prev (unfinished)
{$I SDL_error.inc}                        // 3.1.6-prev


implementation

{ Macros from SDL_version.h }
function SDL_VERSIONNUM(major, minor, patch: Integer): Integer;
begin
  Result:=(major*1000000)+(minor*1000)+patch;
end;

function SDL_VERSIONNUM_MAJOR(version: Integer): Integer;
begin
  Result:=version div 1000000;
end;

function SDL_VERSIONNUM_MINOR(version: Integer): Integer;
begin
  Result:=(version div 1000) mod 1000;
end;

function SDL_VERSIONNUM_MICRO(version: Integer): Integer;
begin
  Result:=version mod 1000;
end;

function SDL_VERSION: Integer;
begin
  Result:=SDL_VERSIONNUM(SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION);
end;

function SDL_VERSION_ATLEAST(X, Y, Z: Integer): Boolean;
begin
  if (SDL_VERSION >= SDL_VERSIONNUM(X, Y, Z)) then
    Result:=True
  else
    Result:=False;
end;

{ Macros from SDL_rect.h }
procedure SDL_RectToFRect(const rect: PSDL_Rect; frect: PSDL_FRect);
begin
  frect^.x:=cfloat(rect^.x);
  frect^.y:=cfloat(rect^.y);
  frect^.w:=cfloat(rect^.w);
  frect^.h:=cfloat(rect^.h);
end;

function SDL_PointInRect(const p: PSDL_Point; const r: PSDL_Rect): cbool;
begin
  Result :=
    (p <> nil) and (r <> nil) and (p^.x >= r^.x) and (p^.x < (r^.x + r^.w)) and
    (p^.y >= r^.y) and (p^.y < (r^.y + r^.h));
end;

function SDL_RectEmpty(const r: PSDL_Rect): cbool;
begin
  Result := (r = nil) or (r^.w <= 0) or (r^.h <= 0);
end;

function SDL_RectsEqual(const a: PSDL_Rect; const b: PSDL_Rect): cbool;
begin
  Result := (a <> nil) and (b <> nil) and (a^.x = b^.x) and (a^.y = b^.y) and
    (a^.w = b^.w) and (a^.h = b^.h);
end;

function SDL_PointInRectFloat(const p: PSDL_FPoint; const r: PSDL_FRect): cbool;
begin
  Result :=
    (p <> nil) and (r <> nil) and (p^.x >= r^.x) and (p^.x <= (r^.x + r^.w)) and
    (p^.y >= r^.y) and (p^.y <= (r^.y + r^.h));
end;

function SDL_RectEmptyFloat(const r: PSDL_FRect): cbool;
begin
  Result := (r = nil) or (r^.w < cfloat(0.0)) or (r^.h < cfloat(0.0));
end;

function SDL_RectsEqualEpsilon(const a: PSDL_Frect; const b: PSDL_FRect;
  const epsilon: cfloat): cbool;
begin
  Result :=
    (a <> nil) and (b <> nil) and ((a = b) or
    ((SDL_fabsf(a^.x - b^.x) <= epsilon) and
    (SDL_fabsf(a^.y - b^.y) <= epsilon) and
    (SDL_fabsf(a^.w - b^.w) <= epsilon) and
    (SDL_fabsf(a^.h - b^.h) <= epsilon)));
end;

function SDL_RectsEqualFloat(const a: PSDL_FRect; b: PSDL_FRect): cbool;
begin
  Result := SDL_RectsEqualEpsilon(a, b, SDL_FLT_EPSILON);
end;

{ Macros from SDL_video.h }
function SDL_WINDOWPOS_UNDEFINED_DISPLAY(X: Integer): Integer;
begin
  Result := (SDL_WINDOWPOS_CENTERED_MASK or X);
end;

function SDL_WINDOWPOS_ISUNDEFINED(X: Integer): Boolean;
begin
  Result := (X and $FFFF0000) = SDL_WINDOWPOS_UNDEFINED_MASK;
end;

function SDL_WINDOWPOS_CENTERED_DISPLAY(X: Integer): Integer;
begin
  Result := (SDL_WINDOWPOS_CENTERED_MASK or X);
end;

function SDL_WINDOWPOS_ISCENTERED(X: Integer): Boolean;
begin
  Result := (X and $FFFF0000) = SDL_WINDOWPOS_CENTERED_MASK;
end;

end.

