// SPDX-License-Identifier: zlib-acknowledgement

#include "types.h"
#include "debug.h"
#include "math.h"
#include "vector.h"

#include "desktop.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

INTERNAL void
update_and_render(SDL_Renderer *renderer, Input *input)
{
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);
}

int
main(int argc, char *argv[])
{
  BP();

  if (SDL_Init(SDL_INIT_VIDEO) == 0)
  {
    if (TTF_Init() == 0)
    {

    }
    else
    {
      BP_MSG(TTF_GetError()); 
    }

int
main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_VIDEO) == 0)
  {
    V2u window_dim = {1280, 720};
    SDL_Window *window = SDL_CreateWindow("Name", SDL_WINDOWPOS_CENTERED, 
                          SDL_WINDOWPOS_CENTERED, window_dim.w, window_dim.h, 
                          SDL_WINDOW_RESIZABLE);
    if (window != NULL)
    {
      SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
      if (renderer != NULL)
      {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // IMPORTANT(Ryan): Mouse values line up to this logical width and height
        SDL_RenderSetLogicalSize(renderer, window_dim.w, window_dim.h);
        SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

        V2u back_buffer_dim = window_dim;
        SDL_Texture *back_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                                                             SDL_TEXTUREACCESS_STREAMING,
                                                             back_buffer_dim.w, 
                                                             back_buffer_dim.h);
        if (back_buffer_texture != NULL)
        {
          u32 back_buffer_size = back_buffer_dim.w * back_buffer_dim.h * sizeof(u32);
          u32 memory_size = GIGABYTES(1);
          void *mem = calloc(back_buffer_size + memory_size, 1);
          if (mem != NULL)
          {
            BackBuffer back_buffer = {};
            back_buffer.dim = back_buffer_dim;
            back_buffer.pixels = (u32 *)mem;

            // TODO(Ryan): Will have to call again if in fullscreen mode
            Input input = {};
            u32 refresh_rate = get_refresh_rate(window);
            input.update_dt = 1.0f / (r32)refresh_rate;
            
            Memory memory = {};
            memory.size = memory_size;
            memory.mem = (u8 *)mem + back_buffer_size;

            Functions functions = {};
            functions.read_entire_file = read_entire_file;
            functions.free_file_result = free_file_result;

            LoadableUpdateAndRender loadable_update_and_render = {};
            loadable_update_and_render.base_file = "/home/ryan/prog/personal/gui/run/gui.so";
            loadable_update_and_render.toggle_file = "/home/ryan/prog/personal/gui/run/gui.so.toggle";

            UpdateAndRender current_update_and_render = \
              reload_update_and_render(&loadable_update_and_render);
            if (current_update_and_render != NULL)
            {
              DebugFrameEndInfo debug_info = {};

              u64 last_counter = SDL_GetPerformanceCounter(); 

              bool want_to_run = true;
              while (want_to_run)
              {
                // FRAME_MARKER();
                
                SDL_Event event = {};
                // BEGIN_BLOCK(EventProcessing);
                while (SDL_PollEvent(&event))
                {
                  if (event.type == SDL_QUIT)
                  {
                    want_to_run = false;
                  }
                }
                // END_BLOCK();

                debug_info.events_processed = get_elapsed_seconds(last_counter, 
                                                                  SDL_GetPerformanceCounter());

                SDL_RenderClear(renderer);

                current_update_and_render = \
                  reload_update_and_render(&loadable_update_and_render);

                s32 pitch = 0;
                if (SDL_LockTexture(back_buffer_texture, NULL, (void **)&back_buffer.pixels, 
                      &pitch) == 0)
                {
                  current_update_and_render(&back_buffer, &input, &memory, &functions);

                  SDL_UnlockTexture(back_buffer_texture);

                  SDL_RenderCopy(renderer, back_buffer_texture, NULL, NULL);
                }
                else
                {
                  BP_MSG(SDL_GetError());
                }

                SDL_RenderPresent(renderer);

                u64 end_counter = SDL_GetPerformanceCounter();
                last_counter = end_counter;

                debug_info.end_of_frame = get_elapsed_seconds(last_counter, end_counter);

                // if (game_functions->debug_frame_end)
                // {
                // IMPORTANT(Ryan): No longer need this, as store in globals
                // game_functions->debug_frame_end(&memory, &debug_info)
                // };
              }
            }
            else
            {
              BP_MSG(SDL_GetError());
              SDL_Quit();
              return 1;
            }
          }
          else
          {
            EBP();
            SDL_Quit();
            return 1;
          }
        }
        else
        {
          BP_MSG(SDL_GetError());
          SDL_Quit();
          return 1;
        }
      }
      else
      {
        BP_MSG(SDL_GetError());
        SDL_Quit();
        return 1;
      }
    }
    else
    {
      BP_MSG(SDL_GetError());
      SDL_Quit();
      return 1;
    }
  }
  else
  {
    BP_MSG(SDL_GetError());
    return 1;
  }

  SDL_Quit();

  return 0;
}
    

// TTF_Init();

  SDL_DestroyTexture(back_buffer_texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

