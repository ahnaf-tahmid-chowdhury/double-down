

#include <iostream>

#include "test_utils.hpp"

#include "double_down/RTI.hpp"

using namespace double_down;

int main() {

  // create new MOAB instance
  moab::Interface* MBI = new moab::Core();

  moab::ErrorCode rval;

  rval = MBI->load_file("../test_files/sphere.h5m");
  MB_CHK_SET_ERR(rval, "Failed to load test file");

  std::unique_ptr<RayTracingInterface> RTI(new RayTracingInterface(MBI));

  rval = RTI->init();
  MB_CHK_SET_ERR(rval, "Failed to initialize the RTI.");

  moab::Range vols;
  rval = RTI->get_vols(vols);
  MB_CHK_SET_ERR(rval, "Failed to get volumes from the RTI.");

  moab::EntityHandle sphere_vol = vols[0];

  // fire a test ray
  double org[3] = {0.0, 0.0, 0.0};
  double dir[3] = {1.0, 0.0, 0.0};

  double dist = 0.0;
  moab::EntityHandle surf;

  RTI->ray_fire(sphere_vol, org, dir, surf, dist);

  if (dist == 0.0) { return 1; }
  if (surf == 0) { return 1; }

  // check bounding box return
  std::array<double, 3> llc, urc;
  RTI->get_bbox(sphere_vol, llc, urc);

  double sphere_bound = 10.0;
  sphere_bound -= 1e-04; // make allowance for faceting tolerance
  for (int i = 0; i < 3; i++) {
    if (llc[i] >= -sphere_bound) { return 1; }
    if (urc[i] <= sphere_bound) { return 1;}
  }

  return 0;
}
