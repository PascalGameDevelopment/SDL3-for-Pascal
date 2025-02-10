{
  This file is part of:

    SDL3 for Pascal
    (https://github.com/PascalGameDevelopment/SDL3-for-Pascal)
    SPDX-License-Identifier: Zlib
}

{ Test SDL3_image routines }

program testsdl3imageunit;

uses
  SDL3, SDL3_image;

var
  Window: PSDL_Window = nil;
  Renderer: PSDL_Renderer = nil;
  ImageSurface: PSDL_Surface = nil;
  ImageTexture: PSDL_Texture = nil;

procedure RenderImage(file_:PChar);
begin
  ImageSurface := IMG_Load(file_);
  ImageTexture := SDL_CreateTextureFromSurface(Renderer, ImageSurface);
  SDL_RenderClear(Renderer);
  SDL_RenderTexture(Renderer, ImageTexture, nil, nil);
  SDL_RenderPresent(Renderer);
  SDL_Delay(1000);
  SDL_RenderClear(Renderer);
  SDL_DestroyTexture(ImageTexture);
  SDL_DestroySurface(ImageSurface);
end;

begin

  SDL_Log('Linked SDL3_image version: %d',[IMG_Version]);

  if not SDL_Init(SDL_INIT_VIDEO) then
  begin
    SDL_Log('Couldn''t initialize SDL: %s', [SDL_GetError]);
    Exit;
  end;

  if not SDL_CreateWindowAndRenderer('Images', 640, 480, 0, @Window, @Renderer) then
  begin
    SDL_Log('Couldn''t create window/renderer: %s', [SDL_GetError]);
    Exit;
  end;

  RenderImage('sample.bmp');
  RenderImage('sample.png');
  RenderImage('sample.jpg');

  SDL_Quit();

end.

