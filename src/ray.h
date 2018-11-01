#pragma once

#include "embree2/rtcore_ray.h"

// This might go away with the alorithm update
enum RayFireType { RF, PIV };

struct RTCRay2 : RTCRay { int rf_type;

};

// TO-DO: there should be a few more double elements here (barycentric coords)
struct RTCDRay: RTCRay2 {
  void set_org(double o[3]) {
    org[0] = o[0]; org[1] = o[1]; org[2] = o[2];
    dorg[0] = o[0]; dorg[1] = o[1]; dorg[2] = o[2];
  }

  void set_dir(double o[3]) {
    dir[0] = o[0]; dir[1] = o[1]; dir[2] = o[2];
    ddir[0] = o[0]; ddir[1] = o[1]; ddir[2] = o[2];
  }

  void set_len(double len) {
    tfar = len;
    dtfar = len;
  }

  double dorg[3], ddir[3], dtfar;
};
