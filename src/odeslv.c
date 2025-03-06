#include "../lib/odeslv.h"
#include "../lib/types/types.h"

void rkstep(soe state, rkparams params) {
  double a[6] = {};
  double b[15] = {};
  double c[6];
  double cstar[6];

  for (uint i = 0; i < 6; i++) {
    for (uint j = 0; j < state.y.size; j++) {
    }
  }
}
