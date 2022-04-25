// SPDX-License-Identifier: zlib-acknowledgement
#pragma once

union V2
{
  struct
  {
    r32 x, y;
  };

  struct
  {
    r32 w, h;
  };

  r32 e[2];
};

union V3
{
  struct 
  {
    r32 x, y, z;
  };

  struct 
  {
    r32 r, g, b;
  };

  r32 e[3];
};

union V4
{
  struct
  {
    union
    {
      V3 xyz;
      struct
      {
        r32 x, y, z;
      };
    };
    r32 w;
  };

  struct
  {
    union
    {
      V3 rgb;
      struct
      {
        r32 r, g, b;
      };
    };
    r32 a;
  };

  r32 e[4];
};


