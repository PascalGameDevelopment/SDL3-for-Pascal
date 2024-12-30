{
  This file is part of:

    SDL3 for Pascal
    (https://github.com/PascalGameDevelopment/SDL3-for-Pascal)
    SPDX-License-Identifier: Zlib
}

{ Example is based on examples/renderer/02-primitives/primitives.c }

program primitives;

uses
  SDL3, SysUtils;

var
  Window: PSDL_Window = nil;
  Renderer: PSDL_Renderer = nil;
  Points: array[0..499] of TSDL_FPoint;
  Rect: TSDL_FRect;
  I: Integer;

begin
  if not SDL_Init(SDL_INIT_VIDEO) then
  begin

    SDL_Log(PChar(Format('Couldn''t initialize SDL: %s', [SDL_GetError])));
    Exit;
  end;

  if not SDL_CreateWindowAndRenderer('primitives', 640, 480, 0, @Window, @Renderer) then
  begin
    SDL_Log(PChar(Format('Couldn''t create window/renderer: %s', [SDL_GetError])));
    Exit;
  end;

  { Set up some random points }
  Randomize;
  for i := 0 to High(Points)-1 do
  begin
    Points[I].x:=(Random(10000)/100)*4.4 + 100.0;
    Points[I].y:=(Random(10000)/100)*2.8 + 100.0;
  end;

  { as you can see from this, rendering draws over whatever was drawn before it. }
  SDL_SetRenderDrawColor(Renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);  { dark gray, full alpha }
  SDL_RenderClear(Renderer);  { start with a blank canvas. }

  { draw a filled rectangle in the middle of the canvas. }
  SDL_SetRenderDrawColor(Renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);  { blue, full alpha }
  Rect.x := 100;
  Rect.y := 100;
  Rect.w := 440;
  Rect.h := 280;
  SDL_RenderFillRect(Renderer, @Rect);

  { draw some points across the canvas. }
  SDL_SetRenderDrawColor(Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);  { red, full alpha }
  SDL_RenderPoints(Renderer, @Points[0], High(Points)-1);

  { draw a unfilled Rectangle in-set a little bit. }
  SDL_SetRenderDrawColor(Renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);  { green, full alpha }
  Rect.x := Rect.x+30;
  Rect.y := Rect.y+30;
  Rect.w := Rect.w-60;
  Rect.h := Rect.h-60;
  SDL_RenderRect(Renderer, @Rect);

  { draw two lines in an X across the whole canvas. }
  SDL_SetRenderDrawColor(Renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);  { yellow, full alpha }
  SDL_RenderLine(Renderer, 0, 0, 640, 480);
  SDL_RenderLine(Renderer, 0, 480, 640, 0);

  SDL_RenderPresent(Renderer);  { put it all on the screen! }

  SDL_Delay(2000);

  SDL_Quit();
end.

