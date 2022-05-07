// SPDX-License-Identifier: zlib-acknowledgement
#pragma once

#define VECTOR_SIZE(amount, type) \
  vector_size(amount * sizeof(type))

typedef r32 v2 __attribute__((VECTOR_SIZE(2, r32)));
typedef r32 v3 __attribute__((VECTOR_SIZE(3, r32)));
typedef r32 v4 __attribute__((VECTOR_SIZE(4, r32)));

typedef union V2
{
  v2 vec;
  struct
  {
    r32 x, y;
  };
  r32 e[2];
} V2;

typedef union V3
{
  v3 vec;
  struct
  {
    r32 x, y, z;
  };
  r32 e[3];
} V3;

typedef union V4
{
  v4 vec;
  struct
  {
    r32 x, y, z, w;
  };
  r32 e[4];
} V4;
