// SPDX-License-Identifier: zlib-acknowledgement

#include "types.h"
#include "debug.h"
#include "math.h"
#include "vector.h"

int
main(int argc, char *argv[])
{
  BP();

  if (SDL_Init(SDL_INIT_VIDEO) == 0)
  {
    V2 window_dim = {1280, 720};
    SDL_Window *window = SDL_CreateWindow("Name", SDL_WINDOWPOS_CENTERED, 
                         SDL_WINDOWPOS_CENTERED, window_dim.w, window_dim.h, 0);

    // TODO(Ryan): Add SDL_RENDERER_PRESENTVSYNC flag when doing animations
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);

    // IMPORTANT(Ryan): Mouse values line up to this logical width and height
    SDL_RenderSetLogicalSize(renderer, window_dim.w, window_dim.h);
    SDL_RenderSetIntegerScale(renderer, 1);

    V2 back_buffer_dim = window_dim;
    SDL_Texture *back_buffer = SDL_CreateTexture(renderer, 
                               SDL_PIXELFORMAT_RGBA8888, 
                               SDL_TEXTUREACCESS_STREAMING,
                               back_buffer_dim.w, back_buffer_dim.h);

    u32 *pixels = malloc(back_buffer_dim.w * back_buffer_dim.h * sizeof(u32));

    BackBuffer back_buffer = {};

    bool want_to_run = true;
    while (want_to_run)
    {
      SDL_Event event = {};
      while (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT)
        {
          want_to_run = false;
        }
      }

     // Set every pixel to white.
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                pixels[x + y * width] =
                    SDL_MapRGBA(window_surface->format, 200, 100, 250, 255);
            }
        }

    }

    SDL_RenderClear(Renderer);
    SDL_UpdateTexture(screen_texture, NULL, pixels, width * 4);
    SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
    SDL_RenderPresent(Renderer);
  }
  else
  {

  }
        SDL_DestroyTexture(*ppTexture);

        SDL_DestroyRenderer(*ppRenderer);

        SDL_DestroyWindow(*ppWindow);
        
        SDL_Quit();

  return 0;
}


    // The Back Buffer texture may be stored with an extra bit of width (pitch) on the video card in order to properly
    // align it in VRAM should the width not lie on the correct memory boundary (usually four bytes).
    int32_t pitch = 0;

    // This will hold a pointer to the memory position in VRAM where our Back Buffer texture lies
    uint32_t* pPixelBuffer = nullptr;

    // Lock the memory in order to write our Back Buffer image to it
    if (!SDL_LockTexture(pTexture, NULL, (void**)&pPixelBuffer, &pitch))
    {
        // The pitch of the Back Buffer texture in VRAM must be divided by four bytes
        // as it will always be a multiple of four
        pitch /= sizeof(uint32_t);

        // Fill texture with randomly colored pixels
        for (uint32_t i = 0; i < g_kRenderWidth * g_kRenderHeight; ++i)
            pPixelBuffer[i] = ARGB(FastRand() % 256, FastRand() % 256, FastRand() % 256, 255);

        // Unlock the texture in VRAM to let the GPU know we are done writing to it
        SDL_UnlockTexture(pTexture);

        // Copy our texture in VRAM to the display framebuffer in VRAM
        SDL_RenderCopy(pRenderer, pTexture, NULL, NULL);

        // Copy the VRAM framebuffer to the display
        SDL_RenderPresent(pRenderer);

        return 0;
    }
